

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------


const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//Поиск кавычек в тексте
bool text_in_quotes(const string& str) {
	for (char ch : str)
		if ( ch == '"' )
			return true;
	
	return false;
}


int main() {
	while(true)
	try {
		string punct_signs {".;,?-'"};
		
		
		cout << "Введите строку: ";
		string line {""};
		getline(cin, line);
		
		//Убираем ненужные символы
		for (int i = 0; i < line.size(); ++i) {
			
			//текст внутри двойных кавычек не трогаем  // '"' aka char(34)
			if (  line[i] == '"'  &&  text_in_quotes( line.substr(i+1, line.size()-(i+1)) )  )
			{
				do
				{
					++i;
				}
				while ( line[i] != '"' );
			}
			
			for (char ch : punct_signs)
				if ( line[i] == ch )
				{
					line[i] = ' ';
					break;
				}
		
		}
		
		cout << "отформатированная строка = [" << line << "]";
		
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