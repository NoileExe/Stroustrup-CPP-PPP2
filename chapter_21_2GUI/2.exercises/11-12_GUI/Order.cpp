


#include "Order.h"


//оператор вывода для переменных класса Purchase
//Формат вывода следующий:
//"название товара в кавычках с пробелами" цена_товара_double  количество_int
ostream& operator<<(ostream& os, const Purchase& pp)
{
	return os << setw(30) << "\"" + pp.name + "\"" << '\t'
			  << setw(8)  << pp.unit_price << '\t'
			  << setw(6)  << pp.count;
}

//оператор вывода в файл для переменных класса Order
//Формат вывода следующий:
//Имя с пробелами
//Дата рождения ДД.ММ.ГГГГ
//Адрес с пробелами
//"название товара 1 в кавычках с пробелами" цена_товара_double  количество_int
//"название товара 2 в кавычках с пробелами" цена_товара_double  количество_int
ostream& operator<<(ostream& os, const Order& oo)
{
	os  <<   oo.name   << endl
		<< oo.birthday << endl
		<< oo.address  << endl;
	
	for(auto& p : oo.purchase)		os << p << endl;
	os << endl;
	
	return os;
}

//оператор вывода на экран для переменных класса Order
void to_screen(ostream& os, const Order& oo)
{
	os << setw(10) << "Name: " << oo.name << endl
	   << setw(10) << "Birthday: " << oo.birthday << endl
	   << setw(10) << "Address: " << oo.address << endl
	   << setw(10) << "Purchases: " << endl;
	
	for(auto& p : oo.purchase)		os << ' ' << p << '\t' << p.unit_price * p.count << endl;
	os << "\n\n";
}

//------------------------------------------------------------------------------

//Формат ввода следующий:
//"название товара в кавычках с пробелами" цена_товара_double  количество_int
istream& operator>>(istream& is, Purchase& pp)
{
	string name {""};
	double unit_price {0.0};
	int count {0};
	
	for(char ch = ' ';   is.get(ch)  &&  ch != '\"';   )
		if( isgraph(ch) )		{ is.putback(ch);		is.clear(ios_base::eofbit); } //Следующая запись не найдена
	
	for(char ch = ' ';   is.get(ch)  &&  ch != '\"';   )		name += ch;
	is >> unit_price >> count;
	
	if(!is  &&  !is.eof())		error("incorrect input [operator>>() for Purchase object]");
	
	pp.name = name;
	pp.unit_price = unit_price;
	pp.count = count;
	
	return is;
}


//Формат ввода следующий:
//
//Имя с пробелами
//Дата рождения ДД.ММ.ГГГГ
//Адрес с пробелами
//"название товара 1 в кавычках с пробелами" цена_товара_double  количество_int
//"название товара 2 в кавычках с пробелами" цена_товара_double  количество_int
istream& operator>>(istream& is, Order& oo)
{
	string name;
	string address;
	Chrono::Date birthday;
	vector<Purchase> purchase;
	
	for(char ch = ' ';  is && isspace(ch);  is.get(ch))		{  }
	if(is) {
		is.unget();
		getline(is, name);
	}
	
	
	for(char ch = ' ';  is && isspace(ch);  is.get(ch))		{  }
	if(is) {
		is.unget();
		is >> birthday;
	}
	
	
	for(char ch = ' ';  is && isspace(ch);  is.get(ch))		{  }
	if(is) {
		is.unget();
		getline(is, address);
	}
	
	
	Purchase pp;
	while(is >> pp)		purchase.push_back(pp);
	
	if(!is  &&  !is.eof())		error("incorrect input [operator>> for Order object]");
	
	oo.name = name;
	oo.address = address;
	oo.birthday = birthday;
	oo.purchase = purchase;
	
	if( name.size() )		is.clear();	//operator>> для Purchase может вернуть is.eof()
	return is;
}

//------------------------------------------------------------------------------