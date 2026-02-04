

#include <yes_or_no.h>
#include "Lines_window.h"

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			constexpr int xmax = 600;	//Размер окна
			constexpr int ymax = 600;
			
			Lines_window win {Point{100,100}, xmax, ymax,   "Глава 16. Задания"};
			// верхний левый угол окна по координатам [100;100]
			// размер окна 600*600
			// заголовок окна: Глава 16. Задания
			
			return gui_main();
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