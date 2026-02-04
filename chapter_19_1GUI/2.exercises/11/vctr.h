


#include <std_lib_facilities.h>


//------------------------------------------------------------------------------

namespace ucptr
{
	template< typename T > class unique_ptr {
	public:
		unique_ptr() : link{nullptr}		{  }
		explicit unique_ptr(T* p) : link{p}		{  }
		~unique_ptr() { if(link)	delete link; }
		
		//Копирующие конструктор и присваивание запрещены
		unique_ptr(const unique_ptr& u) = delete;
		unique_ptr& operator=(const unique_ptr& v) = delete;
		
		//Перемещающие конструктор и присваивание запрещены
		unique_ptr(unique_ptr&& v) = delete;
		unique_ptr& operator=(unique_ptr&& v) = delete;
		
		T& operator*() const		{ return *link; }
		T* operator->() const		{ return link; }
		
		T* release() {
			T* p = link;
			link = nullptr;
			return p;
		}
		
	private:
		T* link;
	};
	
	template< typename T > class counted_ptr {
	public:
		counted_ptr() : n{nullptr}, link{nullptr}		{  }
		explicit counted_ptr(const T& p) : n{new int(1)}, link{new T (p)}		{  }
		~counted_ptr() {
			--(*n);
			if(/*link  &&*/  *n == 0) {
				if(n)		delete n;
				if(link)	delete link;
			}
		}
		
		//Копирующие конструктор и присваивание запрещены
		counted_ptr(const counted_ptr& u) : n{u.n}, link{u.link}
		{
			//Если хоть один из указателей равен нулю - counted_ptr содержит пустые указатели
			if(!n  ||  n==0  ||  !link) {
				if(n)		delete n;
				if(link)	delete link;
				n = nullptr;
				link = nullptr;
			}
			else				++(*u.n);	//Новый совладелец
		}
		
		counted_ptr& operator=(const counted_ptr& u) {
			if(!u.n || !u.link) { }
			else {
				++(*u.n);
				n = u.n;
				link = u.link;
			}
			
			return *this;
		}
		
		//Перемещающие конструктор и присваивание запрещены
		counted_ptr(counted_ptr&& u) {
			if(!u.n || !u.link) {
				n = nullptr;
				link = nullptr;
			}
			
			else {
				n = u.n;
				link = u.link;
			}
			
			u.n = nullptr;
			u.link = nullptr;
		}
		
		counted_ptr& operator=(counted_ptr&& u) {
			if(!u.n || !u.link)		{  }
			else		{ n = u.n;		link = u.link; }
			u.n = nullptr;
			u.link = nullptr;
			
			return *this;
		}
		
		T& operator*() const		{ return *link; }
		T* operator->() const		{ return link; }
		int owners_num() const		{  return *n;  }
		
		T* release() {
			T* p = link;
			*n = 0;
			link = nullptr;
			return p;
		}
		
	private:
		int* n;
		T* link;
	};
}

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
class vctr : private vctr_base<T,A> {
public:
	using vctr_base<T, A>::elem;
	using vctr_base<T, A>::sz;
	using vctr_base<T, A>::alloc;
	using vctr_base<T, A>::space;
	
	vctr() : vctr_base<T,A>{}		{ }
	
	//Конструктор со списком инициализации
	explicit vctr(initializer_list<T> lst) : vctr_base<T,A>{}
	{
		//cout << "\nCalled vctr(initializer_list<T> lst)\n";
		
		reserve(lst.size());
		for (int i = 0; i < lst.size(); ++i)		alloc.construct(&elem[i], *(lst.begin()+i)); //Копируем
		sz = lst.size();
	}
	
	//Копирующие конструктор и присваивание
	vctr(const vctr& v) : vctr_base<T,A>{v.alloc, v.sz}
	{
		//cout << "\nCalled vctr(const vctr& v)\n";
		
		reserve(v.sz);
		for (int i = 0; i < v.sz; ++i)		alloc.construct(&elem[i], v[i]); //Копируем
		sz = v.sz;
	}
	vctr& operator=(const vctr& v);	// Копирующее присваивание
	
	//Перемещающие конструктор и присваивание
	vctr(vctr&& v) : vctr_base<T,A>{v.alloc, v.sz}
	{
		//cout << "\nCalled vctr(vctr&& v)\n";
		
		reserve(v.sz);
		for (int i = 0; i < v.sz; ++i)		alloc.construct(&elem[i], v[i]); //Копируем
		sz = v.sz;
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
	//cout << "\nCalled vctr<T,A>::operator=(const vctr<T,A>& v)\n";
	
	if (this == &v)		return *this;	//Проверка на самоприсваивание
	
	for (T* q = elem; q != elem + sz; ++q)		alloc.destroy(q);	//Удаляем

	if(v.sz > space)	reserve(v.sz);
	
	for (int i = 0; i < v.sz; ++i)		alloc.construct(&elem[i], v[i]); //Копируем
	
	space = sz = v.sz;		//Устанавливаем новый размер
	return *this;
}

//------------------------------------------------------------------------------

//Перемещающее присваивание
template<typename T, typename A>
vctr<T,A>& vctr<T,A>::operator=(vctr<T,A>&& v)
{
	//cout << "\nCalled vctr<T,A>::operator=(vctr<T,A>&& v)\n";
	
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
	if (space == 0)				reserve(8);				//Для начала выделяем память для 8 элементов
	else if (sz == space)		reserve(2 * space);		//Удваиваем размер выделяемой памяти
	
	alloc.construct(&elem[sz], val);	//Добавляем указанное значение в конец вектора
	++sz;				// Кол-в элементов увеличивается на 1
}

template<class T, class A>
void vctr<T,A>::reserve(int newalloc)
{
	if(newalloc <= space)	return;		// Размер никогда не уменьшается
	
	vctr<T, A> b{};	// Выделение новой памяти
	b.elem = b.alloc.allocate(newalloc);
	b.space = newalloc;
	
	//Копирование:
	for (int i = 0; i < sz; ++i)		b.push_back(elem[i]);

	// Освобождение памяти занятой старыми элементами
	for(int i=0; i<sz; ++i)		alloc.destroy(&elem[i]);

	// Память elem будет принадлежать объекту b после выполнения swap и соотв. освободится деструктором при выходе из ф-ции
	swap(*this, b);			// Обмен представлений
}

//------------------------------------------------------------------------------

