

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <climits>			//Для определения максимальных значений для типов
#include <iomanip>			//Для возможности форматирования потока вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void f(int i, double fpd)
{
	cout << setprecision(20) << endl;
	cout << "arguments 'int i'  &  'double fpd' " << i << '\t' << fpd << endl;
	
	char c = i;			//Тип char действительно представляет очень маленькие целые числа
	cout << "char c = i " << c << '\t' << int(c) << endl;
	
	short s = i;		//Опасно: тип int может не поместиться в памяти переменной short
	cout << "short s = i " << s << endl;
	
	i = i+1;			//Что будет, если число i до увеличения было максимально возможным?
	cout << "i = i+1 " << i << endl;
	
	long lg = i*i;		//Опасно: long может быть не больше int
	cout << "long lg = i*i " << lg << endl;
	
	float fps = fpd;	//Опасно: значение типа double может не поместиться в типе float
	cout << "float fps = fpd " << fps << endl;
	
	i = fpd;			//Усечение (напр., 5.7 -> 5)
	cout << "i = fpd " << i << endl;
	
	fps = i;			//Возможна потеря точности (при очень больших целочисленных значениях)
	cout << "fps = i " << fps << endl;
}

void g()
{
	char ch = 0;
	for(int i = 0; i < 500; ++i)		cout << int(ch++) << '\t';
}

//------------------------------------------------------------------------------

//Получает из входного потока шаблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main()
{
	while (true) {
		try
		{
			g();
			keep_window_open("g0");
			
			f(8, 8.0);
			keep_window_open("f1");
			
			f(88, 16.0);
			keep_window_open("f2");
			
			f(int(CHAR_MAX+50), 1.23456789);
			keep_window_open("f3");
			
			f(int(SHRT_MAX+200), 12.34567890123456789);
			keep_window_open("f4");
			
			f(int(INT_MAX), 123456789.0);
			keep_window_open("f5");
			
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

