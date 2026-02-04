

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <set>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

struct Fruit {
	string name;
	int count;
	double unit_price;
	
	Fruit(string s = "", int i = 0, double d = 0.0) : name{s}, count{i}, unit_price{d}		{  }
};

struct Fruit_order {
	bool operator() (const Fruit& a, const Fruit& b) const
		{ return a.name < b.name; }
};

struct Fruit_comparison {
	bool operator() (const Fruit* a, const Fruit* b) const
		{ return a->name < b->name; }
};

//------------------------------------------------------------------------------

ostream& operator<<(ostream &ost, const Fruit& f)
{
	 ost << setw(10) << f.name
		 << " (" << setw(10) << f.unit_price << ")  x  "
		 << setw(3) << f.count << " = " << f.count * f.unit_price;
	
	return ost;
}

ostream& operator<<(ostream &ost, const Fruit* f)
{
	 ost << setw(10) << f->name
		 << " (" << setw(10) << f->unit_price << ")  x  "
		 << setw(3) << f->count << " = " << f->count * f->unit_price;
	
	return ost;
}

template<typename Iter>
void out_array(Iter b, Iter e)
{
	/*cout << "{ ";
	
	
		
	for(auto p = b; p != e; ++p) {
		auto tmp = p;
		++tmp;
		
		if(tmp != e)	cout << *p << ", ";
		else			cout << *p;
	}
	
	cout << " }";*/
	
	for(auto p = b; p != e; ++p)		cout << *p << endl;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			set<Fruit, Fruit_order> inventory1;
			
			inventory1.insert(Fruit {"quince", 5});
			inventory1.insert(Fruit {"apple", 200, 0.37});
			inventory1.insert(Fruit {});
			out_array(inventory1.begin(), inventory1.end());
			
			cout << "\n--------------------------------------------------------------------------\n\n";
			
			set<Fruit*, Fruit_comparison> inventory2;
			
			inventory2.insert(new Fruit {"quince", 10, 0.30});
			inventory2.insert(new Fruit {"apple",  50, 0.50});
			inventory2.insert(new Fruit { "qiwi",  30, 0.77});
			out_array(inventory2.begin(), inventory2.end());
			
			for(auto p = inventory2.begin(); p != inventory2.end(); ++p)
				delete *p;
			
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