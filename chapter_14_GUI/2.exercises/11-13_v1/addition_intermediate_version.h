
#define _USE_MATH_DEFINES

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>
#include <math.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

//Поиск точки пересечения двух линий, если есть таковая
//Явное объявление. Сама ф-ция определена в Graph.cpp
namespace Graph_lib {
	bool line_segment_intersect(
		Point p1, Point p2,
		Point p3, Point p4,
		Point& intersection_point);
}

//------------------------------------------------------------------------------

//constexpr double M_PI = 3.141592653589793238462643383;

namespace addition_intermediate_version {
	//На вход:	ширина и высота будущего окна
	//Возврат:	координаты левой верхней точки окна для отображения окна ровно по центру
	Point win_centering (int w, int h);
	
	bool operator==(Color a, Color b);
	bool operator!=(Color a, Color b);
	
	//Оператор вывода для класса Point
	ostream& operator<<(ostream& ost, const Point& p);
	
	//Оператор вывода для класса Color
	ostream& operator<<(ostream& ost, const Color& c);
	
	//Оператор вывода для класса Line_style
	ostream& operator<<(ostream& ost, const Line_style& s);
	
	//Оператор вывода для класса Font
	ostream& operator<<(ostream& ost, const Graph_lib::Font& f);
	
	//------------------------------------------------------------------------------
	
	class Group : public Shape {
		Vector_ref<Shape> g;
	public:
		void draw_lines() const { for (unsigned int i=0; i < size(); ++i)    g[i].draw(); }
		
		Shape& operator[](int i) { return g[i]; } //работает только с ф-циями класса Shape
		const Shape& operator[](int i) const { return g[i]; }
		int size() const { return g.size(); }
	
	//protected:
		void add_shape(Shape& s) { g.push_back(s); }
		void add_shape(Shape* s) { g.push_back(s); }
		
		void set_color(Color c)         { for (unsigned int i=0; i < size(); ++i)    g[i].set_color(c); }
		void set_fill_color(Color c)    { for (unsigned int i=0; i < size(); ++i)    g[i].set_fill_color(c); }
		void set_style(Line_style s)    { for (unsigned int i=0; i < size(); ++i)    g[i].set_style(s); }
		void move(int dx, int dy)       { for (unsigned int i=0; i < size(); ++i)    g[i].move(dx,dy); }
	};
	
	//------------------------------------------------------------------------------
	
	class chess_board : public Group {
		Point board_start;
		int side_len;		//Длина стороны квадрата
		void draw_board();	//рисование чередующихся белых и чёрных квадратов
	public:
		chess_board(Point p, int l) : board_start{p}, side_len{ l } {
			if (l<=10)		error("incorrect size of the side (" + to_string(l) + ") of the playing field");
			draw_board();
		}
		
		int board_side() { return side_len; }
	};
	
	
	class checkers_canva : public Shape {
		chess_board cb;
		Vector_ref<Circle> checkers;
		void draw_board();	//рисование шашек на поле
	public:
		checkers_canva(Point p, int l) : cb{p, l}
			{ draw_board(); }
		
		void draw_lines() const {
			cb.draw_lines();
			for (int i=0; i < checkers.size(); ++i)		checkers[i].draw_lines();
		}
		
		//Движение на северо-запад
		void white_move_nw(int i);
		void black_move_nw(int i);
		
		//Движение на северо-восток
		void white_move_ne(int i);
		void black_move_ne(int i);
		
		//Движение на юго-запад
		void white_move_sw(int i);
		void black_move_sw(int i);
		
		//Движение на юго-восток
		void white_move_se(int i);
		void black_move_se(int i);
	};
	
	//------------------------------------------------------------------------------
	
	//сортировка вектора с точками по значению X или Y (указывается во втором аргументе)
	void point_sort(vector<Point>& pnts, char ch);
	
	enum lorient {
		horisontal,		// --
		vertical,		// |
		left_diagonal,	// \ наклон
		right_diagonal	// / наклон
	};
	
	//------------------------------------------------------------------------------
	
	struct Striped_closed_polyline : Shape {
		using Shape::Shape;
		
		void draw_lines() const;
		void add(Point p) { Shape::add(p); }
		void set_fill_orient(lorient oo)
		{
			if ( oo == lorient::right_diagonal   ||   oo == lorient::left_diagonal )
				o = lorient::vertical;
			else
				o = oo;
		}
		
