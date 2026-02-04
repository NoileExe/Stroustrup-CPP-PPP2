


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

template<typename T>
class ownvector {
public:
	typedef unsigned long size_t;
	
	class iterator;		//Тип - член класса: iterator
	
	ownvector() : elem{nullptr}, owned{nullptr}, sz{0}, space{0}		{  }
	
	ownvector(size_t n) : elem{new T*[n]}, owned{new T*[n]}, sz{0}, space{n}
		{ for(size_t i = 0; i < n; ++i)		elem[i] = owned[i] = nullptr; }
	
	explicit ownvector(initializer_list<T> lst)
	: elem{new T*[lst.size()]},
	  owned{new T*[lst.size()]},
	  sz{0},
	  space{lst.size()}
	  //space{ static_cast<unsigned long>(lst.size()) }
	{
		//cout << "ownvector(initializer_list<T> lst)" << endl;
		for(size_t i=0;   i < lst.size();   ++i) {
			elem[i]  = new T { *(lst.begin()+i) };
			owned[i] = elem[i];
		}
		
		sz = lst.size();
	}
	
	explicit ownvector(initializer_list<T*> lst)
	: elem{new T*[lst.size()]},
	  owned{new T*[lst.size()]},
	  sz{0},
	  space{lst.size()}
	  //space{ static_cast<unsigned long>(lst.size()) }
	{
		//cout << "ownvector(initializer_list<T*> lst)" << endl;
		for(size_t i=0;   i < lst.size();   ++i) {
			elem[i]  = *(lst.begin()+i);
			owned[i] = elem[i];
		}
		
		sz = lst.size();
	}
	
	//Копирующие конструктор и присваивание
	ownvector(const ownvector& v)
	: elem{new T*[v.sz]},
	  owned{new T*[v.sz]},
	  sz{0},
	  space{v.sz}
	{
		for (int i = 0; i < v.sz; ++i) {
			elem[i] = new T { v[i] }; //Копируем значения
			owned[i] = elem[i];
		}
		
		sz = v.sz;
	}
	
	ownvector& operator=(const ownvector& v);	// Копирующее присваивание
	
	
	//Перемещающие конструктор и присваивание
	ownvector(ownvector&& v)
	: elem{v.elem},
	  owned{v.owned},
	  sz{v.sz},
	  space{v.space}
	{
		v.elem = nullptr;
		v.owned = nullptr;
		v.sz = v.space = 0;
	}
	
	ownvector& operator=(ownvector&& v);
	
	~ownvector() {
		if(elem) {
			for(size_t i=0; i < sz; ++i)
				if (owned[i])		delete owned[i];
			delete[] owned;
			delete[] elem;
		}
	}
	
	
	//Доступ к элементам с проверкой выхода за диапазон
	T& at(size_t n) {
		if ( n>=sz )		throw out_of_range("ownvector range error with index [" + to_string(n) + "]");
		return *elem[n];
	}
	
	const T& at(size_t n) const {
		if ( n>=sz )		throw out_of_range("const ownvector range error with index [" + to_string(n) + "]");
		return *elem[n];
	}
	
	//Доступ к элементам без проверки выхода за диапазон
	T& operator[](size_t n) { return *elem[n]; }
	const T& operator[] (size_t n) const { return *elem[n]; }
	
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
	void push_back(T* val, bool owner = false);
	void reserve(size_t newalloc);
	
private:
	T** elem;		// Начало выделенной памяти (указатель на указатель - указатель на массив указателей в памяти, каждый из которых в свою очередь указывает на память со значением)
	T** owned;		// Указатель на на массив указателей в памяти, обозначает элементы принадлежащие данному вектору
	
	size_t sz;		// Количество элементов
	size_t space;	// Размер выделенной памяти (размер+свободные ячейки памяти размером для типа T)
};

//------------------------------------------------------------------------------

template<class T>
class ownvector<T>::iterator {
	T** curr;	//Текущий узел
	
public:
	iterator(T** pp) : curr(pp)	{  }
	
	iterator& operator++()	{ if(curr) ++curr;	return *this; }		//Вперёд
	iterator& operator--()	{ if(curr) --curr;	return *this; }		//Назад
	T& operator*()			{ return **curr; }						//Разыменование (получение указателя)
	T* operator->()			{ return *curr; }						//Получение указателя
	T* operator[](size_t n)	{ return curr[n]; }						//Доступ по индексу
	//T** get_current()		{ return curr; }						//Получение указателя на указатель
	
