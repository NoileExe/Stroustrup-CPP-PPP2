

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>


using namespace std;

//------------------------------------------------------------------------------

using Line_iter = vector<string>::const_iterator;

//Указывает на первую и последнюю строки сообщения
class Message {
	Line_iter first;
	Line_iter last;
	
public:
	Message(Line_iter p1, Line_iter p2) : first(p1), last(p2)	{  }
	
	Line_iter begin() const { return first; }
	Line_iter end()   const { return last; }
};

//------------------------------------------------------------------------------

//Является ли строка p первой частью строки s
//Возвращает размер строки p если является и нуль в обратном случае
int is_prefix(const string& s, const string& p);

//Ищет отправителя в объекте класса Message
//Возвращает true если он найден; также если найден - отправитель помещается в строку s
bool find_from_addr(const Message& m, string& s);

//На вход ссылка на объект письма и искомая строка (заголовок поля)
//Возвращает текст после искомого текста найденного поля. Если её нет - возвращает пустую строку ""
string find_field(const Message& m, const string& s);

//Имеет ли письмо повторяющиеся поля
//Возвращает true если это так
bool has_repeat_field(const Message& m);

//Имеет ли повторы строка с запятой в качестве разделителя
//Возвращает true если это так
bool has_repeats_in_string(const string& s);

//------------------------------------------------------------------------------

typedef vector<Message>::const_iterator Mess_iter;

//Хранит все строки из файла и упрощает доступ к сообщениям
struct Mail_file {
	string name;			//Имя файла
	vector<string> lines;	//Строки по порядку
	vector<Message> m;		//Сообщения по порядку
	
	//Чтение файла n в строки
	//Открывает файл с именем n и считывает строки в lines
	//Находит в lines границы сообщений и помещает их в m
	//Для простоты установленно, что каждое сообщение заканчивается строкой "----"
	Mail_file(const string& n);
	
	Mess_iter begin() const { return m.begin(); }
	Mess_iter end()   const { return m.end(); }
	
	//Поиск во всех сообщениях получателей писем с темой переданной в качестве аргумента
	//Возвращает строку получателей через запятую (т.е. формат пригодный для ф-ции has_repeats_in_string)
	string search_recipient(const string& s) const;
};

//------------------------------------------------------------------------------