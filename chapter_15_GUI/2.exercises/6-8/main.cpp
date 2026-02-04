

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";


//------------------------------------------------------------------------------

void test_simple_chart (Simple_window& win);
void test_text_chart (Simple_window& win);

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
			
			Simple_window win(tl, xmax, ymax, "Глава 15. Упражнения №6-8");
			// окно посередине экрана
			// размер окна 600*600
			// заголовок окна: Глава 15. Упражнения №6-8
			
			//Point cntr{win.x_max()/2, win.y_max()/2};	//Центральная точка окна
			Point cntr{xoffset, ymax-yoffset};	//Центральная точка окна
			
			
			Axis x {Axis::x,   cntr, xlength,   yxscale,   "Рост"};
			x.set_color(Color::dark_red);
			x.label.move(380, -20);
			
			Axis y {Axis::y,   cntr, ylength,   yxscale,   "Кол-во людей"};
			y.set_color(Color::dark_red);
			
			win.attach(x);
			win.attach(y);
			//win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			test_simple_chart(win);
			test_text_chart(win);
			
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

void test_simple_chart (Simple_window& win) {
	const int xmax = win.x_max();	//Размер окна
	const int ymax = win.y_max();
	
	const int xlength = 400;	//Длины осей
	const int ylength = 400;
	
											//Расстояния:
	const int xoffset = (xmax-xlength)/2;	// от левого края окна до оси y
	const int yoffset = (ymax-ylength)/2;	// от нижнего края окна до оси x
	
	const int yxscale = 20;		//Количество меток на каждой из осей
	
	Point cntr{xoffset, ymax-yoffset};	//Центральная точка окна
	
	//------------------------------------------------------------------------------
	
	vector<double> vd {17.5, 2, 7, 14};
	Bar_chart bc {cntr, vd, xlength, yxscale, yxscale};
	bc.set_color(Color::black);
	bc.set_fill_color(Color::yellow);
	win.attach(bc);
	win.wait_for_button();
	win.detach(bc);
	
	//------------------------------------------------------------------------------
	
	vector<double> vdx {180, 170, 175, 185, 195, 190};
	vector<double> vdy { 23,  7,   9,   17,  1,   6};
	
	Bar_chart bcv {cntr,   vdx, vdy,   xlength, yxscale, yxscale};
	bcv.set_color(Color::dark_red);
	bcv.set_fill_color(Color::red);
	win.attach(bcv);
	win.wait_for_button();
	win.detach(bcv);
	
	//------------------------------------------------------------------------------
	
	vector< pair<double,double> > vdp;
	vdp.push_back( make_pair(180, 23) );
	vdp.push_back( make_pair(170, 7) );
	vdp.push_back( make_pair(175, 9) );
	vdp.push_back( make_pair(185, 17) );
	vdp.push_back( make_pair(195, 1) );
	vdp.push_back( make_pair(190, 6) );
	
	//Вектор будет отсортирован по значениям X
	Bar_chart bcp {cntr, vdp, xlength, yxscale, yxscale};
	bcp.set_color(Color::dark_yellow);
	bcp.set_fill_color(Color::yellow);
	win.attach(bcp);
	win.wait_for_button();
	
	for (int i=0; i<bcp.col_count(); ++i)
		if (i%2 == 0) {
			bcp[i].set_color(Color::dark_red);
			bcp[i].set_fill_color(Color::red);
		}
	
	win.wait_for_button();
	
	for (int i=1; i<bcp.col_count(); ++i)
		bcp[i].move(yxscale*i, 0);
	
	win.wait_for_button();
	win.detach(bcp);
}


void test_text_chart (Simple_window& win) {
	const int xmax = win.x_max();	//Размер окна
	const int ymax = win.y_max();
	
	const int xlength = 400;		//Длины осей
	const int ylength = 400;
	
											//Расстояния:
	const int xoffset = (xmax-xlength)/2;	// от левого края окна до оси y
	const int yoffset = (ymax-ylength)/2;	// от нижнего края окна до оси x
	
	const int yxscale = 20;		//Количество меток на каждой из осей
	
	Point cntr{xoffset, ymax-yoffset};	//Центральная точка окна
	
	//------------------------------------------------------------------------------
	
	//Открываем файл ввода
	cout << "Please enter name of input file: ";
	
	string iname;
	cin >> iname;
	
	ifstream ifs { iname };
	if (!ifs)		error("the specified file cannot be opened (" + iname + ")");
	
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);	// Генерация исключения в случа е состояния bad ()
	
	//------------------------------------------------------------------------------
	
	vector< pair<double,double> > vdp;
	double l, r;
	char ch1, ch2, ch3;
	
				// (    NUM1   ,   NUM2    )
	while (ifs >> ch1 >> l >> ch2 >> r >> ch3)
		vdp.push_back( make_pair(l, r) );
	
	if ( !ifs.eof() )		error("an error occurred while reading the file", iname);
	
	Bar_chart_txt bct {cntr, vdp, xlength, yxscale, yxscale};
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
	
	for (int i=1; i<bct.col_count(); ++i) {
		bct[i].move(yxscale*i, 0);
		bct.mark(i, 'u').move(yxscale*i, 0);
		bct.mark(i, 'd').move(yxscale*i, 0);
	}
	
	for (int i=0; i < bct.col_count(); ++i) {
		bct.mark(i, 'u').set_color(Color::black);
		if (bct.mark(i, 'u').label().size() == 1)	bct.mark(i, 'u').move(2,0);
		else										bct.mark(i, 'u').move(-1,0);
		
		bct.mark(i, 'd').set_color(Color::dark_red);
		bct.mark(i, 'd').move(-7,0);
	}
	
	bct.mark(5, 'u').set_label("one");
	bct.mark(5, 'u').move(-7,0);
	
	
	win.wait_for_button();
	
	win.detach(bct);
}

//------------------------------------------------------------------------------