// calculator01.cpp

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

double expression(); //Объявляем, т.к. ф-ция primary() может вызвать expression()


const char number = '8'; //t.kind == number означает, что t - число
const char quit = 'x'; //t.kind == quit означает, что t - лексема для выхода из программы
const char print = '='; //t.kind == print означает, что t - лексема для вывода решения
const string prompt = "> "; //приглашение ко вводу
const string result = "= "; //для указания на то что за данным текстом следует результат вычислений
const string instructions = "\nВводите выражения в форме: ЧИСЛО ОПЕРАТОР ЧИСЛО "
			"ЗНАК_РАВЕНСТВА.\nЧисла могут быть с любым знаком, целыми и с десят"
			"ичной частью (ТОЧКА - десятичный разделитель)\nДоступные операции:"
			" +, -, *, /, % (остаток от деления), ( ), {()}, ЧИСЛО! (факториал)"
			"; x - для быстрого выхода\nПример:\n> 2+(2*2)= \n\n"; //ИНСТРУКЦИИ

//------------------------------------------------------------------------------

class Token {
public:
	char kind;		//что за символ
	double value;	 //для чисел: значение 
	Token(char ch)	//объект класса Token из символа
		:kind(ch), value(0) { }
	Token(char ch, double val)	 //объект класса Token из символа и числа double
		:kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
	Token_stream();   //создаём Token_stream который читает из потока ввода cin
	Token get();	  //получаем объект Token (член get() определен в другом месте)
	void putback(Token t); //возврат Token обратно в ф-цию (в буфер)
	void ignore(char c); //отбрасывает символы до символа 'c' включительно
private:
	//bool Token_stream::full{ false };		// is there a Token in the buffer?
	bool full;
	Token buffer;	 //здесь сохраняем объект класса Token, помещённый обратно,
														// используя putback ()
};

//------------------------------------------------------------------------------

//Конструкция, которая просто делает буфер пустым изначально:
Token_stream::Token_stream()
	:full(false), buffer(0)	//нет объекта Token в буфере
{
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c) //Символ 'c' представляет разновидность лексем
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
		if (ch == c) return;
}

//Член putback() помещает аргумент в буфер своей ф-ции Token_stream:
void Token_stream::putback(Token t)
{
	if (Token_stream::full)
		error("Ошибка ф-ции Token_stream::putback(): попытка заполнить уже полный буфер");

	Token_stream::buffer = t;	   //копировать t в буфер
	Token_stream::full = true;	  //теперь буфер полон
}

Token_stream ts; //обеспечивает работу с членами ф-ции get() и putback()

//------------------------------------------------------------------------------

int brace = 0; /*фигурная скобка используется для визуального отличия от круглой
(если скобки в скобках), потому если выражение в {} не содержит выражения в () - ОШИБКА*/

Token Token_stream::get()
{
	if (Token_stream::full == true) { //Если в буфере уже имеется объект типа Token..
		//..удаляем его из буфера (помечаем буфер как пустой, т.е. доступный для перезаписи)
		Token_stream::full = false;
		return Token_stream::buffer;
	}

	char ch;
	cin >> ch;	//замечание: оператор >> пропускает пустые пространства
				 //(пробел, символ новой строки, табуляция и т.д.)

	if (cin.eof()) {
		string error_str = "CTRL+Z";
		throw   runtime_error(error_str);
	}

	switch (ch)
	{
		case quit:	//для немедленного выхода
		case print:	//для завершения вычислений и немедленного вывода ответа на экран
		case '!':
		case ')': case '}': case '+': case '-': case '*': case '/': case '%':
			return Token(ch);		//Каждый символ представляет сам себя

		case '(':
			brace = 1; //Покажет что внутри {} скобок присутствуют вложенные круглые
						//Иначе если круглые скобки являются вложенными, при значении 0 - ошибка
			return Token(ch);

		case '{':
			brace = 0; //Покажет что внутри {} скобок отсутствуют вложенные круглые
			return Token(ch);

		case '.': //Число с плавающей зпт может начинаться с точки
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		{
			cin.putback(ch);		 //возвращаем символ обратно в потом ввода
			double val;
			cin >> val;			  //считываем число с плавающей ЗПТ
			return Token(number, val);   //помечаем объект символом '8' означающим "число"
		}

		default:
		{
			cin.putback(ch);
			string str;
			getline(cin, str);
			cin.clear();
			
			string error_str = "недопустимый ввод ( Token_stream::get() )";
			throw   runtime_error(error_str);
		}
	}
}

