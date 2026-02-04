

#include "link.h"

//------------------------------------------------------------------------------

bool operator<(const God& a, const God& b)
{ return a.name < b.name; }

bool operator>(const God& a, const God& b)
{ return a.name > b.name; }

bool operator==(const God& a, const God& b)
{
	return      a.name == b.name
		&& a.mythology == b.mythology
		&& a.transport == b.transport
		   && a.weapon == b.weapon;
}

bool operator!=(const God& a, const God& b)
{ return  !( a == b ); }

ostream& operator<<(ostream& ost, const God& g)
{
	ost << "{ " << g.name << ", " << g.mythology << ", " << g.transport << ", " << g.weapon << " }";
	return ost;
}

//------------------------------------------------------------------------------

//Вставляет n перед данным объектом; возвращает n
Link* Link::insert(Link* n)
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
Link* Link::add(Link* n)
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
Link* Link::add_ordered(Link* n) {
	if (n==0)		return this;
	if (this==0)	return n;
	
	Link* p = this;
	
	//Размещаем n перед текущим объектом и затем смещаем n по 1 позиции вперёд в списке пока следующее value.name не будет >= n->value.name
	p->insert(n);
	while (p  &&  p->value < n->value)	{ p = p->succ;		n->move(1); }
	
	return n;
}

//Удаляет текущий объект из списка; возвращает ссылку на объект следующий за текущим
Link* Link::erase()
{
	if (this==0) return 0;
	if (succ) succ->prev = prev;	//У следующего предыдущий равен предыдущему текущего
	if (prev) prev->succ = succ;
	return succ;
}

//Начиная с текущего элемента продвигаясь вперёд (к следующему элементу) поиск элемента со значением value == s
//Возвращает нуль если не найдено
Link* Link::find(const string& s)
{
	cout << "nonconst find" << '\n';
	
	Link* p = this;
	while(p) {
		if ( p->value.name == s )		return p;
		p = p->succ;
	}
	return 0;
}

const Link* Link::find(const string& s) const
{
	cout << "const find" << '\n';
	
	if (value.name == s)		return this;
	else if (succ)		return succ->find(s);
	
	return 0;
}

//Возвращает ссылку на элемент через n позиций по списку начиная с текущего
//Возвращает нуль если текущий указатель имеет значение nullptr или если закончились элементы
Link* Link::advance(int n) const
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
	
	 return const_cast<Link*>(this);	//Проще сделать ф-цию неконстантной т.к. она работает рекурсивно
}

//Перемещение текущего объекта на n позиций по списку
//Положительное значение n - смещение вперёд по списку
//Отрицательное - назад
//Возвращает новую ссылку на текущий объект
//Возвращает нуль если текущий указатель имеет значение nullptr или если закончились элементы и далее смещать некуда
Link* Link::move(int n)
{
	if (this==0)	return 0;
	
	Link* p = advance(n);
	if (!p)		return 0;
	
	erase();
	if (n>0)	p->add(this);
	if (n<0)	p->insert(this);
	
	return this;
}

//------------------------------------------------------------------------------

//Вывод всех значений value из объектов Link начиная с текущего и продвигаясь по next() до встречи nullptr
void print_all(const Link* p)
{
	while (p) {
		cout << p->value;
		if ( p = p->next() )		cout <<  ",\n";
	}
}