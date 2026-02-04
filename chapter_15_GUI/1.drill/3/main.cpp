

#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

struct Person {
	Person () : fn{""}, sn{""}, a{0} { }
	
	Person (string f, string s, int i) : fn{f}, sn{s}, a{i}
	{
		if (a < 0  ||  150 <= a)		error("Person object init: bad age (" + to_string(a) + ")");
		
		for (auto c : f)
			for (auto b : ";:\"'[]*&^%$#@!")
				if (c == b)		error("Person object init: bad symbol in first name (" + string(1,c) + ")");
		
		for (auto c : s)
			for (auto b : ";:\"'[]*&^%$#@!")
				if (c == b)		error("Person object init: bad symbol in second name (" + string(1,c) + ")");
	}
	
	string first_name()  const { return fn; }
	string second_name() const { return sn; }
	int age()			 const { return a; }
	
private:
	string fn;
	string sn;
	int a;
};


ostream& operator<<(ostream& ost, const Person& p)
{
	ost << p.first_name() << ' ' << p.second_name() << " - " << p.age();
	return ost;
}

istream& operator>>(istream& ist, Person& p)
{
	string first_name;
	string second_name;
	int age;
	
	ist >> first_name >> second_name >> age;
	
	if (!ist) {
		ist.clear(ios_base::failbit);
		return ist;
	}
	
	//Конструктор проверит ошибки ввода
	Person pp {first_name, second_name, age};
	p = pp;
	return ist;
}


int main()
{
	while (true) {
		try
		{
			Person g {"Goofy", "", 63}; //{"Goofy", "", 173}
			
			cout << '\n' << g.first_name() << ' ' << g.second_name() << ' ' << g.age() << '\n';
			cout << '\n' << g.first_name() << ' ' << g.age() << '\n';
			press_Enter_key(true);
			
			
			//;a:b"c'd[e]f*g&h^g%k$l#m@n!o,.
			
			/*Person op;
			
			cout << "\n\n\nPlease enter name and age in next format:\nFIRST_NAME SECOND_NAME AGE\n";
			cin >> op;
			if (!cin)	error("bad enter of Person object");
			cout << "\nObject Person: " << op << "\n\n";*/
			
			
			vector<Person> vp;
			cout << "\n\n\nPlease enter name and age in next format or CTRL+Z to exit:\nFIRST_NAME SECOND_NAME AGE\n";
			
			for (Person p; cin >> p; ) {
				vp.push_back(p);
				cout << "\n\n\nPlease enter name and age in next format or CTRL+Z to exit:\nFIRST_NAME SECOND_NAME AGE\n";
			}
			
			if (vp.size() == 0)		error("empty vector<Person> vp");
			for (Person p : vp)
				cout << "\nObject Person: " << p << "\n\n";
			
			
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

//------------------------------------------------------------------------------