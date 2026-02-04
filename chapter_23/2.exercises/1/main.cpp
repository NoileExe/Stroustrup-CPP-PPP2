


#include "mail.h"

const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Mail_file mfile {"bad.txt"};		//Инициализация объекта данными из файла
			//Mail_file mfile {"clear.txt"};		//Инициализация объекта данными из файла
			
			//Сначала собираем сообщения, поступившие от каждого отправителя, в объекте multimap
			multimap<string, const Message*> sender;
			
			for(const auto& m : mfile) {
				string s;
				if(find_from_addr(&m,s))		sender.insert( make_pair(s, &m) );
			}
			
			//Теперь обходим мультиотображение и извлекаем темы сообщений, поступивших от John Doe
			//Возвращает пару итераторов: первый указывает на первый встреченный элемент в упорядоченной последовательности,
			// второй - на элемент следующий за последним совпадающим по условию
			auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
			for(auto p = pp.first; p != pp.second; ++p)		cout << "!.\t" << find_field(p->second, "Subject: ") << endl;
			
			cout << "\n\n\n\n";
			
			//Так мог бы выглядеть оператор вывода для объектов Mail_file
			for(const auto& m : mfile) {
				for(const auto& s : m)		cout << s << endl;
				cout << *(m.end()) << endl;
				
				//Полностью аналогичный результат
				//for(auto it = m.begin(); it != m.end()+1; ++it)		cout << *it << endl;
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