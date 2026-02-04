#include "names_ages.h"

namespace names_n_ages { //names_n_ages

//-------------------------------------------------------------------------------------------------------------------------------

void Name_pairs::read_data()
//считывает ряд имен в вектор name
{
	read_names();
	read_ages();
}

void Name_pairs::read_names()
{
	for (int i = name.size(); ; ++i) {
		string str = " ";
		char ch = ' ';
		
		cout << "\nВведите имя #" << i+1 << ": ";
		
		cin.clear();
		
		//Посимвольно считываем имя состоящее из букв (англ.) и пробелов
		while (cin.get(ch))
		{
			if ( isalpha(ch)  ||  (isspace(ch) && ch !='\n') )
				str+=ch;
			else if (ch =='\n')
				break;
			else {
				str = "";
				cout << "\n\nИмя может содержать только англ. буквы и пробелы.\n\n";
				//cout << "\n\nИмя может содержать только буквы (англ. и рус.) и пробелы.\n\n";
				--i;
				break;
			}
		}
		
		if (cin.eof() && name.size() == 0)
			error("Выход инициализирован пользователем");
		
		else if (cin.eof())
			return; //Если CTRL+Z, то завершаем ввод
		
		else if (cin.fail()) {
			cout << "\n\nНекорректный ввод.\n\n"; //..сообщаем об ошибке,..
			cin.clear(); //..устраняем ошибку
			--i;
		}
		
		else if (str.size() > 0) {
			//Поиск повторов
			for (int j = 0;  j < name.size(); ++j)
				if ( str == name[j] ) { //Проверка на повторяемость имени
					cout << "\nТакое имя уже было.\n\n";
					--i;
					break;
				}
			
			if ( i == name.size() )		name.push_back(str);
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

//-------------------------------------------------------------------------------------------------------------------------------

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
				if (name[i]<name[j]) {
				    swap(name[i], name[j]);
				    swap(age[i], age[j]);
				    --i;
				    break;
				}
	}
}

void Name_pairs::operator=(const Name_pairs& b)
{
	if (name.size() == 0)
		error("Вам нужно сначала заполнить векторы name и age при помощи ф-ции read_names ( Name_pairs::operator=() )");

	else if (name.size()!=age.size())
		error("Несоответствие размеров векторов name и age ( Name_pairs::operator=() )");
	
	else {

		name.clear();
		age.clear();

		for (int i = 0;  i < b.name_size(); ++i) {
			name.push_back(b.one_name(i));
			 age.push_back(b.one_age(i));
		}
	}
}

//-------------------------------------------------------------------------------------------------------------------------------

bool operator==(const Name_pairs& a, const Name_pairs& b)
{
	if ( (a.name_size() != b.name_size() && a.name_size() != a.age_size()) || (a.age_size() != b.age_size()) )
		return false;
	else if ( a.name_size() > 0 && b.name_size() > 0 )
	{
		for (int i = 0;  i < a.name_size(); ++i)
			if ( a.one_name(i) != b.one_name(i) || a.one_age(i) != b.one_age(i) ) return false;
	}

	return true;
}


bool operator!=(const Name_pairs& a, const Name_pairs& b)
{
	return !(a==b);
}


ostream& operator<<(ostream& os, const Name_pairs& np)
//оператор вывода для переменных класса Name_pairs
{
	if ( np.name_size() == 0 )
		error("Вам нужно сначала заполнить векторы name и age при помощи ф-ции read_names ( ostream& operator<<() )");

	else if ( np.name_size() != np.age_size() )
		error("Несоответствие размеров векторов name и age ( ostream& operator<<() )");
	
	else if ( np.name_size() == np.age_size() ) {

		for (int i = 0;  i < np.name_size(); ++i)
			if ( i < (np.name_size()-1) )
				os << "[" << i+1 << "] " << np.one_name(i) << " " << np.one_age(i) << endl;
			else
				os << "[" << i+1 << "] " << np.one_name(i) << " " << np.one_age(i) << "\n\n";
		
		return os;

	}
	
	else { os.flush(); os << "Объект Name_pairs поврежден."; return os; }
}

//-------------------------------------------------------------------------------------------------------------------------------

} //names_n_ages---------------------------------------