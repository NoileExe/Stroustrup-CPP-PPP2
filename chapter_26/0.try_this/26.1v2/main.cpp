
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>
#include <forward_list>
#include <list>
#include <cmath>
#include <vector>
#include <algorithm>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

namespace bs {

	//На вход: итераторы указывающие на начало и конец упорядоченной по возрастанию
	// (в ином случае неверные результаты) последовательности и искомое значение
	//
	//Работает с vector, list, forward_list
	//
	//Ни в коем случае нельзя менять местами first и last, иначе программа вылетает
	//Ни в коем случае нельзя обрабатывать неупорядоченную последовательность, т.к. есть риск зацикливания
	// (можно было бы исправить таймером, например при достижении 10 секунд возвращать false,
	//   что не совсем верно, т.к. на старых компьютерах правильные большие последовательности могут
	//   обрабатываться дольше этого времени)
	//
	//На выходе результат поиска: найдено(true) или не найдено(false)
	template<class Iter, class T>
	bool binary_search(Iter first, Iter last, const T& val)
	{
		//Пустая последовательность или указатель на крайний левый элемент пуст
		if(first == last  ||  &first == 0)		return false;
		
		Iter p = first;
		unsigned long sz = 0;
		while(p != last)	{ ++p;		++sz; }
		
		p = first;
		for(unsigned long i = 0; i < sz/2; ++i)		++p;
		//середина последовательности
		
		//пока не достигнут конец И не найдено значение
		while(p != last  &&  *p != val)
		{
			if( round(sz/2.0) == 1  &&  *p < val)		++sz;	//чтобы сместились к концу
			
			if(*p < val)		{ first = p; sz = round(sz/2.0); }	//ограничиваем последовательность от текущего проверяемого до конца
			if(val < *p)		{ last = p;  sz = sz/2; }			//ограничиваем последовательность от первого до проверяемого
			
			p = first;
			for(unsigned long i = 0; i < sz/2; ++i)		++p;
			//середина части последовательности
		}
		
		if(p == last  ||  (&p != nullptr  &&  *p != val))		return false;
		return true;
	}

}

//------------------------------------------------------------------------------

template<class T>
ostream& operator<<(ostream& ost, const vector<T>& v)
{
	ost << "{ ";
	for(const T& e : v)		ost << e << ' '; 
	return ost << "}\n\n";
}

template<class T>
ostream& operator<<(ostream& ost, const list<T>& l)
{
	ost << "{ ";
	for(const T& e : l)		ost << e << ' '; 
	return ost << "}\n\n";
}

template<class T>
ostream& operator<<(ostream& ost, const forward_list<T>& l)
{
	ost << "{ ";
	for(const T& e : l)		ost << e << ' '; 
	return ost << "}\n\n";
}


