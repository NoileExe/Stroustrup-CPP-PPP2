//Определение функций объявленных в biblio.h

#include "biblio.h"

namespace biblio {


Book::Book (string ISBN, string book, string author, Chrono::Date date, bool b_stock)
	: ISBN_code(ISBN), Book_name(book), Book_author(author), Lic_date(date), Book_stock (b_stock)
{
	if ( !is_book(ISBN, book, author, date) )
		error("неверно указаны данные книги ( полная инициализация класса Book )");
}

Book::Book (string ISBN, string book, string author, Chrono::Date date)
	: ISBN_code(ISBN), Book_name(book), Book_author(author), Lic_date(date)
{
	if ( !is_book(ISBN, book, author, date) )
		error("неверно указаны данные книги ( инициализация класса Book без указания наличия )");
	
	Book_stock = true;
}

Book::Book ()
	: ISBN_code  (def_book().ret_ISBN()),
	  Book_name  (def_book().ret_book()),
	  Book_author(def_book().ret_auth()),
	  Lic_date   (def_book().ret_licdate()),
	  Book_stock (def_book().ret_stock())
{
}

//------------------------------------------------------------------------------

const Book& def_book()
//данные по умолчанию для пустого члена класса
{
	static const Book defb( "1-1-1-z", "Conan barbarian", "Robert Howard", \
								Chrono::Date(2001,Chrono::Month::jan,1), true );
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
		
		//Если проверяется последняя часть ISBN кода и она является одной цифрой или буквой
		else if ( count == 0  &&  (isdigit(ch) || isalpha(ch))  &&  i == ISBN.size()-1 )
			return true;
		else if (count > 0 && isdigit(ch))
			{}
		else
			return false;
	}
	
	return false;
}

bool is_book(string ISBN, string book, string author, Chrono::Date date)
//проверка корректности инициализируемой книги
{
	//проверка корректности ISBN
	if ( !Correct_ISBN(ISBN) ) return false;
	//cout << "\nПроверка Correct_ISBN() пройдена\n";
	
	//проверку корректности названия книги не производим
	
	//проверка корректности автора (буквы англ., пробел, тире, точка или зпт)
	for (int i = 0; i < author.size(); ++i)
	{
		unsigned char ch = static_cast<unsigned char>(author[i]);
		
		if ( !( isalpha(ch) || ch == ' ' || ch == '-' || ch == '.' || ch == ',' ) )
			return false;
	}
	
	//cout << "\nПроверка имена автора пройдена\n";
	
	//проверку корректности даты не производим, т.к. она производится при инициализации даты
	
	return true;
}

//------------------------------------------------------------------------------

bool operator==(const Book& a, const Book& b)
{
	//return a.ret_ISBN()==b.ret_ISBN();
	
	return     a.ret_ISBN()==b.ret_ISBN()
			&& a.ret_book()==b.ret_book()
			&& a.ret_auth()==b.ret_auth()
		 && a.ret_licdate()==b.ret_licdate()
		   && a.ret_stock()==b.ret_stock();
}


bool operator!=(const Book& a, const Book& b)
{
	return !(a==b);
}


ostream& operator<<(ostream& os, const Book& b)
//оператор вывода для переменных класса Date
{
	os << "\n\nКнига: " << b.ret_book() 
		 << "\nАвтор: " << b.ret_auth()
		 << "\nДата лиц.: " << b.ret_licdate()
		 << "\nКод ISBN: "  << b.ret_ISBN()
		 << "\nНаличие: ";
	
	/*os << "\n\nКнига: " << b.ret_book() 
		 << "\nАвтор: " << b.ret_auth()
		 << "\nКод ISBN: "  << b.ret_ISBN();*/
	
	if (b.ret_stock())	os << "в наличии\n\n";
	else				os << "НЕТ в наличии\n\n";
	
	return os;
}


void getstr (string& s)
//Получает всю строку изменяя передаваемый по ссылке арг. и при ошибочном вводе вызывает исключения
{
	cin.clear();
	getline(cin, s);
	
	if (cin.eof())
		throw Chrono::CTRL_Z_throw {};
	
	else if  (!cin || cin.fail())
		error("неверный ввод (#1)");
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
	Chrono::Date date;
	
	cout << "\n\nНазвание книги: ";
	getstr(book);
	
	cout << "\nАвтор книги: ";
	getstr(author);
	
	cout << "\nДата лиц.(гггг, мм, дд): ";
	is >> date;
	
	cout << "\nКод ISBN n-n-n-x: ";
	getstr(ISBN);
	
	b = Book(ISBN,book,author,date);
	//пробуем внести новые данные в b (проверка на корректность)
	
	get_book_stock(b);
	
	is.ignore();
	return is;
}

//------------------------------------------------------------------------------
}