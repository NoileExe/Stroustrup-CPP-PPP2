


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------



namespace my_list
{
	
	template<class Elem>
	struct Link {
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
		
		list() : first(new Link<Elem>{}), last(first)	{  }
		
		list(initializer_list<Elem> lst)
		: first(new Link<Elem> { *(lst.begin()) }),
		  last (new Link<Elem> {Elem(), first, 0})
		{
			first->succ = last;
			for (int i = 1; i < lst.size(); ++i)		push_back( *(lst.begin()+i) );
		}
		
		//Копирующие конструктор и присваивание
		list(const list& l) = delete;
		list& operator=(const list& l) = delete;
		
		//Перемещающие конструктор и присваивание
		list(list&& l) = delete;
		list& operator=(list&& l) = delete;
		
		//Деструктор
		~list()
		{
			while(first)
			{
				auto tmp = first;
				first = first->succ;
				delete tmp;
			}
		}
		
		iterator begin()	{ return iterator(first); }		//Итератор, указывающий на первый элемент
		iterator  end()		{ return iterator(last); }		//Итератор, указывающий на элемент, следующий за последним
		
		//Вставить v в список после элемента, на который указывает итератор p
		iterator insert(iterator p, const Elem& v);
		
		//Удаление из списка элемента, на который указывает итератор p
		//Возвращает итератор элемента следующего за текущим (или последнего в списке)
		iterator erase(iterator p);
		
		void push_front(const Elem& v);		//Вставка v в начало списка
		void push_back(const Elem& v);		//Вставка v в конец списка
		void pop_front();					//Удаление первого элемента
		void pop_back();					//Удаление последнего элемента
		Elem& front() { return first->val; }		//Первый элемент
		Elem& back()								//Последний элемент
		{
			if(first != last)		return last->prev->val;
			else					return last->val;
		}
		
		Link<Elem>* first;
		Link<Elem>* last;	//Узел находящийся за последним
	};


	template<class Elem>
	class list<Elem>::iterator {
		Link<Elem>* curr;	//Текущий узел
		
	public:
		iterator(Link<Elem>* p) : curr(p)	{  }
		
		Link<Elem>* get_current() { return curr; }
		Link<Elem>* operator->()  { return curr; }
		iterator& operator++()	{ if(curr) curr = curr->succ;	return *this; }		//Вперёд
		iterator& operator--()	{ if(curr) curr = curr->prev;	return *this; }		//Назад
		Elem& operator*()		//Разыменование (получение значения)
		{
			if(curr)	return curr->val;
			else		error("dereferencing of nullptr [list::iterator dereferencing]");
		}
		
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
		Link<Elem>* new_elem = new Link<Elem>(v,0,first);
		first->prev = new_elem;
		first = new_elem;
	}


	//Вставка v в конец списка
	template<class Elem>
	void list<Elem>::push_back(const Elem& v)
	{
		if(first == last)		push_front(v);
		else {
			Link<Elem>* new_elem = new Link<Elem>(v, last->prev, last);
			last->prev->succ = new_elem;
			last->prev = new_elem;
		}
	}


	//Удаление первого элемента
	template<class Elem>
	void list<Elem>::pop_front()
	{
		if(first != last) {
			if(first->succ == last)		//В списке лишь 1 элемент
			{
				delete first;
				delete last;
				first = last = new Link<Elem>{};
			}
			
			else {
				Link<Elem>* tmp = first->succ;	//Запоминаем ссылку на 2ой по счёту элемент списка
				delete first;
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
			if(first->succ == last)		pop_front();	//В списке лишь 1 элемент
			
			else {
				Link<Elem>* tmp = last->prev->prev;
				delete last->prev;
				tmp->succ = last;
				last->prev = tmp;
			}
		}
	}


	//--------------------------------------------------------------------------



	//Вставить v в список после элемента, на который указывает итератор p
	//Возвращает итератор вновь добавленного элемента
	template<class Elem>
	typename list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v)
	{
		if( !(p.get_current()) )		error("nullptr iterator [list insert()]");
		if( p == iterator(last) )		{ push_back(v);		return iterator(last->prev); }
		
		Link<Elem>* new_elem = new Link<Elem>{v, p.get_current(), p->succ};
		p->succ = new_elem;
		return iterator(new_elem);
	}

	//Удаление из списка элемента, на который указывает итератор p
	//Возвращает итератор элемента следующего за текущим (или последнего в списке если удаляется узел следующий за последним (last))
	template<class Elem>
	typename list<Elem>::iterator list<Elem>::erase(iterator p)
	{
		if( !(p.get_current()) )		error("nullptr iterator [list erase()]");
		if( p == iterator(last) )		{ pop_back();		return iterator(last->prev); }
		if( p == iterator(first) )		{ pop_front();		return iterator(  first   ); }
		
		p->succ->prev = p->prev;
		p->prev->succ = p->succ;
		Link<Elem>* tmp = p->succ;
		delete p.get_current();
		return tmp;
	}

}

//------------------------------------------------------------------------------

template<typename Iter>
void out_array(Iter b, Iter e)
{
	cout << "{ ";
	
	for(auto p = b; p != e; ++p) {
		auto tmp = p;
		++tmp;
		
		if(tmp != e)	cout << *p << ", ";
		else			cout << *p;
	}
	
	cout << " }\n";
}

