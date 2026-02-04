



//Включает yes_or_no.h (<string>, <iostream>), <vector>, <algorithm>, <random>
#include "bs_test.h"
#include <fstream>		// для файлового потока ввода-вывода


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			do {
				
				clear_screen();
				
				cout << "\n\nEnter the name of the input file: ";
				string file_name {""};
				getline(cin,file_name);
				
				ifstream ifs {file_name};	//Открываем файловый поток ввода
				if(!ifs)		error("unable to open file '" + file_name + "'");
				ifs.exceptions(ifs.exceptions() | ios_base::badbit);
				
				int error_count = test_all<string>(ifs, true);
				cout << "\n\nNum of errors (random num of elements with count 0-9): " << error_count
					 << "\n\n----------------------------------------------------------------------\n\n";
				ifs.close();
				
				press_Enter_key();
				
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