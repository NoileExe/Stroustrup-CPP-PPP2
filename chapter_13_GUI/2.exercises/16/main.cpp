

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void set_regpoly_bg(Simple_window& win, int r)
{
	Vector_ref<Regular_polygon> rps;
	
	Regular_polygon rp {Point{0,0}, r, 6};
	
	int x_step {rp.center().x + 2*rp.radius() + rp.side_ln()};
	int y_step {rp.in_radius()};
	
	for (int row = 0;   row*y_step <= win.y_max()+y_step;   ++row)
		for (int x = 0;   x <= win.x_max()+x_step/2;   x += x_step)
			if ( row%2>0  &&  x==0 )
				x = rps[rps.size()-1].radius() + rps[rps.size()-1].side_ln()/2 - x_step;
				
			else {
				rps.push_back(new Regular_polygon {Point{x, row*y_step}, r, 6});
				rps[rps.size()-1].set_color( Color(Color::black, Color::visible) );
				rps[rps.size()-1].set_style( Line_style(Line_style::solid, 2) );
				rps[rps.size()-1].set_fill_color(Color::yellow);
				win.attach( rps[rps.size()-1] );
			}
	
	win.wait_for_button();
	
	for (int i = 0; i < rps.size(); ++i)
		win.detach( rps[i] );
}


int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(500, 500)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 500, 500, "Глава 13. Упражнение №16");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 13. Упражнение №16
			
			int r = 20;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			set_regpoly_bg(win, r);
			
			r = 30;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = 40;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = 50;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = 60;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = 70;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = 80;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = 90;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = 100;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = 150;
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			r = win.y_max();
			win.set_label("Радиус шестиугольника: " + to_string(r));
			win.resize(win.x_max(), win.y_max());
			set_regpoly_bg(win, r);
			
			
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