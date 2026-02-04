

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(500, 500)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 500, 500, "Глава 14. Упражнение №4");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 14. Упражнение №4
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Immobile_Circle ic {cntr, 150};
			ic.set_color(Color::black);
			ic.set_fill_color(Color::magenta);
			
			win.attach(ic);
			win.wait_for_button();
			
			ic.move(-50, 0);
			
			
			win.set_label("Нажмите кнопку NEXT для завершения программы");
			win.wait_for_button();
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

//------------------------------------------------------------------------------