


#include <std_lib_facilities.h>


//------------------------------------------------------------------------------

namespace alc
{
	template<typename T> struct
	allocator {
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

template<typename T> class pvector {
public:
	typedef unsigned long size_t;
	
	class iterator;		//Тип - член класса: iterator
	
	pvector() : elem{nullptr}, sz{0}, space{0}		{  }
	
	pvector(size_t n) : elem{new T*[n]}, sz{0}, space{n}
		{ for(size_t i =0; i < n; ++i)		elem[i] = nullptr; }
	
	explicit pvector(initializer_list<T> lst) : elem{new T*[lst.size()]}, sz{0}, space{lst.size()}
	{
		//cout << "pvector(initializer_list<T> lst)" << endl;
		for(size_t i=0;   i < lst.size();   ++i)		elem[i] = new T { *(lst.begin()+i) };
		sz = lst.size();
	}
	
	explicit pvector(initializer_list<T*> lst) : elem{new T*[lst.size()]}, sz{0}, space{lst.size()}
	{
		//cout << "pvector(initializer_list<T*> lst)" << endl;
		for(size_t i=0;   i < lst.size();   ++i)		elem[i] = *(lst.begin()+i);
		sz = lst.size();
	}
	
	//Копирующие конструктор и присваивание
	pvector(const pvector& v) : elem{nullptr}, sz{0}, space{0}
	{
		reserve(v.sz);		//Изменяет все члены класса
		for (int i = 0; i < v.sz; ++i)		elem[i] = new T { *v[i] }; //Копируем значения
		sz = v.sz;
	}
	pvector& operator=(const pvector& v);	// Копирующее присваивание
	
	//Перемещающие конструктор и присваивание
	pvector(pvector&& v) : elem{nullptr}, sz{0}, space{0}
	{
		reserve(v.sz);		//Изменяет все члены класса
		for (int i = 0; i < v.sz; ++i)		elem[i] = v[i]; //Копируем указатели
		sz = v.sz;
		v.sz = v.space = 0;		v.elem = nullptr;
	}
	pvector& operator=(pvector&& v);
	
	~pvector() {
		if(elem) {
			for(size_t i=0; i < sz; ++i)		delete elem[i];
			delete[] elem;
		}
	}
	
	
	//Доступ к элементам с проверкой выхода за диапазон
	T* at(size_t n) {
		if ( n>=sz )		throw out_of_range("pvector range error with index [" + to_string(n) + "]");
		return elem[n];
	}
	
	const T* at(size_t n) const {
		if ( n>=sz )		throw out_of_range("const pvector range error with index [" + to_string(n) + "]");
		return elem[n];
	}
	
	//Доступ к элементам без проверки выхода за диапазон
	T* operator[](size_t n) { return elem[n]; }
	const T* operator[] (size_t n) const { return elem[n]; }
	
	//Первый и последний элемент
	iterator begin() { return elem; }
	iterator begin() const { return elem; }
	iterator end() { return iterator(elem+sz); }
	iterator end() const { return iterator(elem+sz); }
	
	size_t size() const { return sz; }
	size_t capacity() const { return space; }
	
	//Увеличение
	void resize(size_t newsize, T val = T{});
	void push_back(const T& val);
	void reserve(size_t newalloc);
	
private:
	T** elem;		// Начало выделенной памяти (указатель на указатель - указатель на массив указателей в памяти, каждый из которых в свою очередь указывает на память со значением)
	size_t sz;		// Количество элементов
	size_t space;	// Размер выделенной памяти (размер+свободные ячейки памяти размером для типа T)
};

//------------------------------------------------------------------------------

template<class T>
class pvector<T>::iterator {
	T** curr;	//Текущий узел
	
public:
	iterator(T* p)   : curr(&p)	{  }
	iterator(T** pp) : curr(pp)	{  }
	
	iterator& operator++()	{ if(curr) ++curr;	return *this; }		//Вперёд
	iterator& operator--()	{ if(curr) --curr;	return *this; }		//Назад
	T* operator*()			{ return *curr; }						//Разыменование (получение указателя)
	T* operator->()			{ return *curr; }						//Получение указателя
	T* operator[](size_t n)	{ return curr[n]; }						//Доступ по индексу
	//T** get_current()		{ return curr; }						//Получение указателя на указатель
	
	friend bool operator==(const iterator& a, const iterator& b)
		{ return *(a.curr)==*(b.curr); }
	
	friend bool operator!=(const iterator& a, const iterator& b)
		{ return !(a==b); }
};

/*template<class Elem>
class ovector<Elem>::iterator {
	typename vector<Elem*>::iterator it;
public:
	iterator(const iterator& iter) : it(iter.it) { }
	iterator(const typename vector<Elem*>::iterator& iter) : it(iter) { }

	iterator& operator++() { ++it; return *this; }
	iterator& operator--() { --it; return *this; }

	bool operator==(const iterator& other) const { return it==other.it; }
	bool operator!=(const iterator& other) const { return !(*this==other); }

	Elem& operator*() { return **it; }
};*/

//------------------------------------------------------------------------------

//Копирующее присваивание
template<typename T>
pvector<T>& pvector<T>::operator=(const pvector<T>& v)
{
	if (this == &v)		return *this;	//Проверка на самоприсваивание
	//cout << "\nCalled pvector<T>::operator=(const pvector<T>& v)\n";
	
	pvector<T> b (v.sz);			//Выделение новой памяти
	for (size_t i = 0; i < v.sz; ++i)		b.push_back(*v[i]);		//Копируем значения

	// Память elem будет принадлежать объекту b после выполнения swap и соотв. освободится деструктором при выходе из ф-ции
	swap(*this, b);			// Обмен представлений
	
	return *this;
}

//------------------------------------------------------------------------------

//Перемещающее присваивание
template<typename T>
pvector<T>& pvector<T>::operator=(pvector<T>&& v)
{
	//cout << "\nCalled pvector<T>::operator=(pvector<T>&& v)\n";
	this->~pvector();
	
	elem = v.elem;		sz = v.sz;		space = v.space;
	v.space = v.sz = 0;		v.elem = nullptr;
	return *this;
}

//------------------------------------------------------------------------------

template<typename T>
void pvector<T>::resize(size_t newsize, T val)
{
	reserve(newsize);
	
	//Создаём если новый размер больше кол-ва уже инициализированных объектов вектора
	for (size_t i = sz; i < newsize; ++i)		elem[i] = new T {val};
	
	//Уничтожаем если новый размер меньше кол-ва уже инициализированных объектов вектора
	for (size_t i = newsize; i < sz; ++i)		{ delete elem[i];		elem[i] = nullptr; }
	
	sz = newsize;
}

template<typename T>
void pvector<T>::push_back(const T& val)
{
	if (space == 0)				reserve(8);				//Для начала выделяем память для 8 элементов
	else if (sz == space)		reserve(2 * space);		//Удваиваем размер выделяемой памяти
	
	elem[sz] = new T {val};		//Добавляем указанное значение в конец вектора
	++sz;						//Кол-во элементов увеличивается на 1
}

template<class T>
void pvector<T>::reserve(size_t newalloc)
{
	if(newalloc <= space)	return;		// Размер никогда не уменьшается
	
	pvector<T> b (newalloc);			//Выделение новой памяти
	
	// Копирование:
	for (size_t i = 0; i < sz; ++i)		b.push_back(*elem[i]);

	// Память elem будет принадлежать объекту b после выполнения swap и соотв. освободится деструктором при выходе из ф-ции
	swap(*this, b);			// Обмен представлений
}


//------------------------------------------------------------------------------

