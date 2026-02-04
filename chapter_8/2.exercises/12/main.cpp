
#include "vectors.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

void enter_STRINGs (vector<string>& s);

int main()
{
	cout << "Следуйте указаниям программы. Для завершения ввода на ввод подайте"
			" комбинацию CTRL+Z.\n";
	
	vector<string> vstr;
	vector<int> count;
	
	enter_STRINGs(vstr);
	if (cin.eof() && vstr.size() == 0) {
		cout << "\n\nВыход инициализирован пользователем.\n\n";
		press_Enter_key();
		return 0;
	}
	
	alpha_count(vstr, count); //В вектор count запишутся длины строк из вектора vstr
	
	//Везде выводимый ИНДЕКС+1, т.к. отсчёт индексов в веторе начинается с нуля
	cout << "\n\nСамая короткая строка - строка №" << minv_int(count)+1 << ": " 
		 << vstr[minv_int(count)] << "\n";
	cout << "\n\nСамая длинная строка - строка №" << maxv_int(count)+1 << ": " 
		 << vstr[maxv_int(count)] << "\n";
	cout << "\n\nЛексикографически первая (по алфавиту) строка - строка №"  
		 << minv_str(vstr)+1 << ": " << vstr[minv_str(vstr)] << "\n";
	cout << "\n\nЛексикографически последняя (по алфавиту) строка - строка №" 
		 << maxv_str(vstr)+1 << ": " << vstr[maxv_str(vstr)] << "\n\n";
	
	
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
		
		cout << "\nВведите строковое знач. #" << i+1 << ": ";
		
		cin >> str; //ввод только одного слова
		
		if (cin.eof()) return; //Если CTRL+Z, то завершаем ввод
		else if (cin.fail()) {
			cout << "\n\nНекорректный ввод.\n\n";
			cin.clear();
			--i;
		}
		else s.push_back(str);
		
		while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
	}
}
