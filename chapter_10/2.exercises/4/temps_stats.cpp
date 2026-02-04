
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

class EOF_throw {}; //При нажати CTRL+Z / CTRL+D или встрече конца файла
const string iofile_name = "raw_temps.txt";

//--------------------------------------------------------------------------------------------------------

struct Reading {			//Данные о температуре
	int		hour;			//Час измерения [0;23]
	double	temperature;	//В градусах Цельсия либо Фаренгейта
	char	degree;			//Указывает значение temperature (Цельсий/Фаренгейт)
};


//Перевод значений градусов из системы указанной во втором аргументе в обратную ей
//Вызов FarenheitCelsius(10, 'C') вернёт температуру (10) переведённую из градусов Цельсия в Фаренгейты
double FarenheitCelsius(double gradus, char fc)
{
	switch (fc) {
		case 'f': case 'F':
			return (5.0/9) * (gradus-32);
			break;
		
		case 'c': case 'C':
			return ((9.0/5) * gradus)+32;
			break;
		
		default:
			string err_str = "perevod(): Введен неодопустимый символ (" + fc + ')';
			error (err_str);
			break;
	}
}


ostream& operator<<(ostream& ost, const Reading& r)
//Оператор вывода для переменных класса Reading
{
	return ost << r.hour << " " << r.temperature << r.degree;
}
	
istream& operator>>(istream& ist, Reading& r)
//Оператор ввода для переменных класса Reading + проверка достоверности ввода
{
	int hour;
	double tempr;
	char sign;
	
	ist >> hour >> tempr >> sign;	
	
	//--------------------------------------------------Поиск ошибок--------------------------------------------------
	
	if (ist.eof())	return ist; //достигнут конец файла
	
	else if (!ist)
		error("неверный ввод ( Reading operator>> )");
	
	else if  ( sign != 'C'  &&  sign != 'F' )
		error("значение градуса можно указывать только в Цельсиях ('C'), либо в Фаренгейтах ('F'), было введено " + \
					to_string(sign) + " ( Reading operator>> )");
	
	else if  ( hour < 0 ||  23 < hour )
		error("диапазон значений часов от 0 до 23, встречено значение " + to_string(hour) + " ( Reading operator>> )");
	
	//При вводе в градусах по Цельсию
	else if  ( tempr < -273.15 && sign == 'C' )
		error("не может быть температуры ниже абсолютной по Кельвину (-273.15 \xC2\xB0\C)? встречено значение " + \
																		to_string(tempr) + " ( Reading operator>> )");
	
	//При вводе в градусах по Фаренгейту
	else if ( FarenheitCelsius(tempr, sign) < -273.15  && sign == 'F' )
		error("не может быть температуры ниже абсолютной по Кельвину (-273.15 \xC2\xB0\C)? встречено значение " + \
																		to_string(tempr) + " ( Reading operator>> )");
	
	//--------------------------------------------------Поиск ошибок--------------------------------------------------
	
	
	r.hour = hour;
	r.temperature = tempr;
	r.degree = sign;
	
	return ist;
}

//--------------------------------------------------------------------------------------------------------

//Печать в указанный в аргументе поток вывода всех элементов вектора
void print_vreadings(ostream& ost, const vector<Reading>& r)
{
	for (int i=0; i < r.size(); ++i)
		if ( i != r.size()-1 )		ost << r[i] << '\n';
		else						ost << r[i];
	
	//for (const auto &i : r)
	//for (Reading i : r)
	//	ost << i << '\n';
}


double midv_proc(const vector<Reading>& r)
//Вычисление среднего арифметического для ряда температур в векторе Reading
//На вход: константная ссылка на непустой вектор
//Возврат: среднее арифметическое
{
	if ( r.size()==0 )
		error ("пустой вектор ( midv_proc() )!!!");
	
	double middle = 0;
	for (int i = 0;  i < r.size(); ++i)
		middle += r[i].temperature;
	
	middle /= r.size();
	
	if (isinf(middle))
		error ("значение вышло за пределы типа DOUBLE ( midv_proc() )!!!");
	else	return middle;
}

