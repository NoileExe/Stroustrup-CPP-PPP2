#include "token.h"

//------------------------------------------------------------------------------

Roman_int::Roman_int(int n) //Проверка корректности и инициализация арабским числом
	:num(n)
{
	if ( n < 0 )
		error("число не является положительным ( инициализация Roman_int(int) )");
	
	if ( n > 3999 )
		error("число не может быть больше 3999 ( инициализация Roman_int(int) )");
}


Roman_int::Roman_int(string n) //Проверка корректности и инициализация строкой с римским числом
	:num()
{
	//Проверка примитивов (все ли символы допустимы)
	for (char ch : n)
		if ( check_primitives(ch) == false )
			error("найден недопустимый символ '" + to_string(ch) + "' ( инициализация Roman_int(string) )");
	
	num = romanstr2int(n);
}


Roman_int::Roman_int() //при создании пустой переменной класса Roman_int (конструктор по умолчанию)
	:num(1)
{
}

//------------------------------------------------------------------------------------------------------------

//Перевод строкового терма в целочисленное число
int term2int(string str)
{
	if 		( str == "I" )		return 1;
	else if ( str == "IV" )		return 4;
	else if ( str == "V" )		return 5;
	else if ( str == "IX" )		return 9;
	else if ( str == "X" )		return 10;
	else if ( str == "XL" )		return 40;
	else if ( str == "L" )		return 50;
	else if ( str == "XC" )		return 90;
	else if ( str == "C" )		return 100;
	else if ( str == "CD" )		return 400;
	else if ( str == "D" )		return 500;
	else if ( str == "CM" )		return 900;
	else if ( str == "M" )		return 1000;
	
	else						return -888; //Обозначает ошибку
}


//Перевод целочисленного числа в терм (строку)
string int2term(int i)
{
	if		( i == 1 )			return "I";
	else if ( i == 4 )			return "IV";
	else if ( i == 5 )			return "V";
	else if ( i == 9 )			return "IX";
	else if ( i == 10 )			return "X";
	else if ( i == 40 )			return "XL";
	else if ( i == 50 )			return "L";
	else if ( i == 90 )			return "XC";
	else if ( i == 100 )		return "C";
	else if ( i == 400 )		return "CD";
	else if ( i == 500 )		return "D";
	else if ( i == 900 )		return "CM";
	else if ( i == 1000 )		return "M";
	
	else						return ""; //Обозначает ошибку
}

//------------------------------------------------------------------------------------------------------------

//Поиск примитива в векторе primitives. Если примитив присутсвует возвращает true
bool check_primitives (char ch) {
	for (char orig : primitives)
		if ( ch == orig )		return true;
	
	return false; //Примитив не был найден
}


//Перевод из int в строковое представление римского числа
string int2romanstr(int x)
{
	vector<int> intterms { 1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000 };
	
	string str {""};
	
	for (int i = intterms.size()-1; i < intterms.size(); --i)
		
		//Если имеющееся число >= текущего делителя из вектора intterms
		//Т.е. при делении без остатка имеет целую часть
		if ( x/intterms[i] > 0 ) {
			for ( int j = 0; j < x/intterms[i]; ++j)
				str += int2term( intterms[i] );
			
			x %= intterms[i];
		}
	
	if ( str.size() == 0 )
		error("пустой объект Roman_int ( int2romanstr() )");
	
	return str;
}


