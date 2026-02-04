

#include <addition.h>
#include "money.h"


namespace Graph_lib
{
	struct My_window : Window {
		My_window(Point xy, int w, int h, const string& title)
			: Window{xy,w,h,title},
			  button_pushed(false),
			  next_button{ Point{x_max()-150, 0}, 70, 20, "Next",
							[](Address, Address pw) { reference_to<My_window>(pw).next(); } },
			  quit_button{ Point{x_max()-70, 0},  70, 20, "Quit",
							[](Address, Address pw) { reference_to<My_window>(pw).quit(); } }
		{
			attach(next_button);
			attach(quit_button);
		}
		
		void wait_for_button() {
			while (!button_pushed) Fl::wait();
			button_pushed = false;
			Fl::redraw();
		}
		
	protected:
		Button next_button;		//Добавляет пару (next_x, next_y) в объект lines
		Button quit_button;		//Завершает работу программы
		
		bool button_pushed;		//Деталь реализации класса
		
		virtual void next() { button_pushed = true; }
		virtual void quit() { hide(); exit(0); }
	};
	
	//------------------------------------------------------------------------------
	
	//Перевод валют. Если перевод не из рублей или не в рубли, то при переводе между валютами
	// рубль будет базовой валютой и сначала перевод будет производиться в неё и только потом в конечную валюту
	//Курсы по отношению к рублю считываются из файла из записей в формате ВАЛЮТА КУРС.
	//Если курса какой-то из валют не находиться - кнопка с названием валюты будет скрыта из меню
	//Поддерживаются следующие валюты (их аббревиатуры):
	//USD	Доллар США
	//CAD	Канадский доллар
	//RUB	Российский рубль
	//EUR	Евро
	//GBP	Фунт стерлинга
	//JPY	Японская йена
	//CNY	Китайский юань
	
	struct Converter_window : My_window {
		Converter_window(const string& path);
		
	private:
		//Данные:
		vector<Money_Unit> rates;		//Курсы валют по отношению к рублю
		
		
		//Виджеты:
		In_box input;
		Out_box result;
		Menu from_menu;
		Button from_btn;
		Menu to_menu;
		Button to_btn;
		
		
		//Реализация:
		void next();		//Собственно конвертация
		void hide_menu();	//Прячет оба меню и отображает обе кнопки для их отображения
		
		//Отображение меню
		void from_menu_press();
		void to_menu_press();
		
		//Изменение валюты для операции перевода
		void set_from_currency(string str);
		void set_to_currency(string str);
	};
	
	
	
