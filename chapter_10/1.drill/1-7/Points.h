
#include <std_lib_facilities.h>


namespace points {
	
	class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z
	
	
	class Point {
	public:
		Point(int x, int y);	//Проверка корректности и инициализация
		Point();				//Конструктор по умолчанию
		
		//Константные члены не имеют возможности модифицировать объекты
		int X_coord() const { return x; }
		int Y_coord() const { return y; }
		
	private:
		int   x; //абсцисса
		int   y; //ордината
	};
	
	
	bool operator==(const Point& a, const Point& b);
	bool operator!=(const Point& a, const Point& b);

	ostream& operator<<(ostream& os, const Point& p);
	istream& operator>>(istream& is, Point& p);
	
}