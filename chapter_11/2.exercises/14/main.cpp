

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
		string ioname;
		
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
		
		int spaces_count {0};		//Кол-во пробелов
		int alphas_count {0};		//Кол-во букв
		int decdigits_count {0};	//Кол-во десятичных чисел
		int hexdigits_count {0};	//Кол-во шестнадцатиричных чисел
		int upcase_count {0};		//Кол-во букв в верхнем регистре
		int lowcase_count {0};		//Кол-во букв в нижнем регистре
		int alnum_count {0};		//Кол-во символов, которые могут быть определены как буква или цифра
		int cntrls_count {0};		//Кол-во управляющих символов
		int puncts_count {0};		//Кол-во символов пунктуации
		int prints_count {0};		//Кол-во символов, которые могут быть отображены при печати
		int graphs_count {0};		//Кол-во символов, которые могут быть определены как буква, цифра или символ пунктуации
		
		
		for (char signed_ch; ifs.get(signed_ch); )
		{
			unsigned char ch = static_cast<unsigned char>(signed_ch);
			
			if (isspace(ch))	++spaces_count;
			if (isalpha(ch))	++alphas_count;
			if (isdigit(ch))	++decdigits_count;
			if (isxdigit(ch))	++hexdigits_count;
			if (isupper(ch))	++upcase_count;
			if (islower(ch))	++lowcase_count;
			if (isalnum(ch))	++alnum_count;
			if (iscntrl(ch))	++cntrls_count;
			if (ispunct(ch))	++puncts_count;
			if (isprint(ch))	++prints_count;
			if (isgraph(ch))	++graphs_count;
		}
		
		//----------------------------------------------------------------------------------------------------
		
		ofs << "КОЛИЧЕСТВО СИМВОЛОВ КАЖДОГО ВИДА В ФАЙЛЕ\nОдин и тот же символ может относится сразу к нескольким видам символов.\n\n"
			<< "Кол-во пробелов: " << spaces_count << '\n'
			<< "Кол-во букв: " << alphas_count << '\n'
			<< "Кол-во десятичных чисел: " << decdigits_count << '\n'
			<< "Кол-во шестнадцатиричных чисел: " << hexdigits_count << '\n'
			<< "Кол-во букв в верхнем регистре: " << upcase_count << '\n'
			<< "Кол-во букв в нижнем регистре: " << lowcase_count << '\n'
			<< "Кол-во символов, которые могут быть определены как буква или цифра: " << alnum_count << '\n'
			<< "Кол-во управляющих символов: " << cntrls_count << '\n'
			<< "Кол-во символов пунктуации: " << puncts_count << '\n'
			<< "Кол-во символов, которые могут быть отображены при печати: " << prints_count << '\n'
			<< "Кол-во символов, которые могут быть определены как буква, цифра или символ пунктуации: " << graphs_count << '\n';
		
		
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