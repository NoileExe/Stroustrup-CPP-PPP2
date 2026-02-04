

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
			vector<double> vde;					//пустой вектор
			Vector_iterator vie {vde};
			print(vie);
			
			press_Enter_key(true);
			
			vector<double> vd {3.7, 13.4};		//вектор с неколькими значениями
			vd.push_back(100);
			Vector_iterator vi {vd};
			print(vi);
			
			press_Enter_key(true);
			
			list<double> lde;
			List_iterator lie {lde};
			print(lie);
			
			press_Enter_key(true);
			
			list<double> ld = {2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
			ld.push_front(1.1);
			ld.push_back(8.8);
			ld.push_front(0);
			List_iterator li {ld};
			print(li);
			
			press_Enter_key();
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