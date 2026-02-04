


#include <vector>
#include <map>
#include <fstream>


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
	//...
};

//------------------------------------------------------------------------------

typedef vector<Message>::const_iterator Mess_iter;

//Хранит все строки из файла и упрощает доступ к сообщениям
struct Mail_file {
	string name;			//Имя файла
	vector<string> lines;	//Строки по порядку
	vector<Message> m;		//Сообщения по порядку
	
	//Чтение файла n в строки
	Mail_file(const string& n)
		//Открывает файл с именем n и считывает строки в lines
		//Находит в lines границы сообщений и помещает их в m
		//Для простоты установленно, что каждое сообщение заканчивается строкой "----"
	{
		ifstream in {n};	//Открываем файловый поток ввода
		if(!in)		error("Unable to open file '" + n + "'");
		in.exceptions(in.exceptions() | ios_base::badbit);
		
		//Создаем вектор строк
		unsigned int msg_count {0};
		for(string s; !in.eof()  &&  getline(in,s); )
		{
			lines.push_back(s);
			//if( s == "----" )		error("empty message [Mail_file() constructor]");
			
			if( s.size() ) {
				++msg_count;		//Подсчет сообщений
				while( s != "----"  &&  getline(in,s) )		lines.push_back(s);
			}
		}
		
		
		auto first = lines.begin();
		for(auto p = lines.begin(); p != lines.end(); ++p)
		{
			
			while(p != lines.end()  &&  *p == "")		++p;		//Пропуск пустых строк
			
			if( p == lines.end()  &&  m.size() != msg_count )
				error("end of letter (\"----\") not found [Mail_file() constructor]");
			
			//Найден конец сообщения
			if(*p == "----") {
				m.push_back( Message(first,p) );
				first = p+1;	//Строка "----" не является частью сообщения
			}
			
		}
	}
	
	Mess_iter begin() const { return m.begin(); }
	Mess_iter end()   const { return m.end(); }
};

//------------------------------------------------------------------------------