

#include "Chrono.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

long int days_between(const Chrono::Date& a, const Chrono::Date& b)
//Вычисляет кол-во дней между двумя датами с соблюдением условия a < b
//Вызято из упражнения 12 главы 9
{
	using namespace Chrono;
	
	if ( (  a.year() == b.year() && ( int(a.month()) > int(b.month()) || \
			  (int(a.month()) == int(b.month()) && a.day() > b.day()) )  ) \
			|| a.year() > b.year() )
	{
		Date buff	{ a.day(), a.month(), a.year() };
		Date a		{ b.day(), b.month(), b.year() };
		Date b		{ buff.day(), buff.month(), buff.year() };
	}
	
	//Если год больше года начальной даты:
	// -сначала высчитываем кол-во дней от указанной даты (день-месяц)
	//      в год нач. даты до начал след.года
	// -перебираем года до текущего указанного прибавляя кол-во дней
	//      в году (учитывая високосные) к общему числу
	
	//Если год указанной даты совпадает с начальным:
	// -просто высчитываем кол-во дней от начальной даты перебором до указанной даты
	
	// Последним этапом просто прибавляем номер дня в году для указанной даты
	
	int cd = a.day();
	int cm = int(a.month());
	int cy = a.year();
	
	
	long int days = 0;
	
	//Вычисляем кол-во дней от начальной даты до конца года начальной даты
	if (b.year() > cy) {
		days += ( leapyear(cy) ? 366 : 365 ) - day_of_year( Date(cd,Month(cm),cy) );// + 1;
		
		++cy;
	}
	
	//прибавляем дни за каждый полный прошедший год до года конечной даты
	while (b.year() > cy) {
		days += ( leapyear(cy) ? 366 : 365 );
		++cy;
	}
	
	if (a.year() == b.year()) {
		Date first_date	{ a.day(), a.month(), a.year() };		//Начальная дата
		Date last_date	{ b.day(), b.month(), b.year() };		//Конечная дата
		
		while (first_date != last_date) {
			first_date.add_days(1);
			++days;
		}
	}
	
	else
		days += day_of_year(  Date { b.day(), b.month(), b.year() }  );
		//прибавляем последнее число - номер дня конечной даты
	
	return days;
}


int main() {
	while(true)
	try {
		using namespace Chrono;
		
		Date birthday;
		Date today { currentDate() };
		
		cout << "\nФормат ввода: 'число.месяц.год' (ДД.ММ.ГГГГ), пробелы не учитываются\n"
				"\nВведите дату рождения: ";
		
		cin >> birthday;
		
		int age = days_between(birthday, today) / 365;
		//int age = days_between(today, birthday) / 365;
		
		cout << "\n Система счисления\t Дата рождения\t\t Возраст\n"
				  "     Десятичная   \t  " << dec << birthday << "\t\t   " << age << '\n' << \
				  "    Восьмиричная  \t  " << oct << birthday << "\t\t   " << age << '\n' << \
				  " Шестнадцатиричная\t  " << hex << birthday << "\t\t   " << age;
		
		if ( Y_or_N(quit_question) )	return 0;
		//keep_window_open("~~");
	}
	
	catch (Chrono::CTRL_Z_throw) { //Для системных исключений при работе с программой
		cerr << "\nВВОД CTRL+Z\n";
		
		if ( Y_or_N(quit_question) )	return 1001;
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		
		if ( Y_or_N(quit_question) )	return 1001;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		
		if ( Y_or_N(quit_question) )	return 1002;
	}
}