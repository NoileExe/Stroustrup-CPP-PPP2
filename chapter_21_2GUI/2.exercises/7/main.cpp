
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

namespace bs {

	template<class Iter, class T>
	bool binary_search(Iter first, Iter last, const T& val)
	{
		if(first == last  ||  &*first == nullptr)		return false;
		
		Iter p = first + (last-first)/2;
		while(p != last  &&  *p != val)
		{
			if( (last-first)/2 == 0 )		last = first;
			if(*p < val)					first = p;
			if(val < *p)					last = p;
			p = first + (last-first)/2;
		}
		
		if(*p != val)		return false;
		return true;
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
	
	cout << " }";
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			vector<double> vd { 15.16, 0.1, 1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.1, 10.11, 11.12, 12.13, 14.15, 16.17 };
			sort(vd.begin(), vd.end());
			//sort(vd.begin(), vd.end(), [](double a, double b) {return a > b;});		//При обратной сортировке почти ни один из элементов не находится
			cout << "\n\tSorted vector<double>\n\n";
			out_array(vd.begin(), vd.end());
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			//cout << boolalpha;
			string str = "vector<double> binary_search value ";
			cout << "\n\t" << setw(42) << str + "-1:\t"		<< (bs::binary_search(vd.begin(), vd.end(), -1)		? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "888:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 888)	? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "0.1:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 0.1)	? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "1.2:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 1.2)	? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "7.8:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 7.8)	? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "8.9:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 8.9)	? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "11.12:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 11.12)	? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "12.13:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 12.13)	? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "15.16:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 15.16)	? "found" : "NOT found") << endl;
			cout << "\n\t" << setw(42) << str + "16.17:\t"	<< (bs::binary_search(vd.begin(), vd.end(), 16.17)	? "found" : "NOT found") << endl;
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
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