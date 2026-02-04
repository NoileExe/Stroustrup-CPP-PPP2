
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//Получение от пользователя имени файла для ввода или вывода
string get_file_name(string greetings) {
	cout << greetings;
	
	string ioname;
	cin >> ioname;
	
	return ioname;
}


int main() {
	while(true)
	try {
		string ioname = get_file_name("\nВведите имя первого файла:\n");
		
		ifstream ifs1 { ioname };
		if (!ifs1)	error("Невозможно открыть файл '" + ioname + "'");
		
		ifs1.exceptions(ifs1.exceptions()|ios_base::badbit);    // throw for bad()
		
		//----------------------------------------------------------------------------------------------------
		
		ioname = get_file_name("\nВведите имя второго файла:\n");
		
		ifstream ifs2 { ioname };
		if (!ifs2)	error("Невозможно открыть файл '" + ioname + "'");
		
		ifs2.exceptions(ifs2.exceptions()|ios_base::badbit);    // throw for bad()
		
		
		ioname = get_file_name("\nВведите имя файла для вывода результата:\n");
		ofstream ofs { ioname }; //{"output.txt"};
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'"); //'output.txt'");
		//----------------------------------------------------------------------------------------------------
		
		vector<string> files_strings;
		
		while ( ifs1 >> ioname )
			files_strings.push_back(ioname);
		
		while ( ifs2 >> ioname )
			files_strings.push_back(ioname);
		
		sort(files_strings); //files_strings.begin(), files_strings.end()
		
		for (string s : files_strings)
			ofs << s << endl;
		
		//----------------------------------------------------------------------------------------------------
		
		ifs1.close();
		ifs2.close();
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