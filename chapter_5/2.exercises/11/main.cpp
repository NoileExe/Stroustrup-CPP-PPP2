//Программа выводит последовательность Фибонначи в пределах int

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Программа выводит последовательность Фибонначи в пределах типа INT"
			".\n\n";
	
	double prev = 0, next = 1, buff = prev;
	
	while (int(next) == next) { //(next > 0)
		cout << next << " ";
		
		buff = prev; //Запоминаем предыдущий
		prev = next; //Пред. равен текущему
		next += buff; //Текущий равен 
	}
	
	cout << "\n\nВышли за диапазон INT! Вычисление завершено.";
	
	cout << "\n\n"; 
	press_Enter_key();
	return EXIT_SUCCESS;
}
