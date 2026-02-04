


#include <yes_or_no.h>
#include "vctr.h"


//Раскомментировать чтобы попробовать работу с вектором из 19 главы
//#define vector vctr


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

class Tracer {
	string constr;
	string destr;
	
public:
	Tracer() : constr{"Default constructor"}, destr{"Default destructor"}
	{ cout << constr << '\n'; }
	
	Tracer(const string c, const string d) : constr{c}, destr{d}
	{ cout << constr << '\n'; }
	
	//Копирующие конструктор и присваивание, не нужны, т.к. будут созданы компилятором по умолчанию
	Tracer(const Tracer& t) : constr{ "COPY CONSTRUCTOR " + t.constr}, destr{"COPY CONSTRUCTOR " + t.destr}
	{ cout << constr << '\n'; }
	
	Tracer& operator=(const Tracer& t) {
		constr = "COPY ASSIGMENT " + t.constr;
		destr = "COPY ASSIGMENT " + t.destr;
		cout << "COPY ASSIGMENT" << '\n';
		return *this;
	}
	
	//Перемещающие конструктор и присваивание не нужны, т.к. будут созданы компилятором по умолчанию
	//Не могут быть определены пользователем без определения пользовательских копирующих методов
	Tracer(Tracer&& t) : constr{"MOVE CONSTRUCTOR " + t.constr}, destr{"MOVE CONSTRUCTOR " + t.destr}
	{ cout << constr << '\n'; }
	
	Tracer& operator=(Tracer&& t) {
		constr = "MOVE ASSIGMENT " + t.constr;
		destr = "MOVE ASSIGMENT " + t.destr;
		cout << "MOVE ASSIGMENT" << '\n';
	}
	
	~Tracer()		{ cout << destr << '\n';	press_Enter_key(); }
};

//------------------------------------------------------------------------------

class ttt {
	Tracer t;
	
public:
	ttt(const string c, const string d) : t {c, d}		{  }
};

//------------------------------------------------------------------------------

Tracer g {"Global Tracer constructor", "Global Tracer destructor"};

void ff(Tracer t) {  }

void f() {
	cout << "\n\nGlobal\n\n";
	press_Enter_key(true);
	
	cout << "\n\n------------------------------------------------------------------------------\n\nLocal\n\n";
	Tracer l {"Local Tracer constructor", "Local Tracer destructor"};
	press_Enter_key();
	
	cout << "\n\n------------------------------------------------------------------------------\n\nDinamic mem\n\n";
	{
		Tracer* t = new Tracer {"Dinamic mem Tracer constructor", "Dinamic mem Tracer destructor"};
		press_Enter_key();
		delete t;		//Вызывает деструктор
		press_Enter_key();
	}
	
	cout << "\n\n------------------------------------------------------------------------------\n\nClass ttt member\n\n";
	{
		ttt t {"Class ttt member Tracer constructor", "Class ttt member Tracer destructor"};
		press_Enter_key();
	}
	
	cout << "\n\n------------------------------------------------------------------------------\n\nvector<Tracer> + move constructor + copy constructor\n\n";
	{
		vector<Tracer> vt;
		vt.push_back(Tracer {"vector<Tracer> 1 Tracer constructor", "vector<Tracer> 1 Tracer destructor"});
		vt.push_back(Tracer {"vector<Tracer> 2 Tracer constructor", "vector<Tracer> 2 Tracer destructor"});
		vt.push_back(Tracer {"vector<Tracer> 3 Tracer constructor", "vector<Tracer> 3 Tracer destructor"});
		press_Enter_key();
	}
	
	cout << "\n\n------------------------------------------------------------------------------\n\ncopy constructor + copy assigment\n\n";
	{
		Tracer t {g};
		press_Enter_key();
		t = l;
		press_Enter_key();
	}
	
	cout << "\n\nFNCT BOTTOM\n\n";
}

int main()
{
	while (true) {
		try
		{
			f();
			
			keep_window_open("~");
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