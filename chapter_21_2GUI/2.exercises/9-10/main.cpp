



#include <yes_or_no.h>
#include "Chrono.h"
#include <iterator>
#include <numeric>
#include <set>


const string quit_question = "Close program?";


//------------------------------------------------------------------------------

template<typename Iter>
void out_array(Iter b, Iter e)
{
	cout << "{ ";
		
	for(auto p = b; p != e; ++p) {
		auto tmp = p;
		++tmp;
		
		if(tmp != e)	cout << *p << ", ";
		else			cout << *p;
	}
	
	cout << " }";
}

//------------------------------------------------------------------------------

struct Purchase {
	string name;
	double unit_price;
	int count;
	
	Purchase(const string& s = string{}, double d = 0.0, int i = 0) : name{s}, unit_price(d), count(i)		{  }
};

//Предикат на член name класса Purchase
struct Cmp_Purchase_by_name {
	bool operator() (const Purchase& a, const Purchase& b) const
		{ return a.name < b.name; }
};



struct Order {
	string name;
	string address;
	Chrono::Date birthday;
	vector<Purchase> purchase;
	
	Order(const string& n = string{}, const string& a = string{}, Chrono::Date bd = Chrono::currentDate(), const vector<Purchase>& p = vector<Purchase> {})
		: name{n}, address{a}, birthday{bd}, purchase{p}		{  }
};

//------------------------------------------------------------------------------

//оператор вывода для переменных класса Purchase
ostream& operator<<(ostream& os, const Purchase& pp)
{
	return os << setw(30) << "\"" + pp.name + "\"" << '\t'
			  << setw(8)  << pp.unit_price << '\t'
			  << setw(6)  << pp.count;
}

//оператор вывода на экран для переменных класса Order
ostream& operator<<(ostream& os, const Order& oo)
{
	os << setw(10) << "Name: " << oo.name << endl
	   << setw(10) << "Birthday: " << oo.birthday << endl
	   << setw(10) << "Address: " << oo.address << endl
	   << setw(10) << "Purchases: " << endl;
	
	for(auto& p : oo.purchase)		os << ' ' << p << '\t' << p.unit_price * p.count << endl;
	os << "\n\n";
	
	return os;
}

//------------------------------------------------------------------------------

//оператор вывода в файл для переменных класса Order
void to_file(ostream& os, const Order& oo)
{
	os  <<   oo.name   << endl
		<< oo.birthday << endl
		<< oo.address  << endl;
	
	for(auto& p : oo.purchase)		os << p << endl;
	os << endl;
}

//Формат ввода следующий:
//
//"название товара 1 в кавычках с пробелами" цена_товара_double  количество_int
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
//Дата рождения
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

int main()
{
	while (true) {
		try
		{
			string file1 {"input1.txt"};
			string file2 {"input2.txt"};
			string out_file {"output.txt"};
			
			fstream fs {file1, fstream::in};		//Открываем поток ввода
			if (!fs)	error("Unable to open file '" + file1 + "'");
			fs.exceptions(fs.exceptions()|ios_base::badbit);
			
			istream_iterator<Order> ii1{fs};		//Создаём итератор ввода
			istream_iterator<Order> eos;			//Ограничитель ввода (итератор по умолчанию, который означает eof)
			
			vector<Order> vo { ii1, eos };
			sort( vo.begin(), vo.end(), [](Order& a, Order& b) { return a.name < b.name; } );
			//sort( vo.begin(), vo.end(), [](Order& a, Order& b) { return a.birthday < b.birthday; } );
			fs.close();
			
			fs.open(file1, fstream::out);			//Открываем поток вывода ( | fstream::app - для добавления в конец файла)
			for(auto& p : vo)		to_file(fs, p);
			fs.close();
			
			//--------------------------------------------------------------------------
			
			fs.open(file2, fstream::in);			//Открываем поток ввода
			if (!fs)	error("Unable to open file '" + file2 + "'");
			fs.exceptions(fs.exceptions()|ios_base::badbit);
			
			list<Order> lo { istream_iterator<Order> {fs}, eos };
			lo.sort(  [](Order& a, Order& b) { return a.address < b.address; }  );
			fs.close();
			
			fs.open(file2, fstream::out);			//Открываем поток вывода ( | fstream::app - для добавления в конец файла)
			for(auto& p : lo)		to_file(fs, p);
			fs.close();
			
			//--------------------------------------------------------------------------
			
			//fs.open(file1, fstream::in);			//Открываем поток ввода1
			//fstream fs2 {file2, fstream::in};		//Открываем поток ввода2
			fstream ofs {out_file, fstream::out};	//Открываем поток вывода
			
			//ii1 = {fs};
			//istream_iterator<Order> ii2 = {fs2};
			ostream_iterator<Order> io{ofs, "\n\n\n"};	//Создаём итератор вывода
			std::merge(vo.begin(), vo.end(),   lo.begin(), lo.end(),   io,   [](Order& a, Order& b) { return true; } );
			
			//--------------------------------------------------------------------------
			
			set <Purchase, Cmp_Purchase_by_name> all_summ {};
			//set<Purchase, [](const Purchase& a, const Purchase& b) { return a.name < b.name; }> all_summ;		//Не работает
			
			for(auto& o : vo)
				for(auto& p : o.purchase)		all_summ.insert(p);
			
			
			double summ {0.0};
			summ = accumulate(vo.begin(), vo.end(), summ,  [](double& v, Order& o)	{
																						for(auto& p : o.purchase)		v += (p.unit_price * p.count);
																						return v;
																					});
			
			summ = accumulate(lo.begin(), lo.end(), summ, [](double& v, Order& o)	{
																						for(auto& p : o.purchase)		v += (p.unit_price * p.count);
																						return v;
																					});
			
			cout.precision(2);
			cout << "The total amount of orders for both files: " << fixed << summ << endl;
			
			//--------------------------------------------------------------------------
			
			keep_window_open("~");
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}