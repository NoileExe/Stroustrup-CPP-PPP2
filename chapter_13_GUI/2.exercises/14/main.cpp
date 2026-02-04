

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
			Point tl{win_centering(500, 500)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 500, 500, "Глава 13. Упражнение №14");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 13. Упражнение №14
			
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			//гипотенуза меньших треугольников с равными катетами и одновременно длина двух сторон правильного восьмиугольника из 8 прямоугольных треугольников
			int side = round( sqrt(100*100 + 100*100) );
			
			//высота меньших треугольников с равными катетами
			int h = round(  sqrt(100*100 - pow(side,2)/4)  );
			
			Vector_ref<Right_triangle> rts;
			
			rts.push_back(new Right_triangle {Point{cntr.x, cntr.y-side/2-1},				100, 100, 45}); //верхний средний треугольник
			rts[rts.size()-1].set_color( Color(Color::green, Color::invisible) );
			rts[rts.size()-1].set_fill_color(Color::green);
			//rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
			win.attach( rts[rts.size()-1] );
			win.wait_for_button();
			win.detach( rts[rts.size()-1] );
			
			rts.push_back(new Right_triangle {Point{cntr.x-side/2-1, cntr.y-side/2-h-1},	100, 100, 225}); //верхний левый
			rts[rts.size()-1].set_color( Color(Color::red, Color::invisible) );
			rts[rts.size()-1].set_fill_color(Color::red);
			//rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
			win.attach( rts[rts.size()-1] );
			win.wait_for_button();
			win.detach( rts[rts.size()-1] );
			
			rts.push_back(new Right_triangle {Point{cntr.x+side/2+1, cntr.y-side/2-h-1},	100, 100, 225}); //верхний правый
			rts[rts.size()-1].set_color( Color(Color::yellow, Color::invisible) );
			rts[rts.size()-1].set_fill_color(Color::yellow);
			//rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
			win.attach( rts[rts.size()-1] );
			win.wait_for_button();
			win.detach( rts[rts.size()-1] );
			
			
			
			rts.push_back(new Right_triangle {Point{cntr.x-side-1, cntr.y+side/2},	2*side, side});			//средний левый без угла поворота
			rts[rts.size()-1].set_color( Color(Color::blue, Color::invisible) );
			rts[rts.size()-1].set_fill_color(Color::blue);
			//rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
			win.attach( rts[rts.size()-1] );
			win.wait_for_button();
			win.detach( rts[rts.size()-1] );
			
			rts.push_back(new Right_triangle {Point{cntr.x+side+1, cntr.y-side/2},	2*side, side, 180});	//средний правый
			rts[rts.size()-1].set_color( Color(Color::magenta, Color::invisible) );
			rts[rts.size()-1].set_fill_color(Color::magenta);
			//rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
			win.attach( rts[rts.size()-1] );
			win.wait_for_button();
			win.detach( rts[rts.size()-1] );
			
			
			
			rts.push_back(new Right_triangle {Point{cntr.x, cntr.y+side/2+1},				100, 100, 225}); //нижний средний треугольник
			rts[rts.size()-1].set_color( Color(Color::white, Color::invisible) );
			rts[rts.size()-1].set_fill_color(Color::white);
			//rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
			win.attach( rts[rts.size()-1] );
			win.wait_for_button();
			win.detach( rts[rts.size()-1] );
			
			rts.push_back(new Right_triangle {Point{cntr.x-side/2-1, cntr.y+side/2+h+1},	100, 100, 45}); //нижний левый
			rts[rts.size()-1].set_color( Color(Color::black, Color::invisible) );
			rts[rts.size()-1].set_fill_color(Color::black);
			//rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
			win.attach( rts[rts.size()-1] );
			win.wait_for_button();
			win.detach( rts[rts.size()-1] );
			
			rts.push_back(new Right_triangle {Point{cntr.x+side/2+1, cntr.y+side/2+h+1},	100, 100, 45}); //нижний правый
			rts[rts.size()-1].set_color( Color(Color::cyan, Color::invisible) );
			rts[rts.size()-1].set_fill_color(Color::cyan);
			//rts[rts.size()-1].set_style( Line_style(Line_style::solid, 2) );
			win.attach( rts[rts.size()-1] );
			win.wait_for_button();
			win.detach( rts[rts.size()-1] );
			
			
			for (int i = 0; i<rts.size(); ++i)
				win.attach( rts[i] );
			
			
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