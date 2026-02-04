


#include <yes_or_no.h>
#include "game.h"



const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			constexpr int min{10};
			constexpr int max{30};
			
			srand( time(NULL) );
			while(true) {
				int cnt{0};
				while(cnt < min)		cnt = rand() % max;
				
				cout << "Map size is " << cnt << " rooms\n\n";
				Game g{cnt};
				
				while( !g.play()   &&   Y_or_N("Repeat the game?") ) {
					if(Y_or_N("With the same maze, but player and wump in other rooms?"))
						{ g.plr_relocate();	g.wump_relocate(); }	//Изменяется положение игрока и Вампуса
					
					else if(Y_or_N("With the same maze rooms count, but new maze?"))
						{ g.generate_cave(); }	//Изменяется лабиринт
						
					else g.plr_relocate();
				}
				
				if ( Y_or_N(quit_question) )	break;
			}
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
		
		
		return 0;
	}
}