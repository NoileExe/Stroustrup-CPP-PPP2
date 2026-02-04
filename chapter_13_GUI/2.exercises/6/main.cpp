

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void build_scheme(Simple_window& win);

int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(600, 300)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 600, 300, "Глава 13. Упражнение №6");
			// окно посередине экрана
			// размер окна (600*300)
			// заголовок окна: Глава 13. Упражнение №6
			
			build_scheme(win);
			
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

void txtbox_one_style(TXTBox& t) {
	t.set_color(Color::black);
	t.set_style( Line_style(Line_style::solid, 2) );
	t.set_fill_color(Color::white);
}

void arrow_one_style(Arrow& a) {
	a.set_color(Color::black);
	a.set_style( Line_style(Line_style::solid, 1) );
}

void build_scheme(Simple_window& win) {
	Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
	
	TXTBox tb_window		{Point{112, 40}, 80, "Window"};
	txtbox_one_style(tb_window);
	
	TXTBox tb_line_style	{Point{e(tb_window).x+40, 40}, 90, "Line_style"};
	txtbox_one_style(tb_line_style);
	
	TXTBox tb_color			{Point{e(tb_line_style).x+40, 40}, 65, "Color"};
	txtbox_one_style(tb_color);
	
	//----------------------------------------------------------------
	
	TXTBox tb_simpwin	{Point{90, cntr.y}, 125, "Simple_window"};
	txtbox_one_style(tb_simpwin);
	
	TXTBox tb_shape		{Point{e(tb_simpwin).x+60, cntr.y-15}, 70, "Shape"};
	txtbox_one_style(tb_shape);
	
	TXTBox tb_point		{Point{e(tb_shape).x+60, cntr.y}, 65, "Point"};
	txtbox_one_style(tb_point);
	
	//----------------------------------------------------------------
	
	TXTBox tb_line		{Point{30, win.y_max()-40}, 60, "Line"};
	txtbox_one_style(tb_line);
	
	TXTBox tb_lines		{Point{e(tb_line).x+10, win.y_max()-40}, 65, "Lines"};
	txtbox_one_style(tb_lines);
	
	TXTBox tb_poly		{Point{e(tb_lines).x+10, win.y_max()-40}, 75, "Polygon"};
	txtbox_one_style(tb_poly);
	
	TXTBox tb_axis		{Point{e(tb_poly).x+10, win.y_max()-40}, 60, "Axis"};
	txtbox_one_style(tb_axis);
	
	TXTBox tb_rect		{Point{e(tb_axis).x+10, win.y_max()-40}, 90, "Rectangle"};
	txtbox_one_style(tb_rect);
	
	TXTBox tb_text		{Point{e(tb_rect).x+10, win.y_max()-40}, 60, "Text"};
	txtbox_one_style(tb_text);
	
	TXTBox tb_img		{Point{e(tb_text).x+10, win.y_max()-40}, 70, "Image"};
	txtbox_one_style(tb_img);
	
	
	win.attach( tb_window );
	win.attach( tb_line_style );
	win.attach( tb_color );
	win.attach( tb_simpwin );
	win.attach( tb_shape );
	win.attach( tb_point );
	win.attach( tb_line );
	win.attach( tb_lines );
	win.attach( tb_poly );
	win.attach( tb_axis );
	win.attach( tb_rect );
	win.attach( tb_text );
	win.attach( tb_img );
	
	//----------------------------------------------------------------
	
	Arrow a_simpwin		{n(tb_simpwin), s(tb_window)};
	arrow_one_style(a_simpwin);
	
	Arrow a_line		{n(tb_line), Point{sw(tb_shape).x+5, s(tb_shape).y}};
	arrow_one_style(a_line);
	
	Arrow a_lines		{n(tb_lines), Point{sw(tb_shape).x+18, s(tb_shape).y+1}};
	arrow_one_style(a_lines);
	
	Arrow a_poly		{n(tb_poly), Point{s(tb_shape).x-7, s(tb_shape).y}};
	arrow_one_style(a_poly);
	
	Arrow a_axis		{n(tb_axis), Point{s(tb_shape).x, s(tb_shape).y}};
	arrow_one_style(a_axis);
	
	Arrow a_rect		{n(tb_rect), Point{s(tb_shape).x+7, s(tb_shape).y}};
	arrow_one_style(a_rect);
	
	Arrow a_text		{n(tb_text), Point{se(tb_shape).x-18, s(tb_shape).y+1}};
	arrow_one_style(a_text);
	
	Arrow a_img			{n(tb_img), Point{se(tb_shape).x-5, s(tb_shape).y}};
	arrow_one_style(a_img);
	
	
	win.attach( a_simpwin );
	win.attach( a_line );
	win.attach( a_lines );
	win.attach( a_poly );
	win.attach( a_axis );
	win.attach( a_rect );
	win.attach( a_text );
	win.attach( a_img );
	
	win.wait_for_button();
	
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	
	win.detach( tb_window );
	win.detach( tb_line_style );
	win.detach( tb_color );
	win.detach( tb_simpwin );
	win.detach( tb_shape );
	win.detach( tb_point );
	win.detach( tb_line );
	win.detach( tb_lines );
	win.detach( tb_poly );
	win.detach( tb_axis );
	win.detach( tb_rect );
	win.detach( tb_text );
	win.detach( tb_img );
	
	win.detach( a_simpwin );
	win.detach( a_line );
	win.detach( a_lines );
	win.detach( a_poly );
	win.detach( a_axis );
	win.detach( a_rect );
	win.detach( a_text );
	win.detach( a_img );
}