
#include "ha.h"
#include <yes_or_no.h>
#include <console_encoding.h>


ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

int main()
{
	while (true) {
		try
		{
			vector<int> v_fibo;
			int n = 0;
			int first = 1;
			int second = 0;
			
			//Кол-во чисел в задваемой последовательности не менее чем кол-во семян
			//							(2ух чисел от которых начинаются вычисления)
			while (n <= 2)
			{
				cout << "\n\nВведите кол-во (больше 2ух) чисел Фибоначчи:" << endl;
				
				cin >> n;
				
				if ( !cin || cin.eof() )
					while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
				
				if (n <= 2)
					cout << "!!!Кол-во должно быть больше 2ух!!!" << endl;
			}
			
			cout << "\n\n";
			
			//Семя (2 числа от которых начинаются вычисления)
			while (first > second || !cin || cin.eof())
			{
				if ( !cin || cin.eof() )
					while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
				
				cout << "\n\nВведите через пробел первые 2 числа (2ое >= 1ое):" << endl;
				
				cin >> first;
				
				if (cin.eof())	cin.clear();
				else
				{
					cin >> second;
					
					if (cin.eof())	cin.clear();
					else if (first > second)
						cout << "!!!Первое не должно быть больше 2го!!!" << endl;
				}
			}
			
			
			fibonacci(first, second, v_fibo, n);
			
			string str = "\n\nПервые числа последовательности Фибоначчи";
			print(v_fibo, str);
			
			if ( Y_or_N("Закрыть программу?") )
			{
				keep_window_open("~~");
				return EXIT_SUCCESS;
			}
		}
		catch (exception& e) { //Для системных исключений при работе с программой
			cerr << "Ошибка: " << e.what() << '\n';
			
			if (Y_or_N("Закрыть программу?"))	return 0; //1
		}
		catch (...) { //Для непредвиденных исключений
			cerr << "Упс! Неизвестное исключение!\n";
			
			if (Y_or_N("Закрыть программу?"))	return 0; //4
		}
	}
}
