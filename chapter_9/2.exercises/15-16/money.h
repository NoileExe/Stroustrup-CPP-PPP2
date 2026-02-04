#include <std_lib_facilities.h>

/*Вызываемые throw-ошибки string типа:
 * 1 - "неверный ввод (#1)"
 * 2 - "инициализация класса Money отрицательным числом (#2)"
 * 3 - "попытка использовать недопустимый оператор для класса Money (#3)"
 * 4 - "недопустимая валюта 'СЧИТАННОЕ_ИМЯ_ВАЛЮТЫ' (#4)"
 * 5 - "значение вышло за пределы диапазона long int (#5)"
 * 
 * 6 - "значение вышло за пределы диапазона double (#6)"
 * 
 * 99 - на ввод подана комбинация CTRL+Z
 * 
 * 
Валюты и курсы валют неизменны и используются только те что имеются в векторе vector<Money_Unit> Units

Единственная возможность создать объект класса Money 
с отсутствующей валютой в вышеупомянутом векторе - использовать конструктор Money(Money_Unit, long int)
*/

namespace nmsp_Money {
	
	struct Money_Unit {
		Money_Unit(string, double);
		
		void operator=(const Money_Unit& a)
			{ unit_name = a.unit_name; exchng_rate = a.exchng_rate; }
		
		string unit_name;   //имя валюты
		double exchng_rate; //курс валюты по отношению к рублю
	};
	
	//Курс валют на конец 20.12.2020:
	const Money_Unit rub("RUB", 1);			//российский рубль
	const Money_Unit byn("BYN", 29.2747);	//белоруский рубль
	const Money_Unit uah("UAH", 2.6401);	//украинская гривна
	const Money_Unit usd("USD", 73.3155);	//доллар асашай
	const Money_Unit eur("EUR", 89.8262);	//евро
	const Money_Unit gbp("GBP", 99.2692);	//британский фунт стерлинга
	const Money_Unit cny("CNY", 11.2069);	//китайский юань
	const Money_Unit jpy("JPY", 0.7079);	//японские иены
	const Money_Unit error_unit("ERROR_UNIT", 0); //Значение означающее несуществующую валюту
	
	
	class Money
	//Поддерживает операции + И -
	{
	public:
		Money(); //конструктор по умолчанию
		//Money(Money_Unit, long int); //Проблемный конструктор, поэтому отключен
		Money(string, long int);
		Money(Money_Unit, double);
		Money(string, double);
		
		Money_Unit ret_unit()   const { return curr_unit; }
		long int   ret_summ()   const { return summ; }
		double ret_dbl_summ()   const { return summ/100.0; }
		
		void operator=(const Money& a) { curr_unit = a.ret_unit(); summ = a.ret_summ(); }
	private:
		Money_Unit curr_unit;	//денежная единица
		long int summ;			//денежная сумма в копейках
	};
	
	bool operator==(const Money& a, const Money& b);
	bool operator!=(const Money& a, const Money& b);
	bool operator==(const Money_Unit& a, const Money_Unit& b);
	bool operator!=(const Money_Unit& a, const Money_Unit& b);
	
	Money operator+(const Money& a, const Money& b);	//сложение (Money+Money)
	Money operator-(const Money& a, const Money& b);	//вычитание (Money-Money)
	void operator*(const Money& a, const Money& b);		//недопустимая для данного класса операция
	void operator/(const Money& a, const Money& b);		//недопустимая для данного класса операция
	void operator%(const Money& a, const Money& b);		//недопустимая для данного класса операция
	
	double round_05rule(double d); //Округление по третьему числу десятичной части числа
	
	Money_Unit string2unit(string); //перевод строки в валюту
	double convert_to_rub(const Money& a); //перевод в рубли
	double convert2unit(const Money& a, string s);
	//перевод в валюту указанную в параметре string по предопределённому курсу
	double convert2unit(const Money& a, const Money& b);
	//перевод в валюту указанную в параметре b (Money_Unit curr_unit.unit_name)
	//по курсу из того же параметра b (Money_Unit curr_unit.exchng_rate)
	
	ostream& operator<<(ostream& os, const Money& m); //оператор вывода для объектов класса Money
	void     operator>>(istream& is, Money& m); //оператор ввода для объектов класса Money
	
	//------------------------------------------------------------------------------
	
	void clr_enter(); //очистка потока ввода
	
	void err_Enter();				//"неверный ввод (#1)"
	void err_Neg_Num();				//"инициализация класса Money отрицательным числом (#2)"
	void err_False_Operator();		//"попытка использовать недопустимый оператор для класса Money (#3)"
	void err_False_Unit(string s);	//"недопустимая валюта 'СЧИТАННОЕ_ИМЯ_ВАЛЮТЫ' (#4)"
	void err_Over_LongInt();		//"значение вышло за пределы диапазона long int (#5)"
	void err_Over_Double();			//"значение вышло за пределы диапазона double (#6)"
	void err_CTRLZ();				//"Пользователь ввёл CTRL+Z (#99)"

} //namespace nmsp_Money