


#include "document.h"

//------------------------------------------------------------------------------

//namespace doc {
	
	Text_iterator& Text_iterator::operator++()
	{
		++pos;							//Переход к следующему символу
		
		//Если позиция - конец текущей строки
		if( pos == (*ln).end() ) {
			++ln;						//Переход на новую строку
			pos = (*ln).begin();
		}
		
		return *this;
	}

	//------------------------------------------------------------------------------

	//Удаление из документа d строки под номером n
	void erase_line(Document& d, int n)
	{
		if( n < 0  ||  d.line.size()-1 <= n )	return;
		auto p = d.line.begin();
		advance(p, n);
		d.line.erase(p);
	}

	//Найти в последовательности слово old_word и заменить на new_word
	//Возврат итератора первого символа нового слова
	void replace_words(Document& d, const string& old_word, const string& new_word)
	{
		auto b = d.begin();
		auto e = d.end();
		
		//Поиск всех точных совпадений в документе
		for(auto p = find_txt(b, e, old_word);   p != e;   p = find_txt(b, e, old_word))
		{
			auto l = p.get_line();
			auto s = p.get_position();
			
			//cout << &(*s) << endl;
			
			for(char& ch : *l) {
				if( &ch == &(*s) ) {
					auto ch_iter = l->erase( s, s+old_word.size() );
					
					//Вставляем посимвольно новое слово
					for(char n : new_word) {
						ch_iter = l->insert(ch_iter, n);
						++ch_iter;
					}
					
					break;
				}
			}
			
			//cout << &(*s) << endl;
		}
	}

	//Найти в последовательности [first; last) строку s
	//Возврат итератора на первый символ искомой строки в последовательности
	Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
	{
		if(s.size() == 0)		return last; //Поиск пустой строки запрещён
		char first_char = s[0];
		while(true) {
			auto p = first;
			
			//Не даёт вырвать часть из другого слова, т.е. первая буква искомого слова должна быть первой буквой найденного слова (перед ней пробельный символ)
			for( auto prev = p;
				 p!=last  &&  !(*p == first_char  &&  (isspace(*prev) || prev == first) );
				 ++p )
					{ prev = p; }
			
			
			if( p == last  ||  match(p, last, s) )		return p;
			first = ++p;		//Ищем следующее вхождение символа
		}
	}

	//Сравнение начала последовательности до встречи пробельного символа со строкой s
	bool match(Text_iterator first, Text_iterator last, const string& s)
	{
		for(int i = 0;   i<s.size()  &&  first!=last;   ++i, ++first)
			if(*first != s[i])		return false;
		
		//За последним символом совпавшей строки может быть не пробельный символ - соответственно точное совпадение не найдено
		if(first!=last  &&  !isspace(*first))		return false;
		return true;
	}
	
	//Сравнение начала последовательности до встречи пробельного символа со строкой s
	/*bool match(Text_iterator first, Text_iterator last, const string& s)
	{
		string::const_iterator p;
		
		for(p = s.begin(); 
			p != s.end() && first != last && *p == *first; 
			++p, ++first)
		{}
		
		//За последним символом совпавшей строки может быть не пробельный символ - соответственно точное совпадение не найдено
		if(first!=last  &&  !isspace(*first))		return false;
		return p == s.end(); // if we reached end of string, we matched it all
	}*/

	//------------------------------------------------------------------------------

	//Подсчёт всех символов в документе включая пробелы (with_spaces == true) или без них (только буквы, цифры и знаки)
	unsigned int char_count(Document& d, bool with_spaces)
	{
		unsigned int count {0};
		
		for(auto p = d.begin(); p != d.end(); ++p)
			if (isprint(*p)  &&  !isspace(*p))					++count;
			else if (with_spaces  &&  (*p==' ' || *p=='\t'))	++count;
			//else if (with_spaces  &&  isspace(*p))				++count;
		
		return count;
	}

	//Подсчёт всех слов (последовательность любых символов разделённых пробельными символами) в документе
	unsigned int words_count_whitespaces(Document& d) {
		unsigned int count {0};
		
		for(auto p = d.begin(); p != d.end(); ++p)
			//Нашли начало слова
			if (isprint(*p)  &&  !isspace(*p)) {
				++count;
				
				while(p!=d.end()  &&  isprint(*p)  &&  !isspace(*p))		++p;
				if(p == d.end())											break;
			}
		
		return count;
	}

	//Подсчёт всех слов (неразрывная последовательность буквенных символов разделённых другими символами) в документе
	unsigned int words_count_alphabetic(Document& d) {
		unsigned int count {0};
		
		for(auto p = d.begin(); p != d.end(); ++p)
			//Нашли начало слова
			if (isalpha(*p)) {
				++count;
				
				while(p!=d.end()  &&  isalpha(*p))		++p;
				if(p == d.end())						break;
			}
		
		return count;
	}

	//------------------------------------------------------------------------------

	//Содержится ли символ ch в строке s (если да - возврат true)
	bool is_separator(char ch, const string& s) {
		for(auto si = s.begin(); si != s.end(); ++si)
			if(ch == *si)		return true;
		
		return false;
	}

	//Подсчёт всех слов (последовательность любых символов разделённых символами указанными в строке s) в документе
	unsigned int words_count_custom(Document& d, const string& s) {
		unsigned int count {0};
		
		for(auto p = d.begin(); p != d.end(); ++p)
			//Нашли начало слова
			if ( !is_separator(*p, s) ) {
				++count;
				
				while(p!=d.end()  &&  !is_separator(*p, s))		++p;
				if(p == d.end())								break;
			}
		
		
		return count;
	}

	//------------------------------------------------------------------------------

	ostream& operator<<(ostream& os, Document& d)
	{
		//for(auto p : d)		os << *p;
		for(auto p = d.begin(); p != d.end(); ++p)		os << *p;
		return os;
	}

	istream& operator>>(istream& is, Document& d)
	{
		//Пока не будет достигнут конец документа или пока не возникнет ошибка
		for(char ch; is.get(ch); ) {
			d.line.back().push_back(ch);						//Добавление символа
			if(ch == '\n')		d.line.push_back( Line{} );		//Добавление следующей строки
		}
		
		if( d.line.back().size() )		d.line.push_back( Line{} );		//Добавление последней пустой строки
		
		return is;
	}
	
//}