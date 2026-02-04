
#pragma once		//для подключения даного заголовочного файла строго один раз


//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream> и устанавливает using namespace std


using namespace std;

//------------------------------------------------------------------------------

template<class T, unsigned long N = 1000>
class Pool {
public:
	//using size_t = unsigned long;
	typedef unsigned long size_t;
	
	// Выделяет память для N элементов типа T
	Pool() : objects(), is_used(), unused(N)		{  }


	// получает ссылку на элемент типа T из пула; возвращает 0 если не осталось больше свободных ячеек памяти
	T* get()
	{
		for(size_t i=0; i < N; ++i)
			if(!is_used[i])
			{
				is_used[i] = true;
				--unused;
				return &objects[i];
			}
		
		return 0;
	}

	// освобождает память занятую объектом T, который был получен ф-цией get()
	void free(T* obj)
	{
		if(unused == N)				error("an attempt to free memory in an empty pool [ Pool::free() ]");
		
		// проверка что объект принадлежит пулу
		for(size_t i=0; i < N; ++i)
			if(&objects[i] == obj)
				if(!is_used[i])		error("attempt to free an empty memory cell [ Pool::free() ]");
				else				break;
			else if(i+1 == N)		error("attempt to free a memory cell that doesn't belong to the pool [ Pool::free() ]");
		
		*obj = T(); // объект откатываетсяя к значению по умолчанию (как при инициализации встроенного массива)
		++unused;
		is_used[obj-objects] = false;
	}


	size_t already_used() const		{ return (N - unused); }	// Число уже занятых ячеек
	size_t available() const		{ return    unused; }		// Число оставшихся свободных ячеек

private:
	T objects[N];
	bool is_used[N];
	size_t unused;		// Число оставшихся свободных ячеек
};

template<typename T, unsigned long N = 1000>
class pvctr {
public:
	typedef unsigned long size_t;
	
	pvctr() : ptr_to_dat{}, sz{0}, alloc{}		{  }
	
	pvctr(int n) : ptr_to_dat{}, sz{n}, alloc{}
	{
		if(n > N)		error("the number of pvctr elements cannot exceed the number of allocated memory cells [ pvctr() initialisation with size ]");
		for (size_t i=0; i < sz; ++i)		ptr_to_dat[i] = alloc.get();
	}
	
	void push_back(T value)
	{
		//if(!alloc.available())		error("vector is full [ pvctr::push_back() ]");
		if(sz == N)		error("vector is full [ pvctr::push_back() ]");
		
		ptr_to_dat[sz] = alloc.get();
		*ptr_to_dat[sz] = value;
		++sz;
	}
	
	void pop_back()
	{
		if (!sz)		error("vector is empty [ pvctr::pop_back() ]");
		alloc.free( &(*ptr_to_dat[--sz]) );
	}
	
	size_t size() const { return sz; }
	
	T& operator[](size_t n)
	{
		cout << "'" << n << "'";
		if(n >= sz)		error("out of the range [ pvctr::operator[] ]");
		return *ptr_to_dat[n];
	}
	
	const T& operator[](size_t n) const
	{
		if(n >= sz)		error("out of the range [ pvctr::operator[] ]");
		return *ptr_to_dat[n];
	}

private:
	T* ptr_to_dat[N];		//Массив указателей на данные
	size_t sz;
	Pool<T, N> alloc;
};

//------------------------------------------------------------------------------

template<unsigned long N = 4096>
class Stack {
public:
	Stack() : data{}, top{0}, sz{}		{  }


	// размемщение n байт в стеке; возвращает нулевой указатель если места окажется недостаточно
	void* get(int n)
	{
		if (n > available())		return 0;
		
		void* ptr = top;
		top += n;
		
		for(int i=0; i < N; ++i)
			if(sz[i] == 0)		{ sz[i] = n;	break; }
		
		return ptr;
	}

	// освобождает память занятую последним значением внесенным ф-цией get()
	void free()
	{
		if(sz[0] == 0)		error("attempt to free a memory cell in empty stack [ Stack::free() ]");
		
		for(int i=0; i < N; ++i)
			if(sz[i] == 0)
			{
				top -= sz[i-1];
				sz[i-1] = 0;
				break;
			}
	}


	// число уже занятых байт
	unsigned long already_used() const
	{
		unsigned long summ {0};
		
		for(auto s : sz)
			if(s == 0)		break;
			else			summ += s;
		
		return summ;
	}

	// количество свободной памяти в байтах
	unsigned long available() const		{ return N - already_used(); }

private:
	// место для char[N] (размер char == 1 байт) и данные для того чтобы определить какие объекты извлечены из стека, а какие нет
	char data[N];
	char* top;				// верхушка стека (первая свободная)
	unsigned long sz[N];	// размеры размещённых объектов
};

/*template<typename T, unsigned long N = 1000>
class svctr {
public:
	typedef unsigned long size_t;
	
	svctr() : ptr_to_dat{}, sz{0}, alloc{}		{  }
	
	svctr(int n) : ptr_to_dat{}, sz{n}, alloc{}
	{
		if(n > N)		error("the number of svctr elements cannot exceed the number of allocated memory cells [ svctr() initialisation with size ]");
		for (size_t i=0; i < sz; ++i)		ptr_to_dat[i] = alloc.get( sizeof(T) );
	}
	
	void push_back(T value)
	{
		//if(!alloc.available())		error("vector is full [ svctr::push_back() ]");
		if(sz == N)		error("vector is full [ svctr::push_back() ]");
		
		ptr_to_dat[sz] = alloc.get( sizeof(T) );
		*ptr_to_dat[sz] = value;
		++sz;
	}
	
	void pop_back()
	{
		if(!sz)		error("vector is empty [ svctr::pop_back() ]");
		alloc.free();
	}
	
	size_t size() const { return sz; }
	
	T& operator[](size_t n)
	{
		cout << "'" << n << "'";
		if(n >= sz)		error("out of the range [ svctr::operator[] ]");
		return *ptr_to_dat[n];
	}
	
	const T& operator[](size_t n) const
	{
		if(n >= sz)		error("out of the range [ svctr::operator[] ]");
		return *ptr_to_dat[n];
	}

private:
	T* ptr_to_dat[N];		//Массив указателей на данные
	size_t sz;
	Stack<N*sizeof(T)> alloc;
};*/