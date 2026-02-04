#include "money.h"

namespace nmsp_Money {
	
	Money::Money(long int s)
		: summ(s)
	{
		if (s < 0) error_memb.err_Neg_Num();
	}
	
	
	Money::Money() //конструктор по умолчанию
		: summ (0)
	{
	}
	
	//------------------------------------------------------------------------------
	
	bool operator==(const Money& a, const Money& b)
	{
		return a.ret_summ() == b.ret_summ();
	}
	
	bool operator!=(const Money& a, const Money& b)
	{
		return !(a==b);
	}
	
	//------------------------------------------------------------------------------

	ostream& operator<<(ostream& os, const Money& m)
	//оператор вывода для переменных класса Money
	{
		//return os << "RUB" << m.ret_dbl_summ();
		
		/*return os << int(m.ret_summ()/100) << "руб. "
				    << (  m.ret_dbl_summ() - int(m.ret_summ()/100) )*100.0 << "коп.";*/
		
		return os << m.ret_summ()/100 << "руб. " << m.ret_summ()%100 << "коп.";
	}
	
	void operator>>(istream& is, Money& m)
	{
		double summ = 0;
		
		cout << "\nВведите денежную сумму в формате '123.456':\n";
		
		is >> summ;
		
		if  (is.eof()) m.error_memb.err_CTRLZ();  //"Пользователь ввёл CTRL+Z (#99)"
		else if  (!is) m.error_memb.err_Enter();  //"неверный ввод (#1)"
		
		//Есть тысячные части (десятые части копеек)
		if ( summ*100 - int(summ*100) >= 0.5 )  summ = summ*100 + 1;
		else                                    summ = summ*100;
		
		m = Money(summ); //вносим новые данные в m усекая значение double до целого (long int)
	}

} //namespace nmsp_Money