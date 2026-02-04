


#include <std_lib_facilities.h>



//------------------------------------------------------------------------------

namespace my_list
{
	
	template<class Elem>struct Link {
		Link(const Elem& v = Elem(), Link* p = 0, Link* s = 0) : val(v), prev(p), succ(s)	{  }
		
		Link* prev;		//Предыдущий элемент
		Link* succ;		//Следующий элемент
		Elem  val;		//Значение
	};


	template<typename Elem>
	class list {
	//Детали представления и реализации
	public:
		class iterator;		//Тип - член класса: iterator
		
		list() : first(nullptr), last(nullptr)		{  }
		
		list(initializer_list<Elem> lst) : first(new Link<Elem> { *(lst.begin()) }), last(nullptr)
			{ for (int i = 1; i < lst.size(); ++i)		push_back( *(lst.begin()+i) ); }
		
		//Копирующие конструктор и присваивание
		list(const list& l) = delete;
		list& operator=(const list& l) = delete;
		
		//Перемещающие конструктор и присваивание
		list(list&& l) = delete;
		list& operator=(list&& l) = delete;
		
		//Деструктор
		~list()
		{
			while(&first)
			{
				auto tmp = first;
				first = first->succ;
				delete &tmp;
			}
			
			cout << "\n\n\nDestructor completed\n\n";
		}
		
		iterator begin()	{ return first; }				//Итератор, указывающий на первый элемент
		const iterator begin() const	{ return first; }	//Итератор, указывающий на первый элемент
		iterator  end()		{ return last; }				//Итератор, указывающий на элемент, следующий за последним
		const iterator end() const	{ return last; }		//Итератор, указывающий на элемент, следующий за последним
		
		//Вставить v в список после элемента, на который указывает итератор p
		iterator insert(iterator p, const Elem& v);
		
		//Удаление из списка элемента, на который указывает итератор p
		//Возвращает итератор элемента следующего за текущим (или последнего в списке)
		iterator erase(iterator p);
		
		void push_front(const Elem& v);		//Вставка v в начало списка
		void push_back(const Elem& v);		//Вставка v в конец списка
		void pop_front();					//Удаление первого элемента
		void pop_back();					//Удаление последнего элемента
		Elem& front()						//Первый элемент
		{
			if(first != last)		return first->val;
			else					error("empty list [front()]");
		}
		
		const Elem& front() const						//Первый элемент
		{
			if(first != last)		return first->val;
			else					error("empty list [front()]");
		}
		
		Elem& back()						//Последний элемент
		{
			if(first != last) {
				auto last_elem = first;
				while(last_elem->succ)		++last_elem; //Находим последний элемент списка
				return last_elem->val;
			}
			else					error("empty list [back()]");
		}
		
		const Elem& back() const					//Последний элемент
		{
			if(first != last) {
				auto last_elem = first;
				while(last_elem->succ)		++last_elem; //Находим последний элемент списка
				return last_elem->val;
			}
			else					error("empty list [back()]");
		}
		
		iterator first;
		iterator last;	//Узел находящийся за последним
	};


	template<class Elem>
	class list<Elem>::iterator {
		Link<Elem>* curr;   //Текущий узел
		
	public:
		iterator(Link<Elem>* p) : curr(p)	{  }
		
		Link<Elem>* operator&()					{ return curr; }	//Получение ссылки на объект
		const Link<Elem>* operator&() const		{ return curr; }	//Получение ссылки на объект
		Link<Elem>* operator->()				{ return curr; }	//Получение указателя
		const Link<Elem>* operator->() const	{ return curr; }	//Получение указателя
		
		iterator& operator++()										//Вперёд
		{
			if(!curr)						error("attempt to get an increment for a null pointer [class list<Elem>::iterator operator++()]");
			//else if ( !(curr->succ) )		error("end of sequence already reached [class list<Elem>::iterator operator++()]");
			else							curr = curr->succ;
			
			return *this;
		}
		
