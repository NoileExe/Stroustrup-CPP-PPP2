/*
	Ввод и сравнение двух целочисленных значений, а также проведение простейших
	математических операций с ними
*/

#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Пожалуйста, введите два любых числа (после ввода каждого нажмите Enter):\n";
	double val1 = 0;
	double val2 = 0;
	cin >> val1 >> val2;
	cout << '\n';
	
	if (val1 == val2)
	{
		cout << "Значения равны!\n";
	}
	else if (val1 > val2)
	{
		cout << "Максимальное = " << val1 << '\n'
			 << " Минимальное = " << val2 << '\n';
	}
	else
	{
		cout << "Максимальное = " << val2 << '\n'
			 << " Минимальное = " << val1 << '\n';
	}
	
	cout << val1 << " + " << val2 << " = "<< (val1 + val2) << '\n'
		 << val1 << " - " << val2 << " = "<< (val1 - val2) << '\n'
		 << val1 << " X " << val2 << " = "<< (val1 * val2) << '\n'
		 << val1 << " / " << val2 << " = "<< (val1 / val2) << '\n';
	
	keep_window_open();
	return EXIT_SUCCESS;
}
