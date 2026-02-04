

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
			
			Point tl {win_centering(xmax, ymax)};
			
			
			My_window win {tl, xmax, ymax,   "Глава 16. Упражнение №6"};
			// окно ровно посередине окна
			// размер окна 600*600
			// заголовок окна: Глава 16. Упражнение №6
			win.wait_for_button();
			
			Point cntr {xmax/2, ymax/2};
			Clock cl {cntr, (xmax-100)/2};
			win.attach(cl);
			win.wait_for_button();
			
			for (int i=0; i<120; ++i) {
				time_t seconds = time(NULL);
				struct tm* timeinfo = localtime(&seconds);
				tm ti = *timeinfo;
				
				cl.set_time(ti);
				
				Fl::wait();
				win.redraw();
				
				clock_t start = clock();
				clock_t  stop = clock();
				while (stop-start < 1000)	stop = clock();
			}
			
			
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