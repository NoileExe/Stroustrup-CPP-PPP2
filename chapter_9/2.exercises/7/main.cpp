
#include "biblio.h"
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

int main()
{
	int calc_err = 1;
	vector<biblio::Book> my_bs; //my bookshelf
	
	//Указаны все данные
	my_bs.push_back(biblio::Book {"2-22-222-F", "Pushkin", "Pushkin", biblio::Genre::lyrics, Chrono::Date(12, Chrono::Month::march, 1825), true});
	
	//Инициализация без указания наличия (по умолчанию в наличии)
	my_bs.push_back( biblio::Book("3-33-333-Z", "Kukushkin", "Kukushkin", biblio::Genre::prose, Chrono::Date(29, Chrono::Month::december, 2018) ) );
	
	//Указаны все данные (дата по умолчанию)
	my_bs.push_back( biblio::Book("4-44-444-u", "Pushkin", "Pushkin", biblio::Genre::lyrics, Chrono::Date(), false ) );
	
	//Никаких данных не указано (конструктор по умолчанию)
	my_bs.push_back( biblio::Book() );
	
	
	while (true)
	try
	{
		using namespace biblio;
		Book one_book;
		
		//Добавляем вручную книгу - проверка класса и оператора ввода
		cin >> one_book;
		
		for (int i = 0; i < my_bs.size(); ++i)
			if (one_book == my_bs[i])
				error("Такая книга уже имеется"); //"Книга с указанным ISBN уже имеется"
		
		my_bs.push_back(one_book);
		
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
