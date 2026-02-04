


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Вычисляет длину C-строки
int string_ln (const char* s) {
	int ln {0};
	for(int i=0; *(s+i) != 0; ++i)		++ln;
	return ln;
}


char* cat_dot (const char* s1, const char* s2, const char* pnct = ".")
{
	const int ln { string_ln(s1) + string_ln(s2) + string_ln(pnct) }; 
	char* str = new char[ln+1];		//Последний символ - нуль-терминатор
	
	int indx {0};	//Текущий индекс массива (ячейки памяти) str
	for(int i=0; *(s1+i) != 0; ++i)			{ *(str+indx) = *(s1+i);	++indx; }
	for(int i=0; *(pnct+i) != 0; ++i)		{ *(str+indx) = *(pnct+i);	++indx; }
	for(int i=0; *(s2+i) != 0; ++i)			{ *(str+indx) = *(s2+i);	++indx; }
	
	str[indx] = 0;
	
	return  str;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			char s1[] {"Michale"};	//Строка Си-типа
			char s2[] {"Jackson"};	//Строка Си-типа
			char pnct[] {"\t\t"};		//Строка Си-типа
			
			char* p1 {    cat_dot(s1, s2)    };
			char* p2 { cat_dot(s1, s2, pnct) };
			
			cout << p1 << '\n';
			cout << p2 << '\n';
			
			keep_window_open();
			
			delete[] p1;
			delete[] p2;
			
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