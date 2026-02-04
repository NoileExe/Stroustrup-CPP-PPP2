#include "money.h"
#include <yes_or_no.h>
#include <console_encoding.h>


//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

int main()
{
	while (true)
	try {
		using namespace nmsp_Money;
	
		cout << "\nДоступные валюты: RUB, BYN, UAH, USD, EUR, GBP, CNY, JPY\n\n";
		
		Money money1;
		Money money2( "USD", 100.005 );
		Money money3( Money_Unit("K",1000), 5700 ); //long()
		Money money4( cny, 123.456 );
		
		cout << "\n Пустой объект Money: " << money1
			 
			 << "\n\n Money( 'USD', 100.005 ): " << money2
			 << "\n Money^^^ in RUB: " << convert_to_rub(money2)
			 
			 << "\n\n Money( Money_Unit('K',1000), 5700 ): " << money3
			 << "\n Money^^^ in RUB: " << convert_to_rub(money3)
			 
			 << "\n\n Money(cny, 123.456): " << money4
			 << "\n Money^^^ in RUB: " << convert_to_rub(money4)
			 
			 << "\n\n Курс 'USD': " << money2.ret_unit().exchng_rate
			 
			 << "\n\n Money('USD', 100.005) + Money(cny, 123.456) in RUB: " << money2 + money4
			 << "\n Money('USD', 100.005) + Money(cny, 123.456) in USD: "
							<< setprecision(2) << fixed << (money2+money4).ret_dbl_summ() / money2.ret_unit().exchng_rate
			 << "\n Money('USD', 100.005) + Money(cny, 123.456) in USD (2ой способ): "
							<< convert2unit( money2+money4, "USD" )
			 << "\n Money('USD', 100.005) + Money(cny, 123.456) in USD (3ий способ): "
							<< convert2unit( money2+money4, money2 );
		
		//cout << setprecision(k) << fixed << a << endl; //печать double числа с k знаками после запятой
		
		press_Enter_key();
		
		cin >> money1;
		
		//money1 = money4;
		
		cout << "\n money1: " << money1
			 << "\n Money^^^ in RUB: " << convert_to_rub(money1);
		
		
		if ( Y_or_N(quit_question) )    return 0;
	}

	catch (int a) { //class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z
		if ( Y_or_N(quit_question) )	return 1001;
	}

	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << e.what() << '\n';
		//cerr << "Ошибка: " << e.what() << '\n';
		if ( Y_or_N(quit_question) )	return 1002;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		if ( Y_or_N(quit_question) )	return 1003;
	}
}