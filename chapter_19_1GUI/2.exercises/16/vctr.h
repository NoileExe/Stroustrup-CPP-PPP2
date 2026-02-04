


#include <std_lib_facilities.h>


//------------------------------------------------------------------------------

namespace alc
{
	template<typename T> struct allocator {
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
	template<typename T> T* allocator<T>::allocate(int n) {
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
	A alloc;		// распределитель памяти
	T* elem;		// Начало выделенной памяти
	int sz;			// Количество элементов
	int space;		// Размер выделенной памяти (размер+свободные ячейки памяти размером для типа T)
	
	vctr_base() : elem{nullptr}, sz{0}, space{0}	{  }
	vctr_base(const A& a, int n) : alloc{a}, elem{alloc.allocate(n)}, sz{0}, space{n}
	{ /*for(T* p = elem; p != elem+n; ++p)	alloc.construct(p, T{});*/ }
	
	~vctr_base() { if(elem)		alloc.deallocate(elem, space); }
};

//------------------------------------------------------------------------------

template<typename T, typename A = alc::allocator<T> >
class vctr/* : private vctr_base<T,A>*/ {
private:
	vctr_base<T,A>* vb;
	
public:
	//using vctr_base<T,A>::vctr_base;
	
	vctr() : vb{new vctr_base<T,A>}		{ }
	
	//Конструктор со списком инициализации
	explicit vctr(initializer_list<T> lst) : vb{new vctr_base<T,A>}
	{
		//cout << "\nCalled vctr(initializer_list<T> lst)\n";
		
		reserve(lst.size());
		for (int i = 0; i < lst.size(); ++i)		vb->alloc.construct(&(vb->elem[i]), *(lst.begin()+i)); //Копируем
		vb->sz = lst.size();
	}
	
	//Копирующие конструктор и присваивание
	vctr(const vctr& v) : vb{ new vctr_base<T,A>{v.vb->alloc, v.vb->sz} }
	{
		//cout << "\nCalled vctr(const vctr& v)\n";
		
		reserve(v.vb->sz);
		for (int i = 0; i < v.vb->sz; ++i)		vb->alloc.construct(&(vb->elem[i]), v[i]); //Копируем
		vb->sz = v.vb->sz;
	}
	vctr& operator=(const vctr& v);	// Копирующее присваивание
	
	//Перемещающие конструктор и присваивание
	vctr(vctr&& v) : vb{ new vctr_base<T,A>{v.vb->alloc, v.vb->sz} }
	{
		//cout << "\nCalled vctr(vctr&& v)\n";
		
		reserve(v.vb->sz);
		for (int i = 0; i < v.vb->sz; ++i)		vb->alloc.construct(&(vb->elem[i]), v[i]); //Копируем
		vb->sz = v.vb->sz;
		v.vb->sz = v.vb->space = 0;		v.vb->elem = nullptr;
	}
	vctr& operator=(vctr&& v);	// Перемещающее присваивание
	
	//Доступ к элементам с проверкой выхода за диапазон
	T& at(int n) {
		if (n<0 || n>=vb->sz)		throw out_of_range("vctr range error with index [" + to_string(n) + "]");
		return vb->elem[n];
	}
	
	const T& at(int n) const {
		if (n<0 || n>=vb->sz)		throw out_of_range("const vctr range error with index [" + to_string(n) + "]");
		return vb->elem[n];
	}
	
	
	//Доступ к элементам без проверки выхода за диапазон
	T& operator[](int n) { return vb->elem[n]; }
	const T& operator[](int n) const { return vb->elem[n]; }
	
	int size() const { return vb->sz; }
	int capacity() const { return vb->space; }
	
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
	//cout << "\nCalled vctr<T,A>::operator=(const vctr<T,A>& v)\n";
	
	if (this == &v)		return *this;	//Проверка на самоприсваивание
	
	for(T* q = vb->elem; q != vb->elem + vb->sz; ++q)		vb->alloc.destroy(q);	//Удаляем

	if(v.vb->sz > vb->space)	reserve(v.vb->sz);
	
	for(int i = 0; i < v.vb->sz; ++i)		vb->alloc.construct(&(vb->elem[i]), v[i]); //Копируем
	
	vb->space = vb->sz = v.vb->sz;		//Устанавливаем новый размер
	return *this;
}

//------------------------------------------------------------------------------

//Перемещающее присваивание
template<typename T, typename A>
vctr<T,A>& vctr<T,A>::operator=(vctr<T,A>&& v)
{
	//cout << "\nCalled vctr<T,A>::operator=(vctr<T,A>&& v)\n";
	
	for(T* p = vb->elem; p != vb->elem + vb->sz; ++p)		vb->alloc.destroy(p);	//Уничтожение старых элементов в памяти
	vb->alloc.deallocate(vb->elem);
	
	vb->elem = v.vb->elem;		vb->sz = v.vb->sz;		vb->space = v.vb->space;
	v.vb->space = v.vb->sz = 0;		v.vb->elem = nullptr;
	return *this;
}

//------------------------------------------------------------------------------

template<typename T, typename A>
void vctr<T,A>::resize(int newsize, T val)
{
	reserve(newsize);
	
	//Создаём если новый размер больше кол-ва уже инициализированных объектов вектора
	for(int i = vb->sz; i < newsize; ++i)		vb->alloc.construct(&(vb->elem[i]), val);
	
	//Уничтожаем если новый размер меньше кол-ва уже инициализированных объектов вектора
	for(int i = newsize; i < vb->sz; ++i)		vb->alloc.destroy(&(vb->elem[i]));
	
	vb->sz = newsize;
}

template<typename T, typename A>
void vctr<T,A>::push_back(const T& val)
{
	if (vb->space == 0)					reserve(8);				//Для начала выделяем память для 8 элементов
	else if (vb->sz == vb->space)		reserve(2 * vb->space);		//Удваиваем размер выделяемой памяти
	
	vb->alloc.construct(&(vb->elem[vb->sz]), val);	//Добавляем указанное значение в конец вектора
	++(vb->sz);				// Кол-в элементов увеличивается на 1
}

template<class T, class A>
void vctr<T,A>::reserve(int newalloc)
{
	if(newalloc <= vb->space)	return;		// Размер никогда не уменьшается
	
	vctr<T, A> b{};	// Выделение новой памяти
	b.vb->elem = b.vb->alloc.allocate(newalloc);
	b.vb->space = newalloc;
	
	//Копирование:
	for(int i = 0; i < vb->sz; ++i)		b.push_back(vb->elem[i]);

	// Освобождение памяти занятой старыми элементами
	for(int i=0; i < vb->sz; ++i)		vb->alloc.destroy(&(vb->elem[i]));
	
	//delete vb;
	// Память elem будет принадлежать объекту b после выполнения swap и соотв. освободится деструктором при выходе из ф-ции
	swap(*vb, *(b.vb));			// Обмен представлений
}

//------------------------------------------------------------------------------

