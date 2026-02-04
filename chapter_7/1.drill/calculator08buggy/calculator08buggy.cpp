
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include <yes_or_no.h>
#include <console_encoding.h>

struct Token {
	char kind;
	double value;
	string name;
	
	//Предопределение вида токенов
	Token(char ch) :kind(ch), value(0) { } //для операторов и скобок
	Token(char ch, double val) :kind(ch), value(val) { } //для чисел
	Token(char ch, string n) :kind{ch}, name{n} { } //именованная переменная
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { } //объявление пустого объекта Token_stream

	Token get();
	void unget(Token t) { buffer = t; full = true; }

	void ignore(char);
};

const char let = 'L'; //токен с данным значением применяется для определения новой переменной
const char quit = 'Q'; //токен для немедленного завершения программы
const char print = ';'; //токен для обозначения конца выражения и перехода к вычислениям
const char number = '8'; //данный токен обозначает число
const char variable = 'a'; //токен для определения действий над переменной

Token Token_stream::get() //получаем следующий терм
{
	if (full) { full = false; return buffer; } //если буфер заполнить - вернуть его значение
	char ch;
	cin >> ch;
	switch (ch) {
		case quit:
		case print:
		case '(': case ')': case '+': case '-': case '*':
		case '/': case '%': case '=': //операторы математические и программные
			return Token(ch);
		
		case '#':
			return Token(let);

		case '.': case '0': case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': //числа
		{
			cin.unget();
			double val;
			cin >> val;
			return Token(number, val);
		}
		default:
			if (isalpha(ch)){ //Если символ - буква (имя может начинаться только с буквы
				string s = "";
				s += ch;
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
									   //буква,   цифра или нижнее подчеркивание
					s += ch; //FIRST!!!!
				
				cin.unget(); //возврат каретки на 1 символ назад, т.к. он не имеет отношения к имени
				if (s == "quit") return Token(quit); //SECOND!!!!
				return Token(variable, s);
			}
			error("Bad token");
	}
}

void Token_stream::ignore(char c) //отбросить все символы до указанного
{
	if (full && c == buffer.kind) { //если указанный символ уже в буфере - отбрасываем его
		full = false;
		return;
	}
	full = false; //во всех остальных случаях просто отбрасываем значение и продолжаем его поиск

	char ch;
	while (cin >> ch) //при посимвольном чтении игнорируем все символы вплоть до указанного
		if (ch == c) return; //при посимвольном чтении наткнулись на символ? - 
							  //игнорируем его и завершаем процедуру
}

Token_stream ts; //обеспечивает работу с членами ф-ции get() и unget()


struct Variable { //Структура для представления именованных переменных и констант
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> Mass_names; //вектор для хранения всех именованных переменных и констант
//а так же обращения к ним

double get_value(string s)
//получить значение существующей переменной
//на вход: имя переменной
{
	for (int i = 0; i < Mass_names.size(); ++i)
		if (Mass_names[i].name == s) return Mass_names[i].value;
	error("попытка получить значение необъявленной переменной ", s);
}

void set_value(string s, double d)
//изменить (установить) значение существующей переменной
//на вход: имя переменной и её новое значение
{
	for (int i = 0; i < Mass_names.size(); ++i)
		if (Mass_names[i].name == s) {
			Mass_names[i].value = d;
			return;
		}
	error("попытка установить значение для необъявленной переменной ", s);
}


double expression();

bool is_declared(string s)
//проверка существует ли уже переменная с таким именем
//на вход: имя переменной
{
	for (int i = 0; i < Mass_names.size(); ++i)
		if (Mass_names[i].name == s) return true;
	return false;
}

double declaration()
//проверка на корректность ввода при объявлении переменной;
//добавление не объявленной ранее переменной в массив переменных
{
	Token t = ts.get();
	if (t.kind != 'a') error("ожидалось корректное имя переменной");
	string name = t.name;
	if (is_declared(name)) error(name, " попытка повторного объявления");
	t = ts.get();
	if (t.kind != '=') error("символ = пропущен при объявлении переменной ", name);
	double d = expression();
	Mass_names.push_back(Variable(name, d));
	return d;
}

double primary() //обработка чисел, скобок и переменных
{
	Token t = ts.get();
	switch (t.kind) {
	case '(': //регулирует конструкцию '(' выражение ')'
	{	double d = expression();
	t = ts.get();
	if (t.kind != ')') error("ожидалась ')'"); //THIRD?
	}
	case '-': //Помогает избежать ошибки если первое число в выражении отрицательное
		return -primary();
	case number: //символ '8' обозначает что объект является числом
		return t.value;
	case variable: //символ 'a' обозначает что происходит обращение к переменной
		return get_value(t.name); //получить значение переменной по строке с её именем
	default:
		error("ожидалось первичное выражение");
	}
}

double term() //обработка операторов *, / и %
{
	double left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
		if (d == 0) error("деление на ноль");
		left /= d;
		break;
		}
		
		case '%':
			{
				double d = primary();
				if (d == 0)   error("деление на ноль");
				left = fmod(left,d);
				/* Ф-ция из стандартной библиотеки возвращающая остаток от деления
				даже при делении чисел в дробной частью, например:
					
					6.7 % 3.3 = 6.7 - 3.3 * int(6.7/3.3) = 0.1
				*/
				break;
			}
		default:
			ts.unget(t); //возвращаем t обратно в поток token'ов
			return left;
		}
	}
}

double expression() //обработка операторов + и -
{
	double left = term();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t); //возвращаем t обратно в поток token'ов
			return left;
		}
	}
}


double statement() //Определяем что подал на ввод пользователь - объявление переменной или выражение
{
	Token t = ts.get();
	switch (t.kind) {
	case let: //пользователь хочет объявить переменную
		return declaration();
	default: //пользователь запросил другую операцию (вычисления)
		ts.unget(t); //возвращаем t обратно в поток token'ов
		return expression();
	}
}

void clean_up_mess()
//проигнорировать все символы до символа ';' (вызывается после исключения в calculate)
{
	ts.ignore(print);
}

const string prompt = "> "; //приглашение ко вводу
const string result = "= "; //показывает оторажение результата

void calculate() //все вычисления инициализируются тут
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main() 
try {
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "исключение: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "неизвестное исключение\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}
