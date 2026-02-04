
#include "vectors.h"
#include <yes_or_no.h>
#include <console_encoding.h>


ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

void enter_PandW (vector<double>& price, vector<double>& weight); //заполнение векторов

int main()
{
	cout << "Следуйте указаниям программы. Для завершения ввода на ввод подайте"
			" комбинацию CTRL+Z.\n";
	
	vector<double> price;
	vector<double> weight;
	
	enter_PandW(price, weight);
	if (cin.eof() && weight.size() == 0) {
		cout << "\n\nВыход инициализирован пользователем.\n\n";
		press_Enter_key();
		return 0;
	}
	
	
	cin.clear();
	
	cout << "\n\nОбщий чек: " << common_check(price, weight) << "\n\n";
	
	keep_window_open("~~");
	return EXIT_SUCCESS;
}

void enter_PandW (vector<double>& price, vector<double>& weight)
{
	double num;
	
	for (int i = 0;  ; ++i) {
		cin.clear();
		cout << "\n\nВведите цену товара №" << i+1 << ": ";
		
		cin >> num;
		
		if (cin.eof()) return;
		else if (cin.fail()) {
			cout << "\n\nТребуется коректное число с плавающей дес.точкой.\n\n";
			cin.clear();
			--i;
			goto END_of_FOR;
		}
		else price.push_back(num);
		
		while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
			
		cin.clear();
		cout << "\nВведите кол-во/вес товара №" << i+1 << ": ";
		
		cin >> num;
		
		if (cin.eof()) return;
		else if (cin.fail()) {
			cout << "\n\nТребуется коректное число с плавающей дес.точкой.\n\n";
			cin.clear();
			--i;
		}
		else weight.push_back(num);
		
	END_of_FOR:
		while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
	}
}