//------------------------------------------------------------------------------

double fact(double num) //Вычисление факториала. На вход только целые числа
{
	double answer = 1;

	if ( int(num) != num ) {
		string error_str = "факториал должен быть от ЦЕЛОГО числа ( fact() )";
		throw   runtime_error(error_str);
	}
	
	else if (num == 0)	return 1;	 //Факториал нуля равен единице
	
	else if (num < 0) {
		answer *= -1;
		num *= -1; //Чтобы возвращаемое значение было отрицательным
	}

	if (num - int(num) == 0) //Число целое?
		for (double i = 1; i <= num; ++i)
		{
			answer *= i;
		
			//Если при вычислении факториала ответ равен inf или -inf (+-бесконечность)
			if ( isinf(answer) ) {
				string error_str = "при вычислении факториала число выходит за диапазон DOUBLE ( fact() )";
				throw   runtime_error(error_str);
			}
		}

	return answer;
}

//------------------------------------------------------------------------------

//обработка чисел, двух видов скобок и факториала
double primary()
{
	/*Выражение:
							Терм
							Выражение + Терм
							Выражение - Терм
	  Терм:
							Первичное_Выражение
							Терм * Первичное_Выражение
							Терм / Первичное_Выражение
							Терм % Первичное_Выражение
	  Первичное_Выражение:
							Число
							Первичное_Выражение !
							( Выражение )
							( Выражение ) !
							{( Выражение )}
							{( Выражение )} !
							- Первичное_Выражение
							+ Первичное_Выражение
	  Число:
							Литерал_с_плавающей_точкой  */

	Token t = ts.get();
	
	switch (t.kind)
	{
		case '(':	//регулирует конструкцию '(' выражение ')'
		{
			double d = expression();
			t = ts.get();

			if (t.kind != ')') {
				string error_str = "ожидалась закрывающая скобка - ')' ( primary() )";
				throw   runtime_error(error_str);
			}

			//Обнаружение и вычисление факториала
			t = ts.get(); //записываем в t новое значение
			if (t.kind == '!') d = fact(d); //Пробуем вычислить факториал числа
			else if (t.kind != number) cin.putback(t.kind); //ts.putback(t); //Возвращаем символ в поток токенов, иначе потеряется

			return d;
		}

		case '{':	//регулирует конструкцию '{' '(' выражение ')' '}'
		{
			double d = expression();
			t = ts.get();

			if (t.kind != '}') {
				string error_str = "ожидалась закрывающая скобка - '}' ( primary() )";
				throw   runtime_error(error_str);
			}
			
			else if (brace == 0) {
				string error_str = "ожидалось выражение в '(' и ')' внутри выражения в '{' и '}' ( primary() )";
				throw   runtime_error(error_str);
			}

			//Обнаружение и вычисление факториала
			t = ts.get(); //записываем в t новое значение
			if (t.kind == '!') d = fact(d); //Пробуем вычислить факториал числа
			else if (t.kind != number) cin.putback(t.kind); //Возвращаем символ в поток токенов, иначе потеряется

			return d;
		}

		case number:			//символ '8' обозначает что объект является числом
		{
			double d = t.value; //получаем само число

			//Обнаружение и вычисление факториала
			t = ts.get(); //записываем в t новое значение
			if (t.kind == '!') d = fact(d); //Пробуем вычислить факториал числа
			else if (t.kind != number) cin.putback(t.kind); //ts.putback(t); //Возвращаем символ в поток токенов, иначе потеряется

			return d;  //возвращаем значение числа
		}
	
		case '-': //Помогает избежать ошибки если первое число в выражении отрицательное
			return (- primary());
		
		case '+':
			return primary();

		default: {
			string error_str = "ожидалось первичное выражение ( primary() )";
			throw   runtime_error(error_str);
		}
	}
}

