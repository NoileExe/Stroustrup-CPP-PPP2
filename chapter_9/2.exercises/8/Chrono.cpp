//Определение функций объявленных в Chrono.h

#include "Chrono.h"

namespace Chrono {
//Определение функций-членов класса Date:

	int   Date::day()   const { return d; }
	Month Date::month() const { return m; }
	int   Date::year()  const { return y; }

	Date::Date(int dd, Month mm, int yy) //инициализация новой переменной класса Date
		: d(dd), m(mm), y(yy)
	{
		if (!is_date(dd, int(mm), yy))
			error("дата введена с ошибкой ( инициализация объекта Date )");
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

//------------------------------------------------------------------------------

	int days_in_month(Month m, int y)
	//на вход: год и месяц
	//возврат: количество дней в месяце
	{
		switch (int(m)) {
			case 2: //в високосный год в феврале 29 дней, иначе 28
				return (leapyear(y)) ? 29 : 28;
			
			case 4: case 6: case 9: case 11:
				return 30;
			
			default:
				return 31;
		}
	}

	void Date::add_days(int s)
	{
		int n = s;
		if (n<0)
			error("кол-во прибавляемых дней должно быть положительным ( Date::add_days() )");
		
		while (n >= days_in_month(m,y)) {
			n -= days_in_month(m,y);
			add_month(1);
		}
		
		if ((n+d) > days_in_month(m,y)) {
			n -= (days_in_month(m,y)-d);
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
		
		if((n+int(m)) > 12) {
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
		if (y<1800 || y>2200)	return false;
		
		else if (m<1 || m>12)	return false;
		
		else if ( d<1 || d > days_in_month( Month(m), y ) ) return false;
		
		else					return true;
	}

//------------------------------------------------------------------------------

	bool leapyear(int y)
	{
		// any year divisible by 4 except centenary years not divisible by 400
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
	//в формате: дд.мм.гггг
	{
		return os << dd.day() << '.' << int(dd.month())
				  << '.' << dd.year() << " г.";
	}

	istream& operator>>(istream& is, Date& dd)
	//оператор ввода для переменных класса Date
	//в формате: дд.мм.гггг
	{
		int d, m, y;
		char ch1, ch2;
		is >> d >> ch1 >> m >> ch2 >> y;

		if (cin.eof())
			throw CTRL_Z_throw {};
		
		else if  (!is)
			error("неверный ввод ( operator>>() )");
			//return is;
		
		else if (ch1!='.' || ch2!='.') { //Ошибка формата ввода
			is.clear(ios_base::failbit);	//Устанавливаем fail bit
			error("неверный ввод ( operator>>() )");
		}
		
		if ( is_date(d,m,y) )
			dd = Date(d, Month(m), y); //вносим новые данные в dd
		else
			error("дата введена с ошибкой ( operator>>() )");
		
		is.ignore();
		return is;
	}

//------------------------------------------------------------------------------
}