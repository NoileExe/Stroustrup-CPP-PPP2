// This is example code from Chapter 9.8 "The Date class" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <std_lib_facilities.h>

//namespace Chrono {

class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
	Date(int y, Month m, int d);	// check for valid date and initialize
	Date();							// default constructor

	int		day()	const { return d; }
	Month	month()	const { return m; }
	int		year()	const { return y; }

	void add_days(int);
	void add_month(int);
	void add_year(int);
private:
	int   y;
	Month m;
	int   d;
};

const Date& default_date();
bool is_date(int y, int m, int d);
bool leapyear(int y);				// true if y is a leap year

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

//}
