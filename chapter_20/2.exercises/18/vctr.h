


#include <std_lib_facilities.h>



//------------------------------------------------------------------------------

namespace alc
{
	template<typename T>
	struct allocator {
		T* allocate(int n);					//Выделение памяти для n объектов типа T
		
		//Освобождение памяти, занятой n объектами типа T начиная с адреса p
		void deallocate(T* p, int n = 0) { /*if(p)*/		free(p); }
		
		//Создание объекта типа T со значением v по адресу p
		//Размещающий new (не в случайной ячейке динамической памяти, а в ячейке памяти обозначенной адресом указателя)
		void construct(T* p, const T& v) { /*if(p)*/		new(p) T{ v }; }

		//Уничтожение объекта T по адресу p
		void destroy(T* p) { /*if(p)*/		p->~T(); /*Явный вызов деструктора*/ }
	};


	//Выделение памяти для n объектов типа T
	template<typename T>
	T* allocator<T>::allocate(int n) {
		if(n == 0)		return nullptr;
		
		void* p = malloc( sizeof(T) * n );
		if(p == 0) {
			string err_msg = "unable to allocate " + to_string(sizeof(T) * n) + " bytes of memory for " + to_string(n) + " " + typeid(T{}).name() + " objects";
			error(err_msg);
		}
		return (T*)p; //static_cast<T*>(p); //(T*)p; //dynamic_cast<T*>(p); //&T(p);
	}
}

//------------------------------------------------------------------------------

// 19.5.6 - RAII для vector
template<typename T, typename A>
struct vctr_base {
	typedef unsigned long size_t;
	class iterator;		//Тип - член класса: iterator
	
	A alloc;			// Распределитель памяти
	iterator elem;		// Начало выделенной памяти
	size_t sz;			// Количество элементов
	size_t space;		// Размер выделенной памяти (размер+свободные ячейки памяти размером для типа T)
	
	vctr_base() : elem{nullptr}, sz{0}, space{0}	{  }
	vctr_base(const A& a, size_t n) : alloc{a}, elem{alloc.allocate(n)}, sz{0}, space{n}
	{ /*for(T* p = elem; p != elem+n; ++p)	alloc.construct(p, T{});*/ }
	
	~vctr_base() { if(&elem)		alloc.deallocate(&elem, space); }
};

//------------------------------------------------------------------------------

template<class T, typename A>
class vctr_base<T,A>::iterator {
	T* curr;	//Текущий узел
	T* first;	//Самый первый узел в последовательности
	T* last;	//Узел следующий за последним
	
public:
	iterator(T* p, unsigned int n = 0) : curr(p), first(p), last(p+n)	{  }
	
	iterator& operator++()											//Вперёд
	{
		if(curr == last)	error("end of sequence already reached [vctr iterator operator++()]");
		if(curr)			++curr;
		return *this;
	}
	
	iterator& operator--()											//Назад
	{
		if(curr == first)	error("first element of sequence already reached [vctr iterator operator--()]");
		if(curr)			--curr;
		return *this;
	}
	
	T& operator[](size_t n) {
		//if(curr+n < last)		return *(curr[n]);
		if(curr+n < last)		return curr[n];
		else					error("range error [vctr iterator operator[]()] with index " + to_string(curr+n-first));
	}
	const T& operator[](size_t n) const {
		if(curr+n < last)		return curr[n];
		else					error("range error [vctr iterator operator[]() const] with index " + to_string(curr+n-first));
	}
	
	T* operator&()				{ return curr; }					//Получение указателя
	const T* operator&() const	{ return curr; }					//Получение указателя
	
	T& operator*()				{ return *curr; }					//Разыменование (получение значения)
	const T& operator*() const	{ return *curr; }					//Разыменование (получение значения)
	T& operator->()				{ return *curr; }					//Получение значения
	const T& operator->() const	{ return *curr; }					//Получение значения
	
	iterator& operator+=(size_t n) {
		if (n > (last-curr))		error("range error [vctr iterator operator+=()] with index " + to_string(curr+n-first));
		curr += n;					return *this;
	}
	friend iterator operator+(iterator i, size_t n)		{ i += n;		return i; }
	
