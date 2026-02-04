

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream> и устанавливает using namespace std


using namespace std;

//------------------------------------------------------------------------------

template<class T, unsigned long N = 1000>
class vctrPool {
public:
	//using size_t = unsigned long;
	typedef unsigned long size_t;
	
	// Выделяет память для N элементов типа T
	vctrPool() :objects(), is_used(), unused(N)		{  }

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
		if(unused == N)				error("an attempt to free memory in an empty pool [ vctrPool::free() ]");
		
		// проверка что объект принадлежит пулу
		for(size_t i=0; i < N; ++i)
			if(&objects[i] == obj)
				if(!is_used[i])		error("attempt to free an empty memory cell [ vctrPool::free() ]");
				else				break;
			else if(i+1 == N)		error("attempt to free a memory cell that doesn't belong to the pool [ vctrPool::free() ]");
		
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
class vctr {
public:
	typedef unsigned long size_t;
	
	vctr() : ptr_to_dat{}, sz{0}, alloc{}		{  }
	
	vctr(int n) : ptr_to_dat{}, sz{n}, alloc{}
	{
		if(n > N)		error("the number of vctr elements cannot exceed the number of allocated memory cells [ vctr() initialisation with size ]");
		for (size_t i=0; i < sz; ++i)		ptr_to_dat[i] = alloc.get();
	}
	
	void push_back(T value)
	{
		//if(!alloc.available())		error("vector is full [ vctr::push_back() ]");
		if(sz == N)		error("vector is full [ vctr::push_back() ]");
		
		ptr_to_dat[sz] = alloc.get();
		*ptr_to_dat[sz] = value;
		++sz;
	}
	
	void pop_back()
	{
		if (!sz)		error("vector is empty [ vctr::pop_back() ]");
		alloc.free( &(*ptr_to_dat[--sz]) );
	}
	
	size_t size() const { return sz; }
	
	T& operator[](size_t n)
	{
		cout << "'" << n << "'";
		if(n >= sz)		error("out of the range [ vctr::operator[] ]");
		return *ptr_to_dat[n];
	}
	
	const T& operator[](size_t n) const
	{
		if(n >= sz)		error("out of the range [ vctr::operator[] ]");
		return *ptr_to_dat[n];
	}

private:
	T* ptr_to_dat[N];		//Массив указателей на данные
	size_t sz;
	vctrPool<T, N> alloc;
};