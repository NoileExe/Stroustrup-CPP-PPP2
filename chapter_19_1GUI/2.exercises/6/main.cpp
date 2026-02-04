


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
class Number {
	T i;
	
public:
	Number<T> (T n = T()) : i{n}		{}
	
	T& num() { return i; }
	const T& num() const { return i; }
};

template<typename T>
Number<T> operator+(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.num() + n2.num()};
}

template<typename T>
Number<T> operator-(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.num() - n2.num()};
}

template<typename T>
Number<T> operator*(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.num() * n2.num()};
}

template<typename T>
Number<T> operator/(const Number<T>& n1, const Number<T>& n2)
{
	if(n2.num() == 0)		error("division by zero");
	return Number<T>{n1.num() / n2.num()};
}

template<typename T>
Number<T> operator%(const Number<T>& n1, const Number<T>& n2)
{
	if(n2.num() == 0)		error("division by zero");
	return Number<T>{n1.num() % n2.num()};
}


template<typename T>
ostream& operator<<(ostream &ost, const Number<T>& n)
{
	ost << n.num();
	return ost;
}

template<typename T>
istream& operator>>(istream &ist, Number<T>& n)
{
	ist >> n.num();
	return ist;
}


int main()
{
	while (true) {
		try
		{
			{
				Number<int> a {23};
				Number<double> b = 3.3;
				Number<double> c = b;
				Number<double> d {c-b};
				const Number<double> cnst {};
				
				cout << "Number c{b}   " << c << '\n';
				cout << "Number d {c-b}   " << d << '\n';
				cout << "const Number cnst {}   " << cnst << '\n';
				
				c=d;
				cout << "c = d   " << c << '\n';
				
				cout << "enter double: ";
				cin >> c;
				cout << "cin >> c   " << c << '\n';
			}
			
			cout << "\n\n";
			
			{
				Number<int> a {23};
				Number<int> b = 3;
				
				cout << a << " + " << b << " = " << a+b << '\n';
				cout << a << " - " << b << " = " << a-b << '\n';
				cout << a << " * " << b << " = " << a*b << '\n';
				cout << a << " / " << b << " = " << a/b << '\n';
				cout << a << " % " << b << " = " << a%b << '\n';
			}
			
			cout << "\n\n";
			
			{
				Number<double> a {23};
				Number<double> b = 3.3;
				
				cout << a << " + " << b << " = " << a+b << '\n';
				cout << a << " - " << b << " = " << a-b << '\n';
				cout << a << " * " << b << " = " << a*b << '\n';
				cout << a << " / " << b << " = " << a/b << '\n';
				//cout << a << " % " << b << " = " << a%b << '\n';
			}
			
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