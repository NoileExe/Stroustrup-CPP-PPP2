
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

namespace bs {

	//На вход: итераторы указывающие на начало и конец упорядоченной по возрастанию
	// (в ином случае неверные результаты) последовательности и искомое значение
	//На выходе результат поиска: найдено(true) или не найдено(false)
	template<class Iter, class T>
	bool binary_search(Iter first, Iter last, const T& val)
	{
		//Пустая последовательность или указатель на крайний левый элемент пуст
		if(first == last  ||  &*first == nullptr)		return false;
		if((last-first) < 0)							swap(first, last);		//если итераторы поменяны местами, меняем на верный вариант
		
		Iter p = first + (last-first)/2;	//середина последовательности (даже если итераторы поменяны местами)
		
		//пока не достигнут конец И не найдено значение
		while(p != last  &&  *p != val)
		{
			if( (last-first)/2 == 0 )		last = first;	//сместились к концу
			if(*p < val)					first = p;		//ограничиваем последовательность от текущего проверяемого до конца
			if(val < *p)					last = p;		////ограничиваем последовательность от первого до проверяемого
			p = first + (last-first)/2;		//серидина части последовательности
		}
		
		if(*p != val)		return false;
		return true;
	}

}

//------------------------------------------------------------------------------

template<class T>
std::ostream& operator<<(ostream& ost, const vector<T>& v)
{
	ost << "{ ";
	for(const T& e : v)		ost << e << ' '; 
	return ost << "}\n\n";
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n" << boolalpha;
			
			vector<int> vi {4,2,3,5,1};		//не упорядоченная последовательность
			cout << vi;
			cout << "binary search 1: " << bs::binary_search(vi.begin(), vi.end(), 1) << endl;
			cout << "binary search 2: " << bs::binary_search(vi.begin(), vi.end(), 2) << endl;
			cout << "binary search 3: " << bs::binary_search(vi.begin(), vi.end(), 3) << endl;
			cout << "binary search 4: " << bs::binary_search(vi.begin(), vi.end(), 4) << endl;
			cout << "binary search 5: " << bs::binary_search(vi.begin(), vi.end(), 5) << endl;
			
			cout << "\n------------------------------------------------------------------------------\n\n";
			
			sort(vi.begin(), vi.end(), std::greater<int>());	//по убыванию
			cout << vi;
			cout << "binary search 1: " << bs::binary_search(vi.begin(), vi.end(), 1) << endl;
			cout << "binary search 2: " << bs::binary_search(vi.begin(), vi.end(), 2) << endl;
			cout << "binary search 3: " << bs::binary_search(vi.begin(), vi.end(), 3) << endl;
			cout << "binary search 4: " << bs::binary_search(vi.begin(), vi.end(), 4) << endl;
			cout << "binary search 5: " << bs::binary_search(vi.begin(), vi.end(), 5) << endl;
			
			cout << "\n------------------------------------------------------------------------------\n\n";
			
			sort(vi.begin(), vi.end(), std::less<int>());	//по возрастанию
			cout << vi;
			cout << "binary search 1: " << bs::binary_search(vi.begin(), vi.end(), 1) << endl;
			cout << "binary search 2: " << bs::binary_search(vi.begin(), vi.end(), 2) << endl;
			cout << "binary search 3: " << bs::binary_search(vi.begin(), vi.end(), 3) << endl;
			cout << "binary search 4: " << bs::binary_search(vi.begin(), vi.end(), 4) << endl;
			cout << "binary search 5: " << bs::binary_search(vi.begin(), vi.end(), 5) << endl;
			
			cout << "\n------------------------------------------------------------------------------\n\n";
			
			sort(vi.begin(), vi.end());	//по возрастанию
			cout << vi;
			cout << "binary search 1: " << bs::binary_search(vi.end(), vi.begin(), 1) << endl;
			cout << "binary search 2: " << bs::binary_search(vi.end(), vi.begin(), 2) << endl;
			cout << "binary search 3: " << bs::binary_search(vi.end(), vi.begin(), 3) << endl;
			cout << "binary search 4: " << bs::binary_search(vi.end(), vi.begin(), 4) << endl;
			cout << "binary search 5: " << bs::binary_search(vi.end(), vi.begin(), 5) << endl;
			
			cout << "\n------------------------------------------------------------------------------\n\n";
			
			vi.push_back(6);
			cout << vi;
			cout << "binary search 1: " << bs::binary_search(vi.begin(), vi.end(), 1) << endl;
			cout << "binary search 2: " << bs::binary_search(vi.begin(), vi.end(), 2) << endl;
			cout << "binary search 3: " << bs::binary_search(vi.begin(), vi.end(), 3) << endl;
			cout << "binary search 4: " << bs::binary_search(vi.begin(), vi.end(), 4) << endl;
			cout << "binary search 5: " << bs::binary_search(vi.begin(), vi.end(), 5) << endl;
			cout << "binary search 6: " << bs::binary_search(vi.begin(), vi.end(), 6) << endl;
			
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