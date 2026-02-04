/*
	Данная программа принимает на ввод пару Имя Возраст, сверяет с уже внесёнными
	элементами и в случае совпадения выводит ошибку. Так же по окончанию работы при
	вводе "NoName 0" выводит все введённые пары Имя Возраст
*/

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите через пробел (или нажимая Enter после ввода каждого из эле"
		 << "ментов) данные для пары ''ИМЯ ВОЗРАСТ''; для подтверждения ввода н"
		 << "ажмите Enter.\n\nДля завершения ввода и получения на экран всех ра"
		 << "нее введённых пар ''ИМЯ ВОЗРАСТ'' введите пару ''NoName 0''.";

	vector<string> names;	//вектор для запоминания имён
	vector<int> scores;		//вектор для запоминания возраста соответствующего имени
	string n = "NoName";	//текущее имя принятое на ввод 
	int s = 0;				//текущий возраст принятый на ввод

TryAgain:
	
	cout << "\n\nВведите Имя и Возраст: ";
	
	for ( ; cin >> n >> s; ) {
		
		if (n == "NoName" && s == 0) {
			cout << "Ввод завершён пользователем.\n\n";
			break;
		}
		
		for (int i = 0; i < names.size(); ++i) {
			if (n == names[i]) {
				cout << "ОШИБКА! Имя " << n << " уже есть в списке имён под №"
					 << i+1 << ".\nПопробуйте снова.";
				break;
			}
			else if ( i == (names.size()-1) ) {
				names.push_back(n);
				scores.push_back(s);
				break;
			}
		}
		
		if (names.size() == 0) { names.push_back(n);	scores.push_back(s); }
		
		cout << "\n\nВведите Имя и Возраст: ";
	}
	
	if (!cin.good()) { //Если было введено CTRL+Z, CTRL+V или любая др. комбинация
		n = ""; //Обнуляем переменные
		s = 0;
		cin.clear(); //Очищаем поток ввода
		cin.ignore(10000, '\n');
		//cin.ignore();
		goto TryAgain; //Перезапускаем цикл for
	}
	
	cout << "\a\n\n\n\n";
	for (int i = 0; i < names.size(); ++i)
		cout << i+1 << ". " << names[i] << " " << scores[i] << '\n';
	
	cout << "\n\n";
	
	press_Enter_key();
	return EXIT_SUCCESS;
}
