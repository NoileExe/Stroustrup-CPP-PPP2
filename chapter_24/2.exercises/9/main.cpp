

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <MatrixIO11.h>		//Включает <string>, <algorithm>, <iostream>, Matrix11.h
#include <cmath>
#include <iomanip>	//Для возможности форматирования потока вывода
#include <sstream>	//Для строкового потока ввода-вывода
#include <typeinfo>


using namespace std;

using Numeric_lib::Index;

typedef Numeric_lib::Matrix<double, 2> Matrix;



const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Максимальное число по длине при печати с точностью после запятой равной n
//Минус и десятичная точка учитываются
template<class T>
int max_ln(const Numeric_lib::Matrix<T,2>& m, int n = 2)
{
	int max {0};		//максимальная длина столбца системы уравнений
	
	const T* mptr = m.data();
	for(Index i = 0; i < m.size(); ++i)
	{
		ostringstream ost;
		ost << defaultfloat << round(mptr[i]*(10*n)) / (10*n);
		if( ost.str().size() > max )		max = ost.str().size();
	}
	
	return max;
}

ostream& operator<<(ostream& os, const Matrix& m)
{
	int max {max_ln(m)};		//максимальная длина столбца системы уравнений
	
	os << "{\n";
	for(Index i = 0; i < m.dim1(); ++i)
	{
		os << "   {";
		for(Index j = 0; j < m.dim2(); ++j)		os << defaultfloat << " " << setw(max) <<  round(m[i][j]*100) / 100 << " ";
		os << "}\n";
	}
			
	return os << "}";
}

ostream& operator<<(ostream& os, const Numeric_lib::Matrix<int,2>& m)
{
	int max {max_ln(m)};		//максимальная длина столбца системы уравнений
	
	os << "{\n";
	for(Index i = 0; i < m.dim1(); ++i)
	{
		os << "   {";
		for(Index j = 0; j < m.dim2(); ++j)		os << " " << setw(max) <<  m[i][j] << " ";
		os << "}\n";
	}
			
	return os << "}";
}

//------------------------------------------------------------------------------

template<class T, class R>
R triple(T n) { return static_cast<R>(n * 3); }

template<class T>
T triple_same_type(T n) { return n * 3; }

template<class F, class T>
auto my_apply(F f, const Numeric_lib::Matrix<T,2>& m)
{
	using R = typename result_of<F(T)>::type;
	Numeric_lib::Matrix<R, 2> res (m.dim1(), m.dim2());
	
	for(Index i = 0; i < m.size(); ++i)		*(res.data()+i) = f( *(m.data()+i) );
	
	return res;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			double a[2][3] = { {1,2,3}, {4,5.5,6} };
			
			Matrix m1{a};
			Numeric_lib::Matrix<double,2> m2 { my_apply(triple_same_type<double>, m1) };
			//Numeric_lib::Matrix<int,2> m2 { my_apply(triple<double, int>, m1) };
			
			cout << m1 << "\n\n\n" << m2 << "\n\n\n";
			
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