
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";


int str2int(string); //Перевод строки в число и проверка на правильность ввода (целое ли, в диапазоне ли integer, не содержит ли недопустимых символов)

//------------------------------------------------------------------------------------------------------------

//Получение от пользователя имени файла для ввода или вывода
string get_file_name(string greetings) {
	cout << greetings;
	
	string ioname;
	cin >> ioname;
	
	return ioname;
}


void summ_file_ints(istream& ist, int& summ)
{
	for (int i; ist >> i; )		summ += i;
	
	if (ist.eof())		return;
	
	ist.clear();
	string clr;
	ist >> clr;
	
	summ_file_ints(ist, summ);
}

int main() {
	while(true)
	try {
		string ioname = get_file_name("\nВведите имя путь к файлу или только его имя (если находится в одном каталоге с программой):\n");
		
		ifstream ifs { ioname };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);    // throw for bad()
		
		//----------------------------------------------------------------------------------------------------
		
		int summ {0};
		summ_file_ints(ifs, summ);
		
		/*
		string str {""};
		int num {0};
		
		while ( ifs >> str ) {
			for (int i = 0; i < str.size(); ++i)
				if ( !isdigit( str[i] )  &&  !( i==0  &&  str[i]=='-' ) )
					break; //пропускаем слово
				else if ( i == str.size()-1 )
					summ += str2int(str);
		}
		*/
		
		cout << "\n\nСумма всех целых чисел найденных в файле = " << summ << endl;
		
		ifs.close();
		
		if ( Y_or_N(quit_question) )	return 0;
		//keep_window_open("~~");
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




int str2int(string str)
/*Проверяем введено ли целое число (допустимость ввода)
На вход подается строка, которая посимвольно проверяет является ли введённое
целым числом, наличие недопустимых символов, а также проверяет не вышло ли
число за диапазон INT*/
{
	double num = 0;
	bool is_negative = false; //Является ли число отрицательным
	
	//Посимвольно проверяем введёную строку на то число ли введено
	for (int i = 0; i < str.size(); ++i) {
		
		//Cъедаем минусы из строки если они стоят в её начале
		while ( i == 0 && str[i] == 45 ) { is_negative = true; str.erase(i,1); }
		
		//Cъедаем нули из строки если они стоят в её начале
		while ( i == 0 && str[i] == 48 )	str.erase(i,1);
		
		//Съели нули и не осталось символов - возвращаем нуль
		if (str.size() == 0)	return 0;
			
		//i-ый символ строки равен символу десятичной ЗПТ (".", ",")
		//(Если число не является целым)
		else if ( str[i] == 44 || str[i] == 46 ) {
			string err_str = "Найден символ десятичной ЗПТ ('.', ','). Значение должно быть целым.";
			throw runtime_error(err_str);
		}
			
		//если текущий символ проверяемой строки по таблице ASCII от 0 до 9
		else if ( str[i] >= 48 && str[i] <= 57 )
															//тек. индекс
						//число УМНОЖИТЬ на 10^ (длина строки - (i+1))
			num = num + (str[i]-48) * pow(10, ( str.size()-(i+1) ));
			
		//Если символ не является ".", ",", "-" (минус может быть только 1ый символом в строке) или числом 0-9
		else {
			string err_str = "Вы ввели что-то не то.";
			throw runtime_error(err_str);
		}
	}
	
	//2147483647
	//2144444444
	//2199999999
	
	//Значение вне диапазона int
	if ( int(num) != num ) {
		string err_str = "Число за пределами диапазона INTEGER.";
		throw overflow_error(err_str);
	}
	
	//Если 1ый символ - символ МИНУС
	else if ( is_negative ) return num*(-1);
	
	else	return num; //Если всё допустимо - передаём данное число как корректно введённое
}