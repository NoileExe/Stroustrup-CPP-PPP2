
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void to_lower (char* s) {
					//латинские буквы
	int l2u { abs(int('a') - int('A')) }; //количество символов между строчной и заглавной буквами
	
	for (int i = 0;   s[i] != 0;   ++i)
		if ( s[i] < 'a'  &&  isalpha(s[i]) )		s[i] = char( int(s[i]) + l2u );
}


int main()
{
	while (true) {
		try
		{
			char str[] = "Hello, World! XYZ";	//Строка Си-типа
			cout << str << '\n';
			
			to_lower(str);
			cout << str << '\n';
			
			keep_window_open();
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