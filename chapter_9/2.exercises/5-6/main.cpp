
#include "biblio.h"
#include <console_encoding.h>


//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
{
	int calc_err = 1;
	vector<biblio::Book> my_bs; //my bookshelf
	
	while (true) {
		try
		{
			using namespace biblio;
			Book one_book;
			
			my_bs.push_back( Book("2-22-222-F",  "Pushkin", "Pushkin", Chrono::Date(1825,Chrono::Month::mar,12), true ) );	//Указаны все данные
			my_bs.push_back( Book("3-33-333-Z", "Kukushkin", "Kukushkin", Chrono::Date(2018,Chrono::Month::dec,29) ) );		//Инициализация без указания наличия (по умолчанию в наличии)
			my_bs.push_back( Book("4-44-444-u", "Pushkin", "Pushkin", Chrono::Date(), false ) );							//Указаны все данные (дата по умолчанию)
			my_bs.push_back( Book() );																						//Никаких данных не указано (конструктор по умолчанию)
			
			//Добавляем вручную 2 книги - проверка класса и оператора ввода
			for (int i = 0; i<2; ++i) {
				cin >> one_book;
				my_bs.push_back(one_book);
			}
			
			//Проверка оператора вывода для класса Book
			for (int i = 0; i < my_bs.size(); ++i)
				cout << my_bs[i];

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
}
