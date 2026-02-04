

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------


const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//Перевод всех символов в нижний регистр;
//Замена n't на not в словах вроде don't и can't
//Удаление символов . ; , ? - ' из строки только если:
//														это не слово как выше (don't не трогаем)
//														это не яв-ся дефисом в слове (as-is)
//														это не текст содержащий заключёный в кавычки ( " - don't use the as-if rule." )
void txtmod(string& line) {
	//Убираем ненужные символы
	for (int i = 0; i < line.size(); ++i)
	{
		//Все буквы делаем прописными (работает только с английскими)
		line[i] = tolower(static_cast<unsigned char>(line[i]));

		switch (line[i])
		{
			case '-': case '\'': //было бы неплохо добавить больше символов
				//Дефис в словах не трогаем
				if (line[i] == '-'  &&  i != 0  && 
					isalpha(static_cast<unsigned char>(line[i - 1])) &&
					isalpha(static_cast<unsigned char>(line[i + 1])) )
				{
				}

				//n't в словах вроде don't и can't заменяем на not; похожим образом можно поступить c 'will' (сокращение 'll)
				else if (i != 0 && line[i]     == '\'' &&
								   line[i - 1] == 'n'  &&
								   line[i + 1] == 't')
				{
					line = line.substr(0, i - 1) + " not" + line.substr(i + 2, line.size() - (i + 2));
				}

				else
				{
					line.erase(i, 1);
					--i;
				}

				break;

			default:
				if ( !isalpha(static_cast<unsigned char>(line[i])) )
				{
					line.erase(i, 1);
					--i;
				}
		}
	}
}

//Считывание отдельных слов из строки в вектор
void str2words(vector<string>& vs, const string& line) {
	istringstream istr (line);
	
	string word;
	
	while ( istr >> word )
		vs.push_back(word);
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
		
		
		cout << "Укажите файл куда стоит вывести результат: ";
		getline(cin, ioname);
		
		ofstream ofs { ioname };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		//----------------------------------------------------------------------------------------------------
		
		string line {""};
		vector<string> dictionary;
		
		while ( getline(ifs, line) )
		{
			vector<string> tmp;
			str2words(tmp, line);

			for (int i = 0, sz = tmp.size(); i < sz; ++i)
			{
				string& tmp_str = tmp[i];
				txtmod(tmp_str);

				if (tmp_str.size())
					dictionary.push_back(tmp_str);
			}
		}
		
		sort(dictionary);
		
		//----------------------------------------------------------------------------------------------------
		
		for (int i = 0; i < dictionary.size(); ++i) {
			if ( i == 0 )
				ofs << dictionary[i] << '\n';
			else if ( dictionary[i] != dictionary[i-1] )
				ofs << dictionary[i] << '\n';
		}
		
		ifs.close();
		ofs.close();
		
		/*
		//Тестирование ф-ции txtmod()
		cout << "Введите строку: ";
		string line {""};
		getline(cin, line);
		txtmod(line);
		cout << "отформатированная строка = [" << line << "]";
		*/
		
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