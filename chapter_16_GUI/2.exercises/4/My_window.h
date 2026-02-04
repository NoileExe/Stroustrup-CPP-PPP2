

#include <addition.h>


namespace Graph_lib
{
	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title)
			: Window{xy,w,h,title},
			  button_pushed(false),
			  next_button{ Point{x_max()-150, 0}, 70, 20, "Next",
							[](Address, Address pw) { reference_to<My_window>(pw).next(); } },
			  quit_button{ Point{x_max()-70, 0},  70, 20, "Quit",
							[](Address, Address pw) { reference_to<My_window>(pw).quit(); } }
		{
			attach(next_button);
			attach(quit_button);
		}
		
		void wait_for_button() {
			while (!button_pushed) Fl::wait();
			button_pushed = false;
			Fl::redraw();
		}
		
	protected:
		Button next_button;		//Добавляет пару (next_x, next_y) в объект lines
		Button quit_button;		//Завершает работу программы
		
		bool button_pushed;		//Деталь реализации класса
		
		virtual void next() { button_pushed = true; }
		virtual void quit() { hide(); exit(0); }
	};
	
	//------------------------------------------------------------------------------
	
	struct Enter_point_window : My_window {
		Enter_point_window(Point xy, int w = 190, int h = 100, const string& title = "")
			: My_window{xy,w,h,title},
			  next_x{ Point{x_max()-150, 10}, 50, 20, "X:" },
			  next_y{ Point{x_max()-150, 40}, 50, 20, "Y:" },
			  next_r{ Point{x_max()-150, 70}, 50, 20, "Rad:" }
		{
			next_button.move(x_max()-80 - next_button.loc.x, 10);
			next_button.label = "OK";
			next_button.do_it = [](Address, Address pw) { reference_to<Enter_point_window>(pw).next(); };
			
			quit_button.move(-10, 40);
			quit_button.label = "Cancel";
			quit_button.do_it = [](Address, Address pw) { reference_to<Enter_point_window>(pw).quit(); };
			
			attach(next_x);
			attach(next_y);
			attach(next_r);
		}
		
		void wait_for_button() {
			set_label("Enter figure center and radius");
			while (!button_pushed) Fl::wait();
			
			string str_x = next_x.get_string();
			string str_y = next_y.get_string();
			string str_r = next_r.get_string();
			if (str_x.size() == 0   ||   str_y.size() == 0   ||   str_r.size() == 0)
				return;
			
			x = next_x.get_int();
			y = next_y.get_int();
			r = next_r.get_int();
			
			button_pushed = false;
			Fl::redraw();
		}
		
		//Данные:
		int x, y, r;
		
	private:
		
		//Виджеты:
		In_box next_x;
		In_box next_y;
		In_box next_r;
		
		
		//Действия инициируемые обратными вызовами:
		void next() {
			string str_x = next_x.get_string();
			string str_y = next_y.get_string();
			string str_r = next_r.get_string();
			if (str_x.size() == 0   ||   str_y.size() == 0   ||   str_r.size() == 0)
				return;
			
			hide();
			My_window::next();
		}
		
		void quit() { hide(); }
	};
	
	//------------------------------------------------------------------------------
	
	struct Four_Figures_window : My_window {
		Four_Figures_window(Point xy, int w, int h, const string& title)
			: My_window{xy,w,h,title},
			  data_win{Point{win_centering(w+400, h)}},
			  figure_menu{ Point{x_max()-120, 30}, 120, 20, Menu::vertical, "Add figure" },
			  menu_btn{ Point{x_max()-120, 30},    120, 20,    "Figure menu",
						[](Address, Address pw) { reference_to<Four_Figures_window>(pw).figure_menu_press(); } }
		{
			//Заменяем на несколько изменённую ф-цию чтобы скрывать открытое меню
			next_button.do_it = [](Address, Address pw) { reference_to<Four_Figures_window>(pw).next(); };
			
			figure_menu.attach(new Button { Point{0,0},0,0, "Circle",
								[](Address, Address pw) { reference_to<Four_Figures_window>(pw).circle_press(); } });
			figure_menu.attach(new Button { Point{0,0},0,0, "Square",
								[](Address, Address pw) { reference_to<Four_Figures_window>(pw).square_press(); } });
			figure_menu.attach(new Button { Point{0,0},0,0, "Regular triangle",
								[](Address, Address pw) { reference_to<Four_Figures_window>(pw).triang_press(); } });
			figure_menu.attach(new Button { Point{0,0},0,0, "Hexagon",
								[](Address, Address pw) { reference_to<Four_Figures_window>(pw).hexagon_press(); } });
			attach(figure_menu);
			figure_menu.hide();
			attach(menu_btn);
			
			data_win.hide();
		}
		
		void wait_for_button() { My_window::wait_for_button(); }
		
	private:
		//Данные:
		Group shapes;	//Группа всех добавленых фигур
		
		
		//Виджеты:
		Enter_point_window data_win;
		Menu figure_menu;
		Button menu_btn;
		
		void next() { hide_menu();		My_window::next(); }
		void hide_menu() { figure_menu.hide();		menu_btn.show(); }
		
		
		//Действия инициируемые обратными вызовами:
		void circle_press();
		void square_press();
		void triang_press();
		void hexagon_press();
		
		void figure_menu_press() { hide_menu();		menu_btn.hide();	figure_menu.show(); }
	};
	
	
	void Four_Figures_window::circle_press() {
		int x {-1};
		int y {-1};
		int r {0};
		
		//while (x < r  ||  y < r  ||  x > x_max()-r  ||  y > y_max()-r  ||  r <= 0)
		//while (x < 0  ||  y < 0  ||  x > x_max()  ||  y > y_max()) {
		//{
			data_win.show();
			data_win.Enter_point_window::wait_for_button();
			x = data_win.x;
			y = data_win.y;
			r = data_win.r;
		//}
		
		shapes.add_shape(new Circle {Point{x,y}, r});
		
		shapes[shapes.size()-1].set_color(Color::dark_green);
		shapes[shapes.size()-1].set_fill_color(Color::green);
		shapes[shapes.size()-1].set_style( Line_style(Line_style::solid, 2) );
		
		attach( shapes[shapes.size()-1] );
		hide_menu();
	}
	
	void Four_Figures_window::square_press() {
		int x {-1};
		int y {-1};
		int r {0};
		
		//while (x < r  ||  y < r  ||  x > x_max()-r  ||  y > y_max()-r  ||  r <= 0)
		//{
			data_win.show();
			data_win.wait_for_button();
			x = data_win.x;
			y = data_win.y;
			r = data_win.r;
		//}
		
		shapes.add_shape(new Regular_polygon {Point{x,y}, r, 4});
		
		shapes[shapes.size()-1].set_color(Color::dark_magenta);
		shapes[shapes.size()-1].set_fill_color(Color::magenta);
		shapes[shapes.size()-1].set_style( Line_style(Line_style::solid, 2) );
		
		attach( shapes[shapes.size()-1] );
		hide_menu();
	}
	
	void Four_Figures_window::triang_press() {
		int x {-1};
		int y {-1};
		int r {0};
		
		//while (x < r  ||  y < r  ||  x > x_max()-r  ||  y > y_max()-r  ||  r <= 0)
		//{
			data_win.show();
			data_win.wait_for_button();
			x = data_win.x;
			y = data_win.y;
			r = data_win.r;
		//}
		
		shapes.add_shape(new Regular_polygon {Point{x,y}, r, 3});
		
		shapes[shapes.size()-1].set_color(Color::dark_yellow);
		shapes[shapes.size()-1].set_fill_color(Color::yellow);
		shapes[shapes.size()-1].set_style( Line_style(Line_style::solid, 2) );
		
		attach( shapes[shapes.size()-1] );
		hide_menu();
	}
	
	void Four_Figures_window::hexagon_press() {
		int x {-1};
		int y {-1};
		int r {0};
		
		//while (x < r  ||  y < r  ||  x > x_max()-r  ||  y > y_max()-r  ||  r <= 0)
		//{
			data_win.show();
			data_win.wait_for_button();
			x = data_win.x;
			y = data_win.y;
			r = data_win.r;
		//}
		
		shapes.add_shape(new Regular_polygon {Point{x,y}, r, 6});
		
		shapes[shapes.size()-1].set_color(Color::dark_red);
		shapes[shapes.size()-1].set_fill_color(Color::red);
		shapes[shapes.size()-1].set_style( Line_style(Line_style::solid, 2) );
		
		attach( shapes[shapes.size()-1] );
		hide_menu();
	}
}