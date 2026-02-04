

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <list>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

struct Item {
	string name;
	int iid;
	double value;
	
	Item() : name{""}, iid{0}, value{0}		{  }
	Item(string s, int i, double d) : name{s}, iid{i}, value{d}		{  }
};

//------------------------------------------------------------------------------

ostream& operator<<(ostream &ost, const Item& it)
	{ return   ost << it.iid << '\t' << it.name << '\t' << it.value; }

istream& operator>>(istream &ist, Item& it) {
	string name {""};
	int iid {0};
	double value {0};
	
	ist >> iid >> name >> value;
	
	if( (name == ""  ||  !iid  || !value  || 
		ist.bad())  &&  !ist.eof()           )		error("bad input ( operator>> FOR Item object )");
	
	if( ist.eof() ) {
		ist.clear(ios_base::failbit);
		return ist;
	}
	
	ist.clear();
	//cout <<  iid << ' ' << name << ' ' << value << endl;
	
	it.name = name;
	it.iid = iid;
	it.value = value;
	
	return ist;
}

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream &ost, const list<T>& lt)
{
	for(auto p = lt.begin(); p != lt.end(); ++p)		ost << *p << endl;
	return ost;
}

bool vctr_item_name_less(const Item& a, const Item& b)		{ return a.name < b.name; }

class vctr_equ_to_iid {
	int v;
	
public:
	vctr_equ_to_iid(int vv) : v{vv}		{  }
	bool operator()(const Item& it)		{ return it.iid == v; }
};

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			ifstream ifs {"../input.txt"};									//Открываем поток ввода
			if (!ifs)	error("Unable to open file 'input.txt'");
			ifs.exceptions(ifs.exceptions()|ios_base::badbit);
			
			list<Item> li;
			for(Item it;   li.size() < 10  &&  ifs >> it;   )		li.push_back(it);
			cout << "\n\tFirst 10 values:\n\n" << li;									//Вывод значений списка на экран
			cout << "\n--------------------------------------------------------------------------\n";

			li.sort( vctr_item_name_less );												//Сортировка списка
			cout << "\n\tSort by name:\n\n" << li;										//Вывод значений списка на экран
			cout << "\n--------------------------------------------------------------------------\n";

			li.sort( [](const Item& a, const Item& b) { return a.iid < b.iid; } );		//Сортировка списка
			cout << "\n\tSort by iid:\n\n" << li;										//Вывод значений списка на экран
			cout << "\n--------------------------------------------------------------------------\n";

			/*li.sort( [](const Item& a, const Item& b) { return a.value > b.value; } );//Сортировка списка
			cout << "\n\tSort by value:\n\n" << li;										//Вывод значений списка на экран
			cout << "\n--------------------------------------------------------------------------\n";*/
			
			li.sort( [](const Item& a, const Item& b) { return a.value < b.value; } );	//Сортировка списка
			reverse( li.begin(), li.end() );
			cout << "\n\tSort by value:\n\n" << li;										//Вывод значений списка на экран
			cout << "\n--------------------------------------------------------------------------\n";

			li.push_back(Item{"horse shoe", 99, 12.34});
			li.push_back(Item{"Canon S400", 9988, 499.95});
			cout << "\n\tAdd 2 elements:\n\n" << li;											//Вывод значений списка на экран
			cout << "\n--------------------------------------------------------------------------\n";

			auto p = find_if( li.begin(), li.end(), [](const Item& it) { return it.name == "A"; } );
			if( p != li.end() )		li.erase(p);
			p = find_if( li.begin(), li.end(), [](const Item& it) { return it.name == "horse shoe"; } );
			if( p != li.end() )		li.erase(p);
			cout << "\n\tErase 2 elements by name:\n\n" << li;									//Вывод значений списка на экран
			cout << "\n--------------------------------------------------------------------------\n";

			p = find_if( li.begin(), li.end(), vctr_equ_to_iid{3} );
			if( p != li.end() )		li.erase(p);
			p = find_if( li.begin(), li.end(), vctr_equ_to_iid{9988} );
			if( p != li.end() )		li.erase(p);
			cout << "\n\tErase 2 elements by iid:\n\n" << li;									//Вывод значений списка на экран
			cout << "\n--------------------------------------------------------------------------\n";
			
			
			
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