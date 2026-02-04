

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <vector>
#include <numeric>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

namespace cnt
{

	template<class Iter>
	unsigned long count(Iter first, Iter last)
	{
		unsigned long n {0};
		for(auto p = first; p != last; ++p)		++n;
		return n;
	}

	template<class Iter, class Pred>
	unsigned long count_if(Iter first, Iter last, Pred p)
	{
		unsigned long n {0};
		for(auto it = first; it != last; ++it)
			if( p(*it) )	++n;
		return n;
	}

}

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	for(auto p = vt.begin(); p != vt.end(); ++p) {
		auto tmp = p;
		++tmp;
		
		if(tmp != vt.end())		ost << *p << ", ";
		else					ost << *p;
	}
	
	ost << " }";
	
	return ost;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			vector<double> vd { 0.1, 1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.1, 10.11, 11.12, 12.13, 14.15, 15.16, 16.17 };
			
			cout << "\n\tvector<double> with elem count "
				 << cnt::count(vd.begin(), vd.end()) << '/' << vd.size()
				 << ":\n\n" << vd;		//Вывод значений vector на экран
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			double midd = accumulate(vd.begin(), vd.end(), 0.0) / vd.size();
			cout << "\n\tvector<double> elem count greater than middle (" << midd << "): "
				 << cnt::count_if( vd.begin(), vd.end(), [&](double n) { return n > midd; } );
			
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