


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T, typename U>
class Pair {
	T t;
	U u;
	
public:
	Pair() : t{T()}, u{U()}		{}
	Pair(const T f = T(), const U s = U()) : t{f}, u{s}		{}
	
	T& first() { return t; }
	const T& first() const { return t; }
	
	U& second() { return u; }
	const U& second() const { return u; }
};


template<typename T, typename U>
ostream& operator<<(ostream &ost, const Pair<T,U>& p)
{
	ost << '[' << p.first() << "   " << p.second() << ']';
	return ost;
}


int main()
{
	while (true) {
		try
		{
			Pair<string, string> a {"abc", "123"};
			Pair<string, int> b {"onetwothree", 123};
			Pair<double, int> c {1.3, 777};
			
			cout << a << '\n';
			cout << b << '\n';
			cout << c << '\n';
			
			cout << "\n\n";
			
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