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
		else if ( count == 0  &&  (isdigit(ch) || isalpha(ch))  &&  i == ISBN.size()-1 )
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
	if (genre<1 || genre>6) return false;
	
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
		default:	error("Такой жанр не числится в программе ( ostream& operator<<() )");
	}
	
	os << "\nДата лиц.: " << b.ret_licdate()
	   << "\nКод ISBN: "  << b.ret_ISBN()
	   << "\nНаличие: ";
	
	if (b.ret_stock()) os << "ЕСТЬ в наличии\n\n";
	else               os << "НЕТ в наличии\n\n";
	
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
		cout << txt;
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

void get_book_stock (Book& b)
//Добивается от пользователя статуса наличия книги
{
	bool res = Y_or_N("Книга в наличии?");
	
	if (cin.eof())		throw Chrono::CTRL_Z_throw {};
	else				b.chg_stock(res);
}

istream& operator>>(istream& is, Book& b)
{
	string ISBN, book, author;
	int genre;
	Chrono::Date date;
	
	getstr("\nНазвание книги: ", book);
	
	getstr("\nАвтор книги: ", author);
	
	cout << "\nфантастика | проза | периодика | биография | детская | стихи "
		 << "\n    1      |   2   |     3     |     4     |    5    |   6   "
		 << "\nЖанр: ";
	is >> genre;
	
	if (is.get() != '\n')
		while (is.get() != '\n') is.clear();
	
	cout << "\nДата лиц. дд.мм.гггг : ";
	is >> date;
	
	while (true) {
		getstr("\nКод ISBN: ", ISBN);
		
		if ( Correct_ISBN(ISBN) )	break;
		else
			cout << "\n\tНеверный код ISBN\n";
	}
	
	b = Book(ISBN,book,author,Genre(genre),date);
	//пробуем внести новые данные в b (проверка на корректность)
	
	get_book_stock(b);
	
	//is.ignore();
	return is;
}

//------------------------------------------------------------------------------
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
		error("неверные данные пользователя библиотеки (#6)");
}

Patron::Patron ()
	  : username	("Иванов И.И."),
	  ID_card		(999999999),
	  memb_fee_size	(100.0),
	  paid			(false)
{
}

//------------------------------------------------------------------------------

void Patron::chg_mfee_size()
{
	double num = 0;
	
	cout << "\nСтарое знач. членского взноса: " << ret_paid();
	
	while (true) {
		cout << "\nВведите новое знач. взноса: ";
		cin >> num;
		
		if (cin.eof())
			{ cin.ignore(); return; }
		else if  (!cin || cin.fail())
			while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
		else {
			if (cin.get() != '\n')
				while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
				
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

bool get_paid_status()
//Добивается от пользователя статуса оплаты членских взносов
{
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
	
	cout << "\nНомер библиотечной карты: ";
	is >> card;
	
	if (is.get() != '\n')
		while (is.get() != '\n') is.clear();
	
	cout << "\nРазмер членского взноса: ";
	is >> mfee;
	
	if (is.get() != '\n')
		while (is.get() != '\n') is.clear();
	
	paid = get_paid_status();
	
	p = Patron(name,card,mfee,paid);
	//пробуем внести новые данные в p (+проверка на корректность)
	
	//is.ignore();
	return is;
}

}

//------------------------------------------------------------------------------