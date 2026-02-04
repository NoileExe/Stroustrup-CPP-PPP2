
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

const vector<char> vowels {'A', 'E', 'I', 'O', 'U', 'Y'};

//проверяет является ли введённый символ гласной буквой
bool is_vovel(char ch)
{
	for (char c : vowels)
		if ( ch == c  ||  ch == tolower(c) )
			return true;
	
	return false;
}


int main() {
	while(true)
	try {
		string ioname {""};
		
		cout << "Укажите файл для ввода: ";
		getline(cin, ioname);
		
		ifstream ifs { ioname };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);
		
		
		cout << "Укажите файл куда стоит вывести результат: ";
		getline(cin, ioname);
		
		ofstream ofs { ioname };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		
		while ( !ifs.eof() )
		{
			string line;
			char ch;
			
			while ( ifs.get(ch) ) {
				if ( !is_vovel(ch) )	line += ch;
				if ( ch == '\n' )		break;
			}
			
			ofs << line;
		}
		
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