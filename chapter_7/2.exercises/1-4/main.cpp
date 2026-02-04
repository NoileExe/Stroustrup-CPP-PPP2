// calculator01.cpp
/*Так же уже по чистой случайности включает в себя следующие выполненные упражнени:
 * 1-3, 6-8
 * Грамматика указана в прилагаемом файле*/

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

double post_oper(double); //вызывается из pow_proc, factorial, primary
double primary(); //вызывается из pow_proc (возведение в степень)
double expression(); //объявляем, т.к. ф-ция primary() может вызвать expression()


const char NUMBER = '8'; //t.kind == NUMBER означает, что t - число
const char PRINT = ';'; //t.kind == PRINT означает, что t - лексема для вывода решения
const char POW = '^';  //t.kind == POW означает, что t - оператор возведения в степень

const string SQRTKEY = "sqrt";
const char SQRT = 'S'; //t.kind == SQRT означает, что t - оператор извлеч. квадратного корня

const string QUITKEY = "quit";
const char QUIT = 'Q'; //t.kind == QUIT означает, что t - лексема для выхода из программы

const char CONSTANT = '$'; //токен с данным значением применяется для определения новой константы
const char LET = '#'; //токен с данным значением применяется для определения новой переменной
const char VARIABLE = 'a'; //токен для определения действий над переменной

const string PROMPT = "> "; //приглашение ко вводу
const string RESULT = "= "; //для указания на то что за данным текстом следует результат вычислений

const string HELPKEY = "help";
const char HELP = 'H'; //токен с данным значением применяется вызова
const string HELP_INSTR = "\n\n\nВводите выражения в формате: ЧИСЛО ОПЕРАТОР ЧИСЛО ТОЧКА_С_ЗАПЯТОЙ."
			"\n\nДоступные операции:\n\n"
			"-----------------------------------------------------\n"
			"|    +    |    -    |     *     |    /    |    %    |\n"
			"|---------+---------+-----------+---------+---------|\n"
			"|         |         |           |         | остаток |\n"
			"| сложить | отнять  |  умножить |  делить |   от    |\n"
			"|         |         |           |         | деления |\n"
			"-----------------------------------------------------\n"
			
			"------------------------------------------------------\n"
			"|   ()   |   {()}   |    ^    |   ЧИСЛО!  |  sqrt()  |\n"
			"|--------+----------+---------+-----------+----------|\n"
			"|        |вложенные |возвести |           |квадратный|\n"
			"| скобки |  скобки  |    в    | факториал |  корень  |\n"
			"|        |          | степень |           | из числа |\n"
			"------------------------------------------------------\n"
			
			"\nПример:\n> -2+(2*2); \n= 2\n\n"
			
			"Дополнительные операции:\n"
			"sqrt(ЧИСЛО или ВЫРАЖЕНИЕ) - квадратный корень из числа\n"
			
			"В программе предусмотренны следующие неизменяемые значения, т.е. "
			"константы (число Пи, число e и множитель тысяча):\n pi = 3.1415926535"
			"\n e = 2.7182818284\n k = 1000\n\n"
			
			"Имеется также возможность объявлять и применять свои переменные "
			"и константы (задается единожды без возможности изменения).\n"
			"Имя должно начинаться с буквы, может содержать буквы, цифры и символ '_'."
			"\nПример объявления переменной:\n> #var1=5+.79; \n= 5.79\n"
			"\nПример объявления константы:\n> $ con_1 = 10; \n= 10\n"
			"\nПример применения:\n> var1-2;; \n= 3.79\n\n"
			
			"help - вызов справки\nquit - для быстрого выхода\n\n\n"; //ИНСТРУКЦИИ

//------------------------------------------------------------------------------

class Token {
public:
	char kind;		//что за символ
	double value;	 //для чисел: значение
	string name;	  //для переменных: имя
	
	Token(char ch)				 //объект класса Token из символа
		:kind(ch), value(0) { }
	Token(char ch, double val)	 //объект класса Token из символа и числа double
		:kind(ch), value(val) { }
	Token(char ch, string n)
		:kind{ch}, name{n}, value(0) { }	 //именованная переменная
};

//------------------------------------------------------------------------------

class Token_stream {
public:
	Token_stream() :full(0), buffer(0) { }   //создаём Token_stream, который читает из потока ввода cin лексемы
	
