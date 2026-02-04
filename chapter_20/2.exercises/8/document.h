


#include <std_lib_facilities.h>
#include <typeinfo>

//------------------------------------------------------------------------------

//namespace doc {

	using Line = vector<char>;	//Строка - это вектор символов

	//Отслеживает строку и позицию символа в строке
	class Text_iterator {
		list<Line>::iterator ln;
		Line::iterator pos;
	
	public:
		//Устанавливает итератор на позицию pp в ll-й строке
		Text_iterator(list<Line>::iterator ll, Line::iterator pp) : ln{ll}, pos{pp}		{  }
		
		list<Line>::iterator get_line() const {  return ln; }
		Line::iterator   get_position() const { return pos; }
		
		//Переход к следующей строке
		Text_iterator& next_line()
		{ ++ln;		pos = (*ln).begin();		return *this; }
		
		char& operator*()		{ return *pos; }
		char& operator*() const	{ return *pos; }
		Text_iterator& operator++();
		
		bool operator==(const Text_iterator& other) const
			{ return (ln == other.ln && pos == other.pos); }
		
		bool operator!=(const Text_iterator& other) const
			{ return !(*this == other); }
	};


	struct Document {
		list<Line> line;		//Документ - это список строк
		
		Document() { line.push_back( Line{} ); }
		
		Text_iterator begin()	//Первая строка первый символ
			{ return Text_iterator( line.begin(), (*line.begin()).begin() ); }
		
		Text_iterator end()		//За последним символом документа
		{
			if( line.size() == 1 )		error("empty document");
			list<Line>::iterator last_line = line.end();
			--last_line;
			return Text_iterator( last_line, (*last_line).end() );
		}
	};

	//------------------------------------------------------------------------------

	//Удаление из документа d строки под номером n
	void erase_line(Document& d, int n);

	//Найти в документе все слова old_word и заменить их на new_word
	void replace_words(Document& d, const string& old_word, const string& new_word);

	//Найти в последовательности [first; last) строку s
	//Возврат итератора на первый символ искомой строки в последовательности
	Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s);

	//Сравнение начала последовательности до встречи пробельного символа со строкой s
	bool match(Text_iterator first, Text_iterator last, const string& s);
	
	//Перебор строк для определения последней в лексикографическом порядке
	template<typename Iter>		// *Iter яв-ся контейнером с операцией индексирования []
	Iter last_alphabet_line(Iter first, Iter last) {
		if(first == last)		return last;
		
		Iter max_alpha {first++};
		//++first;
		while(first != last)
		{
			if( (*max_alpha)[0] < (*first)[0] )			max_alpha = first;
			else if( (*max_alpha)[0] == (*first)[0] )
				for(int i=0;   i < max_alpha->size()  &&  i < first->size();   ++i) {
					if( (*max_alpha)[i] < (*first)[i] )			{ max_alpha = first;	break; }
					else if( (*max_alpha)[i] > (*first)[i] )	break;
				}
			
			++first;
		}
		
		return max_alpha;
	}

	ostream& operator<<(ostream& os, Document& d);
	istream& operator>>(istream& is, Document& d);

//}