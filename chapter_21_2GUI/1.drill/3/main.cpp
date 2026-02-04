

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	for(auto p = vt.begin(); p != vt.end(); ++p) {
		auto tmp = p;
		++tmp;
		
		if(tmp != vt.end())		ost << *p << ", ";
		else					ost << *p;
	}
	
	ost << " }";
	
	return ost;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			ifstream ifs {"input.txt"};				//Открываем поток ввода
			if (!ifs)	error("Unable to open file 'input.txt'");
			ifs.exceptions(ifs.exceptions()|ios_base::badbit);
			
			istream_iterator<double> ii{ifs};		//Создаём итератор ввода
			istream_iterator<double> eos;			//Ограничитель ввода (итератор по умолчанию, который означает eof)
			
			vector<double> vd { ii, eos };
			if(vd.size() < 16)		error("the condition for the minimum number of values (min 16) is not met (" + to_string(vd.size()) + ")");
			cout << "\n\tvector<double>:\n\n" << vd;		//Вывод значений vector на экран
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			//vector<int> vi (vd.size());
			//copy(vd.begin(), vd.end(), vi.begin());
			vector<int> vi {vd.begin(), vd.end()};
			cout << "\n\tvector<double>   vector<int> copy:\n\n";		//Вывод значений vector на экран
			for(int i = 0; i < vd.size(); ++i)		cout << setw(16) << vd[i] << setw(18) << vi[i] << endl;
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			double vdsumm = accumulate(vd.begin(), vd.end(), 0.0, plus<double>() );		//Последнее можно было и не писать
			cout << "\n\t\tvector<double> summ:\t" << vdsumm;
			int visumm = accumulate(vi.begin(), vi.end(),  0);
			cout << "\n\tvector<double> - vector<int>:\t" << (vdsumm - visumm);
			cout << "\n\tvector<double> - vector<int>:\t" << inner_product(vd.begin(), vd.end(), vi.begin(), 0.0, plus<double>(), minus<double>());
			//Выполняется операция АККУМУЛЯТОР(изначально 0.0) += (vd[i] - vi[i])
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			reverse(vd.begin(), vd.end());
			cout << "\n\tReverse vector<double>:\n\n" << vd;
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			double midd =  accumulate(vd.begin(), vd.end(), 0.0) / vd.size();
			cout << "\n\tMiddle val for vector<double>:\n\n" << midd;
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			int sz = count_if( vd.begin(), vd.end(), [&](double n) { return n < midd; } );
			vector<double> vd2 ( sz );
			copy_if( vd.begin(), vd.end(), vd2.begin(), [&](double n) { return n < midd; } );
			cout << "\n\tCopy to new vector<double> values less than midd:\n\n" << vd2;
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			sort( vd.begin(), vd.end() );
			cout << "\n\tSorted vector<double>:\n\n" << vd;
			cout << "\n\n--------------------------------------------------------------------------\n";
			
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