	iterator& operator-=(size_t n) {
		if (n > (curr-first))		error("range error [vctr iterator operator-=()] with index " + to_string(curr-n-first));
		curr -= n;				return *this;
	}
	friend iterator operator-(iterator i, size_t n)	{ i -= n;		return i; }
	friend size_t operator-(const iterator& i1, const iterator& i2)		{ return (i1.curr - i2.curr); }	//Количество объектов помещающихся между двумя адресами ( (адрес1 - адрес2)/размер_объекта )
	
	friend bool operator>(const iterator& a, const iterator& b)		{ return a.curr>b.curr; }
	friend bool operator<(const iterator& a, const iterator& b)		{ return a.curr<b.curr; }
	friend bool operator<=(const iterator& a, const iterator& b)	{ return a.curr<=b.curr; }
	friend bool operator>=(const iterator& a, const iterator& b)	{ return a.curr>=b.curr; }
	friend bool operator==(const iterator& a, const iterator& b)	{ return a.curr==b.curr; }
	friend bool operator!=(const iterator& a, const iterator& b)	{ return !(a==b); }
};

//------------------------------------------------------------------------------

template<typename T, typename A = alc::allocator<T> >
class vctr : private vctr_base<T,A> {
	using vctr_base<T, A>::elem;
	using vctr_base<T, A>::sz;
	using vctr_base<T, A>::alloc;
	using vctr_base<T, A>::space;
	using iterator = typename vctr_base<T,A>::iterator;

public:
	vctr() : vctr_base<T,A>{}		{  }
	vctr(size_t n) : vctr_base<T,A>{}	{ reserve(n); }
	vctr(const A& a, size_t n) : vctr_base<T,A>{a, n}		{  }
	
	//Конструктор со списком инициализации
	explicit vctr(initializer_list<T> lst) : vctr_base<T,A>{}	{ for (size_t i = 0; i < lst.size(); ++i)		push_back( *(lst.begin()+i) ); }
	
	//Копирующие конструктор и присваивание
	vctr(const vctr& v) : vctr_base<T,A>{v.alloc, v.sz}			{ for (size_t i = 0; i < v.sz; ++i)		push_back( v[i] ); }
	vctr& operator=(const vctr& v);	// Копирующее присваивание
	
	//Перемещающие конструктор и присваивание
	vctr(vctr&& v) : vctr_base<T,A>{v.alloc, v.sz}
	{
		for (size_t i = 0; i < v.sz; ++i)		push_back( v[i] ); //Копируем
		v.sz = v.space = 0;		v.elem = nullptr;
	}
	vctr& operator=(vctr&& v);	// Перемещающее присваивание
	
	//Доступ к элементам с проверкой выхода за диапазон
	T& at(size_t n) {
		if (n<0 || n>=sz)		throw out_of_range("vctr range error with index [" + to_string(n) + "]");
		return elem[n];
	}
	
	const T& at(size_t n) const {
		if (n<0 || n>=sz)		throw out_of_range("const vctr range error with index [" + to_string(n) + "]");
		return elem[n];
	}
	
	//Доступ к элементам без проверки выхода за диапазон
	T& operator[](size_t n) { return elem[n]; }
	const T& operator[](size_t n) const { return elem[n]; }
	
	//Первый и последний элемент
	iterator begin() { return elem; }
	iterator end()   { return elem+sz; }
	
	size_t size() const { return sz; }
	size_t capacity() const { return space; }
	
	//Увеличение
	void resize(size_t newsize, T val = T{}); 
	void push_front(const T& val);
	void push_back(const T& val);
	void reserve(size_t newalloc);
};

//------------------------------------------------------------------------------

//Копирующее присваивание
template<typename T, typename A>
vctr<T,A>& vctr<T,A>::operator=(const vctr<T,A>& v)
{
	if (this == &v)		return *this;	//Проверка на самоприсваивание
	//cout << "\nCalled vctr<T,A>::operator=(const vctr<T,A>& v)\n";
	
	for (auto p = elem; p != elem+sz; ++p)		alloc.destroy(&p);	//Удаляем
	sz = 0;
	for (int i = 0; i < v.sz; ++i)				push_back( v[i] );	//Копируем
	
	return *this;
}

