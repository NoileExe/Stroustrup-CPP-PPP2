
#include "money.h"
#include <yes_or_no.h>
#include <console_encoding.h>


//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
{
	while (true)
	try {
		using namespace nmsp_Money;
	
		Money money1;
		
		Money money2;
		cin >> money2;
		
		Money money3(10003);
		
		cout << "\n money1: " << money1
			 << "\n money2: " << money2
			 << "\n money3 ret_summ(): " << money3.ret_summ()
			 << "\n money3 ret_dbl_summ(): " << money3.ret_dbl_summ();
			
		press_Enter_key();
		
		money1 = money2;
		
		if (money1 == money2)
			cout << "\n\n money1: " << money1;
		
		if (Y_or_N("Закрыть программу?"))	return 0;
	}

	catch (int a) { //class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z
		if (Y_or_N("Закрыть программу?"))	return 1001;
	}

	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << e.what() << '\n';
		//cerr << "Ошибка: " << e.what() << '\n';
		if (Y_or_N("Закрыть программу?"))	return 1002;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		if (Y_or_N("Закрыть программу?"))	return 1003;
	}
}