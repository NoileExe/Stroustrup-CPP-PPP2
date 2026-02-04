

#include <yes_or_no.h>
#include <Simple_window.h>	//если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

double one (double x) { return 1; }			//горизонтальная линия
double slope (double x) { return x/2; }		//наклонная линия (45 градусов)
double square (double x) { return x*x; }	//парабола
double sloping_cos (double x) { return slope(x)+cos(x); }	//парабола

int main()
{
	while (true) {
		try
		{
			constexpr int xmax = 600;	//Размер окна
			constexpr int ymax = xmax;
			
			constexpr int xlength = 400;	//Длины осей
			constexpr int ylength = 400;
			
														//Расстояния:
			constexpr int xoffset = (xmax-xlength)/2;	// от левого края окна до оси y
			constexpr int yoffset = (ymax-ylength)/2;	// от нижнего края окна до оси x
			//constexpr int xspace  = (xmax-xlength)/2;	// от конца оси x до правого края окна
			//constexpr int yspace  = (ymax-ylength)/2;	// от конца оси y до верхнего края окна
			
			constexpr int yxscale = 20;		//Количество меток на каждой из осей
			
			//------------------------------------------------------------------------------
			
			Simple_window win {Point{100,100}, xmax, ymax,   "Глава 15. Задания (Графики функций)"};
			// окно посередине экрана
			// размер окна 600*600
			// заголовок окна: Глава 15. Задания (Графики функций)
			
			Point cntr{win.x_max()/2, win.y_max()/2};	//Центральная точка окна
			
			
			Axis x {Axis::x,   Point{xoffset, cntr.y}, xlength,   yxscale,   "1 == " + to_string(yxscale) + " пикселей"};
			x.set_color(Color::dark_red);
			x.label.move(350, 0);
			
			Axis y {Axis::y,   Point{cntr.x, ymax-yoffset}, ylength,   yxscale,   "1 == " + to_string(yxscale) + " пикселей"};
			y.set_color(Color::dark_red);
			
			win.attach(x);
			win.attach(y);
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			constexpr int r_min = -10; //Диапазон значений [ r_min; r_max )
			constexpr int r_max = 12;
			
			constexpr int n_points = 400;
			
			win.set_label("Уравнение прямой без масштабирования в окне");
			Function horiz1 {one,   r_min, r_max,   cntr,   n_points, 1, 1};
			horiz1.set_color(Color::white);
			win.attach(horiz1);
			win.wait_for_button();
			
			win.set_label("Уравнение прямой с масштабированием в окне");
			
			Function horiz {one,   r_min, r_max,   cntr,   n_points, yxscale, yxscale};
			horiz.set_color(Color::red);
			win.attach(horiz);
			win.wait_for_button();
			
			
			Function diag {slope,   r_min, r_max,   cntr,   n_points, yxscale, yxscale};
			Text diag_txt {Point{diag.point(0).x-10, diag.point(0).y-10},   "x/2"};
			diag.set_color(Color::black);
			diag_txt.set_color(Color::black);
			win.attach(diag);
			win.attach(diag_txt);
			win.wait_for_button();
			
			
			Function parabola {square,   r_min, r_max,   cntr,   n_points, yxscale, yxscale};
			Text parab_txt {Point{parabola.point(n_points/3).x-25, parabola.point(n_points/3).y},   "x*x"};
			parabola.set_color(Color::dark_green);
			parab_txt.set_color(Color::dark_green);
			win.attach(parabola);
			win.attach(parab_txt);
			win.wait_for_button();
			
			
			Function cosin {cos,   r_min, r_max,   cntr,   n_points, yxscale, yxscale};
			Text cos_txt {Point{cosin.point(0).x+10, cosin.point(0).y+20},   "cos"};
			cosin.set_color(Color::blue);
			cos_txt.set_color(Color::blue);
			win.attach(cosin);
			win.attach(cos_txt);
			win.wait_for_button();
			
			
			Function slop_cos {sloping_cos,   r_min, r_max,   cntr,   n_points, yxscale, yxscale};
			Text scos_txt {Point{slop_cos.point(0).x+25, slop_cos.point(0).y},   "slope + cos"};
			slop_cos.set_color(Color::yellow);
			scos_txt.set_color(Color::yellow);
			win.attach(slop_cos);
			win.attach(scos_txt);
			win.wait_for_button();
			
			
			win.put_on_top(x); //поверх остальных фигур
			win.put_on_top(y);
			
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