//Перевод строкового представления римского числа в int, так же проверка корректности строки
int romanstr2int(string str)
{
	//Проверка примитивов (все ли символы допустимы)
	for (char ch : str)
		if ( check_primitives(ch) == false )
			error("найден недопустимый символ '" + to_string(ch) + "' ( romanstr2int() )");
	
	//------------------------------------------------------------------------------------------------------------
	
	int num = 0;	//конечное число
	
	//подсчет термов идущих подряд:
	//	'I', 'X', 'C', 'M' - могут встречаться не более 3ёх раз подряд
	//	'V', 'L', 'D' - могут встречаться не более 1го раза подряд
	int count = 1;
	
	//Проверка строки с чсилом на правильность ввода
	for (int i = 0; i < str.size(); ++i) {
		
		//--------------------------------------------------------------------------------------------------------
		
		//Проверяемый элемент не первый в строке и он равен предыдущему
		if ( i != 0  &&  str[i] == str[i-1] )	++count;
		else									count = 1;
		
		//Больше трёх одинаковых термов подряд для 1, 10, 100, 1000 или более одного для 5, 50, 500
		if ( (str[i] == 'I'  ||  str[i] == 'X'  ||  str[i] == 'C'  ||  str[i] == 'M')  &&  count > 3 )
			error("найдена неправильная последовательность чисел: более трёх повторений символа '" + \
														to_string(str[i]) + "' подряд ( romanstr2int() )");
		else if ( (str[i] == 'V'  ||  str[i] == 'L'  ||  str[i] == 'D')  &&  count > 1 )
			error("найдена неправильная последовательность чисел: более одного повторения символа '" + \
														to_string(str[i]) + "' подряд ( romanstr2int() )");
		
		//--------------------------------------------------------------------------------------------------------
		
		string term = "";
		
		switch ( str[i] ) {
			case 'I':
				//не последний символ в строке и след: IV - 4 || IX - 9
				if ( i != str.size()-1  &&  ( str[i+1] == 'V' || str[i+1] == 'X' ) )
				{
					term = to_string(str[i]) + to_string(str[i+1]);
					++i; //перескакиваем через символ
				}
				
				else if ( str[i+1] == 'L'  ||  str[i+1] == 'C'  ||  str[i+1] == 'D'  ||  str[i+1] == 'M' )
					error("найдена неправильная последовательность чисел в позиции '" + to_string(i+1) + "' ( romanstr2int() )");
				
				else	term = to_string(str[i]); // I - 1
				
				break;
			
			
			case 'X':
				//не последний символ в строке и след: XL - 40 || XC - 90
				if ( i != str.size()-1  &&  ( str[i+1] == 'L'  || str[i+1] == 'C' ) )
				{
					term = to_string(str[i]) + to_string(str[i+1]);
					++i; //перескакиваем через символ
				}
				
				else if ( str[i+1] == 'D'  ||  str[i+1] == 'M' )
					error("найдена неправильная последовательность чисел в позиции '" + to_string(i+1) + "' ( romanstr2int() )");
				
				else	term = to_string(str[i]); // X - 10
				
				break;
			
			
			case 'C':
				//не последний символ в строке и след:CD - 400 || CM - 900
				if ( i != str.size()-1  &&  ( str[i+1] == 'D'  || str[i+1] == 'M' ) )
				{
					term = to_string(str[i]) + to_string(str[i+1]);
					++i; //перескакиваем через символ
				}
				
				else	term = to_string(str[i]); // C - 100
				
				break;
			
			
			case 'V': case 'L': case 'D': case 'M':
				term = to_string(str[i]);
				break;
		}
		
		//-----------------------------------------------------------------------------------------------------------------------
		
		//Поможет избежать ситуаций таких как следующая: XCX
		string s = str.substr(i+1);
		if ( term.size() > 1  &&  s.size() > 0 ) {
			if ( s.size() > 1 )
				s = to_string(s[0]) + to_string(s[1]);
			
			if ( romanstr2int(s) >= term2int( to_string(term[0]) ) )
				error("найдена неправильная последовательность чисел в позиции '" + to_string(i+1) + "' ( romanstr2int() )");
		}
		
		//-----------------------------------------------------------------------------------------------------------------------
		
		if ( num != 0 && (num < term2int( term )  ||  term == "") )
			error("найдена неправильная последовательность чисел в позиции '" + to_string(i+1) + "' ( romanstr2int() )");
		else
			num += term2int( term );
	}
	
	return num;
}

//------------------------------------------------------------------------------------------------------------

ostream& operator<<(ostream& ost, const Roman_int& ri)
{
	ost << int2romanstr( ri.as_int() );
	return ost;
}

