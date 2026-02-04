
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
//#include <iomanip>	//Для возможности форматирования потока вывода
//#include <sstream>		//Для строкового потока ввода-вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Число 160 никогда не будет достигнуто, т.к. при достижении числа 127 и дальнейшем
// увеличении signed char на единицу получаем число -128 и далее по кругу
void infinite()
{
	unsigned char max = 160;	//Очень большое
	for(signed char i = 0; i < max; ++i)		cout << int(i) << '\n';
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			infinite();
			
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