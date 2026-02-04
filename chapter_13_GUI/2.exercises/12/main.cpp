

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
			
			Simple_window win(tl, 500, 500, "Глава 13. Упражнение №12");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 13. Упражнение №12
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			Circle c{cntr, 200};
			c.set_color(Color::black);
			c.set_style( Line_style(Line_style::solid, 2) );
			
			win.attach( c );
			
			
			for (int angle = 90; angle >= -270; angle -= 10)
			{
				string astr = (angle >= 0) ?  to_string(angle) : to_string(360+angle);
				win.set_label("Closed_polyline стрелка с наклоном " + astr + " градусов.   Нажмите NEXT");
				
				Mark m {point_on_circle(c, angle), '+'};
				m.set_color(Color::yellow);
				
				//Circle m {point_on_circle(c, angle), 3};
				//m.set_color(Color::yellow);
				//m.set_fill_color(Color::yellow);
				
				win.attach( m );
				win.wait_for_button();
				win.detach( m );
			}
			
			
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