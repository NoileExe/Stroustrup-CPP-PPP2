#include "names_ages.h"

void Name_pairs::read_data()
//считывает ряд имен в вектор name
{
	read_names();
	read_ages();
}

/*Name_pairs::Name_pairs() :name(), age()
{
	read_data();
}*/

//Заполняет именами вводимыми пользователем с клавиатуры вектор names
void Name_pairs::read_names()
{
	for (int i = name.size(); ; ++i) {
		string str = " ";
		char ch = ' ';
		
		cout << "\nВведите имя #" << i+1 << ": ";
		
		cin.clear();
		
		//Посимвольно считываем имя состоящее из букв (англ. и рус.) и пробелов
		while ( cin.get(ch) )
			if ( (ch>='А' && ch<='п') || (ch>='р' && ch<='я') || isalpha(ch) || ( isspace(ch) && ch !='\n' ) )
				str+=ch;
			else if (ch =='\n')
				break;
			else {
				str = "";
				break;
			}
		
		if (cin.eof() && name.size() == 0)
			error("Выход инициализирован пользователем");
		
		else if (cin.eof())
			return; //Если CTRL+Z, то завершаем ввод
		
		else if (cin.fail()) {
			cout << "\n\nНекорректный ввод.\n\n"; //..сообщаем об ошибке,..
			cin.clear(); //..устраняем ошибку
			//cin.putback(ch); //для того чтобы при очистки введенной строки не происходило подвисания (ожидание ввода)
			--i;
		}
		
		else if (str.size() > 0) {
			//Поиск повторов
			for (int j = 0;  j < name.size(); ++j)
				if ( str == name[j] ) { //Проверка на повторяемость имени
					cout << "\nТакое имя уже было.\n\n";
					//cin.putback(ch);
					--i;
					break;
				}
			
			if ( i == name.size() )		name.push_back(str);
		}
		
		else {
			cout << "\n\nИмя может содержать только англ. буквы и пробелы.\n\n";
			//cout << "\n\nИмя может содержать только буквы (англ. и рус.) и пробелы.\n\n";
			//cin.putback(ch);
			--i;
		}
		
		cin.putback(ch);
		while ( cin.get() != '\n' )		cin.clear(); //Очищает поток символов cin
	}
}

void Name_pairs::read_ages()
//предлагает ввести и считывает возраст для каждого имени в вектор age
{
	int start = 0;
	
	if ( age.size() > name.size() )
		error("Несоответствие размеров векторов name и age ( Name_pairs::read_ages() )");
		
	else if ( age.size() > 0 )
		start = age.size() - 1;
	
	
	for (int i = start; i < name.size(); ++i) {
		double num = 0;
		
		cout << "\nВведите возраст для " << name[i] << ": ";
		
		cin.clear();

		cin >> num;

		if ( cin.eof() && name.size()!=age.size() )
			error("Выход инициализирован пользователем");
		
		else if (cin.fail()) {
			cout << "\n\nТребуется корректное число с плавающей дес.точкой.\n\n";
			cin.clear();
			--i;
		}
		
		else if ( num < 1 || num > 150 ) {
			cout << "\n\nВведенное значение недопустимо ( только диапазон [1; 150] ).\n\n";
			cin.clear();
			--i;
		}
		else age.push_back(num);

		while ( cin.get() != '\n' )		cin.clear(); //Очищает поток символов cin
	}
}

//--------------------------------------------------------------------------------------------------------------

void Name_pairs::print()
//выводит пары name[i], age[i] по одной на строку в порядке определённым вектором name
//при выводе счёт начинается с единицы (для пользователя)
{
	if (name.size() == 0)
		error("Вам нужно сначала заполнить векторы name и age при помощи ф-ции read_names ( Name_pairs::print() )");

	else if (name.size()!=age.size())
		error("Несоответствие размеров векторов name и age ( Name_pairs::print() )");
	
	else {
		for (int i = 0;  i < name.size(); ++i)
			if ( i < (name.size()-1) )	cout << "[" << i+1 << "] " << name[i] << " " << age[i] << endl;
			else						cout << "[" << i+1 << "] " << name[i] << " " << age[i] << "\n\n";
	}
}

void Name_pairs::sort()
//упорядочивает name в алфавитном порядке и соответствующе реорганизовывает вектор age
{
	if (name.size() == 0)
		error("Вам нужно сначала заполнить векторы name и age при помощи ф-ции read_names ( Name_pairs::sort() )");

	else if (name.size()!=age.size())
		error("Несоответствие размеров векторов name и age ( Name_pairs::sort() )");
	
	else {
		for (int i=0; i<name.size(); ++i)
			for (int j=0; j<name.size(); ++j)
				if (name[i]<name[j])
				{
					swap(name[i], name[j]);
					swap(age[i], age[j]);
					--i;
					break;
				}
	}
}
