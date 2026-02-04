

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
			Point tl{win_centering(360, 360)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 360, 360, "Глава 13. Упражнение №13");
			// окно посередине экрана
			// размер окна (360*360)
			// заголовок окна: Глава 13. Упражнение №13
			
			Vector_ref<Graph_lib::Rectangle> vr;
			
			for (int i = 0; i<16; ++i)
				for (int j = 0; j<16; ++j)
				{
					vr.push_back( new Graph_lib::Rectangle {Point{i*20+20, j*20+20}, 20, 20} );
					vr[vr.size()-1].set_color( Color::invisible );		//Самый последний конструктор класса Color
					vr[vr.size()-1].set_fill_color(Color{i*16+j});
					win.attach(vr[vr.size()-1]);
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