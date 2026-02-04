

#define _USE_MATH_DEFINES


#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct Arrow {
	Lines ln;
	Graph_lib::Closed_polyline trngl; //Polygon
	
	void new_arrow (Point p1, Point p2);
	
	Arrow(Point p1, Point p2) { new_arrow(p1, p2); }
};


void Arrow::new_arrow (Point p1, Point p2) {
	ln.add(p1, p2);
	ln.set_color(Color::red);
	ln.set_style( Line_style(Line_style(Line_style::solid, 2)) );
	
	
	//-----------------------------------Угол наклона стрелки-----------------------------------
	//this_angle = acos( (pow(c1, 2) + pow(c2, 2) - pow(opposite_side, 2)) / (2*sideOA*sideOB) ); //в радианах
	double angle { (30.0 * M_PI) / 180.0 }; //Угол поворота каждой стрелки
	
	// наклон стрелки \ или |
	if ( p2.x <= p1.x ) {
		//Длина катетов прямоугольного треугольника образованного линией стрелки и двумя перпендикулярами из оконечных точек (p1.x; p2.y  -  на горизонтали с p2)
		double c1 { sqrt( pow(p1.x-p1.x, 2) + pow(p1.y-p2.y, 2) ) };
		double c2 { sqrt( pow(p2.x-p1.x, 2) + pow(p2.y-p2.y, 2) ) };
		double line_angle { atan(c1/c2) };  //Угол линии стрелки к перпендикуляру опущенному от горизонтали пролегающей через p2
		//cout << line_angle * 180.0 / M_PI << '\t' << (line_angle + angle) * 180.0 / M_PI << '\t' << (line_angle - angle) * 180.0 / M_PI << '\n';
		
		int x = double(p2.x) + 10.0 * cos(line_angle + angle); //точка на окружности
		int y = double(p2.y) + 10.0 * sin(line_angle + angle);
		trngl.add(Point{ x, y });
		
		trngl.add(Point{p2.x, p2.y-1});
		
		x = double(p2.x) + 10.0 * cos(line_angle - angle); //точка на окружности
		y = double(p2.y) + 10.0 * sin(line_angle - angle);
		trngl.add(Point{ x, y });
	}
	
	// наклон стрелки /
	else {
		//Длина катетов прямоугольного треугольника образованного линией стрелки и двумя перпендикулярами из оконечных точек (p1.x; p2.y  -  на горизонтали с p2)
		double c1 { sqrt( pow(p1.x-p1.x, 2) + pow(p1.y-p2.y, 2) ) };
		double c2 { sqrt( pow(p2.x-p1.x, 2) + pow(p2.y-p2.y, 2) ) };
		double line_angle { atan(c2/c1) };  //Угол линии стрелки к горизонтали пролегающей через p2
		
		/*c1 = (3 * M_PI) / 2 - line_angle - angle;
		c2 = (3 * M_PI) / 2 - line_angle - angle + 2*angle;
		cout << "Line angle: " << line_angle * 180.0 / M_PI << '\n' 
			 << c1 * 180.0 / M_PI << '\t' << "cos: " << cos(c1) << '\t' << "sin: " << sin(c1) << '\n'
			 << c2 * 180.0 / M_PI << '\t' << "cos: " << cos(c2) << '\t' << "sin: " << sin(c2) << "\n\n";*/
		
		int x = double(p2.x) + 10.0 * cos((3 * M_PI) / 2 - line_angle - angle); //точка на окружности
		int y = double(p2.y) - 10.0 * sin((3 * M_PI) / 2 - line_angle - angle);
		trngl.add(Point{ x, y });
		
		trngl.add(Point{p2.x, p2.y-1});
		
		x = double(p2.x) + 10.0 * cos((3 * M_PI) / 2 - (line_angle - angle)); //точка на окружности
		y = double(p2.y) - 10.0 * sin((3 * M_PI) / 2 - (line_angle - angle));
		trngl.add(Point{ x, y });
	}
	
	trngl.set_color(Color::red);
	trngl.set_fill_color(Color::red);		// цвет внутри
	trngl.set_style(Line_style(Line_style::solid, 1));
}


