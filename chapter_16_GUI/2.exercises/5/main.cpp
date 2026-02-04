

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
			constexpr int r = 100;
			
			Point tl {win_centering(xmax, ymax)};
			
			
			//Открываем файлы для чтения данных
			ifstream ifs { "5.txt" };
			if (!ifs)		error("the specified file cannot be opened (5.txt)");
			ifs.exceptions(ifs.exceptions() | ios_base::badbit);	// Генерация исключения в случае состояния bad ()
			
			Move_figure_window win {tl, xmax, ymax, r,   "Глава 16. Упражнение №5", ifs};
			
			
			//Move_figure_window win {tl, xmax, ymax, r,   "Глава 16. Упражнение №5"};	//Поток ввода по умолчанию cin
			// окно ровно посередине окна
			// размер окна 600*600
			// заголовок окна: Глава 16. Упражнение №5
			
			win.wait_for_button();
			
			win.fig().set_color(Color::dark_magenta);
			win.fig().set_fill_color(Color::magenta);
			win.fig().set_style( Line_style(Line_style::solid, 2) );
			win.fig().set_fill_orient( lorient::horisontal );
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