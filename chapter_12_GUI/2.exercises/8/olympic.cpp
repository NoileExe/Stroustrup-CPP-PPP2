

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(400, 400);		//верхний левый угол окна (расположение на экране)
	
	//Simple_window win(tl, Fl::w(), Fl::h(), "Упражнение №8");
	Simple_window win(tl, 415, 230, "Упражнение №8");
	// размер окна (415*220)
	// заголовок окна: Упражнение №8
	
	const int c_rad {50};
	
	
	//Координаты центра 1го круга
	tl.x = sqrt( (c_rad+15)*(c_rad+15) + (c_rad+15)*(c_rad+15) );
	tl.y = tl.x;
	
	Graph_lib::Circle c1 {tl, c_rad};
	c1.set_color(Color::blue);
	c1.set_style( Line_style(Line_style::solid, 6) );
	
	Lines l1;
	l1.add( Point(tl.x + c_rad - 1, tl.y - 10), Point(tl.x + c_rad - 1, tl.y + 5) );
	l1.set_color(Color::blue);
	l1.set_style( Line_style(Line_style::solid, 6) );
	
	
	//Координаты центра 2го круга
	tl.x += c_rad + 15 + c_rad;
	Graph_lib::Circle c2 {tl, c_rad};
	c2.set_color(Color::black);
	c2.set_style( Line_style(Line_style::solid, 6) );
	
	Lines l2;
	l2.add( Point(tl.x + c_rad - 1, tl.y - 10), Point(tl.x + c_rad - 1, tl.y + 5) );
	l2.add( Point(tl.x - 15, tl.y + c_rad - 3), Point(tl.x, tl.y + c_rad - 1) );
	l2.set_color(Color::black);
	l2.set_style( Line_style(Line_style::solid, 6) );
	
	
	//Координаты центра 3го круга
	tl.x += c_rad + 15 + c_rad;
	Graph_lib::Circle c3 {tl, c_rad};
	c3.set_color(Color::red);
	c3.set_style( Line_style(Line_style::solid, 6) );
	
	Lines l3;
	l3.add( Point(tl.x - 15, tl.y + c_rad - 3), Point(tl.x, tl.y + c_rad - 1) );
	l3.set_color(Color::red);
	l3.set_style( Line_style(Line_style::solid, 6) );
	
	
	//Координаты центра 4го круга
	tl.x = sqrt( (c_rad+45)*(c_rad+45) + (c_rad+45)*(c_rad+45) );
	tl.y = tl.x;
	tl.x += 15;
	Graph_lib::Circle c4 {tl, c_rad};
	c4.set_color(Color::yellow);
	c4.set_style( Line_style(Line_style::solid, 6) );
	
	
	//Координаты центра эллипса (5го круга)
	tl.x += c_rad + 15 + c_rad;
	Graph_lib::Ellipse e1 {tl, c_rad, c_rad};
	e1.set_color(Color::green);
	e1.set_style( Line_style(Line_style::solid, 6) );	// цвет внутри эллипса
	
	
	win.attach(c1);
	win.attach(c2);
	win.attach(c3);
	win.attach(c4);
	win.attach(e1);
	
	win.attach(l1);
	win.attach(l2);
	win.attach(l3);
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}