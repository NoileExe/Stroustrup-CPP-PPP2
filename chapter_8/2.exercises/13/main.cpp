#include <std_lib_facilities.h>

void intprint (const int);

int main() //int argc, char *argv[]
{
	int p = 888;
	intprint(p);
	intprint(7);
	
	keep_window_open("~~");
	return EXIT_SUCCESS;
}

void intprint (const int arg_const)
{
	int f = arg_const+1;
	cout << "f = arg_const + 1 - " << f << endl;
	cout << "arg_const = " << arg_const << endl;
	//cout << "++arg_const - " << ++arg_const << endl;
}
