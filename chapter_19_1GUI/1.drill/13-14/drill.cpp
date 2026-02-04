


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
ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	for(int i = 0; i < vt.size(); ++i)
		if(i != vt.size()-1)	ost << vt[i] << ", ";
		else					ost << vt[i] << " }";
	
	return ost;
}

template<typename T>
istream& operator>>(istream &ist, vector<T>& vt) {
	char ch{0};
	ist >> ch;
	if (ch != '{') {
		ist.clear(ios_base::failbit);
		return ist;
	}
	
	//Добавление элеметов к существующему вектору
	/*for(T v; ist >> v; ) {
		vt.push_back(v);
		ist >> ch;
		if (ch != ',')		break;
	}*/
	
	//Перезапись вектора с новыми значениями
	vector<T> buf;
	for(T v; ist >> v; ) {
		buf.push_back(v);
		ist >> ch;
		if (ch != ',')		break;
	}
	
	if(ist.bad() || ch !='}')		error("bad input ( operator>> FOR vector<T> )");
	ist.clear();
	
	if(buf.size() > 0 )		vt = buf;
	
	return ist;
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
			S<double>	dv {1.23};
			S<char>		cv {'Y'};
			S<string>	sv {"yup!"};
			S< vector<int> > viv { vector<int> {1, 2, 3} };
			
			
			cout << "Enter new int value of S<int> ";
			read_val(iv);
			
			cout << "Enter new double value of S<double> ";
			read_val(dv);
			
			cout << "Enter new char value of S<char> ";
			read_val(cv);
			
			cout << "Enter new string value of S<string> ";
			read_val(sv);
			
			cout << "Enter new some int values for S< vector<int> > (format '{val, val, val ...}')\n";
			read_val(viv);
			
			cout << "\n"
				 << "S<int>\t\t"	<< iv.get() << '\n'
				 << "S<double>\t"	<< dv.get() << '\n'
				 << "S<char>\t\t"	<< cv.get() << '\n'
				 << "S<string>\t"	<< sv.get() << '\n'
				 << "S< vector<int> >\t" << viv.get() << "\n\n";
			
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