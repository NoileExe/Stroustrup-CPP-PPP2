#include "money.h"

namespace nmsp_Money {
	
	Money_Unit::Money_Unit(string n, double r)
		: unit_name(n), exchng_rate(r)
	{ 
		if (isinf(r)) err_Over_Double(); 
	}
	
	//------------------------------------------------------------------------------
	
	Money::Money() //конструктор по умолчанию
		: curr_unit(rub), summ(0) //RUB 0
	{
	}
	
	/*Money::Money(Money_Unit u, long int s)
		: curr_unit(u), summ(s)
	//конструктор Money(Money_Unit(string, double), long(int))
	{
		 if (s < 0) err_Neg_Num(); //"инициализация класса Money отрицательным числом (#2)"
	}*/
	
	Money::Money(string u, long int s)
		: curr_unit(string2unit(u)), summ(s)
	//конструктор Money(string, long(int))
	{
		if ( string2unit(u) == error_unit ) err_False_Unit(u); //"недопустимая валюта 'СЧИТАННОЕ_ИМЯ_ВАЛЮТЫ' (#4)"
		
		else if (s < 0) err_Neg_Num(); //"инициализация класса Money отрицательным числом (#2)"
	}
	
	Money::Money(Money_Unit u, double s)
		: curr_unit(u), summ(s)
	//конструктор  Money(Money_Unit(string, double), double)
	//P.S.: значение double обязательно с десятичной зпт, например: 123.0
	{
		s = round_05rule(s)*100.0;
		
		if ( s < 0 )				err_Neg_Num();		//"инициализация класса Money отрицательным числом (#2)"
		else if ( s != long(s) )	err_Over_LongInt();	//"значение вышло за пределы диапазона long int (#5)" //s > 0 && long(s) < 0
		else if ( isinf(s) )		err_Over_Double();	//"значение вышло за пределы диапазона double (#6)"
		 
		 curr_unit = u;
		 summ = s;
	}
	
	Money::Money(string u, double s)
		: curr_unit(string2unit(u)), summ(s)
	//конструктор  Money(string, double)
	//P.S.: значение double обязательно с десятичной зпт, например: 123.0
	{
		s = round_05rule(s)*100.0;
		
		if ( string2unit(u) == error_unit ) err_False_Unit(u); //"недопустимая валюта 'СЧИТАННОЕ_ИМЯ_ВАЛЮТЫ' (#4)"
		
		else if ( s < 0 ) err_Neg_Num(); //"инициализация класса Money отрицательным числом (#2)"
		else if ( s != long(s) )  err_Over_LongInt(); //"значение вышло за пределы диапазона long int (#5)"
		else if (isinf(s)) err_Over_Double(); //"значение вышло за пределы диапазона double (#6)"
		
		curr_unit = string2unit(u);
		summ = s;
	}
	
	//------------------------------------------------------------------------------
	
	bool operator==(const Money& a, const Money& b)
	{
		return  a.ret_unit() == b.ret_unit()
			 && a.ret_summ() == b.ret_summ();
	}
	
	bool operator!=(const Money& a, const Money& b)
	{
		return !(a==b);
	}
	
	bool operator==(const Money_Unit& a, const Money_Unit& b)
	{
		return  a.unit_name == b.unit_name
		   && a.exchng_rate == b.exchng_rate;
	}
		
	bool operator!=(const Money_Unit& a, const Money_Unit& b)
	{
		return !(a==b);
	}
	
	//------------------------------------------------------------------------------
	
	Money_Unit string2unit(string s)
	//Возвращает Money_Unit из вектора Units в зависимости от значения строки ИЛИ
	//  Money_Unit error_unit ("ERROR_UNIT", 0) если такой валюты не предусмотренно перечислением
	{
		if		(s == rub.unit_name)	return rub;
		else if (s == byn.unit_name)	return byn;
		else if (s == uah.unit_name)	return uah;
		else if (s == usd.unit_name)	return usd;
		else if (s == eur.unit_name)	return eur;
		else if (s == gbp.unit_name)	return gbp;
		else if (s == cny.unit_name)	return cny;
		else if (s == jpy.unit_name)	return jpy;
		else							return error_unit;
	}
	
	double convert_to_rub(const Money& a)
	//Возвращает число вычисленное из объекта Money переведом в рубли 
	//по курсу указанному в объекте (Money_Unit unit.exchng_rate)
	{
		return round_05rule(a.ret_dbl_summ() * a.ret_unit().exchng_rate);
	}
	
	double convert2unit(const Money& a, string s)
	/*Возвращает число вычисленное из объекта Money переведом в указанную 
	в строковом параметре валюту по курсу данной валюты по отношению к рублю
	P.S.: s обязательно должен совпадать с одним из константных, заранее определённых Money_Unit unit_name*/
	{
		if (s == a.ret_unit().unit_name)	return a.ret_dbl_summ();
		//Если объект и так хранит значение в данной валюте, то вычисления проводить нет смысла
		
		else if (string2unit(s) == error_unit) err_False_Unit(s); //"недопустимая валюта 'СЧИТАННОЕ_ИМЯ_ВАЛЮТЫ' (#4)"
		
		double rate = string2unit(s).exchng_rate; //курс валюты по отношению к рублю
		double summ = convert_to_rub(a); //сначала переводим в рубли
		return round_05rule(summ / rate);
	}
	
