#include "ha.h"
#include <console_encoding.h>


ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

int main()
{
	vector<int> v_fibo;
	
	fibonacci(50, 51, v_fibo, 1000);
	
	int over_border = v_fibo[v_fibo.size()-1];
	
	while (over_border > 0)
		++over_border;
	
	cout << "Граница int = " << --over_border << "\n\n";
	
	keep_window_open("~~");
	return EXIT_SUCCESS;
}
