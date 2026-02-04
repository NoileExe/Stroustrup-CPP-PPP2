

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <map>
#include <numeric>
#include <typeinfo>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T1, typename T2>
ostream& operator<<(ostream &ost, const pair<T1, T2>& ptt)
{
	ost << ptt.first << '\t' << ptt.second;
	return ost;
}

template<typename T1, typename T2>
ostream& operator<<(ostream &ost, const map<T1, T2>& mtt)
{
	for(const auto& p : mtt)		ost << p << endl;
	return ost;
}

template<typename T1, typename T2>
istream& operator>>(istream &ist, map<T1, T2>& mtt)
{
	T1 k {};
	T2 v {};
	
	ist >> k >> v;
	
	if( (k == T1{}  ||  v == T2{}  || ist.bad())  &&  !ist.eof() )
		error("bad input ( operator>> for map<" + std::string(typeid(T1).name()) + ", " + std::string(typeid(T2).name()) + "> object )");
	
	if( ist.eof() ) {
		ist.clear(ios_base::failbit);
		return ist;
	}
	
	//ist.clear();
	mtt[k] = v;
	return ist;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			map<string, int> msi;
			
			msi["A"] = 1;
			msi["Y"] = 2;
			msi["C"] = 3;
			msi["B"] = 4;
			msi["D"] = 5;
			msi["W"] = 6;
			msi["J"] = 7;
			msi["H"] = 8;
			msi["T"] = 9;
			msi["U"] = 10;
			
			cout << "\n\tmap<string, int> 10 values:\n\n" << msi;		//Вывод значений map на экран
			cout << "\n--------------------------------------------------------------------------\n";
			
			msi.erase("C");
			msi.erase("B");
			cout << "\n\tErase 2 values:\n\n" << msi;					//Вывод значений map на экран
			cout << "\n--------------------------------------------------------------------------\n";
			
			cout << "Input new value in next format: key(string) value(int)\n";
			for(int i = 0;   i < 10  &&  cin >> msi;   ++i)		cout << "Input new value in next format: key(string) value(int)\n";
			
			cout << "\n\tInput 0-10 values:\n\n" << msi;				//Вывод значений map на экран
			cout << "\n--------------------------------------------------------------------------\n";
			
			cout << "\n\tSumm for all values:\t" << accumulate(msi.begin(), msi.end(), 0, [](int v, pair<string, int> m) { return v + m.second; } );
			cout << "\n--------------------------------------------------------------------------\n";
			
			map<int, string> mis;
			for(const auto& p : msi)		mis[p.second] = p.first;
			cout << "\n\tConvert to map<int, string>:\n\n" << mis;		//Вывод значений map на экран
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