void rect_one_style (Graph_lib::Rectangle& r) {
	r.set_color(Color::black);
	r.set_style( Line_style(Line_style::solid, 2) );
	r.set_fill_color(Color::white); //dark_yellow
}

void txt_one_style_bold (Text& t) {
	t.set_color(Color::black);
	t.set_font(Graph_lib::Font::times_bold);
	t.set_font_size(12);
}

void txt_one_style_regular (Text& t) {
	t.set_color(Color::black);
	t.set_font(Graph_lib::Font::times);
	t.set_font_size(12);
}


int main()
try
{
	Point p1(0, 0);		//верхний левый угол окна (расположение на экране)
	
	Simple_window win(p1, 560, 620, "Упражнение №10");
	// размер окна (560*620)
	// заголовок окна: Упражнение №10
	
	Vector_ref<Graph_lib::Rectangle> rctngls;
	Vector_ref<Text> txts;
	Vector_ref<Arrow> arrows; //Vector_ref
	
	//--------------------------------chapter12.cpp--------------------------------
	
	int rect_w = 200;	//Длина прямоугольника
	int rect_h = 60;	//Высота прямоугольника
	p1.x = 70;
	p1.y = 520;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "chapter12.cpp:"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "#include \"Graph.h\""});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 30), "#include \"Simple_window.h\""});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 45), "int main() {...}"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//--------------------------------chapter12.cpp--------------------------------
	//----------------------------------Graph.cpp----------------------------------
	
	rect_w = 115;	//Длина прямоугольника
	rect_h = 24;	//Высота прямоугольника
	p1.x = 10;
	p1.y = 400;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "Graph.cpp:"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "Графический код"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//----------------------------------Graph.cpp----------------------------------
	//-------------------------------Simple_window.h-------------------------------
	
	rect_w = 180;	//Длина прямоугольника
	rect_h = 60;	//Высота прямоугольника
	p1.x = 220;
	p1.y = 410;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "Simple_window.h:"});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "//Оконный интерфейс:"});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 30), "class Simple_window {...};"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 45), "..."});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//-------------------------------Simple_window.h-------------------------------
	//-----------------------------------GUI.cpp----------------------------------
	
	rect_w = 100;	//Длина прямоугольника
	rect_h = 24;	//Высота прямоугольника
	p1.x = 430;
	p1.y = 400;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "GUI.cpp:"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "Код GUI"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//-----------------------------------GUI.cpp----------------------------------
	//---------------------------------window.cpp---------------------------------
	
	rect_w = 115;	//Длина прямоугольника
	rect_h = 24;	//Высота прямоугольника
	p1.x = 200;
	p1.y = 335;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "window.cpp:"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "Оконный код"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//---------------------------------window.cpp---------------------------------
	//-----------------------------------Gui.h------------------------------------
	
	rect_w = 150;	//Длина прямоугольника
	rect_h = 60;	//Высота прямоугольника
	p1.x = 400;
	p1.y = 280;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "Gui.h:"});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "//Интерфейс GUI:"});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 30), "struct In_box {...};"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 45), "..."});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//-----------------------------------Gui.h------------------------------------
	//----------------------------------Graph.h-----------------------------------
	
	rect_w = 150;	//Длина прямоугольника
	rect_h = 60;	//Высота прямоугольника
	p1.x = 60;
	p1.y = 230;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "Graph.h:"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "//Графический интерфейс:"});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 30), "struct Shape {...};"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 45), "..."});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//----------------------------------Graph.h-----------------------------------
	//---------------------------------Window.h-----------------------------------
	
	rect_w = 130;	//Длина прямоугольника
	rect_h = 60;	//Высота прямоугольника
	p1.x = 260;
	p1.y = 180;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "Window.h:"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "//Оконный интерфейс:"});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 30), "class Window {...};"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 45), "..."});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//---------------------------------Window.h-----------------------------------
	//----------------------------------Point.h-----------------------------------
	
	rect_w = 130;	//Длина прямоугольника
	rect_h = 24;	//Высота прямоугольника
	p1.x = 60;
	p1.y = 110;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x, p1.y - 10), "Point.h:"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "struct Point {...};"});
	txt_one_style_bold(txts[ txts.size() - 1 ]);
	
	//----------------------------------Point.h-----------------------------------
	//----------------------------------Код FLTK----------------------------------
	
	rect_w = 80;	//Длина прямоугольника
	rect_h = 40;	//Высота прямоугольника
	
	p1.x = 440;
	p1.y = 80;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	p1.x = 445;
	p1.y = 85;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	p1.x = 450;
	p1.y = 90;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "Код FLTK"});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	//----------------------------------Код FLTK----------------------------------
	//---------------------------Заголовочные файлы FLTK--------------------------
	
	rect_w = 90;	//Длина прямоугольника
	rect_h = 40;	//Высота прямоугольника
	
	p1.x = 260;
	p1.y = 30;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	p1.x = 265;
	p1.y = 35;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	p1.x = 270;
	p1.y = 40;
	rctngls.push_back(new Graph_lib::Rectangle {p1, rect_w, rect_h});
	rect_one_style (rctngls[ rctngls.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 15), "Заголовочные "});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	txts.push_back(new Text {Point(p1.x + 8, p1.y + 30), "файлы FLTK"});
	txt_one_style_regular(txts[ txts.size() - 1 ]);
	
	//---------------------------Заголовочные файлы FLTK--------------------------
	//-----------------------------------Стрелки----------------------------------
	
	arrows.push_back( new Arrow(Point{155, 518}, Point{250, 471}) );    // chapter12.cpp -> Simple_window.h
	arrows.push_back( new Arrow(Point{155, 518}, Point{145, 291}) );    // chapter12.cpp -> Graph.h
	arrows.push_back( new Arrow(Point{80,  400}, Point{135, 291}) );    // Graph.cpp -> Graph.h
	arrows.push_back( new Arrow(Point{340, 410}, Point{340, 241}) );    // Simple_window.h -> Window.h
	arrows.push_back( new Arrow(Point{340, 410}, Point{430, 341}) );    // Simple_window.h -> Gui.h
	arrows.push_back( new Arrow(Point{500, 400}, Point{475, 341}) );    // GUI.cpp -> Gui.h
	arrows.push_back( new Arrow(Point{280, 335}, Point{300, 241}) );    // window.cpp -> Window.h
	arrows.push_back( new Arrow(Point{500, 280}, Point{370, 241}) );    // Gui.h -> Window.h
	arrows.push_back( new Arrow(Point{500, 280}, Point{350,  81}) );    // Gui.h -> Заголовочные файлы FLTK
	arrows.push_back( new Arrow(Point{135, 230}, Point{135, 135}) );    // Graph.h -> Point.h
	arrows.push_back( new Arrow(Point{135, 230}, Point{275,  81}) );    // Graph.h -> Заголовочные файлы FLTK
	arrows.push_back( new Arrow(Point{275, 180}, Point{170, 135}) );    // Window.h -> Point.h
	arrows.push_back( new Arrow(Point{325, 180}, Point{325,  81}) );    // Window.h -> Заголовочные файлы FLTK
	arrows.push_back( new Arrow(Point{440, 100}, Point{361,  60}) );    // Код FLTK -> Заголовочные файлы FLTK
	
	//-----------------------------------Стрелки----------------------------------
	
	for (int i = 0; i < rctngls.size(); ++i)
		win.attach( rctngls[i] );
	
	for (int i = 0; i < txts.size(); ++i)
		win.attach( txts[i] );
	
	for (int i = 0; i < arrows.size(); ++i) {
		win.attach( arrows[i].ln );
		win.attach( arrows[i].trngl );
	}
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}