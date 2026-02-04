

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
		
		
		cout << "Укажите файл для форматированного вывода: ";
		getline(cin, ioname);
		
		ofstream ofs { ioname };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		//----------------------------------------------------------------------------------------------------
		
		ofs << scientific << setprecision(8);
		
		while (true)
		{
			double num {0};
			int count {0};
			
			while ( count < 4 )
			{
				ifs >> num;
				if (ifs.fail())
				{
					ifs.clear();
					
					string str_trash;
					ifs >> str_trash;	// Считываем некорректные символы в строку и пропускаем их
					
					continue;
				}
				
				++count;
				
				if (count>1)	ofs << "\t" << setw(20) << num;
				else			ofs << setw(20) << num;
				
				if ( ifs.eof() )	break;
			}
			
			ofs << '\n';
			if ( ifs.eof() )	break;
		}
		
		
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