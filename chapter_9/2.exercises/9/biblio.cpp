//Определение функций объявленных в biblio.h
#include "biblio.h"

namespace biblio {

//------------------------------------------------------------------------------
	
Book::Book (string ISBN, string book, string author, Genre bgen, Chrono::Date date, bool b_stock)
	: ISBN_code(ISBN), Book_name(book), Book_author(author), \
			Book_genre(bgen), Lic_date(date), Book_stock (b_stock)
{
	if ( !is_book(ISBN, book, author, int(bgen), date) )
		error("неверно указаны данные книги ( полная инициализация класса Book )");
}

 
Book::Book (string ISBN, string book, string author, Genre bgen, Chrono::Date date)
	: ISBN_code(ISBN), Book_name(book), Book_author(author), Book_genre(bgen), Lic_date(date)
{
	if ( !is_book(ISBN, book, author, int(bgen), date) )
		error("неверно указаны данные книги ( инициализация класса Book без указания наличия )");
	
	Book_stock = true; //Если не указывается наличие книги, то по умолчанию - в наличии
}

Book::Book ()
	: ISBN_code  (def_book().ret_ISBN()),
	  Book_name  (def_book().ret_book()),
	  Book_author(def_book().ret_auth()),
	  Book_genre (def_book().ret_genre()),
	  Lic_date   (def_book().ret_licdate()),
	  Book_stock (def_book().ret_stock())
{
}

//------------------------------------------------------------------------------

const Book& def_book()
//данные по умолчанию для пустого члена класса
{
	static const Book defb( "1-1-1-z", "Conan barbarian", "Robert Howard", Genre::fantastic,\
								Chrono::Date(1,Chrono::Month::january,2001), true );
	return defb;
}

//------------------------------------------------------------------------------

bool Correct_ISBN(string ISBN)
//проверка корректности ISBN
//Код ISBN предоставляется строкой в формате n-n-n-x, где n - целое число, x - одна цифра или буква
{
	int count = 3; //Код ISBN в формате n-n-n-x должен содержать 3 тире. Это их счётчик в строке
	
	for (int i = 0; i < ISBN.size(); ++i)
	{
		unsigned char ch = static_cast<unsigned char>(ISBN[i]);
		
		if (i > 0 && ch == '-') --count;
		
		//Если проверяется последняя часть ISBN кода и она является цифрой или буквой
		else if (count == 0  &&  (isdigit(ch) || isalpha(ch))  &&  i == ISBN.size()-1)
			return true;
		else if (count > 0 && isdigit(ch))
			{}
		else
			return false;
	}
	
	return false;
}

bool is_book(string ISBN, string book, string author, int genre, Chrono::Date date)
//проверка корректности инициализируемой книги
{
	//проверка корректности ISBN
	if ( !Correct_ISBN(ISBN) ) return false;
	
	//проверку корректности названия книги не производим
	
	//проверка корректности автора (буквы англ., пробел, тире, точка или зпт)
	for (int i = 0; i < author.size(); ++i)
	{
		unsigned char ch = static_cast<unsigned char>(author[i]);
		
		if ( !( isalpha(ch) || ch == ' ' || ch == '-' || ch == '.' || ch == ',' ) )
			return false;
	}
	
	//жанры от 1 до 6
	if (genre<1 || genre>7)		return false;
	
	//проверку корректности даты не производим, т.к. она производится при инициализации даты
	
	return true;
}

//------------------------------------------------------------------------------

bool operator==(const Book& a, const Book& b)
{
	return a.ret_ISBN()==b.ret_ISBN();
	
	/*return     a.ret_ISBN()==b.ret_ISBN()
			&& a.ret_book()==b.ret_book()
			&& a.ret_auth()==b.ret_auth()
		 && a.ret_licdate()==b.ret_licdate()
		   && a.ret_stock()==b.ret_stock();*/
}

bool operator!=(const Book& a, const Book& b)
{
	return !(a==b);
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Book& b)
//оператор вывода для переменных класса Book
{
	os << "\n\nКнига: " << b.ret_book() 
	   << "\nАвтор: " << b.ret_auth()
	   << "\nЖанр: ";
	
	switch( int(b.ret_genre()) ) {
		case 1: os << "фантастика";	break;
		case 2: os << "проза";		break;
		case 3: os << "периодика";	break;
		case 4: os << "биография";	break;
		case 5: os << "детская";	break;
		case 6: os << "стихи";		break;
		case 7: os << "научная";	break;
		default:	error("Такой жанр не числится в программе ( ostream& operator<<() )");
	}
	
	os << "\nДата лиц.: " << b.ret_licdate()
	   << "\nКод ISBN: "  << b.ret_ISBN()
	   << "\nНаличие: ";
	
	if (b.ret_stock())		os << "ЕСТЬ в наличии\n\n";
	else					os << "НЕТ в наличии\n\n";
	
	return os;
}


void getstr (string txt, string& s)
//Добивается от пользователя корректного ввода
//Получает всю строку изменяя передаваемый по ссылке арг.
{
	cin.clear();
	
	while (true)
	try
	{
		cout << txt << " ";
		getline(cin, s);
		
		if ( cin.eof() )
			throw Chrono::CTRL_Z_throw {};
		else if  ( !cin || cin.fail() )
			error("неверный ввод ( getstr() )");
		else
			return;
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		while (cin.get() != '\n')	cin.clear(); //Очищает поток символов cin
	}
}

bool answ_stock ()
//Добивается от пользователя статуса наличия книги
{
	cin.putback('\n');
	bool res = Y_or_N("Книга в наличии?");
	
	if (cin.eof())		throw Chrono::CTRL_Z_throw {};
	else				return res;
}

istream& operator>>(istream& is, Book& b)
{
	string ISBN, book, author;
	int genre;
	Chrono::Date date;
	bool stock;
	
	while (true) {
		getstr("\nКод ISBN: ", ISBN);
		
		if ( Correct_ISBN(ISBN) )	break;
		
		else
			cout << "\n\tНеверный код ISBN\n";
	}
	
	getstr("\nНазвание книги: ", book);
	
	getstr("\nАвтор книги: ", author);
	
	cout << "\n    фантастика | проза | периодика | биография | детская | стихи | научная "
		 << "\n        1      |   2   |     3     |     4     |    5    |   6   |    7    ";
	
	while (true) {
		cout << "\n\nЖанр: ";
		is >> genre;
		
		if ( is.eof() ) {
			is.unget();
			while (is.get() != '\n') is.clear(); //Очищает поток символов cin
			throw Chrono::CTRL_Z_throw {};
		}
		
		else if ( !cin || cin.fail() || genre < 1 || genre > 7 ) {
			is.unget();
			while (is.get() != '\n') is.clear(); //Очищает поток символов cin
			cerr << "\nНеверный ввод. Повторите ввод\n";
		}
		
		else	break;
	}
	
	cout << "\nДата лиц. дд.мм.гггг : ";
	is >> date;
	
	stock = answ_stock();
	
	b = Book(ISBN,book,author,Genre(genre),date,stock);
	//пробуем внести новые данные в b (проверка на корректность)
	
	//is.ignore();
	return is;
}

}

