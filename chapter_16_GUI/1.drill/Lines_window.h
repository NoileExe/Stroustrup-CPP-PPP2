

#include <Gui.h>
#include <Graph.h>


namespace Graph_lib {
	struct Lines_window : Window {
		Lines_window(Point xy, int w, int h, const string& title);
		
	private:
		//Данные:
		Open_polyline lines;
		
		//Виджеты:
		Button next_button;		//Добавляет пару (next_x, next_y) в объект lines
		Button quit_button;		//Завершает работу программы
		In_box next_x;
		In_box next_y;
		Out_box xy_out;
		Menu color_menu;
		Button color_menu_btn;
		Menu style_menu;
		Button style_menu_btn;
		
		void change_color(Color c) { lines.set_color(c); }
		void change_thickness(Line_style sty) { lines.set_style( sty ); }
		
		void hide_menu() {
			color_menu.hide();	color_menu_btn.show();
			style_menu.hide();	style_menu_btn.show();
		}
		
		//Действия инициируемые обратными вызовами:
		void red_pressed()   { change_color(Color::red);		hide_menu(); }
		void blue_pressed()  { change_color(Color::blue);		hide_menu(); }
		void black_pressed() { change_color(Color::black);		hide_menu(); }
		void color_menu_pressed() {
			hide_menu();
			color_menu_btn.hide();	style_menu_btn.hide();
			color_menu.show();
		}
		
		void solid_pressed()		{ change_thickness( Line_style(Line_style::solid, 2) );		hide_menu(); }
		void dash_pressed()			{ change_thickness( Line_style(Line_style::dash, 2) );		hide_menu(); }
		void dot_pressed()			{ change_thickness( Line_style(Line_style::dot, 2) );		hide_menu(); }
		void dashdot_pressed()		{ change_thickness( Line_style(Line_style::dashdot, 2) );		hide_menu(); }
		void dashdotdot_pressed()	{ change_thickness( Line_style(Line_style::dashdotdot, 2) );		hide_menu(); }
		void style_menu_pressed()	{ hide_menu();	style_menu_btn.hide();		style_menu.show(); }
		
		void next();
		void quit() { hide(); }
	};


	Lines_window::Lines_window(Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  next_button{ Point{x_max()-150, 0}, 70, 20, "Next point",
						[](Address, Address pw) { reference_to<Lines_window>(pw).next(); } },
		  quit_button{ Point{x_max()-70, 0}, 70, 20,    "Quit",
						[](Address, Address pw) { reference_to<Lines_window>(pw).quit(); } },
		  next_x{ Point{x_max()-310, 0}, 50, 20, "next x:" },
		  next_y{ Point{x_max()-210, 0}, 50, 20, "next y:" },
		  xy_out{     Point{100, 0},    100, 20, "current (x,y):" },
		  color_menu{ Point{x_max()-70, 30}, 70, 20, Menu::vertical, "Line color" },
		  color_menu_btn{ Point{x_max()-80, 30}, 80, 20,    "Color menu",
						[](Address, Address pw) { reference_to<Lines_window>(pw).color_menu_pressed(); } },
		  style_menu{ Point{x_max()-80, 60}, 80, 20, Menu::vertical, "Line style" },
		  style_menu_btn{ Point{x_max()-80, 60}, 80, 20,    "Style menu",
						[](Address, Address pw) { reference_to<Lines_window>(pw).style_menu_pressed(); } }
	{
		//Такая очерёдность прикрепления виджетов к окну позволяет переключаться последовательно между элементами по нажатию TAB
		//Пробел активирует нажатие на выбранную кнопку
		attach(xy_out);
		xy_out.put("no points");
		attach(next_x);
		attach(next_y);
		attach(next_button);
		attach(quit_button);
		
		/*attach(next_button);
		attach(quit_button);
		attach(next_x);
		attach(next_y);
		attach(xy_out);
		xy_out.put("no points");*/
		
		color_menu.attach(new Button { Point{0,0},0,0, "red",
										[](Address, Address pw) { reference_to<Lines_window>(pw).red_pressed(); } });
		color_menu.attach(new Button { Point{0,0},0,0, "blue",
										[](Address, Address pw) { reference_to<Lines_window>(pw).blue_pressed(); } });
		color_menu.attach(new Button { Point{0,0},0,0, "black",
										[](Address, Address pw) { reference_to<Lines_window>(pw).black_pressed(); } });
		attach(color_menu);
		color_menu.hide();
		
		style_menu.attach(new Button { Point{0,0},0,0, "solid",
										[](Address, Address pw) { reference_to<Lines_window>(pw).solid_pressed(); } });
		style_menu.attach(new Button { Point{0,0},0,0, "dash",
										[](Address, Address pw) { reference_to<Lines_window>(pw).dash_pressed(); } });
		style_menu.attach(new Button { Point{0,0},0,0, "dot",
										[](Address, Address pw) { reference_to<Lines_window>(pw).dot_pressed(); } });
		style_menu.attach(new Button { Point{0,0},0,0, "dashdot",
										[](Address, Address pw) { reference_to<Lines_window>(pw).dashdot_pressed(); } });
		style_menu.attach(new Button { Point{0,0},0,0, "dashdotdot",
										[](Address, Address pw) { reference_to<Lines_window>(pw).dashdotdot_pressed(); } });
		attach(style_menu);
		style_menu.hide();
		
		attach(color_menu_btn);
		attach(style_menu_btn);
		attach(lines);
	}


	void Lines_window::next() {
		hide_menu();
		
		string str_x = next_x.get_string();
		string str_y = next_y.get_string();
		if (str_x.size() == 0   ||   str_y.size() == 0)		return;
		
		int x = next_x.get_int();
		int y = next_y.get_int();
		lines.add(Point{x,y});
		
		//Обновление текущей точки в поле xy_out
		ostringstream ost;
		ost << '(' << x << ',' << y << ')';
		xy_out.put(ost.str());
		
		redraw();
	}
}