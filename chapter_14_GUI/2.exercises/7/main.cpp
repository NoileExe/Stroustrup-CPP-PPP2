

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
			
			Simple_window win(tl, 600, 600, "Глава 14. Упражнение №7");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 14. Упражнение №7
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Striped_closed_polyline scp;
			scp.set_color(Color::black);
			scp.set_fill_color(Color::yellow);
			scp.add(Point {130, 280});
			scp.add(Point {70, 140});
			scp.add(Point {150, 200});
			scp.add(Point {260, 100});
			scp.add(Point {320, 190});
			scp.add(Point {270, 290});
			
			win.attach(scp);
			win.wait_for_button();
			
			scp.set_fill_orient(lorient::horisontal);
			win.wait_for_button();
			win.detach(scp);
			
			
			
			/*Striped_closed_polyline scp1;
			scp1.set_color(Color::black);
			scp1.set_fill_color(Color::red);
			scp1.add(Point {30, 230});
			scp1.add(Point {90, 210});
			scp1.add(Point {150, 190});
			scp1.add(Point {170, 220});
			scp1.add(Point {240, 220});
			scp1.add(Point {275, 190});
			scp1.add(Point {345, 190});
			scp1.add(Point {380, 220});
			scp1.add(Point {450, 220});
			scp1.add(Point {480, 195});
			scp1.add(Point {460, 250});
			scp1.add(Point {470, 280});
			scp1.add(Point {470, 350});
			scp1.add(Point {455, 300});
			scp1.add(Point {455, 270});
			scp1.add(Point {300, 280});
			scp1.add(Point {30, 280});
			
			win.attach(scp1);
			win.wait_for_button();
			
			scp1.set_fill_orient(lorient::horisontal);*/
			
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