#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

const char NUMBER = '8';		//t.kind == NUMBER означает, что t - число
const char PRINT = '\n';		//t.kind == PRINT означает, что t - лексема для вывода решения
const char POW = '^';			//t.kind == POW означает, что t - оператор возведения в степень

const char CONSTANT = '$';		//токен с данным значением применяется для определения новой константы
const char LET = '#';			//токен с данным значением применяется для определения новой переменной
const char VARIABLE = 'a';		//токен для определения действий над переменной

const string PROMPT = "> ";		//приглашение ко вводу
const string RESULT = "= ";		//для указания на то что за данным текстом следует результат вычислений

const string SQRTKEY = "sqrt";
const char SQRT = 'S';			//t.kind == SQRT означает, что t - оператор извлеч. квадратного корня

const string TABLEOUTKEY = "out";
const char TABLEOUT = 'T';		//t.kind == TABLEOUT означает, что t - лексема для вывода всех переменных и констант

class CTRL_Z_throw { };			//Для вызова исключения при вводе CTRL+Z
const string QUITKEY = "quit";
const char QUIT = 'Q';			//t.kind == QUIT означает, что t - лексема для выхода из программы

const string HELPKEY = "help";
const char HELP = 'H';			//токен с данным значением применяется вызова
extern const string HELP_INSTR;

/*extern const char NUMBER;
extern const char PRINT;
extern const char POW;

extern const char CONSTANT;
extern const char LET;
extern const char VARIABLE;

extern const string PROMPT;
extern const string RESULT;

extern const string SQRTKEY;
extern const char SQRT;

extern const string TABLEOUTKEY;
extern const char TABLEOUT;

class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z, которое приводит к выводу на экран вопроса о выходе
extern const string QUITKEY;
extern const char QUIT;

extern const string HELPKEY;
extern const char HELP;
extern const string HELP_INSTR;*/

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
	Token_stream() :full(0), buffer(0) { }   //создаём Token_stream который читает из потока ввода cin
	Token_stream(istream&);
	//Token_stream(istream& is) :input_Ts{cin} { }
	
	Token get();			//получаем объект Token (член get() определен в другом месте)
	void putback(Token t);	//возврат Token обратно в ф-цию (в буфер)
	void ignore(char c);	//отбрасывает символы до символа 'c' включительно
private:
	bool full;
	Token buffer;			//здесь сохраняем объект класса Token, помещённый обратно,
							// используя putback ()

	//istream& input_Ts;
};