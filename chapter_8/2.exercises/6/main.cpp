#include "vectors_int_str.h"
#include <console_encoding.h>


ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора


int main()
{
	vector<string> vstr;
	string str;
	char ch = ' ';
	
	for (int i = 0;  i < 7; ++i) {
		ch = 'a' + i;
		vstr.push_back(to_string(ch));
	}
	
	str = "Вектор до сортировки";
	print_vstr(vstr, str);
	
	//numnums = vector_int1(numnums);
	str = "Вектор после vector_str1";
	print_vstr(vector_str1(vstr), str);
	
	vector_str2(vstr);
	str = "Вектор после vector_str2";
	print_vstr(vstr, str);
	
	vector_str2(vstr);
	str = "Вектор восстановленный при помощи vector_str2";
	print_vstr(vstr, str);
	
	keep_window_open("~~");
	return EXIT_SUCCESS;
}
