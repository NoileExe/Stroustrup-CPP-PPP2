// This is example code from Chapter 9.8 "The Date class" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup

#include <std_lib_facilities.h>

namespace Chrono {
	
	class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z

	enum class Month {
		january=1, february, march, april, may, june, july, august, september, october, november, december
	};

	class Date {
	public:
		Date(int d, Month m, int y);	//Проверка корректности и инициализация
		Date();							//Конструктор по умолчанию

		int   day()   const;	//Константные члены:
		Month month() const;	//			не имеют возможности
		int   year()  const;	//			модифицировать объекты

		void add_days  (int n); //Неконстантные члены:
		void add_month (int n); //  могут модифицировать объекты
		void add_year  (int n);
	private:
		int   d; //День месяца
		Month m; //Месяц
		int   y; //Год
	};

	const Date& default_date();			//Дата по умолчанию для инициализации пустого объекта
	bool is_date(int d, int m, int y);	//Проверка корректности даты
	bool leapyear(int y);				//Возвращает true если 'y' - високосный год

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& dd);

}