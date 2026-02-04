


#include "pool.h"		//Включает <yes_or_no.h>, <iomanip>, <sstream> и <fstream>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<class T, unsigned long N>
std::ostream& operator<<(ostream& ost, const vctr<T,N>& v)
{
	ost << "{ ";
	for (int i = 0; i < v.size(); ++i)
		ost << v[i] << ' '; 
	
	return ost << "}\n\n";
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			constexpr int sz {10};
			
			vctr<int, sz> v {};
			cout << "Empty vctr\n" << v;
			
			//v.pop_back();	//Error ( main() ): vector is empty [ vctr::pop_back() ]
			
			for (int i = 0; i < sz; ++i)		v.push_back(i);
			cout << "Full vctr\n" << v;
			
			v.pop_back();
			cout << "vctr with popback()\n" << v;
			
			v.push_back(123);
			//v.push_back(10);	//Error ( main() ): vector is full [ vctr::push_back() ]
			cout << "Full vctr\n" << v;
			
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