

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
	
	struct Function_window : My_window {
		Function_window(Point xy = win_centering(600,600), int w = 600, int h = 600, const string& title = "Many funcs");
		
		void wait_for_button() {  } //My_window::wait_for_button();
		
	private:
		//Данные:
		Axis x;
		Axis y;
		Moded_Function<int> func;
		
		
		//Виджеты:
		In_box r1;			//Диапазон от
		In_box r2;			//Диапазон до
		In_box pnts;		//Количество точек для построения ф-ции
		In_box prec;		//Точность вычислений
		Menu func_menu;		//Выбор функций
		
		void next() { hide_menu();		next_button.hide();		func_menu.show(); }
		void hide_menu() { func_menu.hide();		next_button.show(); }
		void str_check(const string& str);		//Вспомогательная ф-ция проверяющая правильность ввода числа
		void draw_function(Fct f);				//Изменяет параметры ф-ции
	};
	
	
	
	Function_window::Function_window(Point xy, int w, int h, const string& title)
		: My_window{xy,w,h,title},
		  x{Axis::x,   Point{20, h/2},   w-60,   20,   "X"},
		  y{Axis::y,   Point{w/2, h-20}, h-60,   20,   "Y"},
		  func{sin,   -10.0, 10.0,   Point{w/2, h/2},   500, (w-60)/20.0, (h-60)/20.0},
		  r1  {  Point{30, 0}, 40, 20, "ОТ" },
		  r2  {  Point{102, 0}, 40, 20, "ДО" },
		  pnts{  Point{190, 0}, 40, 20, "точек" },
		  prec{  Point{300, 0}, 40, 20, "точность" },
		  func_menu{ Point{x_max()-150, 0}, 70, 20, Menu::vertical, "Изменить ф-цию" }
	{
		//Деформирует ось x
		/*if (x_max() < 500) {
			detach(next_button);
			detach(quit_button);
			resize(500, y_max());
			next_button.loc = Point{x_max()-150, 0};
			quit_button.loc = Point{x_max()-70, 0};
			attach(next_button);
			attach(quit_button);
		}*/
		
		//Заменяем на изменённую ф-цию
		next_button.do_it = [](Address, Address pw) { reference_to<Function_window>(pw).next(); };
		next_button.label = "Функция";
		
		x.set_color(Color::dark_red);
		x.label.move(w-w/3-10, -18);
		x.label.set_font_size(10);
		
		y.set_color(Color::dark_red);
		y.label.move(9, 5);
		y.label.set_font_size(10);
		
		func.set_color(Color::black);
		func.set_style( Line_style(Line_style::solid, 2) );
		
		func_menu.attach(new Button { Point{0,0},0,0, "sqrt()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(sqrt); } });
		func_menu.attach(new Button { Point{0,0},0,0, "sin()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(sin); } });
		func_menu.attach(new Button { Point{0,0},0,0, "cos()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(cos); } });
		func_menu.attach(new Button { Point{0,0},0,0, "tan()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(tan); } });
		func_menu.attach(new Button { Point{0,0},0,0, "asin()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(asin); } });
		func_menu.attach(new Button { Point{0,0},0,0, "acos()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(acos); } });
		func_menu.attach(new Button { Point{0,0},0,0, "atan()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(atan); } });
		func_menu.attach(new Button { Point{0,0},0,0, "sinh()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(sinh); } });
		func_menu.attach(new Button { Point{0,0},0,0, "cosh()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(cosh); } });
		func_menu.attach(new Button { Point{0,0},0,0, "tanh()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(tanh); } });
		func_menu.attach(new Button { Point{0,0},0,0, "exp()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(exp); } });
		func_menu.attach(new Button { Point{0,0},0,0, "log()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(log); } });
		func_menu.attach(new Button { Point{0,0},0,0, "log10()",
							[](Address, Address pw) { reference_to<Function_window>(pw).draw_function(log10); } });
		
		attach(x);
		attach(y);
		attach(r1);
		attach(r2);
		attach(pnts);
		attach(prec);
		attach(func_menu);
		func_menu.hide();
	}
	
	
	//Вспомогательная ф-ция проверяющая правильность ввода числа
	//Если найдена ошибка - программа завершается через вызов соотв. ф-ции error
	void Function_window::str_check(const string& str) {
		for (int i=0; i < str.size(); ++i)
			if ( str[i] == '.' )		error("you can only enter integer numbers");
			
			else if ( isdigit(str[i])  ||  str[i] == '-' )
				{ if ( str[i] == '-'  &&  i != 0 )		error("bad input"); }
			
			else						error("bad input");
	}
	
	void Function_window::draw_function(Fct f) {
		hide_menu();
		detach(func);
		
		//Конечно в идеале было бы проверять значения и затем указывать на ошибку,
		// но в данном случае без изменения класса Widget это невозможно.
		//Поэтому решено что ошибки так же будет проверять сам класс при изменении
		// его аргументов и прекращать работу программы соответствующим сообщением об ошибке
		//Какие-то ошибки будут проверяться прямо здесь
		
		double a {nan("1")};		//Диапазон от
		double b {nan("1")};		//Диапазон до
		double n {nan("1")};		//Количество точек для построения ф-ции
		double p {nan("1")};		//Точность вычислений
		
		
		istringstream iss;
		
		string data {r1.get_string()};
		str_check(data);
		iss.str(data);
		iss >> a;
		
		data = r2.get_string();
		str_check(data);
		iss.str("");
		iss.clear();
		iss.str(data);
		iss >> b;
		
		data = pnts.get_string();
		str_check(data);
		iss.str("");
		iss.clear();
		iss.str(data);
		iss >> n;
		
		data = prec.get_string();
		str_check(data);
		iss.str("");
		iss.clear();
		iss.str(data);
		iss >> p;
		
		
		if ( !isnan(a)  ||  !isnan(b) ) {
			if ( isnan(a) )			func.set_range(func.begin(), b);
			else if ( isnan(b) )	func.set_range(a,   func.end());
			else					func.set_range(a, b);
		}
		if ( !isnan(n) )		func.set_count( int(n) );
		if ( !isnan(p) )		func.set_precision( int(p) );
		func.set_function(f);
		
		attach(func);
	}
}