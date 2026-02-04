


#include <yes_or_no.h>
#include "vctr.h"


#define vector vctr


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T> struct S {
	explicit S(T vv = T{}) : val{vv}		{ }
	
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



template<typename T> ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	/*for (int i = 0; i <= vt.size(); ++i)		//Захват лишнего элемента без ошибки
		if(i != vt.size()-1)	ost << vt[i] << ", ";
		else					ost << vt[i] << " }";*/
	
	for(int i = 0; i < vt.size(); ++i)
		if(i != vt.size()-1)	ost << vt.at(i) << ", ";
		else					ost << vt.at(i) << " }";
	
	return ost;
}

template<typename T> istream& operator>>(istream &ist, vector<T>& vt) {
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
	vector<T> buf {};
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
			
			S< vector<int> > viv {};
			
			cout << "Enter new some int values for S< vector<int> > (format '{val, val, val ...}')\n";
			read_val(viv);
			
			cout << "\n" << "S< vector<int> >\t" << viv.get() << "\n\n";
			
			//S< vector<int> > vivv{ viv };
			//S< vector<int> > vivv{ viv.get() };
			S< vector<int> > vivv{ vector<int> {1,2,8,9} };
			//S< vector<int> > vivv{ };
			//vivv = viv;
			cout << "\n" << "S< vector<int> >\t" << vivv.get() << "\n\n";
			
			/*vector<int> v {1,2,8,9};
			cout << "\n" << "< vector<int> > {init_list}\t" << v << "\n\n";*/
			
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