		const iterator& operator++() const							//Вперёд
		{
			if(!curr)						error("attempt to get an increment for a null pointer [class list<Elem>::iterator operator++()]");
			//else if ( !(curr->succ) )		error("end of sequence already reached [class list<Elem>::iterator operator++()]");
			else							curr = curr->succ;
			
			return *this;
		}
		
		iterator& operator--()										//Назад
		{
			if(!curr)						error("attempt to get an decrement for a null pointer [class list<Elem>::iterator operator--()]");
			else if ( !(curr->prev) )		error("first element of sequence already reached [class list<Elem>::iterator operator++()]");
			else							curr = curr->prev;
			
			return *this;
		}
		
		const iterator& operator--() const							//Назад
		{
			if(!curr)						error("attempt to get an decrement for a null pointer [class list<Elem>::iterator operator--()]");
			else if ( !(curr->prev) )		error("first element of sequence already reached [class list<Elem>::iterator operator++()]");
			else							curr = curr->prev;
			
			return *this;
		}
		
		Elem& operator*()				{ return curr->val; }		//Разыменование (получение значения)
		const Elem& operator*() const	{ return curr->val; }		//Разыменование (получение значения)
		
		friend bool operator==(const iterator& a, const iterator& b)
			{ return a.curr==b.curr; }
		
		friend bool operator!=(const iterator& a, const iterator& b)
			{ return !(a==b); }
	};


	//--------------------------------------------------------------------------


	//Вставка v в начало списка
	template<class Elem>
	void list<Elem>::push_front(const Elem& v)
	{
		iterator new_elem { new Link<Elem>(v, nullptr, &first) };
		if(first != last)		first->prev = &new_elem;
		first = new_elem;
	}


	//Вставка v в конец списка
	template<class Elem>
	void list<Elem>::push_back(const Elem& v)
	{
		if(first == last)		push_front(v);
		else {
			auto last_elem = first;
			while(last_elem->succ)		++last_elem; //Находим последний элемент списка
			Link<Elem>* new_elem = new Link<Elem>(v, &last_elem, &last);
			last_elem->succ = new_elem;
		}
	}


	//Удаление первого элемента
	template<class Elem>
	void list<Elem>::pop_front()
	{
		if(first != last) {
			if(first->succ == &last)		//В списке лишь 1 элемент
				{ delete &first;		first = last; }
			
			else {
				iterator tmp { first->succ };	//Запоминаем ссылку на 2ой по счёту элемент списка
				delete &first;
				tmp->prev = nullptr;
				first = tmp;
			}
		}
	}


	//Удаление последнего элемента
	template<class Elem>
	void list<Elem>::pop_back()
	{
		if(first != last) {
			if(first->succ == &last)		pop_front();	//В списке лишь 1 элемент
			
			else {
				auto last_elem = first;
				while(last_elem->succ)		++last_elem; //Находим последний элемент списка
				
				Link<Elem>* tmp = last_elem->prev;		//Запоминаем предпоследний
				delete &last_elem;
				tmp->succ = &last;	//last = nullptr
			}
		}
	}


	//--------------------------------------------------------------------------


	//Вставить v в список после элемента, на который указывает итератор p
	//Возвращает итератор вновь добавленного элемента
	template<class Elem>
	typename list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v)
	{
		if( !(&p) )		error("nullptr iterator [list insert()]");
		
		Link<Elem>* new_elem = new Link<Elem>{v, &p, p->succ};
		if(p->succ)		p->succ = new_elem;
		return iterator(new_elem);
	}

	//Удаление из списка элемента, на который указывает итератор p
	//Возвращает итератор элемента следующего за текущим (или последнего в списке если удаляется узел следующий за последним (last))
	template<class Elem>
	typename list<Elem>::iterator list<Elem>::erase(iterator p)
	{
		if( !(&p) )			error("nullptr iterator [list erase()]");
		if( p == first )			{ pop_front();		return first; }
		
		p->succ->prev = p->prev;
		p->prev->succ = p->succ;
		Link<Elem>* tmp = p->succ;
		delete &p;
		return tmp;
	}

}