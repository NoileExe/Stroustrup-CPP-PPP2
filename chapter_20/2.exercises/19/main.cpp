


#include <yes_or_no.h>
#include "lst.h"


const string quit_question = "Close program?";

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
	//cout << to_string(&*first) << "\t" << &*last << endl;
	//keep_window_open("0");
	
	if(!&*first  ||  !&*last)		error("nullptr in function high(iter, iter) arguments");
	keep_window_open("~"); if( first == last )				return last;
	
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


			{
				my_list::list<double> ld;
				
				//cout << "\n\n\nlist<double> front(): " << ld.front() << "\tlist<double> *begin(): " << *(ld.begin());
				//cout << "\n\n\nlist<double> front(): " << ld.front();
				//cout << "\n\n\nlist<double> back(): "  <<  ld.back();
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
				cout << "\n\n\nlist<double> back(): "  <<  ld.back();
				cout << "\n\n\nlist<double> begin() != end()?: "  << (ld.begin() != ld.end()) << "\n\n";
				
				keep_window_open("~");
			}


			{
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
				cout << "\n\n\nlist<double> back(): "  <<  ld.back();
				cout << "\n\n\nlist<double> begin() != end()?: "  << (ld.begin() != ld.end()) << endl;
				
				
				auto p = high(ld.begin(), ld.end());
				if (p==ld.end())		cout << "\n\nThe list is empty";
				else					cout << "\n\nHIGH:\t" << *p << endl;
			}


			{
				const my_list::list<double> ld {1.2, 3, 6, 4.5, 9.0, 7.8, 2};
				cout << "\n\nCONST list<double>:\t";
				out_array(ld.begin(), ld.end());
				
				cout << "\n\n\nCONST list<double> front(): " << ld.front() << "\t\tCONST list<double> *begin(): " << *(ld.begin());
				cout << "\n\n\nCONST list<double> back(): "  <<  ld.back();
				cout << "\n\n\nCONST list<double> begin() != end()?: "  << (ld.begin() != ld.end()) << endl;
				
				
				auto p = high(ld.begin(), ld.end());
				if (p==ld.end())		cout << "\n\nThe list is empty";
				else					cout << "\n\nCONST list HIGH:\t" << *p << endl;
			}
			
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