	Token get();	  //получаем объект Token (член get() определен в другом месте)
	void putback(Token t); //возврат Token обратно в ф-цию (в буфер)
	void ignore(char c); //отбрасывает символы из потока ввода cin до символа 'c' включительно
private:
	bool full;
	Token buffer;	 //здесь сохраняем объект класса Token, помещённый обратно,
														// используя putback ()
};

void Token_stream::ignore(char c)
//Символ 'c' представляет разновидность лексем
//отбрасывает все символы до указанного на входе в функцию (включая его самого), ничего не возвращает
{
	//Сначала проверяем буфер
	if (Token_stream::full && c == Token_stream::buffer.kind)
	{
		Token_stream::full = false;
		return;
	}
	
	//Затем проверяем входные данные
	Token_stream::full = false;
	char ch = 0;
	while (cin.get(ch))
		if (ch == c || ch == '\n') return; // || ch == '\n'
}

//Член putback() помещает аргумент в буфер своей ф-ции Token_stream:
void Token_stream::putback(Token t)
{
	if (Token_stream::full)
		error("Ошибка ф-ции putback(): попытка заполнить уже полный буфер");

	Token_stream::buffer = t;	//копировать t в буфер
	Token_stream::full = true;	//теперь буфер полон
}

Token Token_stream::get()
{
	if (Token_stream::full == true) { //Если в буфере уже имеется объект типа Token..
		//..удаляем его из буфера (помечаем буфер как пустой, т.е. доступный для перезаписи)
		// и возвращаем объект из буфера
		Token_stream::full = false;
		return Token_stream::buffer;
	}

	char ch;
	cin >> ch;	//замечание: оператор >> пропускает пустые пространства
				 //(пробел, символ новой строки, табуляция и т.д.)

	if (cin.eof())   error ("CTRL+Z"); //Закрыть программу? Да или Нет (д / н)

	switch (ch)
	{
		case PRINT: //для завершения вычислений и немедленного вывода ответа на экран
		case LET: case CONSTANT: case '=':
		case POW:
		case '!':
		case '(': case ')':
		case '{': case '}':
		case '+': case '-': case '*': case '/': case '%':
			return Token(ch);		//Каждый символ представляет сам себя
		
		case '.': //Число с плавающей зпт может начинаться с точки
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			cin.putback(ch);		 //возвращаем символ обратно в потом ввода
			double val;
			cin >> val;			  //считываем число с плавающей ЗПТ
			return Token(NUMBER, val);   //помечаем объект символом '8' означающим "число"

		default:
		{
			string str = "";
			
			if (isalpha(ch)){ //Если первый символ - буква (имя может начинаться только с буквы)
				str += ch;
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
									   //буква,   цифра или нижнее подчеркивание
					str += ch;
				
				cin.putback(ch); //возврат каретки на 1 символ назад, т.к. он не имеет отношения к имени
				
				if (str == HELPKEY) return Token(HELP);
				else if (str == QUITKEY) return Token(QUIT);
				else if (str == SQRTKEY) return Token(SQRT);
				
				return Token(VARIABLE, str);
			}
			
			cin.clear();
			error ("недопустимый ввод ( Token_stream::get() )");
		}
	}
}

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
	Symbol_table() { }   //создаём Symbol_table, который читает из потока ввода cin лексемы
	
	double get(string s);			//получить значение существующей переменной
	void set(string s, double d);	//изменить (установить) значение существующей переменной
	bool is_declared(string s);		//проверка существует ли уже переменная с таким именем
	void define(string name, double d, bool cnst);	//добавление не объявленной ранее переменной/константы в массив переменных
private:
	vector<Variable> vector_names;
	//вектор для хранения всех именованных переменных и констант, а так же обращения к ним
};

double Symbol_table::get(string s)
//получить значение существующей переменной
//на вход: имя переменной
//на выходе: значение переменной с указанным именем (если таковая существует)
{
	for (int i = 0; i < Symbol_table::vector_names.size(); ++i)
		if (Symbol_table::vector_names[i].name == s) return Symbol_table::vector_names[i].value;
	
	error ("попытка получить значение необъявленной переменной ( Symbol_table::get() )");
}

