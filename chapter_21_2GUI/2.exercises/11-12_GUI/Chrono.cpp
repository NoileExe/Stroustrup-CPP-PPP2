//Определение функций объявленных в Chrono.h

#include "Chrono.h"

namespace Chrono {
	//Определение функций-членов класса Date:

	Date::Date(int dd, Month mm, int yy) //инициализация новой переменной класса Date
		: d(dd), m(mm), y(yy)
	{
		if (!is_date(dd, int(mm), yy))
				error("date is entered with an error ( Date object init )");
	}

	const Date& default_date();

	Date::Date() //при создании пустой переменной класса Date присваиваем дату по ум.
		:d(default_date().day()),
		 m(default_date().month()),
		 y(default_date().year())
	{
	}

	//------------------------------------------------------------------------------

	const Date& default_date()
	//дата по умолчанию (1 янв 2001) для пустой переменной класса Date
	{
		static const Date dd(01, Month::january, 2001); //начало XXI века
		return dd;
	}

	Date currentDate()
	//получение текущей даты в формате подходящем для Chrono::Date
	//Возвращает текущую дату в формате дд.мм.гггг
	{
		time_t		now = time(0);
		struct tm	tstruct;
		//char		buf[80];
		tstruct = *localtime(&now);
		//strftime(buf, sizeof(buf), "%d.%m.%Y", &tstruct);
		
				  //числа мес. 1-31        месяцы 0-11        кол-во лет с 1900 года
		return Date(tstruct.tm_mday, Month(tstruct.tm_mon+1), tstruct.tm_year+1900);
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
			error("the number of preceded days should be positive ( Date::add_days() )");
		
		while  (n >= days_in_month(m,y) ) {
			n -= days_in_month(m,y);
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
			error("the number of added months should be positive ( Date::add_month() )");
		
		while (n > 12) {
			add_year(1);
			n -= 12;

		}
		
		if( ( n+int(m) )  >  12 ) {
			add_year(1);
			n -= 12;
		}

		m = Month(int(m)+n);
	}

	void Date::add_year(int n)
	{
		//Обязательно проверяем вискосоный ли год!
		if ( m == Month::february && d == 29 && !leapyear(y+n) ) {
			//Рабоет и с положительным, и с отрицательным n (n==0 не должно допускаться)
			m = Month::march;	//В невыискосный год вместо 29 февраля используем 1ое марта
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

	bool operator>(const Date& a, const Date& b)
	{
		if(a.year() > b.year())			return true;
		else if (a.year() < b.year())	return false;
		
		else {
			if(int(a.month()) > int(b.month()))			return true;
			else if(int(a.month()) < int(b.month()))	return false;
			
			else {
				if(a.day() > b.day())			return true;
				else if(a.day() < b.day())		return false;
			}
		}
		
		return false;
	}

	bool operator<(const Date& a, const Date& b)
	{
		if(a != b  &&  !(a > b))		return true;
		
		return false;
	}


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
		return os << dd.day() << '.' << int(dd.month())
				  << '.' << dd.year()/* << " year"*/;
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int d, m, y;
		char ch1, ch2;
		is >> d >> ch1 >> m >> ch2 >> y;
		
		
		/*if (is.eof())		return is;
		
		else */if  (!is  &&  !is.eof())
			error("incorrect input [operator>>() for Date object] 1");
			
		else if (ch1!='.' || ch2!='.') { //Ошибка формата ввода
			is.clear(ios_base::failbit);	//Устанавливаем fail bit
			error("incorrect input [operator>>() for Date object] 2");
		}
		
		if ( is_date(d,m,y) )
			dd = Date(d, Month(m), y); //вносим новые данные в dd
		else
			error("date is entered with an error [operator>>() for Date object]");
		
		//is.ignore();
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
		//Первая строка первой таблицы. Вск - 7ой день, но в программе (enum Day) - 0-ой
								//|Янв  |Март |Май  |Июль |Сент |Нояб
		vector<int> inf_calendar {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
								//   |Февр |Апр  |Июнь |Авг  |Окт  |Дек
		
		int d = dd.day();
		int m = int(dd.month());
		int y = dd.year();
		
		int year_div_28 = 1901; //Год отсчёта для вычислений
		//каждые 28 лет цикл повторяется (1ый столбец 1901 год, 2ой - 1929)
		
		//Если год (y) больше начала отсчета (1901) - ничего не делаем
		//Иначе постепенно отнимаем 28 лет пока начало отсчёта не сравняется или не станет меньше введённого года (y)
		//Всё это нужно чтобы программа работала с датами ранее 1901 года
		while (year_div_28 > y)
			year_div_28 -= 28;
		
		//Отсчёт месяцев (enum class Month) начинается с единицы, а индексы ветора с нуля
		int n = inf_calendar[m-1]; //Слагаемое (перекрёст таблицы 1 год-месяц)
		
		//Перебор лет до указанного года
		for (int i = year_div_28; i <= y; ++i)
		{
			
			if ( (i-year_div_28) % 28 != 0 )
			{
				//в ЯНВ и ФЕВ в год после високосного значение дня недели +2
				if ( m-1 < 2 ) {
					//Предыдущий год от указанной даты - високосный?
					if ( leapyear(i-1) )	n = (n+2)%7;
					else					n = (n+1)%7;
				}
				
				//в остальные месяцы в сам високосный год значение дня недели +2
				else {
					//Текущий год для указанной даты - високосный?
					if ( leapyear(i) )		n = (n+2)%7;
					else					n = (n+1)%7;
				}
				
			}
			
			else n = inf_calendar[m-1]; //откатываем значение после 28 лет
			
			/*
			switch (m-1) 
			{
				//Январь и февраль
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
				
				//Все остальные месяцы
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
			*/
		}
		
		if (y < 1901)   n = ( n + (d+1) ) % 7;
		else            n = ( n + d ) % 7;
		
		return Day(n);
	}


	Date next_workday(Date dd)
	//Дата следующего рабочего дня после текущего от указанной даты (понедельник-пятница)
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
		Date first_date (1, Month::january, dd.year()); //Первая дата в году)
		
		int days_count = 1;
		
		//Ведём подсчёт перебором дней пока не достигнем указанной даты
		while (first_date != dd)
			{ first_date.add_days(1); ++days_count; }
		
		return days_count;
	}


	int week_of_year(const Date& dd)
	//На вход: ссылка на объект даты
	//На выходе: номер недели в году (год берется из даты подаваемой на вход)
	{
		Date first_date (1, Month::january, dd.year()); //Первая дата в году)
		
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