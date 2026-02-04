

#include <cstring>
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

bool is_palindrome(const string& s)
{
	int first {0};					//Индекс первой буквы
	int last = s.length() - 1;		//Индекс последней буквы
	
	while (first < last)			//Середина слова не достигнута
	{
		if (s[first] != s[last])	return false;
		++first;	//Переход вперёд
		--last;		//Переход назад
	}
	
	return true;
}

//------------------------------------------------------------------------------

//Считывает из указанного потока ввода не более 'max-1' символов в массив 'buffer'
istream& read_word(istream& is, char* buffer, int max) {
	is.width(max);		//Следующий оператор >> считает не более max-1 символов
	is >> buffer;		//Читается слово оканчивающееся пробельным символом,
						//в конец автоматически добавляется нуль-терминатор
	return is;
}


//'s' - первый символ массива (C-строки) из 'n' символов
bool is_palindrome(const char s[], int n)
{
	int first {0};			//Индекс первой буквы
	int last {n - 1};		//Индекс последней буквы
	
	while (first < last)	//Середина слова не достигнута
	{
		if (s[first] != s[last])	return false;
		++first;	//Переход вперёд
		--last;		//Переход назад
	}
	
	return true;
}

//------------------------------------------------------------------------------

//Указатель 'first' указывается на первую букву слова в памяти, 'last' - на последнюю
bool is_palindrome(const char* first, const char* last)
{
	while (first < last)	//Середина слова не достигнута
	{
		if (*first != *last)	return false;
		++first;	//Переход вперёд
		--last;		//Переход назад
	}
	
	return true;
}


bool is_palindrome_recursive(const char* first, const char* last)
{
	if (first < last)
	{
		if (*first != *last)	return false;
		return is_palindrome_recursive(first+1, last-1);
	}
	
	return true;
}

//------------------------------------------------------------------------------

string mirror_word (const string& s) {
	string str;
	for (int i = s.size()-1; i >= 0; --i)		str += s[i];
	return str;
}

char* mirror_word (const char* s, int n) {
	char* str = new char[n+1];
	for (int i = 0; i < n; ++i)		str[i] = s[n-i-1];
	str[n] = 0;
	return str;
}

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
			cout << "\n\nThe program determines whether the word entered by the user is a palindrome or not. Several methods and approaches are used.\n\nEnter words (CTRL+Z to exit):\n\n";
			
			//Палиндром с использованием string
			for(string s; cin>>s; ) {
				cout << s << " is";
				if (!is_palindrome(s))		cout << " NOT";
				cout << " a palindrome (string)\n";
				
				cout << s << " is";
				if ( s != mirror_word(s) )		cout << " NOT";
				cout << " a palindrome (strings cmp)\n";
				
				cout << "\n\n";
			}
			cout << "\n\n\n\nEnter words (max length = 128):\n\n";
			
			if ( !cin  &&  !cin.eof() )		error("bad input");
			cin.clear();
			
			
			//Палиндром с использованием массива символов
			constexpr int max {128};
			for(char s[max]; read_word(cin, s, max); ) {
				cout << s << " is";
				if ( !is_palindrome(s, strlen(s)) )		cout << " NOT";
				cout << " a palindrome (array of symbols)\n";
				
				cout << s << " is";
				if ( !is_palindrome(&s[0], &s[strlen(s)-1]) )		cout << " NOT";
				cout << " a palindrome (with pointers)\n";
				
				cout << s << " is";
				if ( !is_palindrome_recursive(&s[0], &s[strlen(s)-1]) )		cout << " NOT";
				cout << " a palindrome (pointers recursive method)\n";
				
				char* p1 = mirror_word(s, strlen(s));
				cout << s << " is";
				if ( strcmpr(s, p1) != 0 )		cout << " NOT";
				cout << " a palindrome (c-strings cmp)\n";
				delete[] p1;
				
				cout << "\n\n";
			}
			
			if ( !cin  &&  !cin.eof() )		error("bad input");
			cin.clear();
			
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