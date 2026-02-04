

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
	
	struct Clock_window : My_window {
		Clock_window(Point xy, int w = 600, int h = 600, const string& title = "")
			: My_window{xy,w,h,title}, r{ (w-100) / 2 }
		{
			if ( y_max() < x_max() )		error("the height of the clock window must not be less than its width");
			
			next_button.hide();
			draw_clock();
		}
		
		void wait_for_button() { }
		
	private:
		void draw_clock();				//Рисует часы (marks, и вектор nums, а также их прикрепление к окну)
		void arrows_on_time(tm& ti);	//Рисует стрелки по указанному времени
		
		//Данные:
		int r;		//Внешний радиус часов
		Vector_ref<Arrow> arrows;	//Стрелки часов
		Vector_ref<Line> marks;		//Метки минут и часов
		Vector_ref<Text> nums;		//Часы 1-12
	};
	
	
	
	void Clock_window::draw_clock()
	{
		const int angle {360/60};		//Через данный угол будут помещаться деления минут/секунд
		Point cntr {x_max()/2, y_max()/2};
		
		for (int i = 90; i > -270; i-=angle) {
			Point u { point_on_circle(cntr, r, i) };
			Point d { point_on_circle(cntr, r-r/10, i) };
			if ( marks.size() % 5 == 0 ) 
				d = Point { point_on_circle(cntr, r-r/10-10, i) };
			
			marks.push_back(new Line {u, d});
			
			marks[marks.size()-1].set_color(Color::black);
			if ( (marks.size()-1) % 5 == 0 )
				marks[marks.size()-1].set_style( Line_style(Line_style::solid, r/50) );		//метки от 12 до 1 (0, 4, 9, 14, 19 и т.д.)
			else
				marks[marks.size()-1].set_style( Line_style(Line_style::solid, r/50-2) );	//метки минут
		}
		
		nums.push_back(new Text { Point{marks[0].point(1).x-r/20,			marks[0].point(1).y+r/10},			"12" });
		nums.push_back(new Text { Point{marks[5].point(1).x-r/15,			marks[5].point(1).y+r/10},			"1" });
		nums.push_back(new Text { Point{marks[10].point(1).x-r/10,			marks[10].point(1).y+2*(r/50)},		"2" });
		nums.push_back(new Text { Point{marks[15].point(1).x-r/10,			marks[15].point(1).y+2*(r/50)},		"3" });
		nums.push_back(new Text { Point{marks[20].point(1).x-r/10,			marks[20].point(1).y+r/100},		"4" });
		nums.push_back(new Text { Point{marks[25].point(1).x-r/15,			marks[25].point(1).y-2*(r/50)},		"5" });
		nums.push_back(new Text { Point{marks[30].point(1).x-2*(r/50),		marks[30].point(1).y-2*(r/50)},		"6" });
		nums.push_back(new Text { Point{marks[35].point(1).x+r/100,			marks[35].point(1).y-2*(r/50)},		"7" });
		nums.push_back(new Text { Point{marks[40].point(1).x+2*(r/50),		marks[40].point(1).y+(r/100)},		"8" });
		nums.push_back(new Text { Point{marks[45].point(1).x+2*(r/50),		marks[45].point(1).y+2*(r/50)},		"9" });
		nums.push_back(new Text { Point{marks[50].point(1).x+2*(r/50),		marks[50].point(1).y+2*(r/50)},		"10" });
		nums.push_back(new Text { Point{marks[55].point(1).x-2*(r/50),		marks[55].point(1).y+r/10},			"11" });
		
		
		for (int i=0; i < marks.size(); ++i)		attach(marks[i]);
		
		for (int i=0; i < nums.size(); ++i) {
			attach(nums[i]);
			nums[i].set_color(Color::black);
			nums[i].set_font(Graph_lib::Font::courier_bold);
			nums[i].set_font_size( r/10 );
		}
		
		redraw();
		
		while (true) {
			time_t seconds = time(NULL);
			struct tm* timeinfo = localtime(&seconds);
			tm ti = *timeinfo;
			
			arrows_on_time(ti);
			
			Fl::redraw();
			Fl::wait();
			Fl::redraw();
			
			//Sleep(1000);		//For WINDOWS
			//sleep(1000);		//For UNIX
			
			clock_t start = clock();
			clock_t  stop = clock();
			while (stop-start < 1000)	stop = clock();
		}
	}
	
	
	
	void Clock_window::arrows_on_time(tm& ti)
	{
		arrows.Vector_ref::~Vector_ref();
		
		Point cntr {x_max()/2, y_max()/2};
		Point smh;
		
		if ( ti.tm_sec > 59 )		ti.tm_sec = 0;
		
		smh = point_on_circle(cntr,   r-r/10,   90 - ti.tm_sec*(360/60));
		arrows.push_back( new Arrow {cntr, smh} );
		arrows[arrows.size()-1].set_color(Color::red);
		arrows[arrows.size()-1].set_style( Line_style(Line_style::solid, 2) );
		
		smh = point_on_circle(cntr,   r-r/5,   90 - ti.tm_min*(360/60));
		arrows.push_back( new Arrow {cntr, smh} );
		arrows[arrows.size()-1].set_color(Color::blue);
		arrows[arrows.size()-1].set_style( Line_style(Line_style::solid, 3) );
		
		smh = point_on_circle(cntr,   r-r/3,   90 - (ti.tm_hour%12)*(360/12));
		arrows.push_back( new Arrow {cntr, smh} );
		arrows[arrows.size()-1].set_color(Color::black);
		arrows[arrows.size()-1].set_style( Line_style(Line_style::solid, 3) );
		
		
		for (int i=0; i < arrows.size(); ++i)		attach(arrows[i]);
	}
}