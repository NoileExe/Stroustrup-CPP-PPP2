#include "rational.h"

namespace Rnums {
	
	//Инициализация лишь целой частью
	Rational::Rational(int fp)
		: full_prt(fp), up (0), down (1)
	{
	}
	
	//Инициализация числителем и знаменателем
	Rational::Rational(int u, int d)
		: up(u), down(d)
	{
		if (d == 0)		error("знаменатель не может быть равен нулю ( инициализация Rational числителем и знаменателем )");
		
		if (d < 0)  { d *= -1; u *= -1; } //минус из знаменателя переносим в числитель
		//Вариант когда дробь представляет вид, напр., 0/-3 не рассматриваем, т.к. в любом случае она равна нулю
		//В случае если оба отрицательны срабатывает правило: минус на минус даёт плюс)
		
		
		full_prt = 0;
		up = u;
		down = d;
	}
	
	//Инициализация целой и дробной (числитель / знаменатель) частями
	Rational::Rational(int fp, int u, int d)
		: full_prt(fp), up(u), down(d)
	{
		if (d == 0)		error("знаменатель не может быть равен нулю ( полноценная инициализация Rational )");
		
		if (fp == 0)
		{
			if (d < 0) { d *= -1; u *= -1; }	//минус из знаменателя переносим в числитель
		}
		else
		{
			if (u < 0) { u *= -1; fp *= -1; }	//минус из числителя переносим в целую часть
			
			if (d < 0) { d *= -1; fp *= -1; }	//минус из знаменателя переносим в целую часть
		}
		
		
		full_prt = fp;
		up = u;
		down = d;
	}
	
	//конструктор по умолчанию
	Rational::Rational()
		: full_prt (0), up (0), down (1)
	{
	}
	
	//Возвращает число в виде десятичной дроби
	double Rational::ret_dbl() const
	{
		double answ = 0;
		
		if (full_prt >= 0)
			answ = double(full_prt) + double(up)/double(down);
		else
			answ = double(full_prt) - double(up)/double(down);
			//Т.к. числитель и знаменатель не могут быть отрицательными: минус всегда переносится в целую часть
		
		return answ;
	}
	
	//------------------------------------------------------------------------------
	
	void Rational::operator=(const Rational& r)
	{
		full_prt = r.ret_full();
		up = r.ret_up();
		down = r.ret_down();
	}
	
	//------------------------------------------------------------------------------
	
	int common_down(Rational a, Rational b)
	//поиск общего знаменателя
	{
		int adown = a.ret_down();
		int bdown = b.ret_down();
		
		int min = 0, max = 0;
		
		if (adown == bdown)		return adown; //если знаменатели и так равны - возвращаем сам знаменатель
		else if (adown > bdown) { min = bdown; max = adown; }
		else if (adown < bdown) { min = adown; max = bdown; }
		
		int curr = 0;
		int answ = 0; //возвращаемое значение
		
		for (int i = 2; i < max; ++i)
		//выясняем не яв-ся ли один из знаменателей (наибольший) общим для обеих дробей
		{
			curr = min * i;
			if (curr == max) { answ = max; break; }
		}
		
		if (answ == 0) //если общий знаменатель не найден..
			answ = adown * bdown; //..предполагаем самый простой вариант общего знаменателя
		
		return answ;
	}
	
	Rational minimize_it(Rational r)
	//сокращение текущей дроби
	{
		int full_prt = r.ret_full();	//целая часть
		int up = r.ret_up();			//числитель
		int down = r.ret_down();		//знаменатель
		
		int min = 0, max = 0;
		
		if (abs(up) > down)
			{ min = down;		max = abs(up); }
		else if ( abs(up) < down  ||  up == down )
			{ min = abs(up);	max = down; }
		
		if ( up != 0 && (max-min) < int(2147483648/2.0) ) { // double(min+max) == min+max
			//for (int i = 2; i <= max; ++i)
			for (int i = min; i > 1; --i)
				//Если числитель и знаменатель делятся без остатка на одно число - можно сократить дробь
				if ( up%i == 0 && down%i == 0 )
					{ up /= i;  down /= i; }
		}
		
		/*if ( full_prt == 0  &&  up == 0 )
			return Rational(0, 0, 1);
		else*/
			return unmax_it( Rational(full_prt, up, down) );
	}
	
