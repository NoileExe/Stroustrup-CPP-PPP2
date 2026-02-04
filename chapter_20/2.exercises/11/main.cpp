

#include <typeinfo>
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename Iter>
void print_container(Iter first, Iter last) {
	cout << "{ ";
	
	for(auto p = first; p!=last; ++p) {
		auto tmp = p;
		++tmp;
		if(tmp != last)		cout << *p << ", ";
		else				cout << *p ;
	}
	
	cout << " }\n\n";
}

//------------------------------------------------------------------------------

void li2vd(vector<double>& vd, list<int>* li)
{
	for(auto p = (*li).begin(); p!=(*li).end(); ++p)
		vd.push_back(*p);
}

//------------------------------------------------------------------------------

template<typename T>
bool min2max(T a, T b)		{ return a < b; }

int main()
{
	while (true) {
		try
		{
			list<int> li {90,8,3,1,2,1};
			vector<double> vd;
			
			li2vd(vd, &li);
			
			cout << "list<int>:\n";
			print_container(li.begin(), li.end());
			
			cout << "vector<double>:\n";
			print_container(vd.begin(), vd.end());
			
			cout << "vector<double> with sort min to max:\n";
			
			//sort(vd.begin(), vd.end(), std::less<double>());		//От меньшего к большему
			//sort(vd.begin(), vd.end(), std::greater<double>());		//От большего к меньшему
			
			//sort(vd.begin(), vd.end(), min2max<double>);			//От меньшего к большему (своя ф-ция)
			
			sort(vd.begin(), vd.end(), [](auto a, auto b) { return a < b; });	//От меньшего к большему (лямбда ф-ция)
			
			print_container(vd.begin(), vd.end());
			
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