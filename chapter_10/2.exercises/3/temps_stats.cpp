
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

class EOF_throw {}; //При нажати CTRL+Z / CTRL+D или встрече конца файла

//------------------------------------------------------------------------------

struct Reading {			//Данные о температуре
	int		hour;			//Час измерения [0;23]
	double	temperature;	//По Цельсию
};

ostream& operator<<(ostream& ost, const Reading& r)
//Оператор вывода для переменных класса Reading
{
	return ost << r.hour << " " << r.temperature << ' ' << 'C'; // char(248) //char(0xC2B0) //char(0x0043) //wchar_t(176)
}
	
istream& operator>>(istream& ist, Reading& r)
//Оператор ввода для переменных класса Reading + проверка достоверности ввода
{
	int hour;
	double tempr;
	
	ist >> hour >> tempr;
	
	if (ist.eof())	return ist; //достигнут конец файла
	
	else if (!ist)
		error("неверный ввод ( Reading operator>> )");
	
	else if  ( hour < 0 ||  23 < hour )
		error("диапазон значений часов от 0 до 23; встречено значение " + to_string(hour) + " ( Reading operator>> )");
	
	//При вводе в градусах по Цельсию
	else if  ( tempr < -273.15 )
		error("не может быть температуры ниже абсолютной по Кельвину (-273.15 \xC2\xB0\C); встречено значение " + \
																		to_string(tempr) + " ( Reading operator>> )");
	
	/*
	//При вводе в градусах по Фаренгейту
	else if ( (5.0/9) * (tempr-32) < -273.15 )
		error("не может быть температуры ниже абсолютной по Кельвину (-273.15 \xC2\xB0\C); встречено значение " + \
																		to_string(tempr) + " ( Reading operator>> )");
	*/
	
	
	r.hour = hour;
	r.temperature = tempr;
	
	return ist;
}

//------------------------------------------------------------------------------

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


int main()
try
{
	ifstream ifs { "raw_temps.txt" };
	if (!ifs)	error("Невозможно открыть файл 'raw_temps.txt' (должен лежать рядом с программой)");
	
	vector<Reading> file_temps;
	
	for (Reading r; ifs >> r; )
		file_temps.push_back(r);
	
	ifs.close();
	
	//Если в цикле при считывании файла не вылетела ошибка
	if ( file_temps.size() != 0 )
		cout << "Данные были записаны в вектор";
	else
		error("не было считанно ни одной пары ЧАС ТЕМПЕРАТУРА. Возможно файл raw_temps.txt пуст");
	
	cout << "\n\nЭлементы вектора:\n";
	print_vreadings(cout, file_temps);
	
	cout << "\nСреднее арифметическое температур: " << midv_proc(file_temps);
	cout << "\nМедиана температур: " << mediv_proc(file_temps) << endl;
	
	press_Enter_key();
}

catch (exception& e) { //Для системных исключений при работе с программой
	cerr << "Ошибка: " << e.what() << '\n';
	
	press_Enter_key();
	return 1001;
}

catch (...) { //Для непредвиденных исключений
	cerr << "Упс! Неизвестное исключение!\n";
	
	press_Enter_key();
	return 1002;
}