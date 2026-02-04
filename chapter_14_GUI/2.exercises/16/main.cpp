

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
			String_controller sce;		//Пустой String_controller
			cout << "\n\n" << "EMPTY String_controller sce:" << '\n';
			sce.show();
			
			cout << "\n\n" << "sce.on():" << '\n';
			sce.on();
			sce.show();
			
			cout << "\n\n" << "sce.set_level(8):" << '\n';
			sce.set_level(8);
			sce.show();
			
			press_Enter_key(true);
			cout << "-----------------------------------------------------------" << '\n';
			
			//------------------------------------------------------------------------------
			
			String_controller sc {true, 777};		//Пустой String_controller
			cout << "\n\n" << "\n\n" << "String_controller sc:" << '\n';
			sc.show();
			
			press_Enter_key(true);
			cout << "-----------------------------------------------------------" << '\n';
			
			//------------------------------------------------------------------------------
			
			Point tl{win_centering( 500, 500 )}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 500, 500, "Глава 14. Упражнение №16");
			// окно посередине экрана
			// размер окна 500*500
			// заголовок окна: Глава 14. Упражнение №16
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Graph_lib::Rectangle r {Point{cntr.x-300/2, cntr.y-300/2}, 300, 300};
			r.set_color(Color::black);
			r.set_fill_color(Color::white);
			r.set_style( Line_style(Line_style::solid, 5) );
			
			win.attach( r );
			
			
			Line_color_controller lcl {r, true, 100};
			
			cout << "\n\n" << "Line_color_controller lcl (init with link on Rectangle object (greater)):" << '\n';
			lcl.show();
			win.wait_for_button();
			
			cout << "\n\n" << "lcl.set_level(0) - change line color:" << '\n';
			lcl.set_level(0);
			lcl.show();
			win.wait_for_button();
			cout << "-----------------------------------------------------------" << '\n';
			
			//------------------------------------------------------------------------------
			
			Line_color_controller lc {new Graph_lib::Rectangle {Point{cntr.x-200/2, cntr.y-200/2}, 200, 200}, false, 155};
			lc.shape().set_color(Color::black);
			lc.shape().set_fill_color(Color::yellow);
			lc.shape().set_style( Line_style(Line_style::solid, 5) );
			
			cout << "\n\n" << "\n\n" << "Line_color_controller lc (init with new Rectangle (smaller)):" << '\n';
			lc.show();
			win.attach( lc.shape() );
			win.wait_for_button();
			
			cout << "\n\n" << "lc.on():" << '\n';
			lc.on();
			lc.show();
			win.wait_for_button();
			
			cout << "\n\n" << "lc.set_level(0) - change line color:" << '\n';
			lc.set_level(0);
			lc.show();
			win.wait_for_button();
			
			cout << "-----------------------------------------------------------" << '\n';
			
			Line_transparency_controller ltc {lc.shape(), false};
			
			cout << "\n\n" << "\n\n" << "Line_transparency_controller ltc (init with link on lc.shape() Rectangle (smaller)):" << '\n';
			ltc.show();
			win.wait_for_button();
			
			cout << "\n\n" << "ltc.on():" << '\n';
			ltc.on();
			ltc.show();
			win.wait_for_button();
			
			cout << "\n\n" << "ltc.off():" << '\n';
			ltc.off();
			ltc.show();
			win.wait_for_button();
			
			cout << "\n\n" << "ltc.on():" << '\n';
			ltc.on();
			ltc.show();
			win.wait_for_button();
			
			cout << "\n\n" << "ltc.set_level(100) - change line visibility:" << '\n';
			ltc.set_level(100);
			ltc.show();
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			Line_thickness_controller lthc {r, false, 10};
			cout << "\n\n" << "\n\n" << "Line_thickness_controller lthc (init with link on Rectangle object (greater)):" << '\n';
			lthc.show();
			win.wait_for_button();
			
			cout << "\n\n" << "lthc.on():" << '\n';
			lthc.on();
			lthc.show();
			win.wait_for_button();
			
			cout << "\n\n" << "lthc.set_level(1) - change line thickness:" << '\n';
			lthc.set_level(1);
			lthc.show();
			win.wait_for_button();
			
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