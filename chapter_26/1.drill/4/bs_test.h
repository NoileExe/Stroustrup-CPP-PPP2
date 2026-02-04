


//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>		// для модификации потоков ввода-вывода
#include <vector>		// контейнер вектор
#include <algorithm>	// sort(), swap()
#include <random>		// рандомизация


using namespace std;

//------------------------------------------------------------------------------

namespace bs
{
	//На вход: итераторы указывающие на начало и конец упорядоченной по возрастанию
	// (в ином случае неверные результаты) последовательности и искомое значение
	//Работает из-за второго условия только с двунаправленными итераторами
	//На выходе результат поиска: найдено(true) или не найдено(false)
	template<class Iter, class T>
	bool binary_search(Iter first, Iter last, const T& val)
	{
		//Пустая последовательность или указатель на крайний левый элемент пуст
		if(first == last  ||  &*first == nullptr)		return false;
		if((last-first) < 0)							swap(first, last);		//если итераторы поменяны местами, меняем на верный вариант
		
		Iter p = first + (last-first)/2;	//середина последовательности (даже если итераторы поменяны местами)
		
		//пока не достигнут конец И не найдено значение
		while(p != last  &&  *p != val)
		{
			if( (last-first)/2 == 0 )		last = first;	//сместились к концу
			if(*p < val)					first = p;		//ограничиваем последовательность от текущего проверяемого до конца
			if(val < *p)					last = p;		////ограничиваем последовательность от первого до проверяемого
			p = first + (last-first)/2;		//середина части последовательности
		}
		
		if(*p != val)		return false;
		return true;
	}
}

//------------------------------------------------------------------------------

template<class T>
struct Test
{
	string		label;
	T			val;
	vector<T>	seq;
	bool		res;
};


// Шаблонный оператор ввода для класса Test
// Может вызывать исключения при неверном формате строки теста или ошибках ввода
template<class T>
istream& operator>>(istream& ist, Test<T>& t)
{
	char		ch {'\0'};		// разделитель '{' или '}'
	string		label {""};		// наименование теста
	T			val {};			// искомое значение
	vector<T>	seq {};			// последовательность значений
	bool		res {false};	// предполагаемый результат поиска
	
	ist >> ch >> label >> val;
	if (ist.eof())			return ist;
	else if(!ist)			{ ist.clear(ios_base::goodbit);		error("unexpected input stream error 1 [ istream operator>>() for Test<T> ]"); }
	else if(ch != '{')		error("start of test string expected (symbol '{') [ istream operator>>() for Test<T> ]");
	
	//--------------------------------------------------------------------------
	
	ist >> ch;
	if(!ist)				{ ist.clear(ios_base::goodbit);		error("unexpected input stream error 2 [ istream operator>>() for Test<T> ]"); }
	else if(ch != '{')		error("start of sequence expected (symbol '{') [ istream operator>>() for Test<T> ]");
	
	T tmp;
	while(ch != '}')
	{
		ist >> ch;
		
		if(ch != '}')
		{
			ist.putback(ch);
			ist >> tmp;
			if(!ist)	{ ist.clear(ios_base::goodbit);		error("unexpected input stream error 3 [ istream operator>>() for Test<T> ]"); }
			else		seq.push_back(tmp);
		}
	}
	
	//--------------------------------------------------------------------------
	
	ist >> res >> ch;
	if(!ist)	{ ist.clear(ios_base::goodbit);		error("unexpected input stream error 4 [ istream operator>>() for Test<T> ]"); }
	else if(ch != '}')		error("end of test string expected (symbol '}') [ istream operator>>() for Test<T> ]");
	
	t = Test<T> {label, val, seq, res};
	
	return ist;
}

//------------------------------------------------------------------------------

// Шаблонный оператор вывода для класса vector
template<class T>
ostream& operator<<(ostream& ost, const vector<T>& v)
{
	ost << "{ ";
	for(const T& e : v)		ost << e << ' '; 
	return ost << "}";
}

//------------------------------------------------------------------------------

template<class T>
int test_all(istream& ist, bool out_seq = false)
/*
 * Проверка всех тестовых последовательностей на верность предположений
 *  (каждый тест предполагает что значение Test<T> t.val находится либо нет
 *   (в зависимости от результата записанного предположения в Test<T> t.res))
 *   в последовательности Test<T> t.seq)
 * 
 * На вход поток ввода откуда будут получаться данные тестов до встречи конца
 *  файла или ошибки ввода, а также значени указывающее на то стоит ли выводить
 *  последовательность в отчет на экране (out_seq == true) или нет (out_seq == false)
 * 
 * В ходе работы ф-ции подсчитываются несоответствия предположениям и возвращается
 *  общее кол-во таких несоответствий
*/
{
	int error_count {0};
	for(Test<T> t; ist >> t; )
	{
		bool r = bs::binary_search(t.seq.begin(), t.seq.end(), t.val);
		
		if(r != t.res)	cout << (++error_count) << " fail - fail found in test " << t.label << ". ";
		else			cout << t.label << " test passed. ";
		
		cout << "Binsearch in sequence with " << t.seq.size() << " elem(-s)) ";
		if(out_seq)		cout << t.seq;
		cout << ", val==" << t.val << " -> " << t.res << "\n";
	}
	
	return error_count;
}

//------------------------------------------------------------------------------

inline int randint(int min, int max)
{
	static default_random_engine ran;
	return uniform_int_distribution<>{min, max}(ran);
}

inline int randint(int max)		{ return randint(0, max); }

//Записывает описание теста с меткой 'lab' в поток вывода 'ost'
//Генерирует последовательность из 'n' элементов типа int, начиная
// со значения 'base'; среднее расстояние между элементами
// имеет равномерное распределение на отрезке [0, spread]
void make_test(ostream& ost, const string& lab, int n, int base, int spread);

//------------------------------------------------------------------------------