//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			
			cout << "\n\n" << boolalpha;
			
			{
				vector<int> vi {4,2,3,5,1};		//не упорядоченная последовательность
				
				cout << "\n----------------------------------VECTOR---------------------------------\n\n";
				
				cout << vi;
				/*cout << "binary search -10: " << bs::binary_search(vi.begin(), vi.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(vi.begin(), vi.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(vi.begin(), vi.end(), 1) << endl;
				//cout << "binary search 1: " << bs::binary_search(vi.end(), vi.begin(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(vi.begin(), vi.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(vi.begin(), vi.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(vi.begin(), vi.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(vi.begin(), vi.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(vi.begin(), vi.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(vi.begin(), vi.end(), 123) << endl;*/
				
				cout << "\n----------------------------------VECTOR---------------------------------\n\n";
				
				sort(vi.begin(), vi.end(), std::greater<int>());	//по убыванию
				cout << vi;
				cout << "binary search -10: " << bs::binary_search(vi.begin(), vi.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(vi.begin(), vi.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(vi.begin(), vi.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(vi.begin(), vi.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(vi.begin(), vi.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(vi.begin(), vi.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(vi.begin(), vi.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(vi.begin(), vi.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(vi.begin(), vi.end(), 123) << endl;
				
				cout << "\n----------------------------------VECTOR---------------------------------\n\n";
				
				sort(vi.begin(), vi.end());	//по возрастанию
				cout << vi;
				cout << "binary search -10: " << bs::binary_search(vi.begin(), vi.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(vi.begin(), vi.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(vi.begin(), vi.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(vi.begin(), vi.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(vi.begin(), vi.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(vi.begin(), vi.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(vi.begin(), vi.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(vi.begin(), vi.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(vi.begin(), vi.end(), 123) << endl;
				
				cout << "\n----------------------------------VECTOR---------------------------------\n\n";
				
				vi.push_back(6);
				cout << vi;
				cout << "binary search -10: " << bs::binary_search(vi.begin(), vi.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(vi.begin(), vi.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(vi.begin(), vi.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(vi.begin(), vi.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(vi.begin(), vi.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(vi.begin(), vi.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(vi.begin(), vi.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(vi.begin(), vi.end(), 6) << endl;
				cout << "binary search 7: " << bs::binary_search(vi.begin(), vi.end(), 7) << endl;
				cout << "binary search 123: " << bs::binary_search(vi.begin(), vi.end(), 123) << endl;
				
				cout << "\n----------------------------------VECTOR---------------------------------\n\n";
			}
			
			
			
			{
				list<int> li {4,2,3,5,1};		//не упорядоченная последовательность
				
				cout << "\n-----------------------------------LIST----------------------------------\n\n";
				
				cout << li;
				/*cout << "binary search -10: " << bs::binary_search(li.begin(), li.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(li.begin(), li.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(li.begin(), li.end(), 1) << endl;
				//cout << "binary search 1: " << bs::binary_search(li.end(), li.begin(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(li.begin(), li.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(li.begin(), li.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(li.begin(), li.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(li.begin(), li.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(li.begin(), li.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(li.begin(), li.end(), 123) << endl;*/
				
				cout << "\n-----------------------------------LIST----------------------------------\n\n";
				
				li.sort(std::greater<int>());	//по убыванию
				cout << li;
				cout << "binary search -10: " << bs::binary_search(li.begin(), li.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(li.begin(), li.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(li.begin(), li.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(li.begin(), li.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(li.begin(), li.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(li.begin(), li.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(li.begin(), li.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(li.begin(), li.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(li.begin(), li.end(), 123) << endl;
				
				cout << "\n-----------------------------------LIST----------------------------------\n\n";
				
				li.sort();	//по возрастанию
				cout << li;
				cout << "binary search -10: " << bs::binary_search(li.begin(), li.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(li.begin(), li.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(li.begin(), li.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(li.begin(), li.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(li.begin(), li.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(li.begin(), li.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(li.begin(), li.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(li.begin(), li.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(li.begin(), li.end(), 123) << endl;
				
				cout << "\n-----------------------------------LIST----------------------------------\n\n";
				
				li.push_back(6);
				cout << li;
				cout << "binary search -10: " << bs::binary_search(li.begin(), li.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(li.begin(), li.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(li.begin(), li.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(li.begin(), li.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(li.begin(), li.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(li.begin(), li.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(li.begin(), li.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(li.begin(), li.end(), 6) << endl;
				cout << "binary search 7: " << bs::binary_search(li.begin(), li.end(), 7) << endl;
				cout << "binary search 123: " << bs::binary_search(li.begin(), li.end(), 123) << endl;
				
				cout << "\n-----------------------------------LIST----------------------------------\n\n";
			}
			
			
			
			{
				forward_list<int> fli {4,2,3,5,1};		//не упорядоченная последовательность
				
				cout << "\n---------------------------------FW_LIST---------------------------------\n\n";
				
				cout << fli;
				/*cout << "binary search -10: " << bs::binary_search(fli.begin(), fli.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(fli.begin(), fli.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(fli.begin(), fli.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(fli.begin(), fli.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(fli.begin(), fli.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(fli.begin(), fli.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(fli.begin(), fli.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(fli.begin(), fli.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(fli.begin(), fli.end(), 123) << endl;*/
				
				cout << "\n---------------------------------FW_LIST---------------------------------\n\n";
				
				fli.sort(std::greater<int>());	//по убыванию
				cout << fli;
				cout << "binary search -10: " << bs::binary_search(fli.begin(), fli.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(fli.begin(), fli.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(fli.begin(), fli.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(fli.begin(), fli.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(fli.begin(), fli.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(fli.begin(), fli.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(fli.begin(), fli.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(fli.begin(), fli.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(fli.begin(), fli.end(), 123) << endl;
				
				cout << "\n---------------------------------FW_LIST---------------------------------\n\n";
				
				fli.sort();	//по возрастанию
				cout << fli;
				cout << "binary search -10: " << bs::binary_search(fli.begin(), fli.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(fli.begin(), fli.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(fli.begin(), fli.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(fli.begin(), fli.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(fli.begin(), fli.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(fli.begin(), fli.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(fli.begin(), fli.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(fli.begin(), fli.end(), 6) << endl;
				cout << "binary search 123: " << bs::binary_search(fli.begin(), fli.end(), 123) << endl;
				
				cout << "\n---------------------------------FW_LIST---------------------------------\n\n";
				
				auto p = fli.begin();
				auto tmp = p;
				while(p != fli.end())		{ tmp = p;		++p; }
				fli.insert_after(tmp, 6);
				cout << fli;
				cout << "binary search -10: " << bs::binary_search(fli.begin(), fli.end(), -10) << endl;
				cout << "binary search 0: " << bs::binary_search(fli.begin(), fli.end(), 0) << endl;
				cout << "binary search 1: " << bs::binary_search(fli.begin(), fli.end(), 1) << endl;
				cout << "binary search 2: " << bs::binary_search(fli.begin(), fli.end(), 2) << endl;
				cout << "binary search 3: " << bs::binary_search(fli.begin(), fli.end(), 3) << endl;
				cout << "binary search 4: " << bs::binary_search(fli.begin(), fli.end(), 4) << endl;
				cout << "binary search 5: " << bs::binary_search(fli.begin(), fli.end(), 5) << endl;
				cout << "binary search 6: " << bs::binary_search(fli.begin(), fli.end(), 6) << endl;
				cout << "binary search 7: " << bs::binary_search(fli.begin(), fli.end(), 7) << endl;
				cout << "binary search 123: " << bs::binary_search(fli.begin(), fli.end(), 123) << endl;
				
				cout << "\n---------------------------------FW_LIST---------------------------------\n\n";
			}
			
			cout << "\n\n" << noboolalpha;
			
			cin.putback('\n');
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