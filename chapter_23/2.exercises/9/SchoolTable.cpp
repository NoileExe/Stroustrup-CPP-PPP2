


#include "SchoolTable.h"	//Содержит <string>, <iostream>, <fstream>, <sstream>, <regex>

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

//------------------------------------------------------------------------------

//Операторы сравнения для структуры one_class
bool operator<(const one_class &a, const one_class &b)		{ return a.num < b.num  ||  (a.num == b.num  &&  a.alpha < b.alpha); }
bool operator>(const one_class &a, const one_class &b)		{ return a.num > b.num  ||  (a.num == b.num  &&  a.alpha > b.alpha); }
bool operator==(const one_class &a, const one_class &b)		{ return a.num == b.num  &&  a.alpha == b.alpha; }
bool operator!=(const one_class &a, const one_class &b)		{ return !(a == b); }

//Оператор вывода для структуры one_class
ostream& operator<<(ostream &ost, const one_class &cl)
{
	string class_num {cl.alpha};
	if(cl.num >= 0)		class_num = to_string(cl.num) + class_num;
	
	ost << left << setw(20) << class_num
		<< left << setw(15) << ("Boys " + to_string(cl.boys))
		<< left << setw(15) << ("Girls " + to_string(cl.girls))
		<< left << setw(15) << ("Total " + to_string(cl.boys+cl.girls));
	
	return ost;
}

//Оператор ввода для структуры one_class
istream& operator>>(istream &ist, one_class &cl)
{
	int num {-1};	//Номер класса
	string alpha;	//Буква класса
	int boys;		//Кол-во в классе учеников (мальчиков)
	int girls;		//Кол-во в классе учениц (девочек)
	
	string line {""};
	while(line.size() == 0  &&  getline(ist, line))		{  }
	
	if (ist.eof())		return ist;
	else if (!ist)		{ ist.clear(ios_base::failbit);		return ist; }
	
	
	
	regex row { "^([\\w ]+)(\\s+\\d+)(\\s+\\d+)(\\s+\\d+)$" };
	smatch matches;
	if (!regex_search(line, matches, row))		{ ist.clear(ios_base::failbit);		return ist; }
	
	//Класс и буквы
	istringstream iss {matches[1]};
	if( isdigit(iss.str()[0]) )		iss >> num >> alpha;
	else							getline(iss, alpha);
	
	//Проверка числовых значений строки
	boys = from_string<int>(matches[2]);
	girls = from_string<int>(matches[3]);
	int summ_row = from_string<int>(matches[4]);
	
	if (boys+girls != summ_row)		error("bad row sum [ operator>>(one_class) ]");
	if (boys < 0  ||  girls < 0)	error("negative value [ operator>>(one_class) ]");
	
	
	
	cl = one_class {num, alpha, boys, girls};
	
	if(alpha == "Alle klasser")		ist.clear(ios_base::eofbit);
	return ist;
}

//------------------------------------------------------------------------------

Table::Table(const string &file_name)
{
	ifstream ifs {file_name};	//Открываем файловый поток ввода
	if(!ifs)		error("Unable to open file '" + file_name + "'");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	
	string line {""};
	int lineno = 0;
	
	//Проверка заголовка
	regex header( "^[\\w ]+(\\s+[\\w ]+)*$");
	while( line.size()==0  &&  getline(ifs,line) )
	{
		++lineno;
		smatch matches;
		if (!regex_search(line, matches, header)  &&  line.size())		error("no header [ Table() constructor ]");
	}
	
	if( ifs.eof()  &&  line.size()==0 )		error("bad file path or empty file [ Table() constructor ]");
	
	one_class cl;
	int total_boys {0};
	int total_girls {0};
	
	//Считывание строк с проверкой сумм в каждой из них
	//"Alle klasser" возвращает eof()
	while( ifs >> cl  &&  !ifs.eof() )
	{
		++lineno;
		school.insert(cl);
		total_boys  += cl.boys;
		total_girls += cl.girls;
	}
	
	if( !ifs.eof() )		error("bad input format in line #" + to_string(lineno+1) + " [ Table() constructor ]");
	if( cl.alpha == "Alle klasser" && (cl.boys != total_boys  ||  cl.girls != total_girls) )
		error("sums for students of one of the sexes do not converge in line #" + to_string(lineno+1) + " [ Table() constructor ]");
}