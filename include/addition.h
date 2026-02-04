
#define _USE_MATH_DEFINES

//Включает Gui.h, который в свою очередь включает Graph.h и Window.h и Point.h и std_lib_facilities.h
#include "Simple_window.h"    //если нужна кнопка "Next"
#include <math.h>

//------------------------------------------------------------------------------

//constexpr double M_PI = 3.141592653589793238462643383;

namespace Graph_lib {
	//На вход:	ширина и высота будущего окна
	//Возврат:	координаты левой верхней точки окна для отображения окна ровно по центру
	Point win_centering (int w, int h);
	
	bool operator==(Color a, Color b);
	bool operator!=(Color a, Color b);
	
	//void operator=(Point& a, const Point& b);
	
	//Оператор вывода для класса Point
	ostream& operator<<(ostream& ost, const Point& p);
	
	//Оператор вывода для класса Color
	ostream& operator<<(ostream& ost, const Color& c);
	
	//Оператор вывода для класса Line_style
	ostream& operator<<(ostream& ost, const Line_style& s);
	
	//Оператор вывода для класса Font
	ostream& operator<<(ostream& ost, const Graph_lib::Font& f);
	
	//------------------------------------------------------------------------------
	
	struct Bar_chart : Shape {
		Bar_chart (Point o, const vector<double>& d, double ln, double xs = 25, double ys = 25);	//Инициализация только координатами по Y
		Bar_chart (Point o, const vector<double>& x, const vector<double>& y, double ln, double xs = 25, double ys = 25);
		Bar_chart (Point o, const vector< pair<double,double> >& xy, double ln, double xs = 25, double ys = 25);
		
		virtual void draw_lines() const { for (unsigned int i=0; i < recs.size(); ++i)		recs[i].draw(); }
		
		void set_color(Color c)			{ for (unsigned int i=0; i < recs.size(); ++i)    recs[i].set_color(c); }
		void set_fill_color(Color c)	{ for (unsigned int i=0; i < recs.size(); ++i)    recs[i].set_fill_color(c); }
		void set_style(Line_style s)	{ for (unsigned int i=0; i < recs.size(); ++i)    recs[i].set_style(s); }
		void move(int dx, int dy)		{ for (unsigned int i=0; i < recs.size(); ++i)    recs[i].move(dx,dy); }
		
		Rectangle& column(int i) { return recs[i]; } //Как аналог для варианта ниже
		Rectangle& operator[](int i) { return recs[i]; }
		const Rectangle& operator[](int i) const { return recs[i]; }
		int col_count() const { return recs.size(); }
	
	protected:
		void vdpairs_sort(vector< pair<double,double> >& vdp);	//Сортировка вектора с парами по значению X
		virtual void chart_points();	//Добавление фигур к гистограмме
		
		Vector_ref<Rectangle> recs;		//Столбики гистограммы
		
		Point orig;				//Точка пересечения осей (условное начало координат (0;0))
		vector< pair<double,double> > vals;	//Значения расположения столбцов на оси X и высоты столбцов по оси Y и vals.size() указывает кол-во столбцов гистограммы
		double xlenght;			//Расстояние по оси X для размещения столбцов одинаковой ширины на одинаковом удалении друг от друга
		double xscale;			//Масштабный множитель для смещения точек по оси X
		double yscale;			//Масштабный множитель для смещения точек по оси Y
	};
	
	
	struct Bar_chart_txt : Bar_chart {
		//Начало отсчёта координат в точке 'o', столбцы шириной 'ln / d.size() / 2' с таким же расстоянием между столбцами;
		// 'vector<double> d' содержит значения высот столбцов (значения по Y)
		// координаты по оси X масштабируются множителем 'xs', а по оси Y - множителем 'ys'
		Bar_chart_txt (Point o, const vector<double>& d, double ln, double xs = 25, double ys = 25)
			: Bar_chart{o, d, ln, xs, ys}
		{ chart_points(); }
		
		Bar_chart_txt (Point o, const vector<double>& x, const vector<double>& y, double ln, double xs = 25, double ys = 25)
			: Bar_chart{o, x, y, ln, xs, ys}
		{ chart_points(); }
		
		Bar_chart_txt (Point o, const vector< pair<double,double> >& xy, double ln, double xs = 25, double ys = 25)
			: Bar_chart{o, xy, ln, xs, ys}
		{ chart_points(); }
		
		void draw_lines() const { Bar_chart::draw_lines();	for (unsigned int i=0; i < marks.size(); ++i)	marks[i].draw(); }
		
		//Доступ к метке для манипуляций над ней
		//Индекс столбца к которому она привязана и местонахождение (верх 'u' или низ 'd')
		Text& mark(int i, char ud);
		
	private:
		void chart_points() override;	//Добавление фигур и меток к гистограмме
		
		Vector_ref<Text> marks;		//Столбики гистограммы
	};
	
	//------------------------------------------------------------------------------
	
