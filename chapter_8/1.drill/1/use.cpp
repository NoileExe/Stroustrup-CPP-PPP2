
#include "my.h"
#include <iostream>

int foo;

void prog_pause()
{
	char cc;
	std::cin >> cc;
}

int main()
{
	foo = 7;
	print_foo();
	print(99);
	
	prog_pause();
	//return 0;
}
