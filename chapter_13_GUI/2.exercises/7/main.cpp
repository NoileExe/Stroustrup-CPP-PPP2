

#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void build_scheme(Simple_window& win);

void txt_one_style_bold (Text& t) {
	t.set_color(Color::black);
	t.set_font(Graph_lib::Font::times_bold);
	t.set_font_size(18);
}

int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(800, 800)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 800, 800, "Глава 13. Упражнение №7");
			// окно посередине экрана
			// размер окна (800*800)
			// заголовок окна: Глава 13. Упражнение №7
			
			build_scheme(win);
			
			win.set_label("Нажмите кнопку NEXT для завершения программы");
			win.wait_for_button();
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}

//------------------------------------------------------------------------------

void build_scheme(Simple_window& win)
{
	Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
	
	Circle r(Point{cntr.x - 100, cntr.y - 100}, 200);
	r.set_fill_color(Color::red);
	r.set_color(Color(Color::black,Color::invisible));
	
	Circle g(Point{cntr.x + 100, cntr.y - 100}, 200);
	g.set_fill_color(Color::green);
	g.set_color(Color(Color::black,Color::invisible));
	
	Circle b(Point{cntr.x, cntr.y + 100}, 200);
	b.set_fill_color(Color::blue);
	b.set_color(Color(Color::black,Color::invisible));
	
	//Точки пересечения пар кругов
	vector<Point> red_green		{circles_intersect(r, g)};
	vector<Point> red_blue		{circles_intersect(r, b)};
	vector<Point> green_blue	{circles_intersect(g, b)};
	
	//------------------------------------------------------------------------------
	
	Closed_polyline y;
	y.set_fill_color(Color::yellow);
	y.set_color(Color(Color::black,Color::invisible));
	y.add(red_green[0]);
	
	for (int angle = point_angle(g, red_green[0]);  ;  ++angle)
	{
		Point p { point_on_circle(g, angle) };
		if ( p.y >= green_blue[1].y )		break;
		
		if ( y.point(y.number_of_points()-1) != p )
			y.add(p);
	}
	
	y.add(green_blue[1]);
	
	
	for (int angle = point_angle(b, green_blue[1]);  ;  --angle)
	{
		Point p { point_on_circle(b, angle) };
		if ( p.x >= red_blue[0].x )		break;
		
		if ( y.point(y.number_of_points()-1) != p )
			y.add(p);
	}
	
	y.add(red_blue[0]);
	
	for (int angle = point_angle(r, red_blue[0]);  ;  ++angle) //.y > red_green[0].y
	{
		Point p { point_on_circle(r, angle) };
		if ( p.y <= red_green[0].y )		break;
		
		if ( y.point(y.number_of_points()-1) != p )
			y.add(p);
	}
	
	//------------------------------------------------------------------------------
	
	
	Closed_polyline m;
	m.set_fill_color(Color::magenta);
	m.set_color(Color(Color::black,Color::invisible));
	m.add(green_blue[1]);
	
	for (int angle = point_angle(b, green_blue[1]);  ;  ++angle)
	{
		Point p { point_on_circle(b, angle) };
		if ( p.y >= red_blue[1].y )		break;
		
		if ( m.point(m.number_of_points()-1) != p )
			m.add(p);
	}
	
	m.add(red_blue[1]);
	
	for (int angle = point_angle(r, red_blue[1]);  ;  ++angle)
	{
		Point p { point_on_circle(r, angle) };
		if ( p.x >= red_green[1].x )		break;
		
		if ( m.point(m.number_of_points()-1) != p )
			m.add(p);
	}
	
	m.add(red_green[1]);
	
	for (int angle = point_angle(g, red_green[1]);  ;  --angle)
	{
		Point p { point_on_circle(g, angle) };
		if ( p.y <= green_blue[1].y )		break;
		
		if ( m.point(m.number_of_points()-1) != p )
			m.add(p);
	}
	
	//------------------------------------------------------------------------------
	
	Closed_polyline c;
	c.set_fill_color(Color::cyan);
	c.set_color(Color(Color::black,Color::invisible));
	c.add(red_blue[0]);
	
	for (int angle = point_angle(r, red_blue[0]);  ;  --angle)
	{
		Point p { point_on_circle(r, angle) };
		if ( p.y >= red_green[1].y )		break;
		
		if ( c.point(c.number_of_points()-1) != p )
			c.add(p);
	}
	
	c.add(red_green[1]);
	
	for (int angle = point_angle(g, red_green[1]);  ;  ++angle)
	{
		Point p { point_on_circle(g, angle) };
		if ( p.x >= green_blue[0].x )		break;
		
		if ( c.point(c.number_of_points()-1) != p )
			c.add(p);
	}
	
	c.add(green_blue[0]);
	
	for (int angle = point_angle(b, green_blue[0]);  ;  ++angle)
	{
		Point p { point_on_circle(b, angle) };
		if ( p.y <= red_blue[0].y )		break;
		
		if ( c.point(c.number_of_points()-1) != p )
			c.add(p);
	}
	
	//------------------------------------------------------------------------------
	
	Closed_polyline w;
	w.set_fill_color(Color::white);
	w.set_color(Color(Color::black,Color::invisible));
	w.add(green_blue[1]);
	
	for (int angle = point_angle(g, green_blue[1]);  ;  ++angle)
	{
		Point p { point_on_circle(g, angle) };
		if ( p.y >= red_green[1].y )		break;
		
		if ( w.point(w.number_of_points()-1) != p )
			w.add(p);
	}
	
	w.add(red_green[1]);
	
	for (int angle = point_angle(r, red_green[1]);  ;  ++angle)
	{
		Point p { point_on_circle(r, angle) };
		if ( p.y <= red_blue[0].y )		break;
		
		if ( w.point(w.number_of_points()-1) != p )
			w.add(p);
	}
	
	w.add(red_blue[0]);
	
	for (int angle = point_angle(b, red_blue[0]);  ;  ++angle)
	{
		Point p { point_on_circle(b, angle) };
		if ( p.x <= green_blue[1].x )		break;
		
		if ( w.point(w.number_of_points()-1) != p )
			w.add(p);
	}
	
	//------------------------------------------------------------------------------
	
	win.attach(r);
	win.attach(g);
	win.attach(b);
	
	win.attach(y);
	win.attach(m);
	win.attach(c);
	win.attach(w);
	
	win.wait_for_button();
	
	
	win.detach(r);
	win.detach(g);
	win.detach(b);
	
	win.detach(y);
	win.detach(m);
	win.detach(c);
	win.detach(w);
}