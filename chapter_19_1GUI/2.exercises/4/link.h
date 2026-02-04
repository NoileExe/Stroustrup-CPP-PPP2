

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

template< typename T > class Link {
public:
	Link<T> (const T& v, Link* p = nullptr, Link* s = nullptr)
		:val{v}, prev{p}, succ{s}   {  }
	
	/*
	~Link<T>()
	{
		if(this == nullptr)		error("'Link' object desriptor for nullptr");
		Link<T>* first {this};
		while(first->prev)		first = first->prev;
		
		while(first) {
			Link<T>* d = first;
			first = first->succ
			delete d;
		}
	}
	*/
	
	//Копирующие конструктор и присваивание запрещены
	Link<T> (const Link<T>& l) = delete;
	Link<T>& operator=(const Link<T>& v) = delete;
	
	//Перемещающие конструктор и присваивание запрещены
	Link<T> (Link<T>&& v) = delete;
	Link<T>& operator=(Link<T>&& v) = delete;
	
	
	Link<T>* insert(Link<T>* n);			//Вставляет n перед данным объектом
	Link<T>* add(Link<T>* n);				//Вставляет n после данного объекта
	Link<T>* add_ordered(Link<T>* n);		//Вставляет n в лексикографической (по алфавиту) последовательности относительно других элементов списка
	Link<T>* erase();						//Удаляет данный объект из списка
	Link<T>* find(const string& s);				//Поиск в списке
	const Link<T>* find(const string& s) const;	//Поиск в константном списке
	Link<T>* advance(int n) const;					//Элемент через n позиций по списку начиная с текущего
	Link<T>* move(int n);							//Перемещение на n позиций по списку
	
	T& value() { return val; }
	const T& value() const { return val; }
	Link<T>* next() const { return succ; }
	Link<T>* previous() const { return prev; }
	
private:
	T val;
	
	Link<T>* prev;
	Link<T>* succ;
};

//------------------------------------------------------------------------------

//Вставляет n перед данным объектом; возвращает n
template< typename T >
Link<T>* Link<T>::insert(Link<T>* n)
{
	if (n==0)		return this;
	if (this==0)	return n;
	
	n->succ = this;		//данный объект идёт после n
	
	if (prev)		prev->succ = n;	//после объекта ранее считавшимся предыдущим для данного, теперь находится n
	
	n->prev = prev;		//объект ранее находившийся перед данным, становится объектом предшествующим n
	prev = n;			//n идёт перед данным объектом
	return n;
}

//Вставляет n после данного объекта; возвращает n
template< typename T >
Link<T>* Link<T>::add(Link<T>* n)
{
	if (n==0)		return this;
	if (this==0)	return n;
	
	n->prev = this;		//данный объект идёт перед n
	
	if (succ)		succ->prev = n; //перед объектом ранее считавшимся следующим для данного, теперь находится n
	
	n->succ = succ;		//объект ранее находившийся после данного, становится объектом следующим после n
	succ = n;			//n идёт после данного объекта
	return n;
}

//Вставляет n в лексикографической (по алфавиту) последовательности относительно других элементов списка;
// возвращает n
template< typename T >
Link<T>* Link<T>::add_ordered(Link<T>* n) {
	if (n==0)		return this;
	if (this==0)	return n;
	
	Link<T>* p = this;
	
	//Размещаем n перед текущим объектом и затем смещаем n по 1 позиции вперёд в списке пока следующее val.name не будет >= n->val.name
	p->insert(n);
	while (p  &&  p->val < n->val)	{ p = p->succ;		n->move(1); }
	
	return n;
}

//Удаляет текущий объект из списка; возвращает ссылку на объект следующий за текущим
template< typename T >
Link<T>* Link<T>::erase()
{
	if (this==0) return 0;
	if (succ) succ->prev = prev;	//У следующего предыдущий равен предыдущему текущего
	if (prev) prev->succ = succ;
	return succ;
}

//Начиная с текущего элемента продвигаясь вперёд (к следующему элементу) поиск элемента со значением val == s
//Возвращает нуль если не найдено
template< typename T >
Link<T>* Link<T>::find(const string& s)
{
	cout << "nonconst find" << '\n';
	
	Link<T>* p = this;
	while(p) {
		if ( p->val.name == s )		return p;
		p = p->succ;
	}
	return 0;
}

template< typename T >
const Link<T>* Link<T>::find(const string& s) const
{
	cout << "const find" << '\n';
	
	if (val.name == s)		return this;
	else if (succ)			return succ->find(s);
	
	return 0;
}

//Возвращает ссылку на элемент через n позиций по списку начиная с текущего
//Возвращает нуль если текущий указатель имеет значение nullptr или если закончились элементы
template< typename T >
Link<T>* Link<T>::advance(int n) const
{
	if (this==0)	return 0;
	
	if (n>0) {
		if (succ == 0)		return 0;
		return  succ->advance(--n);
	}
	
	if (n<0) {
		if (prev == 0)		return 0;
		return  prev->advance(++n);
	}
	
	 return const_cast< Link<T>* >(this);	//Проще сделать ф-цию неконстантной т.к. она работает рекурсивно
}

//Перемещение текущего объекта на n позиций по списку
//Положительное значение n - смещение вперёд по списку
//Отрицательное - назад
//Возвращает новую ссылку на текущий объект
//Возвращает нуль если текущий указатель имеет значение nullptr или если закончились элементы и далее смещать некуда
template< typename T >
Link<T>* Link<T>::move(int n)
{
	if (this==0)	return 0;
	
	Link<T>* p = advance(n);
	if (!p)		return 0;
	
	erase();
	if (n>0)	p->add(this);
	if (n<0)	p->insert(this);
	
	return this;
}

//------------------------------------------------------------------------------

//Вывод всех значений val из объектов Link начиная с текущего и продвигаясь по next() до встречи nullptr
template< typename T >
void print_all(const Link<T>* p)
{
	while (p) {
		cout << p->value();
		if ( p = p->next() )		cout <<  ",\n";
	}
}