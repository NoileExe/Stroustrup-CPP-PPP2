


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

char* strdupl(const char* s) {
	if (!s)			error("nullptr argument [strdupl()]");
	if (s == 0)		error("empty c-string [strdupl()]");
	
	int sz = string_ln(s);
	char* str = new char[sz + 1];
	
	for (int i=0; ; ++i) {
		*(str+i) = *(s+i);
		if ( *(s+i) == 0 )		break;
	}
	
	return str;
}

//Такой вид функци выглядит логичнее хотя и не соответствует тексту упражнения
char* findx (const char* s, const char* x)
{
	if (!s || !x)		error("nullptr argument [strdupl()]");
	if (s == 0)			error("empty c-string [strdupl()]");
	
	
	int cp_id {-1};
	int sz = string_ln(s);
	
	for (int i=0;   *(s+i) != 0;   ++i)
	{
		if (*(s+i) == *x)	//x[0]
			for (int j = 0;   *(x+j) != 0;   ++j)
			{
				//Строка закончилась, а паттерн до сих пор не найден? - искомая строка 'x' отсутствует в строке 's'
				if (i+j > sz)						return nullptr;
			
				//Символы в фрагменте и в искомой строке отличаются? - прекращаем перебор фрагмента
				else if ( *(s+i+j) != *(x+j) )		break;
				
				//Строка найдена полностью? (совпало до последнего символа не считая нуль-терминатор) - запоминаем адрес
				else if ( *(x+j+1) == 0 )			cp_id = i;
			}
		
		//Первое вхождение найдено? - завершаем поиск
		if (cp_id >= 0)		break;
	}
	
	return strdupl(s+cp_id);
}

int main()
{
	while (true) {
		try
		{
			char str1[] = "Hello, World! XYZhere ?";	//Строка Си-типа
			char str2[] = "XYZ";	//Строка Си-типа
			cout << str1 << "\t\t" << str2 << '\n';
			
			char* p = {findx(str1, str2)};
			if (p)
			{
				cout << "'" << str1 << "' CONTAINS '" << str2 << "':\n\t";
				cout << &p << "\t\t" << p << '\n';
				delete[] p;
			}
			else
				cout << "'" << str1 << "' DOES NOT contains '" << str2 << "'\n";
				
			
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