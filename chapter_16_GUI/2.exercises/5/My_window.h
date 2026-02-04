

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
	
	struct Move_figure_window : My_window {
		Move_figure_window(Point xy, int w, int h, int r, const string& title, istream& is = cin)
			: My_window{xy,w,h,title},
			  sc{Point{w/2, h/2}, r},
			  ist{is},
			  xy_out{ Point{100, 0}, 100, 20, "Current (x,y):" }
		{
			//Заменяем на изменённую ф-цию чтобы производить считывание/отображение координат и перемещение фигуры
			next_button.do_it = [](Address, Address pw) { reference_to<Move_figure_window>(pw).next(); };
			
			attach(xy_out);
			attach(sc);
			out_init();
		}
		
		Striped_circle& fig() { return sc; }
		
	private:
		//Данные:
		Striped_circle sc;	//Перемещаемая фигура
		istream& ist;
		
		
		//Виджеты:
		Out_box xy_out;
		
		void out_init() {
			ostringstream ost;
			ost << '(' << sc.center().x << ',' << sc.center().y << ')';
			xy_out.put(ost.str());
		}
		
		void next();
	};
	
	void Move_figure_window::next()
	{
		ist.clear();
		int x, y;	//Новые координаты
		char ch1, ch2, ch3;
		
		if (&ist == &cin)		cout << "\nEnter new center point in format (x,y):\n";
		
		//Считывание значений
		ist >> ch1 >> x >> ch2 >> y >> ch3;
		if (ist.eof()) {
			if (&ist == &cin)		cout << "\n\nFor exit press 'Quit' button\n\n";
			else					{ My_window::next(); return; }
		}
		
		
		if (ch1 != '('  ||  ch2 != ','  ||  ch3 != ')'  ||  ist.fail()) {
			string str;
			
			ist.unget();
			getline(ist, str);
			ist.clear();
			if (&ist == &cin)		cout << "\nBad format. Enter in format (x,y), like this\n(100,150)\n\n";
			
			next();
			return;
		}
		
		
		if (!ist) {
			ist.clear(ios_base::failbit);
			error("bad of point input");
		}
		
		
		//Обновление текущей точки в поле xy_out
		ostringstream ost;
		ost << '(' << x << ',' << y << ')';
		xy_out.put(ost.str());
		
		//Смещение относительно старого местоположения
		int dx {x - sc.center().x};
		int dy {y - sc.center().y};
		
		sc.move(dx,dy);
		if (&ist == &cin)		cout << "\nDone!\n";
		redraw();
		
		My_window::next();
	}
}