//---/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\----
//------------------------------------------------------------------------------
//---\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/----

namespace libman {

//------------------------------------------------------------------------------
Patron::Patron (string name, int card, double mfee, bool cash)
	  : username (name), ID_card (card), memb_fee_size (mfee), paid (cash)
{
	if ( !is_patron(name, card, mfee) )
		error("неверные данные пользователя библиотеки ( полная инициализация нового пользователя )");
}

Patron::Patron ()
	  : username    ("Иванов И.И."),
	  ID_card       (999999999),
	  memb_fee_size (100.0),
	  paid          (false)
{
}

//------------------------------------------------------------------------------

void Patron::chg_mfee_size()
{
	double num = 0;
	
	cout << "\nСтарое знач. членского взноса: " << ret_mfee();
	
	while (true) {
		cout << "\nВведите новое знач. взноса: ";
		cin >> num;
		
		if (cin.eof())
			throw Chrono::CTRL_Z_throw {};
			//cin.ignore(); return;
		
		else if  (!cin || cin.fail())
			cin.ignore();
		
		else {
			if (cin.get() != '\n')
				while (cin.get() != '\n') cin.ignore();
				
			memb_fee_size = num;
			return;
		}
	}
}

//------------------------------------------------------------------------------

bool is_patron (string name, int card, double mfee)
{
	//проверка корректности имени (буквы (русские и англ.), пробел, тире или точка)
	for (int i = 0; i < name.size(); ++i)
		if ( ! ( (name[i]>='А' && name[i]<='п') || (name[i]>='р' && name[i]<='я') || isalpha(name[i]) \
					|| name[i] == ' ' || name[i] == '-' || name[i] == '.' || name[i] == ',') )
	{
		return false;
	}
	
	
	//проверка корректности номера библ. карты
	if (card<0 || card>999999999) return false;
	
	//проверка корректности размера членского взноса
	if (mfee<0 || mfee>9999) return false;
	
	return true;
}

//------------------------------------------------------------------------------

bool operator==(const Patron& a, const Patron& b)
{
	return     a.ret_card()==b.ret_card();
	
	/*
	return		a.ret_name()==b.ret_name()
			 && a.ret_card()==b.ret_card();
			// && a.ret_mfee()==b.ret_mfee()
			// && a.ret_paid()==b.ret_paid();
	*/
}

bool operator!=(const Patron& a, const Patron& b)
{
	return !(a==b);
}

//------------------------------------------------------------------------------

ostream& operator<<(ostream& os, const Patron& p)
{
	os << "\n\nПользователь:  "	<< p.ret_name() 
	   << "\nБибл. карта:   "	<< p.ret_card()
	   << "\nРазмер взноса: "	<< p.ret_mfee()
	   << "\nВзнос оплачен: ";
	
	if (p.ret_paid())	os << "ДА \n\n";
	else				os << "НЕТ\n\n";
	
	return os;
}

//------------------------------------------------------------------------------

bool answ_paid_status()
//Добивается от пользователя статуса оплаты членских взносов
{
	cin.putback('\n');
	bool res = Y_or_N("Взнос оплачен?");
	
	if (cin.eof())		throw Chrono::CTRL_Z_throw {};
	else				return res;
}

istream& operator>>(istream& is, Patron& p)
{
	string name;
	int card = 0;
	double mfee = 0;
	bool paid;
	
	biblio::getstr("\nИмя пользователя: ", name);
	
	while (true) {
		cout << "\nНомер библиотечной карты: ";
		is >> card;
		
		if ( is.eof() ) {
			is.unget();
			while (is.get() != '\n') is.clear(); //Очищает поток символов cin
			throw Chrono::CTRL_Z_throw {};
		}
		
		else if ( !is || is.fail() || !is_patron("AAA", card, 0) ) {
			cin.unget();
			while (is.get() != '\n') is.clear(); //Очищает поток символов cin
			cerr << "\nНеверный ввод. Повторите ввод\n";
		}
		
		else	break;
	}
	
	while (true) {
		cout << "\nРазмер членского взноса: ";
		is >> mfee;
		
		if ( is.eof() ) {
			is.unget();
			while (is.get() != '\n') is.clear(); //Очищает поток символов cin
			throw Chrono::CTRL_Z_throw {};
		}
		
		else if ( !is || is.fail() || !is_patron("AAA", 0, mfee) ) {
			is.unget();
			while (is.get() != '\n') is.clear(); //Очищает поток символов cin
			cerr << "\nНеверный ввод. Повторите ввод\n";
		}
		
		else	break;
	}
	
	paid = answ_paid_status();
	
	p = Patron(name,card,mfee,paid);
	//пробуем внести новые данные в p (+проверка на корректность)
	
	//is.ignore();
	return is;
}

}