	private:
		lorient o {lorient::vertical}; //Направление закрашивающих линий
	};
	
	//------------------------------------------------------------------------------
	
	struct Striped_circle : Circle {
		using Circle::Circle;
		
		void draw_lines() const;
		void set_fill_orient(lorient oo)
		{
			if ( oo == lorient::right_diagonal   ||   oo == lorient::left_diagonal )
				o = lorient::vertical;
			else
				o = oo;
		}
		
	private:
		lorient o {lorient::vertical}; //Направление закрашивающих линий
	};
	
	//------------------------------------------------------------------------------
	
	struct Striped_rectangle : Rectangle {
		using Rectangle::Rectangle;
		
		void draw_lines() const;
		void set_fill_orient(lorient oo) {
			if ( oo == lorient::right_diagonal   ||   oo == lorient::left_diagonal )
				o = lorient::vertical;
			else
				o = oo;
		}
	
	private:
		lorient o {lorient::vertical}; //Направление закрашивающих линий
	};
	
	//------------------------------------------------------------------------------
	
	struct Immobile_Circle : Circle {
		using Circle::Circle;
		void move(int dx, int dy) {  /*error("invalid operation. Immobile_Circle object cannot be moved");*/  }
	};
	
	//------------------------------------------------------------------------------
	
	struct Smiley : Circle {
		using Circle::Circle;
		void draw_lines() const;
	};
	
	//beret //baseball cap
	
	struct Smiley_chinese : Smiley {
		using Smiley::Smiley;
		void draw_lines() const;
	};
	
	struct Smiley_bowler : Smiley {
		using Smiley::Smiley;
		void draw_lines() const;
	};
	
	
	
	struct Frowny : Circle {
		using Circle::Circle;
		void draw_lines() const;
	};
	
	struct Frowny_chinese : Frowny {
		using Frowny::Frowny;
		void draw_lines() const;
	};
	
	struct Frowny_bowler : Frowny {
		using Frowny::Frowny;
		void draw_lines() const;
	};
	
	//------------------------------------------------------------------------------
	
	struct Star : Shape {
		Star (Point cc, int nn, int RR) : c{ cc }, n{ nn }, R{ RR }, r{ int(R/3) }
		{
			if ( n<3 )		error("number of vertices cannot be less than 3 (Star constructor)");
			if ( n>=360 )	error("number of vertices cannot be greater or equals 360 (Star constructor)");
			if ( n<3 )		error("number of vertices cannot be less than 3 (Star constructor)");
			if ( r>R )		error("inner radius greater than outer (Star constructor)");
			if ( r<=0 )		error("inner radius cannot be less than 1 (Star constructor)");
			if ( R<=0 )		error("outer radius cannot be less than 1 (Star constructor)");
			star_points();
		}
		
		Star (Point cc, int nn, int RR, int rr) : c{ cc }, n{ nn }, R{ RR }, r{ rr }
		{
			if ( n<3 )		error("number of vertices cannot be less than 3 (Star def constructor)");
			if ( n>=360 )	error("number of vertices cannot be greater or equals 360 (Star def constructor)");
			if ( r>R )		error("inner radius greater than outer (Star def constructor)");
			if ( r<=0 )		error("inner radius cannot be less than 1 (Star def constructor)");
			if ( R<=0 )		error("outer radius cannot be less than 1 (Star def constructor)");
			star_points();
		}
		
		void draw_lines() const;
		
		
		//Доступ к значениям аргументов класса
		Point center()		const { return c; }
		int legs_count()	const { return n; }
		int out_radius()	const { return R; }
		int in_radius()		const { return r; }
		
	private:
		void star_points();		// добавление  точек (вершин и впадинок)
		
		Point c;	//Центр фигуры
		int n;		//Количество вершин звезды
		int R;		//Внешний радиус (описанный круг)
		int r;		//Внутренний радиус (вписанный круг)
	};
	
	//------------------------------------------------------------------------------
	
	//https://e-maxx.ru/algo/segments_intersection_checking
	int area (Point a, Point b, Point c);
	bool intersect_1 (int a, int b, int c, int d);
	bool intersect (Point a, Point b, Point c, Point d);

	struct Poly : Closed_polyline {
		Poly (const vector<Point>& pnts) : fig{pnts}
		{
			if ( fig.size() < 3 )			error("too few points in the Poly (Poly def constructor)");
			if ( check_intersections() )	error("intersection in the Poly (Poly def constructor)");
			
			for (int i = 0; i < fig.size(); ++i)
				Shape::add(fig[i]);
		}
		
