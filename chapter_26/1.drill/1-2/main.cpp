
//in1.txt - нечетное | четное кол-во элементов | неупорядоченный вектор | вектор упорядоченнный по убыванию
//in2.txt - остальные тесты


//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>	//Включает <string>, <iostream>
#include <fstream>		// для файловог опотока ввода
#include <iomanip>		// для модификации потоков ввода-вывода
#include <vector>		// контейнер вектор
#include <algorithm>	// sort(), swap()


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

namespace bs {

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
	else if(!ist || ch != '{')		{ ist.clear(ios_base::failbit);		return ist; }
	/*else if(!ist)			{ ist.clear(ios_base::goodbit);		error("unexpected input stream error 1 [ istream operator>>() for Test<T> ]"); }
	else if(ch != '{')		error("start of test string expected (symbol '{') [ istream operator>>() for Test<T> ]");*/
	
	//--------------------------------------------------------------------------
	
	ist >> ch;
	if(!ist || ch != '{')		{ ist.clear(ios_base::failbit);		return ist; }
	/*if(!ist)				{ ist.clear(ios_base::goodbit);		error("unexpected input stream error 2 [ istream operator>>() for Test<T> ]"); }
	else if(ch != '{')		error("start of sequence expected (symbol '{') [ istream operator>>() for Test<T> ]");*/
	
	T tmp;
	while(ch != '}')
	{
		ist >> ch;
		
		if(ch != '}')
		{
			ist.putback(ch);
			ist >> tmp;
			if(!ist)		{ ist.clear(ios_base::failbit);		return ist; }
			//if(!ist)	{ ist.clear(ios_base::goodbit);		error("unexpected input stream error 3 [ istream operator>>() for Test<T> ]"); }
			else		seq.push_back(tmp);
		}
	}
	
	//--------------------------------------------------------------------------
	
	ist >> res >> ch;
	if(!ist || ch != '}')		{ ist.clear(ios_base::failbit);		return ist; }
	/*if(!ist)	{ ist.clear(ios_base::goodbit);		error("unexpected input stream error 4 [ istream operator>>() for Test<T> ]"); }
	else if(ch != '}')		error("end of test string expected (symbol '}') [ istream operator>>() for Test<T> ]");*/
	
	t = Test<T> {label, val, seq, res};
	
	return ist;
}

//------------------------------------------------------------------------------


template<class T>
ostream& operator<<(ostream& ost, const vector<T>& v)
{
	ost << "{ ";
	for(const T& e : v)		ost << e << ' '; 
	return ost << "}";
}


//------------------------------------------------------------------------------

template<class T>
int test_all(istream& ist)
{
	int error_count {0};
	int line {0};
	for(Test<T> t; ist >> t; )
	{
		bool r = bs::binary_search(t.seq.begin(), t.seq.end(), t.val);
		
		if(r != t.res)
			cout << ++error_count << " fail in test " << t.label
				 << " binsearch in sequence with " << t.seq.size() << " elem(-s)) " << t.seq
				 << ", val==" << t.val << " -> " << t.res << "\n";
		
		else	cout << t.label << " test passed\n";	// крайне неподробно
		
		++line;		// считает кол-во тестов, но не строки, т.к. могут быть пустые строки или несколько тестов на одной строке
	}
	
	if(!ist.eof() && !ist)
	{
		ist.clear(ios_base::goodbit);
		error("unexpected input stream error for Test<T> in line " + to_string(line+1) + " [ test_all() ]");
	}
	
	return error_count;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			cout << "Enter the name of the input file: ";
			string file_name {""};
			getline(cin,file_name);
			
			ifstream ifs {file_name};	//Открываем файловый поток ввода
			if(!ifs)		error("unable to open file '" + file_name + "'");
			ifs.exceptions(ifs.exceptions() | ios_base::badbit);
			
			//cout << "\n\n" << boolalpha;
			int error_count = test_all<int>(ifs);
			cout << "\n\nNum of errors: " << error_count << "\n\n"; //<< noboolalpha;
			
			cin.putback('\n');
			keep_window_open("~");
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}