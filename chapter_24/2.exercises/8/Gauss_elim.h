

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

//Исключение данного типа вызывается при ошибке в работе алгоритма классического исключения Гаусса.
struct Elim_failure : std::domain_error {
	Elim_failure(string s) : std::domain_error(s) { }
};

//Исключение данного типа вызывается при ошибке в работе алгоритма обратной подстановки
struct Back_subst_failure : std::domain_error {
	Back_subst_failure(string s) : std::domain_error(s) { }
};

//------------------------------------------------------------------------------

//Максимальное число по длине при печати с точностью после запятой равной n
//Минус и десятичная точка учитываются
int max_ln(const Vector& v, int n = 2)
{
	int max {0};		//максимальная длина столбца системы уравнений
	for(Index i = 0; i < v.size(); ++i)
	{
		ostringstream ost;
		ost /*<< fixed*/ << setprecision(n) << v[i];
		if( ost.str().size() > max )		max = ost.str().size();
	}
	
	return max;
}

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
		//cout << ost.str() << endl;
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
		for(Index j = 0; j < m.dim2(); ++j)		os  << " " << setw(max) << m[i][j] << " ";
		os << "}\n";
	}
			
	return os << "}";
}

//------------------------------------------------------------------------------

//Вывод на печать системы уравнений
void print_equsystem(const Matrix& m, const Vector& v)
{
	if(m.dim2() != v.size())
		error("the number of rows of the matrix of coefficients differs from the number of elements of the vector of constants [ print_equsystem(Matrix&, Vector&) ]");
	
	int max {max_ln(m)};		//максимальная длина столбца системы уравнений
	
	for(Index i = 0; i < m.dim2(); ++i) {
		cout << "\t";
		
		for(Index j = 0; j < m.dim1(); ++j)
		{
			ostringstream ost;
			ost << defaultfloat;
			if( m[i][j] == 0   )			ost << m[i][j];
			else if( abs(m[i][j]) > 1 )		ost << abs(round(m[i][j]*100) / 100) << "*X" << j+1;
			else							ost << "X" << j+1;
			
			cout << setw(max+3) << ost.str();	//с учетом "*Xi", где i - индекс
			
			if( j+1 != m.dim1() )
				if( m[i][j+1] < 0 )	cout << "  -  ";
				else				cout << "  +  ";
		}
		
		cout << " = " << v[i] << " ;" << endl;
	}
}

//Вывод на печать расширенной матрицы коэфициентов (с константами)
void print_expmatrix(const Matrix& m, const Vector& v)
{
	if(m.dim2() != v.size())
		error("the number of rows of the matrix of coefficients differs from the number of elements of the vector of constants [ print_expmatrix(Matrix&, Vector&) ]");
	
	int max {max_ln(m)};		//максимальная длина столбца системы уравнений
	if( max < max_ln(v) )		max = max_ln(v);
	
	
	for(Index i = 0; i < m.dim2(); ++i) {
		cout << "   { ";
		
		for(Index j = 0; j < m.dim1(); ++j)		cout << defaultfloat << setw(max) << round(m[i][j]*100) / 100 << " ";
		
		cout << " |  " << defaultfloat << setw(max) << round(v[i]*100) / 100 << " }" << endl;
	}
}

//------------------------------------------------------------------------------

void classical_elimination(Matrix& A, Vector& b);				//Классическое исключение Гаусса без перестановки строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
void elim_with_partial_pivot(Matrix& A, Vector& b);				//Классическое исключение Гаусса  с перестановкой строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
Vector back_substitution(const Matrix& A, const Vector& b);		//Обратная подстановка для вычисления неизвестных

//Классическое исключение Гаусса без перестановки строк
//Возвращает вектор (одномерную матрицу) значений переменных
Vector classical_gaussian_elimination(Matrix A, Vector b)
{
	classical_elimination(A, b);
	/*cout << " A matrix after elimination = " << endl;
	print_expmatrix(A,b);
	cout << "\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n";*/
	return back_substitution(A, b);
}

//Классическое исключение Гаусса с перестановкой строк
//Возвращает вектор (одномерную матрицу) значений переменных
Vector pivotal_elimination(Matrix A, Vector b)
{
	elim_with_partial_pivot(A, b);
	/*cout << " A matrix after elimination = " << endl;
	print_expmatrix(A,b);
	cout << "\n\n-----------------------------------------------------------\n\n";*/
	return back_substitution(A, b);
}

//------------------------------------------------------------------------------

//Классическое исключение Гаусса без перестановки строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
void classical_elimination(Matrix& A, Vector& b)
{
	const Index n = A.dim1();

	//Проходим от первого столбца до предпоследнего,
	// обнуляя элементы, стоящие ниже диагонали
	for (Index j = 0; j < n-1; ++j)
	{
		const double pivot = A(j, j);	//Опорный элемент
		if (pivot == 0) {
			cout << "\n A matrix after elimination = " << "\n\n";
			print_expmatrix(A,b);
			throw Elim_failure("\tELIMINATION FAILURE IN ROW " + to_string(j+1));
		}

		//Обнуляем каждый элемент, стоящий ниже в строке i
		for (Index i = j+1; i < n; ++i)
		{
			const double mult = A(i, j) / pivot; 
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);	//Изменяем вектор 'b' (расширенная часть матрицы - свободные числа)
			
			cout << "\n\tRow " << i+1 << " relative to row " << j+1 << " & column " << j+1 << "\n\n";
			print_expmatrix(A,b);
			press_Enter_key();
		}
	}
}

