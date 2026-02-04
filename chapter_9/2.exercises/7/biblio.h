
#include "Chrono.h"
#include <yes_or_no.h>

namespace biblio {
	
	enum class Genre {
		fantastic=1, prose, periodic, biography, kids, lyrics
	 //     1          2       3          4        5      6
	};
	
	class Book {
	private:
		string ISBN_code;		//ISBN код книги в виде n-n-n-x (n - целое число, x - цифра или буква)
		string Book_name;		//название книги
		string Book_author;		//фамилия автора
		Genre  Book_genre;		//Жанр книги
		Chrono::Date Lic_date;	//дата регистрации авторских прав
		bool Book_stock;		//наличие книги ( книга выдана на руки (false) или нет, т.е. в наличии (true) )
	public:
		Book (string ISBN, string book, string author, Genre bgen, Chrono::Date date);
		Book (string ISBN, string book, string author, Genre bgen, Chrono::Date date, bool b_stock);
		Book ();
		
		//Константные ф-ции возвращающие члены объекта по отдельности
		string ret_ISBN() const { return ISBN_code; }
		string ret_book() const { return Book_name; }
		string ret_auth() const { return Book_author; }
		Genre ret_genre() const { return Book_genre; }
		Chrono::Date ret_licdate() const { return Lic_date; }
		bool  ret_stock() const { return Book_stock; }
		
		void chg_stock(bool bs) { Book_stock = bs; }
		//изменение статуса ( книга выдана на руки (false) или в наличии в библ. (true) )
	};
	
	const Book& def_book(); //Данные для конструктора по умолчанию
	
	bool Correct_ISBN(string ISBN);
	bool is_book(string ISBN, string book, string author, int genre, Chrono::Date date);

	bool operator==(const Book& a, const Book& b);
	bool operator!=(const Book& a, const Book& b);

	ostream& operator<<(ostream& os, const Book& b);
	
	void getstr(string txt, string& s);
	void get_book_stock(Book& b);
	istream& operator>>(istream& is, Book& b);
}