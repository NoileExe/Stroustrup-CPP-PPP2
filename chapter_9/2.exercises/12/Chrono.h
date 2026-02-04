// This is example code from Chapter 9.8 "The Date class" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <std_lib_facilities.h>
#include <time.h>

namespace Chrono {

	class CTRL_Z_throw { }; //Для вызова исключения при вводе CTRL+Z
	
	enum class Month {
		jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date {
	public:
		
		Date(int bday, int bmonth, int byear, int d, Month m, int y);
		//проверка правильности инициализируемой даты через is_date() и инициализация
		//с изменением начальной даты по умолчанию (членов bday, bmonth и byear)
		
		Date(int d, Month m, int y);
		//проверка правильности инициализируемой даты через is_date() и инициализация
		//(bday, bmonth и byear - по умолчанию 1.1.1970)
		
		
		Date(); //конструктор по умолчанию
		
		void Chg_begin_date();	//Позволяет изменить bday, bmonth и byear для текущего объекта Date
		void ScrOut_Dates();	//Выводит начальную дату (bday, bmonth и byear), за ней текущую дату хранящуюся в d, m, y
								// и в конце кол-во дней между ними (between_begin_n_end)
		
		int   day()   const { return d; }
		Month month() const { return m; }
		int   year()  const { return y; }
		
		int   begin_day()   const { return bday; }
		int   begin_month() const { return bmonth; }
		int   begin_year()  const { return byear; }

		void add_days  (int n); //Неконстантные члены:
		void add_month (int n); //      могут модифицировать объекты
		void add_year  (int n);
	private:
		/*Требует от пользователя соблюдение условия:
				ТЕКУЩАЯ_ДАТА >= НАЧАЛЬНАЯ_ДАТА
		Для этого выводит информацию и просит ввести новую нач.дату.
		После ввода стирает с экрана инфо и введенное пользователем.*/
		//посредством изменения начальной даты
		void test_begin_date();
		
		//Вычисляет кол-во дней между двумя датами с соблюдением условия test_begin_date()
		long int days_after_begin();
		long int between_begin_n_end; //кол-во дней между двумя датами
		
		int bday = 1;		//День месяца нач. даты
		int bmonth = 1;		//Месяц нач. даты
		int byear = 1970;	//Год нач. даты
		
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