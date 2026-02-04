//Данная программа угадывает число загаданное пользователем (от 1 до 100)

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Данная программа угадывает загаданное число\nЗагадайте число от 1 "
		 << "до 100, вводите ответы в форме y или n (Yes и No соотв.), для подт"
		 << "верждения ввода ответа нажмите Enter\n\n";
	
	int lower = 1;		// нижняя граница диапазона
	int upper = 100;	// верхняя граница
	int middle;			// середина

	char answer;

	while (lower < upper)
	{
		middle = (upper + lower) / 2;
		
		answer = ' ';
		while (answer != 'y' && answer != 'n') {
			cout << "Ваше число меньше или равно " << middle << "? (y/n)";
			cin >> answer;
		}
		
		/*do
		{
			cout << "Ваше число меньше или равно " << middle << "? (y/n)";
			cin >> answer;
		} while (answer != 'y' && answer != 'n');*/

		if (answer == 'y')
			upper = middle;
		else
			lower = middle + 1;

		cout << "[" << lower << " : " << upper << "]\n";
	}

	cout << "Ваше число  " << upper << "\n";
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}
