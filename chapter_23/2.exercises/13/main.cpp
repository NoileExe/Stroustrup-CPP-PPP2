

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>	//Включает <string>, <iostream>
#include <sstream>
#include <regex>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			string test {"\n"};
			regex dot {"."};
			smatch matches;
			
			if( regex_match(test, matches, dot) )		cout << "test (one newline) MATCHES the pattern \".\"\n\n";
			else										cout << "test (one newline) NOT matches the pattern \".\"\n\n";
			
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