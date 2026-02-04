
#include <yes_or_no.h>
#include "My_window.h"

using namespace Graph_lib;


//const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << HELP_INSTR << "\n\n";	//ВЫВОД ИНСТРУКЦИИ только в поток cout
			press_Enter_key(true);
			
			Calculator_window win {  };
			
			win.wait_for_button();
			win.set_label("Нажмите QUIT для выхода");
			
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