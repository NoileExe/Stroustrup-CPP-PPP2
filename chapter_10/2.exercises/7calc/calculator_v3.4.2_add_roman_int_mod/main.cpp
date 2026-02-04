// calculator01.cpp
//Добавлена возможность вывода списка всех переменных и констант
//Помимо прочего работает с римскими числами. Для этого изменения коснулись инструкций и следующих функций:
//  -[main.cpp]: calculate() - вывод результата
//  -[token.cpp]: Token_stream::get() - считывание римского числа в блоке с именами переменных
//  -[token.h]: прописан заголовочный файл для работы с римскими числами

#include "token.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

Token_stream ts; //обеспечивает работу с членами ф-ции ignore(), get() и putback()
Symbol_table var_table; //обеспечивает работу с переменными и константами

double post_oper(double); //вызывается из pow_proc(), factorial(), primary()
double primary(Token_stream&); //вызывается из pow_proc (возведение в степень)
double expression(Token_stream&); //объявляем, т.к. ф-ция primary() может вызвать expression()

//------------------------------------------------------------------------------

double pow_proc(double num)
//возведение входящего числа в степень, возвращает таковых р-тат вычислений
//либо вызывает исключение
{
	double pow_num = primary(ts);
	
	//pow_num < -323 - будет равно 0, при -323 и больше до -318 - значение искажается
	if ( pow_num > 308 || pow_num < -323 )
		error ("при возведении в степень число выходит за диапазон DOUBLE ( pow_proc() )");
	else if ( pow_num != int(pow_num) )
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
	
	else if (num == 0) return 1;     //Факториал нуля равен единице
	
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
double primary(Token_stream& ts)
{
	Token t = ts.get();
	
	switch (t.kind)
	{
		case '(':		//регулирует конструкцию '(' выражение ')'
		{
			double d = expression(ts);
			t = ts.get();

			if (t.kind != ')')
				error ("ожидалась закрывающая скобка - ')' ( primary() )");
			
			return post_oper(d);
		}
		
		case '{':		//регулирует конструкцию '{' '(' выражение ')' '}'
		{
			string str = " ";
			getline(cin, str);
			cin.clear();
			
			//Поиск круглой открывающей скобки внутри фигурных
			//(наличие закрывающей проверяет primary() через вызов 'double d = expression();')
			for (int i = 0; i < str.size(); ++i) {
				if (str[i] == '(') { str += '\n'; break; } //Чтобы после вычислений не ожидался ввод Enter
				else if (i == str.size()-1)
					error ("ожидалось выражение в '(' и ')' внутри выражения в '{' и '}' ( primary() )");
			}
			
			//cin.putback('\n');
			
			//Начиная с конца возвращаем всю строку в поток ввода
			for (int i = str.size()-1; i >= 0; --i)
				cin.putback(str[i]);
			
			double d = expression(ts);
			t = ts.get();

			if (t.kind != '}')
				error ("ожидалась закрывающая скобка - '}' ( primary() )");
			
			return post_oper(d);
		}
		
		case NUMBER:		//символ '8' обозначает что объект является числом
		{
			double d = t.value; //получаем само число
			return post_oper(d);
		}
		
		case '-':				//Помогает избежать ошибки если первое число в выражении отрицательное
			return post_oper(- primary(ts));
		case '+':
			return post_oper(primary(ts));
		
		case SQRT:
		{
			t = ts.get();
			if (t.kind != '(')
				error ("после оператора 'sqrt' ожидалась открывающая скобка - '(' ( primary() )");
			
			double d = expression(ts); //получаем конечное число в скобках
			if (d < 0)
				error ("корень должен быть из ПОЛОЖИТЕЛЬНОГО числа ( primary() )");
			
			t = ts.get();
			if (t.kind != ')')
				error ("ожидалась закрывающая скобка - ')' ( primary() )");
			
			return post_oper( sqrt(d) );
		}
		
		case VARIABLE: {		//символ 'a' обозначает что происходит обращение к переменной
			string strname = t.name;
			
			t = ts.get();
			if (t.kind == '=') {//Если изменение значения переменной
				double d = expression(ts); //получаем новое значение
				
				//пытаемся изменить значение (ошибка если нет такой переменной или если это константа)
				var_table.set(strname, d);
				return d;
			}
			
			else {				//получить значение переменной по строке с её именем для использования в вычислениях
				ts.putback(t);
				return post_oper( var_table.get(strname) );
			}
		}
		
		default:
			error ("ожидалось первичное выражение ( primary() )");
	}
}

//------------------------------------------------------------------------------

//обработка операторов *, / и %
double term(Token_stream& ts)
{
	double left = primary(ts); //считываем и вычисляем первичное_выражение

	while (true) {
		Token t = ts.get();  //получаем след. объект token из потока token'ов
		switch (t.kind)
		{
			case '*':
				left *= primary(ts); //вычисляем первичное_выражение и умножаем
				break;
			case '/':
			{
				double d = primary(ts);
				if (d == 0)		error ("деление на нуль ( term() )");
				
				left /= d; //вычисляем первичное_выражение и делим
				break;
			}
			case '%':
			{
				double d = primary(ts);
				if (d == 0)		error ("деление на нуль ( term() )");
				
				left = fmod(left,d);
				/* Ф-ция из стандартной библиотеки возвращающая остаток от деления
				даже при делении чисел в дробной частью, например:
					6.7 % 3.3 = 6.7 - 3.3 * int(6.7/3.3) = 0.1
				*/
				break;
			}
			
			default:
				ts.putback(t);		//возвращаем t обратно в поток token'ов
				return left;
		}
	}
}

//------------------------------------------------------------------------------

//обработка операторов + и -
double expression(Token_stream& ts)
{
	double left = term(ts);			//считываем и вычисляем Term

	while (true) {
		Token t = ts.get();		//получаем след. объект Token из потока Token'ов
		switch (t.kind)
		{
			case '+':
				left += term(ts);	//вычисляем Term и прибавляем
				break;
			case '-':
				left -= term(ts);	//вычисляем Term и отнимаем
				break;
			
			default:
				ts.putback(t);		//возвращаем t обратно в поток token'ов
				return left;		//наконец: больше нет + или -: возвращаем ответ
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
	
	if (t.kind == HELP || t.kind == QUIT || t.kind == SQRT || t.kind == TABLEOUT)
		error ("имя переменной/константы не может совпадать с именем команд программы  ( declaration() )");
	
	else if (t.kind == NUMBER)
		error ("введённое имя переменной/константы скорее всего является числом  ( declaration() )");
	
	else if (t.kind != 'a')
		error ("ожидалось корректное имя переменной/константы ( declaration() )");
	
	else if (var_table.is_declared(t.name))
		error ("попытка повторного объявления переменной/константы ( declaration() )");
	
	
	string name = t.name;
	
	t = ts.get();
	if (t.kind != '=')
		error ("при объявлении переменной пропущен символ '=' ( declaration() )");
	
	double d = expression(ts);
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
			return expression(ts);
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
		if (t.kind == QUIT)				return;
		
		//Вызывается исключение в ф-ции calculate() выводящее инструкцию и вновь запускающее расчёты
		else if (t.kind == HELP)		error (HELPKEY);
		
		//вывод всех уже объявленных переменных и констант
		else if (t.kind == TABLEOUT)	error (TABLEOUTKEY);
		
		ts.putback(t);
		
		double res = 0;
		res = statement();
		
		//-------------------------------------------------------------------------------------------------------------------------
		if ( res != int(res)  ||  res < 1  ||  res > 3999 ) {
			cout << "\n\nЗначение не может быть представленно в виде римского числа\n\n";
			cout << RESULT << res << "\n\n"; //endl
		}
		else
		//-------------------------------------------------------------------------------------------------------------------------
			cout << RESULT << Roman_int( res ) << "\n\n"; //endl
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		string str = e.what();
		
		if ( str == HELPKEY )
			cerr << HELP_INSTR;		//ВЫВОД ИНСТРУКЦИИ
		else if ( str == TABLEOUTKEY )
			var_table.table_out();	//Вывод всех переменных/констант
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
			"Числа могут быть с любым знаком, целыми и с десятичной частью ("
			"ТОЧКА - десятичный разделитель), а так же римские от 1 до 3999 (";
	
	for (char ch : primitives)
		if ( ch != primitives[ primitives.size()-1 ] )
			cout << ch << ", ";
		else
			cout << ch;
	
	cout << ").\nДля завершения ввода (подтверждения) нажмите клавишу ENTER.\n\n"
			"   help - вызов справки\n   quit - для быстрого выхода\n\n"; //ПРИВЕТСТВИЕ
	
	var_table.define("pi", 3.1415926535, true);
	var_table.define("e", 2.7182818284, true);
	var_table.define("k", 1000, true);
	
	calculate();
	
	//keep_window_open("~~");
	return 0;
}

//При вводе CTRL+Z вызывается исключение, которое в свое время приводит к 
//вопросу хочет ли пользователь закрыть программу
catch (CTRL_Z_throw) { 
	if (Y_or_N("Закрыть программу?"))	return 1;
	else								calculate();
}

catch (exception& e) { //Для системных исключений при работе с программой
	cerr << "Ошибка ( main() ): " << e.what() << '\n';
	
	
	if (Y_or_N("Закрыть программу?"))	return 1000;
	else								calculate();
}

catch (...) { //Для непредвиденных исключений
	cerr << "Упс! Неизвестное исключение! ( main() )\n";
	
	if (Y_or_N("Закрыть программу?"))	return 1001;
	else								calculate();
}

//------------------------------------------------------------------------------