		void add(Point p)
		{
			fig.push_back(p);
			if ( check_intersections() )	error("intersection in Poly (Poly add Point operation)");
			Shape::add(p);
		}
	
	private:
		bool check_intersections(); //Проверка на то пересекаются ли пара линий в фигуре
		vector<Point> fig;
	};
	
	//------------------------------------------------------------------------------
	
	struct Right_triangle : Polygon {
		//точка треугольника схождения двух катетов под прямым углом и длины катетов
		Right_triangle(Point p, int c1, int c2);
		
		//точка треугольника схождения двух катетов под прямым углом, длины катетов и угол поворота
		Right_triangle(Point p, int c1, int c2, int a);
		
		
		//Углы напротив катетов
		double angle_c1() const { return	atan(l1/l2) * 180 / M_PI; }
		double angle_c2() const { return	atan(l2/l1) * 180 / M_PI; }
		
		//Гипотенуза и катеты
		int hypotenuse() const { return		round(  sqrt(l1*l1 + l2*l2)  ); }
		int leg1() const { return	l1; }
		int leg2() const { return	l2; }
		
	private:
		Point ra;	//Точка треугольника схождения двух катетов под прямым углом
		int l1;		//Длины катетов
		int l2;
	};
	
	//------------------------------------------------------------------------------
	
	struct Regular_polygon : Shape {
		Regular_polygon(Point cc, int rr, int nn) :c{ cc }, r{ rr }, n{ nn }
		{
			if (n<3)		error("the number of Regular_polygon sides cannot be less than 3");
			if (n>360)		error("the number of Regular_polygon sides cannot be greater than 360");
			if (r<0)		error("negative Regular_polygon radius");
			
			angles();
		}
		
		void draw_lines() const;
		void move(int dx, int dy) { c.x+=dx;	c.y+=dy;	Shape::move(dx, dy); }
		
		int side_ln()		const;	//Длина одной из сторон
		int in_radius()		const;	//Радиус вписанной окружности
		int out_radius()	const;	//Радиус описанной окружности (по идее равен радиусу самой фигуры)
		
		Point center()		const { return c; }
		int num_of_angles()	const { return n; }
		int radius()		const { return r; }
	private:
		void angles();	// добавление  точек (углов)
		
		Point c;	// центр правильного многоугольника
		int   n;	// кол-во углов/сторон правильного многоугольника
		int   r;	// радиус описанного круга - расстояние от угла фигуры до центра (т.к. все углы лежат на окружности)
	};
	
	struct Octagon : Regular_polygon {
		Octagon(Point cc, int rr)
			: Regular_polygon{cc, rr, 8}
		{}
	};
	
	struct Regular_hexagon : Regular_polygon {
		Regular_hexagon(Point cc, int rr)
			: Regular_polygon{cc, rr, 6}
		{}
	};
	
	//------------------------------------------------------------------------------
	
	struct Arrow : Shape {
	public:
		Arrow (Point p1, Point p2) {
			add(p1);	//Нарисовать линию стрелки
			add(p2);
			arrow_points();				//Нарисовать стрелку
		}
		
		//Цвет линий и цвет заливки должен быть одинаковым
		void set_color(Color col) {
			Shape::set_color( col );
			Shape::set_fill_color( col );
		} 
		void set_fill_color(Color col) { set_color( col ); }
		
		//Рисует заливку треугольника-указателя (стороны и заливка одинакового цвета)
		void draw_lines() const;
	
	private:
		//Добавляет точки для дальнейшего рисования стрелки через Open_polyline::draw_lines()
		//Формирование точек треугольника-указателя стрелки происходит с учётом угла наклона линии стрелки
		void arrow_points ();
	};
	
	//------------------------------------------------------------------------------
	
	struct Arc : Shape {
		// Центр, min и max дистанция от центра (радиусы)
		Arc(Point p, int ww, int hh)
		:w{ ww }, h{ hh }, begin_angle{0}, end_angle{360} {
			Shape::add(Point{p.x - ww, p.y - hh});
		}
		
		// Центр, min, max дистанция от центра (радиусы) и начальный и конечный угол рисования части элипса
		Arc(Point p, int ww, int hh, double begin, double end);
		
		void draw_lines() const;
		
