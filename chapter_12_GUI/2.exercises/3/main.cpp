

#include <Simple_window.h>    //если нужна кнопка "Next"
#include <Graph.h>

using namespace Graph_lib;

//------------------------------------------------------------------------------

int main()
try
{
	Point tl(450, 450);		//верхний левый угол окна (расположение на экране)
	
	Simple_window win(tl, 410, 200, "Упражнение №3");
	// размер окна (410*200)
	// заголовок окна: Упражнение №3
	
	Open_polyline letter_B; //Буква "Б"
	letter_B.add(Point(125,25));	//1
	letter_B.add(Point(25,25));		//2
	letter_B.add(Point(25,175));	//3
	letter_B.add(Point(75, 175));	//4
	letter_B.add(Point(125, 165));	//5
	letter_B.add(Point(125, 115));	//6
	letter_B.add(Point(75, 105));	//7
	letter_B.add(Point(25, 105));	//8
	
	letter_B.set_color(Color::dark_yellow);
	letter_B.set_style( Line_style(Line_style::solid,2) );
	win.attach(letter_B);
	
	//------------------------------------------------------------------------------
	
	Lines letter_A; //Буква "А"
	
	letter_A.add(Point(155,175), Point(205,25));	//1
	letter_A.add(Point(205,25), Point(255,175));	//2
	letter_A.add(Point(170,125), Point(240,125));	//3
	
	letter_A.set_color(Color::dark_cyan);
	letter_A.set_style( Line_style(Line_style::solid,3) );
	win.attach(letter_A);
	
	//------------------------------------------------------------------------------
	
	Lines letter_I; //Буква "И"
	
	letter_I.add(Point(285,25), Point(285,175));	//1
	letter_I.add(Point(385,25), Point(385,175));	//2
	letter_I.add(Point(285,172), Point(385,105));	//3
	
	letter_I.set_color(Color::dark_blue);
	letter_I.set_style( Line_style(Line_style::solid,4) );
	win.attach(letter_I);
	
	
	win.wait_for_button();		// Отобразить окно!
}

catch (exception& e) {
	return 1;
}

catch (...) {
	return 2;
}