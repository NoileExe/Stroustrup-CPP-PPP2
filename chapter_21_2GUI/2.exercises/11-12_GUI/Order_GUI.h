


#include "Order.h"
#include <addition.h>	//Включает Simple_window.h, который включает Gui.h, который в свою очередь включает Graph.h и Window.h и Point.h и std_lib_facilities.h


namespace Graph_lib
{

	struct Show_window : Window {
		Show_window(const string& file_name, Point xy = win_centering(450,300), int w = 450, int h = 300, const string& title = "SHOW orders in file");
		Show_window(const vector<Order>& v, Point xy = win_centering(450,300), int w = 450, int h = 300, const string& title = "SHOW orders");
		
	private:
		unsigned int ocurr {0};
		unsigned int pcurr {0};
		vector<Order> vo;
		
		
		Button oprev_btn;	//Пред. заказ
		Button onext_btn;	//След. заказ
		Button pprev_btn;	//Пред. позиция в чеке
		Button pnext_btn;	//След. позиция в чеке
		Button quit_btn;	//Закрывает окно программы
		
		Text file;			//Имя файла
		Text ocount;		//Кол-во заказов в файле
		Text pcount;		//Кол-во позиций в текущем заказе
		Text name;			//Имя или номер заказа
		Text date;			//Дата заказа или день рождения
		Text addr;			//Адрес доставки заказа
		Text purchase;		//Текущая позиция в текущем заказе
		
		
		void oprev();				//Предыдущий заказ
		void onext();				//Следующий заказ
		void pprev();				//Предыдущая позиция в чеке
		void pnext();				//Следующая позиция в чеке
		void quit() { hide(); }		//Закрытие окна
	};

//------------------------------------------------------------------------------

	struct Sort_window : Window {
		Sort_window(const string& file_name, Point xy = win_centering(400,150), int w = 400, int h = 150, const string& title = "SORT orders in file or SORTed view");
		
	private:
		//Данные:
		vector<Order> vo;
		
		
		//Виджеты:
		Button sort_btn;	//Выполнить сортировку в файле по заданному критерию
		Button quit_btn;	//Закрывает окно программы
		
		Text file;			//Имя файла
		Text sortby;		//Сортировать по...
		
		In_box tofile;		//Поле ввода пути/имени файла вывода
		
		Menu sort_menu;		//Выбор функций
		Button menu_btn;	//Открывает меню
		
		
		//Обратные вызовы:
		void show_menu() { hide_menu();		menu_btn.hide();		sort_menu.show(); }
		void hide_menu() { sort_menu.hide();		menu_btn.show(); }
		
		void set_sort(const string&);	//Изменение фактора сортировки
		void sortit();					//Сортировка
		void quit() { hide(); }			//Закрытие окна
	};

//------------------------------------------------------------------------------

	struct Add_window : Window {
		Add_window(const string& fn, Point xy = win_centering(600,300), int w = 600, int h = 300, const string& title = "ADD order/purchase to file");
		
	private:
		string file_name;
		vector<Order> vo;
		
		
		Button add_order_btn;	//Кнопка для добавления заказа
		Button add_purch_btn;	//Кнопка для добавления сделки в заказ
		Button quit_btn;		//Закрывает окно программы
		
		Text file;			//Имя файла
		In_box name;		//Имя или номер заказа
		In_box date;		//Дата заказа или день рождения
		In_box addr;		//Адрес доставки заказа
		In_box goods;		//Позиция (сделка) в заказе, название товара
		In_box price;		//Цена за единицу товара
		In_box count;		//Количество позиций товара
		Text result;		//Результат поиска
		
		
		void add_order();			//Добавление заказа
		void add_purch();			//Добавление позиции в заказ
		void quit() { hide(); }		//Закрытие окна
	};

//------------------------------------------------------------------------------

	struct Summ_window : Window {
		Summ_window(const string& file_name, Point xy = win_centering(400,200), int w = 400, int h = 200, const string& title = "TOTAL cost of orders in file");
		
	private:
		vector<Order> vo;
		
		
		Button quit_btn;	//Закрывает окно программы
		
		Text file;			//Имя файла
		Text count;			//Кол-во заказов в файле
		Text greater;		//Наибольший и наименьшие заказы по сумме
		Text lower;
		Text summ;			//Сумма всех заказов в файле
		
		
		void quit() { hide(); }
	};

//------------------------------------------------------------------------------

	struct Search_window : Window {
		Search_window(const string& file_name, Point xy = win_centering(450,250), int w = 450, int h = 250, const string& title = "SEARCH for orders in a file by criteria");
		
	private:
		unsigned int curr {0};
		vector<Order> vo;
		vector<Order> found;
		
		
		Button search_btn;	//Кнопка для запуска процедуры поиска
		Button quit_btn;	//Закрывает окно программы
		
		Text file;			//Имя файла
		In_box name;		//Имя или номер заказа
		In_box date;		//Дата заказа или день рождения
		In_box addr;		//Адрес доставки заказа
		In_box goods;		//Текущая позиция в текущем заказе
		Text result;		//Результат поиска
		
		
		void search();				//Процедура поиска
		void quit() { hide(); }		//Закрытие окна
	};

//------------------------------------------------------------------------------

	//Считывает все значения из файла в вектор vo переданный по ссылке (push_back)
	void read_file(const string& file_name, vector<Order>& vo);

	//Сравнение введённого пользователем с заказом переданным в качестве первого аргумента
	bool cmp_request(const Order& o, const string& n, const string& d, const string& a, const string& g);

}