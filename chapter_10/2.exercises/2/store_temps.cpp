
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

class EOF_throw {}; //При нажати CTRL+Z / CTRL+D или встрече конца файла
const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------

void skip_to_num(istream& ist); //Пропуск любых символов пока не будет достигнуто число

int get_int(istream& ist); //получение на ввод из потока ist целого числа и обработка ошибок
int get_dbl(istream& ist); //получение на ввод из потока ist десятичной дроби или целого числа и обработка ошибок

//------------------------------------------------------------------------------

struct Reading {			//Данные о температуре
	int		hour;			//Час измерения [0;23]
	double	temperature;	//По Цельсию
};

ostream& operator<<(ostream& ost, const Reading& r)
//Оператор вывода для переменных класса Reading
{
	return ost << r.hour << " " << r.temperature; // << char(0xC2B0) << char(0x0043);
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
		error("диапазон значений часов от 0 до 23, встречено значение " + hour);
	
	else if  ( (tempr + 273.15) < 0 ) {
		string error_str = "не может быть температуры ниже абсолютной по Кельвину (-273.15 ";
		error_str.push_back( char(0xC2B0) ); //char(248) или char(0xC2B0)
		error_str += "C.)";
		error(error_str);
	}
	
	
	r.hour = hour;
	r.temperature = tempr;
	
	return ist;
}

//------------------------------------------------------------------------------

//Пропуск любых символов пока не будет достигнуто число
void skip_to_num(istream& ist)
{
	if (ist.fail()) {			//найдено что-то не являющееся целым числом
		ist.clear();			//пробуем получить символ
		char ch;
		while (ist>>ch){		//пропускаем всё что не является числами
			if (isdigit(ch)) {	//как только встретили число - 
				ist.unget();	//возвращаем символ обратно в поток ввода
				return;
			}
		}
	}
	
	error("Нет ввода");			// eof или bad
}


int get_int(istream& ist)
{
	int n = 0;
	
	while(true) {
		if (ist >> n)	return n;
		
		cout << "\nВведённое не является числом. Попробуйте ещё раз.\n";
		skip_to_num(ist);
	}
}

int get_dbl(istream& ist)
{
	double n = 0;
	
	while(true) {
		if ( ist >> n && !isinf(n) )	return n;
		
		cout << "\nВведённое не является числом. Попробуйте ещё раз.\n";
		skip_to_num(ist);
	}
}


int main()
{
	while (true) {
		try
		{
			ofstream ofs { "raw_temps.txt" };
			if (!ofs)	error("Невозможно открыть файл 'raw_temps.txt'");
			
			while ( true ) {
				Reading r;
				
				cout << "\nВведите ЧАС ТЕМПЕРАТУРА_ПО_ЦЕЛЬСИЮ: ";
				cin >> r;
				
				if ( cin.eof() )
					{ cin.clear();	break; }
				
				ofs << r << endl;
			}
			
			ofs.close();
			
			
			if ( Y_or_N(quit_question) )	return 0;
		}

		catch (exception& e) { //Для системных исключений при работе с программой
			cerr << "Ошибка: " << e.what() << '\n';
			if ( Y_or_N(quit_question) )	return 1002;
		}

		catch (...) { //Для непредвиденных исключений
			cerr << "Упс! Неизвестное исключение!\n";
			if ( Y_or_N(quit_question) )	return 1003;
		}
	}
}