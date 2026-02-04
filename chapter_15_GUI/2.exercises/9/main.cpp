

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
			
			//------------------------------------------------------------------------------
			
			//Открываем файл ввода
			cout << "Please enter name of input file: ";
			
			string iname;
			cin >> iname;
			
			ifstream ifs { iname };
			if (!ifs)		error("the specified file cannot be opened (" + iname + ")");
			ifs.exceptions(ifs.exceptions() | ios_base::badbit);	// Генерация исключения в случае состояния bad ()
			
			vector< pair<double,double> > vdp;
			double l, r;
			char ch1, ch2, ch3;
			
						// (    NUM1   ,   NUM2    )
			while (ifs >> ch1 >> l >> ch2 >> r >> ch3)
				vdp.push_back( make_pair(l, r) );
			
			if ( !ifs.eof() )		error("an error occurred while reading the file ", iname);
			
			double vdp_ymax {vdp[0].second};
			for (auto p : vdp)
				if (p.second > vdp_ymax)	vdp_ymax = p.second;
			
			const int xscale = vdp.size() + 1;		//Количество меток на оси X
			const int yscale =  vdp_ymax  + 5;		//Количество меток на оси Y
			
			//------------------------------------------------------------------------------
			
			Point tl{win_centering( xmax, ymax )}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, xmax, ymax, "Глава 15. Упражнения №9");
			// окно посередине экрана
			// размер окна 600*600
			// заголовок окна: Глава 15. Упражнения №9
			
			//Point cntr{win.x_max()/2, win.y_max()/2};	//Центральная точка окна
			Point cntr{xoffset, ymax-yoffset};	//Центральная точка окна
			
			
			Axis x {Axis::x,   cntr, xlength,   xscale,   "Рост"};
			x.set_color(Color::dark_red);
			x.label.move(380, -20);
			
			Axis y {Axis::y,   cntr, ylength,   yscale,   "Кол-во людей"};
			y.set_color(Color::dark_red);
			
			win.attach(x);
			win.attach(y);
			//win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			Bar_chart_txt bct {cntr,   vdp,   xlength, double(xlength/xscale), double(ylength/yscale)};
			bct.set_color(Color::dark_yellow);
			bct.set_fill_color(Color::yellow);
			
			for (int i=0; i<bct.col_count(); ++i)
				if (i%2 == 0) {
					bct.Bar_chart::operator[](i).set_color(Color::dark_cyan);
					bct[i].set_fill_color(Color::cyan);
				}
			
			win.attach(bct);
			win.wait_for_button();
			
			bct.set_color(Color::black);
			win.wait_for_button();
			
			for (int i=0; i < bct.col_count(); ++i) {
				bct.mark(i, 'u').set_color(Color::black);
				if (bct.mark(i, 'u').label().size() == 1)	bct.mark(i, 'u').move(5,0);
				
				bct.mark(i, 'd').set_color(Color::dark_red);
				bct.mark(i, 'd').move(-5,0);
			}
			
			win.wait_for_button();
			win.detach(bct);
			
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