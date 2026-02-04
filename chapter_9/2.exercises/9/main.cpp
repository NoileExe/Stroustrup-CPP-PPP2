
#include "biblio.h"
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

char option_BU(int); //Добивается от пользователя ответа на вопрос какой пункт меню стоит выбрать

void work_with_books(lib_UI::Library& my_lib)
{
	cout << "\nВыберите пункт введя его номер п/п\n"
			"\n1. Вывести список всех книг"
			"\n2. Показать данные по книге"
			"\n3. Добавить книгу"
			"\n4. Регистрация выдачи книги клиенту"
			"\n5. Регистрация возврата книги в библиотеку"
			"\n6. Удалить указанную книгу\n\n";
			
	char lib_opt = option_BU(6);
			
	clear_screen(); //очистка окна консоли
	
	switch(lib_opt) {
		case '1': //1. Вывести список всех книг
			cout << "\n1. Вывести список всех книг\n\n";
			my_lib.print_lib();
			break;
		
		case '2': {//2. Показать данные по книге
			cout << "\n2. Показать данные по книге\n\n";
			string str = my_lib.enter_ISBN();
			my_lib.print_1book(str);
			break;
		}
		
		case '3': //3. Добавить книгу
			cout << "\n3. Добавить книгу\n\n";
			my_lib.add_book();
			break;
		
		case '4': //4. Регистрация выдачи книги клиенту
			cout << "\n4. Регистрация выдачи книги клиенту\n\n";
			my_lib.book2mem();
			break;
		
		case '5': //5. Регистрация возврата книги в библиотеку
			cout << "\n5. Регистрация возврата книги в библиотеку\n\n";
			my_lib.book2lib();
			break;
		
		case '6': {//6. Удалить указанную книгу
			cout << "\n6. Удалить указанную книгу\n\n";
			string str = my_lib.enter_ISBN();
			my_lib.del_1book(str);
			break;
		}
	}
}

void work_with_clients(lib_UI::Library& my_lib)
{
	cout << "\nВыберите пункт введя его номер п/п\n"
			"\n1. Вывести список всех клиентов"
			"\n2. Показать данные по клиенту"
			"\n3. Добавить клиента"
			"\n4. Изменить размер членского взноса"
			"\n5. Изменить статус оплаты членского взноса"
			"\n6. Вывести список должников по книгам"
			"\n7. Удалить указанного клиента\n\n";
	
	char lib_opt = option_BU(7);
	
	clear_screen(); //очистка окна консоли
	
	switch(lib_opt) {
		case '1': //1. Вывести список всех клиентов
			cout << "\n1. Вывести список всех клиентов\n\n";
			my_lib.print_clients();
			break;
		
		case '2': {//2. Показать данные по клиенту
			cout << "\n2. Показать данные по клиенту\n\n";
			int num = my_lib.enter_ID();
			my_lib.print_1client(num);
			break;
		}
		
		case '3': //3. Добавить клиента
			cout << "\n3. Добавить клиента\n\n";
			my_lib.add_member();
			break;
		
		case '4': {//4. Изменить размер членского взноса
			cout << "\n4. Изменить размер членского взноса\n\n";
			int num = my_lib.enter_ID();
			my_lib.chg_mfee(num);
			break;
		}
		
		case '5': {//5. Изменить статус оплаты членского взноса
			cout << "\n5. Изменить статус оплаты членского взноса\n\n";
			int num = my_lib.enter_ID();
			my_lib.chg_mfee_paid_status(num);
			break;
		}
		
		case '6': //6. Вывести список должников по книгам
			cout << "\n6. Вывести список должников по книгам\n\n";
			my_lib.debtors();
			break;
		
		case '7': {//7. Удалить указанного клиента
			cout << "\n7. Удалить указанного клиента\n\n";
			int num = my_lib.enter_ID();
			my_lib.del_1client(num);
			break;
		}
	}
}


int main()
{
	lib_UI::Library my_library;
	
	/*
	//Указаны все данные
	my_library.push_back( biblio::Book("2-22-222-F", "Пушкин", "Пушкин", biblio::Genre::lyrics, Chrono::Date(12, Chrono::Month::march, 1825), true ) );
	
	//Инициализация без указания наличия (по умолчанию в наличии)
	my_library.push_back( biblio::Book("3-33-333-Я", "Кукушкин", "Кукушкин", biblio::Genre::prose, Chrono::Date(29, Chrono::Month::december, 2018) ) );
	
	//Указаны все данные (дата по умолчанию)
	my_library.push_back( biblio::Book("4-44-444-щ", "Пушкин", "Пушкин", biblio::Genre::lyrics, Chrono::Date(), false ) );
	
	//Никаких данных не указано (конструктор по умолчанию)
	my_library.push_back( biblio::Book() );
	*/

	while (true)
	try
	{
		clear_screen(); //очистка окна консоли
		cout << "\nВыберите пункт введя его номер п/п\n"
				"\n1. Книги"
				"\n2. Клиенты\n\n";
		
		char lib_opt = option_BU(2);
		
		clear_screen(); //очистка окна консоли
		
		if (lib_opt == '1')
			work_with_books(my_library);
		
		else if (lib_opt == '2')
			work_with_clients(my_library);

		if (Y_or_N("Закрыть программу?"))	return 0;
	}
	
	catch (Chrono::CTRL_Z_throw) { 
		//while (cin.get() != '\n')	cin.clear(); //Очищает поток символов cin
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

char option_BU(int count)
//Добивается от пользователя ответа на вопрос какой пункт меню стоит выбрать
//На вход: верхняя граница (кол-во пунктов)
//На выходе: ответ пользователя в заданном диапазоне от 1 до count
{
	string str = "";
	cin.clear();
	cout << "> ";
	
	while ( getline(cin, str) )
	{
		if (cin.eof())
			throw Chrono::CTRL_Z_throw {};
		else if (cin.fail() || str.size() > 1 || str[0] < '1' || str[0] > ('0' + count)) //Если ввод не верный
		{
			cin.clear();
			cin.ignore(120, '\n');
		}
		else break;
	}

	return str[0]; //..возвращаем ответ введённый пользователем
}