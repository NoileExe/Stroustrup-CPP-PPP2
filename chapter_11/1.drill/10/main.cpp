
#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

struct Contact {
	Contact (string a, string b, string c, string d)
			: first_name(a), second_name(b), tel_number(c), mailbox(d) { }
	
	string first_name {""};
	string second_name {""};
	string tel_number {""};
	string mailbox {""};
};

//------------------------------------------------------------------------------------------------------------

void print_line(int name, int secondname, int tel, int mail)
{
	int lines_count { name + 4 + secondname + 3 + tel + 3 + mail + 3 };
	
	for (int i = 0; i < lines_count; ++i)
		cout << '-';
}

string string_line(int name, int secondname, int tel, int mail)
{
	int lines_count { name + 4 + secondname + 3 + tel + 3 + mail + 3 };
	string str {""};
	
	
	for (int i = 0; i < lines_count; ++i)
		if ( i == name + 3  ||  i == (name + 3 + secondname + 3)  ||  i == (name + 3 + secondname + 3 + tel + 3) )
			str += '+';
		else if ( i == 0  ||  i == lines_count-1 )
			str += '|';
		else
			str += '-';
	
	return str;
}


int main() {
	while(true)
	try {
		vector<Contact> friends_contacts;
		
		friends_contacts.push_back( Contact("Ivan", "Ivanov", "8-800-888-88-88", "ii@gmail.com") );
		friends_contacts.push_back( Contact("Sergey", "Sergeev", "+7(928) 333-33-33", "serserun@mail.ru") );
		friends_contacts.push_back( Contact("Dmitriy", "Dmitrievich", "8 (812) 222-22-22", "dmidim@dd.su") );
		
		
		//ВНИМАНИЕ!!! Фамилия (second_name) и Имя (first_name) при выводе поменяны местами, т.е. отличаются от последовательности 
		//	в именовании и в объявлении в самой структуре Contact
		string one = "SECOND NAME";
		string two = "FIRST NAME";
		string three = "TELEPHONE NUMBER";
		string four = "E-MAIL";
		
		int max_name_size = one.size(), max_2nd_name_size = two.size(), max_tel_size = three.size(), max_email_size = four.size();
		
		//Определение макс длины каждого поля
		for (Contact fi : friends_contacts) {
			if ( fi.first_name.size() > max_name_size )			max_name_size = fi.first_name.size();
			if ( fi.second_name.size() > max_2nd_name_size )	max_2nd_name_size = fi.second_name.size();
			if ( fi.tel_number.size() > max_tel_size )			max_tel_size = fi.tel_number.size();
			if ( fi.mailbox.size() > max_email_size )			max_email_size = fi.mailbox.size();
		}
		
		cout << "\n\n";
		
		//Шапка таблицы   ФАМИЛИЯ			ИМЯ			ТЕЛЕФОН			ПОЧТА
		print_line ( max_2nd_name_size, max_name_size, max_tel_size, max_email_size );
		
		string between_lines = string_line( max_2nd_name_size, max_name_size, max_tel_size, max_email_size );
		
		cout << "\n"
			 << "| "	<<	setw(max_2nd_name_size)		<< one
			 << " | "	<<	setw(max_name_size)	<< two 
			 << " | "	<<	setw(max_tel_size)		<< three
			 << " | "	<<	setw(max_email_size)	<< four << " |" << '\n'
			 << between_lines << '\n';
		
		
		//Сама таблица
		for (int i = 0; i < friends_contacts.size(); ++i) {
			
			Contact& fi = friends_contacts[i];
			
			cout << "| "	<<	setw(max_2nd_name_size)		<< fi.second_name
				 << " | " 	<<	setw(max_name_size)			<< fi.first_name
				 << " | "	<<	setw(max_tel_size)			<< fi.tel_number
				 << " | "	<<	setw(max_email_size)		<< fi.mailbox << " |" << '\n';
			
			if ( i != friends_contacts.size()-1 )
				cout << between_lines << '\n';
			else
				print_line ( max_name_size, max_2nd_name_size, max_tel_size, max_email_size );
		}
		
		
		if ( Y_or_N(quit_question) )	return 0;
		//keep_window_open("~~");
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		
		if ( Y_or_N(quit_question) )	return 1001;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		
		if ( Y_or_N(quit_question) )	return 1002;
	}
}