template<typename Iter>		//Требует Input_iterator<Iter>()
Iter high(Iter first, Iter last)
//Возвращает итератор, указывающий на элемент из диапазона [first, last), имеющий наибольшее значение
{
	if(!&*first  ||  !&*last)		error("nullptr in function high(iter, iter) arguments");
	if( first == last )				return last;
	
	Iter high = first;
	for(Iter p = first; p != last; ++p)
		if(*p > *high)		high = p;
	
	return high;
}

int main()
{
	while (true) {
		try
		{
			{
				my_list::list<double> ld;
				
				out_array(ld.begin(), ld.end());
				
				cout << "-------------------------------------------------------\n\n";
				
				ld.push_back(1.2345);
				out_array(ld.begin(), ld.end());
				ld.pop_back();
				out_array(ld.begin(), ld.end());
				
				cout << "-------------------------------------------------------\n\n";
				
				ld.push_front(1.2345);
				out_array(ld.begin(), ld.end());
				ld.pop_front();
				out_array(ld.begin(), ld.end());
				
				cout << "-------------------------------------------------------\n\n";
				
				ld.push_back(1.2345);
				ld.push_back(6.7890);
				out_array(ld.begin(), ld.end());
				ld.pop_back();
				out_array(ld.begin(), ld.end());
				
				cout << "-------------------------------------------------------\n\n";
				
				ld.push_back(6.7890);
				out_array(ld.begin(), ld.end());
				ld.pop_front();
				out_array(ld.begin(), ld.end());
				
				keep_window_open("~");
			}
			
			cout << "\n\n\nDestructor completed\n\n";
			
			{
				my_list::list<double> ld;
				
				cout << "\n\n\nlist<double> front(): " << ld.front() << "\tlist<double> *begin(): " << *(ld.begin());
				//cout << "\n\n\nlist<double> back(): "  <<  ld.back() << "\tlist<double> *( --(ld.end()) ): "  << *( --(ld.end()) );
				cout << "\n\n\nlist<double> back(): "  <<  ld.back();
				cout << "\n\n\nlist<double> begin() != end()?: "  << (ld.begin() != ld.end()) << "\n\n";
				
				cout << "-------------------------------------------------------\n\n";
				
				ld.push_back(1.2);
				ld.push_back(2.3);
				ld.push_back(3.4);
				ld.push_back(4.5);
				ld.push_back(17.3);
				ld.push_front(0.1);
				ld.push_front(13.7);
				out_array(ld.begin(), ld.end());
				ld.pop_back();
				ld.pop_front();
				out_array(ld.begin(), ld.end());
				
				cout << "-------------------------------------------------------\n\n";
				
				auto i = ld.begin();
				++i; ++i; ++i;
				ld.insert(i, 17);
				cout << "\n\nlist<double> insert(iterator of 4th elem, 17):\t";
				out_array(ld.begin(), ld.end());
				
				i = ld.begin();
				++i; ++i; ++i; ++i;
				ld.erase(i);
				cout << "\n\nlist<double> erase(iterator of 5th elem):\t";
				out_array(ld.begin(), ld.end());
				
				cout << "\n\n\nlist<double> front(): " << ld.front() << "\tlist<double> *begin(): " << *(ld.begin());
				cout << "\n\n\nlist<double> back(): "  <<  ld.back() << "\tlist<double> *( --(ld.end()) ): "  << *( --(ld.end()) );
				cout << "\n\n\nlist<double> begin() != end()?: "  << (ld.begin() != ld.end()) << endl;
				
				keep_window_open("~");
			}
			
			cout << "\n\n\nDestructor completed\n\n";
			
			my_list::list<double> ld {1.2, 3, 6, 4.5, 9.0, 7.8, 2};
			cout << "\n\nlist<double>:\t";
			out_array(ld.begin(), ld.end());
			
			ld.pop_front();
			cout << "\n\nlist<double> pop_front():\t";
			out_array(ld.begin(), ld.end());
			
			ld.push_front(1.222);
			cout << "\n\nlist<double> push_front(1.222):\t";
			out_array(ld.begin(), ld.end());
			
			ld.pop_back();
			cout << "\n\nlist<double> pop_back():\t";
			out_array(ld.begin(), ld.end());
			
			ld.push_back(20);
			cout << "\n\nlist<double> push_back(20):\t";
			out_array(ld.begin(), ld.end());
			
			auto i = ld.begin();
			++i; ++i; ++i;
			ld.insert(i, 17);
			cout << "\n\nlist<double> insert(iterator of 4th elem, 17):\t";
			out_array(ld.begin(), ld.end());
			
			i = ld.begin();
			++i; ++i; ++i; ++i;
			ld.erase(i);
			cout << "\n\nlist<double> erase(iterator of 5th elem):\t";
			out_array(ld.begin(), ld.end());
			
			cout << "\n\n\nlist<double> front(): " << ld.front() << "\tlist<double> *begin(): " << *(ld.begin());
			cout << "\n\n\nlist<double> back(): "  <<  ld.back() << "\tlist<double> *( --(ld.end()) ): "  << *( --(ld.end()) );
			cout << "\n\n\nlist<double> begin() != end()?: "  << (ld.begin() != ld.end());
			
			
			auto p = high(ld.begin(), ld.end());
			if (p==ld.end())		cout << "\n\nThe list is empty";
			else					cout << "\n\nHIGH:\t" << *p << endl;
			
			
			keep_window_open("~");
			ld.~list();
			cout << "\n\n\nDestructor completed\n\n";
			
			keep_window_open("~");
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