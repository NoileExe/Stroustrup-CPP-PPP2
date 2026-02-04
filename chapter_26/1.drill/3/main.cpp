



//Включает yes_or_no.h (<string>, <iostream>), <fstream>, <vector>, <algorithm>, <random>
#include "bs_test.h"


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			do {
				
				clear_screen();
				
				string test_a {"test_a.txt"};
				string test_b {"test_b.txt"};
				string test_c {"test_c.txt"};
				
				ofstream ofs(test_a.c_str());
				if(!ofs)		error("unable to open output file '" + test_a + "'");
				
				make_test(ofs, "1.1", 10000, 1, 15);		// Большая последовательность
				//make_test(ofs, "1.2", 10000000, 1, 15);		// Очень большая последовательность - долгое построение и поиск
				//make_test(ofs, "1.3", 1000000000, 1, 15);	// Очень большая последовательность - Error ( main() ): bad allocation
				ofs.close();
				
				
				ofs.open(test_b.c_str(), std::ofstream::out);	// Открыть для вывода, ' | std::ofstream::app' - добавлять в конец файла (без перезаписи)
				if(!ofs)		error("unable to open output file '" + test_b + "'");
				for(int i = 1; i <= 10; ++i)
					make_test(ofs, "2." + to_string(i), randint(10000), 1, 15);		// Случайное кол-во элементов от 0 до 10000
				ofs.close();
				
				
				ofs.open(test_c.c_str(), std::ofstream::out);	// Открыть для вывода, перезапись существующего
				if(!ofs)		error("unable to open output file '" + test_c + "'");
				for(int i = 0; i < 10; ++i)
					make_test(ofs, "3." + to_string(i), i, 0, 9);	// Случайные значения элементов в количестве по возрастающей от 0 до 9
				ofs.close();
				
				//----------------------------------------------------------------------
				
				ifstream ifs {test_a};					//Открываем файловый поток ввода
				if(!ifs)		error("unable to open input file '" + test_a + "'");
				ifs.exceptions(ifs.exceptions() | ios_base::badbit);
				
				int error_count {0};
				error_count = test_all<int>(ifs);
				cout << "\n\nNum of errors (very big vectors): " << error_count
					 << "\n\n----------------------------------------------------------------------\n\n";
				ifs.close();
				
				
				ifs.open(test_b, std::ifstream::in);	//Открываем файловый поток ввода
				if(!ifs)		error("unable to open input file '" + test_b + "'");
				error_count = test_all<int>(ifs, false);
				cout << "\n\nNum of errors (random num of elements): " << error_count
					 << "\n\n----------------------------------------------------------------------\n\n";
				ifs.close();
				
				
				ifs.open(test_c, std::ifstream::in);	//Открываем файловый поток ввода
				if(!ifs)		error("unable to open input file '" + test_c + "'");
				error_count = test_all<int>(ifs, true);
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