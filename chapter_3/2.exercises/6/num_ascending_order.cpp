//Ввод чисел и выведение на экран их в порядке возрастания

#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Данная программа выводит в порядке возрастания числа через запятую\n\n"
		 << "Пожалуйста, введите три целых числа (после ввода каждого нажмите Enter):\n";

	//вводимые числа
	int num1 = 0;
	int num2 = 0;
	int num3 = 0;
	
	int buff = 0; //буфер обмена
	cin >> num1 >> num2 >> num3;
	
	if (num1 > num2)
	{
		buff = num1;
		num1 = num2;
		num2 = buff;
	}
	
	if (num1 > num3)
	{
		buff = num1;
		num1 = num3;
		num3 = buff;
	}
	
	if (num2 > num3)
	{
		buff = num2;
		num2 = num3;
		num3 = buff;
	}
	
	cout << '\n' << num1 << ", " << num2 << ", " << num3;
	
	keep_window_open();
	return EXIT_SUCCESS;
}
