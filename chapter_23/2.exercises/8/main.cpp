

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <iomanip>			//Для возможности форматирования потока вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------
 
/*int main(int n, char **pat)
{ 
	cout << n << endl;
	for (int i=0; i < n; ++i)
		cout << pat[i] << endl;
	
	keep_window_open("~");
	return 0;
}*/

//Получает из входного потока шиблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main(int cnt, char** args)
try
{
	if(cnt < 2  ||  cnt > 3)	error("need 2 arguments (input file name & string with regex pattern)");
	
	string file_name {args[1]};
	ifstream ifs {file_name};	//Открываем файловый поток ввода
	if(!ifs)		error("Unable to open file '" + file_name + "'");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	
	regex pattern;
	file_name = args[2];
	try {
		pattern = args[2];		// this checks pat
		cout << "pattern: " << file_name << '\n';
	}
	catch (...) { error( "'" + file_name + "' is not a valid regular expression" ); }
	
	string line;
	int num = 0;
	while( getline(ifs,line) )
	{
		++num;
		smatch matches;
		if (regex_search(line, matches, pattern))
			cout << left << setw(10) << ("L" + to_string(num) + ": ") << line << endl;
	}
	
	keep_window_open("~");
	return 0;
}

catch (exception& e) {
	cerr << "Error ( main() ): " << e.what() << '\n';
	keep_window_open();
	if ( Y_or_N(quit_question) )    return 1001;
	else                            main(cnt, args);
}

catch (...) {
	cerr << "Oops! Unknown error! ( main() )\n";
	keep_window_open();
	if ( Y_or_N(quit_question) )    return 1002;
	else                            main(cnt, args);
}