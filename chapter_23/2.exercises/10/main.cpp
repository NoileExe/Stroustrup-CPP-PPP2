


#include "SchoolTable.h"	//Содержит <string>, <iostream>, <fstream>, <sstream>, <regex>, <iomanip>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			string file_name {"table.txt"};
			Table one_school {file_name};
			
			int total_boys {0};
			int total_girls {0};
			for(auto& cl : one_school) {
				cout << cl << endl;
				total_boys+=cl.boys;
				total_girls+=cl.girls;
			}
			
			Class school_summ {-1, "Alle klasser", total_boys, total_girls};
			cout << school_summ << "\n\n\n";
			
			cin.putback('\n');
			keep_window_open();
			
			cout << one_school << "\n\n\n";
			
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