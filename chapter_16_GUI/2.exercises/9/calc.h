// Калькулятор из 10ой главы 10го упражнения, но без изменения потоков ввода и вывода
/*
 * Token_stream теперь не является глобальным и создаётся в ф-ции calculate() с указанием для токенов потока ввода 
 * 		в качестве явного параметра при инициализации (хранится в классе); 
 * 		все остальные же функции использующие токены получают его по цепочке в качестве ссылочного аргумента на входе.
 * Самой же функции calculate() на вход подаются в качестве явных параметров потоки ввода/вывода, которые указывают откуда 
 * 		брать данные и куда выводить результаты. Поток вывода во время вычислений и для ошибок используется только 
 * 		в ф-ции calculate(), поток же ввода, помимо прочего, до цикла вычислений указывается как явный параметр при 
 * 		инициализации Token_stream использующимся уже всеми другими функциями.
 * Для упрощения были удалены вложенные скобки {} .
 * 
 * Изменения:
 * 		переведены на английский инструкция и ошибки
 * 		ф-ция calculate() значительно изменена для работы с GUI-программой [данный файл]
 * 		для обозначения ошибки (вывод в консоль без закрытия программы) добавлен новый токен EWARNING [token.h и данный файл]
 * 		для отключения возможности изменения потоков ввода/вывода на стандартные/файловые закомментированы строки с идентификацией
 * 			CHANGEINPUTKEY и CHANGEOUTPUTKEY в ф-ции Token_stream::get() [token.cpp две строки]
 * 
*/

//#include <std_lib_facilities.h>
#include "token.h"
#include "varconst.h"



//------------------------------------------------------------------------------

const string quit_question = "Close program?";



class Change_Input {};
class Change_Output {};
//void calculate(istream& ist, ostream& ost);


Symbol_table var_table;			//обеспечивает работу с переменными и константами


double post_oper(double, Token_stream&);	//вызывается из pow_proc(), factorial(), primary()
double primary(Token_stream&);				//вызывается из pow_proc (возведение в степень)
double expression(Token_stream&);			//объявляем, т.к. ф-ция primary() может вызвать expression()

//------------------------------------------------------------------------------

double pow_proc(double num, Token_stream& ts)
//возведение входящего числа в степень, возвращает таковых р-тат вычислений
//либо вызывает исключение  
{
	double pow_num = primary(ts);
	
	//pow_num < -323 - будет равно 0, при -323 и больше до -318 - значение искажается
	if ( pow_num > 308 || pow_num < -323 )
		error ("number is out of DOUBLE range when raised to a power ( pow_proc() )");
	else if ( pow_num != int(pow_num) )
		error ("power value must be an INTEGER number ( pow_proc() )");
	
	pow_num = pow(num,pow_num);
	
	if ( isinf(pow_num) )
		error ("number is out of DOUBLE range when raised to a power ( pow_proc() )");
	
	return post_oper(pow_num, ts); //проверка правильности выражения
	/*На самом деле тут кроется проблема при вводе например 2 ^2 ^2+1 - т.е. при вычислении самой степени выражение
	 * указывающее степень требуется закрывать в скобки иначе указанное выше будет восприниматься прямолинейно:
	 * 2 ^2 ^2+1 == ( (2^2)^2 ) + 1*/
}

double factorial(double num, Token_stream& ts) //Вычисление факториала. На вход только целые положит. числа
{
	if (num - int(num) != 0)
		error ("factorial must be of an INTEGER number ( factorial() )");
	
	else if (num == 0) return 1;     //Факториал нуля равен единице
	
	else if (num < 0)
		error ("factorial must be of a POSITIVE number ( factorial() )");
	
	
	double answer = 1;
	for (double i = 1; i <= num; ++i)
	{
		answer *= i;
		
		//Если при вычислении факториала ответ равен inf или -inf (+-бесконечность)
		if ( isinf(answer) )
			 error ("when calculating the factorial, the number is out of DOUBLE range ( factorial() )");
	}
	
	 //проверка правильности выражения, т.к. за факториалом может стоять ещё выражение, оператор или символ
	return post_oper(answer, ts);
}

