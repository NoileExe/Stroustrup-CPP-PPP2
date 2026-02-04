

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(100, 100);		//верхний левый угол окна
	
	Simple_window win(tl, 300, 300, "Упражнение №1");
	// размер окна (300*300)
	// заголовок окна: Упражнение №1
	
	Graph_lib::Rectangle rctngl {Point(20, 30), 260, 100};
	
	rctngl.set_color(Color::red);
	rctngl.set_style( Line_style(Line_style::solid, 2) );
	
	
	Graph_lib::Polygon poly_rctngl;
	poly_rctngl.add(Point{20, 160});
	poly_rctngl.add(Point{20, 260});
	poly_rctngl.add(Point{280, 260});
	poly_rctngl.add(Point{280, 160});
	
	poly_rctngl.set_color(Color::blue);
	poly_rctngl.set_style( Line_style(Line_style::solid, 2) );
	
	win.attach(rctngl);
	win.attach(poly_rctngl);
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}