

#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int recursive_factorial (int n) { return n>1  ?  n*recursive_factorial(n-1) : 1; }

int iteraive_factorial (int n) { 
	int r {1};
	for ( ; n>1; --n)
		r*=n;
	
	/*while (n>1) {
		r*=n;
		--n;
	}*/
	
	return r;
}


int main()
{
	while (true) {
		try
		{
			constexpr int min_i = 0;
			constexpr int max_i = 20;
			cout << "\n\nNext, this programm  will be calculated the factorial for integer values from "
				 << min_i << " to " << max_i << "\n\n";
			
			for (int i=min_i; i<=max_i; ++i)
				cout << "\nfactorial(" << i << "):\n"
						"iteraive method: "  << iteraive_factorial(i)  << "\n"
						"recursive method: " << recursive_factorial(i) << "\n";
			
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

//------------------------------------------------------------------------------