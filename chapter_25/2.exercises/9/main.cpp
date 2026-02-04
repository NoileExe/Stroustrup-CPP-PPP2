
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
//#include <iomanip>						//Для возможности форматирования потока вывода
//#include <sstream>						//Для строкового потока ввода-вывода
#include <typeinfo>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			//long long int num = 1;
			int num = 1;
			int bits_count = 0;
			while(num != 0)
			{
				++bits_count;
				num <<= 1;
			}
			
			cout << "Number of bits in an " << typeid(num).name() << ": " << bits_count << "\n\n";
			
			
			string str = (int(char{-1}) < 0)  ?  "char is signed" : "char is unsigned";
			cout << str << "\n\n";
			
			
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