double post_oper(double left, Token_stream& ts)
//проверяет идёт ли дальше какой-либо оператор, т.е. завершено ли выражение
//Если всё верно, просто возвращаем лексему как есть, иначе вызываем исключение
//При необходимости вычисляется факториал или происходит возведение в степнь
{
	Token t = ts.get();
	
	switch (t.kind)
	{
		case POW:		//символ '^' обозначает что происходит возведение в степень
			return pow_proc(left, ts); //Пробуем возвести в степень
		
		case '!':		//символ '!' обозначает что происходит вычисление факториала
			return factorial(left, ts); //Пробуем вычислить факториал числа
		
		case PRINT:
		case ')': case '+': case '-': case '*': case '/': case '%':
			ts.putback(t); //Возвращаем символ в поток токенов, иначе потеряется
			return left;
			
		default:
			error ("operator expected (<pressing Enter>, +, -, *, /, %, !, ^) ( post_oper() )");
	}
}

//------------------------------------------------------------------------------

//обработка чисел, двух видов скобок и факториала
double primary(Token_stream& ts)
{
	Token t = ts.get();
	
	switch (t.kind)
	{
		case '(':			//регулирует конструкцию '(' выражение ')'
		{
			double d = expression(ts);
			t = ts.get();

			if (t.kind != ')')
				error ("close bracket expected - ')' ( primary() )");
			
			return post_oper(d, ts);
		}
		
		case NUMBER:		//символ '8' обозначает что объект является числом
		{
			double d = t.value; //получаем само число
			return post_oper(d, ts);
		}
		
		case '-':			//Помогает избежать ошибки если первое число в выражении отрицательное
			return post_oper(- primary(ts), ts);
		case '+':
			return post_oper(primary(ts), ts);
		
		case SQRT:
		{
			t = ts.get();
			if (t.kind != '(')
				error ("opening brace expected after 'sqrt' operator - '(' ( primary() )");
			
			double d = expression(ts); //получаем конечное число в скобках
			if (d < 0)
				error ("root must be from POSITIVE number ( primary() )");
			
			t = ts.get();
			if (t.kind != ')')
				error ("close bracket expected - ')' ( primary() )");
			
			return post_oper( sqrt(d), ts );
		}
		
		case VARIABLE: {	//символ 'a' обозначает что происходит обращение к переменной
			string strname = t.name;
			
			t = ts.get();
			if (t.kind == '=') {//Если изменение значения переменной
				double d = expression(ts); //получаем новое значение
				
				//пытаемся изменить значение (ошибка если нет такой переменной или если это константа)
				var_table.set(strname, d);
				return d;
			}
			
			else { //получить значение переменной по строке с её именем для использования в вычислениях
				ts.putback(t);
				return post_oper( var_table.get(strname), ts );
			}
		}
		
		default:
			error ("primary expression expected ( primary() )");
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
				if (d == 0)		error ("division by zero ( term() )");
				
				left /= d; //вычисляем первичное_выражение и делим
				break;
			}
			case '%':
			{
				double d = primary(ts);
				if (d == 0)		error ("division by zero ( term() )");
				
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
	double left = term(ts);		//считываем и вычисляем Term

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

double declaration(bool cnst, Token_stream& ts)
//проверка на корректность ввода при объявлении переменной;
//добавление не объявленной ранее переменной в массив переменных
//На вход - является ли переменная константой (true если да)
{
	Token t = ts.get();
	
	if (t.kind == HELP || t.kind == QUIT || t.kind == SQRT || t.kind == TABLEOUT)
		error ("the name of a variable/constant cannot be the same as the name of the program commands  ( declaration() )");
	
	else if (t.kind == NUMBER)
		error ("the entered variable/constant name is most likely a number  ( declaration() )");
	
	else if (var_table.is_declared(t.name))
		error ("attempt to re-declare a variable/constant ( declaration() )");
	
	
	string name = t.name;
	
	t = ts.get();
	if (t.kind != '=')
		error ("missing character '=' when declaring a variable ( declaration() )");
	
	double d = expression(ts);
	var_table.define(name, d, cnst);
	
	return d;
}

//Определяем что подал на ввод пользователь - 
//объявление переменной, константы или выражение
double statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
		case LET: //пользователь хочет объявить переменную
			return declaration(false, ts);
			
		 case CONSTANT: //пользователь хочет объявить константу
			return declaration(true, ts);
			
		default: //пользователь запросил другую операцию (вычисления)
			ts.putback(t); //возвращаем t обратно в поток token'ов
			return expression(ts);
	}
}

