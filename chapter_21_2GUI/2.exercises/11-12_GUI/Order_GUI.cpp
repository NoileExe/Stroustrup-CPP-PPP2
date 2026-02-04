


#include "Order_GUI.h"


namespace Graph_lib
{

	Show_window::Show_window(const string& file_name,    Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  pprev_btn	{ Point{w-w/2-90,  h-60}, 80, 20,  "<-purchase",
						[](Address, Address pw) { reference_to<Show_window>(pw).pprev(); } },
		  pnext_btn	{ Point{w-w/2+10,  h-60}, 80, 20,  "purchase->",
						[](Address, Address pw) { reference_to<Show_window>(pw).pnext(); } },
		  oprev_btn	{ Point{w-w/2-125,  h-30}, 70, 20, "Prev order",
						[](Address, Address pw) { reference_to<Show_window>(pw).oprev(); } },
		  onext_btn	{ Point{w-w/2-35,  h-30}, 70, 20,  "Next order",
						[](Address, Address pw) { reference_to<Show_window>(pw).onext(); } },
		  quit_btn	{ Point{w-w/2+55,  h-30}, 70, 20,  "Close",
						[](Address, Address pw) { reference_to<Show_window>(pw).quit(); } },
		  
		  file    { Point{20, 30},	"File: " + file_name },
		  ocount  { Point{20, 60},	"Order #0 from 0" },
		  pcount  { Point{20, 90},	"Purchase #0 from 0" },
		  name    { Point{40, 130},	"Order: " },
		  date    { Point{40, 160},	"Date: " },
		  addr    { Point{40, 190},	"Address: " },
		  purchase{ Point{40, 220},	"Goods   Price  *  Count   Summary" }
	{
		read_file(file_name, vo);
		
		
		attach(pprev_btn);
		attach(pnext_btn);
		attach(oprev_btn);
		attach(onext_btn);
		attach(quit_btn);
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		ocount.set_color(Color::black);
		ocount.set_font(Graph_lib::Font::helvetica_bold);
		ocount.set_font_size(16);
		pcount.set_color(Color::black);
		pcount.set_font(Graph_lib::Font::helvetica_bold);
		pcount.set_font_size(16);
		name.set_color(Color::dark_blue);
		name.set_font(Graph_lib::Font::helvetica);
		name.set_font_size(16);
		date.set_color(Color::dark_blue);
		date.set_font(Graph_lib::Font::helvetica);
		date.set_font_size(16);
		addr.set_color(Color::dark_blue);
		addr.set_font(Graph_lib::Font::helvetica);
		addr.set_font_size(16);
		purchase.set_color(Color::dark_blue);
		purchase.set_font(Graph_lib::Font::helvetica);
		purchase.set_font_size(16);
		
		
		if( vo.size() ) {
			unsigned int curr_order {ocurr + 1};
			ocount.set_label( "Order #" + to_string(curr_order) + " from " + to_string(vo.size()) );
			
			name.set_label( "Order: " + vo[ocurr].name );
			
			ostringstream lbl {""};
			lbl << "Date: " << vo[ocurr].birthday;
			date.set_label( lbl.str() );
			
			addr.set_label( "Address: " + vo[ocurr].address );
			
			if( vo[ocurr].purchase.size() ) {
				pcount.set_label( "Purchase #" + to_string(curr_order) + " from " + to_string(vo[ocurr].purchase.size()) );
				
				lbl.str("");
				lbl.precision(2);
				lbl << fixed << vo[ocurr].purchase[pcurr] << " = " << vo[ocurr].purchase[pcurr].unit_price * vo[ocurr].purchase[pcurr].count;
				purchase.set_label( lbl.str() );
			}
		}
		
		
		attach(file);
		attach(ocount);
		attach(pcount);
		attach(name);
		attach(date);
		attach(addr);
		attach(purchase);
	}

	Show_window::Show_window(const vector<Order>& v,    Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  pprev_btn	{ Point{w-w/2-90,  h-60}, 80, 20,  "<-purchase",
						[](Address, Address pw) { reference_to<Show_window>(pw).pprev(); } },
		  pnext_btn	{ Point{w-w/2+10,  h-60}, 80, 20,  "purchase->",
						[](Address, Address pw) { reference_to<Show_window>(pw).pnext(); } },
		  oprev_btn	{ Point{w-w/2-125,  h-30}, 70, 20, "Prev order",
						[](Address, Address pw) { reference_to<Show_window>(pw).oprev(); } },
		  onext_btn	{ Point{w-w/2-35,  h-30}, 70, 20,  "Next order",
						[](Address, Address pw) { reference_to<Show_window>(pw).onext(); } },
		  quit_btn	{ Point{w-w/2+55,  h-30}, 70, 20,  "Close",
						[](Address, Address pw) { reference_to<Show_window>(pw).quit(); } },
		  
		  file    { Point{20, 30},	"File: ..." },
		  ocount  { Point{20, 60},	"Order #0 from 0" },
		  pcount  { Point{20, 90},	"Purchase #0 from 0" },
		  name    { Point{40, 130},	"Order: " },
		  date    { Point{40, 160},	"Date: " },
		  addr    { Point{40, 190},	"Address: " },
		  purchase{ Point{40, 220},	"Goods   Price  *  Count   Summary" }
	{
		vo = v;
		
		attach(pprev_btn);
		attach(pnext_btn);
		attach(oprev_btn);
		attach(onext_btn);
		attach(quit_btn);
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		ocount.set_color(Color::black);
		ocount.set_font(Graph_lib::Font::helvetica_bold);
		ocount.set_font_size(16);
		pcount.set_color(Color::black);
		pcount.set_font(Graph_lib::Font::helvetica_bold);
		pcount.set_font_size(16);
		name.set_color(Color::dark_blue);
		name.set_font(Graph_lib::Font::helvetica);
		name.set_font_size(16);
		date.set_color(Color::dark_blue);
		date.set_font(Graph_lib::Font::helvetica);
		date.set_font_size(16);
		addr.set_color(Color::dark_blue);
		addr.set_font(Graph_lib::Font::helvetica);
		addr.set_font_size(16);
		purchase.set_color(Color::dark_blue);
		purchase.set_font(Graph_lib::Font::helvetica);
		purchase.set_font_size(16);
		
		
		if( vo.size() ) {
			unsigned int curr_order {ocurr + 1};
			ocount.set_label( "Order #" + to_string(curr_order) + " from " + to_string(vo.size()) );
			
			name.set_label( "Order: " + vo[ocurr].name );
			
			ostringstream lbl {""};
			lbl << "Date: " << vo[ocurr].birthday;
			date.set_label( lbl.str() );
			
			addr.set_label( "Address: " + vo[ocurr].address );
			
			if( vo[ocurr].purchase.size() ) {
				pcount.set_label( "Purchase #" + to_string(curr_order) + " from " + to_string(vo[ocurr].purchase.size()) );
				
				lbl.str("");
				lbl.precision(2);
				lbl << fixed << vo[ocurr].purchase[pcurr] << " = " << vo[ocurr].purchase[pcurr].unit_price * vo[ocurr].purchase[pcurr].count;
				purchase.set_label( lbl.str() );
			}
		}
		
		
		attach(file);
		attach(ocount);
		attach(pcount);
		attach(name);
		attach(date);
		attach(addr);
		attach(purchase);
	}

	//Предыдущий заказ
	void Show_window::oprev()
	{
		if( vo.size()  &&  ocurr ) {
			--ocurr;
			pcurr = 0;
			
			unsigned int curr_order {ocurr + 1};
			ocount.set_label( "Order #" + to_string(curr_order) + " from " + to_string(vo.size()) );
			
			name.set_label( "Order: " + vo[ocurr].name );
			
			ostringstream lbl {""};
			lbl << "Date: " << vo[ocurr].birthday;
			date.set_label( lbl.str() );
			
			addr.set_label( "Address: " + vo[ocurr].address );
			
			if( vo[ocurr].purchase.size() ) {
				pcount.set_label( "Purchase #" + to_string(pcurr+1) + " from " + to_string(vo[ocurr].purchase.size()) );
				
				lbl.str("");
				lbl.precision(2);
				lbl << fixed << vo[ocurr].purchase[pcurr] << "   = " << vo[ocurr].purchase[pcurr].unit_price * vo[ocurr].purchase[pcurr].count;
				purchase.set_label( lbl.str() );
			} else {
				pcount.set_label( "Purchase #0 from 0" );
				purchase.set_label( "Goods   Price  *  Count   Summary" );
			}
			
			redraw();
		}
	}

	//Следующий заказ
	void Show_window::onext()
	{
		if( vo.size()  &&  ocurr != vo.size()-1 ) {
			++ocurr;
			pcurr = 0;
			
			unsigned int curr_order {ocurr + 1};
			ocount.set_label( "Order #" + to_string(curr_order) + " from " + to_string(vo.size()) );
			
			name.set_label( "Order: " + vo[ocurr].name );
			
			ostringstream lbl {""};
			lbl << "Date: " << vo[ocurr].birthday;
			date.set_label( lbl.str() );
			
			addr.set_label( "Address: " + vo[ocurr].address );
			
			if( vo[ocurr].purchase.size() ) {
				pcount.set_label( "Purchase #" + to_string(pcurr+1) + " from " + to_string(vo[ocurr].purchase.size()) );
				
				lbl.str("");
				lbl.precision(2);
				lbl << fixed << vo[ocurr].purchase[pcurr] << "   = " << vo[ocurr].purchase[pcurr].unit_price * vo[ocurr].purchase[pcurr].count;
				purchase.set_label( lbl.str() );
			} else {
				pcount.set_label( "Purchase #0 from 0" );
				purchase.set_label( "     Goods   Price  *  Count   Summary" );
			}
			
			redraw();
		}
	}

	//Предыдущая позиция в чеке
	void Show_window::pprev()
	{
		if( vo.size()  &&  vo[ocurr].purchase.size()  &&  pcurr ) {
			--pcurr;
			
			pcount.set_label( "Purchase #" + to_string(pcurr+1) + " from " + to_string(vo[ocurr].purchase.size()) );
			
			ostringstream lbl {""};
			lbl.precision(2);
			lbl << fixed << vo[ocurr].purchase[pcurr] << "   = " << vo[ocurr].purchase[pcurr].unit_price * vo[ocurr].purchase[pcurr].count;
			purchase.set_label( lbl.str() );
			
			redraw();
		}
	}

	//Следующая позиция в чеке
	void Show_window::pnext()
	{
		if( vo.size()  &&  vo[ocurr].purchase.size()  &&  pcurr != vo[ocurr].purchase.size()-1 ) {
			++pcurr;
			
			pcount.set_label( "Purchase #" + to_string(pcurr+1) + " from " + to_string(vo[ocurr].purchase.size()) );
			
			ostringstream lbl {""};
			lbl.precision(2);
			lbl << fixed << vo[ocurr].purchase[pcurr] << "   = " << vo[ocurr].purchase[pcurr].unit_price * vo[ocurr].purchase[pcurr].count;
			purchase.set_label( lbl.str() );
			
			redraw();
		}
	}

//------------------------------------------------------------------------------

	Sort_window::Sort_window(const string& file_name,    Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  sort_btn { Point{w-w/2-80,  h-30}, 70, 20,  "Sort",
						[](Address, Address pw) { reference_to<Sort_window>(pw).sortit(); } },
		  quit_btn { Point{w-w/2+10,  h-30}, 70, 20,  "Close",
						[](Address, Address pw) { reference_to<Sort_window>(pw).quit(); } },
		  
		  menu_btn { Point{200, 60}, 120, 20,  "Order name",
						[](Address, Address pw) { reference_to<Sort_window>(pw).show_menu(); } },
		  sort_menu {Point{200, 60}, 120, 20, Menu::vertical, "Sort method"},
		  
		  tofile {  Point{160, 90}, 240, 20, "Output file path/name" },
		  
		  file   { Point{20, 30},	"File: " + file_name },
		  sortby { Point{20, 75},	"Sort by (click menu->)" }
	{
		read_file(file_name, vo);
		
		attach(sort_btn);
		attach(quit_btn);
		
		sort_menu.attach(new Button { Point{0,0},0,0, "Order name",
							[](Address, Address pw) { reference_to<Sort_window>(pw).set_sort("Order name"); } });
		sort_menu.attach(new Button { Point{0,0},0,0, "Date",
							[](Address, Address pw) { reference_to<Sort_window>(pw).set_sort("Date"); } });
		sort_menu.attach(new Button { Point{0,0},0,0, "Address",
							[](Address, Address pw) { reference_to<Sort_window>(pw).set_sort("Address"); } });
		sort_menu.attach(new Button { Point{0,0},0,0, "Order summary",
							[](Address, Address pw) { reference_to<Sort_window>(pw).set_sort("Order summary"); } });
		
		attach(tofile);
		attach(sort_menu);
		attach(menu_btn);
		sort_menu.hide();
		
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		sortby.set_color(Color::black);
		sortby.set_font(Graph_lib::Font::helvetica_bold);
		sortby.set_font_size(16);
		
		attach(file);
		attach(sortby);
	}

	//Изменение фактора сортировки
	void Sort_window::set_sort(const string& st)
	{
		hide_menu();
		menu_btn.label = st;
		redraw();
	}

	void Sort_window::sortit()
	{
		if( vo.size() )
		{
			if(menu_btn.label == "Order name")
				sort( vo.begin(), vo.end(), Order_by_name() );
			
			else if(menu_btn.label == "Date")
				sort( vo.begin(), vo.end(), Order_by_birthday() );
			
			else if(menu_btn.label == "Address")
				sort( vo.begin(), vo.end(), Order_by_address() );
			
			else if(menu_btn.label == "Order summary")
				sort( vo.begin(), vo.end(), Order_by_purchase() );
			
			else	error("bad sort type (" + menu_btn.label + ") [Sort_window::sortit()]");
			
			
			string output_file { tofile.get_string() };
			ofstream ofs {output_file};
			
			if( output_file != ""  &&  ofs )
				for(auto& p : vo)		ofs << p;
			else
				{ Show_window win {vo};		gui_main(); }
			
			redraw();
		}
	}

//------------------------------------------------------------------------------

	Add_window::Add_window(const string& fn,    Point xy, int w, int h, const string& title)
		: file_name{fn},
		  Window{xy,w,h,title},
		  add_order_btn { Point{w-w/2-145,  h-30}, 70, 20,  "Add order",
							[](Address, Address pw) { reference_to<Add_window>(pw).add_order(); } },
		  add_purch_btn { Point{w-w/2-55,   h-30}, 110, 20,  "Add purchase" /*to order"*/,
							[](Address, Address pw) { reference_to<Add_window>(pw).add_purch(); } },
		  quit_btn      { Point{w-w/2+75,   h-30},  70, 20,  "Close",
							[](Address, Address pw) { reference_to<Add_window>(pw).quit(); } },
		  
		  file   { Point{20, 30},	"File: " + file_name },
		  name  { Point{160, 60},  400, 20, "Order num/name: " },
		  date  { Point{160, 90},  400, 20, "Date: " },
		  addr  { Point{160, 120}, 400, 20, "Address: " },
		  goods { Point{160, 150}, 400, 20, "Goods name: " },
		  price { Point{160, 180}, 160, 20, "Price: " },
		  count { Point{400, 180}, 160, 20, "Count: " },
		  result { Point{20, 230},	"Result: ..." }
	{
		read_file(file_name, vo);
		
		attach(add_order_btn);
		attach(add_purch_btn);
		attach(quit_btn);
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		result.set_color(Color::black);
		result.set_font(Graph_lib::Font::helvetica);
		result.set_font_size(16);
		
		attach(file);
		attach(result);
		
		attach(name);
		attach(date);
		attach(addr);
		attach(goods);
		attach(price);
		attach(count);
	}

	//Добавление заказа
	void Add_window::add_order()
	{
		result.set_label( "Result: ..." );
		
		
		string n = name.get_string();	//Order num/name
		string d = date.get_string();	//Date
		string a = addr.get_string();	//Address
		string g = goods.get_string();	//Goods name
		string p = price.get_string();	//Price
		string c = count.get_string();	//Count
		
		//Проверка параметров
		if( n == ""  ||  d == ""  ||  a == ""  ||  g == ""  ||  p == ""  ||  c == "" )
		{
			string tmp = "Result: empty field(s):"; 
			
			if(n == "")		tmp += " Order num/name";
			if(d == "")		tmp += " Date";
			if(a == "")		tmp += " Address";
			if(g == "")		tmp += " Goods name";
			if(p == "")		tmp += " Price";
			if(c == "")		tmp += " Count";
			
			result.set_label( tmp );
			redraw();
			return;
		}
		
		
		
		Chrono::Date od;
		double prc {0.0};
		
		try {
			istringstream iss {d};
			iss >> od;		//Проверка правильности ввода даты
			
			iss.clear();
			iss.str(p);
			iss >> prc;
			
			if(!iss)		error("bad input");
		}
		
		catch(exception& e)		{ result.set_label( "Result: " + std::string(e.what()) );		redraw();		return; }
		catch(...)				{ result.set_label( "Result: unknown error" );					redraw();		return; }
		
		int cnt = count.get_int();
		
		if(prc < 0  ||  cnt < 0) {
			result.set_label( "Result: negative value" );
			redraw();
			return;
		}
		
		
		//--------------------------------------------------------------------------
		
		//Проверка того что в файле ещё нет такого заказа (имя, дата и адрес)
		for(auto& o : vo)
			if( o.name == n  &&  o.birthday == od  &&  o.address == a )
			{
				auto it = find_if( o.purchase.begin(), o.purchase.end(), [&](const Purchase& pur) { return pur.name == g; } );
				
				if( it == o.purchase.end() )
					result.set_label( "Result: there is already such an order, but it does not contain the specified item" );
				
				else if( it != o.purchase.end()  &&  it->unit_price == prc  &&  it->count == cnt )
					result.set_label( "Result: in the file, such an order with such a position already exists" );
				
				else if( it != o.purchase.end()  &&  it->unit_price == prc )
					result.set_label( "Result: already exists such an order with such a price, but another count" );
				
				else
					result.set_label( "Result: such order already exists in the file" );
				
				redraw();
				return;
			}
		
		//--------------------------------------------------------------------------
		
		vector<Purchase> purchase { Purchase(g, prc, cnt) };
		
		Order o {n, a, od, purchase};
		vo.push_back( o );
		
		ofstream ofs {file_name, ios_base::app};
		ofs << "\n" << o;
		
		result.set_label( "Result: successfully added (" + n + ")" );
		redraw();
	}

	//Добавление позиции в заказ
	void Add_window::add_purch()
	{
		result.set_label( "Result: ..." );
		
		
		string n = name.get_string();	//Order num/name
		string d = date.get_string();	//Date
		string a = addr.get_string();	//Address
		string g = goods.get_string();	//Goods name
		string p = price.get_string();	//Price
		string c = count.get_string();	//Count
		
		//Проверка параметров
		if( n == ""  ||  d == ""  ||  a == ""  ||  g == ""  ||  p == ""  ||  c == "" )
		{
			string tmp = "Result: empty field(s):"; 
			
			if(n == "")		tmp += " Order num/name";
			if(d == "")		tmp += " Date";
			if(a == "")		tmp += " Address";
			if(g == "")		tmp += " Goods name";
			if(p == "")		tmp += " Price";
			if(c == "")		tmp += " Count";
			
			result.set_label( tmp );
			redraw();
			return;
		}
		
		
		Chrono::Date od;
		double prc {0.0};
		
		try {
			istringstream iss {d};
			iss >> od;		//Проверка правильности ввода даты
			
			iss.clear();
			iss.str(p);
			iss >> prc;
			
			if(!iss)		error("bad input");
		}
		
		catch(exception& e)		{ result.set_label( "Result: " + std::string(e.what()) );		redraw();		return; }
		catch(...)				{ result.set_label( "Result: unknown error" );					redraw();		return; }
		
		
		int cnt = count.get_int();
		
		if(prc < 0  ||  cnt < 0) {
			result.set_label( "Result: negative value" );
			redraw();
			return;
		}
		
		//--------------------------------------------------------------------------
		
		//Проверка есть ли уже в файле такой заказ
		for(auto& o : vo)
		{
			
			if( cmp_request(o, n, d, a, g) )
			{
				auto it = find_if( o.purchase.begin(), o.purchase.end(), [&](const Purchase& pur) { return pur.name == g; } );
				
				//Найдена позиция с такой же ценой - просто прибавляем кол-во товара
				//Иначе далее просто будет создана новая позиция по новой цене
				if( it->unit_price == prc ) {
					it->count += cnt;
					result.set_label( "Result: successfully added quantity (" + g + " * " + to_string(it->count) + ")" );
					break;
				}
			}
			
			//Позиция не была ранее добавлена, но найден заказ с таким именем
			if( result.label() == "Result: ..."  &&  o.name == n ) {
				Purchase purch {g, prc, cnt};
				o.purchase.push_back(purch);
				int qnt = o.purchase[o.purchase.size()-1].count;
				result.set_label( "Result: successfully added (" + g + " * " + to_string(qnt) + ")" );
				break;
			}
			
		}
		
		//--------------------------------------------------------------------------
		
		//Заказ по указанным данным не был найден
		if( result.label() == "Result: ..." )		result.set_label( "Result: no order was found for the specified data. Item not added" );
		else										{ ofstream ofs {file_name};		for(auto& o : vo)	ofs << o; }
		
		
		redraw();
	}

//------------------------------------------------------------------------------

	Summ_window::Summ_window(const string& file_name,    Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  quit_btn	 { Point{w-w/2-35,  h-30}, 70, 20,   "Close",
						[](Address, Address pw) { reference_to<Summ_window>(pw).quit(); } },
		  
		  file   { Point{20, 30},	"File: " + file_name },
		  count  { Point{20, 60},	"Orders count: " },
		  greater{ Point{20, 90},	"Most expensive: " },
		  lower  { Point{20, 120},	"Cheapest: " },
		  summ   { Point{20, 150},	"Total cost (summary): " }
	{
		read_file(file_name, vo);
		
		
		attach(quit_btn);
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		count.set_color(Color::black);
		count.set_font(Graph_lib::Font::helvetica_bold);
		count.set_font_size(16);
		greater.set_color(Color::black);
		greater.set_font(Graph_lib::Font::helvetica);
		greater.set_font_size(16);
		lower.set_color(Color::black);
		lower.set_font(Graph_lib::Font::helvetica);
		lower.set_font_size(16);
		summ.set_color(Color::black);
		summ.set_font(Graph_lib::Font::helvetica_bold);
		summ.set_font_size(16);
		
		
		Order omax = vo[0];
		Order omin = vo[0];
		double pmax = accumulate(vo[0].purchase.begin(), vo[0].purchase.end(), 0.0,  [](double& v, const Purchase& p) { return v + p.unit_price * p.count; });
		double pmin {pmax};
		
		double summary {0.0};
		
		for(Order& o : vo) {
			double tmp = accumulate(o.purchase.begin(), o.purchase.end(), 0.0,  [](double& v, const Purchase& p) { return v + p.unit_price * p.count; });
			summary += tmp;
			if( pmax < tmp )		{ omax = o;		pmax = tmp; }
			if( pmin > tmp )		{ omin = o;		pmin = tmp; }
			
			//Тоже рабочие варианты, но более запутанные
			//if( Order_by_purchase{}.operator()(omax, o) )		omax = o;
			//if( Order_by_purchase{}.operator()(o, omin) )		omin = o;
		}
		
		count.set_label( "Orders count: "		 + to_string(vo.size()) );
		
		ostringstream lbl {""};
		lbl.precision(2);
		lbl << fixed << omax.name << "   " << pmax;
		greater.set_label( "Most expensive: "	+ lbl.str() );
		
		lbl.str("");
		lbl << omin.name << "   " << pmin;
		lower.set_label( "Cheapest: "			 + lbl.str() );
		
		lbl.str("");
		lbl << summary;
		summ.set_label( "Total cost (summary): " + lbl.str() );
		
		attach(file);
		attach(count);
		attach(greater);
		attach(lower);
		attach(summ);
	}

//------------------------------------------------------------------------------

	Search_window::Search_window(const string& file_name,    Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  search_btn { Point{w-w/2-80,  h-30}, 70, 20,  "Search",
						[](Address, Address pw) { reference_to<Search_window>(pw).search(); } },
		  quit_btn   { Point{w-w/2+10,  h-30}, 70, 20,  "Close",
						[](Address, Address pw) { reference_to<Search_window>(pw).quit(); } },
		  
		  file   { Point{20, 30},	"File: " + file_name },
		  name  { Point{160, 60}, 240, 20, "Order num/name: " },
		  date  { Point{160, 90}, 240, 20, "Date: " },
		  addr  { Point{160, 120}, 240, 20, "Address: " },
		  goods { Point{160, 150}, 240, 20, "Goods name: " },
		  result { Point{20, 200},	"Result: ..." }
	{
		read_file(file_name, vo);
		
		attach(search_btn);
		attach(quit_btn);
		
		file.set_color(Color::black);
		file.set_font(Graph_lib::Font::helvetica_bold);
		file.set_font_size(16);
		result.set_color(Color::black);
		result.set_font(Graph_lib::Font::helvetica_bold);
		result.set_font_size(16);
		
		attach(file);
		attach(result);
		
		attach(name);
		attach(date);
		attach(addr);
		attach(goods);
	}

	//Процедура поиска
	void Search_window::search()
	{
		result.set_label( "Result: ..." );
		
		string n = name.get_string();
		string d = date.get_string();
		string a = addr.get_string();
		string g = goods.get_string();
		
		found.clear();
		
		//Сравнение введённого пользователем с заказом переданным в качестве первого аргумента
		for(auto& o : vo)
			if( cmp_request(o, n, d, a, g) )		found.push_back(o);
		
		if( found.size() ) {
			result.set_label( "Result: found " + to_string(found.size()) + " item(s)" );
			redraw();
			Show_window win {found};
			gui_main();
		}
		
		else	result.set_label( "Result: found 0 item(s)" );
		
		redraw();
	}

//------------------------------------------------------------------------------

	//Считывает все значения из файла в вектор vo переданный по ссылке (push_back)
	void read_file(const string& file_name, vector<Order>& vo)
	try {
		fstream fs {file_name, fstream::in};	//Открываем поток ввода
		if (!fs)	error("Unable to open file '" + file_name + "'");
		fs.exceptions(fs.exceptions() | ios_base::badbit);
		
		for(Order o = Order{};   fs >> o;   )		vo.push_back(o);
	}
	catch (exception& e)		{ cerr << "Error [read_file(" << file_name << ", vector<Order>&)]: " << e.what() << '\n'; }
	catch (...)					{ cerr << "Oops! Problems in [read_file(" << file_name << ", vector<Order>&)]\n"; }

	//Сравнение введённого пользователем с заказом переданным в качестве первого аргумента
	bool cmp_request(const Order& o, const string& n, const string& d, const string& a, const string& g)
	{
		bool res {false};
		
		if( n == "" )				res = true;
		else if( n == o.name )		res = true;
		else						return false;
		
		if( d == "" )				res = true;
		else {
			try {
				istringstream dd {d};
				Chrono::Date date;
				dd >> date;
			
				if( date == o.birthday )		res = true;
				else							return false;
			}
			catch (...)		{  }
		}
		
		if( a == "" )				res = true;
		else if( a == o.address )	res = true;
		else						return false;
		
		if( g == "" )				res = true;
		else {
			res = false;
			for(auto& p : o.purchase)
				if( g == p.name )		{ res = true;		break; }
		}
		
		return res;
	}

}