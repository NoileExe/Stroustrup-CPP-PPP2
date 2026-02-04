

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
struct Class {
	int num;		//Номер класса
	string alpha;	//Буква класса
	int boys;		//Кол-во в классе учеников (мальчиков)
	int girls;		//Кол-во в классе учениц (девочек)
};

//Операторы сравнения для структуры Class
bool operator<(const Class &a, const Class &b);
bool operator>(const Class &a, const Class &b);
bool operator==(const Class &a, const Class &b);
bool operator!=(const Class &a, const Class &b);

//Оператор вывода для структуры Class
ostream& operator<<(ostream &ost, const Class &cl);

//Оператор ввода для структуры Class
istream& operator>>(istream &ist, Class &cl);

//------------------------------------------------------------------------------

using Table_iter = set<Class>::const_iterator;

class Table {
	set<Class> school;
	
public:
	Table(const string &file_name);
	
	Table_iter begin() const { return school.begin(); }
	Table_iter  end()  const { return school.end(); }
};

//Оператор вывода для класса Table
ostream& operator<<(ostream &ost, const Table &tb);