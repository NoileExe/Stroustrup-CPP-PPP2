

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------


const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

int main() {
	while(true)
	try {
		string ioname {""};
		
		cout << "Укажите файл-источник ввода: ";
		getline(cin, ioname);
		
		ifstream ifs { ioname };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);
		
		
		cout << "Укажите файл для бинарного вывода: ";
		getline(cin, ioname);
		
		ofstream ofs { ioname, ios_base::binary };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		//----------------------------------------------------------------------------------------------------
		
		/*
		for (int num; ifs >> num; )
			ofs.write(as_bytes(num), sizeof(int));
		*/
		
		vector<int> v;
		
		for (int num; ifs >> num; )
			v.push_back(num);
		
		for (int i : v)
			ofs.write(as_bytes(i), sizeof(int));
		
		
		
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