// calculator01.cpp
//Только целые числа (константы, переменные могут быть проинициализированы в коде нецелыми значениями)
//Незначительно изменена только ф-ция statement() и приветствие/инструкция
//Альтернативный вариант в ф-ции calculate() позволяет вводить нецелые значения, но рез-т обязан быть целым

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
const char PRINT = '\n'; //t.kind == PRINT означает, что t - лексема для вывода решения
const char POW = '^'; //t.kind == POW означает, что t - оператор возведения в степень

const char CONSTANT = '$'; //токен с данным значением применяется для определения новой константы
const char LET = '#'; //токен с данным значением применяется для определения новой переменной
const char VARIABLE = 'a'; //токен для определения действий над переменной

const string PROMPT = "> "; //приглашение ко вводу
const string RESULT = "= "; //для указания на то что за данным текстом следует результат вычислений

const string SQRTKEY = "sqrt";
const char SQRT = 'S';
//t.kind == SQRT означает, что t - оператор извлеч. квадратного корня

const string TABLEOUTKEY = "out";
const char TABLEOUT = 'T';
//t.kind == TABLEOUT означает, что t - лексема для вывода всех переменных и констант

const string QUITKEY = "quit";
const char QUIT = 'Q';
//t.kind == QUIT означает, что t - лексема для выхода из программы

const string HELPKEY = "help";
const char HELP = 'H'; //токен с данным значением применяется вызова
const string HELP_INSTR = "\n\nВводите выражения в формате: ЧИСЛО ОПЕРАТОР ЧИСЛО."
			"\nЧисла могут быть с любым знаком, но обязательно ЦЕЛЫМИ."
			"Для завершения ввода (подтверждения) нажмите клавишу ENTER.\n\n"
			
			"Доступные операции:\n\n"
			"-----------------------------------------------------\n"
			"|    +    |    -    |     *     |    /    |    %    |\n"
			"|---------+---------+-----------+---------+---------|\n"
			"|         |         |           |         | остаток |\n"
			"| сложить | отнять  |  умножить |  делить |   от    |\n"
			"|         |         |           |         | деления |\n"
			"-----------------------------------------------------\n"
			
			"------------------------------------------------------------\n"
			"|   ()   |   {()}    |    ^     |   ЧИСЛО!  |  sqrt(ЧИСЛО) |\n"
			"|--------+-----------+----------+-----------+--------------|\n"
			"|        | вложенные | возвести |           |  квадратный  |\n"
			"| скобки |   скобки  |    в     | факториал |    корень    |\n"
			"|        |           | степень  |           |   из числа   |\n"
			"------------------------------------------------------------\n"
			
			"\nПример:\n> -2+(2*2) \n= 2\n\n"
			
			"В программе предусмотренны следующие константы (число Пи, число e и "
			"множитель тысяча):\n k = 1000\n\n"
			
			"Имеется также возможность объявлять и применять свои переменные (#) "
			"и константы ($), которые задаются единожды без возможности изменения. "
			"Имя должно начинаться с буквы, может содержать буквы, цифры и символ '_'."
			"\nПример объявления переменной:\n> #var1=100 \n= 100\n"
			"\nПример изменения переменной:\n> #var1 =5 \n= 5\n"
			"\nПример объявления константы:\n> $ con_1 = 10 \n= 10\n"
			"\nПример применения:\n> var1-2 \n= 3\n\n"
			"   out - вывод всех констант и переменных в памяти программы\n"
			"   help - вызов справки\n   quit - для быстрого выхода\n\n"; //ИНСТРУКЦИИ

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
		:kind{ch}, name{n} { }	 //именованная переменная
};

//------------------------------------------------------------------------------

class Token_stream {
public:
	Token_stream() :full(0), buffer(0) { }   //создаём Token_stream который читает из потока ввода cin
	
	Token get();	  //получаем объект Token (член get() определен в другом месте)
	void putback(Token t); //возврат Token обратно в ф-цию (в буфер)
	void ignore(char c); //отбрасывает символы до символа 'c' включительно
private:
	bool full;
	Token buffer;	 //здесь сохраняем объект класса Token, помещённый обратно,
														// используя putback ()
};

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
//Символ 'c' представляет разновидность лексем
//отбросывает все символы до указанного на входе в функцию, ничего не возвращает
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
	while (cin >> ch)
		if (ch == c || ch == '\n') return;  // || ch == '\n'
}

