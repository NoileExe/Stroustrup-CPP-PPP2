

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <Matrix11.h>		//Включает <string>, <algorithm>
//#include <MatrixIO11.h>	//Включает <string>, <algorithm>, <iostream>
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

//Оператор ввода для класса Matrix (одномерная матрица)
template<typename T>
istream& operator>>(istream &ist, Matrix<T>& m)
{
	//-----------------------------СКОБКА {----------------------------
	char ch{0};
	ist >> ch;
	
	if( ist.eof() )		return ist;
	
	if( !ist.good() )
	{
		ist.clear(ios_base::goodbit);
		ist.ignore(numeric_limits<streamsize>::max(),'\n');
		throw runtime_error("bad input [ operator>>() for Matrix<T,1> ]");
	}
	
	//if( ch != '{' )		error("Invalid input format for Matrix class (no opening brace '{') [ operator>>() for Matrix<T,1> ]");
	if( ch != '{' )		throw runtime_error("Invalid input format for Matrix class (no opening brace '{') [ operator>>() for Matrix<T,1> ]");
	//-----------------------------СКОБКА {----------------------------
	
	
	//------------------------------ЧИСЛА------------------------------
	for(int i = 0; i < m.size(); ++i)
		if(!ist)	break;
		else		ist >> m[i];
	
	if( !ist.good() )
	{
		ist.clear(ios_base::goodbit);
		ist.ignore(numeric_limits<streamsize>::max(),'\n');
		throw runtime_error("bad input [ operator>>() for Matrix<T,1> ]");
	}
	//------------------------------ЧИСЛА------------------------------
	
	//-----------------------------СКОБКА }----------------------------
	ist >> ch;
	if( ch != '}' )
		if(isdigit(ch)) {
			string err {"A number was encountered instead of a closing brace '}'. It is possible that more numbers were "};
			err += "submitted for input than the size of the Matrix(" + to_string(m.size()) + " elems) [ operator>>() for Matrix<T,1> ]";
			throw runtime_error(err);
		}
		else		throw runtime_error("Invalid input format for Matrix class (no closing brace '}') [ operator>>() for Matrix<T,1> ]");
	//-----------------------------СКОБКА }----------------------------
	
	return ist;
}

template<class T>
istream& operator>>(istream &ist, Row<T,1> m) {
	return operator>>(ist, static_cast<Matrix<T,1>&>(m));
}

//------------------------------------------------------------------------------

//Оператор вывода для класса Matrix (двумерная матрица)
//Построчный вывод
template<typename T>
ostream& operator<<(ostream &ost, const Matrix<T,2>& m)
{
	ost << "{\n";
	for(int r = 0; r < m.dim1(); ++r)		ost << "  " << m[r] << "\n" ;
	return ost << '}';
}


//Оператор ввода для класса Matrix (двумерная матрица)
//Построчный ввод
template<typename T>
istream& operator>>(istream &ist, Matrix<T,2>& m)
{
	//-----------------------------СКОБКА {----------------------------
	char ch{0};
	ist >> ch;
	
	if( ist.eof() )		return ist;
	
	if( !ist.good() )
	{
		ist.clear(ios_base::goodbit);
		ist.ignore(numeric_limits<streamsize>::max(),'\n');
		throw runtime_error("bad input [ operator>>() for Matrix<T,2> ]");
	}
	
	//if( ch != '{' )		error("Invalid input format for Matrix class (no common opening brace '{') [ operator>>() for Matrix<T,2> ]");
	if( ch != '{' )		throw runtime_error("Invalid input format for Matrix class (no common opening brace '{') [ operator>>() for Matrix<T,2> ]");
	//-----------------------------СКОБКА {----------------------------
	
	
	//------------------------------ЧИСЛА------------------------------
	//Построчный ввод
	for(int r = 0; r < m.dim1(); ++r)
		if(!ist)	break;
		else		ist >> m[r];
	//------------------------------ЧИСЛА------------------------------
	
	//-----------------------------СКОБКА }----------------------------
	ist >> ch;
	if( ch != '}' )		throw runtime_error("Invalid input format for Matrix class (no common closing brace '}') [ operator>>() for Matrix<T,2> ]");
	
	if( !ist.good() )
	{
		ist.clear(ios_base::goodbit);
		ist.ignore(numeric_limits<streamsize>::max(),'\n');
		throw runtime_error("bad input [ operator>>() for Matrix<T,2> ]");
	}
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
			Matrix<int,2> mtrx(2,3);
			
			cout << "Enter a matrix of 6 whole numbers in the format:\n" << "{\n{ a b c }\n{ d e f }\n}" << "\n> ";
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

