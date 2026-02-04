

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
			Point tl{win_centering( 800, 700 )}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 800, 700, "Глава 14. Упражнение №17");
			// окно посередине экрана
			// размер окна 800*700
			// заголовок окна: Глава 14. Упражнение №17
			
			Point p {30, win.y_max()/2-25/2}; //25 - высота TXTBox'ов
			
			Scheme_tree st {p, 150, 25, "exception <exception>"};
			st.set_color(Color::black);
			st.set_fill_color(Color::white);
			st.set_style( Line_style(Line_style::dash, 3) );
			
			win.attach( st );
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			vector<string> l21 {"bad_cast <typeinfo>", "bad_typeid <typeinfo>", "logic_error <stdexcept>", "bad_alloc <new>", "ios_base::failure <ios>"};
			p.x = st.point(0).x + st.width() + 100;
			p.y = 25;
			st.add_childs(p, 170, l21);
			
			vector<string> l22 {"runtime_error <stdexcept>", "bad_exception <exception>"};
			p.y = st[st.childs_size()-1].point(0).y + st.height() + st.y_inc;
			st.add_childs(p, 170, l22);
			
			win.wait_for_button();
			
			//------------------------------------------------------------------------------
			
			int lerr {0};	//Индексы дочерних узлов
			int rerr {0};
			
			for (int i=0; i<st.childs_size(); ++i) {
				if (st[i].label() == l21[2]) //"logic_error <stdexcept>"
					lerr = i;
				
				if (st[i].label() == l22[0]) //"runtime_error <stdexcept>"
					rerr = i;
			}
			
			
			vector<string> le31 {"domain_error <stdexception>", "invalid_argument <stdexcept>", "length_error <stdexcept>", "out_of_range <stdexcept>"};
			p.x = st[0].point(0).x + st[st.childs_size()-1].width() + 100;
			//p.x = st[0].point(0).x + st[lerr].width() + 30;
			p.y = 25;
			st[lerr].add_childs(p, 200, le31);
			
			vector<string> re32 {"range_error <stdexcept>", "overflow_error <stdexcept>", "underflow_error <stdexcept>"};
			//p.x = st[0].point(0).x + st[st.childs_size()-1].width() + 30;
			p.y = st[lerr][st[lerr].childs_size()-1].point(0).y + st.height() + 2*st.y_inc;
			st[rerr].add_childs(p, 200, re32);
			
			//------------------------------------------------------------------------------
			
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