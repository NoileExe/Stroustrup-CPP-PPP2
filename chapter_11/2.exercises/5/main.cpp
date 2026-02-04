
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

int main() {
	while(true)
	try {
			cout << "\nВведите строку: ";
			
			string str {""};
			getline(cin, str);
			//cin >> str;
			
			if ( cin.eof() )	break;
			
			for (int i = 0; i < str.size(); ++i)
			{
				unsigned char ch = static_cast<unsigned char>(str[i]);
				cout << "\n\n" << '[' << ch << ']' << '\n';
				
				if ( isprint(ch) ) {
					cout << i << ". Печатаемый символ";
					
					if ( isspace(ch) )
						cout << "; пробельный символ (разделитель)";
					
					else if ( isalnum(ch) ) {
						
						if ( isalpha(ch) ) {
							if ( isupper(ch) )
								cout << "; буква в верхнем регистре";
							else if ( islower(ch) )
								cout << "; буква в нижнем регистре";
							
							if ( isxdigit(ch) )
								cout << "; может быть частью 16тиричного числа";
						}
						
						else if ( isdigit(ch) )
							cout << "; может быть частью числа";
					}
				}
					
				else if ( iscntrl(ch) )
					cout  << i << ". Управляющий символ";
					
				if ( ispunct(ch) )
					cout  << '\n' << i << ". Cимвол не является ни буквой, ни цифрой, ни разделителем, ни управляющим символом";
					
				if ( isgraph(ch) )
					cout  << '\n' << i << ". Буква или цифра или ispunct(ch), но при этом не пробел";
			}
		
		if ( Y_or_N(quit_question) )	return 0;
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		
		if ( Y_or_N(quit_question) )	return 1001;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		
		if ( Y_or_N(quit_question) )	return 1002;
	}
}