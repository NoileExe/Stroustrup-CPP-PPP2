


#include <std_lib_facilities.h>


//------------------------------------------------------------------------------

// 19.5.6 - RAII для vector
template<typename T, typename A>
struct vctr_base {
	A alloc;		// распределитель памяти
	T* elem;		// Начало выделенной памяти
	int sz;			// Количество элементов
	int space;		// Размер выделенной памяти (размер+свободные ячейки памяти размером для типа T)
	
	vctr_base() : elem{nullptr}, sz{0}, space{0}	{ }
	vctr_base(const A& a, int n) : alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n}
	{ /*for(T* p = elem; p != elem+n; ++p)	alloc.construct(p, T{});*/ }
	
	~vctr_base() { alloc.deallocate(elem, space); }
};

//------------------------------------------------------------------------------

template<typename T, typename A = std::allocator<T> >
class vctr : private vctr_base<T,A> {
public:
	using vctr_base<T, A>::elem;
	using vctr_base<T, A>::sz;
	using vctr_base<T, A>::alloc;
	using vctr_base<T, A>::space;
	
	vctr() : vctr_base<T,A>{}		{ }
	
	//Конструктор со списком инициализации
	vctr(initializer_list<T> lst) : vctr_base<T,A>{}
	{
		reserve(lst.size());
		copy(lst.begin(), lst.end(), elem);		// Копирование
		sz = lst.size();
	}
	
	//Копирующие конструктор и присваивание
	vctr(const vctr& v) : vctr_base<T,A>{v.alloc, v.sz}
		{ std::copy(v.elem, v.elem+v.sz, elem); }
	vctr& operator=(const vctr& v);	// Копирующее присваивание
	
	//Перемещающие конструктор и присваивание
	vctr(vctr&& v) : vctr_base<T,A>{v.alloc, v.sz}
	{
		std::copy(v.elem, v.elem+v.sz, elem);
		v.sz = v.space = 0;		v.elem = nullptr;
	}
	vctr& operator=(vctr&& v);	// Перемещающее присваивание
	
	//Доступ к элементам с проверкой выхода за диапазон
	T& at(int n) {
		if (n<0 || n>=sz)		throw out_of_range("vctr range error with index [" + to_string(n) + "]");
		return elem[n];
	}
	
	const T& at(int n) const {
		if (n<0 || n>=sz)		throw out_of_range("const vctr range error with index [" + to_string(n) + "]");
		return elem[n];
	}
	
	
	//Доступ к элементам без проверки выхода за диапазон
	T& operator[](int n) { return elem[n]; }
	const T& operator[](int n) const { return elem[n]; }
	
	int size() const { return sz; }
	int capacity() const { return space; }
	
	//Увеличение
	void resize(int newsize, T val = T{}); 
	void push_back(const T& val);
	void reserve(int newalloc);
};

//------------------------------------------------------------------------------

//Копирующее присваивание
template<typename T, typename A>
vctr<T,A>& vctr<T,A>::operator=(const vctr<T,A>& v)
{
	if (this == &v)		return *this;	//Проверка на самоприсваивание
	
	if (v.sz <= space) {				//Если памяти достаточно - новая память не нужна
		for (int i = 0; i < v.sz; ++i)		elem[i] = v.elem[i];		//Копирование значений
		for (int i = v.sz; i < sz; ++i)		alloc.destroy(&elem[i]);	//Если старый размер больше - удаляем лишние элементы
		sz = v.sz;
		return *this;
	}
	
	//Копируем v во вновь выделенную неинициализированную память
	T* p = alloc.allocate(v.sz);
	std::copy(v.elem, v.elem+v.sz, p);
	
	//Освобождаем ранее занятую память
	for (T* q = elem; q != elem + sz; ++q)		alloc.destroy(q);
	alloc.deallocate(elem, space);
	
	space = sz = v.sz;		//Устанавливаем новый размер
	elem = p;				//Устанавливаем указатель на новые элементы
	return *this;
}

//------------------------------------------------------------------------------

//Перемещающее присваивание
template<typename T, typename A>
vctr<T,A>& vctr<T,A>::operator=(vctr<T,A>&& v)
{
	for (T* p = elem; p != elem + sz; ++p)		alloc.destroy(p);	//Уничтожение старых элементов в памяти
	alloc.deallocate(elem);
	
	elem = v.elem;		sz = v.sz;		space = v.space;
	v.space = v.sz = 0;		v.elem = nullptr;
	return *this;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void vctr<T,A>::resize(int newsize, T val)
{
	reserve(newsize);
	
	//Создаём если новый размер больше кол-ва уже инициализированных объектов вектора
	for (int i = sz; i < newsize; ++i)		alloc.construct(&elem[i], val);
	
	//Уничтожаем если новый размер меньше кол-ва уже инициализированных объектов вектора
	for (int i = newsize; i < sz; ++i)		alloc.destroy(&elem[i]);
	
	sz = newsize;
}

template<typename T, typename A>
void vctr<T,A>::push_back(const T& val)
{
	if (space == 0)		{ reserve(8);	sz = 0; }		//Для начала выделяем память для 8 элементов
	else if (sz == space)		reserve(2 * space);		//Удваиваем размер выделяемой памяти
	
	alloc.construct(&elem[sz], val);	//Добавляем указанное значение в конец вектора
	++sz;				// Кол-в элементов увеличивается на 1
}

template<class T, class A>
void vctr<T,A>::reserve(int newalloc)
{
	if(newalloc <= space)	return;		// Размер никогда не уменьшается
	
	vctr_base<T,A> b{alloc, newalloc};	// Выделение новой памяти
	
	uninitialized_copy(b.elem, &b.elem[sz], elem);		// Копирование в неинициализированную память
	
	// Освобождение памяти занятой старыми элементами
	for(int i=0; i<sz; ++i)		alloc.destroy(&elem[i]);
	
	// Память elem будет принадлежать объекту b после выполнения swap и соотв. освободится при выходе из ф-ции
	swap< vctr_base<T,A> >(*this, b);			// Обмен представлений
}

//------------------------------------------------------------------------------

