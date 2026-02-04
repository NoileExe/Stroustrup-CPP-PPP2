
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <MatrixIO11.h>			//Включает <string>, <algorithm>, <iostream>, Matrix11.h
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

//Сравнение размерностей матриц (количество столбцов, строк и т.п.)
template<class T>
bool check_equ_dim(const Numeric_lib::Matrix<T, 1>& m1, const Numeric_lib::Matrix<T, 1>& m2)
{
	if( m1.size() != m2.size()  ||  m1.size()==0 )		return false;
	return true;
}

template<class T>
bool check_equ_dim(const Numeric_lib::Matrix<T, 2>& m1, const Numeric_lib::Matrix<T, 2>& m2)
{
	if( m1.dim1() != m2.dim1()  ||  m1.dim2() != m2.dim2()  ||  m1.size()==0 )
		return false;
	return true;
}

template<class T>
bool check_equ_dim(const Numeric_lib::Matrix<T, 3>& m1, const Numeric_lib::Matrix<T, 3>& m2)
{
	if( m1.dim1() != m2.dim1()  ||  m1.dim2() != m2.dim2()  ||  m1.dim3() != m2.dim3()  ||  m1.size()==0 )
		return false;
	return true;
}

//------------------------------------------------------------------------------

Matrix operator*(const Matrix& m1, const Matrix& m2)
{
	//Обязательное условие при умножении: количество столбцов первой матрицы должно быть равно количеству строк второй
	if(m1.dim2() != m2.dim1()  &&  m1.size())
		error("when multiplying, the number of columns of the first matrix must be equal to the number of rows of the second matrix");
	
	Matrix res (m1.dim1(), m2.dim2());
	
	for(Index r1 = 0; r1 < m1.dim1(); ++r1)
		for(Index c2 = 0; c2 < m2.dim2(); ++c2)
		{
			double summ {0};
			for(Index r2 = 0; r2 < m2.dim1(); ++r2)
				summ += m1[r1][r2] * m2[r2][c2];
			
			res[r1][c2] = summ;
		}
	
	return res;
}

//------------------------------------------------------------------------------

template<class T, int N = 1>
Numeric_lib::Matrix<T, N> operator+(const Numeric_lib::Matrix<T, N>& m1, const Numeric_lib::Matrix<T, N>& m2)
{
	//Обязательное условие при сложении: количество и строк, и столбцов обоих матриц должно быть равным
	//В зависимости от размерности матрицы добавляется или убиарется одно измерение, но принцип тот же
	if( !check_equ_dim(m1,m2) )
		error("when adding, the number of rows and columns of the first matrix must be equal to the number of rows and columns of the second matrix");
	
	Numeric_lib::Matrix<T, N> res {m1};
	
	T* res_ptr = res.data();
	const T* m2_ptr = m2.data();
	
	for(Index i = 0; i < res.size(); ++i)		res_ptr[i] += m2_ptr[i];
	
	return res;
}

//------------------------------------------------------------------------------

//void mul_summ_random_matrix(Index rows, Index cols)
void mul_summ_random_matrix()
{
	//if(rows < 2  ||  cols < 2)		error("bad size of Matrix<double,2> (rows=" + to_string(rows) + "; columns=" + to_string(cols) + ")");
	
	Matrix m1 = random_matrix(5, 3);
	Matrix m2 = random_matrix(3, 4);
	
	cout << "\n\n\tMatrix<double,2> m1  rows=" << m1.dim1() << "  columns=" << m1.dim2() << "\n";
	cout << "\n\n\tMatrix<double,2> m2  rows=" << m2.dim1() << "  columns=" << m2.dim2() << "\n\n";
	cout << "m1 =\n" << m1 << "\n\n";
	cout << "m2 =\n" << m2 << "\n\n";
	cout << "\n\n\tm1 * m2 =\n";
	cout << m1 * m2 << endl;
	
	
	Vector v1 = random_vector(5);
	Vector v2 = random_vector(5);
	
	cout << "\n\n\tMatrix<double,1> v1  elements=" << v1.size() << "\n";
	cout << "\n\n\tMatrix<double,1> v2  elements=" << v2.size() << "\n\n";
	cout << "v1 =\n" << v1 << "\n\n";
	cout << "v2 =\n" << v2 << "\n\n";
	cout << "\n\n\tv1 + v2 =\n";
	cout << v1 + v2 << endl;
	
	
	Matrix m3 = random_matrix(2, 4);
	Matrix m4 = random_matrix(2, 4);
	
	cout << "\n\n\tMatrix<double,2> m3  rows=" << m3.dim1() << "  columns=" << m3.dim2() << "\n";
	cout << "\n\n\tMatrix<double,2> m4  rows=" << m4.dim1() << "  columns=" << m4.dim2() << "\n\n";
	cout << "m3 =\n" << m3 << "\n\n";
	cout << "m4 =\n" << m4 << "\n\n";
	cout << "\n\n\tm3 + m4 =\n";
	cout << m3 + m4 << endl;
}