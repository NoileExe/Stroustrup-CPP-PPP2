
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//от А до П срабатывает прекрасно для файлов в кодировке UTF-8
//Остальные символы не получилось обработать корректно
/*char rustolower(char ch)
{
	//		русская А						русская П
	if (  char(0xD090) <= ch  &&  ch <= char(0xD09F) )
		return char( ch + 32 );
	
	//		русская Р						русская Я
	if (  char(0xD0A0) <= ch  &&  ch <= char(0xD0AF) )
		return char( abs(ch) + 107 );
		//return char( ch + abs(0xD180 - 0xD0A0) );
	
	else if ( ch == char('Ё') )
		return char('ё');
	
	return ch;
}*/


/*int rustolower(wchar_t ch)
{
	wcout << '\n' << ch;
	
	//		русская А						русская П
	if (  0xD090 <= ch  &&  ch <= 0xD09F )
		return ch + 32;
	
	switch (ch){
		
		case 'Ё':		return 'ё';
		
		
		case 0xD0A0:	return 0xD180;
		
		default:		return ch;
	}
}*/


int main() {
	while(true)
	try {
		string ioname {""};
		
		cout << "Укажите файл-источник ввода: ";
		getline(cin, ioname);
		
		wifstream ifs { ioname };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);
		
		
		cout << "Укажите файл куда стоит вывести результат: ";
		getline(cin, ioname);
		
		wofstream ofs { ioname };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		//Работает только с английскими буквами
		for (wchar_t ch; ifs.get(ch); )
			//if ( 'A' <= ch  &&  ch <= 'Z' ) // isalpha(ch)  &&  isupper(ch)
				{ ofs << wchar_t( tolower(ch) ); }
			//else
				//{ ofs << wchar_t( rustolower(ch) ); }
		
		ifs.close();
		ofs.close();
		
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