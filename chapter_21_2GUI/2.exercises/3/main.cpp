

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <set>
#include <list>
#include <vector>
#include <fstream>
#include <numeric>
#include <iterator>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

namespace cnt
{

	template<class Iter>
	unsigned long count(Iter first, Iter last)
	{
		unsigned long n {0};
		for(auto p = first; p != last; ++p)		++n;
		return n;
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
			cout << "\n\tvector<double> with elem count "
				 << cnt::count(vd.begin(), vd.end()) << '/' << vd.size()
				 << ":\n\n" << vd;					//Вывод значений vector на экран
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			list<double> ld;
			for(auto& x : vd)		ld.push_back(x);
			cout << "\n\tlist<double> with elem count "
				 << cnt::count(ld.begin(), ld.end()) << '/' << ld.size() << ":\n\n";
			out_array(ld.begin(), ld.end());		//Вывод значений list на экран
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			set<double> sd;
			for(auto& x : vd)		sd.insert(x);
			cout << "\n\tset<double> with elem count "
				 << cnt::count(sd.begin(), sd.end()) << '/' << sd.size() << ":\n\n";
			out_array(sd.begin(), sd.end());		//Вывод значений set на экран
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
			sd.erase(14.15);
			cout << "\n\tset<double> with elem count "
				 << cnt::count(sd.begin(), sd.end()) << '/' << sd.size() << ":\n\n";
			out_array(sd.begin(), sd.end());		//Вывод значений set на экран после удаления одного элемента
			
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