char calculate(istream& ist, ostream& ost) //Цикл вычисления выражения
{
	Token_stream ts {ist};
	
	//while (ist)
	try 
	{
		if ( &ist == &cin )
			cout << PROMPT; //Чтобы видеть на экране приглашение ко вводу
		
		Token t = ts.get();
		
		while (t.kind == PRINT)		t = ts.get();
		
		//Если введено 'quit' - немедленный выход из программы
		if (t.kind == QUIT)				return QUIT;
		
		//Вызывается исключение в ф-ции calculate() выводящее инструкцию и вновь запускающее расчёты
		else if (t.kind == HELP)			error (HELPKEY);
		
		//вывод всех уже объявленных переменных и констант
		else if (t.kind == TABLEOUT)		error (TABLEOUTKEY);
		
		//Смена потоков ввода/вывода
		else if (t.kind == CHANGEINPUT)		throw Change_Input{};
		else if (t.kind == CHANGEOUTPUT)	throw Change_Output{};
		
		
		ts.putback(t);
		
		double res = 0;
		res = statement(ts);
		
		ost << defaultfloat << res;
		
		return PRINT;
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		string str = e.what();
		
		if ( str == HELPKEY )	//ВЫВОД ИНСТРУКЦИИ только в поток cout
			{ cout << HELP_INSTR;	return HELP; }
		
		else if ( str == TABLEOUTKEY )	//Вывод всех переменных/констант  только в поток cout
			{ var_table.table_out();		return TABLEOUT; }
		
		else {
			cout << "Error ( calculate() ): " << str << "\n\n";
			ost  << "Error ( calculate() ): " << str << "\n\n";
		}
		
		getline(ist, str);
		ist.clear();
		
		return EWARNING;
	}
	
	catch (Change_Input) { //Изменение потока ввода. Может вызвать исключение в main()
		string input_TS  = "cin";
		string output_TS = "cout";
		
		for (char ch = '0'; cin >> ch  &&  isspace(ch); ) {} 
		cin.unget();
		
		getline(cin, input_TS);
		
		if ( Y_or_N("Вывод стоит производить в файл?") ) {
			cout << "Введите поток/файл для вывода: ";
			
			for (char ch = '0'; cin >> ch  &&  isspace(ch); ) {}
			cin.unget();
			
			getline(cin, output_TS);
		}
		
		
		if ( input_TS  == "cin" )
			if ( output_TS  == "cout" )		calculate(cin, cout);
			else {
				ofstream file_ost { output_TS };
				if (!file_ost)	error("Невозможно открыть файл '" + output_TS + "'");
				
				calculate(cin, file_ost);
			}
			
		else {
			ifstream file_ist { input_TS };
			if (!file_ist)	error("Невозможно открыть файл '" + input_TS + "'");
			file_ist.exceptions(file_ist.exceptions()|ios_base::badbit);
			
			if ( output_TS  == "cout" )		calculate(file_ist, cout);
			else {
				ofstream file_ost { output_TS };
				if (!file_ost)	error("Невозможно открыть файл '" + output_TS + "'");
				
				calculate(file_ist, file_ost);
			}
		}
		
		
		ost << "\n\nПоток закрыт\n\n";
		if ( &ost != &cout )  //Чтобы видеть на экране то же что выводится в файл
			cout << "\n\nПоток закрыт\n\n";
		
		//getline(ist, output_TS);
		ist.clear();
	}
	
	catch (Change_Output) { //Изменение потока вывода. Может вызвать исключение в main()
		string output_TS = "cout";
		
		for (char ch = '0'; cin >> ch  &&  isspace(ch); ) {}
		cin.unget();
		
		getline(cin, output_TS);
		
		if ( output_TS  == "cout" )		calculate(cin, cout);
		else {
			ofstream file_ost { output_TS };
			if (!file_ost)	error("Невозможно открыть файл '" + output_TS + "'");
			
			calculate(cin, file_ost);
		}
		
		
		ost << "\n\nПоток закрыт\n\n";
		if ( &ost != &cout )  //Чтобы видеть на экране то же что выводится в файл
			cout << "\n\nПоток закрыт\n\n";
		
		//getline(ist, output_TS);
		ist.clear();
	}
}

//------------------------------------------------------------------------------