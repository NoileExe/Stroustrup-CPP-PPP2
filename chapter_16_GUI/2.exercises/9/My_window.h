

#include <addition.h>
#include "calc.h"


const istringstream istr {"that const istringstream variable"};
const string istrtype { typeid(istr).name() };


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
	
	struct Calculator_window : My_window {
		Calculator_window(Point xy = win_centering(340,80), int w = 340, int h = 80, const string& title = "Калькулятор");
		
		void wait_for_button() {  } //My_window::wait_for_button();
		
	private:
		//Виджеты:
		In_box input;
		Out_box result;
		
		
		//Реализация:
		void next();		//Собственно конвертация
	};
	
	
	
	Calculator_window::Calculator_window(Point xy, int w, int h, const string& title)
		: My_window{xy, w, h, title},
		  input{  Point{50, 10}, 200, 20, "Ввод" },
		  result{ Point{50, 50}, 200, 20, "Вывод" }		//Решение
	{
		//------------------------------------------------------------------------------
		
		var_table.define("pi", 3.1415926535, true);
		var_table.define("e", 2.7182818284, true);
		var_table.define("k", 1000, true);
		
		//Заменяем на несколько изменённую ф-цию чтобы изменять текст кнопки
		next_button.do_it = [](Address, Address pw) { reference_to<Calculator_window>(pw).next(); };
		next_button.label = "Calculate";
		next_button.move(70,10);
		quit_button.move(-10,50);
		
		detach(next_button);
		attach(input);
		attach(next_button);
		attach(result);
	}
	
	
	void Calculator_window::next() {
		resize(340,80);
		
		ostringstream oss;
		istringstream iss { input.get_string() + PRINT };
		if ( iss.str().size() == 1 ) {
			result.put( "Пустое поле ввода" );
			return;
		}
		
		//Таким образом можно было бы в ф-ции calculate() идентифицировать строковый поток ввода
		//if ( typeid(iss).name() == istrtype )		cout << "POPADANIE\n";
		
		char ch { calculate(iss,oss) };
		
		
		if ( ch == PRINT )
			result.put( oss.str() );
		
		else if ( ch == QUIT )
			//My_window::quit();		//Мгновенный выход, как и было задумано
			result.put( "Нажмите QUIT для выхода" );
		
		else if ( ch == HELP  ||  ch == TABLEOUT )
			result.put( "См. результат в консоли" );
		
		else if ( ch == EWARNING )
			//result.put( oss.str() );		//Вывод ошибки в GUI, хотя можно было бы сделать и отдельное окно для этого
			result.put( "Ошибка. См. в консоли" );
		
		
		My_window::next();
	}
}