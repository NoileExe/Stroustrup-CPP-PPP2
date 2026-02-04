


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

class Int {
	int i;
	
public:
	Int(int n = int()) : i{n}		{}
	
	int& num() { return i; }
	const int& num() const { return i; }
};

Int operator+(const Int& n1, const Int& n2)
{
	return Int(n1.num() + n2.num());
}

Int operator-(const Int& n1, const Int& n2)
{
	return Int(n1.num() - n2.num());
}

Int operator*(const Int& n1, const Int& n2)
{
	return Int(n1.num() * n2.num());
}

Int operator/(const Int& n1, const Int& n2)
{
	if(n2.num() == 0)		error("division by zero");
	return Int(n1.num() / n2.num());
}

Int operator%(const Int& n1, const Int& n2)
{
	if(n2.num() == 0)		error("division by zero");
	return Int(n1.num() % n2.num());
}


ostream& operator<<(ostream &ost, const Int& n)
{
	ost << n.num();
	return ost;
}

istream& operator>>(istream &ist, Int& n)
{
	ist >> n.num();
	return ist;
}


int main()
{
	while (true) {
		try
		{
			Int a {23};
			Int b = 3;
			
			//Int c = a;	//Оба варианта рабочие
			Int c {a};
			cout << "Int c{a}   " << c << '\n';
			
			c=b;
			cout << "c = b   " << c << '\n';
			
			//Int d = a-b;
			Int d {a-b};
			cout << "Int d {a-b}   " << d << '\n';
			
			cout << a << " + " << b << " = " << a+b << '\n';
			cout << a << " - " << b << " = " << a-b << '\n';
			cout << a << " * " << b << " = " << a*b << '\n';
			cout << a << " / " << b << " = " << a/b << '\n';
			cout << a << " % " << b << " = " << a%b << '\n';
			
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