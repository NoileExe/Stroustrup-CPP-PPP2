

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>				//Включает <string>, <iostream>
#include <Matrix11.h>		//Включает <string>, <algorithm>
//#include <MatrixIO11.h>		//Включает <string>, <algorithm>, <iostream>
#include <iomanip>					//Для возможности форматирования потока вывода


using namespace std;
using namespace Numeric_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Оператор вывода для класса Matrix (одномерная матрица)
template<typename T>
ostream& operator<<(ostream &ost, const Matrix<T>& m)
{
	ost << '{';
	for(int i = 0; i < m.size(); ++i)		ost << ' ' << m[i];
	return ost << " }";
}

//Оператор вывода для класса Matrix (двумерная матрица)
//вывод настроен под свои нужды
template<typename T>
ostream& operator<<(ostream &ost, const Matrix<T,2>& m)
{
	ost << '{';
	
	for(int r = 0; r < m.dim1(); ++r)
	{
		ost << "\n  { ";
		
		for(int c = 0; c < m.dim2(); ++c)		cout << left << setw(5) << m[r][c];
		
		ost << " }\n";
	}
	
	return ost << '}';
}

//Построчный вывод двумерной матрицы
/*template<typename T>
ostream& operator<<(ostream &ost, const Matrix<T,2>& m)
{
	ost << "{\n";
	for(int r = 0; r < m.dim1(); ++r)		ost << "  " << m[r] << "\n" ;
	return ost << '}';
}*/

//Оператор ввода для класса Matrix
template<typename T, int N>
istream& operator>>(istream &ist, Matrix<T,N>& m)
{
	//-----------------------------СКОБКА {----------------------------
	char ch{0};
	ist >> ch;
	
	if( ist.eof() )		return ist;
	
	if( !ist.good() )
	{
		ist.clear(ios_base::goodbit);
		ist.ignore(numeric_limits<streamsize>::max(),'\n');
		throw runtime_error("bad input [ operator>>() for Matrix<T,N> ]");
	}
	
	//if( ch != '{' )		error("Invalid input format for Matrix class (no opening brace '{') [ operator>>() for Matrix<T,N> ]");
	if( ch != '{' )		throw runtime_error("Invalid input format for Matrix class (no opening brace '{') [ operator>>() for Matrix<T,N> ]");
	//-----------------------------СКОБКА {----------------------------
	
	
	//------------------------------ЧИСЛА------------------------------
	for(int i = 0; i < m.size(); ++i)
		if(!ist)	break;
		else		ist >> m[i];
	
	if( !ist.good() )
	{
		ist.clear(ios_base::goodbit);
		ist.ignore(numeric_limits<streamsize>::max(),'\n');
		throw runtime_error("bad input [ operator>>() for Matrix<T,N> ]");
	}
	//------------------------------ЧИСЛА------------------------------
	
	//-----------------------------СКОБКА }----------------------------
	ist >> ch;
	if( ch != '}' )
		if(isdigit(ch)) {
			string err {"A number was encountered instead of a closing brace '}'. It is possible that more numbers were "};
			err += "submitted for input than the size of the Matrix(" + to_string(m.size()) + " elems) [ operator>>() for Matrix<T,N> ]";
			throw runtime_error(err);
		}
		else		throw runtime_error("Invalid input format for Matrix class (no closing brace '}') [ operator>>() for Matrix<T,N> ]");
	//-----------------------------СКОБКА }----------------------------
	
	return ist;
}

//------------------------------------------------------------------------------

//Добивается от пользователя ввод значения от min до max
int get_opt(int min, int max)
{
	int choice {min-1};
	
	cin.clear(ios_base::failbit);
	while( !cin  ||  choice < min  ||  choice > max )
	{
		cin.clear(ios_base::goodbit);
		int tmp;
		cout << "> ";
		cin >> tmp;
		
		if( cin )				choice = tmp;
		else					cin.clear(ios_base::goodbit);
		
		for(char ch = ' '; ch != '\n'; cin.get(ch))		{  }
	}
	
	return choice;
}

//------------------------------------------------------------------------------

//Получает из входного потока шаблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main()
{
	while (true) {
		try
		{
			int n {0};
			int m {0};
			
			while(true)
			{
				cout << "\n\nMultiplication table program from 'n' to 'm'\n\nEnter a number 'n' (number of rows 1-50)\n";
				n = get_opt(1,50) + 1;
				
				cout << "\nEnter a number 'm' (number of columns 1-20)\n";
				m = get_opt(1,20) + 1;
				
				//---------------Создание матрицы и заполнение шапки---------------
				Matrix<double, 2> mtrx(n,m);
				for(int c = 0; c < m; ++c)		mtrx[0][c] = c;		//По горизонтали верх
				for(int r = 1; r < n; ++r)		mtrx[r][0] = r;		//По вертикали лево
				//---------------Создание матрицы и заполнение шапки---------------
				
				//----------------Заполнение значений на пересечении---------------
				//В каждой строке 'r' каждый столбец 'c'
				for(int r = 1; r < n; ++r)
					for(int c = 1; c < m; ++c)		mtrx[r][c] = mtrx[r][0] * mtrx[0][c];	//Пересечение
				//----------------Заполнение значений на пересечении---------------
				
				cout << "\n\n\n\n" << mtrx << "\n\n\n\n";
				
				if ( Y_or_N(quit_question) )	break;
			}
			
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