	template<typename T> struct Moded_Function : Shape {
		// график ф-ции f(x) для 'x' в диапазоне [r1:r2) используя отрезки в кол-ве 'c'
		// считая точкой начала отсчёта координат (пересечения осей) точку 'o'
		// координаты по оси X масштабируются множителем 'xs', а по оси Y - множителем 'ys'
		// точность вычисления координат точек ф-ции регулируется аргументом 'p' с типом 'T'
		Moded_Function(Fct* f, double r1, double r2, Point o, int c = 100, double xs = 25, double ys = 25, T p = 1)
					: fequ{f},  rbgn{r1},  rend{r2}, orig{o},    count{c},     xscale{xs},     yscale{ys}, prec{p}
		{ function_points(); }
		
		//Изменение значение и перерисовка графика ф-ции при помощи function_points()
		void set_function (Fct* f) { fequ = f;	function_points(); }
		void set_range (double r1, double r2) {
			if (r2-r1 < 0)		error("bad graphing range");
			rbgn = r1;
			rend = r2;
			function_points();
		}
		void set_count (int c) {
			if (c <= 0)		error("non-positive graphing count");
			count = c;
			function_points();
		}
		void set_scale (double s, char c) {
			if (c == 'x')		xscale = s;
			else if (c == 'y')	yscale = s;
			else				error("bad axis id-symbol (not 'x' or 'y')"); // + string(1,c)
			function_points();
		}
		void set_precision (T p) {
			if (p <= 0)		error("non-positive precision value");
			prec = p;
			function_points();
		}
		
		//Получение текущих значений параметров
		double  begin() const { return rbgn; }
		double   end()  const { return rend; }
		Point reference_point() const { return orig; }
		int     points_count()  const { return count; }
		double  scale(char c)   const {
			if (c == 'x')		return xscale;
			else if (c == 'y')	return yscale;
			else				error("bad axis id-symbol (not 'x' or 'y')"); // + string(1,c)
		}
		int precision() const { return prec; }
		
	private:
		//Сброс точек если функция уже строилась и расстановка точек с новыми значений аргументов
		void function_points()
		{
			if ( number_of_points() != 0 )		Shape::~Shape(); //Удаляем ранее добавленные точки и саму фигуру
			
			if (prec <= 0  ||  prec > 15)	error("bad precision value " + to_string(prec));
			if (rend-rbgn < 0)				error("bad graphing range");
			if (count <= 0)					error("non-positive graphing count");
			
			double dist {(rend-rbgn) / count};
			double r {rbgn};
			
			for (int i=0; i < count; ++i) {
				int x = orig.x + round   (r * xscale * pow(10.0,prec))    / pow(10.0,prec);
				int y = orig.y - round(fequ(r) * yscale * pow(10.0,prec)) / pow(10.0,prec);
				add(Point {x, y});
				r += dist;
			}
		}
		
		Fct* fequ;		//Уравнение функции
		double rbgn;	//Начало диапазона значений определения точек функции
		double rend;	//Конец диапазона значений определения точек функции
		Point orig;		//Точка пересечения осей (условное начало координат (0;0))
		int count;		//Количество точек для риования графика функции
		double xscale;	//Масштабный множитель для смещения точек по оси X
		double yscale;	//Масштабный множитель для смещения точек по оси Y
		T prec;			//Точность вычисления координат точек ф-ции
	};
	
	//------------------------------------------------------------------------------
	
	struct Controller {
		virtual		void on()  = 0;		//чисто виртуальная ф-ция
		virtual		void off() = 0;
		virtual		void set_level(int) = 0;
		virtual		void show() const = 0;
	
	protected:
		Controller() : state{false}, level{0}	{ }
		Controller(bool b, int l) : state{b}, level{l}	{ }
		
		bool state;
		int level;
	};
	
	
	struct String_controller : Controller
	{
		String_controller() : Controller{}	{ }
		String_controller(bool b, int l) : Controller{b, l}
		{ if (level < 0)		error("negative level value"); }
		
		void on()  override { state =  true; }
		void off() override { state = false; }
		void set_level(int l) override;
		void show() const override;
	};
	
	
	struct Line_color_controller : Controller
	{
		Line_color_controller(Shape* s, bool b, int l) : sh{*s}, Controller{b, l}
		{
			if (level < 0)		error("negative level value");
			if (level > 255)	error("level value must be in the range [0; 255]");
			if (state)			on();
		}
		
		Line_color_controller(Shape& s, bool b, int l) : sh{s}, Controller{b, l}
		{
			if (level < 0)		error("negative level value");
			if (level > 255)	error("level value must be in the range [0; 255]");
			if (state)			on();
		}
		
		void on()  { state =  true;		set_level( level ); }
		void off() { state = false; }
		void set_level(int l);
		void show() const;
		Shape& shape() { return sh; }
		const Shape& shape() const { return sh; }
		
	private:
		Shape& sh;
	};
	
	
	struct Line_transparency_controller : Controller
	{
		Line_transparency_controller(Shape* s, bool b) : sh{*s}, Controller{b, (b) ? 255 : 0}
		{ set_level( level ); }
		
		Line_transparency_controller(Shape& s, bool b) : sh{s}, Controller{b, (b) ? 255 : 0}
		{ set_level( level ); }
		