void Symbol_table::set(string s, double d)
//изменить (установить) значение существующей переменной
//на вход: имя переменной и её новое значение
{
	for (int i = 0; i < Symbol_table::vector_names.size(); ++i)
		if ( Symbol_table::vector_names[i].constant && Symbol_table::vector_names[i].name == s )
			error ("попытка изменить константу ( Symbol_table::set() )");
		
		else if (Symbol_table::vector_names[i].name == s) {
			Symbol_table::vector_names[i].value = d;
			return;
		}
	
	error ("попытка установить значение для необъявленной переменной ( Symbol_table::set() )");
}

bool Symbol_table::is_declared(string s)
//проверка существует ли уже переменная с таким именем
//на вход: имя переменной
//на выходе: true - если переменная с таким именем существует / false - если нет
{
	for (int i = 0; i < Symbol_table::vector_names.size(); ++i)
		if (Symbol_table::vector_names[i].name == s)	return true;
	
	return false;
}

void Symbol_table::define(string name, double d, bool cnst)
//добавление не объявленной ранее переменной/константы в массив переменных
//на вход: имя несуществующей переменной, её значение и яв-ся ли она константой или нет (true - если да)
{
	//Если такой переменной/константы ещё не существует в массиве
	if ( Symbol_table::is_declared(name) == false )
		Symbol_table::vector_names.push_back(Variable(name, d, cnst));
	
	else
		error ("попытка объявления уже существующей переменной ( Symbol_table::define() )");
}

//------------------------------------------------------------------------------

Token_stream ts; //обеспечивает работу с членами ф-ции ignore(), get() и putback()
Symbol_table var_table; //обеспечивает работу с переменными и константами

//------------------------------------------------------------------------------

double pow_proc(double num)
//возведение входящего числа в степень, возвращает таковых р-тат вычислений
//либо вызывает исключение  
{
	double pow_num = primary();
	
	//pow_num < -323 - будет равно 0, при -323 и больше до -318 - значение искажается
	if ( pow_num > 308 || pow_num < -323 )
		error ("при возведении в степень число выходит за диапазон DOUBLE ( pow_proc() )");
	else if (pow_num != int(pow_num))
		error ("значение степени должно быть ЦЕЛЫМ числом ( pow_proc() )");
	
	pow_num = pow(num,pow_num);
	
	if ( isinf(pow_num) )
		error ("при возведении в степень число выходит за диапазон DOUBLE ( pow_proc() )");
	
	return post_oper(pow_num); //проверка правильности выражения
	/*На самом деле тут кроется проблема при вводе например 2 ^2 ^2+1 - т.е. при вычислении самой степени выражение
	 * указывающее степень требуется закрывать в скобки иначе указанное выше будет восприниматься прямолинейно:
	 * 2 ^2 ^2+1 == ( (2^2)^2 ) + 1*/
}



double factorial(double num) //Вычисление факториала. На вход только целые положит. числа
{
	if (num - int(num) != 0)
		error ("факториал должен быть от ЦЕЛОГО числа ( factorial() )");
	
	else if (num == 0) return 1;	 //Факториал нуля равен единице
	
	else if (num < 0)
		error ("факториал должен быть от ПОЛОЖИТЕЛЬНОГО числа ( factorial() )");
	
	
	double answer = 1;
	for (double i = 1; i <= num; ++i)
	{
		answer *= i;
		
		//Если при вычислении факториала ответ равен inf или -inf (+-бесконечность)
		if ( isinf(answer) )
			 error ("при вычислении факториала число выходит за диапазон DOUBLE ( factorial() )");
	}
	
	 //проверка правильности выражения, т.к. за факториалом может стоять ещё выражение, оператор или символ
	return post_oper(answer);
}



double post_oper(double left)
//проверяет идёт ли дальше какой-либо оператор, т.е. завершено ли выражение
//Если всё верно, просто возвращаем лексему как есть, иначе вызываем исключение
//При необходимости вычисляется факториал или происходит возведение в степень
{
	Token t = ts.get();
	//char ch;
	//cin >> ch;
	
	switch (t.kind)
	//switch (ch)
	{
		case POW: //символ '^' обозначает что происходит возведение в степень
			return pow_proc(left); //Пробуем возвести в степень
		
		case '!': //символ '!' обозначает что происходит вычисление факториала
			return factorial(left); //Пробуем вычислить факториал числа
		
		case PRINT:
		case ')': case '}': case '+': case '-': case '*': case '/': case '%':
			cin.putback(t.kind);
			//ts.putback(t); //Возвращаем символ в поток токенов, иначе потеряется
			return left;
			
		default:
			error ("ожидался оператор (;, +, -, *, /, %, !, ^) ( post_oper() )");
	}
}

