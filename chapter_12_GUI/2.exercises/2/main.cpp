

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(100, 100);		//верхний левый угол окна
	
	Simple_window win(tl, 150, 150, "Упражнение №1");
	// размер окна (150*150)
	// заголовок окна: Упражнение №1
	
	Graph_lib::Rectangle rctngl {Point(25, 60), 100, 30};
	
	rctngl.set_color(Color::magenta);
	rctngl.set_style( Line_style(Line_style::solid, 2) );
	
	Text txt {Point{45, 80}, "Howdy!"};
	txt.set_font(Graph_lib::Font::times_bold);
	txt.set_font_size(18);
	
	win.attach(rctngl);
	win.attach(txt);
	
	win.set_label("Упражнение №2");
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}