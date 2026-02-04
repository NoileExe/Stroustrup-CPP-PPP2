
#include "Chrono.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
{
	Chrono::Date today;
	
	while (true)
	try {
		using namespace Chrono;
		
		today.ScrOut_Dates();
		
		press_Enter_key(true);
		
		today = Date (19, Month::may, 1963);
		today.ScrOut_Dates();
		
		press_Enter_key();
		
		today = Date (18, 2, 2024, 1, Month::apr, 1945);
		today.ScrOut_Dates();
		
		press_Enter_key();
		
		today = Date (1, 5, 1945, 18, Month::mar, 2024);
		today.ScrOut_Dates();
		
		press_Enter_key();
		
		//------------------------------------------------------------------------------
		
		Date newDate;
		cin >> newDate;
		newDate.ScrOut_Dates();
		
		press_Enter_key();
		
		newDate.Chg_begin_date();
		cout << "\nИзменение КОНЕЧНОЙ даты.";
		cin >> newDate;
		newDate.ScrOut_Dates();
		
		if (Y_or_N("Закрыть программу?"))	return 0;
		//press_Enter_key();
	}

	catch (Chrono::CTRL_Z_throw) { 
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

//------------------------------------------------------------------------------
