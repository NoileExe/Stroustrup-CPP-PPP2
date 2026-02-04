

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
//Форматы даты:
//	ДД.ММ.ГГГГ
//Возвращает true если строка содержит дату по одному из шаблонов
bool contains_date(const string& str)
{
	regex date1;
	
	//string pat = "(\\d{1,2})([-./])(\\d{1,2})([-./])(\\d{1,4})";		//ДД.ММ.ГГГГ
	string pat = "(\\d{1,})";
	pat += "([-./])";
	pat += "(\\d{1,})";
	pat += "([-./])";
	pat += "(\\d{1,})";		//ДД.ММ.ГГГГ
	
	
	try { date1 = pat; }
	catch (...) { error( "'" + pat + "' is not a valid regular expression [contains_date()]" ); }
	
	smatch matches;
	if( regex_search(str, matches, date1) ) {
		//cout << matches[0] << '\t' << matches[1] << ' ' << matches[2] << ' ' << matches[3] << ' ' << matches[4] << ' ' << matches[5] << ' ' << endl;
		int first {0}, second {0}, third {0};
		char ch1, ch2;
		
		istringstream iss {matches[0]};
		iss >> first >> ch1 >> second >> ch2 >> third;
		
		//Если разделители не равны  ИЛИ  число вне диапазона [1;31]  ИЛИ  месяц вне диапазона [1;12]
		//	ИЛИ  год вне диапазона [1;9999]  -  данное не является датой
		if(ch1 != ch2  ||  first < 1  ||  31 < first  ||  second < 1  ||  12 < second  ||  third < 1  ||  9999 < third)
				return false;
		else	return true;
	}
	
	//------------------------------------------------------------------------------
	
	regex date2;
	
	pat = "(\\d*)";
	pat += "(\\s)";
	pat += "(Jan(\\.|uary)?|Feb(\\.|ruary)?|Mar(\\.|ch)?|Apr(\\.|il)?|May|Ju(\\.|ne|ly)?";
	pat += "|Aug(\\.|ust)?|Sep(\\.|tember)?|Oct(\\.|ober)?|Nov(\\.|ember)?|Dec(\\.|ember)?)";
	pat += "(\\s)";
	pat += "(\\d{1,})";		//ДД МЕСяц ГГГГ
	
	try { date2 = pat; }
	catch (...) { error( "'" + pat + "' is not a valid regular expression [contains_date()]" ); }
	
	if( regex_search(str, matches, date2) ) {
		string tmp {matches[1]};
		/*cout << "matches[1].size() " << tmp.size() << endl;
		cout << matches[0] << '\t' << matches[1] << ' ' << matches[2] << ' ' << matches[3] << ' ' << matches[matches.size()-2] 
			 << ' ' << matches[matches.size()-1] << endl;*/
		
		int first {0};
		string second {0};
		int third {0};
		
		istringstream iss {matches[0]};
		if( tmp.size() )	iss >> first;
		iss >> second >> third;
		
		if((tmp.size() && (first<1 || 31<first))  ||  third < 1  ||  9999 < third)
				return false;
		else	return true;
	}
	
	//------------------------------------------------------------------------------
	
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
				if( contains_date(file_name) )		cout << left << setw(10) << ("L" + to_string(num) + ": ") << file_name << endl;
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