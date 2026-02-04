
#define _USE_MATH_DEFINES


#include "addition_intermediate_version.h"


namespace addition_intermediate_version {
	//На вход:	ширина и высота будущего окна
	//Возврат:	координаты левой верхней точки окна для отображения окна ровно по центру
	Point win_centering (int w, int h)
	{
		return Point {x_max()/2 - w/2,  y_max()/2 - h/2};
	}
	
	bool operator==(Color a, Color b) { return a.as_int()==b.as_int(); }
	bool operator!=(Color a, Color b) { return !(a==b); }
	
	//Оператор вывода для класса Point
	ostream& operator<<(ostream& ost, const Point& p) {
		ost << "(" << p.x << ";" << p.y << ")";
		return ost;
	}
	
	//Оператор вывода для класса Color
	ostream& operator<<(ostream& ost, const Color& c) {
		string str;
		switch (c.as_int()) {
			case FL_RED:			str = "red";			break;
			case FL_BLUE:			str = "blue";			break;
			case FL_GREEN:			str = "green";			break;
			case FL_YELLOW:			str = "yellow";			break;
			case FL_WHITE:			str = "white";			break;
			case FL_BLACK:			str = "black";			break;
			case FL_MAGENTA:		str = "magenta";		break;
			case FL_CYAN:			str = "cyan";			break;
			case FL_DARK_RED:		str = "dark_red";		break;
			case FL_DARK_GREEN:		str = "dark_green";		break;
			case FL_DARK_YELLOW:	str = "dark_yellow";	break;
			case FL_DARK_BLUE:		str = "dark_blue";		break;
			case FL_DARK_MAGENTA:	str = "dark_magenta";	break;
			case FL_DARK_CYAN:		str = "dark_cyan";		break;
		}
		
		ost << "color " << str << " | visibility " << int(c.visibility());
		//ost << "color " << c.as_int() << " | visibility " << int(c.visibility());
		return ost;
	}
	
	//Оператор вывода для класса Line_style
	ostream& operator<<(ostream& ost, const Line_style& s) {
		string str;
		switch (s.style()) {
			case FL_SOLID:			str = "solid";		break;
			case FL_DASH:			str = "dash";		break;
			case FL_DOT:			str = "dot";		break;
			case FL_DASHDOT:		str = "dashdot";	break;
			case FL_DASHDOTDOT:		str = "dashdotdot";	break;
		}
		
		ost << "style " << str << " | line width " << s.width();
		//ost << "s.style() " << str << " | line width " << s.width();
		return ost;
	}
	
	//Оператор вывода для класса Font
	ostream& operator<<(ostream& ost, const Graph_lib::Font& f) {
		string str;
		switch (f.as_int()) {
			case FL_HELVETICA:				str = "helvetica";					break;
			case FL_HELVETICA_BOLD:			str = "helvetica_bold";				break;
			case FL_HELVETICA_ITALIC:		str = "helvetica_italic";			break;
			case FL_HELVETICA_BOLD_ITALIC:	str = "helvetica_bold_italic";		break;
			case FL_COURIER:				str = "courier";					break;
			case FL_COURIER_BOLD:			str = "courier_bold";				break;
			case FL_COURIER_ITALIC:			str = "courier_italic";				break;
			case FL_COURIER_BOLD_ITALIC:	str = "courier_bold_italic";		break;
			case FL_TIMES:					str = "times";						break;
			case FL_TIMES_BOLD:				str = "times_bold";					break;
			case FL_TIMES_ITALIC:			str = "times_italic";				break;
			case FL_TIMES_BOLD_ITALIC:		str = "times_bold_italic";			break;
			case FL_SYMBOL:					str = "symbol";						break;
			case FL_SCREEN:					str = "screen";						break;
			case FL_SCREEN_BOLD:			str = "screen_bold";				break;
			case FL_ZAPF_DINGBATS:			str = "zapf_dingbats";				break;
		}
		
		ost << str;
		//ost << f.as_int();
		return ost;
	}
	
	//------------------------------------------------------------------------------
	
	Binary_tree::Binary_tree(Point p, int lvl) : root_c{p}, levels{lvl} {
		if (lvl<0)		error("negative levels value");
		add( Point{root_c.x-r, root_c.y-r} );	//Верхний левый угол квадрата описанного вокруг круга
		grow();
	}
	
	Binary_tree::Binary_tree(Point p, int lvl, string str) : root_c{p}, levels{lvl}, direction{str} {
		if (lvl<0)		error("negative levels value");
		if ( str != up  &&  str != down )
			error("bad value of Binary_tree arrow direction(" + str +")");
		add( Point{root_c.x-r, root_c.y-r} );	//Верхний левый угол квадрата описанного вокруг круга
		grow();
	}
	
	Binary_tree::Binary_tree(Point p, int lvl, string str, Color col) : root_c{p}, levels{lvl}, direction{str}, lc{col} {
		if (lvl<0)		error("negative levels value");
		if ( str != up  &&  str != down )
			error("bad value of Binary_tree arrow direction(" + str +")");
		add( Point{root_c.x-r, root_c.y-r} );	//Верхний левый угол квадрата описанного вокруг круга
		grow();
	}
	
	//Заполнение вектора фигур Circle
	void Binary_tree::grow() {
		if (levels<=0)		return;
		
		set_style( Line_style(Line_style::solid, 2) );
		
		//Самый верхний круг (корень) дерева
		c.push_back(new Circle {root_c, r});
		
		int cx = 2.5*r;		//Расстояние между центрами кружков на самом нижнем уровне дерева
		//Вычисление расстояния между центрами кружков на 2ом уровне
		for (int i=1; i < levels; ++i)
			cx *= 2;
		
		
		//Добавление последующих ветвей
		for (int i=1; i < levels; ++i)					//степени двойки
		{
			cx /= 2;
			int start_x = c[ c.size() - pow(2,i-1) ].point(0).x+r - cx/2;	//левее центра первого слева кружка на пред. уровне
			
			for (int j=0; j < pow(2,i); ++j)			//кол-во кружков на уровне с поряд.номером i+1
			{
				Point cntr {start_x + cx*j,   root_c.y + (8*r)*i};
				c.push_back(new Circle {cntr, r});
			}
		}
	}
	
	void Binary_tree::draw_lines() const {
		if (levels<=0)		return;
		
		//Обеспечивает работу ф-ции Shape::set_fill_color()
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			for (unsigned int i=1; i<c.size(); ++i)
				fl_pie(c[i].point(0).x, c[i].point(0).y,  r+r-1, r+r-1,  0, 360);
			
			fl_pie(point(0).x,point(0).y,r+r-1,r+r-1,0,360);
		}
		