	Rational unmax_it(Rational r)
	//выделение целой части
	{
		int full_prt = r.ret_full();	//целая часть
		int up = r.ret_up();			//числитель
		int down = r.ret_down();		//знаменатель
		
		//Если числитель больше знаменателя - выделяем целую часть от их деления
		if (abs(up) >= abs(down))
		{
			if (full_prt > 0)
				full_prt += up/down; 
			
			else if (full_prt < 0)
				full_prt -= up/down;
			
			//Если нет целой части - числитель может быть отрицательным (минус из знаменателя всегда переносится в числитель)
			else if (full_prt == 0)
			{
				if (up < 0)		full_prt -= abs(up)/down;
				else			full_prt += abs(up)/down;
			}
				
			 up = abs(up) % down; //Остаток от деления (т.к. целая часть вынесена)
		}
		
		return Rational(full_prt, up, down);
	}
	
	Rational maximize_it(Rational r)
	//перевод дроби с целой частью в дробь без таковой и с бОльшим числителем
	{
		int full_prt = r.ret_full();	//целая часть
		int up = r.ret_up();			//числитель
		int down = r.ret_down();		//знаменатель
		
		if (full_prt != 0)
		{
			up += abs(full_prt * down);
			if (full_prt < 0)
				up *= -1;
		}
		
		return Rational(up, down);
	}
	
	//------------------------------------------------------------------------------
	
	bool operator==(const Rational& a, const Rational& b)
	{
		int afull_prt = a.ret_full();	//целая часть
		int aup = a.ret_up();			//числитель
		int adown = a.ret_down();		//знаменатель
		
		int bfull_prt = b.ret_full();	//целая часть
		int bup = b.ret_up();			//числитель
		int bdown = b.ret_down();		//знаменатель
		
		int cmn_down = common_down(a, b); //Общий знаменатель
		
		//Приводим числитель первой дроби к общему знаменателю
		int acmn = aup*(cmn_down/adown)+abs(afull_prt*cmn_down);
		if ( afull_prt < 0 )
			acmn *= -1;
		
		//Приводим числитель второй дроби к общему знаменателю
		int bcmn = bup*(cmn_down/bdown)+abs(bfull_prt*cmn_down);
		if ( bfull_prt < 0 )
			bcmn *= -1;
		
		//Если при приведении к общему знаменателю числители равны
		if ( acmn == bcmn )		return true;
		else					return false;
	}
	
	bool operator!=(const Rational& a, const Rational& b)
	{
		return !(a==b);
	}
	
	//------------------------------------------------------------------------------
	
	Rational operator+(const Rational& a, const Rational& b)
	{
		int afull_prt = a.ret_full();	//целая часть
		int aup = a.ret_up();			//числитель
		int adown = a.ret_down();		//знаменатель
		
		int bfull_prt = b.ret_full();	//целая часть
		int bup = b.ret_up();			//числитель
		int bdown = b.ret_down();		//знаменатель
		
		int cmn_down = common_down(a, b); //Общий знаменатель
		
		//Приводим числитель первой дроби к общему знаменателю
		int acmn = aup*(cmn_down/adown)+abs(afull_prt*cmn_down);
		if ( afull_prt < 0 )
			acmn *= -1;
		
		//Приводим числитель второй дроби к общему знаменателю
		int bcmn = bup*(cmn_down/bdown)+abs(bfull_prt*cmn_down);
		if ( bfull_prt < 0 )
			bcmn *= -1;
		
		return Rational(acmn+bcmn,cmn_down);
	}
	
	Rational operator-(const Rational& a, const Rational& b)
	{
		int afull_prt = a.ret_full();	//целая часть
		int aup = a.ret_up();			//числитель
		int adown = a.ret_down();		//знаменатель
		
		int bfull_prt = b.ret_full();	//целая часть
		int bup = b.ret_up();			//числитель
		int bdown = b.ret_down();		//знаменатель
		
		int cmn_down = common_down(a, b); //Общий знаменатель
		
		//Приводим числитель первой дроби к общему знаменателю
		int acmn = aup*(cmn_down/adown)+abs(afull_prt*cmn_down);
		if ( afull_prt < 0 )
			acmn *= -1;
		
		//Приводим числитель второй дроби к общему знаменателю
		int bcmn = bup*(cmn_down/bdown)+abs(bfull_prt*cmn_down);
		if ( bfull_prt < 0 )
			bcmn *= -1;
		
		return Rational(acmn-bcmn,cmn_down);
	}
	
