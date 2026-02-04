



//Включает yes_or_no.h (<string>, <iostream>), <vector>, <algorithm>, <random>
#include "bs_test.h"

//------------------------------------------------------------------------------

void make_test(ostream& ost, const string& lab, int n, int base, int spread)
//Записывает описание теста с меткой 'lab' в поток вывода 'ost'
//Генерирует последовательность из 'n' элементов типа int, начиная
// со значения 'base'; среднее расстояние между элементами
// имеет равномерное распределение на отрезке [0, spread]
{
	ost << "{ " << lab << " "; 
	
	vector<int> vctr;
	vctr.reserve(n);	// Ускоряет построение очень большого вектора, но не бинарный поиск по нему
	
	int elem = base;
	for(int i = 0; i < n; ++i)				// Создаём элементы
	{
		elem += randint(spread);
		vctr.push_back(elem);
	}

	int val = base + randint(elem - base);	// Искомое значение
	ost << val << " " << vctr;				// Вывод искомого значения и значений вектора в требуемом формате
	
	bool found = false;
	for(int i = 0; i < n; ++i)
		if(vctr[i] == val)		found = true;
	
	ost << found << " }\n";
}

//------------------------------------------------------------------------------