

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";


//------------------------------------------------------------------------------

//Т.к. реализация Fct не подразумевает использование конструкции [i](double) { return leibniz(i); } и подобных ей
// явно передаваемый аргумент осуществим только через глобальную переменную
int leibniz_approx {0};

double leibniz (int n) {
	double l {0};
	
	for (double i=1; i<n; ++i) {
		if (int(i)%2 == 0)	l -= 1/(i+(i-1));
		else				l += 1/(i+(i-1));
	}
	
	return l;
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
			
			Simple_window win(tl, xmax, ymax, "Глава 15. Упражнение №5");
			// окно посередине экрана
			// размер окна 600*600
			// заголовок окна: Глава 15. Упражнение №5
			
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
			
			constexpr int n = 1000;			//Кол-во членов ряда Лейбница
			
			for (int i=1; i<n; i+=50) {
				leibniz_approx = i;
				Moded_Function<int> leib {[](double) { return leibniz(leibniz_approx); },   r_min, r_max,   cntr,   n_points, yxscale, yxscale, 10};
				leib.set_color(Color::dark_magenta);
				cout << "Members num of leibniz: " << i << '\t' << leibniz(leibniz_approx) << '\n';
				win.attach(leib);
				win.wait_for_button();
				win.detach(leib);
			}
			
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