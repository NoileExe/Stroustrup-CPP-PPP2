


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------


char* strdupl(const char* s) {
	if (s == 0)		error("empty c-string strdup()");
	
	int sz {0};
	const char* s_iter = s;
	while (*s_iter != 0)
	{
		++sz;
		++s_iter;
	}
	
	char* str = new char[sz + 1];
	for (int i=0; ; ++i) {
		*(str+i) = *(s+i);
		if ( *(s+i) == 0 )		break;
	}
	
	return str;
}


int main()
{
	while (true) {
		try
		{
			char str[] {"Hello, World!"};
			char* p = strdupl(str);
			
			*(str+2) = '@';
			cout << "strdupl: " << p << '\n';
			cout << "*(str+2) = '@': " << str << '\n';
			
			delete[] p;
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