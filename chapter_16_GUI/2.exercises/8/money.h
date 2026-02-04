#include <std_lib_facilities.h>

namespace Graph_lib {
	
	struct Money_Unit {
		Money_Unit(string n, double r) : unit_name(n), exchange_rate(r)
		{
			if (isinf(r))		error("value out of range of double (Money_Unit constructor)");
			if (isnan(r))		error("value is not a number (Money_Unit constructor)");
			if (r < 0)			error("negative value (Money_Unit constructor)");
		}
		
		string unit_name;		//имя валюты
		double exchange_rate;	//курс валюты по отношению к рублю (стоимость единицы валюты в рублях)
	};
	
	const Money_Unit error_unit("ERROR_UNIT", 0); //Значение означающее несуществующую валюту
	
	
	//Операторы сравнения
	bool operator==(const Money_Unit& a, const Money_Unit& b)
	{
		return  a.unit_name == b.unit_name
		 && a.exchange_rate == b.exchange_rate;
	}
		
	bool operator!=(const Money_Unit& a, const Money_Unit& b)
	{
		return !(a==b);
	}
	
	double round_05rule(double d)
	//Округление по третьему числу десятичной части числа (передаваемого параметра ф-ции)
	//Возвращает число с точностью до 2 чисел после десятичной запятой
	{
		if ( d*100 - int(d*100) >= 0.5 )    d += 0.01;
		d = ( d*100 - ( d*100 - int(d*100) ) ) / 100;	//обрезаем d до двух чисел после запятой (убираем всё что меньше сотых)
		return d;
	}
}