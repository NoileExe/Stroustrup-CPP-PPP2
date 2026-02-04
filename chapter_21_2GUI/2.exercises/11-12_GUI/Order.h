


#include "Chrono.h"
#include <numeric>
#include <set>


//------------------------------------------------------------------------------

struct Purchase {
	string name;
	double unit_price;
	int count;
	
	Purchase(const string& s = string{}, double d = 0.0, int i = 0) : name{s}, unit_price(d), count(i)		{  }
};

//Предикат на член name класса Purchase
struct Purchase_by_name {
	bool operator() (const Purchase& a, const Purchase& b) const
		{ return a.name < b.name; }
};

//Предикат на член unit_price класса Purchase
struct Purchase_by_price {
	bool operator() (const Purchase& a, const Purchase& b) const
		{ return a.unit_price < b.unit_price; }
};

//Предикат на член count класса Purchase
struct Purchase_by_count {
	bool operator() (const Purchase& a, const Purchase& b) const
		{ return a.count < b.count; }
};

//------------------------------------------------------------------------------

struct Order {
	string name;
	string address;
	Chrono::Date birthday;
	vector<Purchase> purchase;
	
	Order(const string& n = string{}, const string& a = string{}, Chrono::Date bd = Chrono::currentDate(), const vector<Purchase>& p = vector<Purchase> {})
		: name{n}, address{a}, birthday{bd}, purchase{p}		{  }
};

//Предикат на член name класса Order
struct Order_by_name {
	bool operator() (const Order& a, const Order& b) const
		{ return a.name < b.name; }
};

//Предикат на член birthday класса Order
struct Order_by_birthday {
	bool operator() (const Order& a, const Order& b) const
		{ return a.birthday < b.birthday; }
};

//Предикат на член address класса Order
struct Order_by_address {
	bool operator() (const Order& a, const Order& b) const
		{ return a.address < b.address; }
};

//Предикат на член 'vector<Purchase> purchase' класса Order
//Вычисляет две суммы чека (все элементы purchase для текущего Order) для двух сделок (Order)
struct Order_by_purchase {
	bool operator() (const Order& a, const Order& b) const
	{
		double a_summ = accumulate(a.purchase.begin(), a.purchase.end(), 0.0,  [](double& v, const Purchase& p) { return v + p.unit_price * p.count; });
		
		double b_summ = accumulate(b.purchase.begin(), b.purchase.end(), 0.0,  [](double& v, const Purchase& p) { return v + p.unit_price * p.count; });
		
		return a_summ < b_summ;
	}
};

//------------------------------------------------------------------------------

//оператор вывода для переменных класса Purchase
//Формат вывода следующий:
//"название товара в кавычках с пробелами" цена_товара_double  количество_int
ostream& operator<<(ostream& os, const Purchase& pp);

//оператор вывода в файл для переменных класса Order
//Формат вывода следующий:
//пмя с пробелами
//Дата рождения ДД.ММ.ГГГГ
//Адрес с пробелами
//"название товара 1 в кавычках с пробелами" цена_товара_double  количество_int
//"название товара 2 в кавычках с пробелами" цена_товара_double  количество_int
ostream& operator<<(ostream& os, const Order& oo);

//оператор вывода на экран для переменных класса Order
void to_screen(ostream& os, const Order& oo);

//------------------------------------------------------------------------------

//Формат ввода следующий:
//"название товара в кавычках с пробелами" цена_товара_double  количество_int
istream& operator>>(istream& is, Purchase& pp);


//Формат ввода следующий:
//
//пмя с пробелами
//Дата рождения ДД.ММ.ГГГГ
//Адрес с пробелами
//"название товара 1 в кавычках с пробелами" цена_товара_double  количество_int
//"название товара 2 в кавычках с пробелами" цена_товара_double  количество_int
istream& operator>>(istream& is, Order& oo);

//------------------------------------------------------------------------------