//------------------------------------------------------------------------------

//обработка чисел, двух видов скобок и факториала
double primary()
{
	Token t = ts.get();
	
	switch (t.kind)
	{
		case '(':	//регулирует конструкцию '(' выражение ')'
		{
			double d = expression();
			t = ts.get();

			if (t.kind != ')')
				error ("ожидалась закрывающая скобка - ')' ( primary() )");
			
			return post_oper(d);
		}
		
		case '{':	//регулирует конструкцию '{' '(' выражение ')' '}'
		{
			string str = " ";
			getline(cin, str);
			cin.clear();
			
			//Поиск круглой открывающей скобки внутри фигурных
			//(наличие закрывающей проверяет primary() через вызов 'double d = expression();')
			for (int i = 0; i < str.size(); ++i) {
				if (str[i] == '(')
					break;
				else if (i == str.size()-1)
					error ("ожидалось выражение в '(' и ')' внутри выражения в '{' и '}' ( primary() )");
			}
			
			//Начиная с конца возвращаем всю строку в поток ввода
			for (int i = str.size()-1; i >= 0; --i)
				cin.putback(str[i]); 
			
			double d = expression();
			t = ts.get();

			if (t.kind != '}')
				error ("ожидалась закрывающая скобка - '}' ( primary() )");
			
			return post_oper(d);
		}
		
		case NUMBER:			//символ '8' обозначает что объект является числом
		{
			double d = t.value; //получаем само число
			return post_oper(d);
		}
		
		case '-': //Помогает избежать ошибки если первое число в выражении отрицательное
			return post_oper(- primary());
		case '+':
			return post_oper(primary());
		
		case SQRT:
		{
			t = ts.get();
			if (t.kind != '(')
				error ("после оператора 'sqrt' ожидалась открывающая скобка - '(' ( primary() )");
			
			double d = expression(); //получаем конечное число в скобках
			if (d < 0)
				error ("корень должен быть из ПОЛОЖИТЕЛЬНОГО числа ( primary() )");
			
			t = ts.get();
			if (t.kind != ')')
				error ("ожидалась закрывающая скобка - ')' ( primary() )");
			
			return post_oper(sqrt(d));
		}
		
		case VARIABLE: { //символ 'a' обозначает что происходит обращение к переменной
			string strname = t.name;
			
			t = ts.get();
			if (t.kind == '=') {//Если изменение значения переменной
				double d = expression(); //получаем новое значение
				
				//пытаемся изменить значение (ошибка если нет такой переменной или если это константа)
				var_table.set(strname, d);
				return d;
			}
			
			else { //получить значение переменной по строке с её именем для использования в вычислениях
				ts.putback(t);
				return post_oper(var_table.get(strname));
			}
		}
		
		default:
			error ("ожидалось первичное выражение ( primary() )");
	}
}

//------------------------------------------------------------------------------

//обработка операторов *, / и %
double term()
{
	double left = primary(); //считываем и вычисляем первичное_выражение

	while (true) {
		Token t = ts.get();  //получаем след. объект token из потока token'ов
		switch (t.kind)
		{
			case '*':
				left *= primary(); //вычисляем первичное_выражение и умножаем
				break;
			case '/':
			{
				double d = primary();
				if (d == 0)		error ("деление на нуль ( term() )");
				
				left /= d; //вычисляем первичное_выражение и делим
				break;
			}
			case '%':
			{
				double d = primary();
				if (d == 0)		error ("деление на нуль ( term() )");
				
				left = fmod(left,d);
				/* Ф-ция из стандартной библиотеки возвращающая остаток от деления
				даже при делении чисел в дробной частью, например:
					6.7 % 3.3 = 6.7 - 3.3 * int(6.7/3.3) = 0.1
				*/
				break;
			}
			
			default:
				ts.putback(t);	 //возвращаем t обратно в поток token'ов
				return left;
		}
	}
}

//------------------------------------------------------------------------------

//обработка операторов + и -
double expression()
{
	double left = term();	  //считываем и вычисляем Term

	while (true) {
		Token t = ts.get();   //получаем след. объект Token из потока Token'ов
		switch (t.kind)
		{
			case '+':
				left += term();	//вычисляем Term и прибавляем
				break;
			case '-':
				left -= term();	//вычисляем Term и отнимаем
				break;
			
			default:
				ts.putback(t);	 //возвращаем t обратно в поток token'ов
				return left;	   //наконец: больше нет + или -: возвращаем ответ
		}
	}
}

