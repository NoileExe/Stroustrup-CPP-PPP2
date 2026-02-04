

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(Fl::w()/2, 0);		//верхний левый угол окна (расположение на экране)
	
	//Simple_window win(tl, Fl::w(), Fl::h(), "Упражнение №6");
	//Simple_window win(tl, x_max(), y_max(), "Упражнение №6");
	Simple_window win(tl, y_max(), x_max(), "Упражнение №6");
	// размер окна соответствует установленному разрешению экрана (преднамеренно перепутаны местами длина и ширина)
	// заголовок окна: Упражнение №6
	
	int rect_lnght = Fl::w() / 2;	//Длина прямоугольника  половина от ширины экрана (разрешение)
	int rect_hght = Fl::h() / 2;	//Высота прямоугольника половина от высоты экрана (разрешение)
	
	Graph_lib::Rectangle rect {Point(25, -25), rect_lnght, rect_hght};
	//верхний левый угол прямоугольник за пределами области видимости экрана
	
	rect.set_color(Color::blue);
	rect.set_style( Line_style(Line_style::solid, 5) );		// Тип и толщина линий
	
	win.attach(rect);
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}