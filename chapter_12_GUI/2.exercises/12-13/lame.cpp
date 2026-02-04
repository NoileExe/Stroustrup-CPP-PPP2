

#define _USE_MATH_DEFINES

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>
#include <yes_or_no.h>
#include <console_encoding.h>

using namespace Graph_lib;

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
const string quit_question = "Закрыть программу?";


//------------------------------------------------------------------------------

//Ввод данных с клавиатуры в командной строке
void get_kb_args(double& a, double& b, double& m, double& n, int& N)
{
	cout << "Введите аргумент a: ";
	cin >> a;
	if (!cin)			error("Неверный ввод аргумента 'a'");
	else if (a == 0)	error("Аргумент 'a' является делителем и не может быть равен 0");
	
	
	
	cout << "Введите аргумент b: ";
	cin >> b;
	
	if		(!cin)		error("Неверный ввод аргумента 'b'");
	else if (b == 0)	error("Аргумент 'b' является делителем и не может быть равен 0");
	
	
	
	cout << "Введите аргумент m: ";
	cin >> m;
	
	if		(!cin)		error("Неверный ввод аргумента 'm'");
	else if (m <= 0)	error("Аргумент 'm' должен быть > 0");
	
	
	
	cout << "Введите аргумент n: ";
	cin >> n;
	
	if		(!cin)		error("Неверный ввод аргумента 'n'");
	else if (n <= 0)	error("Аргумент 'n' должен быть > 0");
	
	
	
	cout << "Введите количество точек для построения: ";
	cin >> N;
	
	if		(!cin)		error("Неверный ввод аргумента 'N'");
	else if (N <= 0)	error("Аргумент 'N' должен быть > 0");
}

//Поиск угла ближайшего к точке отсчёта координат (center) по 3ем координатам
double points_angle(Point curr, Point prev, Point center) {
	//Предыдущая "равноудалённая" точка
	int prevX {prev.x};
	int prevY {prev.y};
	
	//Текущая перебираемая точка
	int currX {curr.x};
	int currY {curr.y};
	
	//Длины сторон треугольника образуемого тремя точками:
	//      точка отсчёта координат (центр формы), пред. "равноудалённая" и текущая перебираемая
	double sideOA			{ sqrt(  pow(center.x-prevX, 2) + pow(center.y-prevY, 2)  ) };
	double sideOB			{ sqrt(  pow(center.x-currX, 2) + pow(center.y-currY, 2)  ) };
	double opposite_side	{ sqrt(  pow(prevX-currX,    2) + pow(prevY-currY,    2)  ) };
	
	//Угол образуемый двуми сторонами треугольника ближе к точке отсчёта координат (центр формы)
	// COS(искомый_угол) = (OA^2 + OB^2 - AB^2) / (2*OA*OB)
	double this_angle {0};
	this_angle = acos( (pow(sideOA, 2) + pow(sideOB, 2) - pow(opposite_side, 2)) / (2*sideOA*sideOB) ); //в радианах
	this_angle = (this_angle * 180.0) / M_PI; //в привычном виде (в градусах)
	
	return this_angle;
}


