
#define _USE_MATH_DEFINES
#include <cmath>

//https://www-formula.ru/2011-09-24-00-40-48
//https://ru.onlinemschool.com/math/formula/regular_polygon/#h5
//https://myalfaschool.ru/articles/ugly-pravilnogo-mnogougolnika-formuly
//
//https://forum.sources.ru/index.php?showtopic=302678


//https://github.com/weenchvd/Programming_Principles_And_Practice_Using_CXX/blob/master/Chapter_12/C12_Exercise_12.11.cpp
//https://bumpyroadtocode.com/2017/09/14/convoluted-polygons-fltk/

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>


using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(100, 100);		//верхний левый угол окна (расположение на экране)
	
	Simple_window win(tl, 600, 600, "Упражнение №11");
	// размер окна (600*600)
	// заголовок окна: Упражнение №11

	Graph_lib::Closed_polyline triangle;
	triangle.set_color(Color::red);
	triangle.set_fill_color(Color::dark_red);
	
	//строим сначала нижние точки треугольника
	triangle.add( Point{230,		350} ); 
	triangle.add( Point{230+160,	350} );
	
	//затем строим верхнюю точку треугольника отталкиваясь от высоты находимой через известную сторону
	int tri_h = sqrt( pow(230+160-230, 2) ) * sqrt(3) / 2;
	triangle.add( Point{230+160/2,	350 - tri_h} ); // y - высота треугольника (AB * sqrt(3) / 2)
	
	//------------------------------------------------------------------------------
	
	Graph_lib::Closed_polyline quad;
	quad.set_color(Color::blue);
	quad.set_fill_color(Color::dark_blue);

	quad.add( Point{230,		350 - tri_h} );
	quad.add( Point{230+160,	350 - tri_h} );
	quad.add( Point{230+160,	350+160 - tri_h} );
	quad.add( Point{230,		350+160 - tri_h} );
	
	//------------------------------------------------------------------------------
	
	Graph_lib::Closed_polyline pentagon;
	pentagon.set_color(Color::green);
	pentagon.set_fill_color(Color::dark_green);
	
	Point center {230+160/2, 350 + int((350 - tri_h  -  350+160 - tri_h) / 2)};
	
	//Радиус описанной окружности вокруг квадрата = половине диагонали
	//для пятиугольника она будет вписанной
	double radius = sqrt(2) * sqrt( pow(230+160 - 230, 2) )   / 2;
	
	//Радиус описанной окружности вокруг пятиугольника
	//сторону пятиугольника выводим из радиуса вписанной окружности
	tri_h = 2 * radius * tan(M_PI / 5);
	radius = tri_h / (2 * sin(M_PI / 5));
	
	radius = 130;

	for (int i = 0; i < 5; i++) {
		int x = center.x + 10 + radius * cos(2 * M_PI * i / 5);
		int y = center.y + radius * sin(2 * M_PI * i / 5);
		
		pentagon.add( Point{x, y} );
	}
	
	//------------------------------------------------------------------------------
	
	Graph_lib::Closed_polyline hexagon;
	hexagon.set_color(Color::yellow);
	hexagon.set_fill_color(Color::dark_yellow);
	
	radius = 143;
	
	for (int i = 0; i < 6; i++) {
		//сдвиг от начала коорд.								поворот точек на 90 градусов
		int x = center.x + 18 + radius * cos( (2 * M_PI * i / 6) + (M_PI/2) );
		int y = center.y + radius * sin( (2 * M_PI * i / 6) + (M_PI/2) );
		
		hexagon.add( Point{x, y} );
	}
	
	//------------------------------------------------------------------------------
	
	Graph_lib::Closed_polyline heptagon;
	heptagon.set_color(Color::magenta);
	heptagon.set_fill_color(Color::dark_magenta);
	
	radius = 153.5;
	
	for (int i = 0; i < 7; i++) {
		//сдвиг от начала коорд.
		int x = center.x + 24 + radius * cos( (2 * M_PI * i / 7) );
		int y = center.y + radius * sin( (2 * M_PI * i / 7) );
		
		heptagon.add( Point{x, y} );
	}
	
	//------------------------------------------------------------------------------
	
	Graph_lib::Closed_polyline octatagon;
	octatagon.set_color(Color::cyan);
	octatagon.set_fill_color(Color::dark_cyan);
	
	radius = 163;
	
	for (int i = 0; i < 8; i++) {
		//сдвиг от начала коорд.								поворот точек на 45/2 градусов
		int x = center.x + 29 + radius * cos( (2 * M_PI * i / 8) + (M_PI/8) ); //(22.5*M_PI/180)
		int y = center.y +		radius * sin( (2 * M_PI * i / 8) + (M_PI/8) );
		
		octatagon.add( Point{x, y} );
	}
	
	//------------------------------------------------------------------------------
	
	win.attach(octatagon);
	win.attach(heptagon);
	win.attach(hexagon);
	win.attach(pentagon);
	win.attach(quad);
	win.attach(triangle);
	
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	cerr << "Error ( main() ): " << e.what() << '\n';
	keep_window_open();
	return 1;
}

catch (...) {
	cerr << "Oops! Unknown error! ( main() )\n";
	keep_window_open();
	return 2;
}