
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//Ищет в строке 'source' слово 'find_this' 

bool present_word(const string& source, const string& find_this)
{
	string word {""};
	istringstream ss(source);
	
	while (ss >> word)
		if ( word == find_this )		return true;
	
	return false;
}


int main() {
	while(true)
	try {
		string ioname {""};
		
		cout << "Укажите файл-источник ввода: ";
		getline(cin, ioname);
		
		ifstream ifs { ioname };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);
		
		
		string word {""};
		cout << "Укажите искомое слово: ";
		cin >> word;
		cout << "\n\n";
		
		int count = 0;
		for (int i = 1; getline(ifs, ioname); ++i)
			if ( present_word(ioname, word) )
				{ cout << i << ". " << ioname << "\n\n";    ++count; }
		
		cout << "\n\nВсего найдено строк с указанным словом: " << count << "\n\n";
		
		ifs.close();
		
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