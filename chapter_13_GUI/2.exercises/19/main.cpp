

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
			
			Simple_window win(tl, 500, 500, "Глава 13. Упражнение №19");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 13. Упражнение №19
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Star s1 {cntr, 5, 150};
			s1.set_color(Color::black);
			s1.set_fill_color(Color::dark_green);
			
			win.attach(s1);
			win.wait_for_button();
			win.detach(s1);
			
			
			Star s2 {cntr, s1.legs_count(), s1.out_radius(), 80};
			s2.set_color(Color::black);
			s2.set_fill_color(Color::dark_yellow);
			
			win.attach(s2);
			win.wait_for_button();
			win.detach(s2);
			
			
			for (int n = 3; n < 40; ++n)
			{
				cout << n << '\n';
				
				Star s {cntr, n, 100};
				s.set_color(Color::black);
				s.set_fill_color(n%255);
				
				win.attach(s);
				win.wait_for_button();
				win.detach(s);
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