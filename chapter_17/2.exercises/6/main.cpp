
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

const int n = 1000;
double cnt {0};


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
			while(true) {
				double* d = new double[n];
				cnt += n;
			}
			
			keep_window_open();
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			cout << "Successfully created by the new operator " << cnt/n << " arrays of double type with " << n << " elements each before overflowing\n";
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}