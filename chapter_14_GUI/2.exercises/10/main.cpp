

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
			
			Simple_window win(tl, 600, 600, "Глава 14. Упражнение №10");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 14. Упражнение №10
			
			Pseudo_window pw {Point{25, 50}, 550, 500, "Глава 14. Упражнение №10"};
			win.attach(pw);
			win.wait_for_button();
			
			Point cntr{pw.x_max()/2, pw.y_max()/2}; //Центральная точка окна
			Circle c1 {cntr, 100};
			pw.attach( c1 );
			win.wait_for_button();
			
			pw.detach( c1 );
			win.wait_for_button();
			
			Point cntr1{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			Circle c2 {cntr1, 100};
			c2.set_color(Color::yellow);
			c2.set_fill_color(Color::dark_red);
			pw.attach( c2 );
			win.wait_for_button();
			
			pw.detach( c2 );
			win.wait_for_button();
			
			pw.set_label("Изображение обрезается по размеру окна");
			Image my_img {Point{0, 0}, "my_img.jpg"};
			pw.attach( my_img );
			
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