		if (color().visibility()) {
			Group l;				//lines
			
			unsigned int N {0}; //кол-во меток на всех пред. уровнях
			for (int i=1; i < levels; ++i) {				//степени двойки
				N += pow(2,i-1);
				
				for (int j=0; j < pow(2,i); j+=2)			//кол-во кружков на уровне с поряд.номером i+1
				{
					//Родительсая метка для следующей пары меток
					Point prnt { s(c[ N + j/2 - pow(2,i-1) ]).x, s(c[ N + j/2 - pow(2,i-1) ]).y };
					
					for (int k=0; k < 2; ++k) {				//пары   кружков
						if ( direction.size() == 0 )
							l.add_shape(new Line  { prnt,   n(c[N+j+k]) });
						else if ( direction == up )
							l.add_shape(new Arrow { n(c[N+j+k]),   prnt });
						else if ( direction == down )
							l.add_shape(new Arrow { prnt,   n(c[N+j+k]) });
						
						l[l.size()-1].set_color( lc );	//Обеспечивает работу ф-ций Binary_tree::set_arrow_color()
					}
				}
			}
			l.draw_lines();
			
			//Обеспечивает работу ф-ций Shape::set_color()  И  Shape::set_style()
			for (unsigned int i=0; i<c.size(); ++i) {
				Circle shape_c {c[i].center(), r};
				shape_c.set_color( color().as_int() );
				shape_c.set_style( style() );
				shape_c.draw();
			}
		}
	}
	
	//------------------------------------------------------------------------------
	
	Binary_txt_tree::Binary_txt_tree(Point p, int lvl) {
		if (lvl<0)		error("negative levels value");
		root_c.x = p.x;
		root_c.y = p.y;
		levels = lvl;
		add( Point{root_c.x-w/2, root_c.y-h/2} );	//Верхний левый угол прямоугольника со скруглёнными углами
		grow();
	}
	
	Binary_txt_tree::Binary_txt_tree(Point p, int lvl, string str) {
		if (lvl<0)		error("negative levels value");
		if ( str != up  &&  str != down )
			error("bad value of Binary_tree arrow direction(" + str +")");
		root_c.x = p.x;
		root_c.y = p.y;
		levels = lvl;
		direction = str;
		add( Point{root_c.x-w/2, root_c.y-h/2} );	//Верхний левый угол прямоугольника со скруглёнными углами
		grow();
	}
	
	Binary_txt_tree::Binary_txt_tree(Point p, int lvl, string str, Color col) {
		if (lvl<0)		error("negative levels value");
		if ( str != up  &&  str != down )
			error("bad value of Binary_tree arrow direction(" + str +")");
		root_c.x = p.x;
		root_c.y = p.y;
		levels = lvl;
		direction = str;
		lc = col;
		add( Point{root_c.x-w/2, root_c.y-h/2} );	//Верхний левый угол прямоугольника со скруглёнными углами
		grow();
	}
	
	//Заполнение вектора фигур TXTBox
	void Binary_txt_tree::grow() {
		if (levels<=0)		return;
		
		set_style( Line_style(Line_style::solid, 2) );
		
		//Самый верхний TXTBox (корень) дерева
		t.push_back(new TXTBox {point(0), w, h, 5, "1"});
		
		int tx = w + w/2;		//Расстояние между верхними левыми углами TXTBox'ов
		//Вычисление расстояния между левыми углами TXTBox'ов на 2ом уровне
		for (int i=1; i < levels; ++i)
			tx *= 2;
		
		
		//Добавление последующих ветвей
		for (int i=1; i < levels; ++i)					//степени двойки
		{
			tx /= 2;
			int start_x = t[ t.size() - pow(2,i-1) ].point(0).x - tx/2; //левее первого слева TXTBox'а на пред. уровне
			
			for (int j=0; j < pow(2,i); ++j)			//кол-во TXTBox'ов на уровне с поряд.номером i+1
			{
				Point new_p {start_x + tx*j,   point(0).y + (8*r)*i};
				t.push_back(new TXTBox {new_p, w, h, 5, to_string(t.size()+1)});
			}
		}
	}
	
	void Binary_txt_tree::draw_lines() const {
		if (levels<=0)		return;
		
		//Обеспечивает работу ф-ции Shape::set_fill_color()
		if (fill_color().visibility())
			for (unsigned int i=0; i<t.size(); ++i) {
				TXTBox shape_t {t[i].point(0), w, h, 5, to_string("\n")};	//пустой текст
				shape_t.set_color( Color(Color::black, Color::invisible) );	//невидимая рамка
				shape_t.set_fill_color( fill_color().as_int() );			//только заполнение
				shape_t.draw();
			}
		
		if (color().visibility()) {
			Group l;				//lines
			
			unsigned int N {0}; //кол-во меток на всех пред. уровнях
			for (int i=1; i < levels; ++i) {				//степени двойки
				N += pow(2,i-1);
				
				for (int j=0; j < pow(2,i); j+=2)			//кол-во меток на уровне с поряд.номером i+1
				{
					//Родительсая метка для следующей пары меток
					Point prnt { s(t[ N + j/2 - pow(2,i-1) ]).x, s(t[ N + j/2 - pow(2,i-1) ]).y };
					
					for (int k=0; k < 2; ++k) {				//пары   кружков
						if ( direction.size() == 0 )
							l.add_shape(new Line  { prnt,   n(t[N+j+k]) });
						else if ( direction == up )
							l.add_shape(new Arrow { n(t[N+j+k]),   prnt });
						else if ( direction == down )
							l.add_shape(new Arrow { prnt,   n(t[N+j+k]) });
						
						l[l.size()-1].set_color( lc );	//Обеспечивает работу ф-ций Binary_tree::set_arrow_color()
					}
				}
			}
			l.draw_lines();
			
			//Обеспечивает работу ф-ций Shape::set_color()  И  Shape::set_style()
			for (unsigned int i=0; i<t.size(); ++i) {
				TXTBox shape_t {t[i].point(0), w, h, 5, t[i].label()};
				shape_t.set_color( color().as_int() );
				shape_t.set_style( style() );
				shape_t.draw();
			}
		}
	}
	
	//------------------------------------------------------------------------------
	
	void chess_board::draw_board() {
		Point& p = board_start;
		int cell {side_len/8};
		
		for (int i=0; i<8; ++i)
			for (int j=0; j<8; ++j) {
				add_shape(new Graph_lib::Rectangle{Point{p.x + j*cell, p.y + i*cell}, cell, cell});
				int indx = size()-1;
				operator[](indx).set_color(Color::black);
				
				if (i%2==0) {
					if (j%2==0)     operator[](indx).set_fill_color(Color::white);
					else            operator[](indx).set_fill_color(Color::black);
				}
					
				else {
					if (j%2==0)     operator[](indx).set_fill_color(Color::black);
					else            operator[](indx).set_fill_color(Color::white);
				}
			}
	}
	
	
	void checkers_canva::draw_board() {
		int r { (cb.board_side()/8 - 4)/2 };	//радиус
		
		for (int cell=0; cell<64; ++cell)
			if ( (cell<24 || 39<cell)  &&  cb[cell].fill_color()==Color::black ) {
				checkers.push_back(new Circle{Point{cb[cell].point(0).x+(cb.board_side()/8)/2, cb[cell].point(0).y+(cb.board_side()/8)/2}, r});
				checkers[checkers.size()-1].set_color(Color::red);
				
				if (cell<24)
					checkers[checkers.size()-1].set_fill_color(Color::white);
				
				else
					checkers[checkers.size()-1].set_fill_color(Color::dark_cyan); //black
			}
	}
	
	//Движение на северо-запад
	void checkers_canva::white_move_nw(int i) {
		if (i>11)
			error("to move black checkers, use a similar function with the word 'black' in the title");
		
		if ( checkers[i].point(0).x-cb.board_side()/8 < cb[0].point(0).x  ||  checkers[i].point(0).y-cb.board_side()/8 < cb[0].point(0).y )
			error("can't move checkers off the board");
		
		checkers[i].move(-cb.board_side()/8, -cb.board_side()/8);
	}
	void checkers_canva::black_move_nw(int i) {
		if (i<12)
			error("to move white checkers, use a similar function with the word 'white' in the title");
		
		if ( checkers[i].point(0).x-cb.board_side()/8 < cb[0].point(0).x  ||  checkers[i].point(0).y-cb.board_side()/8 < cb[0].point(0).y )
			error("can't move checkers off the board");
		
		checkers[i].move(-cb.board_side()/8, -cb.board_side()/8);
	}
	
	//Движение на северо-восток
	void checkers_canva::white_move_ne(int i) {
		if (i>11)
			error("to move black checkers, use a similar function with the word 'black' in the title");
		
		if ( checkers[i].point(0).x+cb.board_side()/8 > cb[0].point(0).x+cb.board_side()  ||  checkers[i].point(0).y-cb.board_side()/8 < cb[0].point(0).y )
			error("can't move checkers off the board");
		
		checkers[i].move(cb.board_side()/8, -cb.board_side()/8);
	}
	void checkers_canva::black_move_ne(int i) {
		if (i<12)
			error("to move white checkers, use a similar function with the word 'white' in the title");
		
		if ( checkers[i].point(0).x+cb.board_side()/8 > cb[0].point(0).x+cb.board_side()  ||  checkers[i].point(0).y-cb.board_side()/8 < cb[0].point(0).y )
			error("can't move checkers off the board");
		
		checkers[i].move(cb.board_side()/8, -cb.board_side()/8);
	}
	
	//Движение на юго-запад
	void checkers_canva::white_move_sw(int i) {
		if (i>11)
			error("to move black checkers, use a similar function with the word 'black' in the title");
		
		if ( checkers[i].point(0).x-cb.board_side()/8 < cb[0].point(0).x  ||  checkers[i].point(0).y+cb.board_side()/8 > cb[0].point(0).y+cb.board_side() )
			error("can't move checkers off the board");
		
		checkers[i].move(-cb.board_side()/8, cb.board_side()/8);
	}
	void checkers_canva::black_move_sw(int i) {
		if (i<12)
			error("to move white checkers, use a similar function with the word 'white' in the title");
		
		if ( checkers[i].point(0).x-cb.board_side()/8 < cb[0].point(0).x  ||  checkers[i].point(0).y+cb.board_side()/8 > cb[0].point(0).y+cb.board_side() )
			error("can't move checkers off the board");
		
		checkers[i].move(-cb.board_side()/8, cb.board_side()/8);
	}
	
	//Движение на юго-восток
	void checkers_canva::white_move_se(int i) {
		if (i>11)
			error("to move black checkers, use a similar function with the word 'black' in the title");
		
		if ( checkers[i].point(0).x+cb.board_side()/8 > cb[0].point(0).x+cb.board_side()  ||  checkers[i].point(0).y+cb.board_side()/8 > cb[0].point(0).y+cb.board_side() )
			error("can't move checkers off the board");
		
		checkers[i].move(cb.board_side()/8, cb.board_side()/8);
	}
	void checkers_canva::black_move_se(int i) {
		if (i<12)
			error("to move white checkers, use a similar function with the word 'white' in the title");
		
		if ( checkers[i].point(0).x+cb.board_side()/8 > cb[0].point(0).x+cb.board_side()  ||  checkers[i].point(0).y+cb.board_side()/8 > cb[0].point(0).y+cb.board_side() )
			error("can't move checkers off the board");
		
		checkers[i].move(cb.board_side()/8, cb.board_side()/8);
	}
	
	//------------------------------------------------------------------------------
	
	//сортировка вектора с точками по значению Y
	void point_sort(vector<Point>& pnts, char ch) {
		if (ch != 'x'  &&  ch != 'y')		error("sorting should be done either by value 'x' or by value 'y'");
		
		vector<int> xy;
		vector<Point> new_pnts;
		
		for (Point p : pnts)
		{
			int curr_xy;
			if (ch == 'x')		curr_xy = p.x;
			else				curr_xy = p.y;
			
			bool repeat_xy {false}; //поиск повторов в векторе
			
			for (int x : xy)
				if (x == curr_xy  &&  pnts.size()%2 != 0)	repeat_xy = true;
			
			if (!repeat_xy)		xy.push_back(curr_xy);
		}
		
		sort(xy.begin(), xy.end());
		
		for (int x : xy)
			for (Point p : pnts)
			{
				int curr_xy;
				if (ch == 'x')		curr_xy = p.x;
				else				curr_xy = p.y;
				
				if (x == curr_xy)	{ new_pnts.push_back(p);	break; }
			}
		
		pnts.clear();
		for (Point p : new_pnts)
			pnts.push_back(p);
	}
	
	
	void Striped_closed_polyline::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			
			//Поиск крайних точек фигуры обозначающих её границы
			int x_min {point(0).x};
			int y_min {point(0).x};
			int x_max {point(0).x};
			int y_max {point(0).x};
			for (int i=0; i < number_of_points(); ++i) {
				if ( x_min > point(i).x )		x_min = point(i).x;
				if ( y_min > point(i).y )		y_min = point(i).y;
				if ( x_max < point(i).x )		x_max = point(i).x;
				if ( y_max < point(i).y )		y_max = point(i).y;
			}
			
			//------------------------------------------------------------------------------
			
			if ( o == vertical )
			{
				for (int x=x_min+2;   x < x_max;   x+=2) {
					vector<Point> fill_lines_pnts; //точки пересечения со сквозной линией на данном значении 'x'
					
					//проверка пересечения свкозной линии с одной из линий фигуры
					for (int i=0;  i < number_of_points(); ++i)
					{
						Point one_intersect;
						int next_x, next_y;
						
						if (i==number_of_points()-1)	{ next_x =  point(0).x;			next_y =  point(0).y;  }
						else							{ next_x = point(i+1).x;		next_y = point(i+1).y; } 
						
						//Если есть пересечение - запоминаем данную точку
						if ( line_segment_intersect(Point{x, y_min-10}, Point{x, y_max+10},   point(i), Point{next_x, next_y},   one_intersect) )
							fill_lines_pnts.push_back(one_intersect);
					}
					
					//сортировка вектора точек по значению 'y'
					point_sort(fill_lines_pnts, 'y');
					
					for (int i=1;  i < fill_lines_pnts.size(); i+=2)
						fl_line(fill_lines_pnts[i-1].x, fill_lines_pnts[i-1].y, fill_lines_pnts[i].x, fill_lines_pnts[i].y);
				}
			}
			
			else if ( o == horisontal )
			{
				for (int y=y_min+2;   y < y_max;   y+=2) {
					vector<Point> fill_lines_pnts; //точки пересечения со сквозной линией на данном значении 'y'
					
					for (int i=0;  i < number_of_points(); ++i)
					{
						Point one_intersect;
						int next_x, next_y;
						
						if (i==number_of_points()-1)	{ next_x =  point(0).x;			next_y =  point(0).y;  }
						else							{ next_x = point(i+1).x;		next_y = point(i+1).y; } 
						
						//Если есть пересечение
						if ( line_segment_intersect(Point{x_min-10, y}, Point{x_max+10, y},   point(i), Point{next_x, next_y},   one_intersect) )
							fill_lines_pnts.push_back(one_intersect);
					}
					
					point_sort(fill_lines_pnts, 'x');
					
					for (int i=1;  i < fill_lines_pnts.size(); i+=2)
						fl_line(fill_lines_pnts[i-1].x, fill_lines_pnts[i-1].y, fill_lines_pnts[i].x, fill_lines_pnts[i].y);
				}
			}
			
			/*fl_color(Color::red);
			fl_line(150, y_min-50, 150, y_max+50);
			fl_line(260, y_min-50, 260, y_max+50);*/
			
			fl_color(color().as_int());	// reset color
		}
		
		if (color().visibility()) {	// draw closing line:
			Shape::draw_lines();
			fl_line(point(number_of_points()-1).x, point(number_of_points()-1).y, point(0).x, point(0).y);
		}
	}
	
	//------------------------------------------------------------------------------
	
	void Striped_circle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			
			/*
			if ( o == vertical ) {
				Point b {center().x - radius(), center().y};
				Point e {center().x + radius(), center().y};
				int ux {b.x};
				int uy {b.y};
				int dx {b.x};
				int dy {b.y};
			
				while (true) {
					for (int a = 180; a > 0; --a) {
						Point u {point_on_circle(center(), radius(), a)};
						
						if ( ux == u.x ) {
							ux = u.x;
							if ( uy == u.y )	uy = uy-1;
							else				uy = u.y;
							break;
						}
					}
					
					
					for (int a = 180; a < 360; ++a) {
						Point d {point_on_circle(center(), radius(), a)};
						
						if ( dx == d.x ) {
							dx = d.x;
							if ( dy == d.y )	dy = dy+1;
							else				dy = d.y;
							break;
						}
					}
					
					if ( ux>=e.x )		break;
					else				fl_line(ux, uy, dx, dy);
					
					ux += 2;
					dx += 2;
				}
			}
			
			else if ( o == horisontal ) {
				Point b {center().x, center().y - radius()};
				Point e {center().x, center().y + radius()};
				int lx {b.x};
				int ly {b.y};
				int rx {b.x};
				int ry {b.y};
			
				while (true) {
					for (int a = 90; a < 270; ++a) {
						Point l {point_on_circle(center(), radius(), a)};
						
						if ( ly == l.y ) {
							ly = l.y;
							if ( lx == l.x )	lx = lx-1;
							else				lx = l.x;
							break;
						}
					}
					
					
					for (int a = 90; a > -90; --a) {
						Point r {point_on_circle(center(), radius(), a)};
						
						if ( ry == r.y ) {
							ry = r.y;
							if ( rx == r.x )	rx = rx+1;
							else				rx = r.x;
							break;
						}
					}
					
					if ( ly>=e.y )		break;
					else				fl_line(lx, ly, rx, ry);
					
					ly += 2;
					ry += 2;
				}
			}
			*/
			
			
			if ( o == vertical )
				for (int i = center().x-radius(); i<center().x+radius(); i+=2) {
					int dx = center().x - i;
					int dy = round( sqrt(pow(radius(), 2) - pow(dx, 2)) ) - 1;
					//Координаты точки на окружности с центром в начале координат: x^2 + y^2 = R^2
					fl_line(i, center().y-dy, i, center().y+dy);
				}
			
			else if ( o == horisontal ) 
				for (int i = center().y-radius(); i<center().y+radius(); i+=2) {
					int dy = center().y - i;
					int dx = round( sqrt(pow(radius(), 2) - pow(dy, 2)) ) - 1;
					//Координаты точки на окружности с центром в начале координат: x^2 + y^2 = R^2
					fl_line(center().x-dx, i, center().x+dx, i);
				}
			
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y,  radius()*2, radius()*2,  0, 360);
		}
	}
	
	//------------------------------------------------------------------------------
	
	void Striped_rectangle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			
			if ( o == vertical )
				for (int i = 2;   point(0).x + i < point(0).x + width();   i+=2)
					fl_line(point(0).x + i, point(0).y,		point(0).x + i, point(0).y+height()-1);
			
			else if ( o == horisontal )
				for (int i = 2;   point(0).y + i < point(0).y + height();   i+=2)
					fl_line(point(0).x, point(0).y + i,		point(0).x+width()-1, point(0).y + i);
			
			else if ( o == right_diagonal )
			{
				int ux = point(0).x;
				int uy = point(0).y;
				
				int dx = point(0).x;
				int dy = point(0).y;
				
				while (true) {
					if ( ux+3 > point(0).x+width() )	{ ux = point(0).x+width()-1;		uy += 3; }
					else								ux += 3;
					
					if ( dy+3 > point(0).y+height() )	{ dy = point(0).y+height()-1;		dx += 3; }
					else								dy += 3;
					
					if ( uy >= point(0).y+height()   &&   dx >= point(0).x+width() )	break;
					
					fl_line(ux, uy, dx, dy);
				}
			}
			
			else if ( o == left_diagonal )
			{
				int ux = point(0).x;
				int uy = point(0).y + height() - 1;
				
				int dx = point(0).x + 3;
				int dy = point(0).y + height() - 1;
				
				while (true) {
					if ( uy-3 < point(0).y )	{ uy = point(0).y;		ux += 3; }
					else						uy -= 3;
					
					if ( dx+3 > point(0).x+width() )	{ dx = point(0).x+width()-1;		dy -= 3; }
					else								dx += 3;
					
					if ( ux >= point(0).x+width()   &&   dy <= point(0).y )		break;
					
					fl_line(ux, uy, dx, dy);
				}
			}
			
			
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, width(), height());
		}
	}
	
	//------------------------------------------------------------------------------
	
	void Smiley::draw_lines() const {
		Circle::draw_lines();
		
		if (color().visibility())
		{
			fl_color(Color::black);
			
			int w { radius()/5 };
			int h { int( radius()/2.7 ) };
			
			Point eye1 { center().x - radius()/2,		center().y - radius()/2 };
			fl_pie(eye1.x, eye1.y,   w, h,   0, 360);
			
			Point eye2 { center().x + radius()/2 - w,	center().y - radius()/2 };
			fl_pie(eye2.x, eye2.y,   w, h,   0, 360);
			
			Point mouth { center().x - radius()/2,		center().y - radius()/3 };
			fl_arc(mouth.x, mouth.y,   radius(), radius(),   180+30, 360-30);
			fl_arc(mouth.x, mouth.y-1,   radius(), radius(),   180+32, 360-28);
			fl_arc(mouth.x, mouth.y-2,   radius(), radius(),   180+34, 360-26);
		}
	}
	
	void Smiley_chinese::draw_lines() const {
		Smiley::draw_lines();
		
		if (color().visibility())
		{
			//point_on_circle(Point c, int r, int angle)
			Point l140	{ point_on_circle(center(), radius(), 140).x - radius()/10,		point_on_circle(center(), radius(), 140).y };
			Point l40	{ point_on_circle(center(), radius(),  40).x + radius()/10,		point_on_circle(center(), radius(), 40).y };
			Point l90	{ center().x,	point_on_circle(center(), radius(), 90).y - radius()/4 };
			
			fl_color(Color::dark_yellow);
			fl_begin_complex_polygon();
			fl_vertex(l90.x, l90.y);
			fl_vertex(l140.x, l140.y);
			fl_vertex(l40.x, l40.y);
			fl_end_complex_polygon();
			
			fl_color(Color::black);
			fl_line(l90.x, l90.y,		l140.x, l140.y);
			fl_line(l140.x, l140.y,		l40.x, l40.y);
			fl_line(l40.x, l40.y,		l90.x, l90.y);
		}
	}
	
	void Smiley_bowler::draw_lines() const {
		Smiley::draw_lines();
		
		if (color().visibility())
		{
			//point_on_circle(Point c, int r, int angle)
			Point l125	{ point_on_circle(center(), radius(), 125).x - radius()/10,		point_on_circle(center(), radius(), 125).y };
			Point l55	{ point_on_circle(center(), radius(),  55).x + radius()/10,		point_on_circle(center(), radius(), 55).y };
			Point l90	{ center().x,	point_on_circle(center(), radius(), 90).y - radius()/4 };
			
			fl_color(Color::black);
			fl_begin_complex_polygon();
			fl_vertex(l125.x+radius()/10, l125.y);
			fl_vertex(l125.x+radius()/10, l125.y-radius());
			fl_vertex( l55.x-radius()/10,  l55.y-radius());
			fl_vertex( l55.x-radius()/10,  l55.y);
			fl_end_complex_polygon();
			
			fl_color(Color::black);
			fl_line(l125.x, l125.y,		l55.x, l55.y);
			fl_line(l125.x+radius()/10, l125.y,				l125.x+radius()/10, l125.y-radius());
			fl_line(l125.x+radius()/10, l125.y-radius(),	 l55.x-radius()/10,  l55.y-radius());
			fl_line( l55.x-radius()/10,  l55.y,				 l55.x-radius()/10,  l55.y-radius());
		}
	}
	
	
	
	void Frowny::draw_lines() const {
		Circle::draw_lines();
		
		if (color().visibility())
		{
			fl_color(Color::black);
			
			int w { radius()/5 };
			int h { int( radius()/2.7 ) };
			
			Point eye1 { center().x - radius()/2,		center().y - radius()/2 };
			fl_pie(eye1.x, eye1.y,   w, h,   0, 360);
			
			Point eye2 { center().x + radius()/2 - w,	center().y - radius()/2 };
			fl_pie(eye2.x, eye2.y,   w, h,   0, 360);
			
			Point mouth { center().x - radius()/2,		center().y + radius()/4 };
			fl_arc(mouth.x, mouth.y,   radius(), radius(),   90-60, 90+60);
			fl_arc(mouth.x, mouth.y+1,   radius(), radius(),   90-58, 90+62);
			fl_arc(mouth.x, mouth.y+2,   radius(), radius(),   90-56, 90+64);
		}
	}
	
	void Frowny_chinese::draw_lines() const {
		Frowny::draw_lines();
		
		if (color().visibility())
		{
			//point_on_circle(Point c, int r, int angle)
			Point l140	{ point_on_circle(center(), radius(), 140).x - radius()/10,		point_on_circle(center(), radius(), 140).y };
			Point l40	{ point_on_circle(center(), radius(),  40).x + radius()/10,		point_on_circle(center(), radius(), 40).y };
			Point l90	{ center().x,	point_on_circle(center(), radius(), 90).y - radius()/4 };
			
			fl_color(Color::dark_yellow);
			fl_begin_complex_polygon();
			fl_vertex(l90.x, l90.y);
			fl_vertex(l140.x, l140.y);
			fl_vertex(l40.x, l40.y);
			fl_end_complex_polygon();
			
			fl_color(Color::black);
			fl_line(l90.x, l90.y,		l140.x, l140.y);
			fl_line(l140.x, l140.y,		l40.x, l40.y);
			fl_line(l40.x, l40.y,		l90.x, l90.y);
		}
	}
	
	void Frowny_bowler::draw_lines() const {
		Frowny::draw_lines();
		
		if (color().visibility())
		{
			//point_on_circle(Point c, int r, int angle)
			Point l125	{ point_on_circle(center(), radius(), 125).x - radius()/10,		point_on_circle(center(), radius(), 125).y };
			Point l55	{ point_on_circle(center(), radius(),  55).x + radius()/10,		point_on_circle(center(), radius(), 55).y };
			Point l90	{ center().x,	point_on_circle(center(), radius(), 90).y - radius()/4 };
			
			fl_color(Color::black);
			fl_begin_complex_polygon();
			fl_vertex(l125.x+radius()/10, l125.y);
			fl_vertex(l125.x+radius()/10-2, l125.y-radius());
			fl_vertex( l55.x-radius()/10+2,  l55.y-radius());
			fl_vertex( l55.x-radius()/10,  l55.y);
			fl_end_complex_polygon();
			
			fl_color(Color::black);
			fl_line(l125.x, l125.y,		l55.x, l55.y);
			fl_line(l125.x+radius()/10, l125.y,				l125.x+radius()/10-2, l125.y-radius());
			fl_line(l125.x+radius()/10, l125.y-radius(),	 l55.x-radius()/10+2,  l55.y-radius());
			fl_line( l55.x-radius()/10,  l55.y,				 l55.x-radius()/10,  l55.y-radius());
		}
	}
	
	//------------------------------------------------------------------------------
	
	// добавление  точек (вершин и впадинок)
	void Star::star_points()
	{
		for (int i = 0; i < n; ++i) {
			//Все углы в равностороннем многоугольнике равны (а внутренние и внешние точки образуют два таковых),
			// и вычисляются по формуле ниже 360.0 / n, где n - кол-во углов (вершин в данном случае)
			//360 градусов == 2*pi в радианах
			double angle {0};
			if ( i < n )		angle = double(i) * (2.0 * M_PI / n) + 90  * M_PI / 180;
			
			//определяем координаты внешней точки
			int x = double(c.x) + R * cos( angle );
			int y = double(c.y) - R * sin( angle );
			add(Point{ x, y });
			
			//определяем координаты внутренней точки
			angle = (angle * 180 / M_PI) + (360 / n) / 2;
			angle = angle * M_PI / 180;
			
			x = double(c.x) + r * cos( angle );
			y = double(c.y) - r * sin( angle );
			add(Point{ x, y });
		}
		
		add( point(0) );
	}
	
	void Star::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for(int i=0; i<number_of_points(); ++i){
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}
		
		if (color().visibility())
			Shape::draw_lines();
	}
	
	//------------------------------------------------------------------------------
	
	//https://e-maxx.ru/algo/segments_intersection_checking
	
	//проверка что граничная точка одной из прямых не является точкой другой прямой
	int area (Point a, Point b, Point c) {
		return	(b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}

	bool intersect_1 (int a, int b, int c, int d) {
		if (a > b)		swap(a, b);
		if (c > d)		swap(c, d);
		
		return		max(a,c) <= min(b,d);
	}

	bool intersect (Point a, Point b, Point c, Point d) {
		return intersect_1 (a.x, b.x, c.x, d.x)		&&
				intersect_1 (a.y, b.y, c.y, d.y)	&&
				area(a,b,c) * area(a,b,d) <= 0		&&
				area(c,d,a) * area(c,d,b) <= 0;
	}
	
	
	bool Poly::check_intersections()
	{
		for (int i = 0; i < fig.size(); ++i)
			for (int j = i+2; j < fig.size(); ++j)
			{
				bool is {false};
				
				if ( j == fig.size()-1  &&  i!=0 )
					is = addition_intermediate_version::intersect(  fig[i], fig[i+1], fig[j],  fig[0]   );
				else if ( j != fig.size()-1 )
					is = addition_intermediate_version::intersect(  fig[i], fig[i+1], fig[j], fig[j+1]  );
				
				if ( is==true ) {
					if ( j == fig.size()-1  &&  i!=0 )
						cerr << fig[i].x << ',' << fig[i].y << ' ' << fig[i+1].x << ',' << fig[i+1].y << '|'
							 << fig[j].x << ',' << fig[j].y << ' ' << fig[ 0 ].x << ',' << fig[ 0 ].y << '\n';
					else
						cerr << fig[i].x << ',' << fig[i].y << ' ' << fig[i+1].x << ',' << fig[i+1].y << '|'
							 << fig[j].x << ',' << fig[j].y << ' ' << fig[j+1].x << ',' << fig[j+1].y << '\n';
					
					return true;
				}
			}
			
		return false;
	}
	
	//------------------------------------------------------------------------------
	
	Right_triangle::Right_triangle(Point p, int c1, int c2) :ra{ p }, l1{ c1 }, l2{ c2 }
	{
		if ( l1<=0  ||  l2<=0 )		error("negative value of the length of one of the legs of a right triangle");
		
		add(p);
		add(Point{p.x+l1, p.y});
		add(Point{p.x, p.y-l2});
	}
	
	//точка треугольника схождения двух катетов под прямым углом, длины катетов и угол поворота
	Right_triangle::Right_triangle(Point p, int c1, int c2, int a) :ra{ p }, l1{ c1 }, l2{ c2 }
	{
		if ( l1<=0  ||  l2<=0 )		error("negative value of the length of one of the legs of a right triangle");
		//if ( a<0 )					error("negative value of rotate angle of a right triangle");
		
		add(p);
		add( point_on_circle(p, l1,   a  ) );
		add( point_on_circle(p, l2, a+90 ) );
	}
	
	//------------------------------------------------------------------------------
	
	//Длина одной из сторон
	int Regular_polygon::side_ln() const {
		double a = pow(point(0).x - point(1).x, 2);
		double b = pow(point(0).y - point(1).y, 2);
		int rs = round( sqrt(a + b) );
		
		return rs;
	}
	
	//Радиус вписанной окружности (середина каждой стороны правильного многоугольника - радиус вписанной и высота из центра на середину любой стороны)
	int Regular_polygon::in_radius() const {
		int sl = side_ln();
		sl /= ( 2.0 * tan(M_PI/n) );
		
		return sl;
	}
	
	//Радиус описанной окружности (все вершины правильного многоугольника - точки окружности)
	int Regular_polygon::out_radius() const {
		int sl = side_ln();
		sl /= ( 2.0 * sin(M_PI/n) );
		
		return sl;
	}
	
	
	void Regular_polygon::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for(int i=0; i<number_of_points(); ++i){
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}
		
		if (color().visibility())
			Shape::draw_lines();
	}
	
	void Regular_polygon::angles()
	{
		for (int i = 0; i <= n; ++i) {
			//Все углы в равностороннем многоугольнике равны, и вычисляются по формуле ниже 360.0 / n, где n - кол-во углов
			//360 градусов == 2*pi в радианах
			double angle {0};
			if ( i < n )		angle = double(i) * (2.0 * M_PI / n);
			
			//определяем координаты
			int x = double(c.x) + r * cos( angle );
			int y = double(c.y) - r * sin( angle );
			
			add(Point{ x, y });
		}
	}
	
	//------------------------------------------------------------------------------
	
	//Добавляет точки для дальнейшего рисования стрелки через Open_polyline::draw_lines()
	//Формирование точек треугольника-указателя стрелки происходит с учётом угла наклона линии стрелки
	void Arrow::arrow_points () {
		Point p1 { point(0) };
		Point p2 { point(1) };
		int r = 10;
		
		double angle { (20.0 * M_PI) / 180.0 }; //Угол поворота лепестков каждой стрелки относительно линии стрелки
		
		//Длина катетов прямоугольного треугольника образованного линией стрелки и двумя перпендикулярами из оконечных точек (p1.x; p2.y  -  на горизонтали с p2)
		double c1 { sqrt( pow(p1.x-p1.x, 2) + pow(p1.y-p2.y, 2) ) };
		double c2 { sqrt( pow(p2.x-p1.x, 2) + pow(p2.y-p2.y, 2) ) };
		
		// наклон стрелки \ или | или __
		if ( p2.x <= p1.x ) {
			double line_angle { atan(c1/c2) };  //Угол линии стрелки к перпендикуляру опущенному от горизонтали пролегающей через p2
			
			/*c1 = line_angle + angle;
			c2 = line_angle - angle;
			cout << "Line angle: " << line_angle * 180.0 / M_PI << '\n' 
				 << c1 * 180.0 / M_PI << '\t' << "cos: " << cos(c1) << '\t' << "sin: " << sin(c1) << '\n'
				 << c2 * 180.0 / M_PI << '\t' << "cos: " << cos(c2) << '\t' << "sin: " << sin(c2) << "\n\n";*/
			
			int x = round( double(p2.x) + r * cos(line_angle + angle) ); //точка на окружности
			int y = round( double(p2.y) + r * sin(line_angle + angle) );
			if ( p2.y > p1.y )		y -= 2 * r * sin(line_angle + angle); //если стрелка направлена вниз
			
			add(Point{ x, y });
			
			
			x = round( double(p2.x) + r * cos(line_angle - angle) ); //точка на окружности
			y = round( double(p2.y) + r * sin(line_angle - angle) );
			if ( p2.y > p1.y )		y -= 2 * r * sin(line_angle - angle); //если стрелка направлена вниз
			
			add(Point{ x, y });
		}
		
		// наклон стрелки /
		else {
			double line_angle { atan(c2/c1) };  //Угол линии стрелки к горизонтали пролегающей через p2
			
			/*c1 = (3 * M_PI) / 2 - line_angle - angle;
			c2 = (3 * M_PI) / 2 - line_angle - angle + 2*angle;
			cout << "Line angle: " << line_angle * 180.0 / M_PI << '\n' 
				 << c1 * 180.0 / M_PI << '\t' << "cos: " << cos(c1) << '\t' << "sin: " << sin(c1) << '\n'
				 << c2 * 180.0 / M_PI << '\t' << "cos: " << cos(c2) << '\t' << "sin: " << sin(c2) << "\n\n";*/
			
			int x = round( double(p2.x) + r * cos((3 * M_PI) / 2 - line_angle - angle) ); //точка на окружности
			int y = round( double(p2.y) - r * sin((3 * M_PI) / 2 - line_angle - angle) );
			if ( p2.y > p1.y )		y += 2 * r * sin((3 * M_PI) / 2 - line_angle - angle); //если стрелка направлена вниз
			
			add(Point{ x, y });
			
			
			x = round( double(p2.x) + r * cos((3 * M_PI) / 2 - (line_angle - angle)) ); //точка на окружности
			y = round( double(p2.y) - r * sin((3 * M_PI) / 2 - (line_angle - angle)) );
			if ( p2.y > p1.y )		y += 2 * r * sin((3 * M_PI) / 2 - (line_angle - angle)); //если стрелка направлена вниз
			
			add(Point{ x, y });
		}
		
		
		add(p2);
	}
	
	//Рисует заливку треугольника-указателя (стороны и заливка одинакового цвета)
	void Arrow::draw_lines () const {
		fl_color(color().as_int());
		fl_begin_complex_polygon();
		for(int i=2; i<5; ++i){
		   fl_vertex(point(i).x, point(i).y);
		}
		fl_end_complex_polygon();
		fl_color(color().as_int());		// перезаливка цветом
		
		Shape::draw_lines();
	}
	
	//------------------------------------------------------------------------------
	
	// Центр, min, max дистанция от центра (радиусы) и начальный и конечный угол рисования части элипса
	Arc::Arc(Point p, int ww, int hh, double begin, double end)
		:w{ ww }, h{ hh }, begin_angle{int(begin)}, end_angle{int(end)}
	{
		if (begin == end)
			error("equal angles");
		
		if (begin < -360  ||  360 < begin) {
			cerr << "\n\nFirst angle (begin) value: " << begin << " - is out of range [-360; 360] (pArc initialisation)\n"
				 << "The angle will be truncated to a value in the given range: begin = " << (int(begin) % 360);
			begin_angle = int(begin) % 360;
		}
		
		if (end < -360  ||  360 < end) {
			cerr << "\n\nSecond angle (end) value: " << begin << " - is out of range [-360; 360] (pArc initialisation)\n"
				 << "The angle will be truncated to a value in the given range: end = " << int(end) % 360;
			end_angle = int(end) % 360;
		}
		
		add(Point{p.x - ww, p.y - hh});
	}

	void Arc::draw_lines() const
	{
	if (fill_color().visibility()) {	// заливка
		fl_color(fill_color().as_int());
		fl_pie(point(0).x,point(0).y,w+w-1,h+h-1,begin_angle,end_angle);
		fl_color(color().as_int());		// перезаливка цветом
	}

	if (color().visibility()) {
		fl_color(color().as_int());
		fl_arc(point(0).x,point(0).y,w+w,h+h,begin_angle,end_angle);
	}
}

	void Arc::set_angles(double begin, double end)
	{
		if (begin == end)
			error("equal angles");
		
		if (begin < -360  ||  360 < begin) {
			cerr << "\n\nFirst angle (begin) value: " << begin << " - is out of range [-360; 360] (pArc::set_angles)\n"
				 << "The angle will be truncated to a value in the given range: begin = " << (int(begin) % 360);
			begin = int(begin) % 360;
		}
		
		if (end < -360  ||  360 < end) {
			cerr << "\n\nSecond angle (end) value: " << end << " - is out of range [-360; 360] (pArc::set_angles)\n"
				 << "The angle will be truncated to a value in the given range: end = " << int(end) % 360;
			end = int(end) % 360;
		}
			
		begin_angle = int(begin);
		end_angle = int(end);
	}
	
	//------------------------------------------------------------------------------
	
	//Рисует прямоугольник с закруглёнными углами
	void Box::draw_lines() const
	{
		if (fill_color().visibility()) {	// заливка
			fl_color(fill_color().as_int());
			
			fl_rectf(point(0).x + r, point(0).y,     w-2*r, h);
			fl_rectf(point(0).x,     point(0).y + r, w,     h-2*r);
			
			fl_pie(point(0).x,           point(0).y,           r+r-1, r+r-1,  90, 180);		//дуга левый верхний угол
			fl_pie(point(0).x + w - 2*r, point(0).y,           r+r-1, r+r-1,  0,  90);		//дуга правый верхний угол
			fl_pie(point(0).x + w - 2*r, point(0).y + h - 2*r, r+r-1, r+r-1, 270, 360);		//дуга правый нижний угол
			fl_pie(point(0).x,           point(0).y + h - 2*r, r+r-1, r+r-1, 180, 270);		//дуга левый нижний угол
			
			fl_color(color().as_int());		// перезаливка цветом
		}

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().as_int());
			
			fl_arc(point(0).x,           point(0).y,           r+r, r+r,  90, 180);		//дуга левый верхний угол
			fl_arc(point(0).x + w - 2*r, point(0).y,           r+r, r+r,  0, 90);		//дуга правый верхний угол
			fl_arc(point(0).x + w - 2*r, point(0).y + h - 2*r, r+r, r+r, 270, 360);		//дуга правый нижний угол
			fl_arc(point(0).x,           point(0).y + h - 2*r, r+r, r+r, 180, 270);		//дуга левый нижний угол
			
			
			fl_line(point(0).x + r,     point(0).y,   point(0).x + w - r, point(0).y);			//верхняя грань прямоугольника
			fl_line(point(0).x + w,     point(0).y + r,   point(0).x + w, point(0).y + h - r);	//правая грань прямоугольника
			fl_line(point(0).x + w - r, point(0).y + h,   point(0).x + r, point(0).y + h);		//нижняя грань прямоугольника
			fl_line(point(0).x,         point(0).y + h - r,   point(0).x, point(0).y + r);		//левая грань прямоугольника
		}
	}
	
	//------------------------------------------------------------------------------
	
	//Рисует прямоугольник с закруглёнными углами и помещает в его центр текст
	void TXTBox::draw_lines() const
	{
		Box::draw_lines();
		
		/*int ofnt = fnt.as_int();
		int osz = fnt_sz;
		fl_font(ofnt, osz);
		fl_draw(lbl.c_str(), point(0).x+15, point(0).y+17);
		fl_font(ofnt,osz);*/
		
		int ofnt = fl_font();
		int osz = fl_size();
		fl_font(fnt.as_int(),fnt_sz);
		fl_draw(lbl.c_str(), point(0).x+15, point(0).y+17);
		fl_font(ofnt,osz);
	}
	
	//------------------------------------------------------------------------------
	
	Pseudo_window::Pseudo_window(Point p, int ww, int hh, string str) : 
				win_start{ Point{p.x, p.y+25} },
				txt { Point{p.x+r, p.y+20}, str },
				bwin { Point{p.x, p.y+25}, ww, hh, r }
	{
		if ( ww<=100  ||  hh<=10 )		error("very small window (" + to_string(ww) + "*" + to_string(hh) + ")");
		if ( str == "" )				str = "My_Window";
		
		txt.set_color(Color::black);
		
		bwin.set_color(Color::black);
		bwin.set_fill_color(Color::dark_cyan);
		
		icons.add_shape(new Line {Point{win_start.x+ww-r-55, win_start.y-10},   Point{win_start.x+ww-r-42, win_start.y-10}}); //иконка '_' (свиток/свернуть)
		icons.add_shape(new Line {Point{win_start.x+ww-r-55, win_start.y-11},   Point{win_start.x+ww-r-42, win_start.y-11}});
		
		icons.add_shape(new Graph_lib::Rectangle{Point{win_start.x+ww-r-32, win_start.y-20}, 15, 10}); //иконка '[]' (максимизировать)
		icons.add_shape(new Graph_lib::Rectangle{Point{win_start.x+ww-r-35, win_start.y-15}, 15, 10});
		
		icons.add_shape(new Line {Point{win_start.x+ww-r-11, win_start.y-7},   Point{win_start.x+ww-r-2, win_start.y-17}}); //иконка 'X' (закрыть)
		icons.add_shape(new Line {Point{win_start.x+ww-r-10, win_start.y-7},   Point{win_start.x+ww-r-1, win_start.y-17}});
		icons.add_shape(new Line {Point{win_start.x+ww-r-11, win_start.y-17},   Point{win_start.x+ww-r-2, win_start.y-7}});
		icons.add_shape(new Line {Point{win_start.x+ww-r-10, win_start.y-17},   Point{win_start.x+ww-r-1, win_start.y-7}});
		
		for (int i=0; i < icons.size(); ++i)
			icons[i].set_color(Color::black);
	}
	
	//------------------------------------------------------------------------------
	
	//Север		(середина верхней грани прямоугольника)
	Point n(const Box& b) {
		int x = b.point(0).x + b.width()/2;
		int y = b.point(0).y;
		Point p{x, y};
		return		p;
	}
	
	//Юг		(середина нижней грани прямоугольника)
	Point s(const Box& b) {
		int x = b.point(0).x + b.width()/2;
		int y = b.point(0).y + b.height();
		Point p{x, y};
		return		p;
	}
	
	//Восток	(середина правой грани прямоугольника)
	Point e(const Box& b) {
		int x = b.point(0).x + b.width();
		int y = b.point(0).y + b.height()/2;
		Point p{x, y};
		return		p;
	}
	
	//Запад		(середина правой грани прямоугольника)
	Point w(const Box& b) {
		int x = b.point(0).x;
		int y = b.point(0).y + b.height()/2;
		Point p{x, y};
		return		p;
	}
	
	//Центр		(центр прямоугольника)
	Point center(const Box& b) {
		int x = b.point(0).x + b.width()/2;
		int y = b.point(0).y + b.height()/2;
		Point p{x, y};
		return		p;
	}
	
	//Северо-восток		(верхний правый угол прямоугольника)
	Point ne(const Box& b) {
		Point cntr{b.point(0).x + b.width() - b.radius(), b.point(0).y + b.radius()};
		Circle c {cntr, b.radius()};
		
		return		point_on_circle(c, 45);
	}
	
	//Юго-восток		(нижний правый угол прямоугольника)
	Point se(const Box& b) {
		Point cntr{b.point(0).x + b.width() - b.radius(), b.point(0).y + b.height() - b.radius()};
		Circle c {cntr, b.radius()};
		
		return		point_on_circle(c, 315);
	}
	
	//Юго-запад			(нижний левый угол прямоугольника)
	Point sw(const Box& b) {
		Point cntr{b.point(0).x + b.radius(), b.point(0).y + b.height() - b.radius()};
		Circle c {cntr, b.radius()};
		
		return		point_on_circle(c, 225);
	}
	
	//Северо-восток		(верхний левый угол прямоугольника)
	Point nw(const Box& b) {
		Point cntr{b.point(0).x + b.radius(), b.point(0).y + b.radius()};
		Circle c {cntr, b.radius()};
		
		return		point_on_circle(c, 135);
	}
	
	//------------------------------------------------------------------------------
	
	//Север		(середина верхней грани прямоугольника)
	Point n(const TXTBox& b) {
		int x = b.point(0).x + b.width()/2;
		int y = b.point(0).y;
		Point p{x, y};
		return		p;
	}
	
	//Юг		(середина нижней грани прямоугольника)
	Point s(const TXTBox& b) {
		int x = b.point(0).x + b.width()/2;
		int y = b.point(0).y + b.height();
		Point p{x, y};
		return		p;
	}
	
	//Восток	(середина правой грани прямоугольника)
	Point e(const TXTBox& b) {
		int x = b.point(0).x + b.width();
		int y = b.point(0).y + b.height()/2;
		Point p{x, y};
		return		p;
	}
	
	//Запад		(середина правой грани прямоугольника)
	Point w(const TXTBox& b) {
		int x = b.point(0).x;
		int y = b.point(0).y + b.height()/2;
		Point p{x, y};
		return		p;
	}
	
	//Центр		(центр прямоугольника)
	Point center(const TXTBox& b) {
		int x = b.point(0).x + b.width()/2;
		int y = b.point(0).y + b.height()/2;
		Point p{x, y};
		return		p;
	}
	
	//Северо-восток		(верхний правый угол прямоугольника)
	Point ne(const TXTBox& b) {
		Point cntr{b.point(0).x + b.width() - b.radius(), b.point(0).y + b.radius()};
		Circle c {cntr, b.radius()};
		
		return		point_on_circle(c, 45);
	}
	
	//Юго-восток		(нижний правый угол прямоугольника)
	Point se(const TXTBox& b) {
		Point cntr{b.point(0).x + b.width() - b.radius(), b.point(0).y + b.height() - b.radius()};
		Circle c {cntr, b.radius()};
		
		return		point_on_circle(c, 315);
	}
	
	//Юго-запад			(нижний левый угол прямоугольника)
	Point sw(const TXTBox& b) {
		Point cntr{b.point(0).x + b.radius(), b.point(0).y + b.height() - b.radius()};
		Circle c {cntr, b.radius()};
		
		return		point_on_circle(c, 225);
	}
	
	//Северо-восток		(верхний левый угол прямоугольника)
	Point nw(const TXTBox& b) {
		Point cntr{b.point(0).x + b.radius(), b.point(0).y + b.radius()};
		Circle c {cntr, b.radius()};
		
		return		point_on_circle(c, 135);
	}
	
	//------------------------------------------------------------------------------
	
	//Север		(середина верхней грани прямоугольника)
	Point n(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x + r.width()/2;
		int y = r.point(0).y;
		Point p{x, y};
		return		p;
	}

	//Юг		(середина нижней грани прямоугольника)
	Point s(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x + r.width()/2;
		int y = r.point(0).y + r.height();
		Point p{x, y};
		return		p;
	}

	//Восток	(середина правой грани прямоугольника)
	Point e(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x + r.width();
		int y = r.point(0).y + r.height()/2;
		Point p{x, y};
		return		p;
	}

	//Запад		(середина правой грани прямоугольника)
	Point w(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x;
		int y = r.point(0).y + r.height()/2;
		Point p{x, y};
		return		p;
	}

	//Центр		(центр прямоугольника)
	Point center(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x + r.width()/2;
		int y = r.point(0).y + r.height()/2;
		Point p{x, y};
		return		p;
	}

	//Северо-восток		(верхний правый угол прямоугольника)
	Point ne(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x + r.width();
		int y = r.point(0).y;
		Point p{x, y};
		return		p;
	}

	//Юго-восток		(нижний правый угол прямоугольника)
	Point se(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x + r.width();
		int y = r.point(0).y + r.height();
		Point p{x, y};
		return		p;
	}

	//Юго-запад			(нижний левый угол прямоугольника)
	Point sw(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x;
		int y = r.point(0).y + r.height();
		Point p{x, y};
		return		p;
	}

	//Северо-восток		(верхний левый угол прямоугольника)
	Point nw(const Graph_lib::Rectangle& r) {
		int x = r.point(0).x;
		int y = r.point(0).y;
		Point p{x, y};
		return		p;
	}

	//------------------------------------------------------------------------------
	
	//Точка на окружности по заданным центру, радиусу окружности и углу отклонения точки
	Point point_on_circle(Point c, int r, int angle) {
		if (angle < -360  ||  360 < angle) {
			cerr << "Angle value (" << angle << ") is out of range [-360; 360]."
					" New angle value ANGLE%360:" << angle%360 << '\n';
			
			angle = angle % 360;
		}
		
		int x = round( c.x + r * cos(angle * M_PI / 180.0) ); //обязательно в радианах
		int y = round( c.y - r * sin(angle * M_PI / 180.0) );
		
		return		Point{x, y};
	}
	
	//Точка на окружности по заданному углу
	Point point_on_circle(const Circle& c, int angle) {
		if (angle < -360  ||  360 < angle) {
			cerr << "Angle value (" << angle << ") is out of range [-360; 360]."
					" New angle value ANGLE%360:" << angle%360 << '\n';
			
			angle = angle % 360;
		}
		
		int x = round( c.center().x + c.radius() * cos(angle * M_PI / 180.0) ); //обязательно в радианах
		int y = round( c.center().y - c.radius() * sin(angle * M_PI / 180.0) );
		return		{x, y};
	}

	//Угол наклона линии от центра до точки на окружности
	int point_angle (const Circle& c, const Point& p) {
		int d = round(  sqrt( pow(c.center().x-p.x, 2) + pow(c.center().y-p.y, 2) )  );
		if ( d != c.radius() )		error("the point is not on the boundary of the circle");
		
		if ( p.x == c.center().x )
			return ( p.y > c.center().y ) ? 270 : 90;
		
		else if ( p.y == c.center().y )
			return ( p.x > c.center().x ) ? 0 : 180;
		
		
		//Длина катетов прямоугольного треугольника образованного линией радиуса из центра круга в указанную точку
		double c1 { sqrt( pow(c.center().x-p.x, 2) + pow(c.center().y-c.center().y, 2) ) };
		double c2 { sqrt( pow(p.x-p.x, 2) + pow(p.y-c.center().y, 2) ) };
		
		int a {0};
		
		if ( p.x < c.center().x ) {
			a = round(  atan(c1 / c2) * 180 / M_PI  );
			return ( p.y < c.center().y ) ? 90+a : 270-a;
		}
		
		else if ( p.x > c.center().x ) {
			a = round(  atan(c2 / c1) * 180 / M_PI  );
			return ( p.y > c.center().y ) ? -a : a;
		}
		
		
		return a;
	}


	//Точки пересечения двух окружностей
	vector<Point> circles_intersect (const Circle& c1, const Circle& c2) {
		//http://algolist.ru/maths/geom/intersect/circlecircle2d.php
		vector<Point> intersects;
		
		
		int r1 {c1.radius()};
		Point cntr1 {c1.center()};
		
		int r2 {c2.radius()};
		Point cntr2 {c2.center()};
		
		//расстояние между центрами двух кругов
		double d = sqrt( pow(cntr1.x-cntr2.x, 2) + pow(cntr1.y-cntr2.y, 2) );
		if ( d > r1+r2 )		error("circles do not intersect ( circles_intersect() )"); //либо можно вернуть пустой вектор и проверять уже непосредственно в вызывающем коде
		if ( d < abs(r1-r2) )	error("one circle is inside another and circles do not intersect ( circles_intersect() )");
		
		//часть d от центра первого круга до высоты прямоугольного треугольника (опущенного на линию d перепендикуляра из точки пересечения двух окружностей)
		//Прямоугольный треугольник образуется r1 (из cntr1 в точку пересечения), линией d и высотой опущенной из точки пересечения окружностей на линию d
		//из уравнений прямоугольного треугольника		a^2 + h^2 = r1^2   И   b^2 + h^2 = r2^2
		double a = (r1*r1 - r2*r2 + d*d) / (2*d);
		
		//высота прямоугольного треугольника (^)
		//из уравнения прямоугольного треугольника		a^2 + h^2 = r1^2
		double h = sqrt ( r1*r1 - a*a );
		
		//координаты пересечения d и высоты прямоугольного треугольника (^)
		//P2 = P0 + a ( P1 - P0 ) / d
		double x_hd = cntr1.x + a * (cntr2.x - cntr1.x) / d;
		double y_hd = cntr1.y + a * (cntr2.y - cntr1.y) / d;
		
		
		//x3 = x2 +- h ( y1 - y0 ) / d
		//y3 = y2 -+ h ( x1 - x0 ) / d
		int x1 = round(  x_hd + h * (cntr2.y - cntr1.y) / d  );
		int y1 = round(  y_hd - h * (cntr2.x - cntr1.x) / d  );
		intersects.push_back({x1, y1});
		
		int x2 = round(  x_hd - h * (cntr2.y - cntr1.y) / d  );
		int y2 = round(  y_hd + h * (cntr2.x - cntr1.x) / d  );
		intersects.push_back({x2, y2});
		
		return		intersects;
	}
	
	
	//Север		(на 12 часов - 90 градусов)
	Point n(const Circle& c) {
		return		point_on_circle(c, 90);
	}

	//Юг		(на 6 часов - 270 градусов)
	Point s(const Circle& c) {
		return		point_on_circle(c, 270);
	}

	//Восток	(на 3 часа - 0/360 градусов)
	Point e(const Circle& c) {
		return		point_on_circle(c, 0);
	}

	//Запад		(на 9 часов - 180 градусов)
	Point w(const Circle& c) {
		return		point_on_circle(c, 180);
	}

	//Центр		(центр круга)
	Point center(const Circle& c) {
		return		c.center();
	}

	//Северо-восток		(между 1 и 2 часами - 45 градусов)
	Point ne(const Circle& c) {
		return		point_on_circle(c, 45);
	}

	//Юго-восток		(между 4 и 5 часами - 315 градусов)
	Point se(const Circle& c) {
		return		point_on_circle(c, 315);
	}

	//Юго-запад			(между 7 и 8 часами - 225 градусов)
	Point sw(const Circle& c) {
		return		point_on_circle(c, 225);
	}

	//Северо-восток		(между 10 и 11 часами - 135 градусов)
	Point nw(const Circle& c) {
		return		point_on_circle(c, 135);
	}

	//------------------------------------------------------------------------------

	//На вход ссылка на объект эллипса и значение угла от 0 до 360
	//Расчёт на основе параметрического уравнения эллипса
	Point point_on_ellipse(const Graph_lib::Ellipse& e, int angle) {
		if (angle < -360  ||  360 < angle) {
			cerr << "Angle value (" << angle << ") is out of range [-360; 360]."
					" New angle value ANGLE%360:" << angle%360 << '\n';
			
			angle = angle % 360;
		}
		
		int x = round( e.center().x + e.major() * cos(angle * M_PI / 180.0) ); //обязательно в радианах
		int y = round( e.center().y - e.minor() * sin(angle * M_PI / 180.0) );
		return		{x, y};
	}


	//Север		(на 12 часов - 90 градусов)
	Point n(const Graph_lib::Ellipse& e) {
		return		point_on_ellipse(e, 90);
	}

	//Юг		(на 6 часов - 270 градусов)
	Point s(const Graph_lib::Ellipse& e) {
		return		point_on_ellipse(e, 270);
	}

	//Восток	(на 3 часа - 0/360 градусов)
	Point e(const Graph_lib::Ellipse& e) {
		return		point_on_ellipse(e, 0);
	}

	//Запад		(на 9 часов - 180 градусов)
	Point w(const Graph_lib::Ellipse& e) {
		return		point_on_ellipse(e, 180);
	}

	//Центр		(центр эллипса)
	Point center(const Graph_lib::Ellipse& e) {
		return		e.center();
	}

	//Северо-восток		(между 1 и 2 часами - 45 градусов)
	Point ne(const Graph_lib::Ellipse& e) {
		return		point_on_ellipse(e, 45);
	}

	//Юго-восток		(между 4 и 5 часами - 315 градусов)
	Point se(const Graph_lib::Ellipse& e) {
		return		point_on_ellipse(e, 315);
	}

	//Юго-запад			(между 7 и 8 часами - 225 градусов)
	Point sw(const Graph_lib::Ellipse& e) {
		return		point_on_ellipse(e, 225);
	}

	//Северо-восток		(между 10 и 11 часами - 135 градусов)
	Point nw(const Graph_lib::Ellipse& e) {
		return		point_on_ellipse(e, 135);
	}
};		// namespace  addition_intermediate_version