double mediv_proc(const vector<Reading>& r)
//Вычисление медианы для ряда температур в векторе Reading
//На вход: непустой вектор (копия, чтобы не сортировать оригинальный)
//Возврат: медиана
{
	if ( r.size()==0 )
		error ("пустой вектор ( mediv_proc() )!!!");
	
	vector<double> temps;
	for (int i = 0;  i < r.size(); ++i)
		temps.push_back( r[i].temperature );
	
	sort( temps.begin(), temps.end() );
	
	double median = 0;
	int mid = int( temps.size() / 2 );
	//срединный элемент (или 1ый срединный если четное кол-во эл. в векторе)
	
	if (temps.size()%2 == 0) //четное кол-во элементов в векторе
		median = ( temps[mid] + temps[mid+1] ) / 2;
	else
		median = temps[mid];
	
	
	if ( isinf(median) )
		error ("значение вышло за пределы типа DOUBLE ( mediv_proc() )!!!");
	else return median;
}

//--------------------------------------------------------------------------------------------------------

//Заполнение файла значениями введёнными с клавиатуры
void store_temps() {
	ofstream ofs { iofile_name }; //имя файла - константа
	if (!ofs)	error("Невозможно открыть файл '" + iofile_name + "' ( store_temps() )");
	
	while ( true ) {
		Reading r;
		
		cout << "\nВведите ЧАС ТЕМП.ЕРАТУРА ИНДЕКС( Цельсий(латинская 'C') / Фаренгейт('F') ):\n";
		cin >> r;
		
		if ( cin.eof() )
			{ cin.clear();	break; }
		
		ofs << r << endl;
	}
}

//--------------------------------------------------------------------------------------------------------

void temps_stats()
{
	ifstream ifs { iofile_name };
	if (!ifs)
	{
		string err = "Невозможно открыть файл '" + iofile_name + "'";
		error(err);
	}
	
	vector<Reading> file_temps;
	
	for (Reading r; ifs >> r; ) {
		if ( r.degree == 'C' ) {
			r.temperature = FarenheitCelsius(r.temperature, r.degree); //Переводим в Фаренгейты
			r.degree = 'F';
		}
		
		file_temps.push_back(r);
	}
	
	ifs.close();
	
	//Если в цикле при считывании файла не вылетела ошибка
	if ( file_temps.size() == 0 )
		error("не было считанно ни одного значения вида ЧАС ТЕМПЕРАТУРА ИНДЕКС. Возможно файл '" + \
															iofile_name + "' пуст ( temps_stats() )");
	
	cout << "\n\nЭлементы вектора:\n";
	print_vreadings(cout, file_temps);
	
	cout << "\n\nСреднее арифметическое температур: "	<< midv_proc(file_temps)	<< "\xC2\xB0\F";
	cout << "\nМедиана температур: "					<< mediv_proc(file_temps)	<< "\xC2\xB0\F\n";
}

//--------------------------------------------------------------------------------------------------------

int main()
try
{
	cout << "\nСначала введите значения с клавиатуры, они запишутся в файл. "
		 << "Затем из того же файла значения будут считаны в вектор с дальнейшим "
		 << "выводом их на экран, а так же значения средней и медианной температуры\n\n";
	
	store_temps(); //Заполнение файла значениями
	temps_stats(); //Заполнение вектора значениями из файла и поиск среднего и медианы температур
	
	keep_window_open("~~");
}

catch (exception& e) { //Для системных исключений при работе с программой
	cerr << "Ошибка: " << e.what() << '\n';
	
	keep_window_open("~~");
	return 1001;
}

catch (...) { //Для непредвиденных исключений
	cerr << "Упс! Неизвестное исключение!\n";
	
	keep_window_open("~~");
	return 1002;
}