		Point center() const { return{point(0).x + w, point(0).y + h}; }
		Point focus1() const { return{center().x + int(sqrt(double(w*w - h*h))), center().y}; }
		Point focus2() const { return{center().x - int(sqrt(double(w*w - h*h))), center().y}; }
		
		void set_major(int ww) { move(abs(w-ww), 0);	w=ww; }
		int major() const { return w; }
		void set_minor(int hh) { move(0, abs(h-hh));	h=hh; }
		int minor() const { return h; }
		
		void set_angles(double begin, double end);
		int first_ang()  const { return begin_angle; }
		int second_ang() const {  return end_angle;  }
	private:
		int w;					//Радиус по горизонтали
		int h;					//Радиус по вертикали
		int begin_angle;	//начальный угол окружности (откуда будет начато рисование дуги эллипса)
		int end_angle;	//конечный  угол окружности (где будет завершено рисование дуги эллипса)
	};
	
	//------------------------------------------------------------------------------
	
	struct Box : Shape {
		Box(Point ul, int ww, int hh) :w{ ww }, h{ hh }, r{ 10 }
		{
			if (h<=0 || w<=0) error("bad rectangle: non-positive side");
			add(ul);
		}
		
		Box(Point ul, int ww, int hh, int rr) :w{ ww }, h{ hh }, r{ rr }
		{
			if (h<=0 || w<=0) error("bad rectangle: non-positive side");
			if (r<0) error("negative rectangle's radius");
			add(ul);
		}
		
		Box(Point ul, Point dr) :w{ dr.x - ul.x }, h{ dr.y - ul.y }, r{ 10 }
		{
			if (h<=0 || w<=0) error("bad rectangle: first point is not top left");
			add(ul);
		}
		
		Box(Point ul, Point dr, int rr) :w{ dr.x - ul.x }, h{ dr.y - ul.y }, r{ rr }
		{
			if (h<=0 || w<=0) error("bad rectangle: first point is not top left");
			if (r<0) error("negative rectangle's radius");
			add(ul);
		}
		
		void draw_lines() const;
		int height() const { return h; }
		int width()  const { return w; }
		int radius() const { return r; }
	private:
		int h;		// height (высота)
		int w;		// width  (ширина)
		int r;		// radius (радиус, отступ от верхнего левого угла фигуры)
	};
	
	//------------------------------------------------------------------------------
	
	struct TXTBox : Box {
		TXTBox(Point p, int ww, string s)
			: Box{p, ww, 25, 5}, lbl{s}
		{ if ( s.size() == 0 )		error("empty TXTBox lable"); }
		
		TXTBox(Point p, int ww, int hh, string s)
			: Box{p, ww, hh, 5}, lbl{s}
		{ if ( s.size() == 0 )		error("empty TXTBox lable"); }
		
		TXTBox(Point p, int ww, int hh, int rr, string s)
			: Box{p, ww, hh, rr}, lbl{s}
		{ if ( s.size() == 0 )		error("empty TXTBox lable"); }
		
		
		void draw_lines() const;
		
		void set_label(const string& s) { lbl = s; }
		string label() const { return lbl; }

		void set_font(Graph_lib::Font f) { fnt = f; }
		Graph_lib::Font font() const { return Graph_lib::Font(fnt); }

		void set_font_size(int s) { fnt_sz = s; }
		int font_size() const { return fnt_sz; }
		
	private:
		string lbl;		//Текст внутри прямоугольника
		Graph_lib::Font fnt{ Graph_lib::Font::times_bold };
		int fnt_sz{ 14 };
	};
	
	//------------------------------------------------------------------------------
	
	class Binary_tree : public Shape {
		Vector_ref<Circle> c;	//circles
		Group l;				//lines
		void grow();			//Заполнение вектора меток и группы линий
		
	protected:
		const string  up  =  "up";
		const string down = "down";
		
		int levels;
		string direction;		// направление стрелки ("up" или "down")
		Color lc {static_cast<int>(fl_color())};	// цвет стрелок/линий
		
	
	public:
		Binary_tree(Point p, int lvl);
		Binary_tree(Point p, int lvl, string str);
		Binary_tree(Point p, int lvl, string str, Color col);
		
		virtual void draw_lines() const;
		
		void set_color(Color col);
		void set_arrow_color(Color col);
		void set_fill_color(Color col)	{ for (int i=0; i<c.size(); ++i)		c[i].set_fill_color(col); }
		void set_style(Line_style sty)	{ for (int i=0; i<c.size(); ++i)		c[i].set_style(sty); }
		void move(int dx, int dy);
		
