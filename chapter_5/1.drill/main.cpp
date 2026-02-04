
#include <console_encoding.h>
#include <std_lib_facilities.h>
//#include <condition_variable>

int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	try
	{
		//!!!!string s = "Success!\n"; for (int i=0; i<=9; ++i) cout << s[i];
		
		//chapter_5 drill#7
		/*if (cond)
			cout << "Success!\n";
		else
			cout << "Fail!\n";*/
			
		string s = "Success!\n"; //chapter_5 drill#15
		for (int i=0; i<9; ++i)
			cout << s[i];
		
		keep_window_open();
		return 0;
	}
	catch (exception& e) {
		cerr << "Ошибка: " << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch (...) {
		cerr << "Неизвестное исключение!\n";
		keep_window_open();
		return 2;
	}
}