		void on()  { state =  true;		set_level( 255 ); }
		void off() { state = false;		set_level( 0 ); }
		void set_level(int l);
		void show() const;
		Shape& shape() { return sh; }
		const Shape& shape() const { return sh; }
		
	private:
		Shape& sh;
	};
	
	
	struct Line_thickness_controller : Controller
	{
		Line_thickness_controller(Shape* s, bool b, int l) : sh{*s}, Controller{b, l}
		{
			if (level < 0)		error("negative level value");
			if (level > 255)	error("level value must be in the range [0; 255]");
		}
		
		Line_thickness_controller(Shape& s, bool b, int l) : sh{s}, Controller{b, l}
		{
			if (level < 0)		error("negative level value");
			if (level > 255)	error("level value must be in the range [0; 255]");
		}
		
		void on()  { state =  true;		set_level( level ); }
		void off() { state = false; }
		void set_level(int l);
		void show() const;
		Shape& shape() { return sh; }
		const Shape& shape() const { return sh; }
		
	private:
		Shape& sh;
	};
	
	//------------------------------------------------------------------------------
	
	struct Iterator {
		Iterator() : i{0}	{ }
		virtual		double* next() = 0;	//чисто виртуальная ф-ция
	
	protected:
		int i;	//Текущий перебираемый элемент
	};
	
	
	struct Vector_iterator : Iterator {
		Vector_iterator (vector<double>& v) : vd{v}		{ }
		
		double* next() override {
			if (i >= vd.size()  ||  vd.size() == 0)		return  nullptr;
			
			++i;
			return &vd[i-1];
		}
		
	private:
		vector<double> vd;
	};
	
	
	struct List_iterator : Iterator {
		List_iterator (list<double>& l) : ld{l}		{ }
		
		double* next() {
			if (i >= ld.size()  ||  ld.size() == 0)		return  nullptr;
			
			//list<double>::iterator li = ld.begin();
			auto li = ld.begin();
			advance(li, i);
			double* d = &*li;	//ссылка на разыменованный double
			++i;
			return d;
		}
		
	private:
		list<double> ld;
	};
	
	
	void print(Iterator&);
	
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
	
	class Binary_tree : public Shape {
		void grow();			//Заполнение группы mrks узлами в виде фигур Circle
		
	protected:
		Binary_tree() {}		//Для производных классов ("инициализация" protected-членов с обход ф-ции grow())
		
		const int r {8};		// радиус кружков
		const string  up  =  "up";
		const string down = "down";
		
		Group mrks;				//Метки
		Vector_ref<Text> txt;	//Текст добавляемый к меткам. txt.size() == mrks.size() и заполнен пустыми строками если ни к одной метке не был добавлен текст
		
		Point root_c;			//Центр корневого узла
		int levels {0};
		string direction {""};	// направление стрелки ("up" или "down")
		Color lc {static_cast<int>(fl_color())};	// цвет стрелок/линий
		
	
	public:
		Binary_tree(Point p, int lvl);
		Binary_tree(Point p, int lvl, string str);
		Binary_tree(Point p, int lvl, string str, Color col);
		
		virtual void draw_lines() const;
		
		void set_color(Color col)		{ lc = col;		Shape::set_color(col); }
		void set_arrow_color(Color col)	{ lc = col;		Shape::set_color( color().as_int() ); }
		
		virtual void move(int dx, int dy) {
			Shape::move(dx,dy);
			mrks.move(dx,dy);
			for (int i=0; i<txt.size(); ++i)	txt[i].move(dx,dy);
		}
		
		
		void set_mark_label(string d, string lbl);	//Установить значение надписи рядом с меткой, путь от корня к которой указан в 1ом аргументе
		
		
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
		const int w {35};	//ширина
		const int h {25};	//высота
		void grow();		//Заполнение группы mrks узлами в виде фигур TXTBox
	
	public:
		Binary_txt_tree(Point p, int lvl);
		Binary_txt_tree(Point p, int lvl, string str);
		Binary_txt_tree(Point p, int lvl, string str, Color col);
		
		void draw_lines() const override;
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
	
	//поиск точки пересечения двух линий, если есть таковая
	//ф-ция определена в Graph.cpp
	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection);
	
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
	
	struct Scheme_tree : TXTBox {
		using TXTBox::TXTBox;
		void draw_lines() const;
		
		void add_childs(Point p, int ww, const vector<string>& s);	//Инициализация ветвей
		Scheme_tree& operator[](int i) { return childs[i]; }
		const Scheme_tree& operator[](int i) const { return childs[i]; }
		int childs_size() const { return childs.size(); }
		
		const int y_inc {20};	//расстояние между нижним левым углом и верхним левым двух соседних дочерних узлов
		
	private:
		Vector_ref<Scheme_tree> childs;
	};
	
	//------------------------------------------------------------------------------
	
	class Pseudo_window : public Shape {
		const int r {10}; //радиус для объекта Box
		
		Point win_start;	//Начальная точка
		Text txt;
		Graph_lib::Box bwin;
		Graph_lib::Group icons;
		
		Graph_lib::Group shapes;		//для прикрепление объектов к "окну"
	
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
};