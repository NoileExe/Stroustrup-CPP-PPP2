//Данная программа вычисляет и выводит все простые числа от 1 до введённого пользователем

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Данная программа вычисляет и выводит все простые числа от 1 до вве"
		 << "дённого пользователем ПОЛОЖИТЕЛЬНОГО ЦЕЛОГО числа.\n\n";
	
	vector<int> prime_nums; //Вектор простых чисел
	int max = 1;

TryAgain:	
	cout << "Введите верхнюю границу для поиска простых чисел: ";
	cin >> max;
	if (max < 2) {
		cout << "\nОШИБКА! Введённое число должно быть целым и больше единицы";
		goto TryAgain;
	}
	
	for (int i = 1; i<=max; ++i) {
		for (int j = 1; j<=i; ++j) {
			if ( (i == 1) || ((j > 1) && ((i%j) == 0) && (j < i)) )
			/*Если текущее число единица ИЛИ j не единица И числа делятся без
			остатка И j меньше (не равно) i*/
				break;
			else if ( (i > 1) && (j == i) )
				prime_nums.push_back(i);
		}
	}
	
	cout << "\nПростые числа в промежутке от 1 до " << max << ":\n";
	
	for (int i = 0; i<prime_nums.size(); ++i)
		cout << prime_nums[i] << "\n";
	
	cout << "\n\n";
	
	press_Enter_key();
	return EXIT_SUCCESS;
}
