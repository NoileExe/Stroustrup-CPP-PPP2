//Решение классического исключения Гаусса, но только для квадратных матриц (кол-во неизвестных == кол-во строк матрицы)
//Так же система уравнений должна иметь решение и оно должно быть в единственном числе


//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <map>
#include <iomanip>	//Для возможности форматирования потока вывода
#include <sstream>	//Для строкового потока ввода-вывода
#include <random>	//Для рандомизации


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int randint(int min, int max) {
	static default_random_engine ran;
	return uniform_int_distribution<>{min, max}(ran);
}

int randint(int max) { return randint(0, max); }

//------------------------------------------------------------------------------

//Добивается от пользователя ввода исправного числа в диапазоне от min до max
int get_kb_int(const string& question, int min = 0, int max = 100)
{
	int num {-1};
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
			do {
				cout << "\n\nProgram for generating numbers in the range from 0 to N in the amount of D\n\n";
				
				int n {get_kb_int("Please enter the UPPER LIMIT of the range of generated number series",0,100)};
				int d {get_kb_int("Please enter the NUMBER OF ITTERATIONS to generate a series of number",5,500)};
				
				map<int,int> nums; //Пары число, частота встречи
				for(int i = 0; i < d; ++i)		++nums[randint(0, n)];
				
				cout << "\n\n\n";
				for(int i = 0; i <= n; ++i)
				{
					cout << setw(4) << left << i << " ";
					
					if( nums.find(i) != nums.end() ) {
						d = nums.find(i)->second;
						for(int j = 0; j < d; ++j)		cout << '*';
					}
					
					cout << endl;
				}
				
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