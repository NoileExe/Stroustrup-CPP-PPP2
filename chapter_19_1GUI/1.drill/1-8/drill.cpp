


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
struct S {
	explicit S(T vv = T()) : val{vv}		{ }
	
	T& get(); //{ return val; }
	
private:
	T val;
};

template<typename T> T& S<T>::get() { return val; }

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			S<int>		iv {123};
			S<int>		idv;	//Значение int от конструктора для данного типа по умолчанию
			S<double>	dv {1.23};
			S<char>		cv {'Y'};
			S<string>	sv {"yup!"};
			S< vector<int> > viv { vector<int> {1, 2, 3} };
			
			
			/*cout << "\n\n"
				 << "S<int>\t\t"	<< iv.val << '\n'
				 << "S<int> def\t"	<< idv.val << '\n'
				 << "S<double>\t"	<< dv.val << '\n'
				 << "S<char>\t\t"	<< cv.val << '\n'
				 << "S<string>\t"	<< sv.val << '\n'
				 << "S< vector<int> >\t";
			
			for(auto v : viv.val)		cout << v << ' ';*/
			
			
			cout << "\n\n\n"
				 << "S<int>\t\t"	<< iv.get() << '\n'
				 << "S<int> def\t"	<< idv.get() << '\n'
				 << "S<double>\t"	<< dv.get() << '\n'
				 << "S<char>\t\t"	<< cv.get() << '\n'
				 << "S<string>\t"	<< sv.get() << '\n'
				 << "S< vector<int> >\t";
			
			for(auto v : viv.get())		cout << v << ' ';
			cout << "\n\n";
			
			//if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
		
		keep_window_open();
		return 0;
	}
}