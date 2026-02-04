#include <std_lib_facilities.h>

void print(const vector<int>& v, const string& s)
//На вход константные ссылки на вектор и строку
//Вывод на экран строку в виде: "ПЕРЕДАННАЯ_СТРОКА (РАЗМЕР_ВЕКТОРА):"
//и далее каждый элемент вектора: [ИНДЕКС] ЭЛЕМЕНТ_ВЕКТОРА
{
	cout << s << " (" << v.size() << "): " << endl;
	
	for (int i = 0;  i < v.size(); ++i)
		if ( i < (v.size()-1) ) cout << "[" << i << "] " << v[i] << endl;
		else					cout << "[" << i << "] " << v[i] << "\n\n";
}