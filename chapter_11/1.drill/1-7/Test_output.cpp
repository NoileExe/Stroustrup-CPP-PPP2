

#include <time.h>
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

int currentYear()
//получение текущей даты по системному времени
//Возвращает текущий год
{
	time_t     now = time(0);
	struct tm  tstruct;
	//char       buf[80];
	tstruct = *localtime(&now);
	//strftime(buf, sizeof(buf), "%d.%m.%Y", &tstruct);
	
	return tstruct.tm_year+1900;
}

int main() {
	while(true)
	try {
		int my_birthyear { 1995 };
		int curr_year { currentYear() };
		int age = curr_year - my_birthyear;
		
		cout << "\n Система счисления\t Год рождения\t Возраст\n" << showbase << //noshowbase
				  "     Десятичная   \t  " << dec << my_birthyear << "\t\t   " << age << '\n' << \
				  "    Восьмиричная  \t  " << oct << my_birthyear << "\t\t   " << age << '\n' << \
				  " Шестнадцатиричная\t  " << hex << my_birthyear << "\t\t   " << age;
		
		if ( Y_or_N(quit_question) )	return 0;
		//keep_window_open("~~");
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