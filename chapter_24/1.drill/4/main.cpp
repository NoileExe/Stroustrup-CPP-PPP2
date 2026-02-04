

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <cmath>
//#include <limits>
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
			while( !cin.eof() )
			{
				cin.clear(ios_base::goodbit);
				cout << "Enter whole numbers - get their square root:\n> ";
				
				int n {0};		//Ввод пользователя
				int res {0};
				cin >> n;
				
				if(cin.eof())		{  }
				else if(cin.fail())
				{
					cerr << "\n\nBAD INPUT!\n\n";
					cin.clear(ios_base::goodbit);
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
				}
				else
				{
					errno = 0;
					res = sqrt(n);
					
					if(errno == EDOM)		cerr << "\n\nFUNCTION 'sqrt()' IS NOT DEFINED FOR NEGATIVE NUMBERS\n\n";
					else if(errno)			cerr << "\n\nSOME ERROR HAS OCCURRED WHEN CALLING A FUNCTION 'sqrt()'\n\n";
					else					cout << res << "\n\n";
				}
			}
			
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

