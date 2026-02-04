

#include <cstring>
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

//Копирует строку в динамическую память и возвращает указатель на эту память
char* strdupl(const char* s, int max_sz)
{
	if (!s)			error("nullptr argument [strdupl()]");
	if (s == 0)		error("empty c-string [strdupl()]");
	
	int sz = string_ln(s);
	
	//if (sz < max_sz)	error("max_sz value cannot exceed the size of the string [strdupl()]");
	
	char* str = new char[(max_sz < sz) ? max_sz + 1 : sz + 1];
	
	for (int i=0; i < max_sz; ++i) {
		*(str+i) = *(s+i);
		if ( *(s+i) == 0 )		break;
	}
	
	if (max_sz <= sz)
		str[sz] = '\0';
	
	return str;
}

//Поиск подстроки x в строке s; возврат nullptr если не найдена
char* findx (const char* s, const char* x, int max_sz)
{
	if (!s || !x)		error("nullptr argument [strdupl()]");
	if (s == 0)			error("empty c-string [strdupl()]");
	
	
	char* cp {nullptr};
	int sz = string_ln(s);
	
	for (int i=0;   *(s+i) != 0 && i < max_sz;   ++i)
	{
		if (*(s+i) == *x)	//x[0]
			for (int j = 0;   *(x+j) != 0 && j < max_sz;   ++j)
				//Строка закончилась, а паттерн до сих пор не найден? - искомая строка 'x' отсутствует в строке 's'
				if (i+j > sz)						return nullptr;
			
				//Символы в фрагменте и в искомой строке отличаются? - прекращаем перебор фрагмента
				else if ( *(s+i+j) != *(x+j) )		break;
				
				//Строка найдена полностью? (совпало до последнего символа не считая нуль-терминатор) - запоминаем адрес
				else if ( *(x+j+1) == 0 )			cp = const_cast<char*>(&s[i]);
		
		//Первое вхождение найдено? - завершаем поиск
		if (cp)		break;
	}
	
	return cp;
}

//Сравнение двух c-строк
//Если первая строка (s1) лексикографически меньше второй (s2) - возвращается отрицательное число
//При равных строках s1 и s2 ф-ция возвращает нуль
//Если первая строка (s1) лексикографически больше второй (s2) - возвращается положительное число
int strcmpr(const char* s1, const char* s2, int max_sz)
{
	for (int i=0;   *(s1+i) != 0 && i < max_sz;   ++i)
		for (int j = 0;   *(s2+j) != 0 && j < max_sz;   ++j)
			//Второе условие: первая строка закончилась, а вторая - нет
			if ( *(s1+i+j) < *(s2+j)  || \
					 (*(s1+i+j+1) == 0  &&  *(s2+j+1)) )			{ /*cout << *(s1+i+j) << '\t' << *(s2+j+1) << '\n';*/		return -1; }
			
			//Второе условие: вторая строка закончилась, а первая - нет
			else if ( *(s1+i+j) > *(s2+j)  || \
					 (*(s2+j+1) == 0  &&  *(s1+i+j+1)) )			{ /*cout << *(s1+i+j+1) << '\t' << *(s2+j) << '\n';*/		return 1; }
			
			else if ( *(s1+i+j+1) == 0  &&  *(s2+j+1) == 0 )		return 0;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			char str1[] = "Hello, World! XYZhere ?";	//Строка Си-типа
			
			char* goodstr = new char[std::strlen(str1) + 1];
			std::strcpy(goodstr, str1);
			
			cout << "\n\ngoodstr / str1: " << goodstr << "\t\t" << str1 << "\n\n\n";
			
			char* p01 { strdupl(goodstr, strlen(str1)) };
			char* p02 { findx(goodstr, str1, strlen(str1)) };
			int   p03 { strcmpr(goodstr, str1, strlen(str1)) };
			
			cout << "strdupl(goodstr, strlen(str1)): " << p01 << "\n\n";
			
			if (p02)	cout << "findx(goodstr, str1, strlen(str1)): " << p02 << "\n\n";
			else		cout << "'" << str1 << "' DOES NOT contains '" << goodstr << "'\n\n";
			
			cout << "Compare: ";
			if (p03 < 0)			cout << "Second greater\n\n";
			else if (p03 > 0)		cout << "First greater\n\n";
			else					cout << "Equale\n\n";
			
			delete[] goodstr;
			delete[] p01;
			//delete[] p02;		// Не нужно удалять т.к. является адресом на середину ранее удаленной строки p01
			
			press_Enter_key(true);
			cout << "\n\n\n";
			
			//------------------------------------------------------------------------------
			
			char* badstr = new char[strlen(str1)];
			for (int i=0; i <= strlen(str1); ++i) {
				*(badstr+i) = *(str1+i);
				if ( *(str1+i) == 0 )		*(badstr+i) = 'b';
			}
			
			cout << "badstr / str1: " << badstr << "\t\t" << str1 << "\n\n\n";
			
			char* p1 { strdupl(badstr, strlen(str1)) };
			char* p2 { findx(badstr, str1, strlen(str1)) };
			int   p3 { strcmpr(badstr, str1, strlen(str1)) };
			
			cout << "strdupl(badstr, strlen(str1)): " << p1 << "\n\n";
			
			if (p2)		cout << "findx(badstr, str1, strlen(str1)): " << p2 << "\n\n";
			else		cout << "'" << str1 << "' DOES NOT contains '" << badstr << "'\n\n";
			
			cout << "Compare: ";
			if (p3 < 0)			cout << "Second greater\n\n";
			else if (p3 > 0)	cout << "First greater\n\n";
			else				cout << "Equale\n\n";
			
			//Редко вылетает доходя сюда, но чаще просто виснет после ввода символа (иногда не закрывается даже через CTRL+C)
			keep_window_open();
			cout << "\n\n\n";
			
			
			delete[] badstr;
			delete[] p1;
			
			
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