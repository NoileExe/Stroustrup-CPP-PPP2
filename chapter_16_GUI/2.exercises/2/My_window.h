

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
		
	private:
		Button next_button;		//Добавляет пару (next_x, next_y) в объект lines
		Button quit_button;		//Завершает работу программы
		
		bool button_pushed;		//Деталь реализации класса
		
		void next() { button_pushed = true; }
		void quit() { hide(); exit(0); }
	};
	
	
	struct Button_shaped_window : My_window {
		Button_shaped_window(Point xy, int w, int h, const string& title)
			: My_window{xy,w,h,title}
		{
			int xcell_side {x_max()/5};
			int ycell_side {y_max()/5};
			Point p {xcell_side/2, ycell_side/2};
			
			for (int i=0; i<4; ++i)
				for (int j=0; j<4; ++j)
				{
					int indx   { board.size() };
					string str { to_string(indx) };
					Point aul {p.x + j*xcell_side, p.y + i*ycell_side}; //Угол фигуры левый верхний
					
					Callback lambdafunc		  {  [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc0(); }  };
					if (indx == 1)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc1(); };
					if (indx == 2)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc2(); };
					if (indx == 3)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc3(); };
					if (indx == 4)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc4(); };
					if (indx == 5)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc5(); };
					if (indx == 6)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc6(); };
					if (indx == 7)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc7(); };
					if (indx == 8)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc8(); };
					if (indx == 9)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc9(); };
					if (indx == 10)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc10(); };
					if (indx == 11)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc11(); };
					if (indx == 12)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc12(); };
					if (indx == 13)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc13(); };
					if (indx == 14)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc14(); };
					if (indx == 15)	lambdafunc = [](Address, Address pw) { reference_to<Button_shaped_window>(pw).nc15(); };
					
					board.push_back( new Button {aul, xcell_side, ycell_side, str, lambdafunc} );
					
					recs.push_back( new Rectangle {aul, xcell_side, ycell_side} );
					recs[recs.size()-1].set_color(Color::black);
				}
				
			for (int i=0; i < board.size(); ++i)	attach(board[i]);
			for (int i=0; i < recs.size(); ++i)		attach(recs[i]);
			reset_colors();
		}
	
	private:
		void reset_colors();
		void next_color(int r);
		
		void nc0() { next_color(0); }
		void nc1() { next_color(1); }
		void nc2() { next_color(2); }
		void nc3() { next_color(3); }
		void nc4() { next_color(4); }
		void nc5() { next_color(5); }
		void nc6() { next_color(6); }
		void nc7() { next_color(7); }
		void nc8() { next_color(8); }
		void nc9() { next_color(9); }
		void nc10() { next_color(10); }
		void nc11() { next_color(11); }
		void nc12() { next_color(12); }
		void nc13() { next_color(13); }
		void nc14() { next_color(14); }
		void nc15() { next_color(15); }
		
		Vector_ref<Button>		board;
		Vector_ref<Rectangle>	recs;
	};
	
	
	void Button_shaped_window::reset_colors() {
		for (int i=0; i<4; ++i)
			for (int j=0; j<4; ++j)
				if (i%2==0) {
					if (j%2==0)		recs[i*4 + j].set_fill_color(Color::white);
					else			recs[i*4 + j].set_fill_color(Color::black);
				}
					
				else {
					if (j%2==0)		recs[i*4 + j].set_fill_color(Color::black);
					else			recs[i*4 + j].set_fill_color(Color::white);
				}
		
		redraw();
	}
	
	void Button_shaped_window::next_color(int r)
	{
		//Сбрасываем цвета остальных квадратов на стандартные если они были изменены
		
		//Короткий вариант при котором возможны раздражающие моргания при перерисовке всех объектов
		Color fc = recs[r].fill_color();
		reset_colors();
		recs[r].set_fill_color(fc);
		
		//Вариант без морганий (перерисовываются лишь квадратики с измененной заливкой)
		//Единственная проблема: при нажатии с перетаскивание цвет может не измениться 
		// и оставаться до повторного нажатия на кнопку
		/*for (int i=0; i < recs.size(); ++i)
			if (i != r)
			{
				if ( (i/4)%2 == 0 ) { //чётные строки (0, 2, 4 и т.д.)
					if (i%2 == 0   &&   recs[i].fill_color() != Color::white)
						{ recs[i].set_fill_color(Color::white); recs[i].draw(); }
					else if (i%2 != 0   &&   recs[i].fill_color() != Color::black)
						{ recs[i].set_fill_color(Color::black); recs[i].draw(); }
				}
				
				else {
					if (i%2 == 0   &&   recs[i].fill_color() != Color::black)
						{ recs[i].set_fill_color(Color::black); recs[i].draw(); }
					else if (i%2 != 0   &&   recs[i].fill_color() != Color::white)
						{ recs[i].set_fill_color(Color::white); recs[i].draw(); }
				}
			}*/
		
		if (recs[r].fill_color() == Color::white   ||   recs[r].fill_color() == Color::black)
			recs[r].set_fill_color(Color::red);
		
		else if (recs[r].fill_color() == Color::red)			recs[r].set_fill_color(Color::dark_red);
		else if (recs[r].fill_color() == Color::dark_red)		recs[r].set_fill_color(Color::blue);
		else if (recs[r].fill_color() == Color::blue)			recs[r].set_fill_color(Color::dark_blue);
		else if (recs[r].fill_color() == Color::dark_blue)		recs[r].set_fill_color(Color::green);
		else if (recs[r].fill_color() == Color::green)			recs[r].set_fill_color(Color::dark_green);
		else if (recs[r].fill_color() == Color::dark_green)		recs[r].set_fill_color(Color::yellow);
		else if (recs[r].fill_color() == Color::yellow)			recs[r].set_fill_color(Color::dark_yellow);
		else if (recs[r].fill_color() == Color::dark_yellow)	recs[r].set_fill_color(Color::magenta);
		else if (recs[r].fill_color() == Color::magenta)		recs[r].set_fill_color(Color::dark_magenta);
		else if (recs[r].fill_color() == Color::dark_magenta)	recs[r].set_fill_color(Color::cyan);
		else if (recs[r].fill_color() == Color::cyan)			recs[r].set_fill_color(Color::dark_cyan);
		
		else if (recs[r].fill_color() == Color::dark_cyan) {
			if ( (r/4)%2 == 0 ) { //чётные строки (0, 2, 4 и т.д.)
				if (r%2 == 0)	recs[r].set_fill_color(Color::white);
				else			recs[r].set_fill_color(Color::black);
			}
			
			else {
				if (r%2 == 0)	recs[r].set_fill_color(Color::black);
				else			recs[r].set_fill_color(Color::white);
			}
		}
	}
}