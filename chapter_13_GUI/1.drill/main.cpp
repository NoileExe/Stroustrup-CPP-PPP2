

//#define _USE_MATH_DEFINES


#include <Simple_window.h>	//если нужна кнопка "Next"
#include <Graph.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";


//------------------------------------------------------------------------------

//НА вход:	ширина и высота будущего окна
//Возврат:	координаты левой верхней точки окна для отображения окна ровно по центру
Point win_centering (int w, int h)
{
	return Point {x_max()/2 - w/2,  y_max()/2 - h/2};
}

int main()
{
	while (true) {
		try
		{
			//-------------------------------------Задание 1-------------------------------------
			
			Point tl {win_centering(800, 1000)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 800, 1000, "Глава 13. Задания");
			// размер окна (800*1000)
			// заголовок окна: Глава 13. Задания
			
			//-------------------------------------Задание 1-------------------------------------
			//-------------------------------------Задание 2-------------------------------------
			
			int k = 100; //множитель (размер каждого деления каждой ячейки)
			Lines grid;
			grid.set_color(Color::black);
			
			for (int x = k; x <= 8*k; x += k)
				grid.add(Point{x, 0}, Point{x, 8*k});
			
			for (int y = k; y <= 8*k; y += k)
				grid.add(Point{0, y}, Point{8*k, y});
			
			win.attach(grid);
			win.wait_for_button();
			
			//-------------------------------------Задание 2-------------------------------------
			//-------------------------------------Задание 3-------------------------------------
			
			Vector_ref<Graph_lib::Rectangle> rect;
			
			for (int x = 0; x < 8*k; x += k)
				for (int y = 0; y < 8*k; y += k) {
					rect.push_back(new Graph_lib::Rectangle{Point(x,y), k, k});
					
					rect[rect.size()-1].set_color(Color::yellow);
					if ( x == y )		rect[rect.size()-1].set_fill_color(Color::red);
					
					win.attach(rect[rect.size()-1]);
				}
			
			win.wait_for_button();
			
			//-------------------------------------Задание 3-------------------------------------
			//-------------------------------------Задание 4-------------------------------------
			
			Image my_img1 {Point{2*k, 0}, "khorya_big.jpg"};
			Image my_img2 {Point{0, 2*k}, "khorya_mid.jpg"};
			Image my_img3 {Point{0, 3*k}, "khorya_mid.jpg"};
			
			win.attach(my_img1);
			win.attach(my_img2);
			win.attach(my_img3);
			
			win.wait_for_button();
			
			my_img1.set_mask(Point{172, 77}, 200, 200);
			my_img3.move(0, k);
			
			win.wait_for_button();
			
			//-------------------------------------Задание 4-------------------------------------
			//-------------------------------------Задание 5-------------------------------------
			
			for (int i = 0; i < 8; ++i)
			{
				Image walking_img {Point{0, i*k}, "mini_khorya.jpg"};
				win.attach(walking_img);
				
				for (int j = 0; j < 8; ++j) {
					win.wait_for_button();
					walking_img.move(k, 0);
				}
			}
			
			//-------------------------------------Задание 5-------------------------------------
			
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