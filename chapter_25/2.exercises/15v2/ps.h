
//#pragma once		//для подключения даного заголовочного файла строго один раз

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream> и устанавливает using namespace std
#include<vector>


using namespace std;

//------------------------------------------------------------------------------

/*struct Obj_500
{
	char* data;
	
	Obj_500() : data{ new char[500] }		{  }
	~Obj_500() { if(data)		delete[] data; }
	
	//Копирующие конструктор и присваивание
	Obj_500(const Obj_500&) = delete;
	Obj_500& operator=(const Obj_500&)
	{
		if(data)		delete[] data;
		data = new char[500];
		return *this;
	}
	
	//Перемещающие конструктор и присваивание
	Obj_500(Obj_500&& obj) : data{obj.data}		{ obj.data = 0; }
	Obj_500& operator=(Obj_500&& obj)
	{
		if(data)		delete[] data;
		data = obj.data;
		obj.data = 0;
		return *this;
	}
};*/

struct Obj_500 { char data[500]; };

//------------------------------------------------------------------------------

template<class T, unsigned long N>
class Pool {
public:
	typedef unsigned long size_t;
	
	// Выделяет память для N элементов типа T
	Pool() : objects{ new T[N] }, is_used{}, unused{N}		{ for(int i=0; i < N; ++i)		is_used.push_back(false); }
	
	~Pool()		{ if(objects)		delete[] objects; }


	// получает ссылку на элемент типа T из пула; возвращает 0 если не осталось больше свободных ячеек памяти
	T* get()
	{
		for(int i=0; i < N; ++i)
			if(is_used[i] == false)
			{
				is_used[i] = true;
				--unused;
				return &(objects[i]);
			}
		
		return 0;
	}

	// освобождает память занятую объектом T, который был получен ф-цией get()
	void free(T* obj)
	{
		if(unused == N)				error("an attempt to free memory in an empty pool [ Pool::free() ]");
		
		// проверка что объект принадлежит пулу
		for(int i=0; i < N; ++i)
		{
			if(&(objects[i]) == obj)
				if(!is_used[i])		error("attempt to free an empty memory cell [ Pool::free() ]");
				else				{ is_used[i] = false;	break; }
			else if(i+1 == N)		error("attempt to free a memory cell that doesn't belong to the pool [ Pool::free() ]");
		}
		
		*obj = T(); // объект откатывается к значению по умолчанию (как при инициализации встроенного массива)
		++unused;
	}


	size_t already_used() const		{ return (N - unused); }	// Число уже занятых ячеек
	size_t available() const		{ return    unused;    }	// Число оставшихся свободных ячеек

private:
	T* objects;
	vector<bool> is_used;
	size_t unused;		// Число оставшихся свободных ячеек
};

//------------------------------------------------------------------------------

template<unsigned long N>
class Stack {
public:
	Stack() : data{ new char[N] }, top{ data }, edges{}		{  }
	
	~Stack() { delete[] data; }


	// размемщение n байт в стеке; возвращает нулевой указатель если места окажется недостаточно
	void* get(int n)
	{
		if (n > available())		return 0;
		
		edges.push_back(top);
		top += n;
		
		return edges.back();
	}

	// освобождает память занятую последним значением внесенным ф-цией get()
	void free()
	{
		if(top == data  ||  edges.size() == 0)		error("attempt to free a memory cell in empty stack [ Stack::free() ]");
		
		top = edges.back();
		edges.pop_back();
	}


	// число уже занятых байт
	unsigned long already_used() const	{ return (top - data) /* / sizeof(char)*/; }
	/*unsigned long already_used() const
	{
		unsigned long summ {0};
		
		for(auto s : sz)
			if(s == 0)		break;
			else			summ += s;
		
		return summ;
	}*/

	// количество свободной памяти в байтах
	unsigned long available() const		{ return N - already_used(); }

private:
	char* data;				// место для char[N] (размер char == 1 байт) и данные для того чтобы определить какие объекты извлечены из стека, а какие нет
	char* top;				// верхушка стека (первая свободная)
	vector<char*> edges;	// начало каждого размещенного объекта
};