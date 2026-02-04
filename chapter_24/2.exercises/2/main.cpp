

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>				//Включает <string>, <iostream>
#include <MatrixIO11.h>		//Включает <string>, <algorithm>, <iostream>
#include <iomanip>	//Для возможности форматирования потока вывода


using namespace std;
using namespace Numeric_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T> struct triple1 {
	void operator()(T& n) { n *= 3; }
};

template<typename T> struct triple2 {
	int operator()(T n) { return n *= 3; }
};

template<typename T> struct triple3 {
	int operator()(T& n) { return n *= 3; }
};

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			int val[] { 1, 2, 3, 4, 5 };
			Matrix<int> m1{val};
			Matrix<int> m2{m1};
			Matrix<int> m3{m1.data(), m1.size()};
			
			cout << left << setw(35) << "m1{int array}: " << m1 << "\n\n";
			cout << left << setw(35) << "m2{m1}: " << m2 << "\n\n";
			cout << left << setw(35) << "m3{m1.data(), m1.size()}: " << m3 << "\n\n\n\n";
			
			m1.apply( triple1<int>() );
			m2 = apply( triple2<int>(), m1 );
			m3.apply( triple3<int>() );
			
			cout << left << setw(35) << "m1.apply( triple1<int>() ): " << m1 << "\n\n";
			cout << left << setw(35) << "m2 = apply( triple2<int>(), m1 ): " << m2 << "\n\n";
			cout << left << setw(35) << "m3.apply( triple3<int>() ): " << m3 << "\n\n";
			
			m3 = apply( triple3<int>(), m1 );
			cout << left << setw(35) << "m3 = apply( triple3<int>(), m1 ): " << m3 << "\n\n";
			cout << left << setw(35) << "m1: " << m1 << "\n\n\n\n";
			
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