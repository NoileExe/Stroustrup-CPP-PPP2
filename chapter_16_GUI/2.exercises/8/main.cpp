

#include <yes_or_no.h>
#include "My_window.h"

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Converter_window win { "change_rate.txt" };		// указывается путь к файлу с курсами валют
			
			win.wait_for_button();
			win.set_label("QUIT для выхода");
			
			return gui_main();
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