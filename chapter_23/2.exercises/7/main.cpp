

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <iomanip>			//Для возможности форматирования потока вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//На вход проверяемая строка
//Форматы номера карты:
//	(Начало_строки или пробельный_символ)dddd-dddd-dddd-dddd(Конец_строки или пробельный_символ)
//Возвращает true если строка содержит номер по шаблону
bool contains_card_num(const string& str)
{
	regex card_num;
	
	string pat = "(^|\\s)(\\d{4}-\\d{4}-\\d{4}-\\d{4})($|\\s)";		//dddd-dddd-dddd-dddd
	try { card_num = pat; }
	catch (...) { error( "'" + pat + "' is not a valid regular expression [contains_card_num()]" ); }
	
	smatch matches;
	if( regex_search(str, matches, card_num) )
	{
		int first {0}, second {0}, third {0}, fourth {0};
		char ch1, ch2, ch3;
		
		istringstream iss {matches[0]};
		iss >> first >> ch1 >> second >> ch2 >> third >> ch3 >> fourth;
		
		if(ch1 != '-'  ||  ch2 != '-'  ||  ch3 != '-'  ||  first < 0  ||  second < 0  ||  third < 0  ||  fourth < 0)
				return false;
		else	return true;
	}
	
	return false;
}

int main()
{
	while (true) {
		try
		{
			string file_name {"in.txt"};
			
			ifstream ifs {file_name};	//Открываем файловый поток ввода
			if(!ifs)		error("Unable to open file '" + file_name + "'");
			ifs.exceptions(ifs.exceptions() | ios_base::badbit);
			
			unsigned int num {0};
			while( getline(ifs, file_name) )
			{
				++num;
				if( contains_card_num(file_name) )		cout << left << setw(10) << ("L" + to_string(num) + ": ") << file_name << endl;
			}
			
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