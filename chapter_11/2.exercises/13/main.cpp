

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
		string ioname;
		
		cout << "Укажите файл-источник ввода: ";
		getline(cin, ioname);
		
		ifstream ifs { ioname };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);
		
		vector<string> txt;
		
		for (string line; getline(ifs, line); )
			txt.push_back(line);
		
		//----------------------------------------------------------------------------------------------------
		
		//Меняем слова местами в каждой строке. Все промежутки между словами заменяются на обычный пробел
		for (string& line : txt)
		{
			vector<string> words { split(line) };
			line = "";
			
			for (int i = words.size()-1; i >= 0; --i)
			{
				if ( i != 0 )
					line += words[i] + ' ';
				else
					line += words[i];
			}
		}
		
		//----------------------------------------------------------------------------------------------------
		
		ifs.close();
		
		ofstream ofs { ioname };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		for (string& line : txt)
			ofs << line << '\n';
		
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