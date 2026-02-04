


#include "mail.h"

//------------------------------------------------------------------------------

//Является ли строка p первой частью строки s
//Возвращает размер строки p
int is_prefix(const string& s, const string& p)
{
	int n = p.size();
	
	//Часть строки s от 0-го до n-го символа
	if( string(s,0,n) == p )		return n;
	return 0;
}

//Ищет отправителя в объекте класса Message
//Возвращает true если он найден; также если найден - отправитель помещается в строку s
bool find_from_addr(const Message& m, string& s)
{
	for(const auto& x : m)
		if( int n = is_prefix(x, "From: ") ) {
			s = string(x, n);	//Все символы строки x начиная с элемента x[n] (n-ый символ)
			return true;
		}
	
	return false;
}

//На вход ссылка на объект письма и искомая строка (заголовок поля)
//Возвращает текст после искомого текста найденного поля. Если её нет - возвращает пустую строку ""
string find_field(const Message& m, const string& s)
{
	for(const auto& x : m)
		if( int n = is_prefix(x, s) )		return string(x, n);	//Все символы строки x начиная с элемента x[n] (n-ый символ)
	
	return "";
}

//Имеет ли письмо повторяющиеся поля (предопределенные форматом, но не обязательные From:, To: и др.)
//Возвращает true если это так
bool has_repeat_field(const Message& m)
{
	map<string, int> cnt;
	
	//Цикл по итераторам требует разыменования 'x'
	//for(auto x = m.begin(); x != m.end(); ++x)
	for(const auto& x : m)
		if( is_prefix(x, "From: ") )				++cnt["From: "];
		else if( is_prefix(x, "To: ") )				++cnt["To: "];
		else if( is_prefix(x, "Subject: ") )		++cnt["Subject: "];
		else if( is_prefix(x, "Date: ") )			++cnt["Date: "];
		else if( is_prefix(x, "Message-ID: ") )		++cnt["Message-ID: "];
		else if( is_prefix(x, "In-Reply-To: ") )	++cnt["In-Reply-To: "];
		else if( is_prefix(x, "References: ") )		++cnt["References: "];
	
	for(auto& x : cnt)
		if(/*x.first.size()  &&  */x.second > 1)	return true;
	
	return false;
}

//Имеет ли повторы строка с запятой в качестве разделителя
//Возвращает true если это так
bool has_repeats_in_string(const string& s)
{
	map<string, int> cnt;
	istringstream iss {s};
	
	string str {""};
	for(char ch = 0; iss.get(ch); )
		if(cnt.size()  &&  ch == ' '  &&  str == "") {  }
		else
		{
			if(ch != ',')		str += to_string(ch);
			else				{ ++cnt[str];	str = ""; }
		}
	
	for(auto& x : cnt)
		if(x.first.size()  &&  x.second > 1)	return true;
	
	return false;
}

//------------------------------------------------------------------------------

//Чтение файла n в строки
Mail_file::Mail_file(const string& n)
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
		
		//Если повторно было считан признак конца письма - ОШИБКА
		if( s == "----" )		error("empty message [Mail_file() constructor]");
		
		//Пустые строки считаются частью сообщения по умолчанию, но поиск конца сообщения не запускают
		if( s.size() ) {
			++msg_count;		//Подсчет сообщений
			while( s != "----"  &&  getline(in,s) )		lines.push_back(s);
			//if( !in.eof()  &&  s == "----" )			++msg_count; //Подсчет сообщений
		}
	}
	
	//Не найдено ни одного признака завершения письма
	if( !msg_count )		error("file format error: no message found [Mail_file() constructor]");
	
	//--------------------------------------------------------------------------
	
	//Обозначаем границы писем
	auto first = lines.begin();
	auto p = first;
	while(p != lines.end())
	{
		
		while(p != lines.end()  &&  *p == "")		++p;		//Пропуск пустых строк
		
		//Найден конец сообщения
		if(p != lines.end()  &&  *p == "----")
		{
			Message m {first,p}; 
			sm.insert( make_pair(find_field(m, "Subject: "), m) );
			
			//Если в данном письме есть поля (вроде From:, To:, Date: и т.д.) с повторами - ОШИБКА
			if( has_repeat_field(m) ) {
				ostringstream oss;
				for(const auto& x : m)		oss << x << endl;
				error("repeating fields in the letter [Mail_file() constructor]:\n\n" + oss.str() + "\n\n");
			}
			
			//Имеются ли повторы в получателях одного и того же письма? Если да - ОШИБКА
			string addrs = find_field(m, "To: ");
			if( has_repeats_in_string(addrs) )		error("repeating destination addresses (" + addrs + ") in the letter [Mail_file() constructor]");
			
			first = p+1;	//Строка "----" не является частью сообщения
		}
		
		
		if( p != lines.end() )		++p;
		
	}
	
	
	//Достигли конца содержимого файла, но при этом не насчитали досточное количество - ОШИБКА
	if( p == lines.end()  &&  sm.size() != msg_count )
		error("end of letter (\"----\") not found [Mail_file() constructor]");
	
	
	auto pp = sm.equal_range(sm.begin()->first);
	while(true)
	{
		//Размер строки (темы письма) больше 0 (т.к. письма могут не иметь темы)
		//				и  найдены повторы в получателях писем с одной и той же темой
		if(  pp.first->first.size()  &&  has_repeats_in_string( search_recipient(pp.first->first) )  )
			error("repeat recipients of emails with the same subject (" + pp.first->first + ") [Mail_file() constructor]");
		
		if(pp.second == sm.end())		break;
		else							pp = sm.equal_range(pp.second->first);
	}
}


//Поиск во всех сообщениях получателей писем с темой переданной в качестве аргумента
//Возвращает строку получателей через запятую (т.е. формат пригодный для ф-ции has_repeats_in_string)
string Mail_file::search_recipient(const string& s) const
{
	string addr {""};
	
	for(const auto& x : sm)
		if( x.first == s )
		{
			string str = find_field(x.second, "To: ");
			if( str.size() )
				if( addr.size() )		addr += (", " + str);
				else					addr += str;
		}
	
	return addr;
}