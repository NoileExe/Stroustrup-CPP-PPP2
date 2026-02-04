

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <regex>
#include <fstream>
#include <sstream>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void wrong_patterns()
{
	regex pat1("(|ghi)");	// missing alternative
	regex pat2("[c-a]");	// not a range
}

//------------------------------------------------------------------------------

//Получает из входного потока шиблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main()
{
	while (true) {
		try
		{
			regex pattern;
			
			string pat;
			cout << "enter pattern: ";
			getline(cin,pat);		// read pattern
			
			
			//wrong_patterns();
			try {
				//wrong_patterns();
				
				pattern = pat;		// this checks pat
				cout << "pattern: " << pat << '\n';
				//cout << "pattern: " << pattern << '\n';
			}
			//catch (bad_expression& b) {
			catch (...) {
				ostringstream ss;
				ss << "'" << pat << "' is not a valid regular expression";
				error( ss.str() );
			}
			
			cout << "now enter lines:\n> ";
			string line;			// input buffer
			int lineno = 0;
			
			while (getline(cin,line))
			{
				++lineno;
				smatch matches;
				if (regex_search(line, matches, pattern))
				{
					cout << "line " << lineno << ": " << line << "\t" << matches.size() << endl;
					for (int i = 0; i<matches.size(); ++i)		cout << "\tmatches[" << i << "]: " <<  matches[i]  << endl;
				}
				else		cout << "didn't match\n";
				
				cout << "\n> ";
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