

#include "link.h"

//------------------------------------------------------------------------------

//Вставляет n перед данным объектом; возвращает сылку на начало списка (т.к. может быть изменена)
Link* Link::insert(Link* n)
{
	if (n==0)		return this;
	if (this==0)	return n;
	
	if (first == this)		{ first = n;	n->succ = this; }
	
	Link* p = first;
	while(p  &&  p->succ != this)		p = p->succ;
	p->succ = n;
	n->succ = this;
	
	p = first;
	while (p) {
		p->first = first;
		p->last = last;
		p = p->succ;
	}
	
	
	return first;
}

//Вставляет n после данного объекта, все остальные "смещает вперёд" по списку; возвращает сылку на начало списка
Link* Link::add(Link* n)
{
	if (n==0)		return this;
	if (this==0)	return n;
	
	if (last == this)	{ last = n;		n->succ = nullptr; }
	else				n->succ = succ;
	
	succ = n;
	
	Link* p = first;
	while (p) {
		p->first = first;
		p->last = last;
		p = p->succ;
	}
	
	return first;
}

//Удаляет указанный объект из списка (ищет начиная с текущего); возвращает сылку на начало списка (т.к. может быть изменена)
Link* Link::erase()
{
	if (this==0)	return 0;
	
	Link* p = first;
	while(p != this)		p = p->succ;
	
	Link* prev = first;
	while(prev  &&  prev->succ != this)		prev = prev->succ;
	
	if (first==this)		first = succ;
	else if (last==this)	{ last = prev;		prev->succ = 0;}
	else					prev->succ = succ;
	
	p = first;
	while (p) {
		p->first = first;
		p->last = last;
		p = p->succ;
	}
	
	succ = nullptr;
	
	return first;
}

//Начиная с первого элемента в списке и продвигаясь вперёд (к следующему элементу) поиск элемента со значением value == s
//Возвращает нуль если не найдено
Link* Link::find(const string& s)
{
	//cout << "nonconst find" << '\n';
	
	Link* p = first;
	while(p) {
		if ( p->value == s )		return p;
		p = p->succ;
	}
	return 0;
}

const Link* Link::find(const string& s) const
{
	//cout << "const find" << '\n';
	
	if (value == s)		return this;
	else if (succ)		return succ->find(s);
	
	return 0;
}

//Возвращает ссылку на элемент через n позиций по списку начиная с текущего
//Возвращает нуль если текущий указатель имеет значение nullptr или если закончились элементы
Link* Link::advance(int n) const
{
	if (this==0)	return 0;
	
	if (n>0) {
		int after_num {0};		//Элементов после текущего объекта
		const Link* p = this;
		//После цикла p становится ссылкой на последний элемент
		while (p  &&  p->succ != 0)			{ ++after_num;		p = p->succ; }
		if (n > after_num  ||  succ==0)		return 0;
		
		return  succ->advance(--n);
	}
	
	if (n<0) {
		int before_num {0};		//Элементов до текущего объекта
		const Link* p = first;
		//После цикла p становится ссылкой на текущий элемент списка
		while (p  &&  p != this)	{ ++before_num;		p = p->succ; }
		if (n < -before_num)		return 0;
		
		const Link* prev = first;
		while (prev  &&  prev->succ != this)	prev = prev->succ;
		
		if (prev)		return  prev->advance(++n);
		//Иначе возвращается текущий элемент
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
void print_all(Link l)
{
	cout << "{ ";
	
	Link* p = l.begin();
	while (p) {
		cout << p->value;
		if ( p = p->next() )		cout <<  ", ";
	}
	
	cout << " }";
}