//Классическое исключение Гаусса с перестановкой строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
void elim_with_partial_pivot(Matrix& A, Vector& b)
{
	const Index n = A.dim1();

	for (Index j = 0; j < n; ++j) {
		Index pivot_row = j;

		//Поиск подходящего опорного элемента
		for (Index k = j + 1; k < n; ++k)
			if( abs(A(k, j)) > abs(A(pivot_row, j)) )		pivot_row = k;

		//Обмен строк для лучего опорного элемента
		if(pivot_row != j) {
			A.swap_rows(j, pivot_row);
			std::swap(b(j), b(pivot_row));
			
			cout << "\n\tSwap rows " << j+1 << " and " << pivot_row+1 << "\n\n";
			print_expmatrix(A,b);
			press_Enter_key();
		}
		
		const double pivot = A(j, j);
		if(pivot==0)
		{
			cout << "\n A matrix after elimination = " << "\n\n";
			print_expmatrix(A,b);
			error("\tCAN'T SOLVE: pivot==0");
		}
		
		//Исключение Гаусса
		for (Index i = j + 1; i < n; ++i)
		{
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j)); 
			b(i) -= mult * b(j);
			
			cout << "\n\tRow " << i+1 << " relative to row " << j+1 << " & column " << j+1 << "\n\n";
			print_expmatrix(A,b);
			press_Enter_key();
		}
	}
}

//------------------------------------------------------------------------------

//Обратная подстановка для вычисления неизвестных
Vector back_substitution(const Matrix& A, const Vector& b)
{
	const Index n = A.dim1();	//Количество элементов в строке (столбцов)
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i)
	{
		double s = b(i) - dot_product(A[i].slice(i+1), x.slice(i+1));

		if (double m = A(i, i))		x(i) = s / m;
		else						throw Back_subst_failure("Back substitution failure in row " + to_string(i+1));
		//else						error("can't solve: diagonal element is zero during back substitution");
	}

	return x;
}

//------------------------------------------------------------------------------

//Генерация одномерной матрицы размерностью n (кол-во элементов / столбцов)
Vector random_vector(Index n)
{
	Vector v(n);

	/*for (Index i = 0; i < n; ++i)
		v(i) = 1.0 * n * rand() / RAND_MAX;*/

	random_device rd;
	mt19937 mersenne( rd() );		// инициализируем Вихрь Мерсенна случайным стартовым числом
	//mt19937 mersenne(static_cast<unsigned int>(time(0)));	// инициализируем Вихрь Мерсенна случайным стартовым числом
	
	for(Index i = 0; i < n; ++i)
		v(i) = mersenne() % 10;

	return v;
}


//Генерация двумерной матрицы размерностью n*n
Matrix random_matrix(Index n)
{
	Matrix m(n,n);

	for (Index i = 0; i < n; ++i)
		m[i] = random_vector(n);

	return m;
}


Vector operator*(const Matrix& m, const Vector& u)
{
	const Index n = m.dim1();
	Vector v(n);	//Каждый эллемент вектора 'v' равен сумме произведений соответствующей строки матрицы 'm' на вектор 'u'
	for (Index i = 0; i < n; ++i)		v(i) = dot_product(m[i], u);
	return v;
}

//------------------------------------------------------------------------------

void solve_random_system(Index n)
{
	Matrix A = random_matrix(n);
	Vector b = random_vector(n);
	
	cout << "\n\n\tSolving A*x=B\n\n";
	cout << "A = " << A << "\n\n";
	cout << "b = " << b << "\n\n";
	print_equsystem(A, b); //Вывод системы уравнений
	press_Enter_key();
	print_expmatrix(A, b); //Вывод расширенной матрицы
	press_Enter_key();

	try {
		Vector x = classical_gaussian_elimination(A, b);
		cout << "classical elim SOLUTION is x = " << x << "\n\n";
	}
	catch(const exception& e) {
		cerr << e.what() << "\n\n";
		press_Enter_key();
		
		try {
			cout << "\n\n\tSolving A*x=B\n\n";
			cout << "A = " << A << "\n\n";
			cout << "b = " << b << "\n\n";
			print_equsystem(A, b); //Вывод системы уравнений
			cout << "\n\n";
			print_expmatrix(A, b); //Вывод расширенной матрицы
			
			Vector x = pivotal_elimination(A, b);
			cout << "elim SOLUTION with partial pivot is x = " << x << "\n\n";
		}
		catch(const exception& e) {
			cerr << e.what() << std::endl;
		}
	}
}