

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
			const string img {"papper_plane.jpg"};
			
			Point tl {win_centering(xmax, ymax)};
			
			
			Fly_img_window win {  tl, xmax, ymax,   "Глава 16. Упражнение №7",   img, [](double x){ return pow(sin(x), 2) * pow(cos(x), 2); }  };
			// окно ровно посередине окна
			// размер окна 600*600
			// заголовок окна: Глава 16. Упражнение №7
			
			win.set_bg_color(Color::black);
			win.wait_for_button();	//Сразу запускает анимацию
			
			
			/*clock_t start = clock();
			clock_t  stop = clock();
			while (stop-start < 1000)		stop = clock();*/
			
			win.set_bg_color(Color::white);
			win.set_function( [](double x){ return sin(x)+2; } );
			win.wait_for_button();	//Сразу запускает анимацию
			
			/*start = clock();
			stop  = clock();
			while (stop-start < 1000)		stop = clock();*/
			
			win.set_points_count(200);
			win.wait_for_button();	//Сразу запускает анимацию
			
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