//---/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\-/\----
//------------------------------------------------------------------------------
//---\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/-\/----

namespace lib_UI {

bool Library::book_is_present (string ISBN) const
//true - если в векторе my_library существует запись с ISBN_code == входной строке ISBN
//false - если книга с переданным ISBN не встречается, либо же если он ошибочен
{
	if ( biblio::Correct_ISBN(ISBN) )
	{
		for (int i = 0; i < my_library.size(); ++i)
				if ( my_library[i].ret_ISBN() == ISBN )  return true;
	}
	
	return false;
}

void Library::add_book()
/*Добавить новую книгу (новый элемент в конец вектора my_library)
Оператор ввода также проверит правильность ввода данных для указанного пространства 
имён и при необходимости вызовет исключение (запись в вектор не будет добавлена)*/
{
	using namespace biblio;
	
	Book one_book;
	cin >> one_book;
	
	for (int i = 0; i < my_library.size(); ++i)
		//Используется процедура bool operator==(const Book& a, const Book& b)
		//Сравнивает ISBN двух объектов класса biblio::Book
		if ( my_library[i] == one_book ) {
			print_1book( one_book.ret_ISBN() );
			error("такая книга уже числится ( Library::add_book() )");
		}
	
	my_library.push_back(one_book);
	//my_library[my_library.size()-1].chg_stock(true); //В любом случае если добавляем книгу, то она должна иметь статус "ЕСТЬ в наличии"
}

void Library::print_lib() const
//Вывести на экран список всех книг
{
	//using namespace biblio;
	
	if ( my_library.empty() )
		error("пустая библиотека (нет ни одной записи о книге) ( Library::print_lib() )");
	
	for (int i = 0; i < my_library.size(); ++i)
		biblio::operator <<(cout, my_library[i]);
}

void Library::print_1book(string ISBN) const
//Вывести на экран описание одной книги
{
	if ( my_library.empty() )
		error("пустая библиотека (нет ни одной записи о книге) ( Library::print_1book )");
	
	for (int i = 0; i < my_library.size(); ++i)
			if ( my_library[i].ret_ISBN() == ISBN )
				biblio::operator <<(cout, my_library[i]);
}

void Library::del_1book(string ISBN)
//Удалить одну указанную книгу из БД, книга при этом не должна быть выдана на руки
// т.е. не должна числиться в векторе lib_transits.
//(Указанная книга - элемент biblio::Book, с ISBN совпадающим с переданным в аргументе, из вектора my_library)
{
	if ( my_library.empty() )
		error("пустая библиотека (нет ни одной записи о книге) ( Library::del_1book )");
	
	for (int i = 0; i < lib_transits.size(); ++i)
		if ( lib_transits[i].one_book.ret_ISBN() == ISBN ) {
			cout << "\n\nКнига:\n";
			biblio::operator <<(cout, lib_transits[i].one_book);
			
			cout << "\n\nВыдана пользователю:\n";
			libman::operator <<(cout, lib_transits[i].one_member);
			
			cout << "\n\nДата выдачи: ";
			Chrono::operator <<(cout, lib_transits[i].trans_date);
			
			cout << "\n\n";
			error("\nНевозможно удалить. Данная книга находится у клиента на руках!");
		}
	
	//Книга не числится ни у кого на руках - можно удалить
	for (int i = 0; i < my_library.size(); ++i)
		if ( my_library[i].ret_ISBN() == ISBN )
			my_library.erase(my_library.begin() + i); //Удалить элемент с индексом i из вектора книг
}

//------------------------------------------------------------------------------
	
bool Library::user_is_present(int ID_card) const
//true - если в векторе lib_members существует запись с ID_card == входной строке ID_card
//false - если человек с переданным ID_card не встречается
{
	for (int i = 0; i < lib_members.size(); ++i)
			if ( lib_members[i].ret_card() == ID_card )
				return true;
	
	return false;
}

void Library::add_member()
/*Добавить нового клиента (новый элемент в конец вектора lib_members)
Оператор ввода также проверит правильность ввода данных для указанного пространства 
имён и при необходимости вызовет исключение (запись в вектор не будет добавлена)*/
{
	using namespace libman;
	
	Patron one_user;
	cin >> one_user;
	
	//Если такого ID карты пользователя пока нет - добавляем
	if ( !user_is_present(one_user.ret_card()) )
		{ lib_members.push_back(one_user); }
	
	else {
		print_1client( one_user.ret_card() );
		error("пользователь с таким номером карты уже существует ( Library::add_member )");
	}
}

void Library::print_clients() const
//Вывести на экран список всех клиентов
{
	using namespace libman;
	
	if ( lib_members.empty() )
		error("пустой перечень клиентов (нет ни одной записи о клиенте) ( Library::print_clients )");
	
	for (int i = 0; i < lib_members.size(); ++i)
		libman::operator << (cout, lib_members[i]);
}

void Library::print_1client(int ID_card) const
//вывести на экран описание одного клиента
{
	if ( lib_members.empty() )
		error("пустой перечень клиентов (нет ни одной записи о клиенте) ( Library::print_1client )");
	
	for (int i = 0; i < lib_members.size(); ++i)
		if ( lib_members[i].ret_card() == ID_card )
			libman::operator << (cout, lib_members[i]);
}

void Library::del_1client(int ID_card)
//Удалить одного указанного клиента из БД, клиент при этом не должен иметь задолжности
// по книгам, т.е. не должен числиться в векторе lib_transits.
//(Указанный клиент - элемент libman::Patron, с ID_card совпадающим с переданным в аргументе,
// из вектора lib_members)
{
	if ( lib_members.empty() )
		error("пустой перечень клиентов (нет ни одной записи о клиенте) ( Library::del_1client )");
	
	for (int i = 0; i < lib_transits.size(); ++i)
//////////По идее нужна доп.функция которая выводит все задолжности клиента с переданным в качестве аргумента ID
//////////Также не помешает оператор краткого вывода объектов Book и Patron
		if ( lib_transits[i].one_member.ret_card() == ID_card ) {
			cout << "\n\nКнига:\n";
			biblio::operator <<(cout, lib_transits[i].one_book);
			
			cout << "\n\nВыдана пользователю:\n";
			libman::operator <<(cout, lib_transits[i].one_member);
			
			cout << "\n\nДата выдачи: ";
			Chrono::operator <<(cout, lib_transits[i].trans_date);
			
			cout << "\n\n";
			error("\nНевозможно удалить. Данный клиент ещё не вернул все книги!");
		}
	
	//Пользователь с указанным ID найден и у него нет задолжностей:
	for (int i = 0; i < lib_members.size(); ++i)
		if ( lib_members[i].ret_card() == ID_card )
			lib_members.erase(lib_members.begin() + i); //Удалить элемент с индексом i из вектора клиентов
}

//------------------------------------------------------------------------------

string Library::enter_ISBN() const
//вспомогательная ф-ция для book2mem() И book2lib. Добивается корректного ввода ISBN СУЩЕСТВУЮЩЕЙ книги
{
	string str;
	
	while (true)
	{
		cout << "Введите ISBN книги: ";
		getline(cin, str);
		
		if (cin.eof())
			throw Chrono::CTRL_Z_throw {};
		
		else if ( !cin || cin.fail() )
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		else if ( !biblio::Correct_ISBN(str) )
		{
			cout << "\n\nНеверный формат ISBN!\n\n";
			press_Enter_key();
		}
		
		else if ( !book_is_present(str) )
		{
			cout << "\n\nНет книги с таким ISBN!\n\n";
			press_Enter_key();
		}
		
		else	return str;
	}

	error("Что-то пошло не так! ( Library::enter_ISBN() )");
}

//------------------------------------------------------------------------------

int Library::enter_ID() const
//вспомогательная ф-ция для book2mem() И book2lib. Добивается корректного ввода ID СУЩЕСТВУЮЩЕГО клиента
{
	string str;
	int num;
	
	while (true)
	{
		cout << "Введите ID карты клиента: ";
		cin >> num;
		
		if (cin.eof())
			throw Chrono::CTRL_Z_throw {};
		
		//ошибочный ввод
		else if ( !cin || cin.fail() ) {
			cin.unget();
			while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
		}
		
		//если такой карты нет в базе данных
		else if ( !user_is_present(num) )
		{
			cout << "\n\nНет пользователя с таким ID карты!\n\n";
			press_Enter_key();
		}
		
		else    return num;
	}

	error("Что-то пошло не так! ( Library::enter_ID() )");
}

//------------------------------------------------------------------------------

void Library::book2mem()
//Выдача книги клиенту
/*Процедура следующая:
 * Пользователь вводит ISBN книги, которая подлежит выдаче клиенту 
 *          и которая обязательно должна быть в наличии в библиотеке
 * Пользователь вводит ID карты клиента, который хочет арендовать книгу
 *          и у которого обязательно должны быть уплачены членские взносы
 * Делается запись в вектор lib_transits о передачи указанной книги указанному клиенту
 * Статус наличия книги меняется на false
*/
{
	//Для краткости делаем ссылки на векторы
	vector<biblio::Book>& vlib = my_library;
	vector<libman::Patron>& vmems = lib_members;
	
	if ( vlib.empty() )
		error("пустая библиотека (нет ни одной записи о книге) ( Library::book2mem() )");
	
	else if ( vmems.empty() )
		error("пустой перечень клиентов (нет ни одной записи о клиенте) ( Library::book2mem() )");
	
	
	string ISBN_code {""};
	ISBN_code = enter_ISBN(); //Добивается ввода существующего ISBN в верном формате
	print_1book(ISBN_code); //Для удобства печатаем данные по данному объекту
	
	for (int i = 0; i < vlib.size(); ++i)
		//Если книги с указанным ISBN НЕТ в наличии - вызываем исключение
		if ( ( vlib[i].ret_ISBN() == ISBN_code )  &&  !( vlib[i].ret_stock() ) )
			error("книга уже выдана на руки: нет в наличии ( Library::book2mem() )");
	
	
	int ID_card {-1};
	ID_card = enter_ID(); //Добивается ввода существующего ID в верном формате
	print_1client(ID_card); //Для удобства печатаем данные по данному объекту
	
	for (int i = 0; i < vmems.size(); ++i)
		//Если у пользователя с указанным ID карты не уплачены взносы - вызываем исключение
		if ( ( vmems[i].ret_card() == ID_card )  &&  !( vmems[i].ret_paid() ) )
			error("указанный пользователь не уплатил членские взносы ( Library::book2mem() )");
	
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
	
	//Ищем книгу с данным ISBN в векторе и меняем наличие на "НЕТ в наличии"
	for (int i = 0; i < vlib.size(); ++i)
	{
		//Нашли книгу с указанным ISBN
		if ( vlib[i].ret_ISBN() == ISBN_code )
		{
			for (int j = 0; j < vmems.size(); ++j)
			{
				//Нашли пользователя с указанным ID карты
				if ( vmems[j].ret_card() == ID_card )
				{
					vlib[i].chg_stock(false); //Помечаем что книга выдана на руки (не в наличии)
					
					//Делаем запись о передачи книги клиенту библиотеки
					lib_transits.push_back( Transaction(vlib[i], vmems[j], currentDate()) );
					
					cout << "КНИГА ВЫДАНА КЛИЕНТУ!";
					break;
				}
			}
			
			break;
		}
	}
}

void Library::book2lib()
//Возврат книги в библиотеку
/*Процедура следующая:
 * Пользователь вводит ISBN книги, которая подлежит возврату от клиента 
 *          и которая обязательно должна числится в библиотеке как отсутствующая
 * Пользователь вводит ID карты клиента, который хочет вернуть книгу
 *          и за которым должна числится аренда именно этой книги
 * Удаляется запись из вектора lib_transits о передачи указанной книги указанному клиенту
 * Статус наличия книги меняется на true
*/
{
	//Для краткости делаем ссылки на векторы
	vector<biblio::Book>& vlib = my_library;
	vector<libman::Patron>& vmems = lib_members;
	vector<Transaction>& vtrans = lib_transits;
	
	if ( vlib.empty() )
		error("пустая библиотека (нет ни одной записи о книге) ( Library::book2lib() )");
	
	else if ( vmems.empty() )
		error("пустой перечень клиентов (нет ни одной записи о клиенте) ( Library::book2lib() )");
	
	
	string ISBN_code {""};
	ISBN_code = enter_ISBN(); //Добивается ввода существующего ISBN в верном формате
	print_1book(ISBN_code); //Для удобства печатаем данные по данному объекту
	
	for (int i = 0; i < vlib.size(); ++i)
		//Если книга с указанным ISBN УЖЕ ЕСТЬ в наличии - вызываем исключение
		if ( ( vlib[i].ret_ISBN() == ISBN_code )  &&  ( vlib[i].ret_stock() ) )
			error("данная книга и так в наличии ( Library::book2lib() )");
	
	
	int ID_card {-1};
	ID_card = enter_ID(); //Добивается ввода существующего ID в верном формате
	print_1client(ID_card); //Для удобства печатаем данные по данному объекту
	
	//------------------------------------------------------------------------------
	//------------------------------------------------------------------------------
	
	for (int i = 0; i < vtrans.size(); ++i)
	{
		//Нашли транзакцию с данной книгой
		if ( vtrans[i].one_book.ret_ISBN() == ISBN_code )
		{
			
			if ( vtrans[i].one_member.ret_card() == ID_card )
			{
				//Удалить элемент с индексом i из вектора транзакций
				vtrans.erase(vtrans.begin() + i);
				
				//перебор по вектору книг my_library
				for (int j = 0; j < vlib.size(); ++j)
					if ( vlib[j].ret_ISBN() == ISBN_code )	//Нашли книгу с указанным ISBN
						vlib[j].chg_stock(true);			//Помечаем что книга в наличии
				
				cout << "КНИГА ВОЗВРАЩЕНА В БИБЛИОТЕКУ!";
				break;
			}
			
			else    error("данную книгу приобретал другой клиент ( Library::book2lib() )");
			
		}
	}
}

//------------------------------------------------------------------------------

void Library::chg_mfee(int ID_card)
//Изменить размер членского взноса
{
	vector<libman::Patron>& vmems = lib_members;
	
	print_1client(ID_card); //Для удобства печатаем данные по данному объекту
	
	for (int i = 0; i < vmems.size(); ++i)
		if ( ( vmems[i].ret_card() == ID_card ) )
			vmems[i].chg_mfee_size();
}

void Library::chg_mfee_paid_status(int ID_card)
//Изменить статус оплаты членского взноса
{
	vector<libman::Patron>& vmems = lib_members;
	
	print_1client(ID_card); //Для удобства печатаем данные по данному объекту
	
	for (int i = 0; i < vmems.size(); ++i)
		if ( ( vmems[i].ret_card() == ID_card ) )
		{
			//Смена статуса уплаты взносов на обратный от текущего
			vmems[i].chg_unpaid( !vmems[i].ret_paid() );
			cout << "\nСтатус оплаты взноса клиента ID " << ID_card <<": ";
			if ( vmems[i].ret_paid() )	cout << "ДА";
			else						cout << "НЕТ";
			break;
		}
}
	
//------------------------------------------------------------------------------

void Library::debtors() const
//Вывод списка клиентов с задолжностью по книгам
{
	if ( lib_transits.empty() )
		error("нет записей о выданных книгах ( Library::debtors() )");
	
	for (int i = 0; i < lib_transits.size(); ++i)
		cout << "\n\nИмя: " << lib_transits[i].one_member.ret_name()
			 << "\nКарта: " << lib_transits[i].one_member.ret_card()
			 << "\nКнига: " << lib_transits[i].one_book.ret_auth()    //АВТОР 'НАЗВАНИЕ'
			 << " '" << lib_transits[i].one_book.ret_book() << "' "
			 << "\nISBN: " << lib_transits[i].one_book.ret_ISBN()
			 << "\nДата выдачи: " << lib_transits[i].trans_date;
}

} //namespace lib_UI

//------------------------------------------------------------------------------

Chrono::Date currentDate()
//Получение текущей даты в формате подходящем для Chrono::Date
{
	time_t     now = time(0);
	struct tm  tstruct;
	//char       buf[80];
	tstruct = *localtime(&now);
	//strftime(buf, sizeof(buf), "%d.%m.%Y", &tstruct);
	
					//числа мес. 1-31               месяцы 0-11          кол-во лет с 1900 года
	return Chrono::Date(tstruct.tm_mday, Chrono::Month(tstruct.tm_mon+1), tstruct.tm_year+1900);
}

//------------------------------------------------------------------------------
