


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Сравнение двух c-строк
//Если первая строка (s1) лексикографически меньше второй (s2) - возвращается отрицательное число
//При равных строках s1 и s2 ф-ция возвращает нуль
//Если первая строка (s1) лексикографически больше второй (s2) - возвращается положительное число
int strcmpr(const char* s1, const char* s2)
{
	for (int i=0;   *(s1+i) != 0;   ++i)
		for (int j = 0;   *(s2+j) != 0;   ++j)
			//Второе условие: первая строка закончилась, а вторая - нет
			if ( *(s1+i+j) < *(s2+j)  || \
					 (*(s1+i+j+1) == 0  &&  *(s2+j+1)) )			{ cout << *(s1+i+j) << '\t' << *(s2+j) << '\n';		return -1; }
			
			//Второе условие: вторая строка закончилась, а первая - нет
			else if ( *(s1+i+j) > *(s2+j)  || \
					 (*(s2+j+1) == 0  &&  *(s1+i+j+1)) )			{ cout << *(s1+i+j) << '\t' << *(s2+j) << '\n';		return 1; }
			
			else if ( *(s1+i+j+1) == 0  &&  *(s2+j+1) == 0 )		return 0;
}


int main()
{
	while (true) {
		try
		{
			char str1[] {"Hello, World!"};	//Строка Си-типа
			char str2[] {"Hello, Space!"};	//Строка Си-типа
			
			cout << str1 << "\t\t" << str2 << '\n';
			int str_compare {strcmpr(str1, str2)};
			if (str_compare < 0)		cout << "Second greater" << "\n\n";
			else if (str_compare > 0)	cout << "First greater" << "\n\n";
			else						cout << "Equale" << "\n\n";
			
			cout << str2 << "\t\t" << str1 << '\n';
			str_compare = strcmpr(str2, str1);
			if (str_compare < 0)		cout << "Second greater" << "\n\n";
			else if (str_compare > 0)	cout << "First greater" << "\n\n";
			else						cout << "Equale" << "\n\n";
			
			
			
			char abc1[] {"abc"};	//Строка Си-типа
			char abc2[] {"abc"};	//Строка Си-типа
			char abc3[] {"abcd"};	//Строка Си-типа
			
			cout << abc1 << "\t\t" << abc2 << '\n';
			str_compare = strcmpr(abc1, abc2);
			if (str_compare < 0)		cout << "Second greater" << "\n\n";
			else if (str_compare > 0)	cout << "First greater" << "\n\n";
			else						cout << "Equale" << "\n\n";
			
			cout << abc1 << "\t\t" << abc3 << '\n';
			str_compare = strcmpr(abc1, abc3);
			if (str_compare < 0)		cout << "Second greater" << "\n\n";
			else if (str_compare > 0)	cout << "First greater" << "\n\n";
			else						cout << "Equale" << "\n\n";
			
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