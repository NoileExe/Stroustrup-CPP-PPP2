
#include "Chrono.h"
#include <yes_or_no.h>
#include <time.h>


Chrono::Date currentDate(); //получение текущей даты в формате подходящем для Chrono::Date


namespace biblio {
	
	enum class Genre {
		fantastic=1, prose, periodic, biography, kids, lyrics, science
	 //     1          2       3          4        5      6       7
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
		
		//Константные ф-ции получающие члены объекта по отдельности
		string ret_ISBN() const { return ISBN_code; }
		string ret_book() const { return Book_name; }
		string ret_auth() const { return Book_author; }
		Genre ret_genre() const { return Book_genre; }
		Chrono::Date ret_licdate() const { return Lic_date; }
		bool  ret_stock() const { return Book_stock; }
		
		void chg_stock(bool bs) { Book_stock = bs; }
		//изменение статуса ( книга выдана на руки (false) или в наличии в библ. (true) )
	};
	
	const Book& def_book();
	
	bool Correct_ISBN(string ISBN); //вспомогательная ф-ция для is_book()
	bool is_book(string ISBN, string book, string author, int genre, Chrono::Date date);

	bool operator==(const Book& a, const Book& b);
	bool operator!=(const Book& a, const Book& b);

	ostream& operator<<(ostream& os, const Book& b);
	
	void getstr(string& s);	//вспомогательная ф-ция для operator>>()
	bool answ_stock();		//вспомогательная ф-ция для operator>>()
	istream& operator>>(istream& is, Book& b);
	
} //namespace biblio

//------------------------------------------------------------------------------

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
		
		//Константные ф-ции получающие члены объекта по отдельности
		string ret_name() const { return username; }
		int    ret_card() const { return ID_card; }
		double ret_mfee() const { return memb_fee_size; }
		bool   ret_paid() const { return paid; }
		
		void chg_mfee_size();
		void chg_unpaid(bool p_up) { paid = p_up; }
	};
	
	bool is_patron (string name, int card, double mfee);
	
	bool operator==(const Patron& a, const Patron& b);
	bool operator!=(const Patron& a, const Patron& b);
	
	ostream& operator<<(ostream& os, const Patron& p);
	
	bool answ_paid_status();    //вспомогательная ф-ция для operator>>()
	istream& operator>>(istream& is, Patron& p);
	
} //namespace libman

//------------------------------------------------------------------------------

namespace lib_UI {
	
	class Library {
	private:
		struct Transaction {
			Transaction(biblio::Book b, libman::Patron m, Chrono::Date d)
					    :one_book(b),one_member(m),trans_date(d) { }
		
			biblio::Book    one_book;
			libman::Patron  one_member;
			Chrono::Date    trans_date;
		};
	
		vector<biblio::Book>   my_library;		//книги
		vector<libman::Patron> lib_members;	//клиенты
		vector<Transaction>    lib_transits;		//передача книг клиентам
	public:
		bool book_is_present (string ISBN) const;
			//true - если в векторе my_library существует запись с ISBN_code == входной строке ISBN
			//false - если книга с переданным ISBN не встречается, либо же если он ошибочен
		void add_book();    //добавить новую книгу
		void print_lib() const;   //вывести на экран список всех книг
		void print_1book(string ISBN) const; //вывести на экран описание одной книги
		void del_1book(string ISBN); //удалить одну указанную книгу из БД
		
		bool user_is_present(int ID_card) const;
			//true - если в векторе lib_members существует запись с ID_card == входной строке ID_card
			//false - если человек с переданным ID_card не встречается
		void add_member();      //добавить нового клиента
		void print_clients() const;   //вывести на экран список всех клиентов
		void print_1client(int ID_card) const; //вывести на экран описание одного клиента
		void del_1client(int ID_card); //удалить одного указанного клиента из БД
		
		string enter_ISBN() const;
			//вспомогательная ф-ция для book2mem() И book2lib, а также ф-ций print_1 и del_1.
			//Добивается корректного ввода ISBN СУЩЕСТВУЮЩЕЙ книги
		int enter_ID() const;
			//вспомогательная ф-ция для book2mem() И book2lib, а также ф-ций print_1 и del_1.
			//Добивается корректного ввода ID СУЩЕСТВУЮЩЕГО клиента
		
		void book2mem();	//выдача книги клиенту
		void book2lib();	//возврат книги в библиотеку
		
		void chg_mfee(int ID_card); //изменить размер членского взноса
		void chg_mfee_paid_status(int ID_card); //изменить статус оплаты членского взноса
		
		
		void debtors() const;	//вывод списка клиентов с задолжностью по книгам
		
	};

} //namespace lib_UI