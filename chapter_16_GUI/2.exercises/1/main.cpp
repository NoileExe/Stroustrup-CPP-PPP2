

#include <yes_or_no.h>
#include "My_window.h"

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
			
			My_window win {Point{100,100}, xmax, ymax,   "Глава 16. Упражнение №1"};
			// верхний левый угол окна по координатам [100;100]
			// размер окна 600*600
			// заголовок окна: Глава 16. Упражнение №1
			
			win.wait_for_button();
			
			Circle c1 {Point{300,300}, 150};
			win.attach(c1);
			win.wait_for_button();
			
			c1.move(100, 0);
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