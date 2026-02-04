

#include "My_window.h"
#include <yes_or_no.h>

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
			
			Point tl {win_centering(xmax, ymax)};
			
			Function_window win {tl, xmax, ymax,   "Глава 16. Упражнение №10"};
			// окно ровно посередине окна
			// размер окна 600*600
			// заголовок окна: Глава 16. Упражнение №10
			
			win.wait_for_button();
			win.set_label("Нажмите кнопку QUIT для завершения программы");
			return gui_main();		//Без данной строки после последнего нажатия кнопки Next программа закрывается
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