
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


constexpr double pi = M_PI; //3.14159265

using namespace Graph_lib;

//------------------------------------------------------------------------------

bool equilateral(vector<Point>& pnts)
{
	if ( pnts.size() < 2 )
		return false;
	
	double first_line_lenght { sqrt(  pow((pnts[0].x-pnts[1].x), 2) + pow((pnts[0].y-pnts[1].y), 2)  ) }; //Длина линии
	
	for (int i = 1; i < pnts.size(); ++i)
	{
		double line_lenght { sqrt( pow((pnts[i].x-pnts[i-1].x), 2) + pow((pnts[i].y-pnts[i-1].y), 2) ) }; //Длина линии
		if ( line_lenght != first_line_lenght  &&  abs(line_lenght - first_line_lenght) > 2 )		return false;
	}
	
	return true;
}

//------------------------------------------------------------------------------

//На вход:
// - ссылка на фигуру к которой будут добавляться точки
// - точка центра окружности в которую будет вписана фигура
// - ссылка на радиус окружности в которую будет вписана фигура (изменяет радиус на новый для след. фигуры)
// - кол-во углов фигуры
void next_fig (Closed_polyline& efig, Point ccntr, double& radius, int n)
{
	vector<Point> pnts;
	
	//cout << "N = " << n << '\n';
	
	for (int i = 0; i <= n; ++i) {
		//Все углы в равностороннем многоугольнике равны, и вычисляются по формуле ниже 360.0 / n, где n - кол-во углов
		//360 градусов == 2*pi в радианах
		double angle {0};
		if ( i < n )		angle = double(i) * (2.0 * pi / n);
		
		//определяем координаты
		//int x = double(ccntr.x) + int(radius) * cos( angle );
		//int y = double(ccntr.y) + int(radius) * sin( angle );
		int x = double(ccntr.x) + radius * cos( angle );
		int y = double(ccntr.y) - radius * sin( angle );
		
		//cout << angle << "\tX = " << x << "\tY = " << y << '\n';
		efig.add( Point{x, y} );
		pnts.push_back( Point{x, y} );
	}
	
	//Проверка на то равны ли стороны - на деле вредная, т.к. уже в 8ми угольнике разница составляет около 1.3 пикселей
	if ( equilateral(pnts) == false )		error ("The figure is not correct (equilateral).");
	
	//Длина одной из сторон
	double a_lnght =  sqrt( pow(pnts[0].x - pnts[1].x, 2) + pow(pnts[0].y - pnts[1].y, 2) );
	
	//Радиус вписанной окружности для след. вписанной фигуры
	radius = a_lnght / ( 2.0 * tan(pi/n) );
	
	//Радиус описанной окружности
	//radius = a_lnght / ( 2 * sin(pi/n) );
	
	if		( n==3 )	efig.set_color(Color::red);
	else if ( n==4 )	efig.set_color(Color::blue);
	else if ( n==5 )	efig.set_color(Color::green);
	else if ( n==6 )	efig.set_color(Color::yellow);
	else if ( n==7 )	efig.set_color(Color::magenta);
	else if ( n==8 )	efig.set_color(Color::cyan);
	
	if		( n==3 )	efig.set_fill_color(Color::dark_red);
	else if ( n==4 )	efig.set_fill_color(Color::dark_blue);
	else if ( n==5 )	efig.set_fill_color(Color::dark_green);
	else if ( n==6 )	efig.set_fill_color(Color::dark_yellow);
	else if ( n==7 )	efig.set_fill_color(Color::dark_magenta);
	else if ( n==8 )	efig.set_fill_color(Color::dark_cyan);
}


int main()
try
{
	Point tl(100, 100);		//верхний левый угол окна (расположение на экране)
	
	Simple_window win(tl, 600, 600, "Упражнение №11");
	// размер окна (600*600)
	// заголовок окна: Упражнение №11
	
	
	const Point ccntr {300, 300}; //Координаты центра окружности
	double radius {250};
	
	//Circle c1 {ccntr, int(radius)};
	//c1.set_color(Color::red);
	//win.attach( c1 );
	
	Closed_polyline octagon;
	next_fig(octagon, ccntr, radius, 8);
	win.attach( octagon );
	
	
	//Circle c2 {ccntr, int(radius)};
	//c2.set_color(Color::red);
	//win.attach( c2 );
	
	Closed_polyline heptagon;
	next_fig(heptagon, ccntr, radius, 7);
	win.attach( heptagon );
	
	
	//Circle c3 {ccntr, int(radius)};
	//c3.set_color(Color::red);
	//win.attach( c3 );
	
	Closed_polyline hexagon;
	next_fig(hexagon, ccntr, radius, 6);
	win.attach( hexagon );
	
	
	//Circle c4 {ccntr, int(radius)};
	//c4.set_color(Color::red);
	//win.attach( c4 );
	
	Closed_polyline pentagon;
	next_fig(pentagon, ccntr, radius, 5);
	win.attach( pentagon );
	
	
	//Circle c5 {ccntr, int(radius)};
	//c5.set_color(Color::red);
	//win.attach( c5 );
	
	Closed_polyline square;
	next_fig(square, ccntr, radius, 4);
	win.attach( square );
	
	
	//Circle c6 {ccntr, int(radius)};
	//c6.set_color(Color::red);
	//win.attach( c6 );
	
	Closed_polyline triangle;
	next_fig(triangle, ccntr, radius, 3);
	win.attach( triangle );
	
	
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