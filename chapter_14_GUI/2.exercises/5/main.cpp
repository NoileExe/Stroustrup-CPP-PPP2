

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
			Point tl{win_centering(600, 600)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 600, 600, "Глава 14. Упражнение №5");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 14. Упражнение №5
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Striped_rectangle sr {Point{cntr.x - 400/2, cntr.y - 250/2}, 400, 250};
			sr.set_color(Color::black);
			sr.set_fill_color(Color::red);
			
			win.attach(sr);
			win.wait_for_button();
			
			sr.set_fill_orient(lorient::horisontal);
			win.wait_for_button();
			
			sr.set_fill_orient(lorient::right_diagonal);
			win.wait_for_button();
			
			sr.set_fill_orient(lorient::left_diagonal);
			
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