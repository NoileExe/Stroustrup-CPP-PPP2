
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

char* findx (const char* s, const char* x) {
	char* cp {nullptr};
	
	for (int i = 0;   s[i] != 0;   ++i)
	{
		if (s[i] == x[0])
			for (int j = 0;   x[j] != 0;   ++j)
				//Символы в фрагменте и в искомой строке отличаются? - прекращаем перебор фрагмента
				if (s[i+j] != x[j])			break;
				
				//Строка найдена полностью? - запоминаем адрес
				else if (x[j+1] == 0)		cp = const_cast<char*>(&s[i]);
		
		//Первое вхождение найдено? - завершаем поиск
		if (cp)		break;
	}
	
	return cp;
}


int main()
{
	while (true) {
		try
		{
			char str1[] = "Hello, World! XYZhere ?";	//Строка Си-типа
			char str2[] = "XYZ";	//Строка Си-типа
			cout << str1 << "\t\t" << str2 << '\n';
			
			char* cp {findx(str1, str2)};
			cout << &cp << "\t\t" << cp << '\n';
			
			keep_window_open();
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