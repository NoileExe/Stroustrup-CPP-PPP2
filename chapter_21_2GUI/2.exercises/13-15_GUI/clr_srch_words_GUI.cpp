

#include "clr_srch_words_GUI.h"
#include <iterator>

//------------------------------------------------------------------------------

//Очистка слова
// (убирает сокращение "n't" заменяя на " not"; убирает окончание множественного числа "s"; пропускает все небуквенные символы; заглавные буквы в прописные)
void clear_word(string& word)
{
	if(word == "won't"  ||  word == "won't ")		{ word = "will not";	return; }
	else if(word == "can't"  ||  word == "can't ")	{ word = "can not";		return; }
	
	ostringstream tmp;
	for(int i = 0; i < word.size(); ++i)
		//сокращение 'not'
		if( word[i] == 'n' &&
			i+1 < word.size()  &&  i+2 < word.size()  &&  i+3 == word.size()
			&&  word[i+1] == '\''  &&  word[i+2] == 't' )
										{ tmp << " not";	break; }
		
		//множественное число либо лишний апостроф
		else if( (word[i] == 's'  &&  i+1 == word.size()  &&  tmp.str().size() > 1)  ||  !isalpha(word[i]) )
										{  }
		
		//заглавные буквы
		else if( isupper(word[i]) )		{ word[i]= tolower( word[i] );		tmp << word[i]; }
		
		else							tmp << word[i];
	
	word = tmp.str();
}

//Очистка всех слов в файле
void clear_file(const string& file_name)
{
	fstream ifs {file_name, fstream::in};	//Открываем файловый поток ввода
	if (!ifs)	error("Unable to open file '" + file_name + "'");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	ifs << std::noskipws;					//Чтобы не пропускать пробелы
	
	istream_iterator<char> ii{ifs};			//Создаём итератор ввода
	istream_iterator<char> ii_eof;			//Ограничитель ввода (итератор по умолчанию, который означает eof)
	
	ofstream ofs {file_name};				//Открываем файловый поток вывода
	ostream_iterator<char> oi{ofs};			//Создаём итератор вывода
	
	while( ii != ii_eof )
	{
		string word;
		while( ii != ii_eof  &&  isalpha(*ii) ) //Считываем слово
		{
			word += *ii++;
			if( ii != ii_eof  &&  *ii == '\'' )		word += *ii++;
		}
		
		if( word.size() )		clear_word(word);
		
		for(auto& ch : word)						*oi = ch;
		if( ii != ii_eof  &&  !isspace(*ii) )		*oi = ' ';
		else if( ii != ii_eof )						*oi = *ii;
		
		if( ii != ii_eof )		++ii;
	}
	
	ifs.close();
	ofs.close();
}

//------------------------------------------------------------------------------

//Наиболее часто встречаемое в последовательности слово
map<string, int>::iterator word_max_qty (map<string, int>& msi)
{
	auto max = msi.begin();
	
	for(auto it = msi.begin(); it != msi.end(); ++it)
		if( max->second < it->second )		max = it;
	
	return max;
}

//Наиболее длинное в последовательности слово
map<string, int>::iterator word_max_ln (map<string, int>& msi)
{
	auto max = msi.begin();
	
	for(auto it = msi.begin(); it != msi.end(); ++it)
		if( (*max).first.size() < (*it).first.size() )		max = it;
	
	return max;
}

//Наиболее короткое в последовательности слово
map<string, int>::iterator word_min_ln (map<string, int>& msi)
{
	auto min = msi.begin();
	
	for(auto it = msi.begin(); it != msi.end(); ++it)
		if( (*min).first.size() > (*it).first.size() )		min = it;
	
	return min;
}

//------------------------------------------------------------------------------

//Поиск в файле слова и указание того сколько раз он встречается.
//Так же вывод наиболее часто встречаемого, наиболее длинного и наиболее короткого слов в тексте файла
void word_qty (const string& file_name, const string& w)
{
	ifstream ifs {file_name, fstream::in};	//Открываем файловый поток ввода
	if (!ifs)	error("Unable to open file '" + file_name + "'");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	
	string word = w;
	clear_word(word);
	
	map<string, int> words;
	for(string s; ifs >> s; )		{ clear_word(s);	++words[s]; }
	
	auto iw = find_if( words.begin(), words.end(), [&](const pair<string, int>& psi) { return psi.first == word; } );
	if(iw != words.end())
		cout << "\n\nThe word '" << iw->first << "' appears in the text " << iw->second << " time(s)\n";
	else
		cout << "\n\nThe word '" << word << "' is not found\n";
	
	iw = word_max_qty(words);
	cout << "The most frequently used word in the text is: " << iw->first << " (" << iw->second << ")\n";
	
	iw = word_max_ln(words);
	cout << "The longest word in the text is: " << (*iw).first << " (" << (*iw).first.size() << ")\n";
	
	iw = word_min_ln(words);
	cout << "The shortest word in the text is: " << (*iw).first << " (" << (*iw).first.size() << ")\n";
}

