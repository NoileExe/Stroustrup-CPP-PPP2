

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(450, 450);		//верхний левый угол окна (расположение на экране)
	
	Simple_window win(tl, 350, 350, "Упражнение №4");
	// размер окна (350*350)
	// заголовок окна: Упражнение №4
	
	Vector_ref<Graph_lib::Rectangle> rctngls;
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			int ax = 25+100*j;
			int ay = 25+100*i;
			
			rctngls.push_back(new Graph_lib::Rectangle (Point(ax, ay), 100, 100) );
			
			int indx = rctngls.size()-1;
			
			rctngls[indx].set_style( Line_style(Line_style::solid, 2) );		// Тип и толщина линий
			
			// цвет внутри прямоугольника
			if ( (indx+1)%2 == 0 )		rctngls[indx].set_fill_color(Color::white);
			else						rctngls[indx].set_fill_color(Color::red);
			
			win.attach( rctngls[indx] );
		}
	}
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}