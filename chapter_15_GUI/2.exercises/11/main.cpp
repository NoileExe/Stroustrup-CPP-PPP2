

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
			//Данные о средних температурах взяты с сайта: https://ru.weatherspark.com/
			
			//Открываем файлы для чтения данных
			ifstream Minvody { "minvody.txt" };
			if (!Minvody)		error("the specified file cannot be opened (minvody.txt)");
			Minvody.exceptions(Minvody.exceptions() | ios_base::badbit);	// Генерация исключения в случае состояния bad ()
			
			ifstream Sochi { "sochi.txt" };
			if (!Sochi)		error("the specified file cannot be opened (sochi.txt)");
			Sochi.exceptions(Sochi.exceptions() | ios_base::badbit);	// Генерация исключения в случае состояния bad ()
			
			ifstream SPB { "spb.txt" };
			if (!SPB)		error("the specified file cannot be opened (spb.txt)");
			SPB.exceptions(SPB.exceptions() | ios_base::badbit);	// Генерация исключения в случае состояния bad ()
			
			
			vector< pair<double,double> >   vdp;	//Общий вектор для поиска мин/макс значения температуры по всем городам
			vector< pair<double,double> >   mnv;	//Вектор значений температуры по месяцам для города Минеральные Воды (Минводы)
			vector< pair<double,double> >   sch;	//Вектор значений температуры по месяцам для города Сочи
			vector< pair<double,double> >   spb;	//Вектор значений температуры по месяцам для города Санкт-Петербург (СПб)
			
			double l, r;
			char ch1, ch2, ch3;
			
			//for (Temp_Data td; Minvody >> td; )
							// (    NUM1   ,   NUM2    )
			while (Minvody >> ch1 >> l >> ch2 >> r >> ch3) {
				mnv.push_back( make_pair(l, r) );
				vdp.push_back( make_pair(l, r) );
			}
			
			if ( !Minvody.eof() )		error("an error occurred while reading the file 'minvody.txt'");
			//if ( mnv.size() > 12 )		error("read more than 12 values. Please check the input file 'minvody.txt'");
			
			
			
						  // (    NUM1   ,   NUM2    )
			while (Sochi >> ch1 >> l >> ch2 >> r >> ch3) {
				sch.push_back( make_pair(l, r) );
				vdp.push_back( make_pair(l, r) );
			}
			
			if ( !Sochi.eof() )			error("an error occurred while reading the file 'sochi.txt'");
			//if ( sch.size() > 12 )		error("read more than 12 values. Please check the input file 'sochi.txt'");
			
			
			
						// (    NUM1   ,   NUM2    )
			while (SPB >> ch1 >> l >> ch2 >> r >> ch3) {
				spb.push_back( make_pair(l, r) );
				vdp.push_back( make_pair(l, r) );	//В таком виде требуется меньше изменений
			}
			
			if ( !SPB.eof() )			error("an error occurred while reading the file 'spb.txt'");
			//if ( spb.size() > 12 )		error("read more than 12 values. Please check the input file 'spb.txt'");
			
			
			
			double vdp_ymax {vdp[0].second};
			double vdp_ymin {vdp[0].second};
			for (auto p : vdp) {
				if (p.second < vdp_ymin)	vdp_ymin = p.second;
				if (p.second > vdp_ymax)	vdp_ymax = p.second;
			}
			
			vdp.clear();
			Minvody.close();
			Sochi.close();
			SPB.close();
			
			//------------------------------------------------------------------------------
			
			constexpr int xmax = 600;	//Размер окна
			constexpr int ymax = 600;
			
			constexpr int xlength = 500;	//Длины осей
			constexpr int ylength = 500;
			
			const int xscale = 12;								//Количество меток на оси X
			const int yscale = vdp_ymax + abs(vdp_ymin) + 4;	//Количество меток на оси Y
																							//Расстояния:
			const int xoffset = (xmax-xlength)/2;											// от левого края окна до оси y
			const int yoffset = (ymax-ylength)/2 + (ylength/yscale) * (abs(vdp_ymin) + 2);	// от нижнего края окна до оси x
			
			//------------------------------------------------------------------------------
			
			Point tl{win_centering( xmax, ymax )}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, xmax, ymax, "Глава 15. Упражнения №11");
			// окно посередине экрана
			// размер окна 600*600
			// заголовок окна: Глава 15. Упражнения №11
			
			//Point cntr{win.x_max()/2, win.y_max()/2};	//Центральная точка окна
			Point cntr{xoffset, ymax-yoffset};	//Точка пересечения осей
			
			
			Axis x {Axis::x,   cntr, xlength,   xscale,   "Месяц"};
			x.set_color(Color::dark_red);
			x.label.move(390, -17);
			x.label.set_font_size(12);
			
			Axis y {Axis::y,   Point{cntr.x, ymax - (ymax-ylength)/2}, ylength,   yscale,   "Темп., C"};
			y.set_color(Color::dark_red);
			y.label.move(-10, 0);
			y.label.set_font_size(12);
			
			win.attach(x);
			win.attach(y);
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			Group ymarks;
			int counter = vdp_ymin - 2;
			
			for (int i=0; i <= yscale; ++i)
			{
				Point p {y.point(0).x - 20,   y.point(0).y - i*(ylength/yscale) + 5};
				if (0 <= counter  &&  counter < 10)		p.x = y.point(0).x - 15;
				
				ymarks.add_shape(new Text {p, to_string(counter)});
				++counter;
			}
			
			ymarks.set_color(Color::dark_red);
			
			
			Group xmarks;
			
			for (int i=1; i <= xscale; ++i)
			{
				Point p {0, x.point(0).y + 15};
				if (i < 10)		p.x = x.point(0).x + i*(xlength/xscale) - 3;
				else			p.x = x.point(0).x + i*(xlength/xscale) - 7;
				
				xmarks.add_shape(new Text {p, to_string(i)});
			}
			
			xmarks.set_color(Color::dark_red);
			
			
			win.attach(xmarks);
			win.attach(ymarks);
			
			//------------------------------------------------------------------------------
			
			//Легенда
			Circle c1 { Point{150, ymax - 20}, 6 };
			c1.set_color(Color::dark_yellow);
			c1.set_fill_color(Color::dark_yellow);
			Text t1 { Point{160, ymax - 15}, "Минводы" };
			t1.set_color(Color::dark_yellow);
			
			Circle c2 { Point{250, ymax - 20}, 6 };
			c2.set_color(Color::dark_green);
			c2.set_fill_color(Color::dark_green);
			Text t2 { Point{260, ymax - 15}, "Сочи" };
			t2.set_color(Color::dark_green);
			
			Circle c3 { Point{320, ymax - 20}, 6 };
			c3.set_color(Color::dark_cyan);
			c3.set_fill_color(Color::dark_cyan);
			Text t3 { Point{330, ymax - 15}, "Санкт-Петербург" };
			t3.set_color(Color::dark_cyan);
			
			win.attach(c1);
			win.attach(t1);
			win.attach(c2);
			win.attach(t2);
			win.attach(c3);
			win.attach(t3);
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			//Графики по городам: Минеральные Воды (Минводы), Сочи, Санкт-Петербург (СПб)
			Open_polyline gmnv;
			gmnv.set_color(Color::dark_yellow);
			gmnv.set_style( Line_style(Line_style::solid, 2) );
			for (auto p : mnv)
				gmnv.add( Point{cntr.x + int(p.first * (xlength/xscale)),   cntr.y - int(p.second * (ylength/yscale))} );
			
			Open_polyline gsch;
			gsch.set_color(Color::dark_green);
			gsch.set_style( Line_style(Line_style::solid, 2) );
			for (auto p : sch)
				gsch.add( Point{cntr.x + int(p.first * (xlength/xscale)),   cntr.y - int(p.second * (ylength/yscale))} );
			
			Open_polyline gspb;
			gspb.set_color(Color::dark_cyan);
			gspb.set_style( Line_style(Line_style::solid, 2) );
			for (auto p : spb)
				gspb.add( Point{cntr.x + int(p.first * (xlength/xscale)),   cntr.y - int(p.second * (ylength/yscale))} );
			
			win.attach(gmnv);
			win.attach(gsch);
			win.attach(gspb);
			
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