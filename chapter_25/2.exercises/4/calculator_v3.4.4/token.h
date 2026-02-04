
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <vector>
#include <fstream>		//Для файлового потока ввода-вывода
#include <bitset>

//------------------------------------------------------------------------------

using namespace std;

//------------------------------------------------------------------------------

const char NUMBER = '8';		//t.kind == NUMBER означает, что t - число
const char PRINT = '\n';		//t.kind == PRINT означает, что t - лексема для вывода решения

const char CONSTANT = '$';		//токен с данным значением применяется для определения новой константы
const char LET = '#';			//токен с данным значением применяется для определения новой переменной
const char VARIABLE = 'a';		//токен для определения действий над переменной


const string CHANGEINPUTKEY = "from";
const char CHANGEINPUT = 'I';	//токен для обозначения смены потока ввода

const string CHANGEOUTPUTKEY = "to";
const char CHANGEOUTPUT = 'O';	//токен для обозначения смены потока вывода


const string PROMPT = "> ";	//приглашение ко вводу
const string RESULT = "= ";	//для указания на то что за данным текстом следует результат вычислений

const string POWKEY = "pow";
const char POW = 'P';			//t.kind == POW означает, что t - оператор возведения в степень

const string SQRTKEY = "sqrt";
const char SQRT = 'S';			//t.kind == SQRT означает, что t - оператор извлеч. квадратного корня

const string TABLEOUTKEY = "out";
const char TABLEOUT = 'T';		//t.kind == TABLEOUT означает, что t - лексема для вывода всех переменных и констант

const string QUITKEY = "quit";
const char QUIT = 'Q';			//t.kind == QUIT означает, что t - лексема для выхода из программы

const string HELPKEY = "help";
const char HELP = 'H';			//токен с данным значением применяется вызова
extern const string HELP_INSTR;

//------------------------------------------------------------------------------

struct Variable { //Структура для представления именованных переменных и констант
	string name;
	double value;
	bool constant;
	
	Variable(string n, double v)
		:name(n), value(v), constant(false)	{ }
	Variable(string n, double v, bool c)
		:name{n}, value{v}, constant{c}		{ }
};


class Symbol_table {
public:
	Symbol_table() { }		//создаём Symbol_table, который читает из потока ввода cin лексемы
	
	void table_out();				//Вывод на экран всех констант и переменных
	double get(string s);			//получить значение существующей переменной
	void set(string s, double d);	//изменить (установить) значение существующей переменной
	bool is_declared(string s);		//проверка существует ли уже переменная с таким именем
	void define(string name, double d, bool cnst);	//добавление не объявленной ранее переменной/константы в массив переменных
private:
	vector<Variable> vector_names;
	//вектор для хранения всех именованных переменных и констант, а так же обращения к ним
};

//------------------------------------------------------------------------------

class Token {
public:
	char kind;			//что за символ
	double value;		//для чисел: значение
	string name;		//для переменных: имя
	
	Token(char ch)					//объект класса Token из символа
		:kind(ch), value(0) { }
	Token(char ch, double val)		//объект класса Token из символа и числа double
		:kind(ch), value(val) { }
	Token(char ch, string n)
		:kind{ch}, name{n} { }		//именованная переменная
};

//------------------------------------------------------------------------------

class Token_stream {
public:
	Token_stream() :full(0), buffer(0), ist(cin) { }				//создаём Token_stream, который читает из потока ввода cin
	Token_stream(istream& is) :full(0), buffer(0), ist(is) { };		//Создаём Token_stream, читающий лексемы из указанного в аргументе потока ввода
	
	Token get();			//получаем объект Token (член get() определен в другом месте)
	void putback(Token t);	//возврат Token обратно в ф-цию (в буфер)
	void ignore(char c);	//отбрасывает символы до символа 'c' включительно
private:
	bool full;
	Token buffer;		//здесь сохраняем объект класса Token, помещённый обратно, используя putback ()
	istream& ist;
};