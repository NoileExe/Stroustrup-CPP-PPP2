

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

//Оператор вывода для класса Matrix
template<typename T, int N>
ostream& operator<<(ostream &ost, const Matrix<T,N>& m)
{
	ost << '{';
	for(int i = 0; i < m.size(); ++i)		ost << ' ' << m[i];
	return ost << " }";
}

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
	//if( ch != '{' )		throw runtime_error("Invalid input format for Matrix class (no opening brace '{') [ operator>>() for Matrix<T,N> ]");
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

//Получает из входного потока шаблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main()
{
	while (true) {
		try
		{
			Matrix<double> mtrx(10);
			
			cout << "Enter a matrix of 10 elements with a decimal in the format { a.a b.b }\n> ";
			cin >> mtrx;
			cout << mtrx << "\n\n";
			
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
