
#include "Chrono.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			using namespace Chrono;

			Date today(1963, Month::may, 19);
			
			cout << "\nФормат ввода: '(год,месяц,число)' пробелы не учитываются\n"
					"Введите дату: ";
			
			cin >> today;

			int n = 0;
			cout << "Сколько дней прибавить: ";
			cin >> n;
			
			if (cin.eof())
				throw CTRL_Z_throw {};
			else if (cin.fail())
				error("неверный ввод ( main() )");

			Date tomorrow = today;
			tomorrow.add_days(n);

			cout << "\nОбъект 'today' "		<<	today		<< endl;
			cout << "Объект 'tomorrow' "	<<	tomorrow	<< "\n\n";

			if (Y_or_N("Закрыть программу?"))	return 0;
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
}

//------------------------------------------------------------------------------
