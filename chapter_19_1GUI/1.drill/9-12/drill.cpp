


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
struct S {
	explicit S(T vv = T()) : val{vv}		{ }
	
	T& get() { return val; }
	const T& get() const { return val; }
	void set(const T& vv) { val = vv; }
	S& operator=(const T&);
	
private:
	T val;
};

template<typename T>
S<T>& S<T>::operator=(const T& vv)
{
	val = vv;
	return *this;
}


template<typename T>
void read_val(T& v) { cin >> v.get(); }

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			S<int>		iv {123};
			S<int>		idv;	//Значение int от конструктора для данного типа по умолчанию
			S<double>	dv {1.23};
			const S<double>	dcv {1.23};
			S<char>		cv {'Y'};
			S<string>	sv {"yup!"};
			S< vector<int> > viv { vector<int> {1, 2, 3} };
			
			iv.set(321);
			dv = 3.21;
			//dcv = 3.21; //компилятор выдает ошибка как и должно быть
			
			cout << "Enter new char value of S<char> ";
			read_val(cv);
			
			cout << "\n"
				 << "S<int>\t\t"		<< iv.get()  << '\n'
				 << "S<int> def\t"		<< idv.get() << '\n'
				 << "S<double>\t"		<< dv.get()  << '\n'
				 << "S<dbl> const\t"	<< dcv.get() << '\n'
				 << "S<char>\t\t"		<< cv.get()  << '\n'
				 << "S<string>\t"		<< sv.get()  << '\n'
				 << "S< vector<int> >\t";
			
			for(auto v : viv.get())		cout << v << ' ';
			cout << "\n\n";
			
			keep_window_open();
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