istream& operator>>(istream& ist, Roman_int& ri)
{
	string str {""};
	char ch {'F'};
	
	while ( ist.get(ch)  &&  isalpha(ch) )
		if ( !check_primitives(ch) )	break;
		else							str += ch;
	
	
	//Достигли конца файла, но при этом число было считано
	if ( str.size() != 0  &&  ist.eof() )			ist.clear();
	
	//Если ни одного символа не получили - возвращаем конец файла
	else if ( ist.eof()  ||  ist.fail() )			return ist;
	
	//Поток в состоянии bad (крит. ошибка)
	//else if ( ist.bad() )
	//	error("поток ввода при считывании значения типа Roman_int был повреждён");
	
	//Пропуск пустых строк и пробелов в случае когда число не было считано
	else if ( str.size() == 0  &&  isspace(ch) )	return operator>>(ist, ri);
	
	//Римское число не было считано
	else if ( str.size() == 0 )
	{
		ist.unget();
		ist.clear(ios_base::failbit);
		error("неизвестный символ '" + to_string(ch) + "' ( ввод значения типа Roman_int )");
	}
	
	//Всё хорошо возвращаем последний символ, если он не является пробелом, табуляцией или переходом на новую строку
	else if ( !isspace(ch) )						ist.unget();
	
	
	ri = Roman_int( str ); //Разбитие строки на отдельные термы и проверка корректности при инициализации строкой
	
	return ist;
}

//------------------------------------------------------------------------------------------------------------


//==!===!===!===!===!===!===!===!===!===!===!===!= Сравнение ==!===!===!===!===!===!===!===!===!===!===!===!=
bool operator==(const Roman_int& a, const Roman_int& b) {
	return		a.as_int()==b.as_int();
}

bool operator!=(const Roman_int& a, const Roman_int& b) {
	return		!(a==b);
}
//==!===!===!===!===!===!===!===!===!===!===!===!= Сравнение ==!===!===!===!===!===!===!===!===!===!===!===!=


//+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/% Математические операции +-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%

//сложение (Roman_int+Roman_int)
Roman_int operator+(const Roman_int& a, const Roman_int& b)
{
	int res = a.as_int() + b.as_int();
	
	if ( a.as_int() + b.as_int() > 3999 )
		error("результат вне диапазона римских чисел (> 3999) " + to_string(a.as_int()) + " + " + \
							to_string(b.as_int()) + " = " + to_string(res) + " ( Roman_int operator+() )");
	
	return Roman_int( res );
}

//вычитание (Roman_int-Roman_int)
Roman_int operator-(const Roman_int& a, const Roman_int& b)
{
	int res = a.as_int() - b.as_int();
	
	if ( a.as_int() - b.as_int() < 1 )
		error("отрицательный или нулевой результат " + to_string(a.as_int()) + " - " + to_string(b.as_int()) + \
															" = " + to_string(res) + " ( Roman_int operator-() )");
	
	return Roman_int( res );
}

// Roman_int*Roman_int
Roman_int operator*(const Roman_int& a, const Roman_int& b)
{
	double res = double(a.as_int()) * b.as_int();
	
	if ( res > 3999  ||  res < 1  || res != int(res) )
		error("результат вне диапазона римских чисел ( <1 или >3999 или вне диапазона integer ) " + to_string(a.as_int()) + \
										" * " + to_string(b.as_int()) + " = " + to_string(res) + " ( Roman_int operator*() )");
	
	return Roman_int( int(res) );
}

// Roman_int/Roman_int
Roman_int operator/(const Roman_int& a, const Roman_int& b)
{
	int res = a.as_int() / b.as_int();
	return Roman_int( res );
}
	
Roman_int operator%(const Roman_int& a, const Roman_int& b) {	// Roman_int%Roman_int
	int res = a.as_int() % b.as_int();
	return Roman_int( res );
}

//+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/% Математические операции +-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


//инициализация констант
/*Symbol_table::Symbol_table()
{
	vector_names.push_back( Variable("pi", 3.1415926535, true) );
	vector_names.push_back( Variable("e", 2.7182818284, true) );
	vector_names.push_back( Variable("k", 1000, true) );
}*/

