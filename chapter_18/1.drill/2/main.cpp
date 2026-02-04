


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

vector<int> gv(10);

int fct(int n) {
	if (n < 0)		error("negative argument fct()");
	
	if (n == 0)		return 1;
	else			return n * fct(n-1);
}


void f(vector<int> v) {
	if (v.size() == 0)		error("empty vector in argument f()");
	
	vector<int> lv( v.size() );
	for (int i=0; i < lv.size(); ++i)		{ lv[i] = gv[i];		cout << lv[i] << '\n'; }
	
	cout << "\n\n";
	
	vector<int> lv2 {v};
	for (int i=0; i < lv2.size(); ++i)		cout << lv2[i] << '\n';
}


int main()
{
	while (true) {
		try
		{
			for (int i=0; i < gv.size(); ++i)		gv[i] = int ( pow(2, i) );
			f(gv);
			press_Enter_key(true);
			
			vector<int> vv;
			for (int i=0; i < 10; ++i)		vv.push_back( fct(i) );
			f(vv);
			
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