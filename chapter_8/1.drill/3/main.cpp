
#include <yes_or_no.h>
#include "XYZ.h"


int main()
{
	X::var = 7;
	X::print();		//вывод var из пространства имён X
	
	using namespace Y;
	var = 9;
	print();		//вывод var из пространства имён Y
	
	{
		using Z::var;
		using Z::print;
		var = 11;
		print();	//вывод var из пространства имён Z
	}
	
	print();		//вывод var из пространства имён Y
	X::print();		//вывод var из пространства имён X
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}
