

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
			
			Simple_window win(tl, 500, 500, "Глава 14. Упражнение №1");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 14. Упражнение №1
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Frowny f1 {cntr, 100};
			f1.set_color(Color::black);
			f1.set_fill_color(Color::yellow);
			
			win.attach(f1);
			win.wait_for_button();
			win.detach(f1);
			
			
			Smiley s1 {cntr, 100};
			s1.set_color(Color::black);
			s1.set_fill_color(Color::yellow);
			
			win.attach(s1);
			win.wait_for_button();
			win.detach(s1);
			
			//------------------------------------------------------------------------------
			
			Frowny_chinese fchinese {cntr, 100};
			fchinese.set_color(Color::black);
			fchinese.set_fill_color(Color::yellow);
			
			win.attach(fchinese);
			win.wait_for_button();
			win.detach(fchinese);
			
			
			Frowny_bowler fbowler {cntr, 100};
			fbowler.set_color(Color::black);
			fbowler.set_fill_color(Color::yellow);
			
			win.attach(fbowler);
			win.wait_for_button();
			win.detach(fbowler);
			
			
			for (int r = 100;  r>=10;  r-=10) {
				Smiley_chinese schinese {cntr, r};
				schinese.set_color(Color::black);
				schinese.set_fill_color(Color::yellow);
				
				win.attach(schinese);
				win.wait_for_button();
				win.detach(schinese);
			}
			
			for (int r = 100;  r>=10;  r-=10) {
				Smiley_bowler sbowler {cntr, r};
				sbowler.set_color(Color::black);
				sbowler.set_fill_color(Color::yellow);
				
				win.attach(sbowler);
				win.wait_for_button();
				win.detach(sbowler);
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