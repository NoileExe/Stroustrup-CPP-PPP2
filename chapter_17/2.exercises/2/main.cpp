
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template <typename T>
unsigned int pointer2int (T* a)
{
	unsigned int d {0}; //т.к. его верхнее значение равно 4 294 967 295 (максимальный адрес FFFF FFFF)
	
	if (a) {
		ostringstream oss;
		oss << a;
		
		istringstream iss { oss.str() };
		iss >> hex >> d;
		if (!iss)		error("problem reading address");
	}
	
	else		error("nullptr ( pointer2int() )");
	
	return d;
}


int main()
{
	while (true) {
		try
		{
			int* pint = new int[] {1, 2};
			cout << "Size of int (pointer2int): " << pointer2int(&pint[1]) - pointer2int(&pint[0]) << '\n';
			cout << "Size of int (sizeof): " << sizeof(int) << "\n\n";
			
			double* pdbl = new double[] {1, 2};
			cout << "Size of double (pointer2int): " << pointer2int(&pdbl[1]) - pointer2int(&pdbl[0]) << '\n';
			cout << "Size of double (sizeof): " << sizeof(double) << "\n\n";
			
			bool* pbool = new bool[] {true, true};
			cout << "Size of bool (pointer2int): " << pointer2int(&pbool[1]) - pointer2int(&pbool[0]) << '\n';
			cout << "Size of bool (sizeof): " << sizeof(bool) << "\n\n";
			
			delete[] pint;
			delete[] pdbl;
			delete[] pbool;
			
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