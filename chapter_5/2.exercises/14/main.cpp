/*
	Программа записывает в один из семи векторов (по названию дня недели) значение;
	 по завершению выводит количество отвергнутых значений, состав каждого вектора
	 и сумму значений в каждом векторе
	 Русские символы не работают при вводе, увы
*/

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>
//..............................................................................
int input_check (string);				//Определение какой день недели подан на ввод, а также ошибок
void print_similar (vector<int>, int);	//Вывод всех элементов вектора и их суммы
//..............................................................................
int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите день недели (допускаются некоторые распространённые вариан"
			"ты написания, например Monday, monday, Mon или mon для понедельник"
			"а) и через пробел ЦЕЛОЕ число.\nДля подтверждения - клавиша Enter."
			"\nКомбинация клавиш CTRL+Z для завершения ввода\n\n";
	
	vector<int> monday;
	vector<int> tuesday;
	vector<int> wednesday;
	vector<int> thursday;
	vector<int> friday;
	vector<int> saturday;
	vector<int> sunday;
	
	string inday = "";		//Ввод дня (для определения вектора)
	double innum = 0;		//Ввод числа
	int numoferr = 0;		//Количество ошибочно введённых

TryAgain:
	cout << "\n\nПроизведите ввод (ДЕНЬ_НЕДЕЛИ ЧИСЛО): ";
	
	while ( (cin >> inday >> innum) )
	{
		//cout << inday << endl;
		if ( innum < -2147483648.0 || innum > 2147483647.0 ) {
			cout << "Была допущенна ошибка при вводе числа (01 - число вне диапазона INT)\n";
			++numoferr;
		}
		
		else if ( isinf(innum) ) {
			cout << "Была допущенна ошибка при вводе числа (02 - число вне диапазона DOUBLE)\n";
			++numoferr;
		}
		
		else if ( int(innum) != innum ) {
			cout << "Была допущенна ошибка при вводе числа (03 - не целое число)\n";
			++numoferr;
		}
		
		else switch (input_check(inday)) {
			case 1: //Если введён "Понедельник", "понедельник", "ПН" или и т.д.
				monday.push_back(int(innum));
				break;
			
			case 2:
				tuesday.push_back(int(innum));
				break;
				
			case 3:
				wednesday.push_back(int(innum));
				break;
				
			case 4:
				thursday.push_back(int(innum));
				break;
				
			case 5:
				friday.push_back(int(innum));
				break;
			
			case 6:
				saturday.push_back(int(innum));
				break;
			
			case 7:
				sunday.push_back(int(innum));
				break;
				
			default:
				++numoferr;
				break;
		}
		
		cin.clear();
		innum = 0;
		
		cout << "\n\nПроизведите ввод (ДЕНЬ_НЕДЕЛИ ЧИСЛО): ";
	}
	
	if (!cin.eof() || isnan(innum)) {
		cout << "Была допущенна ошибка при вводе числа (00 - не число)\n";
		++numoferr;
		cin.clear();
		getline(cin, inday);
		goto TryAgain;
	}
	
	cout << "\n\nДопущенно ошибок ввода: " << numoferr;
	
	for (int i = 1; i <= 7; ++i)
	{
		if (i == 1)			print_similar(monday, i);
		else if (i == 2)	print_similar(tuesday, i);
		else if (i == 3)	print_similar(wednesday, i);
		else if (i == 4)	print_similar(thursday, i);
		else if (i == 5)	print_similar(friday, i);
		else if (i == 6)	print_similar(saturday, i);
		else if (i == 7)	print_similar(sunday, i);
	}
	
	cout << "\n\n"; 
	press_Enter_key();
	return EXIT_SUCCESS;
}
//..............................................................................
//Определение какой день недели подан на ввод, а также ошибак при вводе дня недели
int input_check (string inday)
{
	if (inday == "Понедельник" || inday == "понедельник" || inday == "ПН" 
			|| inday == "пн" || inday == "Пн" || inday == "ПНД" 
			|| inday == "пнд" || inday == "Пнд" || inday == "Monday" 
			|| inday == "monday" || inday == "Mon" || inday == "mon")
		return 1;
		
	else if (inday == "Вторник" || inday == "вторник" || inday == "ВТ" 
				|| inday == "вт" || inday == "Вт" || inday == "ВТР" 
				|| inday == "втр" || inday == "Втр" || inday == "Tuesday" 
				|| inday == "tuesday" || inday == "Tue" || inday == "tue")
		return 2;
		
	else if (inday == "Среда" || inday == "среда" || inday == "СР" 
				|| inday == "ср" || inday == "Ср" || inday == "СРД" 
				|| inday == "срд" || inday == "Срд" || inday == "Wednesday" 
				|| inday == "wednesday" || inday == "Wed" || inday == "wed")
		return 3;
		
	else if (inday == "Четверг" || inday == "четверг" || inday == "ЧТ" 
				|| inday == "чт" || inday == "Чт" || inday == "ЧТВ" 
				|| inday == "чтв" || inday == "Чтв" || inday == "Thursday" 
				|| inday == "thursday" || inday == "Thu" || inday == "thu")
		return 4;
		
	else if (inday == "Пятница" || inday == "пятница" || inday == "ПТ" 
				|| inday == "пт" || inday == "Пт" || inday == "ПТН" 
				|| inday == "птн" || inday == "Птн" || inday == "Friday" 
				|| inday == "friday" || inday == "Fri" || inday == "fri")
		return 5;
		
	else if (inday == "Суббота" || inday == "суббота" || inday == "СБ" 
				|| inday == "сб" || inday == "Сб" || inday == "СБТ" 
				|| inday == "сбт" || inday == "Сбт" || inday == "Saturday" 
				|| inday == "saturday" || inday == "Sat" || inday == "sat")
		return 6;
		
	else if (inday == "Воскресение" || inday == "воскресение" || inday == "ВС" 
				|| inday == "вс" || inday == "Вс" || inday == "ВСК" 
				|| inday == "вск" || inday == "Вск" || inday == "Sunday" 
				|| inday == "sunday" || inday == "Sun" || inday == "sun")
		return 7;
			
	else if (inday.size() == 0) {
		cout << "Была допущенна ошибка при вводе числа (03 - пустое значение дн"
				"я недели)\n";
		return 8;
	}
	else {
		cout << "Была допущенна ошибка при вводе дня недели (04 - недопустимое "
				"значение дня недели)\n";
		return 8;
	}
		
}
//..............................................................................
//Вывод всех элементов вектора и их суммы
void print_similar (vector<int> dow, int i)
{
	int summ = 0; //Для подсчёта суммы
	
	cout << "\n\nВектор '";
	
	if (i == 1)			cout << "monday";
	else if (i == 2)	cout << "tuesday";
	else if (i == 3)	cout << "wednesday";
	else if (i == 4)	cout << "thursday";
	else if (i == 5)	cout << "friday";
	else if (i == 6)	cout << "saturday";
	else if (i == 7)	cout << "sunday";
	
	cout << "' (кол-во элементов " << dow.size() << "): ";
	
	
	for (int j = 0; j < dow.size(); ++j)
	{
		cout << dow[j] << " ";		//Перечисляем все элементы
		summ += dow[j];				//Вычисляем сумму всех элементов
	}
			
	cout << "\nСумма всех элементов: " << summ; //Выводим сумму
}
