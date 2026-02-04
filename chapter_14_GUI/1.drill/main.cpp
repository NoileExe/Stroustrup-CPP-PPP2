
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

class B1 {
public:
	virtual void vf()	{ cout << "B1::vf()"  << '\n'; }
	void f()			{ cout << "B1::f()"   << '\n'; }
	//virtual void pvf()	= 0;
};

class D1 : public B1 {
public:
	void vf()	{ cout << "D1::vf()" << '\n'; }
	void f()	{ cout << "D1::f()"  << '\n'; }
};

class D2 : public D1 {
public:
	virtual void pvf()	{ cout << "D2::pvf()" << '\n'; }
};

//------------------------------------------------------------------------------

class B2 {
public:
	virtual void pvf()	= 0;
};

class D21 : public B2 {
public:
	void pvf()	{ cout << lbl << '\n'; }

private:
	const string lbl {"D21 const string"};
};

class D22 : public B2 {
public:
	void pvf()	{ cout << num << '\n'; }

private:
	const int num {22};
};


void f(B2& bb) {
	bb.pvf();
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			B1 b;
			b.vf();
			b.f();
			//b.pvf();
			
			/*D1 d;
			d.vf();
			d.f();
			d.pvf();*/
			
			/*B1& blink {d};
			blink.vf();
			blink.f();
			blink.pvf();*/
			
			/*D2 dd;
			dd.vf();
			dd.f();
			dd.pvf();*/
			
			
			/*D21 b2d21;
			D22 b2d22;
			
			f(b2d21);
			f(b2d22);*/
			
			keep_window_open();
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