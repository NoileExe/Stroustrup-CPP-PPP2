

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
		
		cout << "Укажите файл-источник бинарного ввода: ";
		getline(cin, ioname);
		
		ifstream ifs { ioname, ios_base::binary };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);
		
		
		cout << "Укажите файл для вывода результата: ";
		getline(cin, ioname);
		
		ofstream ofs { ioname };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		//----------------------------------------------------------------------------------------------------
		
		/*
		for (int num; ifs.read(as_bytes(num), sizeof(int)); )
			ofs << num << '\n';
		*/
		
		vector<int> v;
		
		for (int num; ifs.read(as_bytes(num), sizeof(int)); )
			v.push_back(num);
		
		for (int i : v)
			ofs << i << '\n';
		
		
		
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