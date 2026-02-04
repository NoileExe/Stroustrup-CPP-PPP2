

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(0, 0);		//верхний левый угол окна (расположение на экране)
	
	//Simple_window win(tl, Fl::w(), Fl::h(), "Упражнение №7");
	Simple_window win(tl, x_max(), y_max(), "Упражнение №7");
	// размер окна соответствует установленному разрешению экрана
	// заголовок окна: Упражнение №7
	
	//------------------------------------------Фасад------------------------------------------
	
	int rect_w = 400;	//Длина прямоугольника
	int rect_h = 350;	//Высота прямоугольника
	tl.x = Fl::w() / 2 - rect_w / 2;    //Координаты верхнего левого угла фигуры (дом посередине окна)
	tl.y = Fl::h() / 2 - rect_h / 2;
	
	Graph_lib::Rectangle house_rect {tl, rect_w, rect_h};
	
	house_rect.set_color(Color::black);
	house_rect.set_fill_color(Color::yellow);	// цвет внутри прямоугольника
	house_rect.set_style( Line_style(Line_style::solid, 5) );		// Тип и толщина линий
	
	//------------------------------------------Фасад------------------------------------------
	//------------------------------------------Окна-------------------------------------------
	
	rect_w = house_rect.width()  / 4;	//Длина прямоугольника
	rect_h = house_rect.height() / 3;	//Высота прямоугольника
	tl.x += 25;    //Координаты верхнего левого угла фигуры
	tl.y *= 1.6;
	
	Graph_lib::Rectangle window1_rect {tl, rect_w, rect_h};
	
	window1_rect.set_color(Color::black);
	window1_rect.set_fill_color(Color::blue);	// цвет внутри прямоугольника
	window1_rect.set_style( Line_style(Line_style::solid, 5) );		// Тип и толщина линий
	
	
	Lines windows_cross;    //Перегородки окон
	
	windows_cross.add( Point(tl.x + rect_w/2, tl.y), Point(tl.x + rect_w/2, tl.y + rect_h) );
	windows_cross.add( Point(tl.x, tl.y + rect_h/2), Point(tl.x + rect_w/2, tl.y + rect_h/2) );
	
	//-----------------------------------------------------------------------------------------
	
	tl.x += house_rect.width() - 25 - 25 - window1_rect.width();
	
	Graph_lib::Rectangle window2_rect {tl, rect_w, rect_h};
	
	window2_rect.set_color(Color::black);
	window2_rect.set_fill_color(Color::blue);	// цвет внутри прямоугольника
	window2_rect.set_style( Line_style(Line_style::solid, 5) );		// Тип и толщина линий
	
	windows_cross.add( Point(tl.x + rect_w/2, tl.y), Point(tl.x + rect_w/2, tl.y + rect_h) );
	windows_cross.add( Point(tl.x, tl.y + rect_h/2), Point(tl.x + rect_w/2, tl.y + rect_h/2) );
	
	windows_cross.set_color(Color::black);
	windows_cross.set_style( Line_style(Line_style::solid, 3) );		// Тип и толщина линий
	
	//------------------------------------------Окна-------------------------------------------
	//------------------------------------------Дверь------------------------------------------
	
	rect_w = house_rect.width()  / 3;	//Длина прямоугольника
	rect_h = house_rect.height() / 1.5;	//Высота прямоугольника
	tl.x = Fl::w() / 2 - rect_w / 2;    //Координаты верхнего левого угла фигуры
	tl.y = Fl::h() / 2 - house_rect.height() / 2 + rect_h / 2;
	
	Graph_lib::Rectangle door_rect {tl, rect_w, rect_h};
	
	door_rect.set_color(Color::black);
	door_rect.set_fill_color(Color::dark_red);	// цвет внутри прямоугольника
	door_rect.set_style( Line_style(Line_style::solid, 5) );		// Тип и толщина линий
	
	tl.x += rect_w / 2;    //Координаты центра круга
	tl.y += 60;
	Graph_lib::Circle peephole {tl, 5};
	peephole.set_color(Color::black);
	peephole.set_fill_color(Color::blue);		// цвет внутри круга
	
	tl.x += (rect_w / 2) / 2;    //Координаты центра эллипса
	tl.y += (rect_h / 2) - 40;
	Graph_lib::Ellipse doorhandle {tl, 10, 5};
	doorhandle.set_color(Color::black);
	doorhandle.set_fill_color(Color::black);	// цвет внутри эллипса
	
	//------------------------------------------Дверь------------------------------------------
	//------------------------------------------Крыша------------------------------------------
	
	Graph_lib::Polygon roof_poly; //Три точки образуют треугольник
	
	tl.x = Fl::w() / 2 - house_rect.width() / 2 - 15;
	tl.y = Fl::h() / 2 - house_rect.height() / 2;
	roof_poly.add(tl);
	
	tl.x += house_rect.width() + 30;
	roof_poly.add(tl);
	
	tl.x -= house_rect.width() / 2 + 15;
	tl.y -= 150;
	roof_poly.add(tl);
	
	roof_poly.set_color(Color::black);
	roof_poly.set_fill_color(Color::dark_red);		// цвет внутри многоугольника
	roof_poly.set_style( Line_style(Line_style::solid, 5) );		// Тип и толщина линий
	
	//------------------------------------------Крыша------------------------------------------
	//------------------------------------------Труба------------------------------------------
	
	rect_w = 40;	//Длина прямоугольника
	rect_h = 100;	//Высота прямоугольника
	tl.x = Fl::w() / 2 - house_rect.width() / 2 + rect_w + 15;    //Координаты верхнего левого угла фигуры
	tl.y = Fl::h() / 2 - house_rect.height() / 2 - rect_h;
	
	Graph_lib::Rectangle smokepipe_rect {tl, rect_w, rect_h};
	
	smokepipe_rect.set_color(Color::black);
	smokepipe_rect.set_fill_color(Color::dark_red);	// цвет внутри прямоугольника
	smokepipe_rect.set_style( Line_style(Line_style::solid, 3) );		// Тип и толщина линий
	
	//------------------------------------------Труба------------------------------------------
	
	win.attach(house_rect);
	
	win.attach(window1_rect);
	win.attach(window2_rect);
	win.attach(windows_cross);
	
	win.attach(door_rect);
	win.attach(peephole);
	win.attach(doorhandle);
	
	win.attach(smokepipe_rect);
	
	win.attach(roof_poly);
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}