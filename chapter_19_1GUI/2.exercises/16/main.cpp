

#include <stddef.h>
#include <yes_or_no.h>
#include "vctr.h"



#define vector vctr



const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T> ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	for(int i = 0; i < vt.size(); ++i)
		if(i != vt.size()-1)	ost << vt.at(i) << ", ";
		else					ost << vt.at(i);
	
	ost << " }";
	
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

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			string str { (sizeof(vector<int>) == sizeof(int*)) ? "EQU" : "NOT EQU" };
			
			cout << "sizeof(vector<int>) " << sizeof(vector<int>) << "\t\t" << "sizeof(int*) " << sizeof(int*) << "\t\t" << str << "\n\n";
			
			cout << "\n\n";
			
			vector<int> vi {1,2,7,8};
			
			cout << "\n" << "vector<int>\t" << vi << "\n\n";
			
			str = (sizeof(vi) == sizeof(int*)) ? "EQU" : "NOT EQU";
			cout << "sizeof(vi) " << sizeof(vi) << "\t\t\t" << "sizeof(int*) " << sizeof(int*) << "\t\t" << str << "\n\n";
			
			
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