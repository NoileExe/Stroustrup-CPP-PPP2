

#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

struct X {
	int val;
	
	void out(const string& s, int nv) {
		cerr << this << "->" << s << ": " << val << " (" << nv << ")\n";
	}
	X() { out("X()", 0);	val=0; }	//Конструктор по умолчанию
	X(int v) { val=v;	out("X(int)", v); }
	
	//Копирующий конструктор
	X(const X& x) { val=x.val;		out("X(X&)", x.val); }
	
	//Копирующее присваивание
	X& operator=(const X& a) {
		out("X::operator=()", a.val);
		val=a.val;		return *this;
	}
	
	~X() { out("~X()", 0); }	//Деструктор
};



X glob(2);		//Глобальная переменная

X copy(X a) { return a; }
X copy2(X a) { X aa = a;	return aa; }
X& ref_to(X& a) { return a; }
X* make(int i) { X a(i);	return new X(a); }

struct XX {
	X a;
	X b;
};



int main()
{
	while (true) {
		try
		{
			X loc {4};				//Локальная переменная
			X loc2 {loc};			//Копирующий конструктор
			loc = X{5};				//Копирующее присваивание
			loc2 = copy(loc);		//Передача по значению и возврат
			loc2 = copy2(loc);
			X loc3 {6};
			X& r = ref_to(loc);		//Передача по ссылке и возврат
			delete make(7);
			delete make(8);
			vector<X> v(4);			//Значения по умолчанию
			XX loc4;
			X* p = new X{9};		//X в динамической памяти
			delete p;
			X* pp = new X[5];		//Массив X в динамической памяти
			delete[] pp;
			
			
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