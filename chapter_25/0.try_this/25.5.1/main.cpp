
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
//#include <iomanip>	//Для возможности форматирования потока вывода
#include <limits>		//Получение диапазона допустимых значений для типов
#include <sstream>		//Для строкового потока ввода-вывода
#include <bitset>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Добивается от пользователя ввода исправного числа в диапазоне от min до max
template<class N> //Требует Number<N>
N get_kb_num(const string& question, N min = 0, N max = 100)
{
	N num {-1};
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

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			int min_num {std::numeric_limits<int>::min()};
			int max_num {std::numeric_limits<int>::max()};
			int num {0};
			
			do {
				num = get_kb_num("Enter number", min_num, max_num);
				cout << dec << num << " == "
					 << hex << "0x" << num << " == "
					 << std::bitset<8*sizeof(int)>(num) << dec << '\n';
				
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