//------------------------------------------------------------------------------

//обработка операторов *, / и %
double term()
{
	double left = primary(); //считываем и вычисляем первичное_выражение
	Token t = ts.get();		//получаем след. объект token из потока token'ов

	while (true) {
		switch (t.kind)
		{
			case '*':
				left *= primary(); //вычисляем первичное_выражение и умножаем
				t = ts.get();
				break;

			case '/':
			{
				double d = primary();

				if (d == 0) {
					string error_str = "деление на нуль ( term() )";
					throw   runtime_error(error_str);
				}

				left /= d; //вычисляем первичное_выражение и делим
				t = ts.get();
				break;
			}

			case '%':
			{
				double d = primary();

				if (d == 0) {
					string error_str = "деление на нуль ( term() )";
					throw   runtime_error(error_str);
				}

				left = fmod(left,d);
				/* Ф-ция из стандартной библиотеки возвращающая остаток от деления
				даже при делении чисел в дробной частью, например:
					
					6.7 % 3.3 = 6.7 - 3.3 * int(6.7/3.3) = 0.1
				*/
			
				t = ts.get();
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
	Token t = ts.get();		//получаем след. объект token из потока token'ов

	while (true) {
		switch (t.kind)
		{
			case '+':
				left += term();	//вычисляем Term и прибавляем
				t = ts.get();
				break;

			case '-':
				left -= term();	//вычисляем Term и отнимаем
				t = ts.get();
				break;

			default:
				ts.putback(t);	 //возвращаем t обратно в поток token'ов
				return left;	   //наконец: больше нет + или -: возвращаем ответ
		}
	}
}

//------------------------------------------------------------------------------

void clean_up_mess() //Цикл вычисления выражения
{
	ts.ignore(print);
}

void calculate() //Цикл вычисления выражения
{
	cout << instructions; //ИНСТРУКЦИИ
		
	while (cin)
	try 
	{
		cout << prompt;
		Token t = ts.get();
		
		while (t.kind == print) t = ts.get();
		
		if (t.kind == quit) return; //Если нажат 'x' - немедленный выход из программы
		
		ts.putback(t);
		cout << result << expression() << "\n\n";
	}
	catch (exception& e) { //Для системных исключений при работе с программой
		string str = e.what();
		
		//При вводе CTRL+Z вызывается исключение в main(), которое в свое время приводит к вопросу хочет ли пользователь закрыть программу
		if ( str == "CTRL+Z" )
			throw runtime_error(str);
		
		else
			cerr << "Ошибка ( calculate() ): " << str << '\n';
		
		clean_up_mess();
	}
}

//------------------------------------------------------------------------------

int main()
try
{
	cout << "Добро пожаловать в программу калькулятор 2019 по Бьярне Страуструпу.\n\n"
			"После знака '>' вводите выражение в формате указаном ниже.\n"
			"Для завершения ввода (подтверждения) нажмите клавишу ENTER.\n\n"
			"Последний (знак равенства '=') - используется для завершения выраж"
			"ения и произведения вычисления. ВНИМАНИЕ! Если вы не введёте знак "
			"равенства вы не получите результата вычислений.\n\nЧисла могут быт"
			"ь с любым знаком, целыми и с десятичной частью (ТОЧКА - десятичный"
			" разделитель).\n"; //ПРИВЕТСТВИЕ И ИНСТРУКЦИИ
	
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
	
	if (Y_or_N("Хотите закрыть программу?"))	return 1000; //1
	else										calculate();
}

catch (...) { //Для непредвиденных исключений
	cerr << "Упс! Неизвестное исключение!\n";
	
	if (Y_or_N("Хотите закрыть программу?"))	return 1001; //3
	else										calculate();
}

//------------------------------------------------------------------------------
