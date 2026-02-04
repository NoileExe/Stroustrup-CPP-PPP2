

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>	//Включает <string>, <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <iomanip>		//Для возможности форматирования потока вывода


using namespace std;

//------------------------------------------------------------------------------

typedef string::const_iterator Line_iter;
//using Line_iter = string::const_iterator;

//Указывает на первый и последний символ строки
class Line {
	Line_iter first;
	Line_iter last;
	
public:
	Line(Line_iter p1, Line_iter p2) : first(p1), last(p2)	{  }
	
	Line_iter begin() const { return first; }
	Line_iter end()   const { return last; }
};

//Вывод одной строки
ostream& operator<<(ostream& ost, const Line& l)
{
	for(auto ch : l)		ost << ch;
	return ost;
}

//------------------------------------------------------------------------------

typedef vector<Line>::const_iterator Doc_iter;
//using Doc_iter = vector<Line>::const_iterator;

//Хранит все строки из файла и упрощает доступ к ним
struct Document {
	string full_text;		//Вся строка в памяти
	vector<Line> lines;		//Итератор на начало и конец (символ перехода на новую строку) каждой строки
	
	///Открывает файл с именем n и считывает посимвольно всё содержимое в full_text
	//Находит в full_text границы сообщений и помещает их в lines
	//Установленно, что каждая строка заканчивается символом '\n'
	Document(const string& n)
	{
		ifstream ifs {n};	//Открываем файловый поток ввода
		if(!ifs)		error("Unable to open file '" + n + "'");
		ifs.exceptions(ifs.exceptions() | ios_base::badbit);
		
		for(char ch = ' '; ifs.get(ch); )		full_text+=ch;
		ifs.close();
		
		Line_iter first = full_text.begin();
		Line_iter last = full_text.begin();
		while(first != full_text.end())
			if( ++last == full_text.end()  ||  *last == '\n' ) {
				lines.push_back(Line{first,last});
				first = last;
			}
	}
	
	Doc_iter begin() const { return lines.begin(); }
	Doc_iter end()   const { return lines.end(); }
	
	Line& front()
	{
		if(lines.size())	return lines[0];
		else				error("trying to access an empty document [ Document::front() ]");
	}
	
	Line& back(){
		if(lines.size())	return lines[lines.size()-1];
		else				error("trying to access an empty document [ Document::front() ]");
	}
};