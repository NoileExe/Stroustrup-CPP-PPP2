
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template <typename T>
ostream& print_array(ostream& os, T* a, int cn)
{
	if (a) {
		for (int i=0; i < cn; ++i) {
			os << "Type: " << typeid(&a[i]).name() << '\t' << &a[i] << '\t' << a[i];
			if (i < cn-1)		os << ",\n";
			else				os << "\n\n";
		}
	}
	
	return os;
}


char* strdupl (const char* s) {
	int size {0};
	for (int i = 0;   s[i] != 0;   ++i)		++size;
	
	char* str = new char[size+1]; //для нуля-терминатора которым заканчивается любая си-строка
	for (int i = 0;   i < size+1;   ++i)		str[i] = s[i];
	
	return str;
}


int main()
{
	while (true) {
		try
		{
			char cstr[] = "Hello, World! XYZ";	//Строка Си-типа
			cout << cstr << '\n';
			
			char* cp {strdupl(cstr)}; //чтобы была возможность удалить
			string str = cp;
			cout << str << '\n';
			
			print_array(cout, cstr, str.size());
			print_array(cout, str.c_str(), str.size());
			print_array(cout, cp, str.size());
			
			delete[] cp;
			
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