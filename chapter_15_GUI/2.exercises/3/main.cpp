

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

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
			constexpr int ymax = 600;
			
			constexpr int xlength = 400;	//Длины осей
			constexpr int ylength = 400;
			
														//Расстояния:
			constexpr int xoffset = (xmax-xlength)/2;	// от левого края окна до оси y
			constexpr int yoffset = (ymax-ylength)/2;	// от нижнего края окна до оси x
			//constexpr int xspace  = (xmax-xlength)/2;	// от конца оси x до правого края окна
			//constexpr int yspace  = (ymax-ylength)/2;	// от конца оси y до верхнего края окна
			
			constexpr int yxscale = 20;		//Количество меток на каждой из осей
			
			//------------------------------------------------------------------------------
			
			Point tl{win_centering( xmax, ymax )}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, xmax, ymax, "Глава 15. Упражнение №3");
			// окно посередине экрана
			// размер окна 600*600
			// заголовок окна: Глава 15. Упражнение №3
			
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
			
			constexpr int r_min = -10;	//Диапазон значений [ r_min; r_max )
			constexpr int r_max = 11;
			constexpr int n_points = 1000;	//Кол-во точек
			
			Moded_Function<int> f {one,   r_min, r_max,   cntr,   n_points, yxscale, yxscale};
			f.set_color(Color::dark_green);
			win.attach(f);
			win.wait_for_button();
			
			f.set_function(slope);
			win.wait_for_button();
			
			f.set_function(square);
			win.wait_for_button();
			
			f.set_precision(8);
			win.wait_for_button();
			
			f.set_precision(15);
			win.wait_for_button();
			
			//f.set_precision(20);
			//win.wait_for_button();
			
			f.set_function([](double x) { return square(x)*x+x; });	//пробуем указать через лямбда функцию
			win.wait_for_button();
			
			f.set_function(cos);
			win.wait_for_button();
			
			f.set_function(sloping_cos);
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
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