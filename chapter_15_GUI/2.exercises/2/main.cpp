

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

template<typename T> void print_function (const Moded_Function<T>& f) {
	cout << "\n\nRange [" << f.begin() << ';' << f.end() << ")\n"
			"Reference point " << f.reference_point() << "\n"
			"Points count " << f.points_count() << "\n"
			"X scale " << f.scale('x') << "  |  Y scale " << f.scale('y') << "\n";
}

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
			
			Simple_window win(tl, xmax, ymax, "Глава 15. Упражнение №2");
			// окно посередине экрана
			// размер окна 600*600
			// заголовок окна: Глава 15. Упражнение №2
			
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
			constexpr int n_points = 400;	//Кол-во точек
			
			Moded_Function<int> f {one,   r_min, r_max+2,   cntr,   n_points};
			win.attach(f);
			
			
			win.set_label("Уравнение прямой без масштабирования в окне");
			
			f.set_color(Color::white);
			print_function(f);
			win.wait_for_button();
			
			
			win.set_label("Уравнение прямой с масштабированием в окне");
			
			f.set_color(Color::red);
			f.set_scale(yxscale, 'x');
			f.set_scale(yxscale, 'y');
			print_function(f);
			win.wait_for_button();
			
			f.set_range(f.begin(), r_max);
			print_function(f);
			win.wait_for_button();
			
			
			f.set_color(Color::black);
			f.set_function(slope);
			print_function(f);
			win.wait_for_button();
			
			
			f.set_color(Color::dark_green);
			f.set_function(square);
			print_function(f);
			win.wait_for_button();
			
			f.set_count(20);
			print_function(f);
			win.wait_for_button();
			
			
			f.set_color(Color::dark_yellow);
			f.set_count(n_points);
			f.set_function([](double x) { return square(x)*x+x; });	//пробуем указать через лямбда функцию
			print_function(f);
			win.wait_for_button();
			
			
			f.set_color(Color::blue);
			f.set_function(cos);
			print_function(f);
			win.wait_for_button();
			
			
			f.set_color(Color::yellow);
			f.set_function(sloping_cos);
			print_function(f);
			
			Text scos_txt {Point{f.point(0).x+25, f.point(0).y},   "slope + cos"};
			scos_txt.set_color(f.color());
			win.attach(scos_txt);
			
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