	double convert2unit(const Money& a, const Money& b)
	//Возвращает число вычисленное из объекта Money переведом в валюту, указанную 
	//во втором параметре (объект Money) по курсу данной валюты по отношению к рублю
	{
		if (a.ret_unit() == b.ret_unit())	return a.ret_dbl_summ();
		//Если объекты и так хранит значение в одинаковой валюте, то вычисления проводить нет смысла
		
		double rate = b.ret_unit().exchng_rate; //курс валюты по отношению к рублю
		double summ = convert_to_rub(a); //сначала переводим в рубли
		return round_05rule(summ / rate);
	}
	
	//------------------------------------------------------------------------------
	
	double round_05rule(double d)
	//Округление по третьему числу десятичной части числа (передаваемого параметра ф-ции)
	//Возвращает число с точностью до 2 чисел после десятичной запятой
	{
		if ( d*100 - int(d*100) >= 0.5 )    d += 0.01;
		
		d = ( d*100 - ( d*100 - int(d*100) ) ) / 100;
		//обрезаем d до двух чисел после запятой (убираем всё что меньше сотых)
		
		return d;
	}
	
	Money operator+(const Money& a, const Money& b)
	//Возвращает объект Money представляющий собой сумму значений двух других объектов переведённых в рубли
	{
		double summ = 0;
		
		//summ = ( a.ret_dbl_summ() / a.ret_unit().exchng_rate ) + ( b.ret_dbl_summ() / b.ret_unit().exchng_rate );
		
		summ = convert_to_rub(a) + convert_to_rub(b);
		
		return Money( rub, summ ); //рубли, сумма
	}
	
	Money operator-(const Money& a, const Money& b)
	//Возвращает объект Money представляющий собой разность значений двух других объектов переведённых в рубли
	{
		double sub = 0;
		
		//sub = ( a.ret_dbl_summ() / a.ret_unit().exchng_rate ) - ( b.ret_dbl_summ() / b.ret_unit().exchng_rate );
		
		sub = convert_to_rub(a) - convert_to_rub(b);
		
		return Money( rub, abs(sub) ); //рубли, разность
	}
	
	//"попытка использовать недопустимый оператор для класса Money (#3)"
	void operator*(const Money& a, const Money& b) { err_False_Operator(); }
	
	void operator/(const Money& a, const Money& b) { err_False_Operator(); }
	
	void operator%(const Money& a, const Money& b) { err_False_Operator(); }
	
	//------------------------------------------------------------------------------

	ostream& operator<<(ostream& os, const Money& m)
	//Оператор вывода для переменных класса Money
	{
		return os << m.ret_unit().unit_name << " " << m.ret_dbl_summ();
	}
	
	void operator>>(istream& is, Money& m)
	/*Оператор ввода для переменных класса Money
	Для изменения объекта передаваемого по ссылке использует инициализацию
	посредством 4го конструктора -- Money(string, double)*/
	{
		string unit = "";
		double summ =  0;
		
		cout << "\nВведите денежную сумму в формате 'RUB123.456':\n";
		
		//Полагаем что любая валюта обозначается лишь 3мя буквами
		for (int i = 0; i < 3; ++i)
			unit += is.get();
		
		//for (char i = ' '; is.get(i); )
		//	unit += i;
		
		is >> summ;
		
		if (is.eof()) err_CTRLZ();  //"Пользователь ввёл CTRL+Z (#99)"
		else if (!is) err_Enter();  //"неверный ввод (#1)"
		
		m = Money(unit, summ);
		//пытаемся внести новые данные в m (конструктор Money(string, double))
		//значение double усекается до целого (double)
	}
	
	//------------------------------------------------------------------------------
	
	const string first_word = "\n\nОшибка: ";
	
	void clr_enter()
	{
		string str;
		getline(cin, str);
		cin.clear();
	}
	
	void err_Enter()
	{
		clr_enter();
		error(first_word + "неверный ввод (#1)");
	}
	
	void err_Neg_Num()
	{
		clr_enter();
		error (first_word + "инициализация класса Money отрицательным числом (#2)");
	}
	
	void err_False_Operator()
	{
		clr_enter();
		error (first_word + "попытка использовать недопустимый оператор для класса Money (#3)");
	}
	
	void err_False_Unit(string s)
	{
		clr_enter();
		error (first_word + "недопустимая валюта '" + s + "' (#4)");
	}
	
	void err_Over_LongInt()
	{
		clr_enter();
		error (first_word + "значение вышло за пределы диапазона long int (#5)");
	}
	
	void err_Over_Double()
	{
		clr_enter();
		error (first_word + "значение вышло за пределы диапазона double (#6)");
	}
	
	void err_CTRLZ()
	{
		clr_enter();
		string s = "Пользователь ввёл CTRL+Z (#99)";
		//string s = " ";
		throw 99;
	}
		
} //namespace nmsp_Money