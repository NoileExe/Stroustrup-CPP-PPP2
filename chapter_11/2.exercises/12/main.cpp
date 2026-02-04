

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
		
		//Альтернативное решение для 12 упражнения с заменой всех пространств между словами на обычный пробел
		//Меняем символы местами в каждом слове в каждой строке
		for (string& line : txt)
		{
			vector<string> words { split(line) };
			line = "";
			
			//вариант где пробел не ставится в конце строки
			for (int i = 0; i < words.size(); ++i)
			{
				string str = words[i];
				
				for (int j = 0; j < str.size()/2; ++j)
					swap (str[j], str[str.size()-j-1]);
				
				if ( i != words.size()-1 )		line += str + ' ';
				else							line += str;
			}
		}
		
		
		
		//Меняем символы местами в каждом слове в каждой строке с сохранением пробельных расстояний
		/*for (string& line : txt) {
			for (int i = 0; i < line.size(); ++i) {
				while ( isspace(line[i]) )
					++i;	//пропускаем все пробельные символы
				
				int end = i;
				while ( end+1 <= line.size()-1  &&  !isspace(line[end+1]) )
					++end;	//поиск конца текущего слова
				
				//получаем очередное слово и меняем символы местами
				string word { line.substr(i, i+end+1) };
				
				for (int j = 0; j < word.size()/2; ++j)
					swap (word[j], word[word.size()-j-1]);
				
				//заменяем слово в строке
				string before_word {""};
				string after_word {""};
				
				if ( i == 0 )
					after_word = line.substr(end+1, line.size()-end+1);
				else if (end == line.size()-1)
					before_word = line.substr(0, line.size()-i+1);
				else {
					before_word = line.substr(0, line.size()-i+1);
					after_word = line.substr(end+1, line.size()-end+1);
				}
					
				line = before_word + word + after_word;
				
				
				i = end; //перемещаемся в конец текущего слова, чтобы продолжить перебор сразу после него
			}
		}*/
		
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