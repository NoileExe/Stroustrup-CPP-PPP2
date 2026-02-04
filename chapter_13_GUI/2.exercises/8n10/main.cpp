

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void txt_one_style_bold (Text& t) {
	t.set_color(Color::black);
	t.set_font(Graph_lib::Font::times_bold);
	t.set_font_size(18);
}

int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(600, 600)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 600, 600, "Глава 13. Упражнения №8 и №10");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 13. Упражнения №8 и №10
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Regular_hexagon reghex {cntr, 250};
			reghex.set_color(Color::black);
			reghex.set_style( Line_style(Line_style::solid, 2) );
			reghex.set_fill_color(Color::dark_magenta);
			
			win.attach(reghex);
			win.wait_for_button();
			
			
			win.detach(reghex);
			
			for (int n = 3; n <= 20; ++n) {
				Regular_polygon rp {cntr, 150, n};
				rp.set_color(Color::black);
				rp.set_style( Line_style(Line_style::solid, 2) );
				rp.set_fill_color(Color::dark_green);
				
				win.attach( rp );
				win.wait_for_button();
				win.detach( rp );
			}
			
			Regular_polygon rp {cntr, 150, 360};
			rp.set_color(Color::black);
			rp.set_fill_color(Color::dark_yellow);
			win.attach( rp );
			win.wait_for_button();
			win.detach( rp );
			
			Circle c {cntr, 150};
			c.set_color(Color::black);
			c.set_fill_color(Color::dark_blue);
			win.attach( c );
			win.wait_for_button();
			win.detach( c );
			
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