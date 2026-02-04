

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include "mail.h"


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Является ли строка p первой частью строки s
//Возвращает размер строки p
int is_prefix(const string& s, const string& p)
{
	int n = p.size();
	
	//Часть строки s от 0-го до n-го символа
	if( string(s,0,n) == p )		return n;
	return 0;
}

//Ищет отправителя в объекте класса Message
//Возвращает true если он найден; также если найден - отправитель помещается в строку s
bool find_from_addr(const Message* m, string& s)
{
	for(const auto& x : *m)
		if( int n = is_prefix(x, "From: ") ) {
			s = string(x, n);	//Все символы строки x начиная с элемента x[n] (n-ый символ)
			return true;
		}
	
	return false;
}

//Возвращает тему сообщения. Если её нет - возвращает пустую строку ""
string find_subject(const Message* m)
{
	for(const auto& x : *m)
		if( int n = is_prefix(x, "Subject: ") )		return string(x, n);	//Все символы строки x начиная с элемента x[n] (n-ый символ)
	
	return "";
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Mail_file mfile {"in.txt"};		//Инициализация объекта данными из файла
			
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
			for(auto p = pp.first; p != pp.second; ++p)		cout << "!.\t" << find_subject(p->second) << endl;
			
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