

#include <yes_or_no.h>
#include "link.h"


//#define Link Link<God>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Link<God>* gods = new Link<God> ( God{"Thor", "Norse", "Thor's vehicle", "Thor's weapon"} );
			gods->add(new Link<God> ( God{"Odin", "Norse", "Eight-legged flying horse Sleipner", "Spear Gungnir"} ));
			gods->add(new Link<God> ( God{"Freia", "Norse", "Freia's vehicle", "Freia's weapon"} ));
			
			gods->add(new Link<God> ( God{"Hera", "Greek", "Hera's vehicle", "Hera's weapon"} ));
			gods->add(new Link<God> ( God{"Athena", "Greek", "Athena's vehicle", "Athena's weapon"} ));
			gods->add(new Link<God> ( God{"Ares", "Greek", "Ares's vehicle", "Ares's weapon"} ));
			gods->add(new Link<God> ( God{"Poseidon", "Greek", "Poseidon's vehicle", "Poseidon's weapon"} ));
			gods->add(new Link<God> ( God{"Zeus", "Greek", "", "Lightning"} ));
			
			gods->add(new Link<God> ( God{"Juno", "Roman", "Juno's vehicle", "Juno's weapon"} ));
			gods->add(new Link<God> ( God{"Jupiter", "Roman", "Jupiter's vehicle", "Jupiter's weapon"} ));
			gods->add(new Link<God> ( God{"Minerva", "Roman", "Minerva's vehicle", "Minerva's weapon"} ));
			gods->add(new Link<God> ( God{"Venus", "Roman", "Venus's vehicle", "Venus's weapon"} ));
			gods->add(new Link<God> ( God{"Mars", "Roman", "Mars's vehicle", "Mars's weapon"} ));
			//gods->add(new Link<God> ( God{"Jupiter", "Roman", "Jupiter's vehicle", "Jupiter's weapon"} ));
			gods->add(new Link<God> ( God{"Ops", "Roman", "Ops's vehicle", "Ops's weapon"} ));
			gods->add(new Link<God> ( God{"Saturn", "Roman", "Saturn's vehicle", "Saturn's weapon"} ));
			
			print_all(gods);
			cout << "\n\n";
			
			press_Enter_key(true);
			
			//Возвращаем Юпитера на место
			{
				Link<God>* p = gods->find("Jupiter");
				Link<God>* bckp = gods;
				if (p==gods)		gods = p->next();
				//Элемент списка найден, но смещение невозможно
				if ( p  &&  !(p->move(3)) )		gods = bckp;
				
				print_all(gods);
				cout << "\n\n";
			}
			
			press_Enter_key();
			
			//------------------------------------------------------------------------------
			
			Link<God>* norse_gods {nullptr};
			Link<God>* greek_gods {nullptr};
			Link<God>* roman_gods {nullptr};
			
			for(Link<God>* p = gods; p != nullptr; p = p->next())
			{
				if (p->value().mythology == "Norse") {
					if (!norse_gods)	norse_gods = new Link<God> (p->value());
					else {
						Link<God>* pn = norse_gods->add_ordered( new Link<God> (p->value()) );
						if (pn->next() == norse_gods)		norse_gods = pn;
					}
				}
				
				if (p->value().mythology == "Greek") {
					if (!greek_gods)	greek_gods = new Link<God> (p->value());
					else {
						Link<God>* pg = greek_gods->add_ordered( new Link<God> (p->value()) );
						if (pg->next() == greek_gods)		greek_gods = pg;
					}
				}
				
				if (p->value().mythology == "Roman") {
					if (!roman_gods)	roman_gods = new Link<God> (p->value());
					else {
						Link<God>* pr = roman_gods->add_ordered( new Link<God> (p->value()) );
						if (pr->next() == roman_gods)		roman_gods = pr;
					}
				}
				
				//p = p->next();
			}
			
			print_all(norse_gods);		cout << "\n\n";
			print_all(greek_gods);		cout << "\n\n";
			print_all(roman_gods);		cout << "\n\n";
			
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