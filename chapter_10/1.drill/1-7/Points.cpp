
#include "Points.h"


namespace points {
	
	Point::Point(int xx, int yy) //инициализация переменной класса Point
		: x(xx), y(yy)
	{
		/*if (!valid_point(xx, yy))
			error("координаты введены с ошибкой ( инициализация объекта Point )");*/
	}
	
	
	Point::Point() //при создании пустой переменной класса Point присваиваем нулевые коорд.
		:x(0), y(0)
	{
	}
	
	//------------------------------------------------------------------------------
	
	bool operator==(const Point& a, const Point& b)
	{
		return		a.X_coord() == b.X_coord()
				 && a.Y_coord() == b.Y_coord();
	}
	
	
	bool operator!=(const Point& a, const Point& b)
	{
		return !(a==b);
	}
	
	//------------------------------------------------------------------------------
	
	ostream& operator<<(ostream& ost, const Point& p)
	//Оператор вывода для переменных класса Point
	{
		return ost << '[' << p.X_coord() << " ; " << p.Y_coord() << ']';
	}
	
	
	istream& operator>>(istream& ist, Point& p)
	//Оператор ввода для переменных класса Point в формате (x, y)
	{
		int x, y;
		char ch1, ch2, ch3;
		ist >> ch1 >> x >> ch2 >> y  >> ch3;

		if (ist.eof())
			//throw CTRL_Z_throw {};
			return ist;
		
		else if  (!ist)
			error("неверный ввод ( operator>>(Point) )");
			
		else if ( ch1!='[' || ch2!=';' || ch3!=']' ) { //Ошибка формата ввода
			ist.clear(ios_base::failbit);	//Устанавливаем fail bit
			error("неверный ввод ( operator>>(Point) )");
		}
		
		//вносим новые данные в p
		p = Point(x, y);
		
		//ist.ignore();
		return ist;
	}
	
}