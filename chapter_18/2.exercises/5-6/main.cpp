


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

string cat_dot (const string&s1, const string&s2, const string& pnct = ".") {
	return  s1 + pnct + s2;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			string s1 {"Michaele"};
			string s2 {"Jackson"};
			string pnct {"\t\t"};
			
			cout << cat_dot(s1, s2) << '\n';
			cout << cat_dot(s1, s2, pnct) << '\n';
			
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