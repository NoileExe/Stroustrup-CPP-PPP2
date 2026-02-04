

#include "swap_columns.h"					//Включает <iomanip>, <random> и <yes_or_no.h>, который влючает <string>, <iostream> и устанавливает using namespace std


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			do {
				swap_random_matrix(3,4);		//3 строкии, 4 столбца
				cout << "\n--------------------------------------------------------------------------";
				//cin.putback('\n');
			} while( Y_or_N("Repeat?") );
			
			
			cin.putback('\n');
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