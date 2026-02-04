

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
			
			Simple_window win(tl, 500, 500, "Глава 13. Упражнение №18");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 13. Упражнение №18
			
			vector<Point> pnts;
			pnts.push_back(Point{100, 50});
			pnts.push_back(Point{30, 150});
			pnts.push_back(Point{130, 160});
			//pnts.push_back(Point{50, 40});
			//pnts.push_back(Point{160, 10});
			
			Poly p {pnts};
			p.set_color(Color::black);
			p.set_fill_color(Color::dark_yellow);
			win.attach(p);
			
			//p.add(Point{50, 40});
			p.add(Point{160, 10});
			
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