//Член putback() помещает аргумент в буфер своей ф-ции Token_stream:
void Token_stream::putback(Token t)
{
	if (Token_stream::full)
		error("Ошибка ф-ции putback(): попытка заполнить уже полный буфер");

	Token_stream::buffer = t;	   //копировать t в буфер
	Token_stream::full = true;	  //теперь буфер полон
}

Token Token_stream::get()
{
	 if (Token_stream::full) { //Если в буфере уже имеется объект типа Token..
		//..удаляем его из буфера (помечаем буфер как пустой, т.е. доступный для перезаписи)
		Token_stream::full = false;
		return Token_stream::buffer;
	}

	char ch = ' ';
	cin.get(ch); //Съедаем пробелы while ( isspace(ch) && ch != PRINT && !cin.eof() ) 
	
	if (cin.eof())   error ("CTRL+Z"); //Закрыть программу? Да или Нет (д / н)
	
	else if (ch == PRINT) return Token(PRINT); //для завершения вычислений и немедленного вывода ответа на экран
	cin.unget();
	
	cin >> ch;	//замечание: оператор >> пропускает пустые пространства
				  //(пробел, символ новой строки, табуляция и т.д.)
	switch (ch)
	{
		case LET: case CONSTANT: case '=': //переменные и константы
		case POW: //степень
		case '!': //факториал
		case '(': case ')':
		case '{': case '}':
		case '+': case '-': case '*': case '/': case '%':
			return Token(ch);		//Каждый символ представляет сам себя
		
		case '.': //Число с плавающей зпт может начинаться с точки
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			cin.unget(); //возврат каретки на 1 символ назад
			double val;
			cin >> val;		//считываем число с плавающей ЗПТ
			
			//if ( ch == '.' && val == 0 )	error ("недопустимый ввод ( Token_stream::get() )");
			
			return Token(NUMBER, val);	//помечаем объект символом '8' означающим "число"
		
		default:
		{
			string str = "";
			
			if ( isalpha(ch) ){ //Если первый символ - буква (имя может начинаться только с буквы)
				str += ch;
				
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
									   //буква,		  цифра	или нижнее подчеркивание
					str += ch;
				
				cin.unget(); //возврат каретки на 1 символ назад, т.к. он не имеет отношения к имени
				
				if (str == HELPKEY)				return Token(HELP);
				else if (str == QUITKEY)		return Token(QUIT);
				else if (str == SQRTKEY)		return Token(SQRT);
				else if (str == TABLEOUTKEY)	return Token(TABLEOUT);
				
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
	
	void table_out();				//Вывод на экран всех констант и переменных
	double get(string s);			//получить значение существующей переменной
	void set(string s, double d);	//изменить (установить) значение существующей переменной
	bool is_declared(string s);		//проверка существует ли уже переменная с таким именем
	void define(string name, double d, bool cnst);	//добавление не объявленной ранее переменной/константы в массив переменных
private:
	vector<Variable> vector_names;
	//вектор для хранения всех именованных переменных и констант, а так же обращения к ним
};

void Symbol_table::table_out() //Вывод на экран всех констант и переменных подряд
{
	for (int i = 0; i < vector_names.size(); ++i) {
		cout << '\t' << i+1 << ". "; 
		
		if (vector_names[i].constant)		cout << "const " << CONSTANT;
		else								cout << "var   " << LET;
		
		cout << ' ' << vector_names[i].name << " = " << vector_names[i].value << ";\n";
	}
}

double Symbol_table::get(string s)
//получить значение существующей переменной
//на вход: имя переменной
//на выходе: значение переменной с указанным именем (если таковая существует)
{
	for (int i = 0; i < vector_names.size(); ++i)
		if (vector_names[i].name == s) return vector_names[i].value;
	
	error ("попытка получить значение необъявленной переменной ( Symbol_table::get() )");
}

void Symbol_table::set(string s, double d)
//изменить (установить) значение существующей переменной
//на вход: имя переменной и её новое значение
{
	for (int i = 0; i < vector_names.size(); ++i)
		if ( vector_names[i].constant && vector_names[i].name == s )
			error ("попытка изменить константу ( Symbol_table::set() )");
		
		else if ( vector_names[i].name == s ) {
			vector_names[i].value = d;
			return;
		}
	
	error ("попытка установить значение для необъявленной переменной ( Symbol_table::set() )");
}

bool Symbol_table::is_declared(string s)
//проверка существует ли уже переменная с таким именем
//на вход: имя переменной
//на выходе: true - если переменная с таким именем существует / false - если нет
{
	for (int i = 0; i < vector_names.size(); ++i)
		if ( vector_names[i].name == s )	return true;
	
	return false;
}

void Symbol_table::define(string name, double d, bool cnst)
//добавление не объявленной ранее переменной/константы в массив переменных
//на вход: имя несуществующей переменной, её значение и яв-ся ли она константой или нет (true - если да)
{
	//Если такой переменной/константы ещё не существует в массиве
	if ( is_declared(name) == false )
		vector_names.push_back(Variable(name, d, cnst));
	
	//Если переменная с таким именем уже существует..
	else
		error ("попытка объявления уже существующей переменной ( Symbol_table::define() )"); //..ошибка
		//set(string name, double d); //..изменяем её значение
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
	else if (num == 0)
		return 1;	 //Факториал нуля равен единице
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
//При необходимости вычисляется факториал или происходит возведение в степнь
{
	Token t = ts.get();
	
	switch (t.kind)
	{
		case POW: //символ '^' обозначает что происходит возведение в степень
			return pow_proc(left); //Пробуем возвести в степень
		
		case '!': //символ '!' обозначает что происходит вычисление факториала
			return factorial(left); //Пробуем вычислить факториал числа
		
		case PRINT:
		case ')': case '}': case '+': case '-': case '*': case '/': case '%':
			cin.unget();
			//ts.putback(t); //Возвращаем символ в поток токенов, иначе потеряется
			return left;
			
		default:
			error ("ожидался оператор (<нажатие Enter>, +, -, *, /, %, !, ^) ( post_oper() )");
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
			return narrow_cast<int>( expression() );
	}
}

void calculate() //Цикл вычисления выражения
{
	while (cin)
	try 
	{
		double res = 0;
		
		cout << PROMPT;
		Token t = ts.get();
		
		while (t.kind == PRINT)		t = ts.get();
		
		//Если введено 'quit' - немедленный выход из программы
		if (t.kind == QUIT)				return;
		
		//Вызывается исключение в ф-ции calculate() выводящее инструкцию и вновь запускающее расчёты
		else if (t.kind == HELP)		error (HELPKEY);
		
		//вывод всех уже объявленных переменных и констант
		else if (t.kind == TABLEOUT)	error (TABLEOUTKEY);
		
		ts.putback(t);
		res = statement();
		
		cout << RESULT << res << "\n\n"; //endl
		
		/*if (fmod(res,int(res)) != 0)
			error ("сужающее преобразование ( calculate() )");
		
		cout << RESULT << narrow_cast<int>(res) << "\n\n"; //endl*/
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		string str = e.what();
		
		//При вводе CTRL+Z вызывается исключение в main(), которое в свое время приводит к 
		//вопросу хочет ли пользователь закрыть программу
		if ( str == "CTRL+Z" )		error(str);
		
		else if ( str == HELPKEY )		cerr << HELP_INSTR; //ИНСТРУКЦИИ
		
		else if ( str == TABLEOUTKEY )	var_table.table_out();
		
		else
			cerr << "Ошибка ( calculate() ): " << str << "\n\n";
		
		getline(cin, str);
		cin.clear();
		//ts.ignore(PRINT);
	}
}

//------------------------------------------------------------------------------

int main()
try
{
	cout << "Добро пожаловать в программу калькулятор 2022 по Бьярне Страуструпу.\n\n"
			"После знака '>' вводите выражение в формате: ЧИСЛО ОПЕРАТОР ЧИСЛО. "
			"Числа могут быть с любым знаком, но обязательно ЦЕЛЫМИ.\n"
			"Для завершения ввода (подтверждения) нажмите клавишу ENTER.\n\n"
			"   help - вызов справки\n   quit - для быстрого выхода\n\n"; //ПРИВЕТСТВИЕ
	
	//var_table.define("pi", 3.1415926535, true);
	//var_table.define("e", 2.7182818284, true);
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
	cin.clear();
	
	if (Y_or_N("Закрыть программу?"))	return 1002; //4
	else								calculate();
}

//------------------------------------------------------------------------------
