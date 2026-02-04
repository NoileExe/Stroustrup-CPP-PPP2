
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

class EOF_throw {}; //При нажати CTRL+Z / CTRL+D или встрече конца файла
const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------

//Получение от пользователя имени файла для ввода или вывода
string get_file_name(string greetings)
{
	cout << greetings;
	
	string ioname;
	cin >> ioname;
	
	return ioname;
}

//Пропуск любых символов пока не будет достигнуто число
void skip_to_int(istream& ist)
{
	if (ist.fail()) {			//найдено что-то не являющееся целым числом
		ist.clear();			//пробуем получить символ
		char ch;
		while (ist>>ch){		//пропускаем всё что не является числами
			if (isdigit(ch)) {	//как только встретили число - 
				ist.unget();	//возвращаем символ обратно в поток ввода
				return;
			}
		}
	}
	
	error("Нет ввода");			// eof или bad
}


int get_int(istream& ist)
{
	int n = 0;
	
	while(true) {
		if (ist >> n)	return n;
		
		cout << "\nВведённое не является числом. Попробуйте ещё раз.\n";
		skip_to_int(ist);
	}
}


int main()
{
	while (true) {
		try
		{
			string ioname = get_file_name("Введите имя файла с числами: ");
			
			ifstream ifs { ioname };
			if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
			
			double summ {0};
			
			while ( !ifs.eof() ) {
				//int n = get_int(ifs);
				summ += get_int(ifs);
			}
			
			ifs.close();
			cout << "summ: " << summ;
			
			
			if ( Y_or_N(quit_question) )	return 0;
		}

		catch (exception& e) { //Для системных исключений при работе с программой
			cerr << "Ошибка: " << e.what() << '\n';
			if ( Y_or_N(quit_question) )	return 1002;
		}

		catch (...) { //Для непредвиденных исключений
			cerr << "Упс! Неизвестное исключение!\n";
			if ( Y_or_N(quit_question) )	return 1003;
		}
	}
}