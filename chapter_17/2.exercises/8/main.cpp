
//Достаточно 8 символов для переполнения памяти? 9 символ отличается от введёного

#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "Please enter some characters. Terminate with '!'\n";
			
			string str;
			char ch {' '};
			
			while( cin >> ch   &&   ch != '!' ) {
				str += ch;
				cout << str << '\n';
			}
			
			//Не CTRL+Z, но поток при этом в состоянии fail
			if ( !cin.eof()  &&  !cin )		error("bad input");
			
			keep_window_open("~~");
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