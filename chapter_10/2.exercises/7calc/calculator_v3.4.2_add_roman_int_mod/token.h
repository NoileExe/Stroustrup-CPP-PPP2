#include <std_lib_facilities.h>



//--------------------------------------------- Строка <-> Число ---------------------------------------------

							  // 1    5    10    50    100   500   1000
const vector<char> primitives { 'I', 'V',  'X',  'L',  'C',  'D',  'M' };

bool check_primitives (char);	//Поиск примитива в векторе primitives. Если примитив присутсвует возвращает true

int term2int(string);			//Перевод составной части (терма) римского числа из строкового представления в целочисленное
string int2term(int);			//Перевод целого числа в терм

string int2romanstr(int);		//Перевод из int в строковое представление римского числа
int romanstr2int(string);		//Перевод строкового представления римского числа в int, так же проверка корректности строки

//--------------------------------------------- Строка <-> Число ---------------------------------------------


class Roman_int {
public:
	Roman_int(int n);			//Проверка корректности и инициализация арабским числом
	Roman_int(string n);		//Проверка корректности и инициализация строкой с римским числом
	Roman_int();				//Конструктор по умолчанию
	
	
	//Перевод из Roman_int в int
	int as_int() const { return num; }

private:
	int num;		//римское представление числа разбитое последовательно на составные части
};


//<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>> Ввод/Вывод <<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>
ostream& operator<<(ostream& ost, const Roman_int& ri);
istream& operator>>(istream& is, Roman_int& ri);
//<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>> Ввод/Вывод <<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>


//==!===!===!===!===!===!===!===!===!===!===!===!= Сравнение ==!===!===!===!===!===!===!===!===!===!===!===!=
bool operator==(const Roman_int& a, const Roman_int& b);
bool operator!=(const Roman_int& a, const Roman_int& b);
//==!===!===!===!===!===!===!===!===!===!===!===!= Сравнение ==!===!===!===!===!===!===!===!===!===!===!===!=


//+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/% Математические операции +-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%
Roman_int operator+(const Roman_int& a, const Roman_int& b);	//сложение (Roman_int+Roman_int)
Roman_int operator-(const Roman_int& a, const Roman_int& b);	//вычитание (Roman_int-Roman_int)
Roman_int operator*(const Roman_int& a, const Roman_int& b);	// Roman_int*Roman_int
Roman_int operator/(const Roman_int& a, const Roman_int& b);	// Roman_int/Roman_int
Roman_int operator%(const Roman_int& a, const Roman_int& b);	// Roman_int%Roman_int
//+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/% Математические операции +-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


const char NUMBER = '8';	//t.kind == NUMBER означает, что t - число
const char PRINT = '\n';	//t.kind == PRINT означает, что t - лексема для вывода решения
const char POW = '^';		//t.kind == POW означает, что t - оператор возведения в степень

const char CONSTANT = '$';	//токен с данным значением применяется для определения новой константы
const char LET = '#';		//токен с данным значением применяется для определения новой переменной
const char VARIABLE = 'a';	//токен для определения действий над переменной

const string PROMPT = "> ";	//приглашение ко вводу
const string RESULT = "= ";	//для указания на то что за данным текстом следует результат вычислений

const string SQRTKEY = "sqrt";
const char SQRT = 'S';		//t.kind == SQRT означает, что t - оператор извлеч. квадратного корня

const string TABLEOUTKEY = "out";
const char TABLEOUT = 'T';	//t.kind == TABLEOUT означает, что t - лексема для вывода всех переменных и констант

class CTRL_Z_throw { };		//Для вызова исключения при вводе CTRL+Z
const string QUITKEY = "quit";
const char QUIT = 'Q';		//t.kind == QUIT означает, что t - лексема для выхода из программы

const string HELPKEY = "help";
const char HELP = 'H';		//токен с данным значением применяется вызова
extern const string HELP_INSTR;

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
	Token_stream() :full(0), buffer(0) { }	//создаём Token_stream который читает из потока ввода cin
	Token_stream(istream&);
	//Token_stream(istream& is) :input_Ts{cin} { }
	
	Token get();			//получаем объект Token (член get() определен в другом месте)
	void putback(Token t);	//возврат Token обратно в ф-цию (в буфер)
	void ignore(char c);	//отбрасывает символы до символа 'c' включительно
private:
	bool full;
	Token buffer;		//здесь сохраняем объект класса Token, помещённый обратно,
						// используя putback ()

	//istream& input_Ts;
};