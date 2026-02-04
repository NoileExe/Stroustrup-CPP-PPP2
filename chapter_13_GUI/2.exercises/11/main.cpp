

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
			
			Simple_window win(tl, 500, 500, "Глава 13. Упражнение №11");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 13. Упражнение №11
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Graph_lib::Ellipse ell {cntr, 150, 100};
			ell.set_color(Color::black);
			ell.set_style( Line_style(Line_style::solid, 2) );
			
			
			Axis vert {Axis::y, Point{cntr.x, s(ell).y+50}, 300, 20, "Ось y"};
			vert.set_color(Color::black);			// выбор цвета линии
			vert.label.set_color(Color::black);		// выбор цвета текста
			
			Axis hori {Axis::x, Point{w(ell).x-50, cntr.y}, 400, 20, "Ось x"};
			hori.set_color(Color::black);			// выбор цвета линии
			hori.label.set_color(Color::black);		// выбор цвета текста
			
			
			Mark f1 {ell.focus1(),'+'};
			f1.set_color(Color::yellow);
			
			Mark f2 {ell.focus2(),'+'};
			f2.set_color(Color::yellow);
			
			Mark ep {point_on_ellipse(ell, 70), '+'};
			ep.set_color(Color::yellow);
			
			
			Graph_lib::Line l1 {f1.point(0), ep.point(0)};
			l1.set_color(Color::magenta);
			l1.set_style( Line_style(Line_style::solid, 2) );
			
			Graph_lib::Line l2 {f2.point(0), ep.point(0)};
			l2.set_color(Color::magenta);
			l2.set_style( Line_style(Line_style::solid, 2) );
			
			
			win.attach( hori );
			win.attach( vert );
			win.attach( ell );
			
			win.attach( l1 );
			win.attach( l2 );
			
			win.attach( f1 );
			win.attach( f2 );
			win.attach( ep );
			
			
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