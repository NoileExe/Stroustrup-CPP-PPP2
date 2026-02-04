

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//целое число с указанием системы счисления
class ns_int {
public:
	ns_int() :num(0), found(10) { }					//создаём ns_int равный нулю с основанием 10
	ns_int(int n) :num(n), found(10) { }			//создаём ns_int равный указанному числу с основанием 10
	ns_int(int n, int s) :num(n), found(s) { }		//создаём ns_int равный указанному числу с указанным основанием
	
	int num_sys() const		{ return found; }
	operator int () const	{  return num;  }
private:
	int num;		//само число
	int found;		//система счисления
};

//Оператор ввода для объектов класса ns_int
//Определяет разрядность введённого числа и само число
istream& operator>>(istream& ist, ns_int& ni)
{
	int num = 0;
	bool neg = false;
	int found = 10;
	
	//Считываем число ввиде слова, чтобы потом не возвращать символы в поток
	string str;
	ist >> str;
	
	if ( ist.eof() )	return ist;
	
	//-------------------------------------------------------------------------------
	
	//Определяем отрицательное ли число
	if ( str[0] == '-' )	{ str.erase(0,1);	neg = true; }
	
	//-------------------------------------------------------------------------------
	
	//Определяем систему счисления и запоминаем её в переменную found
	if ( str.size() == 1 )
		found = 10;
	
	else if ( str[0] == '0' )
		if ( str[1] == 'x' )	found = 16;
		else					found =  8;
	
	else	found = 10;
	
	//-------------------------------------------------------------------------------
	
	//Поиск ошибок в ведённой строке
	for (char ch : str)
		if ( !isxdigit(ch)  &&  ch!='x' )
			{ ist.clear(ios_base::failbit);		return ist; }
	
	//-------------------------------------------------------------------------------
	
	//Считываем само число в той системе счисления, в которой оно указано пользователем
	istringstream is {str};
	is.unsetf(ios::dec|ios::oct|ios::hex);
	is >> num;
	
	if ( neg ) num *= -1;
	
	ni = ns_int {num, found};
	
	
	return ist;
}


int main() {
	while(true)
	try {
		cout << showbase;
		
		while ( true )
		{
			cout << "\nВведите число в 10тичной/8ричной(0 вначале числа)/16тиричной(0x вначале числа) системе счисления:\n";
			
			ns_int num = 0;
			cin >> num;
			
			if ( cin.eof() )	break;
			else if ( !cin )	error ("введённое не является числом");
			
			while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
			
			
			if ( num.num_sys() == 8 )
				cout << oct << int(num) << "\t(8миричное)\tпревращается в 10тичное\t"  << dec << int(num) << '\n';
			
			else if ( num.num_sys() == 10 )
				cout << dec << int(num) << "\t(10тичное)\tпревращается в 10тичное\t"   << dec << int(num) << '\n';
			
			else if ( num.num_sys() == 16 )
				cout << hex << int(num) << "\t(16тиричное)\tпревращается в 10тичное\t" << dec << int(num) << '\n';
		}
		
		if ( Y_or_N(quit_question) )	return 0;
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		
		if ( Y_or_N(quit_question) )	return 1001;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		
		if ( Y_or_N(quit_question) )	return 1002;
	}
}