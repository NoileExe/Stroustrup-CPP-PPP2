


//Включает <yes_or_no.h> (в свою очередь включает <string>, <iostream>), <regex>, <fstream>, <sstream>, <iomanip>
#include "Document.h"

const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Добивается от пользователя ввода исправной строки
string get_kb_line(const string& question)
{
	string str {""};
	while(true)
	{
		cout << "\n" << question << "\n\n> ";
		getline(cin, str);
		
		if( (cin.good() && str.size())  ||  cin.eof() )		break;
		else {
			str = "";
			cin.clear(ios_base::goodbit);
		}
	}
	
	//Возвращаем ответ введённый пользователем
	return str;
}

//------------------------------------------------------------------------------

//Получает из входного потока шаблон и набор строк;
// проверяет корректность шаблона и ищет строки, содержащие его
int main()
{
	while (true) {
		try
		{
			string file_name { get_kb_line("Enter the name of the input file:") };
			Document doc {file_name};
			
			//Вывод содержимого файла на экран
			//for(auto str : doc)		cout << str;
			
			
			while(true)
			{
				regex pattern;
				string tmp { get_kb_line("Enter the string pattern (CTRL+Z to exit)") };
				if( cin.eof() )		{ cin.clear();	break; }
				
				try { pattern = tmp; }
				catch (...) { cerr << "'" << tmp << "' is not a valid regular expression";		pattern = ""; }
				
				smatch matches;
				
				tmp = "";
				//Если неверно указан шаблон - повторный запрос ввода (сообщение об ошибке уже было выведено выше)
				if( regex_match(tmp, matches, pattern) )	{ cout << "empty regex pattern string" << endl; }
				
				//Проверка есть ли вообще в тексте хоть одно совпадение по шаблону
				else if( regex_search(doc.front().begin(), doc.back().end(), matches, pattern) )
				{
					int num {1};		//Номер текущей перебираемой (первой из диапазона) строки
					
					Doc_iter first_str = doc.begin();	//Проверяемый диапазон строк
					Doc_iter last_str  = doc.begin();	//Проверяемый диапазон строк
					
					Line_iter first_ch = first_str->begin();	//Проверяемый диапазон символов
					Line_iter last_ch  = first_str->end();		//Проверяемый диапазон символов
					
					//Перебор всех повторений
					while(first_str != doc.end())
					{
						//Поиск от первой строки совпадений по тексту с расширением диапазона строк за один цикл на одну
						//Соответственно расширяется и диапазон символов, который подлежит сравнению
						while(last_str != doc.end()  &&  !regex_search(first_ch, last_ch, matches, pattern))
							if(++last_str != doc.end())		last_ch = last_str->end();
						
						//Если найдено ещё одно совпадение
						if(regex_search(first_ch, last_ch, matches, pattern))
						{
							//Сужение диапазона спереди для выявления диапазона строк в которых найдено совпадение
							while(first_str != last_str  &&  regex_search(first_ch, last_ch, matches, pattern))
							{
								if(++first_str != doc.end())		first_ch = first_str->begin();
								++num;
							}
							
							//Совпадение по шаблону может охватывать несколько строк и цикл вышел за этот диапазон, значит взвращаем на 1 строку назад
							//Если же совпадение остается, значит оно охватывает лишь одну конкретную строку
							if( first_str != doc.end()  &&  !regex_search(first_ch, last_ch, matches, pattern) )
							{
								--num;
								--first_str;
								first_ch = first_str->begin();
							}
							
							cout << left << setw(10) << ("L" + to_string(num) + ": ") << *first_ch;
							while(first_ch != last_ch)		cout << *(++first_ch);
							
							cout << "\n\n";
						}
						
						
						//Перемещение указателей за текущий диапазон совпадений
						if(last_str != doc.end()) {
							if(++last_str != doc.end())		last_ch = last_str->end();
							else							first_str = last_str;
							
							while(first_str != last_str)
							{
								++first_str;
								first_ch = first_str->begin();
								++num;
							}
						}
						
						else							first_str = last_str;
					}
				}
				
				else		cout << "No matches found";
				
				cout << "\n\n\n\n";
			}
			
			cin.putback('\n');
			keep_window_open("~");
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}