int main()
{
	while (true) {
		try
		{
			cout << "\nСуперэллипс (кривая Ламе) — двумерная геометрическая фигура, замкнутая кривая, "
					"напоминающая эллипс, сохраняющая геометрические особенности большой полуоси и мал"
					"ой полуоси, а также симметрию относительно них, но иную общую форму.\n"
					"Определяется следующим уравнением:\n"
					 << "_   _m    _   _n    " << '\n'
					 << "| x |     | y |    |" << '\n'
					 << "|---|  +  |---| =  |" << "\t, где m, n > 0" << '\n'
					 << "| a |  +  | b |    |" << "\n\n\n";
			
			
			double a, b, m, n;
			int N;
			
			get_kb_args(a, b, m, n, N);
			
			/*a = 250; b = 250; m = 5; n = 5;
			
			cout << "Enter the number of points to plot: ";
			cin >> N;
			
			if      (!cin)		error("Invalid argument input 'N'");
			else if (N <= 0)	error("Argument 'N' should be > 0");*/
			
			//------------------------------------------------------------------------------
			
			Point tl(x_max() / 2 - 600/2, y_max() / 2 - 600/2); //Расположение ровно по середине экрана
			
			Simple_window win(tl, 600, 600, "Упражнения №12-13");
			// размер окна (600*600)
			// заголовок окна: Упражнения №12-13
			
			if ( win.x_max() != win.y_max() )       error("окно должно быть квадратным");
			
			
			Graph_lib::Closed_polyline Lamecurve;
			Lamecurve.set_color(Color::black);
			Lamecurve.set_style( Line_style(Line_style::solid, 2) );
			
			//точка отсчёта координат в середине окна
			Point center(win.x_max() / 2, win.y_max() / 2);
			
			int radius;
			radius = 2 * ( win.x_max()/3 ); //две трети от ширины окна
			if ( a>b  ||  a==b )    radius = a;
			else                    radius = b;
			
			
			double y;
			vector<Point> points;
			
			//Точки для построения кривой Ламе выше оси X
			for (int x = -radius; x < radius; ++x) {
				y = b * pow( 1-pow(abs(x/a), m),  1/n );
				points.push_back( Point{int(x + center.x), int(y + center.y)} );
				Lamecurve.add( points[points.size()-1] );
			}
			
			//Точки для построения кривой Ламе ниже оси X
			for (int x = radius; x > -radius; --x) {
				y = b * pow( 1-pow(abs(x/a), m),  1/n );
				points.push_back( Point{int(x + center.x), int(-y + center.y)} );
				Lamecurve.add( points[points.size()-1] );
			}
			
			//------------------------------------------------------------------------------
			
			vector<Point> Npoints;
			
			//2.0 * M_PI / N  - в радианах
			//360.0      / N  - в градусах
			double angle {360.0      / N};
			
			//Аргумент N по сути задаёт кол-во углов в правильном многоугольнике.
			//В свою очередь все эти углы равны
			//Отталкиваясь от этого рассуждения через заданный угол получаем "равноудалённые" точки
			for (int i = 0; i < points.size(); ++i) {
				if ( i == 0 )		Npoints.push_back(points[i]);
				
				else {
					//Угол между текущей перебираемой точкой и точкой ранее добавленой в вектор Npoints
					double this_angle { points_angle(points[i], Npoints[Npoints.size()-1], center) };
					
					if ( abs(angle-this_angle) < 0.2  ||  this_angle > angle ) {
						Npoints.push_back(points[i]);
						//cout << angle << '\t' << this_angle << '\n';
					}
				}
			}
			
			//cout << angle << '\t' << points_angle(Npoints[Npoints.size()-1], Npoints[0], center) << '\n';
			
			Vector_ref<Lines> l;
			
			//Аргумент N по сути задаёт кол-во углов в правильном многоугольнике.
			//В свою очередь все эти углы равны
			//Отталкиваясь от этого рассуждения через заданный угол 
			for (int i = 0; i < points.size(); ++i)
				for (int j = 0; j < Npoints.size(); ++j)
					if ( points[i] == Npoints[j] )
					{
						l.push_back( new Lines );
						
						//for (int k = j; k < Npoints.size(); ++k) {
						for (int k = 0; k < Npoints.size(); ++k) {
							if ( Npoints[k] != Npoints[j] )     l[l.size()-1].add(Npoints[j], Npoints[k]);
							
							//раскрашивание линий разными цетами по четвертям
							if ( i < points.size()/4 ) { // [0; points.size()/4)
								l[l.size()-1].set_color(Color::red);
								l[l.size()-1].set_style( Line_style(Line_style(Line_style::solid, 2)) );
							}
							
							else if ( i < points.size()/2 ) { // [points.size()/4; points.size()/2)
								l[l.size()-1].set_color(Color::green);
								l[l.size()-1].set_style( Line_style(Line_style(Line_style::dash, 2)) );
							}
							
							else if ( i < 3*points.size()/4 ) { // [points.size()/2; 3*points.size()/4)
								l[l.size()-1].set_color(Color::magenta);
								l[l.size()-1].set_style( Line_style(Line_style(Line_style::dot, 2)) );
							}
							
							else if ( i <= points.size() ) { // [3*points.size()/4; points.size()]
								l[l.size()-1].set_color(Color::blue);
								l[l.size()-1].set_style( Line_style(Line_style(Line_style::dashdot, 2)) );
							}
						}
					}
			
			for (int i = 0; i < l.size(); ++i)
				win.attach(l[i]);
			
			win.attach(Lamecurve);
			
			win.wait_for_button();
			return 0;
		}

		catch (exception& e) {
			cerr << "Ошибка ( main() ): " << e.what() << '\n';
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Упс! Неизвестная ошибка! ( main() )\n";
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}