		//Общее кол-во меток (кружков)
		unsigned int nodes_count() const {
			unsigned int n {0};
			for (int i=0; i < levels; ++i)		n += pow(2,i);
			return n;
		}
		
		int levels_count() const { return levels; }
	};
	
	//------------------------------------------------------------------------------
	
	class Binary_txt_tree : public Binary_tree {
		Vector_ref<TXTBox> t;	//TXTBoxes
		Group l;				//lines
		void grow();			//Заполнение вектора меток и группы линий
	
	public:
		Binary_txt_tree::Binary_txt_tree(Point p, int lvl) : Binary_tree{p, lvl}
		{
			grow();
		}
		
		Binary_txt_tree::Binary_txt_tree(Point p, int lvl, string str) : Binary_tree{p, lvl, str}
		{
			grow();
		}
		
		Binary_txt_tree::Binary_txt_tree(Point p, int lvl, string str, Color col) : Binary_tree{p, lvl, str, col}
		{
			grow();
		}
		
		void draw_lines() const override {
			if (levels<=0)		return;
			
			for (unsigned int i=0; i < l.size(); ++i)    l[i].draw();
			for (unsigned int i=0; i < t.size(); ++i)    t[i].draw();
		}
		
		void set_color(Color col)		{
			lc = col;
			for (int i=0; i<l.size(); ++i)		l[i].set_color(col);
			for (int i=0; i<t.size(); ++i)		t[i].set_color(col);
		}
		
		void set_arrow_color(Color col)	{
			lc = col;
			for (int i=0; i<l.size(); ++i)		l[i].set_color(col);
		}
		
		void set_fill_color(Color col)	{ for (int i=0; i<t.size(); ++i)		t[i].set_fill_color(col); }
		void set_style(Line_style sty)	{ for (int i=0; i<t.size(); ++i)		t[i].set_style(sty); }
		void move(int dx, int dy)		{
			for (int i=0; i<l.size(); ++i)		l[i].move(dx,dy);
			for (int i=0; i<t.size(); ++i)		t[i].move(dx,dy);
		}
	};
	
	//------------------------------------------------------------------------------
	
	class Pseudo_window : public Shape {
		const int r {10}; //радиус для объекта Box
		
		Point win_start;	//Начальная точка
		Text txt;
		Box bwin;
		Group icons;
		
		Group shapes;		//для прикрепление объектов к "окну"
	
	public:
		Pseudo_window(Point p, int ww, int hh, string str);
		
		void draw_lines() const {
			txt.draw_lines();
			bwin.draw_lines();
			icons.draw_lines();
			shapes.draw_lines();
		}
		
		int x_max() const { return bwin.width(); }
		int y_max() const { return bwin.height(); }
		
		void set_label(string s) {
			if ( s == "" )			s = "My_Window";
			txt.set_label(s);
		}
		
		void attach(Shape& s) {
			s.move(win_start.x, win_start.y);
			shapes.add_shape(s);
		}
		
		void attach(Image& s) {
			s.move(win_start.x+r, win_start.y+r);
			s.set_mask(Point{win_start.x+r, win_start.y+r}, bwin.width()-20, bwin.height()-20);
			shapes.add_shape(s);
		}
		
		void detach(Shape& s)
		{
			for (unsigned int i = shapes.size(); 0<i; --i)	// guess last attached will be first released
				if (&shapes[i-1]==&s) {
					shapes[i-1].set_color(Color(Color::black, Color::invisible));
					shapes[i-1].set_fill_color(Color(Color::black, Color::invisible));
				}
		}
	};
	
	//------------------------------------------------------------------------------
	
	Point n(const Box& b);      //Север		(середина верхней грани прямоугольника)
	Point s(const Box& b);      //Юг		(середина нижней грани прямоугольника)
	Point e(const Box& b);      //Восток	(середина правой грани прямоугольника)
	Point w(const Box& b);      //Запад		(середина правой грани прямоугольника)
	Point center(const Box& b); //Центр		(центр прямоугольника)
	Point ne(const Box& b);     //Северо-восток		(верхний правый угол прямоугольника)
	Point se(const Box& b);     //Юго-восток		(нижний правый угол прямоугольника)
	Point sw(const Box& b);     //Юго-запад			(нижний левый угол прямоугольника)
	Point nw(const Box& b);     //Северо-восток		(верхний левый угол прямоугольника)
	
