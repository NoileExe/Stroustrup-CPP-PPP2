


#include <addition.h>	//Включает Simple_window.h, который включает Gui.h, который в свою очередь включает Graph.h и Window.h и Point.h и std_lib_facilities.h
#include <map>
#include <set>
#include <numeric>
#include <FL/Fl_Multiline_Output.H>

//------------------------------------------------------------------------------

//Очистка слова
// (убирает сокращение "n't" заменяя на " not"; убирает окончание множественного числа "s"; пропускает все небуквенные символы; заглавные буквы в прописные)
void clear_word(string& word);

//Очистка всех слов в файле
void clear_file(const string& file_name);

//------------------------------------------------------------------------------

//Наиболее часто встречаемое в последовательности слово
map<string, int>::iterator word_max_qty (map<string, int>& msi);

//Наиболее длинное в последовательности слово
map<string, int>::iterator word_max_ln (map<string, int>& msi);

//Наиболее короткое в последовательности слово
map<string, int>::iterator word_min_ln (map<string, int>& msi);

//------------------------------------------------------------------------------

//Поиск в файле слова и указание того сколько раз он встречается.
//Так же вывод наиболее часто встречаемого, наиболее длинного и наиболее короткого слов в тексте файла
void word_qty (const string& file_name, const string& w);

//Вывод слов из файла начинающихся на указанную последовательность букв
void search_1st_letter (const string& file_name, const string& w);

//Вывод слов из файла длинной равной указанной
void search_lngth_word (const string& file_name, unsigned int ln);

//------------------------------------------------------------------------------

namespace Graph_lib
{

	//Поле вывода с переходом на новую строку
	struct MLOut_box : Widget {
		MLOut_box(Point xy, int w, int h, const string& s) : Widget(xy,w,h,s,0)		{ }
		
		void put(const string& s)		{ reference_to<Fl_Multiline_Output>(pw).value(s.c_str()); }
		
		string value()		{ return reference_to<Fl_Multiline_Output>(pw).value(); }
		
		void attach(Window& win)
		{
			pw = new Fl_Multiline_Output(loc.x, loc.y, width, height, label.c_str());
			own = &win;
		}
	};

//------------------------------------------------------------------------------

	struct Word_qty_window : Window {
		Word_qty_window(const string& file_name,    Point xy = win_centering(450,250), int w = 450, int h = 250, const string& title = "QUANTITY of words");
		
	private:
		void read_file(const string& file_name);
		map<string, int> words;
		
		
		Button search_btn;	//Кнопка для запуска процедуры поиска
		Button quit_btn;	//Закрывает окно программы
		
		Text file;			//пмя файла
		In_box wordin;		//пскомое слово
		Text max_qty;		//Наиболее чаще встречаемое слово в тексте
		Text longest;		//Самое длинное слово в тексте
		Text shortest;		//Самое короткое слово в тексте
		Text result;		//Результат поиска
		
		
		void search();				//Процедура поиска
		void quit() { hide(); }		//Закрытие окна
	};

//------------------------------------------------------------------------------

	struct Letter_srch_window : Window {
		Letter_srch_window(const string& file_name, Point xy = win_centering(450,250), int w = 450, int h = 250, const string& title = "ALL WORDS BEGINNING with the LETTER ...");
		
	private:
		const unsigned int max_line_ln {60};	//Максимальная длина линии в поле вывода
		void read_file(const string& file_name);
		set<string> words;
		
		
		Button search_btn;	//Кнопка для запуска процедуры поиска
		Button quit_btn;	//Закрывает окно программы
		
		Text file;			//пмя файла
		In_box  wordin;		//пскомое начало слова
		MLOut_box foundout;	//Найденные слова через ;
		
		
		void search();				//Процедура поиска
		void quit() { hide(); }		//Закрытие окна
	};

//------------------------------------------------------------------------------

	struct Length_srch_window : Window {
		Length_srch_window(const string& file_name,    Point xy = win_centering(450,250), int w = 450, int h = 250, const string& title = "ALL words with LETTER COUNT equal to ...");
		
	private:
		const unsigned int max_line_ln {60};	//Максимальная длина линии в поле вывода
		void read_file(const string& file_name);
		set<string> words;
		
		
		Button search_btn;	//Кнопка для запуска процедуры поиска
		Button quit_btn;	//Закрывает окно программы
		
		Text file;			//пмя файла
		In_box  wordin;		//пскомое начало слова
		MLOut_box foundout;	//Найденные слова через ;
		
		
		void search();				//Процедура поиска
		void quit() { hide(); }		//Закрытие окна
	};

}