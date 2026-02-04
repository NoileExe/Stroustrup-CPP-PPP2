

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void circle_tests(Simple_window& win);
void ellipse_tests(Simple_window& win);

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
			
			Simple_window win(tl, 600, 600, "Глава 13. Упражнение №5");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 13. Упражнение №5
			
			//------------------------------------------------------------------------------
			
			circle_tests(win);
			ellipse_tests(win);
			
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

void circle_tests(Simple_window& win) {
	Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
	
	Graph_lib::Circle c {cntr, 200};
	c.set_color(Color::red);
	c.set_style( Line_style(Line_style::solid, 2) );
	
	Text txt(Point(20, 30), "");
	txt_one_style_bold(txt);
	
	win.attach( c );
	win.attach( txt );
	
	
	
	ostringstream oss;
	oss << "Координаты n() /\\: (" << n(c).x << ";" << n(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m1{n(c), '+'};
	m1.set_color(Color::black);
	win.attach( m1 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты s() \\/: (" << s(c).x << ";" << s(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m2{s(c), '+'};
	m2.set_color(Color::black);
	win.attach( m2 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты e() >: (" << e(c).x << ";" << e(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m3{e(c), '+'};
	m3.set_color(Color::black);
	win.attach( m3 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты w() <: (" << w(c).x << ";" << w(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m4{w(c), '+'};
	m4.set_color(Color::black);
	win.attach( m4 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты center() [+]: (" << center(c).x << ";" << center(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m5{center(c), '+'};
	m5.set_color(Color::black);
	win.attach( m5 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты ne() /|: (" << ne(c).x << ";" << ne(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m6{ne(c), '+'};
	m6.set_color(Color::black);
	win.attach( m6 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты se() \\|: (" << se(c).x << ";" << se(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m7{se(c), '+'};
	m7.set_color(Color::black);
	win.attach( m7 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты sw() |/: (" << sw(c).x << ";" << sw(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m8{sw(c), '+'};
	m8.set_color(Color::black);
	win.attach( m8 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты nw() |\\: (" << nw(c).x << ";" << nw(c).y << ")";
	txt.set_label(oss.str());
	
	Mark m9{nw(c), '+'};
	m9.set_color(Color::black);
	win.attach( m9 );
	
	win.wait_for_button();
	
	win.detach( c );
	win.detach( txt );
	win.detach( m1 );
	win.detach( m2 );
	win.detach( m3 );
	win.detach( m4 );
	win.detach( m5 );
	win.detach( m6 );
	win.detach( m7 );
	win.detach( m8 );
	win.detach( m9 );
}

//------------------------------------------------------------------------------

void ellipse_tests(Simple_window& win) {
	Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
	
	Graph_lib::Ellipse ell {cntr, 200, 100};
	ell.set_color(Color::red);
	ell.set_style( Line_style(Line_style::solid, 2) );
	
	Text txt(Point(20, 30), "");
	txt_one_style_bold(txt);
	
	win.attach( ell );
	win.attach( txt );
	
	
	
	ostringstream oss;
	oss << "Координаты n() /\\: (" << n(ell).x << ";" << n(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m1{n(ell), '+'};
	m1.set_color(Color::black);
	win.attach( m1 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты s() \\/: (" << s(ell).x << ";" << s(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m2{s(ell), '+'};
	m2.set_color(Color::black);
	win.attach( m2 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты e() >: (" << e(ell).x << ";" << e(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m3{e(ell), '+'};
	m3.set_color(Color::black);
	win.attach( m3 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты w() <: (" << w(ell).x << ";" << w(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m4{w(ell), '+'};
	m4.set_color(Color::black);
	win.attach( m4 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты center() [+]: (" << center(ell).x << ";" << center(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m5{center(ell), '+'};
	m5.set_color(Color::black);
	win.attach( m5 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты ne() /|: (" << ne(ell).x << ";" << ne(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m6{ne(ell), '+'};
	m6.set_color(Color::black);
	win.attach( m6 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты se() \\|: (" << se(ell).x << ";" << se(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m7{se(ell), '+'};
	m7.set_color(Color::black);
	win.attach( m7 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты sw() |/: (" << sw(ell).x << ";" << sw(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m8{sw(ell), '+'};
	m8.set_color(Color::black);
	win.attach( m8 );
	
	win.wait_for_button();
	
	
	oss.str("");
	oss << "Координаты nw() |\\: (" << nw(ell).x << ";" << nw(ell).y << ")";
	txt.set_label(oss.str());
	
	Mark m9{nw(ell), '+'};
	m9.set_color(Color::black);
	win.attach( m9 );
	
	win.wait_for_button();
	
	win.detach( ell );
	win.detach( txt );
	win.detach( m1 );
	win.detach( m2 );
	win.detach( m3 );
	win.detach( m4 );
	win.detach( m5 );
	win.detach( m6 );
	win.detach( m7 );
	win.detach( m8 );
	win.detach( m9 );
}