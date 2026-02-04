

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
			float x = 1.0/10;
			float sum = 0;
			for(int i = 0; i<10; ++i)		sum+=x;
			cout << setprecision(15) << sum << endl;
			
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

