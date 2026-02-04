
#include "roman_int.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

class EOF_throw {}; //При нажати CTRL+Z / CTRL+D или встрече конца файла
const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

//Получение от пользователя имени файла для ввода или вывода
string get_file_name(string msg) {
	cout << msg;
	
	string ioname;
	cin >> ioname;
	
	return ioname;
}


int main()
{
	while (true)
	try {
		Roman_int ri;
		/*cout << ri << '\t' << ri.as_int() << '\n';
		cout << Roman_int(10) << '\t' << Roman_int(10).as_int() << '\n';
		cout << Roman_int("XX") << '\t' << Roman_int("XX").as_int() << '\n';
		
		cout << Roman_int(19) + Roman_int("XX") << '\t' << (Roman_int(19) + Roman_int("XX")).as_int() << '\n';
		cout << Roman_int("II") * Roman_int(3) << '\t' << (Roman_int("II") * Roman_int(3)).as_int() << '\n';
		
		
		cout << "Введите римское число: ";
		cin >> ri;
		cout << ri << '\t' << ri.as_int() << '\n';*/
		
		string ioname = get_file_name("Введите имя файла с римскими числами на проверку:\n");
		
		ifstream ifs { ioname };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);    // throw for bad()
		
		//----------------------------------------------------------------------------------------------------
		
		vector<Roman_int> RonamsNums;
		
		for (Roman_int ri; ifs >> ri; )
			RonamsNums.push_back(ri);
		
		ifs.close();
		
		//----------------------------------------------------------------------------------------------------
		
		ioname = get_file_name("Введите имя файла для вывода:\n");
		
		ofstream ofs { ioname };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		for ( Roman_int ri : RonamsNums )
			ofs << ri << '\t' << ri.as_int() << '\n';
		
		ofs.close();
		
		if ( Y_or_N(quit_question) )	return 0;
		//keep_window_open("~~");
	}

	/*catch (EOF_throw) {
		cerr << "\nПрограмма завершена пользователем.";
		keep_window_open("~~");
		return 1001;
	}*/

	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		
		if ( Y_or_N(quit_question) )	return 1002;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		
		if ( Y_or_N(quit_question) )	return 1003;
	}
}