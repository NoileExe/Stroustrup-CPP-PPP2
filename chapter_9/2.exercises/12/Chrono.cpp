//Определение функций объявленных в Chrono.h

#include "Chrono.h"

namespace Chrono {
//Определение функций-членов класса Date:

Date::Date(int bd, int bm, int by, int dd, Month mm, int yy) //инициализация новой переменной класса Date
	: bday(bd), bmonth(bm), byear(by), d(dd), m(mm), y(yy)
{
	if ( !is_date(bd, bm, by)  ||  !is_date(dd, int(mm), yy) )
		error("дата введена с ошибкой ( инициализация объекта Date )");
	
	//days_after_begin();
}

Date::Date(int dd, Month mm, int yy) //инициализация новой переменной класса Date
	: d(dd), m(mm), y(yy)
{
	if ( !is_date(dd, int(mm), yy) )
		error("дата введена с ошибкой ( инициализация объекта Date )");
}

Date::Date() //при создании пустой переменной класса Date присваиваем дату по ум.
	:d(default_date().day()),
	 m(default_date().month()),
	 y(default_date().year())
{
}

//------------------------------------------------------------------------------

void Date::test_begin_date()
/*Требует от пользователя соблюдение условия:
		ТЕКУЩАЯ_ДАТА >= НАЧАЛЬНАЯ_ДАТА
Для этого выводит информацию и просит ввести новую нач.дату.
После ввода стирает с экрана инфо и введенное пользователем.*/
{
	while ( (byear == y && \
			( bmonth > int(m) || (bmonth == int(m) && bday > d) ) ) \
			|| byear > y )
	//Текущая дата меньше начальной даты
	{
		cout    << "Текущая указанная дата ("
				<< d << "." << int(m) << "." << y << "г."
				<< ") меньше начальной точки отсчёта: "
				<< bday << "." << bmonth << "." << byear << "г.";
		
		cout    << "\nИзмените дату нач. точки отсчёта на меньшую чем текущая дата.\n";
		
		Chg_begin_date();
		
		cin.clear();
	}
}

long int Date::days_after_begin()
/*Вычисляет кол-во дней между двумя датами с соблюдением условия test_begin_date();
изменяет член класса between_begin_n_end - приравнивает к полученному значению
и возвращает полученное значение*/
{
	test_begin_date(); //Проверяем дату (больше ли она начальной)
	
	//Если год больше года начальной даты:
	// -сначала высчитываем кол-во дней от указанной даты (день-месяц)
	//      в год нач. даты до начал след.года
	// -перебираем года до текущего указанного прибавляя кол-во дней
	//      в году (учитывая високосные) к общему числу
	
	//Если год указанной даты совпадает с начальным:
	// -просто высчитываем кол-во дней от начальной даты перебором до указанной даты
	
	// Последним этапом просто прибавляем номер дня в году для указанной даты
	
	int cd = bday;
	int cm = bmonth;
	int cy = byear;
	
	
	long int days = 0;
	
	if (y > cy) {
		days += ( leapyear(cy) ? 366 : 365 ) - day_of_year( Date(cd,Month(cm),cy) );// + 1;
		//Вычисляем кол-во дней от начальной даты до конца года (начальной даты)
		
		++cy;
	}
	
	while (y > cy) {
		days += ( leapyear(cy) ? 366 : 365 );
		//прибавляем дни за каждый полный прошедший год до года конечной даты
		
		++cy;
	}
	
	if (byear == y) {
		Date first_date (bday, Month(bmonth), byear);	//Начальная дата
		Date last_date  (d,m,y);						//Конечная дата
		while (first_date != last_date) {
			first_date.add_days(1);
			++days;
		}
	}
	else
		days += day_of_year( Date(d,m,y) );
		//прибавляем последнее число - номер дня конечной даты
	
	between_begin_n_end = days; //запоминаем для текущего объекта класса Date и возвращаем значение
	return days;
}

const Date& default_date()
//в качестве даты по умолчанию (для пустой переменной класса Date) устанавливается текущая дата
{
	static const Date dd = currentDate();
	return dd;
}

Date currentDate()
//получение текущей даты в формате подходящем для Chrono::Date
//Возвращает текущую дату в формате дд.мм.гггг
{
	time_t     now = time(0);
	struct tm  tstruct;
	//char       buf[80];
	tstruct = *localtime(&now);
	//strftime(buf, sizeof(buf), "%d.%m.%Y", &tstruct);
	
				//числа мес. 1-31       месяцы 0-11       кол-во лет с 1900 года
	return Date(tstruct.tm_mday, Month(tstruct.tm_mon+1), tstruct.tm_year+1900);
}

//------------------------------------------------------------------------------

void Date::Chg_begin_date()
//Позволяет изменить bday, bmonth и byear для текущего объекта Date
{
	Date begin_date;
	
	cout << "\nИзменение НАЧАЛЬНОЙ даты.";
	cin >> begin_date;
	
	bday = begin_date.day();
	bmonth = int( begin_date.month() );
	byear = begin_date.year();
}

void Date::ScrOut_Dates()
/*Выводит начальную дату (bday, bmonth и byear), 
за ней текущую дату хранящуюся в d, m, y и в конце кол-во дней между ними (between_begin_n_end).
Перед выводом на экран изменяет between_begin_n_end посредством ф-ции days_after_begin(); */
{
	days_after_begin();
	
	cout    << "\nНачальная дата: " << bday << "." << bmonth << "." << byear << " г."
			<< "\nКонечная дата: " << d << "." << int(m) << "." << y << " г."
			<< "\nДней между датами: " << between_begin_n_end << endl;
}
	
//------------------------------------------------------------------------------

int days_in_month(Month m, int y)
//на вход: год и месяц
//возврат: количество дней в месяце
{
	switch (int(m)) {
		case 2: //в високосный год в феврале 29 дней, иначе 28
			return (leapyear(y)) ? 29 : 28;
		
		case 4: case 6: case 9: case 11: //апрель, июнь, сентябрь, ноябрь
			return 30;
		
		default:
			return 31;
	}
}

void Date::add_days(int n)
{
	if (n<0)
		error("кол-во прибавляемых дней должно быть положительным ( Date::add_days() )");
	
	while ( n >= days_in_month(m,y) ) {
		n -= days_in_month(m, y);
		add_month(1);
	}
	
	if ( (n+d) > days_in_month(m, y) ) {
		n -= ( days_in_month(m, y) - d );
		d = 0;
		add_month(1);
	}
	
	d += n;
}

void Date::add_month(int n)
{
	if (n<0)
		error("кол-во прибавляемых месяцев должно быть положительным ( Date::add_month() )");
	
	while (n > 12) {
		add_year(1);
		n -= 12;
	}
	
	if(( n+int(m)) > 12 ) {
		add_year(1);
		n -= 12;
	}

	m = Month(int(m)+n);
}

void Date::add_year(int n)
{
	//Обязательно проверяем вискосоный ли год!
	if (m==Month::feb && d==29 && !leapyear(y+n)) {
		//Рабоет и с положительным, и с отрицательным n (n==0 не должно допускаться)
		m = Month::mar;	//В невыискосный год вместо 29 февраля используем 1ое марта
		d = 1;
	}
	
	y += n;
}

//------------------------------------------------------------------------------

bool is_date(int d, int m, int y)
//проверка корректности инициализируемой даты
{
	if (y<1800 || y>2200)
		return false;
	else if (m<1 || m>12)
		return false;
	else if ( d<1 || d > days_in_month( Month(m), y ) )
		return false;
	else
		return true;
}

//------------------------------------------------------------------------------

bool leapyear(int y)
{
	//Вискокосными годами считаются все делящиеся на 4,при этом если год начала 
	//столетия делится на 100, но не делится на 400 - он не яв-ся високосным
	if (y%4) return false;
	
	if (y%100==0 && y%400) return false;
	
	return true;
}

//------------------------------------------------------------------------------

bool operator==(const Date& a, const Date& b)
{
	return   a.day()==b.day()
		&& a.month()==b.month()
		 && a.year()==b.year();
}


bool operator!=(const Date& a, const Date& b)
{
	return !(a==b);
}


ostream& operator<<(ostream& os, const Date& dd)
//оператор вывода для переменных класса Date
{
	/*return os   << "Начальная дата: " << dd.day() << '.' << int(dd.month()) 
				<< '.' << dd.year() << " г."
				<< "\nКонечная дата: " << begin_date.day() << '.' << int(begin_date.month()) 
				<< '.' << begin_date.year() << " г."
				<< "\nДней между: " << dd.between_BnE();*/
	
	
	return os << dd.day() << '.' << int(dd.month())
			  << '.' << dd.year() << " г.";
}

istream& operator>>(istream& is, Date& dd)
{
	int d, m, y;
	char ch1, ch2;
	
	cout << "\nВведите дату в формате 'дд.мм.гггг': ";
	
	is >> d >> ch1 >> m >> ch2 >> y;

	if (cin.eof())
		throw CTRL_Z_throw {};
	
	else if  (!is)
		error("неверный ввод ( operator>>() )");
	
	else if (ch1!='.' || ch2!='.') { //Ошибка формата ввода
		is.clear(ios_base::failbit);	//Устанавливаем fail bit
		error("неверный ввод ( operator>>() )");
	}
	
	if ( is_date(d,m,y) )
		dd = Date(dd.begin_day(), dd.begin_month(), dd.begin_year(), d, Month(m), y); //вносим новые данные в dd
	else
		error("дата введена с ошибкой ( operator>>() )");
	
	is.ignore();
	return is;
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, Day d)
//В зависимости от значения печатает название дня недели
{
	switch (d) {
		case sunday:
			os << "воскресение";
			break;
		
		case monday:
			os << "понедельник";
			break;
		
		case tuesday:
			os << "вторник";
			break;
		
		case wednesday:
			os << "среда";
			break;
		
		case thursday:
			os << "четверг";
			break;
		
		case friday:
			os << "пятница";
			break;
		
		case saturday:
			os << "суббота";
			break;
	}
	
	return os;
}

Day day_of_week(const Date& dd)
//На вход: объект класса Date
//На выход: день недели для данной даты
//См. папку 'info'
{
							//|Янв  |Март |Май  |Июль |Сент |Нояб
	vector<int> inf_calendar {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
							//   |Февр |Апр  |Июнь |Авг  |Окт  |Дек
	
	int d = dd.day();
	int m = int(dd.month());
	int y = dd.year();
	
	int year_div_28 = 1901;
	//каждые 28 лет цикл повторяется
	//Если год (y) больше начала отсчета (1901) - ничего не делаем
	//Иначе постепенно отнимаем 28 лет пока наало отсчёта не сравняется или не станет меньше году (y)
	while (year_div_28 > y)
		year_div_28 -= 28;
	
	int n = inf_calendar[m-1];
	for (int i = year_div_28; i <= y; ++i)
	{
		switch (m-1) 
		{
			case 0: case 1:
			{
				if ( (i-year_div_28) % 28 != 0 )
				{
					if ( leapyear(i-1) ) n = (n+2)%7; //в год после високосного значение +2
					else n = (n+1)%7;
				}
				else n = inf_calendar[m-1]; //откатываем значение после 28 лет
				
				break;
			}
			
			case 2: case 3: case 4: case 5: case 6: 
			case 7: case 8: case 9: case 10: case 11:
			{
				if ( (i-year_div_28) % 28 != 0 ) 
				{
					if ( leapyear(i) ) n = (n+2)%7; //в високосный год значение +2
					else n = (n+1)%7;
				}
				else n = inf_calendar[m-1]; //откатываем значение после 28 лет
				
				break;
			}
			
		}
	}
	
	if (y < 1901)	n = ( n + (d+1) ) % 7;
	else			n = ( n + d ) % 7;
	
	return Day(n);
}

Date next_workday(Date dd)
{
	switch (day_of_week(dd))
	{
		case sunday: case monday: case tuesday:
		case wednesday: case thursday: //0, 1, 2, 3, 4
			dd.add_days(1);
			break;
		case friday: //5
			dd.add_days(3); //перескакиваем субботу и воскресение
			break;
		case saturday: //6
			dd.add_days(2); //перескакиваем воскресение
			break;
	}
	
	return dd;
}

int day_of_year(const Date& dd)
//На вход: ссылка на объект даты
//На выходе: номер дня в году (год берется из даты подаваемой на вход)
{
	Date first_date (1, Month::jan, dd.year()); //Первая дата в году)
	Day first_WDoY = day_of_week(first_date);   //Первый день недели в году (1st WeekDay of Year)
	
	int days_count = 1;
	
	while (first_date != dd) { first_date.add_days(1); ++days_count; }
	
	return days_count;
}

int week_of_year(const Date& dd)
//На вход: ссылка на объект даты
//На выходе: номер недели в году (год берется из даты подаваемой на вход)
{
	Date first_date (1, Month::jan, dd.year()); //Первая дата в году)
	
	int weeks_count = 1;
	
	//Ведём подсчёт перебором дней пока не достигнем указанной даты
	while (first_date != dd) {
		first_date.add_days(1);
		
		//Каждый новый понедельник - новая неделя
		if ( day_of_week(first_date) == monday )
			++weeks_count;
	}
	
	return weeks_count;
}

}