//------------------------------------------------------------------------------

double declaration(bool cnst)
//проверка на корректность ввода при объявлении переменной;
//добавление не объявленной ранее переменной в массив переменных
//На вход - является ли переменная константой (true если да)
{
	Token t = ts.get();
	
	if (t.kind != 'a')
		error ("ожидалось корректное имя переменной/константы ( declaration() )");
	
	else if (t.name == HELPKEY || t.name == QUITKEY || t.name == SQRTKEY)
		error ("имя переменной/константы не может совпадать с именем команд программы  ( declaration() )");
	
	else if (var_table.is_declared(t.name))
		error ("попытка повторного объявления переменной/константы ( declaration() )");
	
	
	string name = t.name;
	
	t = ts.get();
	if (t.kind != '=')
		error ("при объявлении переменной пропущен символ '=' ( declaration() )");
	
	double d = expression();
	var_table.define(name, d, cnst);
	
	return d;
}

//Определяем что подал на ввод пользователь - 
//объявление переменной, константы или выражение
double statement()
{
	Token t = ts.get();
	switch (t.kind) {
		case LET: //пользователь хочет объявить переменную
			return declaration(false);
			
		 case CONSTANT: //пользователь хочет объявить константу
			return declaration(true);
			
		default: //пользователь запросил другую операцию (вычисления)
			ts.putback(t); //возвращаем t обратно в поток token'ов
			return expression();
	}
}

void calculate() //Цикл вычисления выражения
{
	while (cin)
	try 
	{
		cout << PROMPT;
		Token t = ts.get();
		
		while (t.kind == PRINT)		t = ts.get();
		
		//Если введено 'quit' - немедленный выход из программы
		if (t.kind == QUIT) return;
		
		//Вызывается исключение в ф-ции calculate() выводящее инструкцию и вновь запускающее расчёты
		else if (t.kind == HELP)	error (HELPKEY);
		
		ts.putback(t);
		cout << RESULT << statement() << "\n\n"; //endl
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		string str = e.what();
		
		//При вводе CTRL+Z вызывается исключение в main(), которое в свое время приводит к 
		//вопросу хочет ли пользователь закрыть программу
		if ( str == "CTRL+Z" )		error(str);
		
		else if ( str == HELPKEY ) {
			getline(cin, str);
			cin.clear();
			cerr << HELP_INSTR; //ИНСТРУКЦИИ
		}
		
		else
			cerr << "Ошибка ( calculate() ): " << str << "\n\n";
		
		cin.clear();
		ts.ignore(PRINT);
	}
}

//------------------------------------------------------------------------------

int main()
try
{
	cout << "Добро пожаловать в программу калькулятор 2022 по Бьярне Страуструпу.\n\n"
			"После знака '>' вводите выражение в форме: ЧИСЛО ОПЕРАТОР ЧИСЛО ТОЧКА_С_ЗАПЯТОЙ.\n"
			"Для завершения ввода (подтверждения) нажмите клавишу ENTER.\n\n"
			"Последний (точка с запятой ';') - используется для завершения выраж"
			"ения и произведения вычисления. ВНИМАНИЕ! Если вы не введёте точку "
			"с запятой вы не получите результата вычислений.\n\nЧисла могут быт"
			"ь с любым знаком, целыми и с десятичной частью (ТОЧКА - десятичный"
			" разделитель).\n\n"; //ПРИВЕТСТВИЕ
	
	var_table.define("pi", 3.1415926535, true);
	var_table.define("e", 2.7182818284, true);
	var_table.define("k", 1000, true);
	
	calculate();
	
	keep_window_open("~~");
	return 0;
}

catch (exception& e) { //Для системных исключений при работе с программой
	string str;
	getline(cin, str);
	cin.clear();
	
	str = e.what();

	if ( str != "CTRL+Z" )
		cerr << "Ошибка ( main() ): " << e.what() << '\n';
	
	if (Y_or_N("Закрыть программу?"))	return 1000; //1
	else								calculate();
}

catch (...) { //Для непредвиденных исключений
	cerr << "Упс! Неизвестное исключение!\n";
	
	if (Y_or_N("Закрыть программу?"))	return 1002; //4
	else								calculate();
}

//------------------------------------------------------------------------------
