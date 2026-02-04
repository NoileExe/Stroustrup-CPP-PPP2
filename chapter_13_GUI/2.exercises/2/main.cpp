

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
			
			Simple_window win(tl, 600, 600, "Глава 13. Упражнение №2");
			// размер окна (600*600)
			// заголовок окна: Глава 13. Упражнение №2
			
			win.set_label("Инициализация сторонами и изменение цвета.   Нажмите кнопку NEXT");
			
			{
				Point center{win.x_max()/2, win.y_max()/2};
				Graph_lib::Box test_box( Point{center.x-125, center.y-125}, 250, 250 );
				test_box.set_color(Color::dark_magenta);
				win.attach( test_box );
				
				win.wait_for_button();
				
				
				test_box.set_style( Line_style(Line_style::dash, 3) );
				test_box.set_fill_color(Color::magenta);
				
				win.wait_for_button();
			}
			
			//------------------------------------------------------------------------------
			
			win.set_label("Инициализация сторонами и радиусом и перемещение.   Нажмите кнопку NEXT");
			
			{
				Point center{win.x_max()/2, win.y_max()/2};
				Graph_lib::Box test_box( Point{10, 10}, 100, 150, 50);
				
				test_box.set_color(Color::dark_green);
				test_box.set_style( Line_style(Line_style::solid, 1) );
				test_box.set_fill_color(Color::green);
				win.attach( test_box );
				
				win.wait_for_button();
				
				
				test_box.move(center.x-50-10, center.y-75-10);
				
				win.wait_for_button();
			}
			
			//------------------------------------------------------------------------------
			
			win.set_label("Инициализация двумя точками.   Нажмите кнопку NEXT");
			
			{
				Point center{win.x_max()/2, win.y_max()/2};
				Graph_lib::Box test_box( Point{center.x-125, center.y-125}, Point{center.x-25, center.y+25} );
				
				test_box.set_color(Color::dark_yellow);
				test_box.set_style( Line_style(Line_style::solid, 2) );
				test_box.set_fill_color(Color::yellow);
				win.attach( test_box );
				
				win.wait_for_button();
			}
			
			//------------------------------------------------------------------------------
			
			win.set_label("Инициализация двумя точками и радиусом.   Нажмите кнопку NEXT");
			
			{
				Graph_lib::Box test_box( Point{50, win.y_max()-200}, Point{450, win.y_max()-50}, 30 );
				
				test_box.set_color(Color::dark_cyan);
				test_box.set_style( Line_style(Line_style::solid, 5) );
				test_box.set_fill_color(Color::cyan);
				win.attach( test_box );
				
				win.wait_for_button();
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