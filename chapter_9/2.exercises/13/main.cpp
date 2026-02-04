
#include <console_encoding.h>
#include <yes_or_no.h>
#include "rational.h"

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
{
	while (true)
	try {
		using namespace Rnums;
		
		Rational first_R;		//Инициализация пустого объекта Rational
		Rational second_R {1};	//Инициализация объекта Rational только целой частью
		
		cin >> first_R;
	
		cout << "\nПервоначальная дробь: " << first_R
			 << "\nВ виде десятичной дроби: " << first_R.ret_dbl()
			 << "\nВыделеная целая часть: " << unmax_it(first_R)
			 << "\nСокращенная дробь: " << minimize_it(first_R)
			 << "\nНеправильная дробь: " << maximize_it(first_R);
	
		press_Enter_key();
		
		cout << "\n\nВВЕДИТЕ ПЕРВУЮ ДРОБЬ\n";
		cin >> first_R;
		
		cout << "\n\nВВЕДИТЕ ВТОРУЮ ДРОБЬ\n";
		cin >> second_R;
		
		if (first_R == second_R)
			cout << "\n\nДроби равны";
		else
			cout << "\n\nДроби НЕравны";
		
		cout << "\nСложение : " << first_R << " + " << second_R << " = " << first_R+second_R << " = " << unmax_it( minimize_it(first_R+second_R) )
			 << "\nВычитание: " << first_R << " - " << second_R << " = " << first_R-second_R << " = " << unmax_it( minimize_it(first_R-second_R) )
			 << "\nУмножение: " << first_R << " * " << second_R << " = " << first_R*second_R << " = " << unmax_it( minimize_it(first_R*second_R) )
			 << "\nДеление  : " << first_R << " / " << second_R << " = " << first_R/second_R << " = " << unmax_it( minimize_it(first_R/second_R) );
		
		if (Y_or_N("Закрыть программу?"))	return 0;
	}

	catch (int a) { //class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z
		if (Y_or_N("Закрыть программу?"))	return 1001;
	}

	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		if (Y_or_N("Закрыть программу?"))	return 1002;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		if (Y_or_N("Закрыть программу?"))	return 1003;
	}
}