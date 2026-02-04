

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(0, 0);		//верхний левый угол окна (расположение на экране)
	
	//Simple_window win(tl, x_max(), y_max(), "Упражнение №5");
	Simple_window win(tl, Fl::w(), Fl::h(), "Упражнение №5");
	// размер окна соответствуетустановленному разрешению экрана
	// заголовок окна: Упражнение №5
	
	int rect_lnght = Fl::w() * (3/4.0);	//Длина прямоугольника  3/4 от ширины экрана (разрешение)
	int rect_hght = Fl::h() * (2/3.0);	//Высота прямоугольника 2/3 от высоты экрана (разрешение)
	
	tl.x = Fl::w()/2 - rect_lnght/2;	//Координаты прямоугольника чтобы разместить его посередине
	tl.y = Fl::h()/2 - rect_hght/2;
	
	Graph_lib::Rectangle inner_rect {tl, rect_lnght, rect_hght};
	
	inner_rect.set_color(Color::yellow);
	inner_rect.set_style( Line_style(Line_style::solid, 2) );		// Тип и толщина линий
	
	//-----------------------------------------------------------------------------------------------
	
	rect_lnght = inner_rect.width() + 20*2-16;	//Длина внешнего прямоугольника
	rect_hght = inner_rect.height() + 20*2-16;	//Высота внешнего прямоугольника
	
	tl.x = x_max()/2 - rect_lnght/2;	//Координаты прямоугольника чтобы разместить его посередине
	tl.y = y_max()/2 - rect_hght/2;		//Ф-ции аналоги Fl::w()  и  Fl::h() возвращающие в совокупе текущее разрешение экрана
	
	Graph_lib::Rectangle outer_rect {tl, rect_lnght, rect_hght};
	
	outer_rect.set_color(Color::red);
	outer_rect.set_style( Line_style(Line_style::solid, 20) );		// Тип и толщина линий
	
	
	win.attach(inner_rect);
	win.attach(outer_rect);
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}