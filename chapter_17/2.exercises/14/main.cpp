
//Найдено другое решение на git'е, при котором 8 символов - не предел
//Видимо в зависимости от того в какую область памяти попадёт программа
// работа может завершится на разных этапах без ошибок и предупреждений
//Так же может попасть в область самой выполняемой программы и испортить её саму (см. скриншоты)


#include "link.h"
#include <yes_or_no.h>



const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Link norse_gods ("Thor");
			
			/*norse_gods.end()->add(new Link("Odin"));
			norse_gods.end()->add(new Link("Zeus"));
			norse_gods.end()->add(new Link("Freia"));*/
			
			//cout <<  norse_gods.end()  << '\t' <<  norse_gods.end()->value  << "\n";
			//cout << norse_gods.begin() << '\t' << norse_gods.begin()->value << "\n";
			
			norse_gods.begin()->insert(new Link("Odin"));
			norse_gods.find("Odin")->insert(new Link("Zeus")); //Также будет добавлен впёред списка, т.к. "Odin" в данной точке является первым в списке
			norse_gods.begin()->insert(new Link("Freia"));
			
			
			Link greek_gods ("Hera");
			greek_gods.begin()->insert(new Link("Athena")); 
			greek_gods.begin()->insert(new Link("Mars"));
			greek_gods.begin()->insert(new Link("Poseidon"));
			
			Link* p = greek_gods.find("Mars");
			if (p)		p->value = "Ares";
			
			
			//Перемещаем Зевса в его Пантеон (удаляя из norse_gods)
			{
				Link* p = norse_gods.find("Zeus");
				if (p) {
					p->erase();
					greek_gods.begin()->insert(new Link(p->value));
				}
			}
			
			//Отображаем оба списка:
			print_all( norse_gods );
			cout << "\n";
			
			print_all( greek_gods );
			cout << "\n";
			press_Enter_key(true);
			
			
			cout << "\n\nMOVE Ares (1)\n";
			{
				Link* p = greek_gods.find("Ares");
				if (p)		p = p->move(1);
			}
			print_all(greek_gods);
			cout << "\n";
			press_Enter_key(true);
			
			
			cout << "\nMOVE Ares (-2)\n\n";
			{
				Link* p = greek_gods.find("Ares");
				if (p)		p = p->move(-2);
			}
			print_all(greek_gods);
			cout << "\n";
			press_Enter_key(true);
			
			
			
			{
				Link* zeus = greek_gods.find("Zeus");
				
				cout << "\n\nMOVE Zeus begin to end\n";
				while( zeus != greek_gods.end() ) {
					zeus->move(1);
					
					print_all(greek_gods);
					cout << "\n";
					press_Enter_key(true);
				}
				
				cout << "\nMOVE Zeus end to begin\n";
				while( zeus != greek_gods.begin() ) {
					zeus->move(-1);
					
					print_all(greek_gods);
					cout << "\n";
					press_Enter_key(true);
				}
			}
			
			keep_window_open("~~");
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