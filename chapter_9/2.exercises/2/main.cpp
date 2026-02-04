
#include "names_ages.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
try
{
	Name_pairs my_family;

	cout << "Следуйте указаниям программы. Для завершения ввода на ввод подайте"
			" комбинацию CTRL+Z.\n\n";

	my_family.read_data();
	my_family.print();

	cout << "Нажмите Enter" << endl;
	
	while (cin.get() != '\n') cin.clear();

	my_family.sort();
	my_family.print();

	keep_window_open("~~");
	return 0;
}

catch (exception& e) { //Для системных исключений при работе с программой
	cerr << "Ошибка: " << e.what() << '\n';
	press_Enter_key();
	return 1001;
}

catch (...) { //Для непредвиденных исключений
	cerr << "Упс! Неизвестное исключение!\n";
	press_Enter_key();
	return 1003;
}
