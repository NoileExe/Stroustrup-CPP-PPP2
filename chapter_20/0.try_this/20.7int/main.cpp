

#include <typeinfo>
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	for(int i = 0; i < vt.size(); ++i)
		if(i != vt.size()-1)	ost << vt.at(i) << ", ";
		else					ost << vt.at(i);
	
	ost << " }";
	
	return ost;
}


template<typename T>
void f(const T& ivls)
{
	int sz {0};
	
	vector<int> vi {1, 2, 3, 4, 5};
	vector<int> vn {1, 3, 4, 4, 5};
	//vector<int> vn {1, 2, 3};
	//vector<int> vn {1, 2, 3, 4, 5, 6};
	vector<int> arg {};
	
	//Работают так же хорошо как и вариант ниже
	//for(auto v : ivls)
	//for(const auto& v : ivls)
		//{ arg.push_back(v);		++sz; }
	
	for(auto p = begin(ivls); p!=end(ivls); ++p)	{ arg.push_back(*p);	++sz; }
	
	cout << "\nsize: " << sz << "\n\t";
	
	//--------------------------------------------------------------------------
	
	bool vequ { (vi.size() != arg.size())  ?  false : true };	//Указывает на то равны векторы или нет
	
	for(int i = 0; i < vi.size()  &&  vequ; ++i)
		if(vi[i] != arg[i])		vequ = false;
	
	if( !vequ )		cout << "NOT ";
	cout << "equale with " << vi << " vector" << "\n\t";
	
	//--------------------------------------------------------------------------
	
	vequ = (vn.size() != arg.size())  ?  false : true;
	
	for(int i = 0; i < vn.size()  &&  vequ; ++i)
		if(vn[i] != arg[i])		vequ = false;
	
	if( !vequ )		cout << "NOT ";
	cout << "equale with " << vn << " vector" << "\n\n";
	
	//--------------------------------------------------------------------------
	
	auto cpy {ivls};
	cout << "fnct arg object type is:\t" << typeid(ivls).name() << endl;
	cout << "copied object type is:\t\t" << typeid(cpy).name() << endl;
	
	//Унифицировать получение данных из cpy для всех типов не получилось
}


int main()
{
	while (true) {
		try
		{
			int				i_int[]	{1, 2, 3, 4, 5};
			vector<int>		i_vct	{1, 2, 3, 4, 5};
			list<int>		i_lst	{1, 2, 3, 4, 5};
			
			f(i_int);
			f(i_vct);
			f(i_lst);
			
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