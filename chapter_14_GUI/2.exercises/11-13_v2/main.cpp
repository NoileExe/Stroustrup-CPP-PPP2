

//#define _USE_MATH_DEFINES

#include <yes_or_no.h>
#include "addition_intermediate_version.h"


const string quit_question = "Close program?";


//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Point tl{addition_intermediate_version::win_centering( x_max(), y_max() )}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, x_max(), y_max(), "Глава 14. Упражнение №11");
			// окно посередине экрана
			// размер окна по текущему разрешению экрана (на весь экран)
			// заголовок окна: Глава 14. Упражнение №11
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			//Обычные линии (упражение 11)
			for (int i = 0; i < 9; ++i) {
				win.set_label("Уровень дерева = " + to_string(i));
				
				addition_intermediate_version::Binary_tree bt {Point{cntr.x, 40}, i};
				bt.set_color(Color::dark_yellow);
				
				win.attach( bt );
				cout << '\n' << "Tree  LVLs count: " << bt.levels_count() << '\n';
				cout <<			"Tree NODEs count: " << bt.nodes_count() << '\n';
				win.wait_for_button();
				
				win.detach( bt );
			}
			
			//------------------------------------------------------------------------------
			
			//Обычные линии и TXTBox вместо кружков (упражение 12)
			for (int i = 0; i < 9; ++i) {
				win.set_label("Уровень TXTBox дерева = " + to_string(i));
				
				addition_intermediate_version::Binary_txt_tree bt {Point{cntr.x, 40}, i};
				bt.set_color(Color::dark_red);
				bt.set_fill_color(Color::green);
				
				win.attach( bt );
				
				cout << '\n' << "Tree  LVLs count: " << bt.levels_count() << '\n';
				cout <<			"Tree NODEs count: " << bt.nodes_count() << '\n';
				win.wait_for_button();
				
				win.detach( bt );
			}
			
			//------------------------------------------------------------------------------
			
			//Стрелки вверх без изменения их цвета в конструкторе (упражение 13)
			win.set_label("Глава 14. Упражнение №13");
			
			addition_intermediate_version::Binary_tree btu {Point{cntr.x, 40}, 6, "up"};
			
			win.attach( btu );
			win.wait_for_button();
			
			btu.set_color(Color::dark_red);
			win.wait_for_button();
			
			btu.set_arrow_color(Color::cyan);
			win.wait_for_button();
			
			win.detach( btu );
			
			
			//Стрелки вниз с изменением их цвета в конструкторе (упражение 13)
			addition_intermediate_version::Binary_tree btd {Point{cntr.x, 40}, 7, "down", Color::magenta};
			win.attach( btd );
			win.wait_for_button();
			
			btd.set_fill_color(Color::green);
			win.wait_for_button();
			
			btd.set_style( Line_style(Line_style::solid, 5) ); //Не работает, т.к. нет перезагруженной ф-ции
			win.wait_for_button();
			
			btd.move(50, 50);
			win.wait_for_button();
			
			win.detach( btd );
			
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

//------------------------------------------------------------------------------