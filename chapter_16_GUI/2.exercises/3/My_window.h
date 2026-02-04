

#include <addition.h>
#include <random>


namespace Graph_lib
{
	inline int rand_int(int min, int max) {
		static default_random_engine ran;
		return uniform_int_distribution<>{min,max} (ran);
	}
	
	Point rand_point(int xmax, int ymax) {
		int x { rand_int(0, xmax) };
		int y { rand_int(0, ymax) };
		return Point{x, y};
	}
	
	
	
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
		
	private:
		Button next_button;		//Добавляет пару (next_x, next_y) в объект lines
		Button quit_button;		//Завершает работу программы
		
		bool button_pushed;		//Деталь реализации класса
		
		void next() { button_pushed = true; }
		void quit() { hide(); exit(0); }
	};
	
	struct Jumping_button_window : My_window {
		Jumping_button_window(Point xy, int w, int h, const string& title, const string& img)
			: My_window{xy,w,h,title},
			  jumping_button{ Point{0,0}, 60, 60, "+",
								[](Address, Address pw) { reference_to<Jumping_button_window>(pw).jump(); } },
			  button_img{Point{0,0}, img}
		{
			button_img.set_mask(Point{0, 0}, 60, 60);
			
			attach(jumping_button);
			attach(button_img);
			
			const int lim_x = x_max()-jumping_button.width*2;
			const int lim_y = y_max()-jumping_button.height*2;
			Point rndp { rand_point(lim_x, lim_y) };
			jumping_button.move(rndp.x, rndp.y);
			button_img.move(rndp.x, rndp.y);
		}
		
	private:
		void jump();
		
		Button jumping_button;		//Прыгающая кнопка
		Image button_img;			//Изображение поверх неё
	};
	
	
	void Jumping_button_window::jump() {
		const int lim_x = x_max()-jumping_button.width;
		const int lim_y = y_max()-jumping_button.height;
		
		//Новая точка
		Point rndp { rand_point(lim_x, lim_y) };
		
		//Смещение относительно старого местоположения
		int dx {rndp.x - jumping_button.loc.x};
		int dy {rndp.y - jumping_button.loc.y};
		
		jumping_button.move(dx, dy);
		button_img.move(dx, dy);
	}
}