

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <MatrixIO11.h>		//Включает <string>, <algorithm>, <iostream>, Matrix11.h
#include <iomanip>	//Для возможности форматирования потока вывода
#include <random>	//Для рандомизации
#include <sstream>	//Для строкового потока ввода-вывода
#include <typeinfo>

//------------------------------------------------------------------------------

using namespace std;

using Numeric_lib::Index;

typedef Numeric_lib::Matrix<double, 2> Matrix;
typedef Numeric_lib::Matrix<double, 1> Vector;

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

ostream& operator<<(ostream& os, const Vector& v)
{
	os << " { ";
	for(int i = 0; i < v.size(); ++i)		os << v[i] << " ";
	return os << "}";
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

//------------------------------------------------------------------------------

void swap_columns(Matrix& mtrx, Index a, Index b)
// swap_columns() перебирает строки и попарно меняет элементы с указанным индексом в каждой строке
{
	if(a == b)		return;
	for (Index i=0; i < mtrx.dim1(); ++i)
		std::swap(mtrx[i][a], mtrx[i][b]);
}

//------------------------------------------------------------------------------

//Генерация одномерной матрицы размерностью n (кол-во элементов / столбцов)
Vector random_vector(Index n)
{
	Vector v(n);

	random_device rd;
	mt19937 mersenne( rd() );		// инициализируем Вихрь Мерсенна случайным стартовым числом
	//mt19937 mersenne(static_cast<unsigned int>(time(0)));	// инициализируем Вихрь Мерсенна случайным стартовым числом
	
	for(Index i = 0; i < n; ++i)
		v(i) = mersenne() % 10;

	return v;
}


//Генерация двумерной матрицы размерностью rows*cols
Matrix random_matrix(Index rows, Index cols)
{
	Matrix m(rows,cols);

	for (Index i = 0; i < rows; ++i)
		m[i] = random_vector(cols);

	return m;
}

//------------------------------------------------------------------------------

//Добивается от пользователя ввода исправного числа в диапазоне от min до max
int get_kb_int(const string& question, int min = 0, int max = 100)
{
	int num {-1};
	while(true)
	{
		cout << "\n" << question << "\n\n> ";
		
		string str {""};
		getline(cin, str);
		istringstream iss {str};
		iss >> num;
		
		if( cin.good()  &&  !iss.fail()  &&  (min <= num && num <= max) )
			break;
		else {
			cout << "\n\tRange [" << min << "; " << max << "]\n\n";
			num = -1;
			cin.clear(ios_base::goodbit);
		}
	}
	
	//Возвращаем ответ введённый пользователем
	return num;
}

void swap_random_matrix(Index rows, Index cols)
{
	if(rows < 2  ||  cols < 2)		error("bad size of Matrix<double,2> (rows=" + to_string(rows) + "; columns=" + to_string(cols) + ")");
	
	Matrix M = random_matrix(rows, cols);
	
	cout << "\n\n\tRandom Matrix<double,2>  rows=" << M.dim1() << "  columns=" << M.dim2() << "\n\n";
	cout << M << "\n\n";
	
	Index a {get_kb_int("Which columns swap (col_1)?", 0, cols-1)};
	Index b {get_kb_int("Which columns swap (col_2)?", 0, cols-1)};
	
	swap_columns(M, a, b);
	cout << "\n\nSwaped columns " << a << " & " << b << ":\n" << M << "\n\n";
}