

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

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
			
			Simple_window win(tl, 600, 600, "Глава 13. Упражнение №4");
			// окно посередине экрана
			// размер окна (600*600)
			// заголовок окна: Глава 13. Упражнение №4
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Graph_lib::Rectangle r {Point(cntr.x - 200/2, cntr.y - 300/2), 200, 300};
			r.set_color(Color::black);
			r.set_style( Line_style(Line_style::solid, 2) );
			
			Text txt(Point(20, 30), "");
			txt_one_style_bold(txt);
			
			win.attach( r );
			win.attach( txt );
			
			//------------------------------------------------------------------------------
			
			ostringstream oss;
			oss << "Координаты n() /\\: (" << n(r).x << ";" << n(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m1{n(r), '+'};
			m1.set_color(Color::red);
			win.attach( m1 );
			
			win.wait_for_button();
			
			
			oss.str("");
			oss << "Координаты s() \\/: (" << s(r).x << ";" << s(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m2{s(r), '+'};
			m2.set_color(Color::red);
			win.attach( m2 );
			
			win.wait_for_button();
			
			
			oss.str("");
			oss << "Координаты e() >: (" << e(r).x << ";" << e(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m3{e(r), '+'};
			m3.set_color(Color::red);
			win.attach( m3 );
			
			win.wait_for_button();
			
			
			oss.str("");
			oss << "Координаты w() <: (" << w(r).x << ";" << w(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m4{w(r), '+'};
			m4.set_color(Color::red);
			win.attach( m4 );
			
			win.wait_for_button();
			
			
			oss.str("");
			oss << "Координаты center() [+]: (" << center(r).x << ";" << center(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m5{center(r), '+'};
			m5.set_color(Color::red);
			win.attach( m5 );
			
			win.wait_for_button();
			
			
			oss.str("");
			oss << "Координаты ne() /|: (" << ne(r).x << ";" << ne(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m6{ne(r), '+'};
			m6.set_color(Color::red);
			win.attach( m6 );
			
			win.wait_for_button();
			
			
			oss.str("");
			oss << "Координаты se() \\|: (" << se(r).x << ";" << se(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m7{se(r), '+'};
			m7.set_color(Color::red);
			win.attach( m7 );
			
			win.wait_for_button();
			
			
			oss.str("");
			oss << "Координаты sw() |/: (" << sw(r).x << ";" << sw(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m8{sw(r), '+'};
			m8.set_color(Color::red);
			win.attach( m8 );
			
			win.wait_for_button();
			
			
			oss.str("");
			oss << "Координаты nw() |\\: (" << nw(r).x << ";" << nw(r).y << ")";
			txt.set_label(oss.str());
			
			Mark m9{nw(r), '+'};
			m9.set_color(Color::red);
			win.attach( m9 );
			
			win.wait_for_button();
			
			win.detach( r );
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