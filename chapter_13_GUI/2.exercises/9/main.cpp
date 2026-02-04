

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
			Point tl{win_centering(800, 800)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 800, 800, "Глава 13. Упражнение №9");
			// окно посередине экрана
			// размер окна (800*800)
			// заголовок окна: Глава 13. Упражнение №9
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Vector_ref<Regular_hexagon> m;
			
			m.push_back(new Regular_hexagon {Point{100, 70}, 50});
			m[m.size()-1].set_color(Color::black);
			m[m.size()-1].set_style( Line_style(Line_style::solid, 2) );
			m[m.size()-1].set_fill_color(Color::yellow);
			win.attach( m[m.size()-1] );
			
			for (int i = 1; ; ++i) //i < 36 //2 ряда - значение кратно 9
			{
				int x = m[m.size()-1].center().x + 2*m[m.size()-1].radius() + m[m.size()-1].side_ln();
				int y = m[m.size()-1].center().y;
				
				if ( x >= win.x_max()-50 ) {
					x = 100 + m[m.size()-1].radius() + m[m.size()-1].side_ln()/2;
					y += m[m.size()-1].in_radius();
				}
				
				if ( i%9==0  &&  i!=0 ) {
					x = 100;
					y = m[m.size()-1].center().y + m[m.size()-1].in_radius();
				}
				
				if ( y >= win.y_max() - m[m.size()-1].in_radius()-10 )
					break;
				
				m.push_back(new Regular_hexagon {Point{x,y}, 50});
				m[m.size()-1].set_color(Color::black);
				m[m.size()-1].set_style( Line_style(Line_style::solid, 2) );
				m[m.size()-1].set_fill_color(Color::yellow);
				
				win.attach( m[m.size()-1] );
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