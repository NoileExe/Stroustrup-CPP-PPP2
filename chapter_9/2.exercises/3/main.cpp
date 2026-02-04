
#include "names_ages.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
try
{
	names_n_ages::Name_pairs my_family;
	names_n_ages::Name_pairs my_family1;

	cout << "Следуйте указаниям программы. Для завершения ввода на ввод подайте"
			" комбинацию CTRL+Z.\n\n";

	my_family.read_data();
	cout << "Не сортированно (1ый объект):\n" << my_family;

	press_Enter_key(true);

	my_family.sort();
	cout << "Сортированно (1ый объект):\n" << my_family;


	//----------------------------------------------------------------------------
	my_family1.read_data();
	my_family1.sort();
	cout << "Сортированно (2ой объект):\n" << my_family1;

	if (my_family1 == my_family)		cout << "Объекты равны!\n\n";
	else if (my_family1 != my_family)	cout << "Объекты НЕ равны!!!\n\n";
	else								cout << "Что-то пошло не так!!!\n\n";

	press_Enter_key();

	my_family1 = my_family;
	if (my_family1 == my_family)		cout << "Объекты равны!\n\n";
	else if (my_family1 != my_family)	cout << "Объекты НЕ равны!!!\n\n";
	else								cout << "Что-то пошло не так!!!\n\n";
	
	cout << "После операции 2ой_объект = 1ый_объект (2ой объект):\n" << my_family1;
	//----------------------------------------------------------------------------

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