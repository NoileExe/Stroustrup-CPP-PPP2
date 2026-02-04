/*
	Данная программа принимает на ввод имя, сверяет с имеющимися в векторе names и
	выводит количество балов для данного студента; если не найдено сообщает об ошибке.
	При вводе "NoName" выводит все введённые пары имя Оценка (баллы)
*/

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


string ns (int); //ф-ция для заполнения вектора names
int sn (int); //ф-ция для заполнения вектора scores

int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите имена студентов чтобы получить полученные ими оценки. Для "
		 << "подтверждения ввода нажмите Enter.\n\nДля завершения ввода и получ"
		 << "ения на экран всех пар ''ИМЯ ОЦЕНКА'' введите ''NoName''.";
	
	/*
	//вектор для запоминания имён
	vector<string> names = {"Dina", "Anton", "Yura", "Roman", "Lada", "Liya", "Vyacheslav", "Dusya", "Stanislav", "Igor", "Vasiliy", 
							"Vladimir", "Ekaterina", "Ludmila", "Maxim", "Pavel", "Aleksey", "Sergey", "Vladislav", "Rostislav"};
	
	//вектор для запоминания возраста соответствующего имени
	vector<int> scores = {5, 4, 3, 4, 5, 5, 4, 4, 5, 4, 4, 2, 4, 5, 4, 3, 5, 3, 4, 4};
	*/
	
	vector<string> names; //вектор для запоминания имён
	vector<int> scores; //вектор для запоминания возраста соответствующего имени
	
	for (int i = 0; i < 20; ++i)
	{
		names.push_back( ns(i) );
		scores.push_back( sn(i) );
	}
	
	
TryAgain:
	
	cout << "\n\nВведите имя: ";
	
	for (string n = "NoName"; cin >> n; )
	{
		if (n == "NoName") {
			cout << "Ввод завершён пользователем.\n\n";
			break;
		}
		
		for (int i = 0; i <= names.size(); ++i) {
			if (i == names.size()) {
				cout << "ОШИБКА! Имя " << n << " не найдено.\nПопробуйте снова."
					 << "\n\n";
				
				break;
			}
			else if (n == names[i]) {
				cout << "Оценка: " << scores[i] << "\n\n";
				break;
			}
		}
		
		cout << "Введите имя: ";
	}
	
	//Если было введено CTRL+Z, CTRL+V или любая др. комбинация
	if (!cin.good())
	{
		cin.clear(); //Очищаем поток ввода
		cin.ignore(10000, '\n');
		//cin.ignore();
		goto TryAgain; //Перезапускаем цикл for
	}
	
	for (int i = 0; i < names.size(); ++i)
		cout << i+1 << ". " << names[i] << " " << scores[i] << '\n';
	
	cout << "\n\n";
	
	press_Enter_key();
	return EXIT_SUCCESS;
}

string ns (int indx)
{
	switch (indx)
	{
		case 0:
			return ("Dina");
			break;
			
		case 1:
			return ("Anton");
			break;
				
		case 2:
			return ("Yura");
			break;
				
		case 3:
			return ("Roman");
			break;
				
		case 4:
			return ("Lada");
			break;
				
		case 5:
			return ("Liya");
			break;
				
		case 6:
			return ("Vyacheslav");
			break;
				
		case 7:
			return ("Dusya");
			break;
				
		case 8:
			return ("Stanislav");
			break;
				
		case 9:
			return ("Igor");
			break;
				
		case 10:
			return ("Vasiliy");
			break;
				
		case 11:
			return ("Vladimir");
			break;
				
		case 12:
			return ("Ekaterina");
			break;
				
		case 13:
			return ("Ludmila");
			break;
				
		case 14:
			return ("Maxim");
			break;
				
		case 15:
			return ("Pavel");
			break;
				
		case 16:
			return ("Aleksey");
			break;
				
		case 17:
			return ("Sergey");
			break;
				
		case 18:
			return ("Vladislav");
			break;
				
		case 19:
			return ("Rostislav");
			break;
	}
}

int sn (int indx)
{
	if (indx == 0) 			return (5);
	else if (indx == 1)		return (4);
	else if (indx == 2) 	return (3);
	else if (indx == 3) 	return (4);
	else if (indx == 4) 	return (5);
	else if (indx == 5) 	return (5);
	else if (indx == 6) 	return (4);
	else if (indx == 7) 	return (4);
	else if (indx == 8) 	return (5);
	else if (indx == 9) 	return (4);
	else if (indx == 10) 	return (4);
	else if (indx == 11) 	return (2);
	else if (indx == 12) 	return (4);
	else if (indx == 13) 	return (5);
	else if (indx == 14) 	return (4);
	else if (indx == 15) 	return (3);
	else if (indx == 16) 	return (5);
	else if (indx == 17) 	return (3);
	else if (indx == 18) 	return (4);
	else if (indx == 19) 	return (4);
}
