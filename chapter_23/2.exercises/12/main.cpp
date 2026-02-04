

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>	//Включает <string>, <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <iomanip>		//Для возможности форматирования потока вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Перевод строкового значения в тип T путём строкового потока ввода
template<class T>
T from_string(const string& s)
{
	istringstream is(s);
	T t;
	if (!(is >> t))		error("bad cast from string [ from_string() ]");
	return t;
}

//Перевод месяца в число
//Возвращает 0 если записанный в виде строки переданный в качестве аргумента не найден
int month_to_num(const string& s)
{
	regex jan {"Jan(\\.|uary)?"};
	regex feb {"Feb(\\.|ruary)?"};
	regex mar {"Mar(\\.|ch)?"};
	regex apr {"Apr(\\.|il)?"};
	regex may {"May"};
	regex jun {"Jun(\\.|e)?"};
	regex jul {"Jul(\\.|y)?"};
	regex aug {"Aug(\\.|ust)?"};
	regex sep {"Sep(\\.|tember)?"};
	regex oct {"Oct(\\.|ober)?"};
	regex nov {"Nov(\\.|ember)?"};
	regex dec {"Dec(\\.|ember)?"};
	
	smatch matches;
	
	if( regex_match(s, matches, jan) )		return 1;
	if( regex_match(s, matches, feb) )		return 2;
	if( regex_match(s, matches, mar) )		return 3;
	if( regex_match(s, matches, apr) )		return 4;
	if( regex_match(s, matches, may) )		return 5;
	if( regex_match(s, matches, jun) )		return 6;
	if( regex_match(s, matches, jul) )		return 7;
	if( regex_match(s, matches, aug) )		return 8;
	if( regex_match(s, matches, sep) )		return 9;
	if( regex_match(s, matches, oct) )		return 10;
	if( regex_match(s, matches, nov) )		return 11;
	if( regex_match(s, matches, dec) )		return 12;
	
	return 0;
}

//------------------------------------------------------------------------------

//На вход проверяемая строка
//Форматы искомой даты:
//	ДД.ММ.ГГГГ или ДД МЕСяц ГГГГ
//Если дата в одном из форматов найдена, то она преобразуется в ISO формат (ГГГГ-ММ-ДД)
// при этом измененяется исходная строка
//Возвращает true если найдено совпадение по шаблону и строка была изменена
bool formate_date(string& str)
{
	regex date1;
	
	string pat = "(^.*\\s+|^)";
	pat += "(\\d{1,})";
	pat += "([-./])";
	pat += "(\\d{1,})";
	pat += "([-./])";
	pat += "(\\d{1,})";
	pat += "(\\s+.*$|$)";		//текст ДД.ММ.ГГГГ текст
	
	
	try { date1 = pat; }
	catch (...) { error( "'" + pat + "' is not a valid regular expression [contains_date()]" ); }
	
	smatch matches;
	if( regex_search(str, matches, date1) )
	{
		//matches[1] - текст с пространством перед датой
		int day  {from_string<int>(matches[2])};	//Число
		string ch1 {matches[3]};
		int month {from_string<int>(matches[4])};	//Месяц
		string ch2 {matches[5]};
		int year  {from_string<int>(matches[6])};	//Год
		//matches[7] - пространство с текстом после даты
		
		//Если разделители не равны  ИЛИ  число вне диапазона [1;31]  ИЛИ  месяц вне диапазона [1;12]
		//  ИЛИ  год вне диапазона [1;9999]  -  данное не является датой
		if(ch1 != ch2  ||  day < 1  ||  31 < day  ||  month < 1  ||  12 < month  ||  year < 1  ||  9999 < year)
				return false;
		else {
			ostringstream oss;
			oss << matches[1] << setfill('0') << setw(4) << to_string(year) << "-"
				<< setfill('0') << setw(2) << to_string(month) << "-"
				<< setfill('0') << setw(2) << to_string(day) << matches[7];
			str = oss.str();
			
			return true;
		}
	}
	
	//------------------------------------------------------------------------------
	
	regex date2;
	
	pat = "(^.*\\s+|^)";
	pat += "(\\d{1,})";
	pat += "(\\s)";
	pat += "(Jan(\\.|uary)?|Feb(\\.|ruary)?|Mar(\\.|ch)?|Apr(\\.|il)?|May|Ju(\\.|ne|ly)?";
	pat += "|Aug(\\.|ust)?|Sep(\\.|tember)?|Oct(\\.|ober)?|Nov(\\.|ember)?|Dec(\\.|ember)?)";
	pat += "(\\s)";
	pat += "(\\d{1,})";
	pat += "(\\s+.*$|$)";		//текст ДД МЕСяц ГГГГ текст
	
	try { date2 = pat; }
	catch (...) { error( "'" + pat + "' is not a valid regular expression [contains_date()]" ); }
	
	if( regex_search(str, matches, date2) )
	{
		//matches[1] - текст с пространством перед датой
		int day  {from_string<int>(matches[2])};	//Число
		//matches[3] - пробельный символ
		int month {month_to_num(matches[4])};	//Месяц
		//matches[matches.size()-3] - пробельный символ
		int year  {from_string<int>(matches[matches.size()-2])};	//Год
		//matches[matches.size()-1] - пространство с текстом после даты
		
		if(day < 1  ||  31 < day  ||  month < 1  ||  12 < month  ||  year < 1  ||  9999 < year)
				return false;
		else {
			ostringstream oss;
			oss << matches[1] << setfill('0') << setw(4) << to_string(year) << "-"
				<< setfill('0') << setw(2) << to_string(month) << "-"
				<< setfill('0') << setw(2) << to_string(day) << matches[matches.size()-1];
			str = oss.str();
			
			return true;
		}
	}
	
	//------------------------------------------------------------------------------
	
	return false;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			string infile_name {"in.txt"};
			string outfile_name {"out.txt"};
			
			ifstream ifs {infile_name};	//Открываем файловый поток ввода
			if(!ifs)		error("Unable to open file '" + infile_name + "'");
			ifs.exceptions(ifs.exceptions() | ios_base::badbit);
			
			ofstream ofs(outfile_name);
			if (!ofs)		error("Can't open output file '" + outfile_name + "'");
			
			while( getline(ifs, infile_name) )
			{
				formate_date(infile_name);
				ofs << infile_name << endl;
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