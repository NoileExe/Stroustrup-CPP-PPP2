//Решение классического исключения Гаусса, но только для квадратных матриц (кол-во неизвестных == кол-во строк матрицы)
//Так же система уравнений должна иметь решение и оно должно быть в единственном числе


//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>				//Включает <string>, <iostream>
#include <MatrixIO11.h>		//Включает <string>, <algorithm>, <iostream>, Matrix11.h
#include <iomanip>	//Для возможности форматирования потока вывода
#include <random>	//Для рандомизации


using namespace std;

using Numeric_lib::Index;

typedef Numeric_lib::Matrix<double, 2> Matrix;
typedef Numeric_lib::Matrix<double, 1> Vector;


const string quit_question = "Close program?";

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

void classical_elimination(Matrix& A, Vector& b);				//Классическое исключение Гаусса без перестановки строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
void elim_with_partial_pivot(Matrix& A, Vector& b);				//Классическое исключение Гаусса  с перестановкой строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
Vector back_substitution(const Matrix& A, const Vector& b);		//Обратная подстановка для вычисления неизвестных

//Классическое исключение Гаусса без перестановки строк
//Возвращает вектор (одномерную матрицу) значений переменных
Vector classical_gaussian_elimination(Matrix A, Vector b)
{
	classical_elimination(A, b);
	cout << " A matrix after elimination = " << A << endl;
	return back_substitution(A, b);
}

//Классическое исключение Гаусса с перестановкой строк
//Возвращает вектор (одномерную матрицу) значений переменных
Vector pivotal_elimination(Matrix A, Vector b)
{
	elim_with_partial_pivot(A, b);
	cout << " A matrix after elimination = " << A << endl;
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
			cout << "\n A matrix after elimination = " << A << endl;
			throw Elim_failure("\tELIMINATION FAILURE IN ROW " + to_string(j));
		}

		//Обнуляем каждый элемент, стощий ниже в строке i
		for (Index i = j+1; i < n; ++i)
		{
			const double mult = A(i, j) / pivot; 
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);	//Изменяем вектор 'b' (расширенная часть матрицы - свободные числа)
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
		}
		
		const double pivot = A(j, j);
		if(pivot==0)
		{
			cout << "\n A matrix after elimination = " << A << endl;
			error("\tCAN'T SOLVE: pivot==0");
		}
		
		//Исключение Гаусса
		for (Index i = j + 1; i < n; ++i)
		{
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j)); 
			b(i) -= mult * b(j);
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
		double s = b(i)-dot_product(A[i].slice(i+1), x.slice(i+1));

		if (double m = A(i, i))		x(i) = s / m;
		else						throw Back_subst_failure("Back substitution failure in row " + to_string(i));
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
	
	cout << "\n\nSolving A*x=B" << endl;
	cout << "A = " << A << endl;
	cout << "b = " << b << endl;

	try {
		Vector x = classical_gaussian_elimination(A, b);
		cout << "classical elim solution is x = " << x << endl;
		Vector v = A * x;
		cout << " A * x = " << v << endl;
	}
	catch(const exception& e) {
		cerr << e.what() << "\n\n";
		
		try {
			Vector x = pivotal_elimination(A, b);
			cout << "elim with partial pivot is x = " << x << endl;
			Vector v = A * x;
			cout << " A * x = " << v << endl;
		}
		catch(const exception& e) {
			cerr << e.what() << std::endl;
		}
	}
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			{
				double a[3][3] = 
				{
					{1,2,3},
					{2,3,4},
					{3,4,1}
				};
				double b[3] = {14,20,14};

				Matrix A(a);
				Vector B(b);

				cout << "Solving A*x=B" << endl;
				cout << "A=\n" << A << endl;
				cout << "B="   << B << endl;

				Vector x = classical_gaussian_elimination(A, B);
				cout << "x1 (classical_gaussian_elimination)=" << x << endl << endl;
				
				x = pivotal_elimination(A, B);
				cout << "x2 (pivotal_elimination)=" << x << endl;
			}
			
			cout << "\n--------------------------------------------------------------------------\n\n";
			
			{
				double a[3][3] = 
				{
					{4,6,2},
					{2,3,9},
					{6,3,0}
				};
				double b[3] = {0,4,2};

				Matrix A(a);
				Vector B(b);

				cout << "Solving A*x=B" << endl;
				cout << "A=\n" << A << endl;
				cout << "B="   << B << endl;

				//Vector x1 = classical_gaussian_elimination(A, B);
				//cout << "x1 (classical_gaussian_elimination)=" << x1 << endl << endl;
				
				Vector x2 = pivotal_elimination(A, B);
				cout << "x2 (pivotal_elimination)=" << x2 << endl;
			}
			
			cout << "\n--------------------------------------------------------------------------\n\n";
			
			/*solve_random_system(3);
			cout << "\n\n";
			
			solve_random_system(4);
			cout << "\n\n";
			
			solve_random_system(5);
			cout << "\n\n";*/
			
			
			do {
				solve_random_system(3);
				cout << "\n--------------------------------------------------------------------------";
				cin.putback('\n');
			} while( Y_or_N("Repeat?") );
			
			
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