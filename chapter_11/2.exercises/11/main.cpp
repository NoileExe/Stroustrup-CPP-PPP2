

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//Попадается ли символ ch в строке w
bool is_whitespace(char ch, const string& w)
{
	for (char c : w)
		if ( ch == c )
			return true;
	
	return false;
}

//Считывание из строки в вектор отдельных слов разделённых пробельными символами и символами из строки w
vector<string> split(const string& s, const string& w)
{
	istringstream istr (s);
	string word;
	vector<string> vs;
	
	for (char ch; istr.get(ch); )
	{
		if ( isspace(ch)  ||  is_whitespace(ch, w) )
		{
			if ( word != "" )	vs.push_back(word);
			word = "";
		}
		
		else
			word += ch;
	}
	
	if ( word != "" )	vs.push_back(word);
	return vs;
}



int main() {
	while(true)
	try {
		cout << "Введите строку: ";
		
		string whspaces {";:,.?!()\"\'{}<>/&$@#%^*|~"};
		//cout << '\n' << '\n' << whspaces << '\n';
		
		string line {""};
		getline(cin, line);
		
		vector<string> words {split(line, whspaces)};
		
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