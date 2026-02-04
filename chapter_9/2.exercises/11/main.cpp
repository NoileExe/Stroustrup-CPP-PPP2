
#include "Chrono.h"
#include <yes_or_no.h>
#include <console_encoding.h>


//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
{
	Chrono::Date test_date_obj;

	while (true)
	try {
		using namespace Chrono;
		
		cout << "\nТекущая дата: "  <<   currentDate()  << "\n\n";
		
		press_Enter_key();
		
		//------------------------------------------------------------------------------
		
		cout << "\nФормат ввода: 'число.месяц.год' пробелы не учитываются\n"
			"\nВведите дату: ";
	
		cin >> test_date_obj;
		
		cout << "\nЭто " << day_of_week(test_date_obj)
			 << "\nДень #" << day_of_year(test_date_obj)
			 << "\nНеделя #" << week_of_year(test_date_obj)
			 << "\nСледующий рабочий день: "  << next_workday(test_date_obj)
			 << "\nЭто " << day_of_week(next_workday(test_date_obj));
		
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
