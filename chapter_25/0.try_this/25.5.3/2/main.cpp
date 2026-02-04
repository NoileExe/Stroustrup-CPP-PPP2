
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
//#include <iomanip>	//Для возможности форматирования потока вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
void print(T value)
{
	cout << int(value) << '\t';
	//cout << static_cast<int>(value) << '\t';
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			int si = 257;			//Не мпомещается в тип char. На 2 больше, чем тип unsigned char
			char c = si;			//Неявное преобразование в char (см. signed char)
			unsigned char uc = si;	// 1 - т.к. 8 единиц == беззнаковому числу 255, т.е. при достижении 256 == 0, 257 == 1
			signed char sc = si;	// 1 - т.к. 8 единиц == знаковому числу -128 (при достижении 128), далее 128+128 == 256 == 0, 257 == 1
			print(si); print(c); print(uc); print(sc); cout << '\n';

			si = 129;
			c = si;					//-127 - т.к. 8 единиц == знаковому числу -128 (при достижении 128), а увеличение на единицу этого числа даёт -127
			uc = si;				//129 - т.к. unsigned char имеет диапазон значений [0; 255]
			sc = si;				//Смотри обычный char
			print(si); print(c); print(uc); print(sc); cout << '\n';

			si = 128;
			c = si;
			uc = si;
			sc = si;
			print(si); print(c); print(uc); print(sc); cout << '\n';
			
			
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