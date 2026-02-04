
//Найдено другое решение на git'е, при котором 8 символов - не предел
//Видимо в зависимости от того в какую область памяти попадёт программа
// работа может завершится на разных этапах без ошибок и предупреждений
//Так же может попасть в область самой выполняемой программы и испортить её саму (см. скриншоты)


#include <yes_or_no.h>
#include <std_lib_facilities.h>



const string quit_question = "Close program?";

//------------------------------------------------------------------------------

class Link {
public:
	string value;
	Link(const string& v, Link* p = nullptr, Link* s = nullptr)
		:value{v}, prev{p}, succ{s}   {  }
	
	Link* insert(Link* n);		//Вставляет n перед данным объектом
	Link* add(Link* n);			//Вставляет n после данного объекта
	Link* erase();				//Удаляет данный объект из списка
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
		if ( p->value == s )		return p;
		p = p->succ;
	}
	return 0;
}

const Link* Link::find(const string& s) const
{
	cout << "const find" << '\n';
	
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

void print_all(Link* p)
{
	cout << "{ ";
	while (p) {
		cout << p->value;
		if ( p = p->next() )		cout <<  ", ";
	}
	cout << " }";
}


int main()
{
	while (true) {
		try
		{
			Link* norse_gods = new Link("Thor");
			norse_gods = norse_gods->insert(new Link("Odin"));
			norse_gods = norse_gods->insert(new Link("Zeus"));
			norse_gods = norse_gods->insert(new Link("Freia"));
			
			Link* greek_gods = new Link("Hera");
			greek_gods = greek_gods->insert(new Link("Athena")); 
			greek_gods = greek_gods->insert(new Link("Mars"));
			greek_gods = greek_gods->insert(new Link("Poseidon"));
			
			Link* p = greek_gods->find("Mars");
			if (p) p->value = "Ares";
			
			// Move Zeus into his correct Pantheon: 
			{
				Link* p = norse_gods->find("Zeus");
				if (p) {
					if (p==norse_gods)		norse_gods = p->next();
					p->erase();
					greek_gods = greek_gods->insert(p);
				}
			}
			
			// Finally, let's print out those lists:
			
			print_all(norse_gods);
			cout<<"\n";
			
			print_all(greek_gods);
			cout<<"\n";
			
			press_Enter_key(true);
			
			
			
			{
				Link* p = greek_gods->find("Zeus");
				Link* bckp = greek_gods;
				if (p==greek_gods)		greek_gods = p->next();
				//Элемент списка найден, но смещение невозможно
				if ( p  &&  !(p->move(4)) )		greek_gods = bckp;
			}
			print_all(greek_gods);
			cout<<"\n";
			
			press_Enter_key(true);
			
			
			
			{
				Link* p = greek_gods->find("Zeus");
				if (p)		p->move(-2);
				if ( p->next() == greek_gods )		greek_gods = p;
			}
			print_all(greek_gods);
			cout<<"\n";
			
			keep_window_open("~~");
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}