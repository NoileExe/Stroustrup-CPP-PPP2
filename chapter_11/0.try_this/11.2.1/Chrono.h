//Со всеми изменениями из главы 9 включая изменения вплоть до 11 упражнения этой главы

#include <std_lib_facilities.h>
#include <time.h>

namespace Chrono {
	
	class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z

	enum class Month {
		january=1, february, march, april, may, june, july, august, september, october, november, december
	};

	class Date {
	public:
		Date(int d, Month m, int y);	//Проверка корректности и инициализация
		Date();							//Конструктор по умолчанию
		
		//Константные члены не имеют возможности модифицировать объекты
		int   day()   const { return d; }
		Month month() const { return m; }
		int   year()  const { return y; }
		
		//Неконстантные члены могут модифицировать объекты
		void add_days  (int n);
		void add_month (int n);
		void add_year  (int n);
	private:
		int   d; //День месяца
		Month m; //Месяц
		int   y; //Год
	};

	const Date& default_date();			//Дата по умолчанию для инициализации пустого объекта
	bool is_date(int d, int m, int y);	//Проверка корректности даты

	Date currentDate(); //Получение текущей даты в формате подходящем для Chrono::Date

	int days_in_month(Month m, int y); //Кол-во дней в месяце

	bool leapyear(int y);	//Возвращает true если 'y' - високосный год

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& dd);



	enum Day {	// sunday==0
		sunday=0, monday, tuesday, wednesday, thursday, friday, saturday
	};

	ostream& operator<<(ostream& os, Day d);
	Day day_of_week(const Date& dd);	//Какой день недели был в определённую дату
	Date next_workday(Date dd);			//Следующий рабочий день от указанной даты (все кроме сбт и вск)
	int day_of_year (const Date& dd);	//Номер дня в году для указанной даты
	int week_of_year(const Date& dd);	//Номер недели в году, в которую включена указанная дата

}