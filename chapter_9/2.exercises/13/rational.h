#include <std_lib_facilities.h>

namespace Rnums {
	
	class Rational {
	public:
		Rational(int full_prt);						//Инициализация лишь целой частью
		Rational(int up, int down);					//Инициализация числителем и знаменателем
		Rational(int full_prt, int up, int down);	//Инициализация целой и дробной (числитель / знаменатель) частями
		Rational();									//конструктор по умолчанию
		
		int ret_full()   const { return full_prt; }
		int ret_up()     const { return up; }
		int ret_down()   const { return down; }
		double ret_dbl() const; //Возвращает число в виде десятичной дроби
		
		void operator=(const Rational& r); //Rational
	private:
		int full_prt;	//целая часть
		int up;			//числитель
		int down;		//знаменатель
	};
	
	int common_down(Rational a, Rational b);	//поиск общего знаменателя
	Rational minimize_it(Rational r);			//сокращение дроби
	Rational unmax_it(Rational r);				//выделение целой части
	Rational maximize_it(Rational r);			//перевод дроби с целой частью в дробь без таковой и с бОльшим числителем
	
	bool operator==(const Rational& a, const Rational& b);
	bool operator!=(const Rational& a, const Rational& b);
	
	Rational operator+(const Rational& a, const Rational& b);
	Rational operator-(const Rational& a, const Rational& b);
	Rational operator*(const Rational& a, const Rational& b);
	Rational operator/(const Rational& a, const Rational& b);
	
	ostream& operator<<(ostream& os, const Rational& r);
	void operator>>(istream& is, Rational& r);

} //namespace Rnums