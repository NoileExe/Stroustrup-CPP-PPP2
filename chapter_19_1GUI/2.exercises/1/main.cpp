


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
void f(vector<T>& v1, const vector<T>& v2)
{
	/*if (v1.size() > v2.size())
		throw error("size of v1 > size of v2");*/
	
	
	/*int max {-1};
	
	if(v1.size() < v2.size())	max = v1.size();
	else						max = v2.size();	//Размер второго вектора меньше или равен размеру первого
	
	for(int i=0; i < max; ++i)		v1[i] += v2[i];*/
	
	
	for(int i=0; i < v1.size(); ++i)		v1[i] += v2[i % v2.size()];
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
			vector<string> vstr2 {"def", "456", "sdfa"};
			cout << "vstr1: " << vstr1 << endl;
			cout << "vstr2: " << vstr2 << endl;
			
			f(vstr1,vstr2);
			cout << "RES: " << vstr1 << "\n\n";


			vector<char> vch1 {'a', 'a', '0'};
			vector<char> vch2 {'c', 'c', '0'};
			cout << "vch1: " << vch1 << endl;
			cout << "vch2: " << vch2 << endl;
			
			f(vch1,vch2);
			cout << "RES: " << vch1 << "\n\n";


			vector<int> vint1 {1, 2, 3, 4};
			vector<int> vint2 {5, 6};
			cout << "vint1: " << vint1 << endl;
			cout << "vint2: " << vint2 << endl;
			
			f(vint1,vint2);
			cout << "RES: " << vint1 << "\n\n";


			vector<double> vdbl1 {1, 2, 3, 4};
			vector<double> vdbl2 {5.2, 6.3};
			cout << "vdbl1: " << vdbl1 << endl;
			cout << "vdbl2: " << vdbl2 << endl;
			
			f(vdbl1,vdbl2);
			cout << "RES: " << vdbl1 << "\n\n";
			
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