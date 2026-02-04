

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(100, 100);		//верхний левый угол окна
	
	Simple_window win(tl, 600, 400, "My window");
	// размер окна (600*400)
	// заголовок окна: My window
	
	Axis hori(Axis::x, Point(20, 360), 300, 10, "Ось x");
	// разновидность класса Shape
	// Axis::x обозначает горизонталью ось
	// начиная от (20,360)
	// 300 пикселей в длину
	// содержащую 10 делений
	// с подписью "Ось x"
	
	Axis vert(Axis::y, Point(20, 360), 300, 10, "Ось y");
	
	vert.set_color(Color::cyan);			// выбор цвета линии
	vert.label.set_color(Color::dark_red);	// выбор цвета текста
	
	
	win.attach(hori);		//привязываем фигуру (ось x) к ранее созданному окну win
	win.attach(vert);
	win.set_label("№12.7.3");
	
	//------------------------------------------------------------------------------
	
	Function gsin(sin, 0, 100, Point(20, 210), 1000, 50, 50);	//График синуса
	// Рисуем sin() в диапазоне [0:100) от (0,0) до (20,150)
	// используя 1000 точек; для масштабирования координаты умножаются на 50 каждая
	
	win.attach(gsin);
	
	gsin.set_color(Color::blue);
	
	win.set_label("№12.7.4");
	
	//------------------------------------------------------------------------------
	
	Graph_lib::Polygon polytrngl;		//разновидность Shape
	
	polytrngl.add(Point{60, 280});		//Три точки образуют треугольник
	polytrngl.add(Point{60, 120});
	polytrngl.add(Point{180, 280});
	
	polytrngl.set_color(Color::red);
	polytrngl.set_style(Line_style::dash);
	
	win.attach(polytrngl);
	win.set_label("№12.7.5");
	
	//------------------------------------------------------------------------------
	
	Graph_lib::Rectangle rctngl {Point(300, 50), 100, 150};
	
	Closed_polyline poly_rctngl;
	poly_rctngl.add(Point{100, 50});
	poly_rctngl.add(Point{200, 50});
	poly_rctngl.add(Point{200, 100});
	poly_rctngl.add(Point{100, 122});
	poly_rctngl.add(Point{50, 75});
	
	win.attach(rctngl);
	win.attach(poly_rctngl);
	win.set_label("№12.7.6");
	
	//------------------------------------------------------------------------------
	
	//Если добавить позже - будет поверх прямоугольника
	/*Function gsin(sin, 0, 100, Point(20, 210), 1000, 50, 50);	//График синуса
	// Рисуем sin() в диапазоне [0:100) от (0,0) до (20,150)
	// используя 1000 точек; для масштабирования координаты умножаются на 50 каждая
	
	win.attach(gsin);
	
	gsin.set_color(Color::blue);*/
	
	rctngl.set_fill_color(Color::yellow);	// цвет внутри прямоугольник
	polytrngl.set_style( Line_style(Line_style::dash, 4) );		// Тип и толщина линий
	poly_rctngl.set_style( Line_style(Line_style::dash, 2) );
	poly_rctngl.set_fill_color(Color::dark_magenta);
	
	win.set_label("№12.7.7");
	
	//------------------------------------------------------------------------------
	
	Text txt {Point{350, 125}, "Hello, graphical world!"};
	txt.set_font(Graph_lib::Font::times_bold);
	txt.set_font_size(20);
	
	win.attach(txt);
	win.set_label("№12.7.8");
	
	//------------------------------------------------------------------------------
	
	Image my_img {Point{100, 50}, "my_img.jpg"};
	my_img.move(300,200);
	my_img.set_mask(Point{0, 0}, 165, 70); // Обрезаем картнку (устанавливая маску)
	
	win.attach(my_img);
	win.set_label("№12.7.9");
	
	//------------------------------------------------------------------------------
	
	Circle c(Point(100,200),50);
	c.set_style( Line_style(Line_style(Line_style::dot, 2.25)) );
	
	Graph_lib::Ellipse e(Point(100,200), 75,25);
	e.set_color(Color::dark_red);
	e.set_style( Line_style(Line_style(Line_style::solid, 2)) );
	
	Mark m(Point(100,200),'x');
	
	ostringstream oss;
	oss << "screen size: " << x_max() << "*" << y_max()
		<< "; window size: " << win.x_max() << "*" << win.y_max();
	Text sizes(Point(100,20),oss.str());
	
	win.attach(c);
	win.attach(e);
	win.attach(m);
	win.attach(sizes);
	win.set_label("№12.7.10");
	
	//------------------------------------------------------------------------------
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}

//------------------------------------------------------------------------------
 