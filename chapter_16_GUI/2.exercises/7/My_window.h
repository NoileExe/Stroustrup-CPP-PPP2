

#include <addition.h>
#include <time.h>


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
	
	struct Fly_img_window : My_window {
		Fly_img_window(Point xy, int w, int h, const string& title, const string& path, Fct* f)
			: My_window{xy,w,h,title},
			  bg{ Point{0, 21}, w, h-21 },
			  route{ f,   -(w/20)/2.0-2, (w/20)/2.0,   Point{w/2, h/2},   500, 20.0, 20.0 },
			  curr_point_num{ 0 },
			  img{ route.point(curr_point_num), path }
		{
			//Заменяем на несколько изменённую ф-цию чтобы изменять текст кнопки
			next_button.do_it = [](Address, Address pw) { reference_to<Fly_img_window>(pw).next(); };
			next_button.label = "Start";
			
			bg.set_color(Color::white);
			bg.set_fill_color(Color::white);
			attach(bg);
			attach(img);
		}
		
		void wait_for_button() { next(); }
		void start_fly();		//Передвижение фигуры
		
		
		void set_bg_color(Color col) { bg.set_color(col);		bg.set_fill_color(col); }
		
		void set_points_count (int c) {
			route.set_count(c);
			curr_point_num = 0;
			int dx {route.point(0).x - img.point(0).x};
			int dy {route.point(0).y - img.point(0).y};
			img.move(dx, dy); //Смещение относительно старого местоположения
			Fl::redraw();
		}
		
		void set_function(Fct* f) {
			route.set_function(f);
			curr_point_num = 0;
			int dx {route.point(0).x - img.point(0).x};
			int dy {route.point(0).y - img.point(0).y};
			img.move(dx, dy); //Смещение относительно старого местоположения
			Fl::redraw();
			//Fl::wait();
		}
		
	private:
		//Реализация:
		Rectangle bg;		//Белый фон
		void next();		//Нажатие кнопки Start/Stop
		
		
		//Данные:
		Moded_Function<int> route;		//По точкам ф-ции будет перемещаться картинка
		int curr_point_num;				//Индекс перебираемой для смещения картинки точки ф-ции route
		Image img;						//Перемещаемая картинка
	};
	
	
	
	void Fly_img_window::start_fly() {
		while (!button_pushed)
		{
			if ( curr_point_num == route.number_of_points()-1 )
				curr_point_num = 0;
			else
				++curr_point_num;
			
			//Смещение относительно старого местоположения
			int dx {route.point(curr_point_num).x - img.point(0).x};
			int dy {route.point(curr_point_num).y - img.point(0).y};
			img.move(dx, dy);
			
			clock_t start = clock();
			clock_t  stop = clock();
			while (stop-start < 40)		stop = clock();
			
			Fl::redraw();
			Fl::wait();
			//Fl::redraw();
		}
		
		button_pushed = false;
		Fl::redraw();
	}
	
	
	void Fly_img_window::next() {
		if (next_button.label == "Stop") {
			My_window::next();
			next_button.label = "Start";
		}
		else {
			button_pushed = false;
			next_button.label = "Stop";
			start_fly();
		}
	}
}