//------------------------------------------------------------------------------

//Вывод слов из файла начинающихся на указанную последовательность букв
void search_1st_letter (const string& file_name, const string& w)
{
	ifstream ifs {file_name, fstream::in};	//Открываем файловый поток ввода
	if (!ifs)	error("Unable to open file '" + file_name + "'");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	
	string word = w;
	clear_word(word);
	set<string> words;
	
	cout << "\n\nWords starting on the letter(s) " << word << ":\n";
	for(string s; ifs >> s; )
	{
		clear_word(s);
		
		if(s.size() >= word.size()) {
			for(int i = 0; i < word.size(); ++i)
				if(s[i] != word[i])				break;
				else if(i == word.size()-1)		words.insert(s);
		}
	}
	
	for(auto& s : words)		cout << s << endl;
}

//------------------------------------------------------------------------------

//Вывод слов из файла длинной равной указанной
void search_lngth_word (const string& file_name, unsigned int ln)
{
	ifstream ifs {file_name, fstream::in};	//Открываем файловый поток ввода
	if (!ifs)	error("Unable to open file '" + file_name + "'");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	
	set<string> words;
	
	cout << "\n\n" << ln << " letter(s) long words:\n";
	for(string s; ifs >> s; )
	{
		clear_word(s);
		if(s.size() == ln)		words.insert(s);
	}
	
	for(auto& s : words)		cout << s << endl;
}

//------------------------------------------------------------------------------

namespace Graph_lib
{