	Point n(const TXTBox& b);       //Север		(середина верхней грани прямоугольника)
	Point s(const TXTBox& b);       //Юг		(середина нижней грани прямоугольника)
	Point e(const TXTBox& b);       //Восток	(середина правой грани прямоугольника)
	Point w(const TXTBox& b);       //Запад		(середина правой грани прямоугольника)
	Point center(const TXTBox& b);  //Центр		(центр прямоугольника)
	Point ne(const TXTBox& b);      //Северо-восток		(верхний правый угол прямоугольника)
	Point se(const TXTBox& b);      //Юго-восток		(нижний правый угол прямоугольника)
	Point sw(const TXTBox& b);      //Юго-запад			(нижний левый угол прямоугольника)
	Point nw(const TXTBox& b);      //Северо-восток		(верхний левый угол прямоугольника)
	
	//------------------------------------------------------------------------------
	
	Point n(const Graph_lib::Rectangle& r);         //Север		(середина верхней грани прямоугольника)
	Point s(const Graph_lib::Rectangle& r);         //Юг		(середина нижней грани прямоугольника)
	Point e(const Graph_lib::Rectangle& r);         //Восток	(середина правой грани прямоугольника)
	Point w(const Graph_lib::Rectangle& r);         //Запад		(середина правой грани прямоугольника)
	Point center(const Graph_lib::Rectangle& r);    //Центр		(центр прямоугольника)
	Point ne(const Graph_lib::Rectangle& r);        //Северо-восток		(верхний правый угол прямоугольника)
	Point se(const Graph_lib::Rectangle& r);        //Юго-восток		(нижний правый угол прямоугольника)
	Point sw(const Graph_lib::Rectangle& r);        //Юго-запад			(нижний левый угол прямоугольника)
	Point nw(const Graph_lib::Rectangle& r);        //Северо-восток		(верхний левый угол прямоугольника)
	
	//------------------------------------------------------------------------------
	
	Point point_on_circle(Point c, int r, int angle);	//Точка на окружности по заданным центру, радиусу окружности и углу отклонения точки
	Point point_on_circle(const Circle& c, int angle);						//Точка на окружности по заданному углу
	int point_angle (const Circle& c, const Point& p);						//Угол наклона линии от центра до точки на окружности (радиуса)
	vector<Point> circles_intersect (const Circle& c1, const Circle& c2);	//Точки пересечения двух окружностей
	
	Point n(const Circle& c);       //Север		(на 12 часов - 90 градусов)
	Point s(const Circle& c);       //Юг		(на 6 часов - 270 градусов)
	Point e(const Circle& c);       //Восток	(на 3 часа - 0/360 градусов)
	Point w(const Circle& c);       //Запад		(на 9 часов - 180 градусов)
	Point center(const Circle& c);  //Центр		(центр круга)
	Point ne(const Circle& c);      //Северо-восток		(между 1 и 2 часами - 45 градусов)
	Point se(const Circle& c);      //Юго-восток		(между 4 и 5 часами - 315 градусов)
	Point sw(const Circle& c);      //Юго-запад			(между 7 и 8 часами - 225 градусов)
	Point nw(const Circle& c);      //Северо-восток		(между 10 и 11 часами - 135 градусов)
	
	//------------------------------------------------------------------------------
	
	Point point_on_ellipse(const Graph_lib::Ellipse& e, int angle);		//Точка на эллипсе по заданному углу
	
	Point n(const Graph_lib::Ellipse& e);       //Север		(на 12 часов - 90 градусов)
	Point s(const Graph_lib::Ellipse& e);       //Юг		(на 6 часов - 270 градусов)
	Point e(const Graph_lib::Ellipse& e);       //Восток	(на 3 часа - 0/360 градусов)
	Point w(const Graph_lib::Ellipse& e);       //Запад		(на 9 часов - 180 градусов)
	Point center(const Graph_lib::Ellipse& e);  //Центр		(центр эллипса)
	Point ne(const Graph_lib::Ellipse& e);      //Северо-восток		(между 1 и 2 часами - 45 градусов)
	Point se(const Graph_lib::Ellipse& e);      //Юго-восток		(между 4 и 5 часами - 315 градусов)
	Point sw(const Graph_lib::Ellipse& e);      //Юго-запад			(между 7 и 8 часами - 225 градусов)
	Point nw(const Graph_lib::Ellipse& e);      //Северо-восток		(между 10 и 11 часами - 135 градусов)
};		// namespace  addition_intermediate_version