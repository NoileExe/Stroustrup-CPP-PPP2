#include "token.h"

//------------------------------------------------------------------------------

const string HELP_INSTR = "\n\nEnter expressions in the format: NUMBER OPERATOR NUMBER."
			"\nNumbers can be with any sign, integers and decimals "
			"(DOT - decimal separator). "
			"To complete the entry (confirmation), press the ENTER key.\n\n"
			
			"Available operations:\n\n"
			"-------------------------------------------------------\n"
			"|    +    |     -    |     *     |    /   |     %     |\n"
			"----------+----------+-----------+--------+-----------|\n"
			"|         |          |           |        | remainder |\n"
			"|   add   | subtract |  multiply | divide |   of the  |\n"
			"|         |          |           |        |  division |\n"
			"-------------------------------------------------------\n"
			
			"------------------------------------------------------\n"
			"|      ()     |     ^     |  NUMBER!  | sqrt(NUMBER) |\n"
			"--------------+-----------+-----------+--------------|\n"
			"|             |  raise to |           |  square root |\n"
			"| parentheses | the power | factorial |     of a     |\n"
			"|             |           |           |    number    |\n"
			"------------------------------------------------------\n"
			
			"\nExample:\n> -2+(2*2) \n= 2\n\n"
			
			"The program provides the following constants (number Pi, number e and "
			"a thousand multiplier):\n pi = 3.1415926535\n e = 2.7182818284\n k = 1000\n\n"
			
			"It is also possible to declare and apply your own variables (#) "
			"and constants ($), which are set once without the possibility of change. "
			"Name must start with a letter, may contain letters, numbers, and the '_' symbol."
			"\nVariable declaration example:\n> #var1=100 \n= 100\n"
			"\nVariable change example:\n> var1 =5+.79 \n= 5.79\n"
			"\nConstant declaration example:\n> $ con_1 = 10 \n= 10\n"
			"\nUse example:\n> var1-2 \n= 3.79\n\n"
			"   out - output of all constants and variables in program memory\n"
			"   help - call help\n   quit - for a quick exit\n\n"; //ИНСТРУКЦИИ

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
//Символ 'c' представляет разновидность лексем
//отбросывает все символы до указанного на входе в функцию, ничего не возвращает
{
	//Сначала проверяем буфер
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	
	//Затем проверяем входные данные
	Token_stream::full = false;
	char ch = 0;
	while (ist >> ch)
		if (ch == c || ch == '\n') return;  // || ch == '\n'
}

//Член putback() помещает аргумент в буфер своей ф-ции Token_stream:
void Token_stream::putback(Token t)
{
	if (full)
		error("Function putback() error: attempt to fill an already full buffer");

	buffer = t;			//копировать t в буфер
	full = true;		//теперь буфер полон
}

Token Token_stream::get()
{
	if (full) { //Если в буфере уже имеется объект типа Token..
		//..удаляем его из буфера (помечаем буфер как пустой, т.е. доступный для перезаписи)
		full = false;
		return buffer;
	}

	char ch = ' ';
	ist.get(ch); //Съедаем пробелы while ( isspace(ch) && ch != PRINT && !cin.eof() )		//basic_istream::
	
	if (ist.eof())   return Token(QUIT);
	
	else if (ch == PRINT) return Token(PRINT); //для завершения вычислений и немедленного вывода ответа на экран
	ist.unget();
	
	ist >> ch;		//замечание: оператор >> пропускает пустые пространства
					//(пробел, символ новой строки, табуляция и т.д.)
	
	switch (ch)
	{
		case LET: case CONSTANT: case '=': //переменные и константы
		case POW: //степень
		case '!': //факториал
		case '(': case ')':
		case '+': case '-': case '*': case '/': case '%':
			return Token(ch);        //Каждый символ представляет сам себя
		
		case '.': //Число с плавающей зпт может начинаться с точки
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			ist.unget(); //возврат каретки на 1 символ назад
			double val;
			ist >> val;		//считываем число с плавающей ЗПТ
			
			//if ( ch == '.' && val == 0 )	error ("invalid input ( Token_stream::get() )");
			
			return Token(NUMBER, val);	//помечаем объект символом '8' означающим "число"
		
		default:
		{
			string str = "";
			
			if ( isalpha(ch) ){ //Если первый символ - буква (имя может начинаться только с буквы)
				str += ch;
				
				while (ist.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
									   //буква,          цифра    или нижнее подчеркивание
					str += ch;
				
				ist.unget(); //возврат каретки на 1 символ назад, т.к. он не имеет отношения к имени
				
				if		(str == HELPKEY)			return Token(HELP);
				else if (str == QUITKEY)			return Token(QUIT);
				else if (str == SQRTKEY)			return Token(SQRT);
				else if (str == TABLEOUTKEY)		return Token(TABLEOUT);
				//else if (str == CHANGEINPUTKEY)		return Token(CHANGEINPUT);
				//else if (str == CHANGEOUTPUTKEY)	return Token(CHANGEOUTPUT);
				
				return Token(VARIABLE, str);
			}
			
			ist.clear();
			error ("invalid input ( Token_stream::get() )");
		}
	}
}

//------------------------------------------------------------------------------