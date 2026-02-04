
//#include <typeinfo>
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template <typename T>
ostream& print_array(ostream& os, T* a, int cn)
{
	if (a) {
		for (int i=0; i < cn; ++i) {
			os << "Type: " << typeid(&a[i]).name() << '\t' << showbase << hex << &a[i] << dec << '\t' << a[i];
			if (i < cn-1)		os << ",\n";
			else				os << "\n\n";
		}
	}
	
	os << noshowbase << dec; //на случай возникновения ошибки
	return os;
}


int main()
{
	while (true) {
		try
		{
			int* p1 = new int[] {7, 8};
			print_array(cout, p1, 2);
			press_Enter_key(true);
			
			delete[] p1;
			
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