

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void txt_one_style_bold (Text& t) {
	t.set_color(Color::black);
	t.set_font(Graph_lib::Font::times_bold);
	t.set_font_size(12);
}

int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(600, 600)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 600, 600, "Глава 13. Упражнение №1");
			// размер окна (600*600)
			// заголовок окна: Глава 13. Упражнение №1
			
			Point center{win.x_max()/2, win.y_max()/2};
			Graph_lib::Arc test_arc(center, 250,250, 45,180);
			test_arc.set_color(Color::black);
			
			
			ostringstream oss;
			oss << "Центр [" << test_arc.center().x << ";" << test_arc.center().y << "]"
				<< "      Фокус 1 [" << test_arc.focus1().x << ";" << test_arc.focus1().y << "]"
				<< "      Фокус 2 [" << test_arc.focus2().x << ";" << test_arc.focus2().y << "]";
			Text txt1(Point(10, 15), oss.str());
			txt_one_style_bold(txt1);
			
			
			oss.str("");
			oss << "Радиус по горизонтали: " << test_arc.major()
				<< "      Радиус по вертикали: " << test_arc.minor();
			Text txt2(Point(10, 35), oss.str());
			txt_one_style_bold(txt2);
			
			
			Text instr(Point(10, 55), "НАЖМИТЕ КНОПКУ NEXT");
			txt_one_style_bold(instr);
			
			win.attach( txt1 );
			win.attach( txt2 );
			win.attach( instr );
			win.attach( test_arc );
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			win.set_label("Инициализация фигуры без указания углов");
			
			//Для скрытия фигуры используется ограниченная область видимости, после выхода за которую фигура уничтожается
			{
				Graph_lib::Arc test_arc2(center, 200,250);
				test_arc2.set_color(Color::black);
				win.attach( test_arc2 );
				win.wait_for_button();
			}
			
			//------------------------------------------------------------------------------
			
			win.set_label("Изменение радиусов окружности");
			
			oss.str("");
			oss << "Центр [" << test_arc.center().x << ";" << test_arc.center().y << "]"
				<< "      Фокус 1 [" << test_arc.focus1().x << ";" << test_arc.focus1().y << "]"
				<< "      Фокус 2 [" << test_arc.focus2().x << ";" << test_arc.focus2().y << "]";
			txt1.set_label(oss.str());
			
			oss.str("");
			oss << "Радиус по горизонтали: " << test_arc.major()
				<< "      Радиус по вертикали: " << test_arc.minor();
			txt2.set_label(oss.str());
			
			win.wait_for_button();
			
			
			test_arc.set_major(200);
			test_arc.set_minor(150);
			//test_arc.move(250-200, 250-150); //смещение выполняется к старому центру уже при изменении радиусов
			
			oss.str("");
			oss << "Центр [" << test_arc.center().x << ";" << test_arc.center().y << "]"
				<< "      Фокус 1 [" << test_arc.focus1().x << ";" << test_arc.focus1().y << "]"
				<< "      Фокус 2 [" << test_arc.focus2().x << ";" << test_arc.focus2().y << "]";
			txt1.set_label(oss.str());
			
			oss.str("");
			oss << "Радиус по горизонтали: " << test_arc.major()
				<< "      Радиус по вертикали: " << test_arc.minor();
			txt2.set_label(oss.str());
			
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			
			win.set_label("Раскраска фигуры");
			
			test_arc.set_color(Color::dark_green);
			test_arc.set_style( Line_style(Line_style::dashdot, 3) );
			test_arc.set_fill_color(Color::green);
			
			//------------------------------------------------------------------------------
			
			win.set_label("Изменение углов арки");
			
			oss.str("");
			oss << "Угол начальный: " << test_arc.first_ang()
				<< "      Угол конечный: " << test_arc.second_ang();
			txt2.set_label(oss.str());
			
			win.wait_for_button();
			
			
			test_arc.set_angles(test_arc.first_ang(), test_arc.first_ang()-250);
			
			oss.str("");
			oss << "Угол начальный: " << test_arc.first_ang()
				<< "      Угол конечный: " << test_arc.second_ang();
			txt2.set_label(oss.str());
			
			win.wait_for_button();
			
			
			test_arc.set_angles(test_arc.first_ang(), test_arc.first_ang()-20);
			
			oss.str("");
			oss << "Угол начальный: " << test_arc.first_ang()
				<< "      Угол конечный: " << test_arc.second_ang();
			txt2.set_label(oss.str());
			
			win.wait_for_button();
			
			
			instr.set_label("ДЛЯ ЗАВЕРШЕНИЯ ПРОГРАММЫ НАЖМИТЕ КНОПКУ NEXT");
			test_arc.set_angles(test_arc.first_ang(), 1060);
			
			oss.str("");
			oss << "Угол начальный: " << test_arc.first_ang()
				<< "      Угол конечный: " << test_arc.second_ang();
			txt2.set_label(oss.str());
			
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
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