


#include "mail.h"
#include <regex>
#include <unordered_map>
#include <chrono>	//Выяснение текущего времени и вычисление разности в промежутке времени
#include <iomanip>	//Для возможности форматирования потока вывода


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Mail_file mfile {"in.txt"};		//Инициализация объекта данными из файла
			
			
			
			auto t1 = chrono::system_clock::now();
			
			//Собираем сообщения с запоминанием отправителя в объекте multimap
			{
				multimap<string, const Message*> sender;
				for(const auto& m : mfile) {
					string s;
					if(find_from_addr(m,s))		sender.insert( make_pair(s, &m) );
				}
			}
			
			auto t2 = chrono::system_clock::now();
			
			//Собираем сообщения с запоминанием отправителя в объекте unordered_multimap
			{
				unordered_multimap<string, const Message*> sender;
				for(const auto& m : mfile) {
					string s;
					if(find_from_addr(m,s))		sender.insert( make_pair(s, &m) );
				}
			}
			
			auto t3 = chrono::system_clock::now();
			
			cout << left << setw(32)<< "\n\nfor MULTIMAP time: "
				 << chrono::duration_cast< chrono::milliseconds >(t2-t1).count() << "(ms) | "
				 << chrono::duration_cast< chrono::microseconds >(t2-t1).count() << "(mcs) | "
				 << chrono::duration_cast< chrono::nanoseconds >(t2-t1).count() << "(ns)\n";
			
			cout << left << setw(30) << "for UNORDERED_MULTIMAP time: "
				 << chrono::duration_cast< chrono::milliseconds >(t3-t2).count() << "(ms) | "
				 << chrono::duration_cast< chrono::microseconds >(t3-t2).count() << "(mcs) | "
				 << chrono::duration_cast< chrono::nanoseconds >(t3-t2).count() << "(ns)\n";
			
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