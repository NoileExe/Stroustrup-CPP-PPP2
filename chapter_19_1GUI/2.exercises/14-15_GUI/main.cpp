


#include <yes_or_no.h>
#include "Wumpus_GUI.h"

using namespace Graph_lib;



const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Wumpus_GUI win {};		//Окно игры ровно посередине экрана
			//Wumpus_GUI win;		//Окно игры ровно посередине экрана
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