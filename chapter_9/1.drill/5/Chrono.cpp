//Определение функций объявленных в Chrono.h

#include "Chrono.h"

namespace Chrono {
//Определение функций-членов класса Date:

	int		Date::day()		const { return d; }
	Month	Date::month()	const { return m; }
	int		Date::year()	const { return y; }

	Date::Date(int yy, Month mm, int dd) //инициализация новой переменной класса Date
		: y(yy), m(mm), d(dd)
	{
		if (!is_date(yy,int(mm),dd))
			error("дата введена с ошибкой ( инициализация объекта Date )");
	}

	const Date& default_date();

	Date::Date() //при создании пустой переменной класса Date присваиваем дату по ум.
		:y(default_date().year()),
		 m(default_date().month()),
		 d(default_date().day())
	{
	}

	//------------------------------------------------------------------------------

	const Date& default_date()
	//дата по умолчанию (1 янв 2001) для пустой переменной класса Date
	{
		static const Date dd(2001, Month::jan, 1); //начало XXI века
		return dd;
	}

	//------------------------------------------------------------------------------

	int days_in_month(int y, Month m)
	//на вход: год и месяц
	//возврат: количество дней в месяце
	{
		switch (int(m))
		{
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
		
		while (n >= days_in_month(y,m))
		{
			n -= days_in_month(y,m);
			add_month(1);
		}
		
		if ((n+d) > days_in_month(y,m))
		{
			n -= (days_in_month(y,m)-d);
			d = 0;
			add_month(1);
		}
		
		d += n;
	}

	void Date::add_month(int n)
	{
		if (n<0)
			error("кол-во прибавляемых месяцев должно быть положительным ( Date::add_month() )");
		
		while (n > 12)
		{
			add_year(1);
			n -= 12;
		}
		
		if((n+int(m)) > 12)
		{
			add_year(1);
			n -= 12;
		}

		m = Month(int(m)+n);
	}

	void Date::add_year(int n)
	{
		if (m==Month::feb && d==29 && !leapyear(y+n))	// beware of leap years!
		{
				// makes sense for both positive and negative n (n==0 should be impossible here)
				m = Month::mar;		// use March 1 instead of February 29
				d = 1;
		}
		
		y += n;
	}

	//------------------------------------------------------------------------------

	bool is_date(int y, int m, int d)
	//проверка корректности инициализируемой даты
	{
		if (y<1800 || y>2200)
			return false;
		else if (m<1 || m>12)
			return false;
		else if ( d<1 || d > days_in_month( y, Month(m) ) )
			return false;
		else
			return true;
	}

	//------------------------------------------------------------------------------

	bool leapyear(int y)
	{
		// any year divisible by 4 except centenary years not divisible by 400
		if (y%4)	return false;
		
		if (y%100==0 && y%400)	return false;
		
		return	true;
	}

	//------------------------------------------------------------------------------

	bool operator==(const Date& a, const Date& b)
	{
		return a.year()==b.year()
				&& a.month()==b.month()
				&& a.day()==b.day();
	}


	bool operator!=(const Date& a, const Date& b)
	{
		return !(a==b);
	}


	ostream& operator<<(ostream& os, const Date& dd)
	//оператор вывода для переменных класса Date
	{
		return os << '(' << dd.year()
				  << ',' << int(dd.month())
				  << ',' << dd.day()
				  << ')';
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;

		if (cin.eof())
			throw CTRL_Z_throw {};
		
		else if  (!is)
			error("неверный ввод ( operator>>() )");
			//return is;
			
		else if (ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')')	// oops: format error
		{
			is.clear(ios_base::failbit);			// set the fail bit
			error("неверный ввод ( operator>>() )");
			//return is;
		}
		if ( is_date(y,m,d) )
			dd = Date(y,Month(m),d); //вносим новые данные в dd
		else
			error("дата введена с ошибкой ( operator>>() )");

		return is;
	}

//------------------------------------------------------------------------------
}
