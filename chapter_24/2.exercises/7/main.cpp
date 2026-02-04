//Решение классического исключения Гаусса, но только для квадратных матриц (кол-во неизвестных == кол-во строк матрицы)
//Так же система уравнений должна иметь решение и оно должно быть в единственном числе

//Решение без библиотеки Matrix при помощи классов построенных на основе встроенных массивов
//Большое упущение в данном случае в функции my_Matrix::operator[] - возвращается ссылка на my_Vector с неконстантным размером,
// т.е. матрице 3*3 можно приравнять одну из строк, например, вектору размером 4 элемента и сломать программу
//Попытался устранить проблему через возврат класса Row - наследника my_Vector с перегруженнными функциями operator=()



#include "Gauss_elim.h"					//Включает <iomanip>, <random> и <yes_or_no.h>, который влючает <string>, <iostream> и устанавливает using namespace std


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			/*{
				double a[3] = {1,2,3};
				double b[3] = {1,2,3};
				
				my_Vector<double> v1(a, 3);
				my_Vector<double> v2(b, 3);
				cout << my_dot_product(v1,v2) << "\n\n";
				
				
				double a1[2][3] = { {1,2,3}, {1,2,3} };
				double b1[2][3] = { {1,2,3}, {1,2,3} };
				
				my_Matrix<double> m1(&a1[0][0], 3, 2);
				my_Matrix<double> m2(&b1[0][0], 3, 2);
				cout << my_dot_product(m1[0],m2[0]) + my_dot_product(m1[1],m2[1]) << "\n\n";
			}
			
			{
				my_Vector<double> v1 {1,2,3};
				my_Vector<double> v2 {v1};
				cout << my_scale_and_add(v1, 1.0, v2) << "\n\n";
				cout << my_scale_and_add(v1.slice(1), 1.0, v2.slice(1)) << "\n\n";
				cout << my_scale_and_add(v1.slice(1), 0.5, v2.slice(1)) << "\n\n";
				
				
				my_Matrix<double> m1 { {1,2,3}, {1,2,3} };
				my_Matrix<double> m2 {m1};
				cout << my_scale_and_add(m1[0], 1.0, m2[0]) << endl
					 << my_scale_and_add(m1[1].slice(0), 2.0, m2[1].slice(0)) << "\n\n";
			}*/
			
			{
				my_Matrix<double> A = 
				{
					{1,2,3},
					{2,3,4},
					{3,4,1}
				};
				
				my_Vector<double> B = {14, 20, 14};

				cout << "Solving A*x=B" << endl;
				cout << "A=" << A << endl;
				cout << "B=" << B << "\n\n";

				my_Vector<double> x = classical_gaussian_elimination(A, B);
				cout << "x1 (classical_gaussian_elimination)=" << x << endl << endl;
				
				x = pivotal_elimination(A, B);
				cout << "x2 (pivotal_elimination)=" << x << endl;
			}
			
			cout << "\n--------------------------------------------------------------------------\n\n";
			
			{
				my_Matrix<double> A = 
				{
					{4,6,2},
					{2,3,9},
					{6,3,0}
				};
				my_Vector<double> B = {0,4,2};

				cout << "Solving A*x=B" << endl;
				cout << "A=\n" << A << endl;
				cout << "B="   << B << endl;

				//my_Vector<double> x1 = classical_gaussian_elimination(A, B);
				//cout << "x1 (classical_gaussian_elimination)=" << x1 << endl << endl;
				
				my_Vector<double> x2 = pivotal_elimination(A, B);
				cout << "x2 (pivotal_elimination)=" << x2 << endl;
			}
			
			cout << "\n--------------------------------------------------------------------------\n\n";
			
			do {
				solve_random_system<double>(3);
				cout << "\n--------------------------------------------------------------------------";
				cin.putback('\n');
			} while( Y_or_N("Repeat?") );
			
			
			// \/Проблема\/Проблема\/Проблема\/Проблема\/Проблема\/Проблема\/Проблема\/Проблема\/Проблема\/
			/*{
				my_Matrix<double> A = 
				{
					{4,6,2},
					{2,3,9},
					{6,3,0}
				};

				cout << "A=\n" << A << endl;
				
				my_Vector<double> B1 = {0,4,2,5};
				my_Vector<double> B2 = {0,4,2};
				A[1] = B2;
				cout << "A=\n" << A << endl;
				cout << "A=\n" << A[1] << endl;
				cout << "A=\n" << A[1][2] << endl;
			}*/
			// /\Проблема/\Проблема/\Проблема/\Проблема/\Проблема/\Проблема/\Проблема/\Проблема/\Проблема/\
			
			
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