//------------------------------------------------------------------------------

//Перемещающее присваивание
template<typename T, typename A>
vctr<T,A>& vctr<T,A>::operator=(vctr<T,A>&& v)
{
	//cout << "\nCalled vctr<T,A>::operator=(vctr<T,A>&& v)\n";
	
	for (auto p = elem; p != elem+sz; ++p)		alloc.destroy(&p);	//Уничтожение старых элементов в памяти
	alloc.deallocate(&elem);
	
	elem = v.elem;		sz = v.sz;		space = v.space;
	v.space = v.sz = 0;		v.elem = nullptr;
	return *this;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void vctr<T,A>::resize(size_t newsize, T val)
{
	reserve(newsize);
	elem = iterator(&elem, newsize);
	
	//Создаём если новый размер больше кол-ва уже инициализированных объектов вектора
	for (size_t i = sz; i < newsize; ++i)		alloc.construct(&elem[i], val);
	
	//Уничтожаем если новый размер меньше кол-ва уже инициализированных объектов вектора
	for (size_t i = newsize; i < sz; ++i)		alloc.destroy(&elem[i]);
	
	sz = newsize;
}

template<typename T, typename A>
void vctr<T,A>::push_front(const T& val)
{
	if (space == 0)				reserve(8);				//Для начала выделяем память для 8 элементов
	else if (sz == space)		reserve(2 * space);		//Удваиваем размер выделяемой памяти
	
	vctr<T, A> b{alloc, space};		//Новый вектор с первым текущим элементом
	
	b.push_back(val);
	for (size_t i = 0; i < sz; ++i)		b.push_back(elem[i]);		//Копирование остальных элементов
	
	for(size_t i=0; i < sz; ++i)		alloc.destroy(&elem[i]);	//Освобождение памяти занятой старыми элементами
	
	// Память elem будет принадлежать объекту b после выполнения swap и соотв. освободится деструктором при выходе из ф-ции
	size_t tmp_sz = b.sz;
	size_t tmp_space = b.space;
	iterator tmp_elem{ &b.elem, b.sz };
	
	b.sz = sz;
	b.space = space;
	b.elem = iterator(&elem, space);
	
	sz = tmp_sz;
	space = tmp_space;
	elem = tmp_elem;
	
	//swap(*this, b);			// Обмен представлений
}

template<typename T, typename A>
void vctr<T,A>::push_back(const T& val)
{
	if (space == 0)				reserve(8);				//Для начала выделяем память для 8 элементов
	else if (sz == space)		reserve(2 * space);		//Удваиваем размер выделяемой памяти
	
	elem = iterator(&elem, sz+1);		// Кол-в элементов увеличивается на 1
	alloc.construct(&elem[sz], val);	//Добавляем указанное значение в конец вектора
	++sz;
}

template<class T, class A>
void vctr<T,A>::reserve(size_t newalloc)
{
	if(newalloc <= space)	return;		// Размер никогда не уменьшается
	
	vctr<T, A> b{};		// Выделение новой памяти
	b.elem = iterator( b.alloc.allocate(newalloc), newalloc );
	b.space = newalloc;
	
	// Копирование:
	for (size_t i = 0; i < sz; ++i)		b.push_back(elem[i]);
	b.elem = iterator( &b.elem, b.sz );
	
	// Освобождение памяти занятой старыми элементами
	for(size_t i=0; i < sz; ++i)		alloc.destroy(&elem[i]);
	
	// Память elem будет принадлежать объекту b после выполнения swap и соотв. освободится деструктором при выходе из ф-ции
	size_t tmp_sz = b.sz;
	size_t tmp_space = b.space;
	iterator tmp_elem = b.elem;
	
	b.sz = sz;
	b.space = space;
	b.elem = iterator(&elem, space);
	
	sz = tmp_sz;
	space = tmp_space;
	elem = tmp_elem;
	
	//swap(*this, b);			// Обмен представлений
}

//------------------------------------------------------------------------------