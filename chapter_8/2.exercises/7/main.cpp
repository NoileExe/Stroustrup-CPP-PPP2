
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора


void my_error (string error_str)
{
	try		{ throw 'e'; }
	
	catch (...) {
		string str;
		getline(cin, str);
		cin.clear();
		
		cerr << "Ошибка: " << error_str << '\n';
		
		keep_window_open("~~");
		throw;
	}
}

void for_names (vector<string>& n); //заполнение вектора с именами
void for_ages (const vector<string>& n, vector<double>& d); //заполнение вектора возрастов

int main()
{
	cout << "Следуйте указаниям программы. Для завершения ввода имён на ввод "
			"подайте комбинацию CTRL+Z, данная комбинация также при повторном "
			"использовании немедленно завершит программу.\n\n";
	
	vector<string> names;
	vector<string> names_copy;
	vector<double> ages;
	
	for_names(names);
	if ( cin.eof() && names.size() == 0 ) {
		cout << "\n\nВыход инициализирован пользователем.\n\n";
		press_Enter_key();
		return 0;
	}
	
	for_ages(names, ages);
	/*if (cin.eof()) {
		cout << "\n\nВыход инициализирован пользователем.\n\n";
		press_Enter_key();
		return 0;
	}
	
	else*/ if ( names.size() != ages.size() )
		my_error ("Разные размеры векторов!");
	
	
	names_copy = names;
	sort( names.begin(), names.end() );
	cout << "\n\n";
	for (int i = 0;  i < names.size(); ++i) {
		for (int j = 0;  j < names_copy.size(); ++j) {
			if (names[i] == names_copy[j])
				cout << names[i] << " - " << ages[j] << endl;
		}
	} //Цикл вывода пар имя - возраст на экран
	
	keep_window_open("~~");
	return EXIT_SUCCESS;
}

void for_names (vector<string>& n)
//Заполнение пользователем вектора имён
{
	string str;
	char ch;
	
	for (int i = 0;  ; ++i) {
		cin.clear();
		str = "";
		ch = 'a';
		cout << "\nВведите имя #" << i+1 << ": ";
		
		cin.get(ch);
		while ( ( (ch>='А' && ch<='п') || (ch>='р' && ch<='я') || isalpha(ch) ) && !cin.eof() )
		//Посимвольно считываем имя состоящее из букв
		{
			str+=ch;
			cin.get(ch);
		}
		
		if ( cin.eof() ) return; //Если CTRL+Z, то завершаем ввод
		
		else if ( isspace(ch) ) {
			for (int j = 0;  j < n.size(); ++j) {
				if ( str == n[j] ) { //Проверка на повторяемость имени
				    cout << "\n\nТакое имя уже было.\n\n";
				    --i;
				    break;
				}
			}
			
			//Всё перебрали и не встретили повтора
			if ( n.size() == i )	n.push_back(str);
		}
		
		else {
			cout << "\n\nИмя может содержать только буквы.\n\n";
			--i;
		}
		
		if (ch != '\n')
			while (cin.get() != '\n') cin.ignore();
	}
}

void for_ages (const vector<string>& n, vector<double>& d)
//Заполнение пользователем вектора возрастов по имени
{
	double num;
	
	for (int i = 0;  i < n.size(); ++i) {
		cin.clear();
		cout << "\nВведите возраст для " << n[i] << ": ";
		
		cin >> num;
		
		if (cin.eof()) return;
		
		else if (cin.fail()) {
			cout << "\n\nТребуется коректное число с плавающей дес.точкой.\n\n";
			cin.clear();
			--i;
		}
		
		else	d.push_back(num);
		
		if (cin.get() != '\n')
			while (cin.get() != '\n') cin.ignore();
	}
}
