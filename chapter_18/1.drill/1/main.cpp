


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

const int num {10};
int ga[num];

int fct(int n) {
	if (n < 0)		error("negative argument fct()");
	
	if (n == 0)		return 1;
	else			return n * fct(n-1);
}


void f(int a[], int n) {
	if (n < 1)		error("incorrect count of elements in array f()");
	
	//int la[n];	//выдает ошибку, даже если создать отдульную константную переменную как выше
	int la[10];
	
	for (int i=0; i<n; ++i)		{ la[i] = a[i];	cout << la[i] << '\n'; }
	
	cout << "\n\n";
	
	int* p = new int[n];
	for (int i=0; i<n; ++i)		{ p[i] = a[i];	cout << p[i] << '\n'; }
	
	delete[] p;
}


int main()
{
	while (true) {
		try
		{
			for (int i=0; i < num; ++i)		ga[i] = pow(2, i);
			f(ga, num);
			press_Enter_key(true);
			
			int aa[num];
			for (int i=0; i < num; ++i)		aa[i] = fct(i);
			f(aa, num);
			
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