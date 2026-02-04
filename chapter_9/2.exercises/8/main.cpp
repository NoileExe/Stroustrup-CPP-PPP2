
#include "biblio.h"
#include <console_encoding.h>


//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string BOOK_STR = "books";
const string USER_STR = "membership";
string option_BU();

int main()
{
	vector<biblio::Book>   my_lib;		//library
	vector<libman::Patron> lib_mems;	//library members
	
	//Указаны все данные
	my_lib.push_back(biblio::Book {"2-22-222-F", "Pushkin", "Pushkin", biblio::Genre::lyrics, Chrono::Date(12, Chrono::Month::march, 1825), true});
	
	//Инициализация без указания наличия (по умолчанию в наличии)
	my_lib.push_back( biblio::Book("3-33-333-Z", "Kukushkin", "Kukushkin", biblio::Genre::prose, Chrono::Date(29, Chrono::Month::december, 2018) ) );
	
	//Указаны все данные (дата по умолчанию)
	my_lib.push_back( biblio::Book("4-44-444-u", "Pushkin", "Pushkin", biblio::Genre::lyrics, Chrono::Date(), false ) );
	
	//Никаких данных не указано (конструктор по умолчанию)
	my_lib.push_back( biblio::Book() );

	while (true)
	try
	{
		string lib_opt = option_BU();
		
		
		if (lib_opt == BOOK_STR) {
			using namespace biblio;
			Book one_book;
			
			//Добавляем вручную книгу
			cin >> one_book;
			
			for (int i = 0; i < my_lib.size(); ++i)
				if (one_book == my_lib[i])
					error("Такая книга уже имеется"); //"Книга с указанным ISBN уже имеется"
			
			my_lib.push_back(one_book);
		
			for (int i = 0; i < my_lib.size(); ++i) {
				cout << my_lib[i];
			}
		}
		
		else if (lib_opt == USER_STR) {
			using namespace libman;
			Patron one_user;
		
			cin >> one_user;
			lib_mems.push_back(one_user);
		
			for (int i = 0; i < lib_mems.size(); ++i) {
				cout << lib_mems[i];
			}
		}

		if (Y_or_N("Закрыть программу?"))	return 0;
	}
	
	catch (Chrono::CTRL_Z_throw) { 
		if (Y_or_N("Закрыть программу?"))	return 1001;
	}

	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		if (Y_or_N("Закрыть программу?"))	return 1002;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		if (Y_or_N("Закрыть программу?"))	return 1003;
	}
}

//Добивается от пользователя ответа на вопрос с каким классом будет вестись работа;
//неверно введённый ответ затирает пробелами и возвращает каретку на прежнее место.
//Возвращает ответ пользователя в виде строки
string option_BU()
{
	string str = "";
	cin.clear();
	cout << "\nЧто вы хотите сделать - добавить книгу (введите '" << BOOK_STR << "') или"
			" добавить читателя (введите '" << USER_STR << "')?\n";
	
	while ( getline(cin, str) )
	{
		if (cin.eof())
			throw Chrono::CTRL_Z_throw {};
		else if (cin.fail() || str != BOOK_STR && str != USER_STR) //Если ответ не верный
		{
			cin.clear();
			cin.ignore(120, '\n');
		}
		else break;
	}

	return str; //..возвращаем ответ введённый пользователем
}

//------------------------------------------------------------------------------
