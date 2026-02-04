#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

const char NUMBER = '8';			//t.kind == NUMBER означает, что t - число
const char PRINT = '\n';			//t.kind == PRINT означает, что t - лексема для вывода решения
const char POW = '^';				//t.kind == POW означает, что t - оператор возведения в степень

const char CONSTANT = '$';			//токен с данным значением применяется для определения новой константы
const char LET = '#';				//токен с данным значением применяется для определения новой переменной
const char VARIABLE = 'a';			//токен для определения действий над переменной


const string CHANGEINPUTKEY = "from";
const char CHANGEINPUT = 'I';		//токен для обозначения смены потока ввода

const string CHANGEOUTPUTKEY = "to";
const char CHANGEOUTPUT = 'O';		//токен для обозначения смены потока вывода


const string PROMPT = "> ";		//приглашение ко вводу
const string RESULT = "= ";		//для указания на то что за данным текстом следует результат вычислений

const string SQRTKEY = "sqrt";
const char SQRT = 'S';				//t.kind == SQRT означает, что t - оператор извлеч. квадратного корня

const string TABLEOUTKEY = "out";
const char TABLEOUT = 'T';			//t.kind == TABLEOUT означает, что t - лексема для вывода всех переменных и констант

const string QUITKEY = "quit";
const char QUIT = 'Q';				//t.kind == QUIT означает, что t - лексема для выхода из программы

const string HELPKEY = "help";
const char HELP = 'H';				//токен с данным значением применяется вызова
extern const string HELP_INSTR;

const char EWARNING = 'E';		//обозначает ошибку

//------------------------------------------------------------------------------

class Token {
public:
	char kind;		//что за символ
	double value;	//для чисел: значение
	string name;	//для переменных: имя
	
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
	Token buffer;		//здесь сохраняем объект класса Token, помещённый обратно,
															// используя putback ()
	istream& ist;
};