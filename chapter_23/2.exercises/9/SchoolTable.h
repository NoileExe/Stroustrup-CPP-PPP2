

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <regex>
#include <iomanip>			//Для возможности форматирования потока вывода


using namespace std;

//------------------------------------------------------------------------------

//Перевод строкового значения в тип T путём строкового потока ввода
template<class T> T from_string(const string& s);

//Данные по количеству учеников отдельно взятого класса
struct one_class {
	int num;		//Номер класса
	string alpha;	//Буква класса
	int boys;		//Кол-во в классе учеников (мальчиков)
	int girls;		//Кол-во в классе учениц (девочек)
};

//Операторы сравнения для структуры one_class
bool operator<(const one_class &a, const one_class &b);
bool operator>(const one_class &a, const one_class &b);
bool operator==(const one_class &a, const one_class &b);
bool operator!=(const one_class &a, const one_class &b);

//Оператор вывода для структуры one_class
ostream& operator<<(ostream &ost, const one_class &cl);

//Оператор ввода для структуры one_class
istream& operator>>(istream &ist, one_class &cl);

//------------------------------------------------------------------------------

using Table_iter = set<one_class>::const_iterator;

class Table {
	set<one_class> school;
	
public:
	Table(const string &file_name);
	
	Table_iter begin() const { return school.begin(); }
	Table_iter  end()  const { return school.end(); }
};