	friend bool operator==(const iterator& a, const iterator& b)
		{ return a.curr==b.curr; }
	
	friend bool operator!=(const iterator& a, const iterator& b)
		{ return !(a==b); }
};

//------------------------------------------------------------------------------

//Копирующее присваивание
template<typename T>
ownvector<T>& ownvector<T>::operator=(const ownvector<T>& v)
{
	if (this == &v)		return *this;	//Проверка на самоприсваивание
	//cout << "\nCalled ownvector<T>::operator=(const ownvector<T>& v)\n";
	
	if(elem) {
		for(size_t i=0; i < sz; ++i)
			if (owned[i])		delete owned[i];
		delete[] owned;
		delete[] elem;
	}

	elem = new T*[v.space ? v.space : v.sz];
	owned = new T*[v.space ? v.space : v.sz];
	space = v.space ? v.space : v.sz;
	sz = 0;
	
	for (size_t i = 0; i < space; ++i)
	{
		elem[i] = nullptr;
		owned[i] = nullptr;
	} 

	for (size_t i = 0; i < v.sz; ++i)
	{
		elem[i] = new T{ *(v.elem[i]) };
		owned[i] = elem[i];					//При копировании владеем всеми элементами
	}

	sz = v.sz;

	return *this;
}

//------------------------------------------------------------------------------

//Перемещающее присваивание
template<typename T>
ownvector<T>& ownvector<T>::operator=(ownvector<T>&& v)
{
	if (this == &v)		return *this;
	
	if(elem) {
		for(size_t i=0; i < sz; ++i)
			if (owned[i])		delete owned[i];
		delete[] owned;
		delete[] elem;
	}
	
	elem = v.elem;
	owned = v.owned;
	sz = v.sz;
	space = v.space;
	
	v.elem = nullptr;
	v.owned = nullptr;
	v.sz = v.space = 0;
	
	return *this;
}

//------------------------------------------------------------------------------

template<typename T>
void ownvector<T>::resize(size_t newsize, T val)
{
	//Уничтожаем если новый размер меньше кол-ва уже инициализированных объектов вектора
	for(size_t i = newsize; i < sz; ++i)
	{
		delete elem[i];
		elem[i] = nullptr;
		owned[i] = nullptr;
	}

	reserve(newsize);
	
	//Создаём если новый размер больше кол-ва уже инициализированных объектов вектора
	for(size_t i = sz; i < newsize; ++i)
	{
		elem[i] = new T {val};
		owned[i] = elem[i];
	}

	sz = newsize;
}

//Добавление элементов в конец вектора (вектор владеет памятью на создаваемые элементы)
template<typename T>
void ownvector<T>::push_back(const T& val)
{
	if (space == 0)				reserve(8);				//Для начала выделяем память для 8 элементов
	else if (sz == space)		reserve(2 * space);		//Удваиваем размер выделяемой памяти
	
	elem[sz] = owned[sz] = new T {val};			//Добавляем указанное значение в конец вектора
	++sz;										//Кол-во элементов увеличивается на 1
}

//Добавление элементов в конец вектора (вектор владеет памятью на создаваемые элементы ТОЛЬКО ЕСЛИ owner == true)
//owner не обязательно указывать, т.к. он по умолчанию false
template<typename T>
void ownvector<T>::push_back(T* val, bool owner)
{
	if (space == 0)				reserve(8);				//Для начала выделяем память для 8 элементов
	else if (sz == space)		reserve(2 * space);		//Удваиваем размер выделяемой памяти
	
	elem[sz] = val;		//Добавляем указанное значение в конец вектора

	if(owner)		owned[sz] = elem[sz];	//Вектор является владельцем данного элемента
	else			owned[sz] = nullptr;	//Пропуск элемента (не владеет)

	++sz;							//Кол-во элементов увеличивается на 1
}

template<class T>
void ownvector<T>::reserve(size_t newalloc)
{
	if(newalloc <= space)	return;		// Размер никогда не уменьшается
	
	T** new_elem  = new T*[newalloc];
	T** new_owned = new T*[newalloc];

	for (size_t i = 0; i < sz; ++i)
	{
		new_elem[i] = elem[i];
		new_owned[i] = owned[i];
	}

	for (size_t i = sz; i < newalloc; ++i)
	{
		new_elem[i] = nullptr;
		new_owned[i] = nullptr;
	}

	delete[] elem;
	delete[] owned;

	elem = new_elem;
	owned = new_owned;
	space = newalloc;
}

//------------------------------------------------------------------------------

