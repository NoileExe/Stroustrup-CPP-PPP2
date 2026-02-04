

#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

class Link {
public:
	string value;
	
	Link(const string& v, Link* b = nullptr, Link* e = nullptr, Link* s = nullptr)
		:value{v}, first{b}, last{e}, succ{s}
	{
		if (first == nullptr)		first = this;
		if (last == nullptr)		{ last = this;		succ = nullptr; }
	}
	
	Link* insert(Link* n);		//Вставляет n перед данным объектом
	Link* add(Link* n);			//Вставляет n после данного объекта
	Link* erase();				//Удаляет указанный объект из списка (ищет начиная с first)
	Link* find(const string& s);				//Поиск в списке
	const Link* find(const string& s) const;	//Поиск в константном списке
	Link* advance(int n) const;					//Элемент через n позиций по списку начиная с текущего
	Link* move(int n);							//Перемещение на n позиций по списку
	
	Link* next() const { return succ; }
	Link* begin() const { return first; }
	Link* end()   const { return last; }
	
private:
	Link* first;	//Первый элемент списка
	Link* last;		//Последний элемент списка
	Link* succ;		//Элемент списка следующий за текущим
};

//------------------------------------------------------------------------------

//Вывод всех значений value из объектов Link начиная с текущего и продвигаясь по next() до встречи nullptr
void print_all(Link l);