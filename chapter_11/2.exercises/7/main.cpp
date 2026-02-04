

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
		
		//n't в словах вроде don't и can't заменяем на not
		for (int i = 0; i < line.size(); ++i)
			if ( line[i] == '\'' ) // '\'' aka char(39)
				if ( line[i-1] == 'n'  &&  line[i+1] == 't' ) {
					line = line.substr(0, i-1)  +  " not"  +  line.substr(i+2, line.size()-(i+2));
					break;
				}
		
		//Убираем ненужные символы
		for (int i = 0; i < line.size(); ++i) {
			//Всебуквы делаем прописными
			line[i] = tolower(line[i]);
			
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
				if ( line[i] == ch ) {
					//Дефис в словах не трогаем
					if ( ch == '-'  &&  isalpha(line[i-1])  &&  isalpha(line[i+1]) )
						{ }
					else
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