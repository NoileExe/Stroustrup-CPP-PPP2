#include "vectors.h"

void my_error (string error_str)
{
	try		{ throw 'e'; }
	
	catch (...) {
		cerr << "Ошибка: " << error_str << '\n';
		
		while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
		
		keep_window_open("~~");
		throw;
	}
}

//------------------------------------------------------------------------------

void alpha_count (const vector<string>& v, vector<int>& c)
//изменяет вектор c записывая в него длины строк из вектора v по сответствующим индексам
{
	if (v.size()==0)
		my_error ("пустой вектор (alpha_count)!!!");
		
	for (int i = 0;  i < v.size(); ++i)
		c.push_back(v[i].size());
}

//------------------------------------------------------------------------------

int minv_int(const vector<int>& v)
//Поиск наименьшего элемента в векторе
//На вход: константная ссылка на непустой вектор
//Возврат: индекс наименьшего элемента в векторе
{
	if (v.size()==0)
		my_error ("пустой вектор (minv_int)!!!");
	
	int min = 0;
	for (int i = 0;  i < v.size(); ++i)
		if (v[i] < v[min])
			min = i;
	
	return min;
}

int maxv_int(const vector<int>& v)
//Поиск наибольшего элемента в векторе
//На вход: константная ссылка на непустой вектор
//Возврат: индекс наибольшего элемента в векторе
{
	if (v.size()==0)
		my_error ("пустой вектор (maxv_int)!!!");
	
	int max = 0;
	for (int i = 0;  i < v.size(); ++i)
		if (v[i] > v[max])
			max = i;
	
	return max;
}

//------------------------------------------------------------------------------

int minv_str(const vector<string>& v)
//Поиск наименьшего элемента в векторе
//На вход: константная ссылка на непустой вектор
//Возврат: индекс наименьшего элемента в векторе
{
	if (v.size()==0)
		my_error ("пустой вектор (minv_str)!!!");
	
	int min = 0;
	for (int i = 0;  i < v.size(); ++i)
		if (v[i] < v[min])
			min = i;
	
	return min;
}

int maxv_str(const vector<string>& v)
//Поиск наибольшего элемента в векторе
//На вход: константная ссылка на непустой вектор
//Возврат: индекс наибольшего элемента в векторе
{
	if (v.size()==0)
		my_error ("пустой вектор (maxv_str)!!!");
	
	int max {0};
	for (int i = 0;  i < v.size(); ++i)
		if (v[i] > v[max])
			max = i;
	
	return max;
}
