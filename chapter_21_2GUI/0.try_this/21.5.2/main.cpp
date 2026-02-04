

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <vector>
#include <numeric>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

struct Record {
	double unit_price;	//Цена
	int units;			//Количество проданных единиц
	
	Record(double d, int i) : unit_price{d}, units{i}
	{
		if(unit_price <= 0)		error("negative or zero value of price");
		if(   units    < 0)		error("negative value of unit's count");
	}
};

//Вычисляет стоимость и накапливает итог
double price(double v, const Record& r)		{ return v + r.unit_price * r.units; }

double f(const vector<Record>& vr)
{
	double total = accumulate(vr.begin(), vr.end(), 0.0, price);
	return total;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			vector<Record> vr {Record(9.99, 30), Record(0.01, 30), Record(25, 4), Record(15, 4)};
			cout << f(vr);
			
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