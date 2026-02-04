

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";


//------------------------------------------------------------------------------

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
			
			Simple_window win(tl, xmax, ymax, "Глава 15. Упражнение №4");
			// окно посередине экрана
			// размер окна 600*600
			// заголовок окна: Глава 15. Упражнение №4
			
			Point cntr{win.x_max()/2, win.y_max()/2};	//Центральная точка окна
			
			
			Axis x {Axis::x,   Point{xoffset, cntr.y}, xlength,   yxscale,   "ОСЬ X"};
			x.set_color(Color::dark_red);
			x.label.move(350, 0);
			
			Axis y {Axis::y,   Point{cntr.x, ymax-yoffset}, ylength,   yxscale,   "ОСЬ Y"};
			y.set_color(Color::dark_red);
			
			win.attach(x);
			win.attach(y);
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			constexpr int r_min = -10;	//Диапазон значений [ r_min; r_max )
			constexpr int r_max = 10;
			constexpr int n_points = 400;	//Кол-во точек
			
			Moded_Function<int> fsin {sin,   r_min, r_max,   cntr,   n_points, yxscale, yxscale, 10};
			Text fsin_txt {Point{fsin.point(0).x - 40, fsin.point(0).y}, "sin(x)"};
			fsin.set_color(Color::dark_green);
			fsin.set_style( Line_style(Line_style::solid, 2) );
			fsin_txt.set_color(Color::dark_green);
			
			Moded_Function<int> fcos {cos,   r_min, r_max,   cntr,   n_points, yxscale, yxscale, 10};
			Text fcos_txt {Point{fcos.point(0).x - 40, fcos.point(0).y + 10}, "cos(x)"};
			fcos.set_color(Color::dark_yellow);
			fcos.set_style( Line_style(Line_style::solid, 2) );
			fcos_txt.set_color(Color::dark_yellow);
			
			Moded_Function<int> sincos { [](double x) { return sin(x)+cos(x); },   r_min, r_max,   cntr,   n_points, yxscale, yxscale, 10};
			Text sincos_txt {Point{0, sincos.point(0).y}, "sin(x) + cos(x)"};
			sincos.set_color(Color::dark_blue);
			sincos.set_style( Line_style(Line_style::solid, 2) );
			sincos_txt.set_color(Color::dark_blue);
			
			Moded_Function<int> sin2cos2 { [](double x) { return pow(sin(x),2) + pow(cos(x),2); },   r_min, r_max,   cntr,   n_points, yxscale, yxscale, 10};
			Text sin2cos2_txt {Point{0, sin2cos2.point(0).y - 5}, "sin(x)^2 + cos(x)^2"};
			sin2cos2.set_color(Color::dark_magenta);
			sin2cos2.set_style( Line_style(Line_style::solid, 2) );
			sin2cos2_txt.set_color(Color::dark_magenta);
			
			
			win.attach(fsin);
			win.attach(fsin_txt);
			win.attach(fcos);
			win.attach(fcos_txt);
			win.attach(sincos);
			win.attach(sincos_txt);
			win.attach(sin2cos2);
			win.attach(sin2cos2_txt);
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