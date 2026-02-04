
//Достаточно 8 символов для переполнения памяти? 9 символ отличается от введёного

#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template <typename T> unsigned int pointer2int (T* a) {
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
			int var1{0};
			int var2{0};
			cout << "\n\nvar1: " << &var1 << "\tvar2: " << &var2 << '\n';
			
			if ( pointer2int(&var2) - pointer2int(&var1) > 0 )
				cout << "Stack grows up\n\n";
			else
				cout << "Stack grows down\n\n";
			
			
			int* addr1 = new int;
			int* addr2 = new int;
			cout << "\n\naddr1: " << addr1 << "\taddr2: " << addr2 << '\n';
			
			if ( pointer2int(addr2) - pointer2int(addr1) > 0)
				cout << "Heap (dynamic mem) grows up\n\n";
			else
				cout << "Heap (dynamic mem) grows down\n\n";
			
			delete addr1;
			delete addr2;
			
			keep_window_open("~~");
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