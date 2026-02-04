

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

//Получает из входного потока шаблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main()
{
	while (true) {
		try
		{
			Matrix <int> a(10);
			Matrix<int> b(10);
			Matrix<double> c(10);
			Matrix<int,2>d(10,10);
			Matrix<int, 3> e(10,10,10);
			
			cout << left << setw(40) << "SIZEOF 'Matrix <int> a(10)'"			<< sizeof(a) << endl;
			cout << left << setw(10) << "a.size()" << a.size() << "\n\n";
			cout << left << setw(40) << "SIZEOF 'Matrix<int> b(10)'"			<< sizeof(b) << endl;
			cout << left << setw(10) << "b.size()" << b.size() << "\n\n";
			cout << left << setw(40) << "SIZEOF 'Matrix<double> c(10)'"			<< sizeof(c) << endl;
			cout << left << setw(10) << "c.size()" << c.size() << "\n\n";
			cout << left << setw(40) << "SIZEOF 'Matrix<int,2>d(10,10)'"		<< sizeof(d) << endl;
			cout << left << setw(10) << "d.size()" << d.size() << "\n\n";
			cout << left << setw(40) << "SIZEOF 'Matrix<int, 3> e(10,10,10)'"	<< sizeof(e) << endl;
			cout << left << setw(10) << "e.size()" << e.size() << "\n\n";
			
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

