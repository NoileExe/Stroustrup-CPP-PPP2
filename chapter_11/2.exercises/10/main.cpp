

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//Считывание отдельных слов из строки в вектор
vector<string> split(const string& s) {
	istringstream istr (s);
	string word;
	vector<string> vs;
	
	while ( istr >> word )
		vs.push_back(word);
	
	return vs;
}



int main() {
	while(true)
	try {
		cout << "Введите строку: ";
		string line {""};
		getline(cin, line);
		vector<string> words {split(line)};
		
		for (string s : words)
			cout << s << '\n';
		
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