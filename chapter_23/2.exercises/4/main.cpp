


#include "mail.h"
#include <regex>

const string quit_question = "Close program?";

//------------------------------------------------------------------------------
//Добивается от пользователя ввода темы сообщения
string get_kb_line(const string& question)
{
	string str {""};
	while(true)
	{
		cout << "\n" << question << "\n\n> ";
		getline(cin, str);
		
		if(cin.good())		break;
		else {
			str = "";
			cin.clear(ios_base::goodbit);
		}
	}
	
	//Возвращаем ответ введённый пользователем
	return str;
}

//На вход ссылка на объект со считанным файлом почты
void search_mails_by_name(const Mail_file& mfile)
{
	string val { get_kb_line("Enter the value of \"From: \" field to search") };
	
	cout << "Search result for \"" << val << "\"\n\n";
	
	regex pattern;
	string pat = "^(From:\\s*)(" + val + ")\\s*(<" + "[[:alnum:]]+" + "@" + "[[:alnum:]]+" + "." + "[[:alnum:]]{2,}" + ">)$";
	try { pattern = pat; }
	catch (...) { error( "'" + pat + "' is not a valid regular expression [search_mails()]" ); }
	
	//Собираем сообщения совпадающие с указанным регулярным выражением
	int cnt {0};
	for(const auto& m : mfile)
		for(const auto& s : m) {
			smatch matches;
			
			//Вывод тем писем совпавших с указанным шаблоном (регулярным выражением)
			if ( regex_match(s, matches, pattern) )
			{
				cout << ++cnt << ".\t" << find_field(m, "Subject: ") << endl;
				break;
			}
		}
	
	if(!cnt)		cout << "NOTHING WAS FOUND" << endl;
}


int main()
{
	while (true) {
		try
		{
			Mail_file mfile {"in.txt"};		//Инициализация объекта данными из файла
			
			while(true) {
				cout << "SEARCH ALL SUBJECT BY SENDER'S NAME\n\n";
				search_mails_by_name(mfile);
				cout << "\n\n\n\n";
				if( !Y_or_N("Would you like to search further by email sender?") )		break;
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