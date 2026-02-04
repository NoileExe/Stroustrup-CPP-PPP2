
#include "vectors.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

void enter_NUMs (vector<double>& n); //заполнение вектора

int main()
{
	cout << "Следуйте указаниям программы. Для завершения ввода на ввод подайте"
			" комбинацию CTRL+Z.\n";
	
	vector<double> numnums;
	
	enter_NUMs(numnums);
	if (cin.eof() && numnums.size() == 0) {
		cout << "\n\nВыход инициализирован пользователем.\n\n";
		press_Enter_key();
		return 0;
	}
	
	struct_minmaxmid s_mmmm = search_4m(numnums);
	
	cout << "\n\nМаксимальный элемент вектора:   "	<< s_mmmm.max	<< "\n";
	cout << "\nМинимальный элемент вектора:    "	<< s_mmmm.min	<< "\n";
	cout << "\nСреднее арифметическое вектора: "	<< s_mmmm.mid	<< "\n";
	cout << "\nМедиана для элементов вектора:  "	<< s_mmmm.medi	<< "\n\n";
	
	keep_window_open("~~");
	return EXIT_SUCCESS;
}

void enter_NUMs (vector<double>& n)
{
	double num;
	
	for (int i = 0;  ; ++i) {
		cin.clear();
		cout << "\nВведите число №" << i+1 << ": ";
		
		cin >> num;
		
		if (cin.eof()) return;
		else if (cin.fail()) {
			cout << "\n\nТребуется коректное число с плавающей дес.точкой.\n\n";
			cin.clear();
			--i;
		}
		else if (isinf(num)) {
			cout << "\n\nЗначение вышло за пределы типа DOUBLE.\n\n";
			cin.clear();
			--i;
		}
		else n.push_back(num);
		
		if (cin.get() != '\n')
			while (cin.get() != '\n') cin.ignore();
	}
}