	Word_qty_window::Word_qty_window(const string& file_name,    Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  search_btn { Point{w-w/2-80,  h-30}, 70, 20,  "Find",
						[](Address, Address pw) { reference_to<Word_qty_window>(pw).search(); } },
		  quit_btn   { Point{w-w/2+10,  h-30}, 70, 20,  "Close",
						[](Address, Address pw) { reference_to<Word_qty_window>(pw).quit(); } },
		  
		  file    { Point{20, 30},	"File: " + file_name },
		  wordin { Point{160, 50}, 240, 20, "Search word: " },
		  max_qty { Point{20, 100},	"Frequently used:   " },
		  longest { Point{20, 130},	"   Longest word:   " },
		  shortest{ Point{20, 160},	"  Shortest word:   " },
		  result  { Point{20, 190},	"Result: ..." }
	{
		read_file(file_name);
		
		attach(search_btn);
		attach(quit_btn);
		
		attach(wordin);
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		max_qty.set_color(Color::black);
		max_qty.set_font(Graph_lib::Font::helvetica);
		max_qty.set_font_size(16);
		longest.set_color(Color::black);
		longest.set_font(Graph_lib::Font::helvetica);
		longest.set_font_size(16);
		shortest.set_color(Color::black);
		shortest.set_font(Graph_lib::Font::helvetica);
		shortest.set_font_size(16);
		result.set_color(Color::black);
		result.set_font(Graph_lib::Font::helvetica_bold);
		result.set_font_size(16);
		
		attach(file);
		
		auto iw = word_max_qty(words);
		max_qty.set_label( "Frequently used:   " + iw->first + " (" + to_string( iw->second ) + ")" );
		attach(max_qty);
		
		iw = word_max_ln(words);
		longest.set_label( "   Longest word:   " + (*iw).first  + " (" + to_string((*iw).first.size()) + " symb)" );
		attach(longest);
		
		iw = word_min_ln(words);
		shortest.set_label( "  Shortest word:   " + (*iw).first + " (" + to_string((*iw).first.size()) + " symb)" );
		attach(shortest);
		attach(result);
	}

	//Считывает все значения из файла в объект map
	void Word_qty_window::read_file(const string& file_name)
	try {
		ifstream ifs {file_name};	//Открываем файловый поток ввода
		if (!ifs)	error("Unable to open file '" + file_name + "'");
		ifs.exceptions(ifs.exceptions() | ios_base::badbit);
		
		//ifs.clear(ios_base::badbit);
		for(string s; ifs >> s; )		{ clear_word(s);	++words[s]; }
	}
	catch (exception& e)	{ result.set_label( "Error: " + std::string( e.what() ) ); }
	catch (...)				{ result.set_label( "Oops! Problems in " + file_name ); }

	//Процедура поиска
	void Word_qty_window::search()
	{
		result.set_label( "Result: ..." );
		
		string word { wordin.get_string() };
		
		if( !word.size() )
			result.set_label( "Result: empty word field" );
		
		else {
			clear_word(word);
			auto iw = find_if( words.begin(), words.end(), [&](const pair<string, int>& psi) { return psi.first == word; } );
			
			if(iw != words.end())		result.set_label( "Result: the word '" + iw->first + "' appears in the text " + to_string(iw->second) + " time(s)" );
			else						result.set_label( "Result: the word '" + word + "' is not found" );
		}
		
		redraw();
	}

	//------------------------------------------------------------------------------

	Letter_srch_window::Letter_srch_window(const string& file_name,    Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  search_btn { Point{w-w/2-80,  h-30}, 70, 20,  "Find",
						[](Address, Address pw) { reference_to<Letter_srch_window>(pw).search(); } },
		  quit_btn   { Point{w-w/2+10,  h-30}, 70, 20,  "Close",
						[](Address, Address pw) { reference_to<Letter_srch_window>(pw).quit(); } },
		  
		  file    { Point{20, 30},	"File: " + file_name },
		  wordin   { Point{160, 50}, 240, 20, "Search 1st letters: " },
		  foundout { Point{20, 80}, 410, 120, "" }
	{
		read_file(file_name);
		
		attach(search_btn);
		attach(quit_btn);
		
		attach(wordin);
		attach(foundout);
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		
		attach(file);
	}

	//Считывает все значения из файла в объект set
	void Letter_srch_window::read_file(const string& file_name)
	try {
		ifstream ifs {file_name};	//Открываем файловый поток ввода
		if (!ifs)	error("Unable to open file '" + file_name + "'");
		ifs.exceptions(ifs.exceptions() | ios_base::badbit);
		
		for(string s; ifs >> s; )		{ clear_word(s);	words.insert(s); }
	}
	catch (exception& e)	{ cerr << "\nError: " << e.what() << endl; }
	catch (...)				{ cerr << "\nOops! Problems in " << file_name << endl; }

	//Процедура поиска
	void Letter_srch_window::search()
	{
		ostringstream txt;
		foundout.put( txt.str() );
		
		string word { wordin.get_string() };
		if( word.size() )
		{
			clear_word(word);
			
			unsigned int ln {0};
			for(auto& s : words)
				if( s.size() >= word.size()  &&  s.find(word, 0) == 0 )
					if( ln + s.size() + 4 > max_line_ln )		{ txt << s << ";\n";	ln = 0; }
					else										{ txt << s << ";   ";	ln += s.size() + 4; }
			
			if( txt.str().size() )		foundout.put( txt.str() );
			else						foundout.put( "Nothing found" );
			
			//cout << foundout.value();
		}
		
		else		foundout.put( "empty letter(s) field" );
		
		redraw();
	}

	//------------------------------------------------------------------------------

	Length_srch_window::Length_srch_window(const string& file_name,    Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  search_btn { Point{w-w/2-80,  h-30}, 70, 20,  "Find",
						[](Address, Address pw) { reference_to<Length_srch_window>(pw).search(); } },
		  quit_btn   { Point{w-w/2+10,  h-30}, 70, 20,  "Close",
						[](Address, Address pw) { reference_to<Length_srch_window>(pw).quit(); } },
		  
		  file    { Point{20, 30},	"File: " + file_name },
		  wordin   { Point{160, 50}, 240, 20, "Search word with lng: " },
		  foundout { Point{20, 80}, 410, 120, "" }
	{
		read_file(file_name);
		
		attach(search_btn);
		attach(quit_btn);
		
		attach(wordin);
		attach(foundout);
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		
		attach(file);
	}

	//Считывает все значения из файла в объект set
	void Length_srch_window::read_file(const string& file_name)
	try {
		ifstream ifs {file_name};	//Открываем файловый поток ввода
		if (!ifs)	error("Unable to open file '" + file_name + "'");
		ifs.exceptions(ifs.exceptions() | ios_base::badbit);
		
		for(string s; ifs >> s; )		{ clear_word(s);	words.insert(s); }
	}
	catch (exception& e)	{ cerr << "\nError: " << e.what() << endl; }
	catch (...)				{ cerr << "\nOops! Problems in " << file_name << endl; }

	//Процедура поиска
	void Length_srch_window::search()
	{
		ostringstream txt;
		foundout.put( txt.str() );
		
		int word { wordin.get_int() };
		if( word  &&  word > 0 )
		{
			unsigned int ln {0};
			for(auto& s : words)
				if(s.size() == word)
					if( ln + s.size() + 4 > max_line_ln )		{ txt << s << ";\n";	ln = 0; }
					else										{ txt << s << ";   ";	ln += s.size() + 4; }
			
			if( txt.str().size() )		foundout.put( txt.str() );
			else						foundout.put( "Nothing found" );
		}
		
		else		foundout.put( "bad count field" );
		
		redraw();
	}

	//------------------------------------------------------------------------------

}