	Converter_window::Converter_window(const string& path)	//Пусть к файлу с курсами валют
		: My_window{win_centering(340,80),   340, 80,   "Конвертёр валют"},
		  input{  Point{x_max()-300, 10}, 50, 20, "USD" },
		  result{ Point{x_max()-210, 10}, 50, 20, "RUB" },
		  from_menu{ Point{x_max()-320, 50}, 140, 20, Menu::vertical, "Перевод из валюты" },
		  from_btn{  Point{x_max()-320, 50}, 140, 20, "",
					[](Address, Address pw) { reference_to<Converter_window>(pw).from_menu_press(); } },
		  to_menu{ Point{x_max()-160, 50}, 140, 20, Menu::vertical, "Перевод в валюту" },
		  to_btn{  Point{x_max()-160, 50}, 140, 20,   "",
					[](Address, Address pw) { reference_to<Converter_window>(pw).to_menu_press(); } }
	{
		//------------------------------------------------------------------------------
		
		ifstream ifs { path };
		if (!ifs)		error("the specified file cannot be opened (" + path + ")");
		ifs.exceptions(ifs.exceptions() | ios_base::badbit);	// Генерация исключения в случае состояния bad ()
		
		//Данные 4 строки можно было бы убрать если бы получилось передать аргумент (строка с именем валюты) в Callback функцию
		string currency {"RUB"};
		double exchange_rate {1.0};
		rates.push_back( Money_Unit{currency, exchange_rate} );
		vector<string> currencies {"USD", "CAD", "RUB", "EUR", "GBP", "JPY", "CNY"};
		
		while (ifs >> currency >> exchange_rate)
			rates.push_back( Money_Unit{currency, exchange_rate} );
		
		if ( !ifs.eof() )			error("an error occurred while reading the file ", path);
		if ( rates.size() == 0)		error("empty file ", path);
		
		//Проверка наличия базовой валюты
		for (int i=0; i < rates.size(); ++i)
			if ( rates[i].exchange_rate == 1 )		break;
			else if ( i == rates.size()-1 )			rates.push_back( Money_Unit{"BASE", 1.0} );
		
		
		for (int i=0; i < rates.size(); ++i)
		{
			//Разрешено ли использовать валюту (наличие аббревиатуры валюты в векторе 'currencies')
			for (auto s : currencies)
				if ( s == currencies[currencies.size()-1]  &&  rates[i].unit_name != s  &&  rates[i].unit_name != "BASE" )
					error("bad currency name");
				else if ( rates[i].unit_name == s )
					break;
			
			//Поиск повторов валют
			for (int j=0; j < rates.size(); ++j)
				if ( i != j  &&  rates[i].unit_name == rates[j].unit_name )						error("currency repeat in vector of exchange rates");
				//if ( i != j  &&  rates[i] == rates[j] )											error("currency repeat in vector of exchange rates");
			
			//Установка начальных значений
			if ( from_btn.label == ""  &&  rates[i].exchange_rate != 1 ) {
				from_btn.label = "Перевести из " + rates[i].unit_name;
				input.label = rates[i].unit_name;
			}
			
			if ( to_btn.label == ""  &&  rates[i].exchange_rate == 1 ) {
				to_btn.label = "Перевести в " + rates[i].unit_name;
				result.label = rates[i].unit_name;
			}
		}
		
		//------------------------------------------------------------------------------
		
		//Все кнопки обоих меню можно было бы добавлять циклом из строк unit_name вектора rates если бы получилось
		//передать аргумент (строка с именем валюты) в Callback функцию
		
		from_menu.attach(new Button { Point{0,0},0,0, "USD",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_from_currency("USD"); } });
		from_menu.attach(new Button { Point{0,0},0,0, "CAD",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_from_currency("CAD"); } });
		from_menu.attach(new Button { Point{0,0},0,0, "RUB",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_from_currency("RUB"); } });
		from_menu.attach(new Button { Point{0,0},0,0, "EUR",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_from_currency("EUR"); } });
		from_menu.attach(new Button { Point{0,0},0,0, "GBP",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_from_currency("GBP"); } });
		from_menu.attach(new Button { Point{0,0},0,0, "JPY",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_from_currency("JPY"); } });
		from_menu.attach(new Button { Point{0,0},0,0, "CNY",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_from_currency("CNY"); } });
		
		to_menu.attach(new Button { Point{0,0},0,0, "USD",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_to_currency("USD"); } });
		to_menu.attach(new Button { Point{0,0},0,0, "CAD",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_to_currency("CAD"); } });
		to_menu.attach(new Button { Point{0,0},0,0, "RUB",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_to_currency("RUB"); } });
		to_menu.attach(new Button { Point{0,0},0,0, "EUR",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_to_currency("EUR"); } });
		to_menu.attach(new Button { Point{0,0},0,0, "GBP",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_to_currency("GBP"); } });
		to_menu.attach(new Button { Point{0,0},0,0, "JPY",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_to_currency("JPY"); } });
		to_menu.attach(new Button { Point{0,0},0,0, "CNY",
							[](Address, Address pw) { reference_to<Converter_window>(pw).set_to_currency("CNY"); } });
		
		//Проверка ошибок если бы было автоматическое заполнение меню из файла
		if ( from_menu.selection.size() != to_menu.selection.size() )		error("the number of menus items is different (from_menu & to_menu)");
		
		//------------------------------------------------------------------------------
		
		//Заменяем на несколько изменённую ф-цию чтобы изменять текст кнопки
		next_button.do_it = [](Address, Address pw) { reference_to<Converter_window>(pw).next(); };
		next_button.label = "Convert";
		next_button.move(0,10);
		quit_button.move(0,10);
		
		detach(next_button);	//Открепляем от окна виджеты чтобы размеры не деформировались при изменении размеров окна
		detach(quit_button);
		
		const int h = 80 + 20*(from_menu.selection.size()-1);
		resize(340, h);
		
		attach(input);
		attach(result);
		attach(next_button);
		attach(quit_button);
		
		attach(from_menu);
		attach(from_btn);
		attach(to_menu);
		attach(to_btn);
		hide_menu();
	}
	
	
	
	void Converter_window::next() {
		hide_menu();
		
		double a_rate {rates[0].exchange_rate};		//Из чего переводить (курс)
		double b_rate {rates[0].exchange_rate};		//Во что переводить (курс)
		
		for (auto m : rates){
			if ( m.unit_name == input.label )		a_rate = m.exchange_rate;
			if ( m.unit_name == result.label )		b_rate = m.exchange_rate;
		}
		
		double num_a;
		double num_b;
		string str { input.get_string() };
		
		if ( str.size() != 0 ) {
			stringstream ss { str };
			ss >> num_a;
			if ( isinf(num_a)  ||  isnan(num_a)  ||  !ss )		error("bad input");
			
			num_b = num_a * a_rate;
			if ( b_rate != 1 )		num_b = num_b / b_rate;		//Не является базовой валютой
			num_b = round_05rule(num_b);
			
			ss.str("");		//Очистка строкового потока ввода
			ss.clear();
			ss << defaultfloat << num_b;
			result.put( ss.str() );
		}
		
		My_window::next();
	}
	
	void Converter_window::hide_menu() {
		from_menu.hide();
		to_menu.hide();
		from_btn.show();
		to_btn.show();
	}
	
	void Converter_window::from_menu_press() {
		hide_menu();
		from_btn.hide();
		from_menu.show();
		//Сокрытие кнопок меню с валютами по которым данные не были считаны
		for(int i=0; i < from_menu.selection.size(); ++i)
			for(int j=0; j < rates.size(); ++j)
				if ( from_menu.selection[i].label  == rates[j].unit_name )		break;
				else if ( j == rates.size()-1 )									from_menu.selection[i].hide();
	}
	
	void Converter_window::to_menu_press() {
		hide_menu();
		to_btn.hide();
		to_menu.show();
		//Сокрытие кнопок меню с валютами по которым данные не были считаны
		for(int i=0; i < to_menu.selection.size(); ++i)
			for(int j=0; j < rates.size(); ++j)
				if ( to_menu.selection[i].label  == rates[j].unit_name )		break;
				else if ( j == rates.size()-1 )									to_menu.selection[i].hide();
	}
	
	void Converter_window::set_from_currency(string str) {
		input.label = str;
		detach(from_btn);
		from_btn.label = "Перевести из " + str;
		attach(from_btn);
		hide_menu();
	}
	
	void Converter_window::set_to_currency(string str) {
		result.label = str;
		detach(to_btn);
		to_btn.label = "Перевести в " + str;
		attach(to_btn);
		hide_menu();
	}
}