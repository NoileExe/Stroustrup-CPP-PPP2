

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void set_triangles_bg(Simple_window& win, int l1, int l2)
{
	Vector_ref<Right_triangle> rts;
	
	for (int y = 0; y <= win.y_max(); y += l2)
		for (int x = 0; x <= win.x_max(); x += l1)
		{
			if ( y>0  &&  x != win.x_max() ) {
				rts.push_back(new Right_triangle {Point{x, y}, l1, l2});
				
				rts[rts.size()-1].set_color( Color(Color::black, Color::visible) );
				rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
				rts[rts.size()-1].set_fill_color(Color::green);
				win.attach( rts[rts.size()-1] );
			}
			
			if ( x>0  &&  y != win.y_max() ) {
				rts.push_back(new Right_triangle {Point{x, y}, l1, l2, 180});
				
				rts[rts.size()-1].set_color( Color(Color::black, Color::visible) );
				rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
				rts[rts.size()-1].set_fill_color(Color::yellow);
				win.attach( rts[rts.size()-1] );
			}
			
			
			//При некратных длинах сторон относительно размеров окна
			if ( y+l2 > win.y_max()  &&  win.y_max()%l2 != 0 ) {
				rts.push_back(new Right_triangle {Point{x, y+l2}, l1, l2});
				
				rts[rts.size()-1].set_color( Color(Color::black, Color::visible) );
				rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
				rts[rts.size()-1].set_fill_color(Color::green);
				win.attach( rts[rts.size()-1] );
			}
			
			if ( x+l1 > win.x_max()  &&  win.x_max()%l1 != 0 ) {
				rts.push_back(new Right_triangle {Point{x+l1, y}, l1, l2, 180});
				
				rts[rts.size()-1].set_color( Color(Color::black, Color::visible) );
				rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
				rts[rts.size()-1].set_fill_color(Color::yellow);
				win.attach( rts[rts.size()-1] );
			}
		}
	
	win.wait_for_button();
	
	for (int i = 0; i < rts.size(); ++i)
		win.detach( rts[i] );
}


int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(500, 500)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 500, 500, "Глава 13. Упражнение №15");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 13. Упражнение №15
			
			int l1 = 50;
			int l2 = 50;
			set_triangles_bg(win,l1,l2);
			
			l1 = 70;
			l2 = 70;
			set_triangles_bg(win,l1,l2);
			
			l1 = 70;
			l2 = 150;
			set_triangles_bg(win,l1,l2);
			
			l1 = 150;
			l2 = 70;
			set_triangles_bg(win,l1,l2);
			
			l1 = win.x_max();
			l2 = win.y_max();
			set_triangles_bg(win,l1,l2);
			
			
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