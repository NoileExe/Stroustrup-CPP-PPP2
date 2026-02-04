#include <std_lib_facilities.h>

/*Вызываемые throw-ошибки string типа:
 * 1 - "неверный ввод (#1)"
 * 2 - "инициализация класса Money отрицательным числом (#2)"
 * 
 * 99 - на ввод подана комбинация CTRL+Z
*/

namespace nmsp_Money {
	
	class Money {
	public:
		struct Invalid {
			const string first_word = "Ошибка: ";
			
			void clr_enter() { string str; getline(cin, str); cin.clear(); }
			
			void err_Enter()
			{ clr_enter();	error(first_word + "неверный ввод (#1)"); }
			
			void err_Neg_Num()
			{ clr_enter();	error(first_word + "инициализация класса Money отрицательным числом (#2)"); }
			
			void err_CTRLZ()
			{ string s = "Пользователь ввёл CTRL+Z (#99)"; clr_enter(); throw 99; }
		};
		Invalid error_memb;
		//Объект структуры Invalid для вызова исключений связанных с работой класса
		
		Money(long int summ);
		Money(); //конструктор по умолчанию
		
		long int ret_summ()     const { return summ; }
		double   ret_dbl_summ() const { return summ/100.0; }
		void operator=(const Money& a) { summ = a.ret_summ(); }
	private:
		long int summ; //денежная сумма
	};
	
	bool operator==(const Money& a, const Money& b);
	bool operator!=(const Money& a, const Money& b);
	
	ostream& operator<<(ostream& os, const Money& m);
	void     operator>>(istream& is, Money& m);

} //namespace nmsp_Money