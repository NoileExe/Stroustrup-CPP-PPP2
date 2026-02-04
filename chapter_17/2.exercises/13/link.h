

#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

struct God {
	string name;
	string mythology;
	string transport;
	string weapon;
};

bool operator<(const God& a, const God& b);
bool operator>(const God& a, const God& b);
bool operator==(const God& a, const God& b);
bool operator!=(const God& a, const God& b);

ostream& operator<<(ostream& ost, const God& g);

//------------------------------------------------------------------------------

class Link {
public:
	God value;
	Link(const God& v, Link* p = nullptr, Link* s = nullptr)
		:value{v}, prev{p}, succ{s}   {  }
	
	Link* insert(Link* n);			//Вставляет n перед данным объектом
	Link* add(Link* n);				//Вставляет n после данного объекта
	Link* add_ordered(Link* n);		//Вставляет n в лексикографической (по алфавиту) последовательности относительно других элементов списка
	Link* erase();					//Удаляет данный объект из списка
	Link* find(const string& s);				//Поиск в списке
	const Link* find(const string& s) const;	//Поиск в константном списке
	Link* advance(int n) const;					//Элемент через n позиций по списку начиная с текущего
	Link* move(int n);							//Перемещение на n позиций по списку
	
	Link* next() const { return succ; }
	Link* previous() const { return prev; }
	
private:
	Link* prev;
	Link* succ;
};

//------------------------------------------------------------------------------

//Вывод всех значений value из объектов Link начиная с текущего и продвигаясь по next() до встречи nullptr
void print_all(const Link* p);