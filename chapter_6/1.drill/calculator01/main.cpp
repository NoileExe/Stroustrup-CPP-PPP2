// calculator01.cpp

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------
ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
//------------------------------------------------------------------------------

class Token {
public:
	char kind;		// what kind of token
	double value;	 // for numbers: a value 
	Token(char ch)	// make a Token from a char
		:kind(ch), value(0) { }
	Token(char ch, double val)	 // make a Token from a char and a double
		:kind(ch), value(val) { }
};

//------------------------------------------------------------------------------

class Token_stream {
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();	  // get a Token (get() is defined elsewhere)
	void putback(Token t);	// put a Token back
private:
	//bool Token_stream::full{ false };		// is there a Token in the buffer?
	bool full;
	Token buffer;	 // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)	// no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
	if (Token_stream::full) error("putback() into a full buffer");
	Token_stream::buffer = t;	   // copy t to buffer
	Token_stream::full = true;	  // buffer is now full
}

//------------------------------------------------------------------------------

int num_of_symb = 0; //Чтобы отслеживать первый символ в строке или нет

//------------------------------------------------------------------------------

Token Token_stream::get()
{
	if (Token_stream::full) {	   // do we already have a Token ready?
		// remove token from buffer
		Token_stream::full = false;
		return Token_stream::buffer;
	}

	char ch;
	cin >> ch;	// note that >> skips whitespace (space, newline, tab, etc.)
	
	if (cin.eof())   throw 6;

	switch (ch) {
	
	case 'x':  throw 5;// for "quit"

	case '=':	// for "print"
	case ')': case '}': case '+': case '*': case '/':
		return Token(ch);		// let each character represent itself
		
	case '(': case '{':
		num_of_symb = 0;
		return Token(ch);
	 
	case '-': 
	{
		if ( num_of_symb == 0 ) //Если считывается первое число в выражении
		{
			cin.putback(ch);		 // put digit back into the input stream
			double val;
			cin >> val;			  // read a floating-point number
			return Token('8', val);   // let '8' represent "a number"
		}
		else   return Token(ch);
	}

	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);		 // put digit back into the input stream
		num_of_symb = 1;
		double val;
		cin >> val;			  // read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}

	default:
		throw 1; //cerr << "Bad token";

	}
}

//------------------------------------------------------------------------------

Token_stream ts;		// provides get() and putback() 

//------------------------------------------------------------------------------

double expression();	// declaration so that primary() can call expression()
char question_close();

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	
	case '(':	// handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') throw 2; //cerr << "')' expected\n\n> ";
		return d;
	}
	
	case '{':	// handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}') throw 2; //cerr << "')' expected\n\n> ";
		return d;
	}
	
	case '8':			// we use '8' to represent a number
		return t.value;  // return the number's value
		
	case '=': //Избежать ошибки если первое отрицательное
		cin.putback(t.kind);
		return 0;

	default: //cerr << "primary expected\n\n> ";
		throw 3;
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
	double left = primary();
	Token t = ts.get();		// get the next token from token stream

	while (true) {
		switch (t.kind) {
		
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0)   throw 4; //cerr << "divide by zero\n\n> ";
			left /= d;
			t = ts.get();
			break;
		}

		default:
			ts.putback(t);	 // put t back into the token stream
			return left;
		}
	}
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
	double left = term();	  // read and evaluate a Term
	Token t = ts.get();		// get the next token from token stream

	while (true) {
		switch (t.kind) {
		case '+':
			left += term();	// evaluate Term and add
			t = ts.get();
			break;
		case '-':
			left -= term();	// evaluate Term and subtract
			t = ts.get();
			break;

		default:
			ts.putback(t);	 // put t back into the token stream
			return left;	   // finally: no more + or -: return the answer
		}
	}
}

//------------------------------------------------------------------------------

int first_or_not = 0; //Чтобы отслеживать какой раз вызывается ф-ция main()

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			if (first_or_not == 0)
			{
				cout << "Добро пожаловать в программу калькулятор 2019 по Бьярне Страуструпу.\n\n"
					"После знака '>' вводите выражение в форме: ЧИСЛО ОПЕРАТОР ЧИСЛО ЗНАК_РАВЕНСТВА.\n"
					"Для завершения ввода (подтверждения) нажмите клавишу ENTER.\n\n"
					"Последний (знак равенства '=') - используется для завершения выраж"
					"ения и произведения вычисления. ВНИМАНИЕ! Если вы не введёте знак "
					"равенства вы не получите результата вычислений.\n\nЧисла могут быт"
					"ь с любым знаком, целыми и с десятичной частью (ТОЧКА - десятичный"
					" разделитель).\n\nДоступные операции: +, -, *, /, ( ); x - для быс"
					"трого выхода\n\nПример:\n> 2+(2*2)= ";
				first_or_not = 1;
			}
			else
				cout << "\nВводите выражения в форме: ЧИСЛО ОПЕРАТОР ЧИСЛО ЗНАК_РАВЕНСТВА.\n"
					"Доступные операции: +, -, *, /, ( )\nПример:\n> 2+(2*2)= ";

			double val = 0;
			cout << "\n\n> ";
			while (cin) {
				Token t = ts.get();

				if (t.kind == '=')		// '=' for "print now"
				{
					cout << " = " << val << "\n\n> ";
					num_of_symb = 0;
				}
				else
					ts.putback(t);

				val = expression();
			}
			
			cout << "\n\n";
			press_Enter_key();
			return EXIT_SUCCESS;
		}
		catch (exception& e) {
			cerr << "error: " << e.what() << '\n';
			
			num_of_symb = 0;
			
			if (question_close() == 'y')	return 0; //1
		}
		catch (int a) {
			string str;
			getline(cin, str);
			cin.clear();

			if (a < 5)			cerr << "Ошибка: ";

			if (a == 1)			cerr << "недопустимый ввод (#1)	 ";
			else if (a == 2)	cerr << "ожидалась закрывающая скобка - ')' или '}' (#2)	 ";
			else if (a == 3)	cerr << "ожидалось первичное выражение (#3)	 ";
			else if (a == 4)	cerr << "деление на нуль (#4)	 ";
			else if (a == 5)	return 0;
			
			num_of_symb = 0;
			
			if (question_close() == 'y')	return 0; //2
		}
		catch (...) {
			cerr << "Упс! Неизвестное исключение!\n";
			
			num_of_symb = 0;
			
			if (question_close() == 'y')	return 0; //3
		}
	}
}

//------------------------------------------------------------------------------

char question_close()
{
	string str;
	/*getline(cin, str);
	cin.clear();*/
	cout << "\nЗакрыть программу (введите 'y' или 'n' - Да или Нет)?\n";

	char ch = '0';
	while (cin >> ch && ch != 'y' && ch != 'n')
	{
		getline(cin, str);
		cin.clear();

		cout << "Закрыть программу (введите 'y' или 'n' - Да или Нет)?\n";
	}

	if (cin.eof())
	{
		getline(cin, str);
		cin.clear();
		return 'y';
	}
	else 
	{
		getline(cin, str);
		cin.clear();
		return ch;
	}
}

//------------------------------------------------------------------------------
