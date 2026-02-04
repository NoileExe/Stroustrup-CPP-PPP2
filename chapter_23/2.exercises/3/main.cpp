


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

//На вход ссылка на объект со считанным файлом почты и регулярное выражение ввиде строки
void search_mails(const Mail_file& mfile, const string& pat)
{
	string val { get_kb_line("Enter the value of field to search") };
	
	cout << "Search result for \"" << val << "\"\n\n";
	regex pattern;
	try { pattern = pat + "(" + val + ")$"; }
	catch (...) {
		ostringstream ss;
		ss << "'" << pat << "(" << val << ")$" << "' is not a valid regular expression [search_mails()]";
		error( ss.str() );
	} 
	
	//Собираем сообщения совпадающие с указанным регулярным выражением
	vector<const Message*> vals;
	for(const auto& m : mfile)
		for(const auto& s : m) {
			smatch matches;
			if ( regex_match(s, matches, pattern) )	{ vals.push_back(&m);	break; }
		}
	
	//Вывод писем совпавших с указанным шаблоном (регулярным выражением)
	for(auto m : vals)
	{
		for(const auto& s : *m)		cout << s << endl;
		cout << *(m->end()) << endl;
	}
}


int main()
{
	while (true) {
		try
		{
			Mail_file mfile {"in.txt"};		//Инициализация объекта данными из файла
			
			//John Doe <jdoe@machine.example>
			while(true) {
				cout << "SEARCH BY SENDER'S FULL NAME & EMAIL ADDRESS\n\n";
				search_mails(mfile, "^(From:\\s*)");
				cout << "\n\n\n\n";
				if( !Y_or_N("Would you like to search further by email sender?") )		break;
				cout << "\n\n\n\n";
			}
			
			cout << "\n------------------------------------------------------------------------------\n";
			
			//Saying Hello
			while(true) {
				cout << "SEARCH BY EMAIL SUBJECT\n\n";
				search_mails(mfile, "^(Subject:\\s*(Fw:|Re:)?\\s*)");
				cout << "\n\n\n\n";
				if( !Y_or_N("Would you like to search further by email subject?") )		break;
				cout << "\n\n\n\n";
			}
			
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