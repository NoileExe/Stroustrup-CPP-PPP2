
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------


const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

int main() {
	while(true)
	try {
		double d = 1234567.89;
		
		cout << defaultfloat << d << '\t' << fixed << d << '\t' << scientific << d << '\n';
		
		
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