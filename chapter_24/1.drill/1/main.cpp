

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>			//Для возможности форматирования потока вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Получает из входного потока шаблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main()
{
	while (true) {
		try
		{
			cout << left << setw(15) << "SIZEOF char"	<< sizeof(char)		<< '\t' << sizeof(char {'$'})		<< "\n\n";
			cout << left << setw(15) << "SIZEOF short"	<< sizeof(short)	<< '\t' << sizeof(short {2022})		<< "\n\n";
			cout << left << setw(15) << "SIZEOF int"	<< sizeof(int)		<< '\t' << sizeof(int {2022})		<< "\n\n";
			cout << left << setw(15) << "SIZEOF long"	<< sizeof(long)		<< '\t' << sizeof(long {2022})		<< "\n\n";
			cout << left << setw(15) << "SIZEOF float"	<< sizeof(float)	<< '\t' << sizeof(float {23.02})	<< "\n\n";
			cout << left << setw(15) << "SIZEOF double"	<< sizeof(double)	<< '\t' << sizeof(double {23.02})	<< "\n\n";
			
			
			char* c = new char {'$'};
			short* s = new short {2022};
			int* i = new int {2022};
			double* d = new double {23.02};
			cout << left << setw(15) << "SIZEOF char*"		<< sizeof(char*)	<< '\t' << sizeof(c) << "\n\n";
			cout << left << setw(15) << "SIZEOF short*"		<< sizeof(short*)	<< '\t' << sizeof(s) << "\n\n";
			cout << left << setw(15) << "SIZEOF int*"		<< sizeof(int*)		<< '\t' << sizeof(i) << "\n\n";
			cout << left << setw(15) << "SIZEOF double*"	<< sizeof(double*)	<< '\t' << sizeof(d) << "\n\n";
			
			delete c;
			delete s;
			delete i;
			delete d;
			
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

