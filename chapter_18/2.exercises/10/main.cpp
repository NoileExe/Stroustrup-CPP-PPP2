

#include <cstring>
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//'s' - первый символ массива (C-строки) из 'n' символов
//возвращает true если влово является палиндромом
bool is_palindrome(const char s[], int n);

char* mirror_word (const char* s, int n);		//Возвращает указатель на строку в динамической памяти, которая вяляется зеркальной копией входной строки (задом наперёд)
int strcmpr(const char* s1, const char* s2);	//Сравнение двух c-строк
void strcopy (char* src, char* trgt);			//Копирует строку из src в trgt



//Считывает из указанного потока ввода символы в массив 'buffer'
//При превышении максимально допустимой длины слова для ввода (аргумент max) выдаёт сообщение в поток вывода
istream& read_word_msg(istream& is, char* buffer, int max)
{
	if (max <= 0)		{ delete[] buffer;		error("negative max border [read_word_msg()]"); }
	
	*buffer = 0;
	char ch {0};
	
	for(int i=0; is.get(ch)  &&  i < max; ++i)
		if ( !isspace(ch) )		{ *(buffer+i) = ch;		*(buffer+i+1) = 0; }
		else					break;
	
	if ( !is  &&  !is.eof() )	{ delete[] buffer;		error("bad input"); }
	if ( is.eof() )				return is;
	if ( *buffer == 0 )			return read_word_msg(is, buffer, max);
	
	//Сообщение и игнорирование последующих символов
	if (ch != '\n') {
		cout << "\n\nword length exceeded max length(" << max << "). All other characters in that line will be ignored\n\n";
		while (is.get() != '\n')	is.clear(); //Игнорируем символы до перехода на новую строку
	}
	
	is.unget();
	return is;
}

//------------------------------------------------------------------------------

//Считывает из указанного потока ввода символы в массив 'buffer'
istream& read_word_inf(istream& is, char*& buffer) {
	int max{3};
	char* str = new char[max];
	*str = 0;
	
	char ch{0};
	int indx{0};	//Текущий индекс
	while ( is.get(ch) )
	{
		if ( !is  &&  !is.eof() )			{ delete[] buffer;		error("bad input"); }
		if ( is.eof() )						return is;
		if ( *str != 0  &&  ch == '\n' )	break;
		if ( ch == '\n' )					ch = 0;		//Позволит не смещать указатель
		
		is.clear();
		
		//Добавляем новый символ в конец строки
		if ( indx < max ) {
			str[indx] = ch;
			if (ch != 0)	str[++indx] = 0;	//Добавить нуль терминатор, но перед этим увеличить значение индекса
		}
		
		if ( strlen(str) == max ) {
			char* tmp2 = new char[max];
			strcopy(str, tmp2);
			delete[] str;
			
			max *= 2;
			str = new char[max];
			strcopy(tmp2, str);
			
			delete[] tmp2;
		}
	}
	
	buffer = str;
	return is;
}

//------------------------------------------------------------------------------

//'s' - первый символ массива (C-строки) из 'n' символов
//возвращает true если влово является палиндромом
bool is_palindrome(const char s[], int n)
{
	int first  {0};			//Индекс первой буквы
	int last {n - 1};		//Индекс последней буквы
	
	while (first < last)	//Середина слова не достигнута
	{
		if (s[first] != s[last])	return false;
		++first;	//Переход вперёд
		--last;		//Переход назад
	}
	
	return true;
}

//Возвращает указатель на строку в динамической памяти, которая вяляется зеркальной копией входной строки (задом наперёд)
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

//Копирует строку из src в trgt
void strcopy (char* src, char* trgt) {
	for(int i=0; i <= strlen(src); ++i)		trgt[i] = src[i];
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\nThe program determines whether the word entered by the user is a palindrome or not. Several methods and approaches are used.\n\nEnter words (CTRL+Z to exit):\n\n";
			
			cout << "At the first stage, the maximum word length is 4 characters\n\n";
			
			//Палиндром с использованием массива символов
			constexpr int max {4};
			for(char s[max]; read_word_msg(cin, s, max); ) {
				cout << s << " is";
				if ( !is_palindrome(s, strlen(s)) )		cout << " NOT";
				cout << " a palindrome (array of symbols)\n";
				
				char* p1 = mirror_word(s, strlen(s));
				cout << s << " is";
				if ( strcmpr(s, p1) != 0 )		cout << " NOT";
				cout << " a palindrome (c-strings cmp)\n";
				delete[] p1;
				
				cout << "\n\n";
			}
			
			if ( !cin  &&  !cin.eof() )		error("bad input");
			cin.clear();
			
			cout << "\n\nAt the second stage, the length of the word is not limited\n\n";
			
			char* s;
			while( true ) {
				char* s;
				read_word_inf(cin, s);
				if ( !cin  &&  !cin.eof() )		{ delete s;		error("bad input"); }
				if ( cin.eof() )				break;
				
				cout << s << " is";
				if ( !is_palindrome(s, strlen(s)) )		cout << " NOT";
				cout << " a palindrome (array of symbols)\n";
				
				char* p1 = mirror_word(s, strlen(s));
				cout << s << " is";
				if ( strcmpr(s, p1) != 0 )		cout << " NOT";
				cout << " a palindrome (c-strings cmp)\n";
				
				delete[] p1;
				delete s;
				cout << "\n\n";
			}
			
			delete s;
			
			if ( !cin  &&  !cin.eof() )		error("bad input");
			cin.clear();
			
			keep_window_open("~~");
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