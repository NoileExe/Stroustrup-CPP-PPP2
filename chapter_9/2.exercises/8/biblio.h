
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
		bool Book_stock;		//наличие книги ( книга выдана на руки (false) или нет (true) )
	public:
		Book (string ISBN, string book, string author, Genre bgen, Chrono::Date date);
		Book (string ISBN, string book, string author, Genre bgen, Chrono::Date date, bool b_stock);
		Book ();
		
		string ret_ISBN() const { return ISBN_code; } //ф-ции получающие члены объекта по отдельности
		string ret_book() const { return Book_name; }
		string ret_auth() const { return Book_author; }
		Genre ret_genre() const { return Book_genre; }
		Chrono::Date ret_licdate() const { return Lic_date; }
		bool  ret_stock() const { return Book_stock; }
		
		void chg_stock(bool bs) { Book_stock = bs; }
		//изменение статуса ( книга выдана на руки (false) или в наличии в библ. (true) )
	};
	
	const Book& def_book();
	
	bool is_book(string ISBN, string book, string author, int genre, Chrono::Date date);

	bool operator==(const Book& a, const Book& b);
	bool operator!=(const Book& a, const Book& b);

	ostream& operator<<(ostream& os, const Book& b);
	
	void getstr(string txt, string& s);
	istream& operator>>(istream& is, Book& b);
}

namespace libman {
	
	class Patron {
	private:
		string username;		//имя пользователя
		int    ID_card;			//номер библиотечной карты
		double memb_fee_size;	//размер членского взноса
		bool   paid;			//указывает заплатил ли человек членские взносы
	public:
		Patron (string name, int card, double mfee, bool cash);
		Patron ();
		
		string ret_name() const { return username; } //ф-ции получающие члены объекта по отдельности
		int    ret_card() const { return ID_card; }
		double ret_mfee() const { return memb_fee_size; }
		bool   ret_paid() const { return paid; }
		
		void chg_mfee_size();
	};
	
	bool is_patron (string name, int card, double mfee);
	
	ostream& operator<<(ostream& os, const Patron& p);
	istream& operator>>(istream& is, Patron& p);
}
