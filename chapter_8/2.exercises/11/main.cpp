
#include "vectors.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

void enter_STRINGs (vector<string>& s); //заполнение вектора
const string quitkey = "expensive";

int main()
{
	cout << "Следуйте указаниям программы. Для завершения ввода на ввод подайте"
			" комбинацию CTRL+Z. Строка '" << quitkey << "' для завершения вывода "
			"вектора на экран.\n";
	
	vector<string> vstr;
	
	enter_STRINGs(vstr);
	if (cin.eof() && vstr.size() == 0) {
		cout << "\n\nВыход инициализирован пользователем.\n\n";
		press_Enter_key();
		return 0;
	}
	
	cout << "\n\nprint_until_s: ";
	print_until_s(vstr, quitkey);
	
	cout << "\n\nprint_until_ss: ";
	print_until_ss(vstr, quitkey, 3);
	
	keep_window_open("~~");
	return EXIT_SUCCESS;
}

//Заполняет вектор по ссылке переданный в аргументе строковыми значениями введёнными пользователем
void enter_STRINGs (vector<string>& s)
{
	string str;
	
	for (int i = 0; ; ++i) {
		cin.clear();
		str = "";
		
		cout << "\nВведите строковое значение #" << i+1 << ": ";
		
		cin >> str; //ввод только одного слова
		
		if (cin.eof())
			return; //Если CTRL+Z, то завершаем ввод
		else if (cin.fail())
		{
			cout << "\n\nНекорректный ввод.\n\n";
			cin.clear();
			--i;
		}
		
		else s.push_back(str);
		
		//Очищаем поток символов cin пока не будет достигнут конец строки
		while (cin.get() != '\n') cin.clear();
	}
}
