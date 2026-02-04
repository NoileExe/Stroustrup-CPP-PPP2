

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <vector>
#include <numeric>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

namespace cnt
{

	//Подсчитывает кол-во элементов равных заданному
	template<class Iter, class T>
	unsigned long count(Iter first, Iter last, const T& val)
	{
		unsigned long n {0};
		
		if(&*first == nullptr)	return n;	//Помогает если контейнер пуст
		
		for( ;   first != last;   ++first)
			if(*first == val)		++n;
		
		if(*first == val)		++n;
		
		return n;
	}

	template<class Iter, class T>
	Iter find(Iter first, Iter last, const T& val)
	{
		if(&*first == nullptr)	return Iter{};
		
		while(first != last  &&  *first != val)		++first;
		if(*first != val)		return Iter{};
		else					return first;
	}

}

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
			vector<double> v0;//{1.0, 1.0};
			cout << "\n\tvector<double> elem count with value [1.0] "
				 << cnt::count(v0.begin(), --v0.end(), 1.0)
				 << ":\n\n" << v0;										//Вывод значений vector на экран
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			v0.push_back(1.0);
			//v0.push_back(1.0);
			cout << "\n\tvector<double> elem count with value [1.0] "
				 << cnt::count(v0.begin(), --v0.end(), 1.0)
				 << ":\n\n" << v0;										//Вывод значений vector на экран
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			v0.push_back(1.0);
			cout << "\n\tvector<double> elem count with value [1.0] "
				 << cnt::count(v0.begin(), --v0.end(), 1.0)
				 << ":\n\n" << v0;										//Вывод значений vector на экран
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			vector<double> vd { 0.1, 1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.1, 10.11, 11.12, 12.13, 14.15, 15.16, 16.17 };
			auto it = vd.end();
			--it;
			
			double f {5.6};
			cout << "\n\tvector<double> elem count with value [" << f << "] "
				 << cnt::count(vd.begin(), it, f) << ":\n\n" << vd;		//Вывод значений vector на экран
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			double num {6.7};
			auto e = vector<double>::iterator{};
			auto p = cnt::find(vd.begin(), vd.end(), num);
			string str = (p != e) ? "found" : "NOT found";
			cout << "\n\tSearch in vector<double> elem " << num << ": " << str;
			
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