

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void octagon_test (Simple_window& win);

void txt_one_style_bold (Text& t) {
	t.set_color(Color::black);
	t.set_font(Graph_lib::Font::times_bold);
	t.set_font_size(18);
}

int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(600, 600)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 600, 600, "Глава 14. Упражнение №8");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 14. Упражнение №7
			
			octagon_test(win);
			
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

void octagon_test (Simple_window& win)
{
	cout << "\n\n" << "Press NEXT button to continue\n\n";
	
	Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
	Octagon o{cntr, 200};
	win.attach(o);
	win.wait_for_button();
	
	cout << "\tSET color(Color::black) | fill color(Color::cyan) | border style( Line_style(Line_style::solid, 2) )\n\n";
	o.set_color(Color::black);
	o.set_fill_color(Color::cyan);
	o.set_style( Line_style(Line_style::solid, 2) );
	win.wait_for_button();
	
	cout << "\tGET color:        " << o.color() << "\n";
	cout << "\tGET fill color:   " << o.fill_color() << "\n";
	cout << "\tGET border style: " << o.style() << "\n\n";
	win.wait_for_button();
	
	cout << "\tGET figure points (points count = " << o.number_of_points() << ")\n";
	for (int i=0; i < o.number_of_points(); ++i)
		cout << o.point(i)  << "\n";
		
	cout << "\n";
	win.wait_for_button();
	
	cout << "\tMOVE figure down (bias = 50 x, 50 y)\n\n";
	o.move(50, 50);
	win.wait_for_button();
	
	cout << "\tGET new figure points (points count = " << o.number_of_points() << ")\n";
	for (int i=0; i < o.number_of_points(); ++i)
		cout << o.point(i)  << "\n";
		
	cout << "\n";
	win.wait_for_button();
	
	cout << "\tGET count of angles: " << o.num_of_angles() << "\n";
	cout << "\tGET lenght of every side: " << o.side_ln() << "\n";
	cout << "\tGET figure center point: " << o.center() << "\n";
	cout << "\tGET inner circle radius: " << o.in_radius() << "\n";
	cout << "\tGET outer circle radius: " << o.out_radius() << "\n";
	cout << "\tGET figure radius: " << o.radius() << "\n";
	win.wait_for_button();
	win.detach(o);
}