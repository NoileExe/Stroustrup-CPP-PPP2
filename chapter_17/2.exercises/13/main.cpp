
#include "link.h"
#include <yes_or_no.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			//Добавление каждого нового элемента в начало списка
			/*Link* gods = new Link ( God{"Freia", "Norse", "Freia's vehicle", "Freia's weapon"} );
			gods = gods->insert(new Link ( God{"Odin", "Norse", "Eight-legged flying horse Sleipner", "Spear Gungnir"} ));
			gods = gods->insert(new Link ( God{"Thor", "Norse", "Thor's vehicle", "Thor's weapon"} ));

			gods = gods->insert(new Link ( God{"Zeus", "Greek", "", "Lightning"} ));
			gods = gods->insert(new Link ( God{"Poseidon", "Greek", "Poseidon's vehicle", "Poseidon's weapon"} ));
			gods = gods->insert(new Link ( God{"Ares", "Greek", "Ares's vehicle", "Ares's weapon"} ));
			gods = gods->insert(new Link ( God{"Athena", "Greek", "Athena's vehicle", "Athena's weapon"} ));
			gods = gods->insert(new Link ( God{"Hera", "Greek", "Hera's vehicle", "Hera's weapon"} ));

			gods = gods->insert(new Link ( God{"Saturn", "Roman", "Saturn's vehicle", "Saturn's weapon"} ));
			gods = gods->insert(new Link ( God{"Ops", "Roman", "Ops's vehicle", "Ops's weapon"} ));
			//gods = gods->insert(new Link ( God{"Jupiter", "Roman", "Jupiter's vehicle", "Jupiter's weapon"} ));
			gods = gods->insert(new Link ( God{"Mars", "Roman", "Mars's vehicle", "Mars's weapon"} ));
			gods = gods->insert(new Link ( God{"Venus", "Roman", "Venus's vehicle", "Venus's weapon"} ));
			gods = gods->insert(new Link ( God{"Minerva", "Roman", "Minerva's vehicle", "Minerva's weapon"} ));
			gods = gods->insert(new Link ( God{"Jupiter", "Roman", "Jupiter's vehicle", "Jupiter's weapon"} ));
			gods = gods->insert(new Link ( God{"Juno", "Roman", "Juno's vehicle", "Juno's weapon"} ));*/
			
			
			//Добавление каждого нового элемента в конец списка
			Link* gods = new Link ( God{"Thor", "Norse", "Thor's vehicle", "Thor's weapon"} );
			Link* p = gods->add(new Link ( God{"Odin", "Norse", "Eight-legged flying horse Sleipner", "Spear Gungnir"} ));
			p = p->add(new Link ( God{"Freia", "Norse", "Freia's vehicle", "Freia's weapon"} ));
			
			p = p->add(new Link ( God{"Hera", "Greek", "Hera's vehicle", "Hera's weapon"} ));
			p = p->add(new Link ( God{"Athena", "Greek", "Athena's vehicle", "Athena's weapon"} ));
			p = p->add(new Link ( God{"Ares", "Greek", "Ares's vehicle", "Ares's weapon"} ));
			p = p->add(new Link ( God{"Poseidon", "Greek", "Poseidon's vehicle", "Poseidon's weapon"} ));
			p = p->add(new Link ( God{"Zeus", "Greek", "", "Lightning"} ));
			
			p = p->add(new Link ( God{"Juno", "Roman", "Juno's vehicle", "Juno's weapon"} ));
			p = p->add(new Link ( God{"Jupiter", "Roman", "Jupiter's vehicle", "Jupiter's weapon"} ));
			p = p->add(new Link ( God{"Minerva", "Roman", "Minerva's vehicle", "Minerva's weapon"} ));
			p = p->add(new Link ( God{"Venus", "Roman", "Venus's vehicle", "Venus's weapon"} ));
			p = p->add(new Link ( God{"Mars", "Roman", "Mars's vehicle", "Mars's weapon"} ));
			//p = p->add(new Link ( God{"Jupiter", "Roman", "Jupiter's vehicle", "Jupiter's weapon"} ));
			p = p->add(new Link ( God{"Ops", "Roman", "Ops's vehicle", "Ops's weapon"} ));
			p = p->add(new Link ( God{"Saturn", "Roman", "Saturn's vehicle", "Saturn's weapon"} ));
			
			print_all(gods);
			cout << "\n\n";
			
			press_Enter_key(true);
			
			//Возвращаем Юпитера на место
			{
				Link* p = gods->find("Jupiter");
				Link* bckp = gods;
				if (p==gods)		gods = p->next();
				//Элемент списка найден, но смещение невозможно
				if ( p  &&  !(p->move(3)) )		gods = bckp;
				
				print_all(gods);
				cout << "\n\n";
			}
			
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			
			Link* norse_gods {nullptr};
			Link* greek_gods {nullptr};
			Link* roman_gods {nullptr};
			
			p = gods;
			while (p) {
				if (p->value.mythology == "Norse") {
					if (!norse_gods)	norse_gods = new Link (p->value);
					else {
						Link* pn = norse_gods->add_ordered( new Link (p->value) );
						if (pn->next() == norse_gods)		norse_gods = pn;
					}
				}
				
				if (p->value.mythology == "Greek") {
					if (!greek_gods)	greek_gods = new Link (p->value);
					else {
						Link* pg = greek_gods->add_ordered( new Link (p->value) );
						if (pg->next() == greek_gods)		greek_gods = pg;
					}
				}
				
				if (p->value.mythology == "Roman") {
					if (!roman_gods)	roman_gods = new Link (p->value);
					else {
						Link* pr = roman_gods->add_ordered( new Link (p->value) );
						if (pr->next() == roman_gods)		roman_gods = pr;
					}
				}
				
				p = p->next();
			}
			
			print_all(norse_gods); cout << "\n\n";
			print_all(greek_gods); cout << "\n\n";
			print_all(roman_gods); cout << "\n\n";
			
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