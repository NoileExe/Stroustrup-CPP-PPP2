#include "vectors_int.h"
#include <console_encoding.h>


ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

int main()
{
	vector<int> numnums;
	string str;
	
	for (int i = 0;  i < 6; ++i)
		numnums.push_back(i+1);
	
	str = "Вектор до сортировки";
	print_vector(numnums, str);
	
	//numnums = vector_int1(numnums);
	str = "Вектор после vector_int1";
	print_vector(vector_int1(numnums), str);
	
	vector_int2(numnums);
	str = "Вектор после vector_int2";
	print_vector(numnums, str);
	
	keep_window_open("~~");
	return EXIT_SUCCESS;
}
