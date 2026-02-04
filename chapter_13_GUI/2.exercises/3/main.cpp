

#define _USE_MATH_DEFINES


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
			
			Simple_window win(tl, 600, 600, "Глава 13. Упражнение №3");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 13. Упражнение №3
			
			/*Circle c{Point{win.x_max()/2, win.y_max()/2}, 150};
			win.attach( c );*/
			
			for (int angle = 0; angle <= 360; angle += 10) {
				win.set_label("Closed_polyline стрелка с наклоном " + to_string(angle) + " градусов.   Нажмите кнопку NEXT для поворота");
				
				Point p1{win.x_max()/2, win.y_max()/2};
				
				int r = 150; //радиус окружности  aka  длина линии
				int x = round( double(p1.x) + r * cos(angle*M_PI/180.0) ); //точка на окружности (угол обязательно в радианах)
				int y = round( double(p1.y) - r * sin(angle*M_PI/180.0) );
				
				Point p2{x, y};			// разные направления стрелки
				
				Arrow arrow {p1, p2};
				
				arrow.set_color(Color::red);
				arrow.set_style( Line_style(Line_style::solid, 1) );
				arrow.set_fill_color(Color::dark_red); //так же изменит цвет линии
				
				win.attach( arrow );
				win.wait_for_button();
				
				//arrow.move(100,100);
				//win.wait_for_button();
				
				win.detach( arrow );
			}
			
			
			//------------------------------------------------------------------------------
			
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