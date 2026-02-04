


#include "mail.h"

const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Добивается от пользователя ввода темы сообщения
string get_kb_subject()
{
	string str {""};
	while(true)
	{
		cout << "\nEnter the subject of the message to search\n\n> ";
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

void print_subj_mails(const Mail_file& mfile)
{
	string subj { get_kb_subject() };
	
	cout << "All emails with subject \"" << subj << "\"\n\n";
	
	auto pp = mfile.sm.equal_range(subj);
	for(auto p = pp.first; p != pp.second; ++p)
	{
		for(const auto& s : p->second)		cout << s << endl;
		cout << *(p->second.end()) << endl;
	}
}


int main()
{
	while (true) {
		try
		{
			Mail_file mfile {"in.txt"};		//Инициализация объекта данными из файла
			
			//------------------------------------------------------------------------------
			
			//Сначала собираем сообщения, поступившие от каждого отправителя, в объекте multimap
			multimap<string, const Message*> sender;
			
			for(const auto& m : mfile) {
				string s;
				if(find_from_addr(m.second,s))		sender.insert( make_pair(s, &m.second) );
			}
			
			cout << "All emails with sender \"John Doe <jdoe@machine.example>\"\n\n";
			
			//Теперь обходим мультиотображение и извлекаем темы сообщений, поступивших от John Doe
			//Возвращает пару итераторов: первый указывает на первый встреченный элемент в упорядоченной последовательности,
			// второй - на элемент следующий за последним совпадающим по условию
			auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
			for(auto p = pp.first; p != pp.second; ++p)		cout << "!.\t" << find_field(*(p->second), "Subject: ") << endl;
			
			cout << "\n\n\n\n";
			
			//------------------------------------------------------------------------------
			
			while(true) {
				print_subj_mails(mfile);
				if( !Y_or_N("Would you like to search further by email subject?") )		break;
			}
			
			//------------------------------------------------------------------------------
			
			//Так мог бы выглядеть оператор вывода для объектов Mail_file
			/*for(const auto& m : mfile) {
				for(const auto& s : m.second)		cout << s << endl;
				cout << *(m.second.end()) << endl;
				
				//Полностью аналогичный результат
				//for(auto it = m.second.begin(); it != m.second.end()+1; ++it)		cout << *it << endl;
			}*/
			
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