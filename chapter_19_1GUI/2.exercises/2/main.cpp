


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

/*template<typename T, typename U>
double f(const vector<T>& vt, const vector<U>& vu)
{
	int max {-1};
	
	if(vt.size() < vu.size())	max = vt.size();
	else						max = vu.size();	//Размер второго вектора меньше или равен размеру первого
	
	double summ {0};
	for(int i=0; i < max; ++i)		summ += vt[i]*vu[i];
	return summ;
}*/

//Только если возможно неявное приведение всех типов к одному из перечисленных
template<typename T, typename U>
typename common_type<T,U,double>::type f(const vector<T>& vt, const vector<U>& vu)
{
	int max {-1};
	
	if(vt.size() < vu.size())	max = vt.size();
	else						max = vu.size();	//Размер второго вектора меньше или равен размеру первого
	
	double summ {0};
	for(int i=0; i < max; ++i)		summ += vt[i]*vu[i];
	return summ;
}


template<typename T>
ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	for(int i = 0; i < vt.size(); ++i)
		if(i != vt.size()-1)	ost << vt[i] << ", ";
		else					ost << vt[i] << " }";
	
	return ost;
}


int main()
{
	while (true) {
		try
		{
			vector<string> vstr1 {"abc", "123"};
			vector<string> vstr2 {"abc", "123"};
			vector<char> vch1 {'a', 'a', '0'};
			vector<char> vch2 {'a', 'a', '0'};
			vector<int> vint1 {1, 2, 3, 4};
			vector<int> vint2 {5, 6};
			vector<double> vdbl1 {1, 2, 3, 4};
			vector<double> vdbl2 {1.1, 2.2, 3.3, 4.5};
			
			/*cout << "vstr1: " << vstr1 << '\n'
				 << "vch1: " << vch1 << '\n'
				 << "RES: " << f(vstr1, vch1) << "\n\n";*/

			/*cout << "vstr1: " << vstr1 << '\n'
				 << "vstr2: " << vstr2 << '\n'
				 << "RES: " << f(vstr1, vstr2) << "\n\n";*/

			cout << "vch2: " << vch2 << '\n'
				 << "vch1: " << vch1 << '\n'
				 << "RES: " << f(vch2, vch1) << "\n\n";

			/*cout << "vstr1: " << vstr1 << '\n'
				 << "vint1: " << vint1 << '\n'
				 << "RES: " << f(vstr1, vint1) << "\n\n";*/

			cout << "vint1: " << vint1 << '\n'
				 << "vint2: " << vint2 << '\n'
				 << "RES: " << f(vint1, vint2) << "\n\n";

			cout << "vdbl1: " << vdbl1 << '\n'
				 << "vdbl2: " << vdbl2 << '\n'
				 << "RES: " << f(vdbl1, vdbl2) << "\n\n";

			cout << "vint1: " << vint1 << '\n'
				 << "vdbl1: " << vdbl1 << '\n'
				 << "RES: " << f(vint1, vdbl1) << "\n\n";

			cout << "vint1: " << vint1 << '\n'
				 << "vdbl2: " << vdbl2 << '\n'
				 << "RES: " << f(vint1, vdbl2) << "\n\n";

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