void Symbol_table::table_out() //Вывод на экран всех констант и переменных подряд
{
	for (int i = 0; i < vector_names.size(); ++i) {
		cout << '\t' << i+1 << ". "; 
		
		if (vector_names[i].constant)		cout << "const ";
		else								cout << "var   ";
		
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
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


const string roman_instr = "I-MMMCMXCIX (обозначения: I = 1 ; V = 5 ; X = 10 ; L = 50 ; C = 100 ; D = 500 ; M = 1000)";
const string HELP_INSTR = "\n\nВводите выражения в формате: ЧИСЛО ОПЕРАТОР ЧИСЛО."
			"\nЧисла могут быть с любым знаком, целыми и с десятичной частью "
			"(ТОЧКА - десятичный разделитель), а так же римские от 1 до 3999 " + \
									roman_instr + \
			". Для завершения ввода (подтверждения) нажмите клавишу ENTER.\n\n"
			
			"Доступные операции:\n\n"
			"---------------------------------------------------\n"
			"|    +    |   -    |     *     |    /   |    %    |\n"
			"----------+--------+-----------+--------+---------|\n"
			"|         |        |           |        | остаток |\n"
			"| сложить | отнять |  умножить | делить |   от    |\n"
			"|         |        |           |        | деления |\n"
			"---------------------------------------------------\n"
			
			"------------------------------------------------------------\n"
			"|   ()   |    {()}   |    ^     |   ЧИСЛО!  |  sqrt(ЧИСЛО) |\n"
			"---------+-----------+----------+-----------+--------------|\n"
			"|        | вложенные | возвести |           |  квадратный  |\n"
			"| скобки |   скобки  |     в    | факториал |    корень    |\n"
			"|        |           |  степень |           |   из числа   |\n"
			"------------------------------------------------------------\n"
			
			"\nПример:\n> -2+(2*2) \n= II\n\n"
			
			"В программе предусмотренны следующие константы (число Пи, число e и "
			"множитель тысяча):\n pi = 3.1415926535\n e = 2.7182818284\n k = 1000\n\n"
			
			"Имеется также возможность объявлять и применять свои переменные (#) "
			"и константы ($), которые задаются единожды без возможности изменения. "
			"Имя должно начинаться с буквы, может содержать буквы, цифры и символ '_'."
			"\nПример объявления переменной:\n> #var1=100 \n= C\n"
			"\nПример изменения переменной:\n> var1 =V+.79 \n= 5.79\n"
			"\nПример объявления константы:\n> $ con_1 = X \n= X\n"
			"\nПример применения:\n> var1-2 \n= 3.79\n\n"
			"   out - вывод всех констант и переменных в памяти программы\n"
			"   help - вызов справки\n   quit - для быстрого выхода\n\n"; //ИНСТРУКЦИИ

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
	while (cin >> ch)
		if (ch == c || ch == '\n') return;  // || ch == '\n'
}

//Член putback() помещает аргумент в буфер своей ф-ции Token_stream:
void Token_stream::putback(Token t)
{
	if (full)
		error("Ошибка ф-ции putback(): попытка заполнить уже полный буфер");

	buffer = t;		//копировать t в буфер
	full = true;	//теперь буфер полон
}

Token Token_stream::get()
{
	 if (full) { //Если в буфере уже имеется объект типа Token..
		//..удаляем его из буфера (помечаем буфер как пустой, т.е. доступный для перезаписи)
		full = false;
		return buffer;
	}

	char ch = ' ';
	cin.get(ch); //Съедаем пробелы while ( isspace(ch) && ch != PRINT && !cin.eof() ) 
	
	if (cin.eof())   return Token(QUIT);// throw CTRL_Z_throw {}; //Закрыть программу? Да или Нет (д / н)
	
	else if (ch == PRINT) return Token(PRINT); //для завершения вычислений и немедленного вывода ответа на экран
	cin.unget();
	
	cin >> ch;		//замечание: оператор >> пропускает пустые пространства
					//(пробел, символ новой строки, табуляция и т.д.)
	
	switch (ch)
	{
		case LET: case CONSTANT: //Проверка на то является ли имя переменной римским числом
		case '=': //переменные и константы
		case POW: //степень
		case '!': //факториал
		case '(': case ')':
		case '{': case '}':
		case '+': case '-': case '*': case '/': case '%':
			return Token(ch);        //Каждый символ представляет сам себя
		
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
			
			if ( isalpha(ch) ) { //Если первый символ - буква (имя может начинаться только с буквы, но так же может и римское число)
				str += ch;
				
				while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_'))
										//буква,         цифра    или нижнее подчеркивание
					str += ch;
				
				cin.unget(); //возврат каретки на 1 символ назад, т.к. он не имеет отношения к имени
				
				//-------------------------------------------------------------------------------------------------------------------------
				int count = 0;
				for (char ch : str)
					if ( check_primitives(ch) )		++count;
				
				if ( count == str.size() ) {
					for (int i = str.size()-1; i >= 0; --i)
						cin.putback(str[i]);
					
					Roman_int ri;
					cin >> ri;
					
					return Token( NUMBER, ri.as_int() ); // return Token( NUMBER, Roman_int(str).as_int() );
				}
				//-------------------------------------------------------------------------------------------------------------------------
				
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