	Rational operator*(const Rational& a, const Rational& b)
	{
		int afull_prt = a.ret_full();	//целая часть
		int aup = a.ret_up();			//числитель
		int adown = a.ret_down();		//знаменатель
		
		int bfull_prt = b.ret_full();	//целая часть
		int bup = b.ret_up();			//числитель
		int bdown = b.ret_down();		//знаменатель
		
		
		if (afull_prt > 0 )			aup += afull_prt*adown;
		else if (afull_prt < 0 )	aup = ( aup + abs(afull_prt*adown) ) * (-1);
		
		if (bfull_prt > 0)			bup += bfull_prt*bdown;
		else if (bfull_prt < 0 )	bup = ( bup + abs(bfull_prt*bdown) ) * (-1);
		
		
		return Rational(aup*bup,adown*bdown);
	}
	
	Rational operator/(const Rational& a, const Rational& b)
	{
		int afull_prt = a.ret_full();	//целая часть
		int aup = a.ret_up();			//числитель
		int adown = a.ret_down();		//знаменатель
		
		int bfull_prt = b.ret_full();	//целая часть
		int bup = b.ret_up();			//числитель
		int bdown = b.ret_down();		//знаменатель
		
		
		if (afull_prt > 0 )			aup += afull_prt*adown;
		else if (afull_prt < 0 )	aup = ( aup + abs(afull_prt*adown) ) * (-1);
		
		if (bfull_prt > 0)			bup += bfull_prt*bdown;
		else if (bfull_prt < 0 )	bup = ( bup + abs(bfull_prt*bdown) ) * (-1);
		
		
		return Rational(aup*bdown,adown*bup); //переворачиваем вторую дробь и умножаем
	}
	

	ostream& operator<<(ostream& os, const Rational& r)
	//оператор вывода для переменных класса Rational
	{
		if ( r.ret_full() != 0 ) //Если имеется целая часть
		{
			os << r.ret_full();
			if (r.ret_up() != 0) //Если имеется дробная часть
				os << "(" << r.ret_up() << "/" << r.ret_down() << ")";
		}
		else if ( r.ret_up() != 0 )
			os << r.ret_up() << "/" << r.ret_down();
		else
			os << 0;
		
		return os;
	}

	void operator>>(istream& is, Rational& r)
	{
		int full = 0, up = 0, down = 1;
		char ch1, ch2, ch3;
		
		cout << "\nВведите дробь в формате (только целые числа)"
				"\n'ЦЕЛАЯ_ЧАСТЬ (ЧИСЛИТЕЛЬ/ЗНАМЕНАТЕЛЬ)'"
				"\n\t\tили"
				"\n     'ЧИСЛИТЕЛЬ/ЗНАМЕНАТЕЛЬ': \n";
		
		is >> full >> ch1 >> up; // >> ch2 >> down >> ch3;
		
		if (is.eof()) {
			is.clear(ios_base::failbit);
			//is.ignore();
			throw 99;
		}
		
		else if (!is) {
			is.clear(ios_base::failbit);
			is.ignore();
			error("неверный ввод ( operator>>() )");
		}
		
		if (ch1 != '(') { 
			if (ch1 == '/') { //введена дробь без целой части
				down = up;
				up = full;
				full = 0;
			}
			else { //Ошибка формата ввода
				is.clear(ios_base::failbit);	//Устанавливаем fail bit
				error("неверный ввод ( operator>>() )");
			}
		}
		else {
			is >> ch2 >> down >> ch3;
			if (ch2 != '/' || ch3 != ')') { //Ошибка формата ввода
				is.clear(ios_base::failbit);	//Устанавливаем fail bit
				error("неверный ввод ( operator>>() )");
			}
		}
		
		/*if (is.eof()) {
			is.clear(ios_base::failbit);
			is.ignore();
			throw 99;
		}
		
		else if (!is) {
			is.clear(ios_base::failbit);
			is.ignore();
			error("неверный ввод ( operator>>() )");
		}*/
		
		r = Rational(full, up, down); //вносим новые данные в r
		
		//return is;
	}

} //namespace Rnums