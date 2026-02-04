

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <regex>
#include <fstream>
#include <stdexcept>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Получает из входного потока шиблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main()
{
	while (true) {
		try
		{
			string n = "in.txt";
			ifstream in {n};	//Открываем файловый поток ввода
			if(!in)		error("Unable to open file '" + n + "'");
			in.exceptions(in.exceptions() | ios_base::badbit);
			
			/*boost::*/regex pat ("\\w{2}\\s*\\d{5}(-\\d{4})?");	// ZIP code pattern
			//cout << "pattern: " << pat << '\n';
			
			int lineno = 0;
			string line;	// input buffer
			while (getline(in,line)) {
				++lineno;
				/*boost::*/smatch matches;		// matched strings go here
				if (/*boost::*/regex_search(line, matches, pat)) {
					cout << lineno << ": " << matches[0] << '\n';
					if (1<matches.size() && matches[1].matched)
						cout  << "\t: " << matches[1] << '\n';		// sub-match
				}
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