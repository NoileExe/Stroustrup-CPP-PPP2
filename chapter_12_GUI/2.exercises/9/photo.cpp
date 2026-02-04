

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(x_max() / 2 - 450/2, y_max() / 2 - 350/2);		//верхний левый угол окна (расположение на экране)
	
	Simple_window win(tl, 340, 450, "Johnny Depp (Джонни Депп)");
	// размер окна (340*450) т.к. картинка 260*390
	// заголовок окна: Johnny Depp (Джонни Депп)
	
	Text txt {Point(42, 35), "Johnny Depp (Джонни Депп)"};
	txt.set_font(Graph_lib::Font::times_bold);
	txt.set_font_size(20);
	txt.set_color(Color::black);
	
	Image img {Point(40, 50), "photo.jpg"};
	
	win.attach(txt);
	win.attach(img);
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}