//Перевод слова в число

#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Программа принимает слово от пользователя и выводит число.\n"
		 << "Ввод доступен для чисел 0-4 на АНГЛИЙСКОМ языке в нижнем регистре.\n\n"
		 << "Чтобы завершить работу с программой нажмите комбинацию клавиш "
		 << "CTRL+Z и затем клавишу Enter.\n\n"
		 << "Вводите числа словом (нажмите Enter чтобы подтвердить ввод):\n";
	
	string one_word = "";
	while (cin >> one_word) //Повторяем след. инструкции пока производится ввод
	{
		if (one_word == "zero")
			cout << "0\n\n";
		else if (one_word == "one")
			cout << "1\n\n";
		else if (one_word == "two")
			cout << "2\n\n";
		else if (one_word == "three")
			cout << "3\n\n";
		else if (one_word == "four")
			cout << "4\n\n";
		else cout << "Я не знаю такого числа!\n\n";
	}
	
	keep_window_open();
	return EXIT_SUCCESS;
}
