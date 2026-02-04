

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
			
			Simple_window win(tl, 600, 600, "Глава 14. Упражнение №9");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 14. Упражнение №9
			
			win.set_label("класс chess_board");
			
			chess_board cb {Point{0,0}, win.x_max()};
			win.attach( cb );
			
			win.wait_for_button();
			win.detach( cb );
			
			//------------------------------------------------------------------------------
			
			win.set_label("класс checkers_canva");
			
			checkers_canva ch {Point{21,21}, win.x_max()-40};
			win.attach( ch );
			win.wait_for_button();
			
			ch.white_move_sw(11);
			win.wait_for_button();
			
			//ch.black_move_ne(2);
			ch.black_move_ne(2+11);
			win.wait_for_button();
			
			ch.white_move_se(11);
			win.wait_for_button();
			
			/*ch.white_move_se(11);
			win.wait_for_button();*/
			win.detach( ch );
			
			
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