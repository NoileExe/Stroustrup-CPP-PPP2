

#include <ctime>		//Для рандомизации по текущему времени (секунде)
#include <chrono>
#include <addition.h>	//Включает Simple_window.h, который включает Gui.h, который в свою очередь включает Graph.h и Window.h и Point.h и std_lib_facilities.h



namespace Graph_lib {
	struct Room {
		int num{0};				//Номер комнаты
		bool pit{false};		//Наличие пропасти
		bool bat{false};		//Наличие летучих мышей
		bool visited{false};	//Посещалась ли комната
		
		Room* room1{nullptr};	//Переходы в соседние комнаты
		Room* room2{nullptr};
		Room* room3{nullptr};
	};
	
	struct Player {
		int arrows{0};			//Количество стрел
		Room* loc{nullptr};		//Местоположение игрока/монстра
	};
	
	
	struct Wumpus_GUI : Window {
		Wumpus_GUI(Point xy = win_centering(800,600), int w = 800, int h = 600, const string& title = "Охота на Вампуса!");
		~Wumpus_GUI() {
			for(auto b : map_btns)				delete b;
			for(int i=0; i<cave.size(); ++i)	delete cave[i];
		}
		
	private:
		//Реализация игры:
		void generate_cave();				//Создание случайной пещеры отталкиваясь от размера вектора
		void play(char ch);					//Собственно сама игра (на вход действие: m - движение, s - выстрел)
		void plr_relocate();				//Перемещение игрока в случайную позицию в лабиринте
		void wump_relocate();				//Перемещение Вампуса в случайную позицию в лабиринте
		
		int is_vacancy(Room* r);				//Проверка есть ли комнаты со свободным входом/выходом [вспомогательная ф-ция для generate_cave()]
		bool is_neighbor(Room* a, Room* b);		//Проверка являются ли комнаты соседями [вспомогательная ф-ция для generate_cave()]
		bool is_full(Room* r);					//Проверка заняты ли все входы/выходы у комнаты 'r' [вспомогательная ф-ция для generate_cave()]
		
		void look_around();					//Вывод описания окружения
		bool move();						//Если пользователь решил совершить движение используется данная ф-ция
		Room* shoot();						//Если пользователь решил совершить выстрел из лука используется данная ф-ция
		void wump_turn();					//Ход Вампуса
		
		int randnum(int n);					//Остаток от деления на n
		Room* randroom(Room* r);			//Перемещение в одну из 4 случайных комнат (текущая либо 3 соседних)
		
		void map_cheat(Room* r);			//Вывод соседних комнат рядом с указанной комнатой (комната где находится игрок)
		void full_map_cheat();				//Вывод полной карты: все комнаты посещены и их статус известен (отображается на кнопках)
		
		
		//Данные:
		int min_rooms_count {10};	//Минимальное кол-во комнат в лабиринте
		int max_rooms_count {45};	//Максимальное кол-во комнат в лабиринте
		
		vector<Room*> cave;		//Пещера состоит из комнат
		Player plr;
		Player wump;
		Player gmap;
		
		
		//Виджеты:
		Button newgame_btn;		//Генерирует новую пещеру с новым кол-вом комнат
		Button quit_btn;		//Завершает работу программы
		
		Text arrows_out;		//Кол-во оставшихся стрел
		Text curr_room_out;		//Описание текущей комнаты (Номер и куда ведут тоннели)
		Text room1_out;			//Описание соседних комнат (если хоть в одной соседней мыши, яма или Вампус)
		Text room2_out;
		Text room3_out;
		Text msg_out;			//Сообщения о результате действия
		
		Button move_btn;		//Кнопка "Идти". Перемещение игрока
		Button shoot_btn;		//Кнопка "Стрелять". Выстрел стрелой с заданным маршрутом
		In_box route_in;		//Переход в комнату или маршрут стрелы
		
		vector<Button*> map_btns;	//Карта каждой комнаты (кнопки)
		
		Text stat_out;			//Статус комнаты при просмотре карты
		Text mark_out;			//Отметки для комнаты (скрыты если комната посещена)
		
		Button null_btn;		//Кнопка отметки "     Ничего     "
		Button bats_btn;		//Кнопка отметки "Летучие мыши (b)"
		Button pits_btn;		//Кнопка отметки "  Пропасть (p)  "
		Button wump_btn;		//Кнопка отметки "   Вампус (W)   "
		
		TXTBox room_up;
		TXTBox room_center;
		TXTBox room_left;
		TXTBox room_right;
		
		
		void pls_wait();
		void new_game();			//Генерирует новую карту
		void draw_map(int n);		//Отображает карту для текущей или выбранной по нажатию кнопки комнаты
		void set_mark(string s);	//Делает пометку отображаемой НЕПОСЕЩЁННОЙ комнаты (по номеру, который указан в центральном квадрате карты)
		void quit() { hide();	exit(0); }
	};
	
	
//-------------------------------------------------------------------------------------------------------------------------------------------------
	
	
	Wumpus_GUI::Wumpus_GUI(Point xy, int w, int h, const string& title)
		: Window{xy,w,h,title},
		  newgame_btn{ Point{w-150, 0}, 70, 20, "New game",
						[](Address, Address pw) { reference_to<Wumpus_GUI>(pw).new_game(); } },
		  quit_btn	 { Point{w-70,  0}, 70, 20,   "Quit",
						[](Address, Address pw) { reference_to<Wumpus_GUI>(pw).quit(); } },
		  
		  arrows_out{ Point{20, 30},	"Изучая пещеры убейте выстрелом монстра Вампуса, указав маршрут полёта" },
		  curr_room_out{ Point{20, 70},	"волшебной стрелы через 1-3 комнаты (при ошибке может попасть в игрока)." },
		  room1_out{ Point{20, 100},	"Избегайте смертоносных бездонных ям (от них веет сквозняком) и огромных летучих мышей, способных" },
		  room2_out{ Point{20, 130},	"поднять и унести даже человека, а так же не попадитесь в лапы Вампуса (может проснуться от звука " },
		  room3_out{ Point{20, 160},	"стрелы и найти вас). Нажмите кнопку 'New Game' для начала новой игры." },
		  msg_out  { Point{20, 200},	"Удачной охоты!" },
		  
		  move_btn	 { Point{w-w/2-80, 230}, 70, 20,   "Идти",
						[](Address, Address pw) { reference_to<Wumpus_GUI>(pw).play('m'); } },
		  shoot_btn	 { Point{w-w/2+10, 230}, 70, 20, "Стрелять",
						[](Address, Address pw) { reference_to<Wumpus_GUI>(pw).play('s'); } },
		  route_in{ Point{w-w/2-80, 260}, 160, 20, "Номера комнат" },
		  
		  stat_out{ Point{w-w/2-120, 330},	"Комната #...   Статус: ..." },
		  mark_out{ Point{w-115, 390},		"Отметки" },
		  
		  null_btn	 { Point{w-160, 400}, 150, 20,      "Ничего",
						[](Address, Address pw) { reference_to<Wumpus_GUI>(pw).set_mark("Ничего"); } },
		  bats_btn	 { Point{w-160, 420}, 150, 20, "Летучие мыши (b)",
						[](Address, Address pw) { reference_to<Wumpus_GUI>(pw).set_mark("Летучие мыши (b)"); } },
		  pits_btn	 { Point{w-160, 440}, 150, 20,   "Пропасть (p)",
						[](Address, Address pw) { reference_to<Wumpus_GUI>(pw).set_mark("Пропасть (p)"); } },
		  wump_btn	 { Point{w-160, 460}, 150, 20,    "Вампус (W)",
						[](Address, Address pw) { reference_to<Wumpus_GUI>(pw).set_mark("Вампус (W)"); } },
						
		  room_up		{ Point{w-w/2-25,  400}, 40, 25, "  X" },
		  room_center	{ Point{w-w/2-25,  470}, 40, 25, "  X" },
		  room_left		{ Point{w-w/2-125, 470}, 40, 25, "  X" },
		  room_right	{ Point{w-w/2+80,  470}, 40, 25, "  X" }
	{
		//Такая очерёдность прикрепления виджетов к окну позволяет переключаться последовательно между элементами по нажатию TAB
		//Пробел активирует нажатие на выбранную кнопку
		attach(newgame_btn);
		attach(quit_btn);
		
		arrows_out.set_color(Color::black);
		arrows_out.set_font(Graph_lib::Font::helvetica_bold);
		arrows_out.set_font_size(16);
		curr_room_out.set_color(Color::black);
		curr_room_out.set_font(Graph_lib::Font::helvetica_bold);
		curr_room_out.set_font_size(16);
		room1_out.set_color(Color::black);
		room1_out.set_font(Graph_lib::Font::helvetica_bold);
		room2_out.set_color(Color::black);
		room2_out.set_font(Graph_lib::Font::helvetica_bold);
		room3_out.set_color(Color::black);
		room3_out.set_font(Graph_lib::Font::helvetica_bold);
		msg_out.set_color(Color::black);
		msg_out.set_font(Graph_lib::Font::helvetica_bold);
		msg_out.set_font_size(16);
		
		attach(arrows_out);
		attach(curr_room_out);
		attach(room1_out);
		attach(room2_out);
		attach(room3_out);
		attach(msg_out);
		
		attach(move_btn);
		attach(shoot_btn);
		attach(route_in);
		
		for(int i = 0; i<max_rooms_count; ++i) {
			int bx {20  + (i/15) * 50};
			int by {290 + (i%15) * 20};
			
			/*cout << "case " << i << ":" << endl
				 << "\tmap_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(" << i+1 << "); } });" << endl
				 << "\tbreak;" << endl << endl;*/
			
			switch(i) {
				case 0:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(1); } });
					break;
					
				case 1:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(2); } });
					break;

				case 2:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(3); } });
					break;

				case 3:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(4); } });
					break;

				case 4:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(5); } });
					break;

				case 5:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(6); } });
					break;

				case 6:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(7); } });
					break;

				case 7:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(8); } });
					break;

				case 8:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(9); } });
					break;

				case 9:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(10); } });
					break;

				case 10:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(11); } });
					break;

				case 11:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(12); } });
					break;

				case 12:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(13); } });
					break;

				case 13:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(14); } });
					break;

				case 14:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(15); } });
					break;

				case 15:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(16); } });
					break;

				case 16:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(17); } });
					break;

				case 17:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(18); } });
					break;

				case 18:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(19); } });
					break;

				case 19:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(20); } });
					break;

				case 20:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(21); } });
					break;

				case 21:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(22); } });
					break;

				case 22:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(23); } });
					break;

				case 23:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(24); } });
					break;

				case 24:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(25); } });
					break;

				case 25:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(26); } });
					break;

				case 26:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(27); } });
					break;

				case 27:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(28); } });
					break;

				case 28:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(29); } });
					break;

				case 29:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(30); } });
					break;

				case 30:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(31); } });
					break;

				case 31:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(32); } });
					break;

				case 32:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(33); } });
					break;

				case 33:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(34); } });
					break;

				case 34:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(35); } });
					break;

				case 35:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(36); } });
					break;

				case 36:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(37); } });
					break;

				case 37:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(38); } });
					break;

				case 38:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(39); } });
					break;

				case 39:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(40); } });
					break;

				case 40:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(41); } });
					break;

				case 41:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(42); } });
					break;

				case 42:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(43); } });
					break;

				case 43:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(44); } });
					break;

				case 44:
					map_btns.push_back(new Button { Point{bx,by}, 45, 20, to_string(i+1), [](Address, Address pw) { reference_to<Wumpus_GUI>(pw).draw_map(45); } });
					break;
			}
		}
		
		for(auto b : map_btns)		attach(*b);
		
		stat_out.set_color(Color::black);
		stat_out.set_font(Graph_lib::Font::helvetica_bold);
		stat_out.set_font_size(16);
		mark_out.set_color(Color::black);
		mark_out.set_font(Graph_lib::Font::helvetica_bold);
		
		attach(stat_out);
		attach(mark_out);
		
		attach(null_btn);
		attach(bats_btn);
		attach(pits_btn);
		attach(wump_btn);
		
		
		room_up.set_color(Color::black);
		room_center.set_color(Color::black);
		room_left.set_color(Color::black);
		room_right.set_color(Color::black);
		
		room_up.set_font(Graph_lib::Font::helvetica_bold);
		room_center.set_font(Graph_lib::Font::helvetica_bold);
		room_left.set_font(Graph_lib::Font::helvetica_bold);
		room_right.set_font(Graph_lib::Font::helvetica_bold);
		
		room_up.set_style( Line_style(Line_style::solid, 2) );
		room_center.set_style( Line_style(Line_style::solid, 2) );
		room_left.set_style( Line_style(Line_style::solid, 2) );
		room_right.set_style( Line_style(Line_style::solid, 2) );
		
		attach(room_up);
		attach(room_center);
		attach(room_left);
		attach(room_right);
	}
	
	
	void Wumpus_GUI::pls_wait() {
		/*detach(arrows_out);
		detach(curr_room_out);
		detach(room1_out);
		detach(room2_out);
		detach(room3_out);
		detach(msg_out);*/
		
		arrows_out.set_label("Пожалуйста, подождите. Происходит создание подземелья.");
		curr_room_out.set_label("");
		room1_out.set_label("");
		room2_out.set_label("");
		room3_out.set_label("");
		msg_out.set_label("");
		
		/*attach(arrows_out);
		attach(curr_room_out);
		attach(room1_out);
		attach(room2_out);
		attach(room3_out);
		attach(msg_out);*/
		
		redraw();
		
		null_btn.hide();
		bats_btn.hide();
		pits_btn.hide();
		wump_btn.hide();
		
		for(int i = 0; i < max_rooms_count; ++i)		{ map_btns[i]->label = to_string(i+1);	map_btns[i]->show(); }
		
		/*auto t0 = chrono::steady_clock::now();
		auto t1 = chrono::steady_clock::now() - t0;
		while(chrono::duration_cast<chrono::seconds>(t1).count() < 2)	{ t1 = chrono::steady_clock::now() - t0; }*/
		
		redraw();
	}
	
	void Wumpus_GUI::new_game() {
		pls_wait();
		
		for(int i=0; i < cave.size(); ++i)				if(cave[i])		delete cave[i];
		cave.clear();	//Очищаем вектор
		
		//Новое кол-во комнат
		int cnt{ 0 };
		while(cnt < min_rooms_count)		cnt = randnum(max_rooms_count);
		
		for(int i=0; i < cnt; ++i)						cave.push_back(new Room);	//Заполнение вектора пустыми комнатами
		for(int i = cnt; i < max_rooms_count; ++i)		map_btns[i]->hide();		//Скрыть неиспользуемые комнаты
		
		generate_cave();
		cout << cnt << " rooms" << endl;
		plr.arrows = 5;
		look_around();		//Описание окружения
		msg_out.set_label("Что Вы будете делать?");
		
		plr.loc->visited = true;
		map_btns[plr.loc->num - 1]->label = "}" + to_string(plr.loc->num) + "{";
		draw_map(plr.loc->num);
		
		redraw();
	}
	
	
	//Отображает карту для текущей или выбранной по нажатию кнопки комнаты, переносит текст с кнопок и если комната посещена - помечает цветом фона
	//На вход номер комнаты (т.к. кнопка не хранит ссылку на комнату)
	void Wumpus_GUI::draw_map(int n) {
		//if(plr.arrows == 0)		return; //Если игра была окончена - не даём нарисовать карту
		if(cave.size() == 0)		return; //Если игра не была начата - не даём нарисовать карту
		if(n > cave.size())			error("bad room number [draw_map(int)] (" + to_string(n) + ")");
		
		gmap.loc = cave[n-1];
		string stat {"Комната #" + to_string(gmap.loc->num) + "   Статус: "};
		
		room_center.set_label( map_btns[gmap.loc->num - 1]->label );
		
		if(gmap.loc->visited) {
			null_btn.hide();
			bats_btn.hide();
			pits_btn.hide();
			wump_btn.hide();
			
			if(gmap.loc->pit)			stat += "пропасть ";
			if(gmap.loc->bat)			stat += "мыши ";
			if(gmap.loc == wump.loc)	stat += "Вампус ";
			
			stat += "посещена";
			
			room_up.set_label   ( (gmap.loc->room1)  ?  map_btns[gmap.loc->room1->num - 1]->label : "  X");
			room_left.set_label ( (gmap.loc->room2)  ?  map_btns[gmap.loc->room2->num - 1]->label : "  X");
			room_right.set_label( (gmap.loc->room3)  ?  map_btns[gmap.loc->room3->num - 1]->label : "  X");
			
			if(gmap.loc->bat)								room_center.set_fill_color( Color(Color::yellow, Color::visible) );
			if(gmap.loc->pit  ||  gmap.loc == wump.loc)		room_center.set_fill_color( Color(Color::red, Color::visible) );
			if(!gmap.loc->pit  &&  !gmap.loc->bat  &&  gmap.loc != wump.loc)
															room_center.set_fill_color( Color(Color::green, Color::visible) );
			
			if(gmap.loc->room1  &&  gmap.loc->room1->visited) {
				if(gmap.loc->room1->bat)										room_up.set_fill_color( Color(Color::yellow, Color::visible) );
				if(gmap.loc->room1->pit  ||  gmap.loc->room1 == wump.loc)		room_up.set_fill_color( Color(Color::red, Color::visible) );
				if(!gmap.loc->room1->pit  &&  !gmap.loc->room1->bat  &&  gmap.loc->room1 != wump.loc)
																				room_up.set_fill_color( Color(Color::green, Color::visible) );
			}
			else	room_up.set_fill_color( Color(Color::white, Color::invisible) );
			
			if(gmap.loc->room2  &&  gmap.loc->room2->visited) {
				if(gmap.loc->room2->bat)										room_left.set_fill_color( Color(Color::yellow, Color::visible) );
				if(gmap.loc->room2->pit  ||  gmap.loc->room2 == wump.loc)		room_left.set_fill_color( Color(Color::red, Color::visible) );
				if(!gmap.loc->room2->pit  &&  !gmap.loc->room2->bat  &&  gmap.loc->room2 != wump.loc)
																				room_left.set_fill_color( Color(Color::green, Color::visible) );
			}
			else	room_left.set_fill_color( Color(Color::white, Color::invisible) );
			
			if(gmap.loc->room3  &&  gmap.loc->room3->visited) {
				if(gmap.loc->room3->bat)										room_right.set_fill_color( Color(Color::yellow, Color::visible) );
				if(gmap.loc->room3->pit  ||  gmap.loc->room3 == wump.loc)		room_right.set_fill_color( Color(Color::red, Color::visible) );
				if(!gmap.loc->room3->pit  &&  !gmap.loc->room3->bat  &&  gmap.loc->room3 != wump.loc)
																				room_right.set_fill_color( Color(Color::green, Color::visible) );
			}
			else	room_right.set_fill_color( Color(Color::white, Color::invisible) );
		}
		
		else {
			null_btn.show();
			bats_btn.show();
			pits_btn.show();
			wump_btn.show();
			
			stat += "не посещена";
			
			room_up.set_label   ( (gmap.loc->room1->visited)  ?  map_btns[gmap.loc->room1->num - 1]->label : "???" );
			room_left.set_label ( (gmap.loc->room2->visited)  ?  map_btns[gmap.loc->room2->num - 1]->label : "???" );
			room_right.set_label( (gmap.loc->room3->visited)  ?  map_btns[gmap.loc->room3->num - 1]->label : "???" );
			
			room_center.set_fill_color( Color(Color::white, Color::invisible) );
			
			if(gmap.loc->room1  &&  gmap.loc->room1->visited) {
				if(gmap.loc->room1->bat)										room_up.set_fill_color( Color(Color::yellow, Color::visible) );
				if(gmap.loc->room1->pit  ||  gmap.loc->room1 == wump.loc)		room_up.set_fill_color( Color(Color::red, Color::visible) );
				if(!gmap.loc->room1->pit  &&  !gmap.loc->room1->bat  &&  gmap.loc->room1 != wump.loc)
																				room_up.set_fill_color( Color(Color::green, Color::visible) );
			}
			else	room_up.set_fill_color( Color(Color::white, Color::invisible) );
			
			if(gmap.loc->room2  &&  gmap.loc->room2->visited) {
				if(gmap.loc->room2->bat)										room_left.set_fill_color( Color(Color::yellow, Color::visible) );
				if(gmap.loc->room2->pit  ||  gmap.loc->room2 == wump.loc)		room_left.set_fill_color( Color(Color::red, Color::visible) );
				if(!gmap.loc->room2->pit  &&  !gmap.loc->room2->bat  &&  gmap.loc->room2 != wump.loc)
																				room_left.set_fill_color( Color(Color::green, Color::visible) );
			}
			else	room_left.set_fill_color( Color(Color::white, Color::invisible) );
			
			if(gmap.loc->room3  &&  gmap.loc->room3->visited) {
				if(gmap.loc->room3->bat)										room_right.set_fill_color( Color(Color::yellow, Color::visible) );
				if(gmap.loc->room3->pit  ||  gmap.loc->room3 == wump.loc)		room_right.set_fill_color( Color(Color::red, Color::visible) );
				if(!gmap.loc->room3->pit  &&  !gmap.loc->room3->bat  &&  gmap.loc->room3 != wump.loc)
																				room_right.set_fill_color( Color(Color::green, Color::visible) );
			}
			else	room_right.set_fill_color( Color(Color::white, Color::invisible) );
		}
		
		stat_out.set_label(stat);
		redraw();
	}
	
	//Делает пометку отображаемой НЕПОСЕЩЁННОЙ комнаты (по номеру, который указан в центральном квадрате карты)
	//На вход пометка (текст с кнопки который позволяет определить какую пометку делать)
	void Wumpus_GUI::set_mark(string s) {
		if(cave.size() == 0)		return;		//Если игра ещё не начата и/или игрок проиграл
		if(gmap.loc->visited)		return;		//Если комната посещена не делаем никаких пометок (по идее и кнопки то для этого должны быть скрыты)
		
		
		if(s == "Ничего")				map_btns[gmap.loc->num-1]->label = to_string(gmap.loc->num);
		if(s == "Летучие мыши (b)")		map_btns[gmap.loc->num-1]->label = "b" + to_string(gmap.loc->num) + "b";
		if(s == "Пропасть (p)")			map_btns[gmap.loc->num-1]->label = "p" + to_string(gmap.loc->num) + "p";
		if(s == "Вампус (W)")			map_btns[gmap.loc->num-1]->label = "W" + to_string(gmap.loc->num) + "W";
		
		draw_map(gmap.loc->num);
	}
	
//-------------------------------------------------------------------------------------------------------------------------------------------------
	
	//Собственно сама игра
	//На вход действие: m - движение, s - выстрел
	//Выставляет количество стрел равное 0, если игрок умирает
	//Если кол-во стрел и так равно 0, то ничего не происходит (игрок должен начать новую игру)
	void Wumpus_GUI::play(char ch)
	{
		//Пустой боезапас - игра окончена или даже не начата
		if(plr.arrows == 0) {
			arrows_out.set_label("Изучая пещеры убейте выстрелом монстра Вампуса, указав маршрут полёта");
			curr_room_out.set_label("волшебной стрелы через 1-3 комнаты (при ошибке может попасть в игрока).");
			room1_out.set_label("Избегайте смертоносных бездонных ям (от них веет сквозняком) и огромных летучих мышей, способных");
			room2_out.set_label("поднять и унести даже человека, а так же не попадитесь в лапы Вампуса (может проснуться от звука ");
			room3_out.set_label("стрелы и найти вас). Нажмите кнопку 'New Game' для начала новой игры.");
			msg_out.set_label("НАЧНИТЕ НОВУЮ ИГРУ.");
			redraw();
			return;
		}
		
		
		msg_out.set_label("");
		
		if( route_in.get_string() == "" ) {
			if( ch == 'm' )		msg_out.set_label("ВВЕДИТЕ НОМЕР ОДНОЙ ИЗ СОСЕДНИХ КОМНАТ ДЛЯ ПЕРЕМЕЩЕНИЯ");
			if( ch == 's' )		msg_out.set_label("ВВЕДИТЕ МАРШРУТ СТРЕЛЫ (номера комнат в кол-ве от 1 до 3 разделённые пробелами)");
			redraw();
			return;
		}
		if( route_in.get_string() == "cheat1" ) {
			msg_out.set_label("ПРИМЕНЕН ЧИТ #1 (просмотр соседних с текущей комнат)");
			map_cheat(plr.loc);
			redraw();
			return;
		}
		if( route_in.get_string() == "cheat2" ) {
			msg_out.set_label("ПРИМЕНЕН ЧИТ #2 (узнать содержание всех комнат)");
			full_map_cheat();
			redraw();
			return;
		}
		
		//После перемещения игрок умер
		if( ch == 'm'  &&  !move() ) {
			plr.arrows = 0;
			full_map_cheat();	//Если игрок умер - даём ему возможность посмотреть всю карту
			redraw();
			return;
		}
		
		if( ch == 's' ) {
			Room* r{ shoot() };
			if(r) {
				string msg {"Стрелы: " + to_string(plr.arrows)};		//Сообщения для игрока
				arrows_out.set_label( msg );
				redraw();
				
				if(plr.loc == wump.loc)	//Встреча с Вампусом
				{
					curr_room_out.set_label("ВАМПУС ВХОДИТ В КОМНАТУ И ХВАТАЕТ ВАС. ВЫ СЪЕДЕНЫ");
					room1_out.set_label("");
					room2_out.set_label("");
					room3_out.set_label("");
					msg_out.set_label("ХА-ХА-ХА! ВЫ ПРОИГРАЛИ!");
					plr.arrows = 0;
					full_map_cheat();	//Если игрок умер - даём ему возможность посмотреть всю карту
					redraw();
					return; //return false;
				}
				
				if(r == plr.loc)		//Стрела попала в игрока
				{
					curr_room_out.set_label("СТРЕЛА ОТСКАКИВАЕТ И ПРОНЗАЕТ ВАС. ГЛУПАЯ СМЕРТЬ");
					room1_out.set_label("");
					room2_out.set_label("");
					room3_out.set_label("");
					msg_out.set_label("ХА-ХА-ХА! ВЫ ПРОИГРАЛИ!");
					plr.arrows = 0;
					full_map_cheat();	//Если игрок умер - даём ему возможность посмотреть всю карту
					redraw();
					return; //return false;
				}
				
				if(r == wump.loc)		//Стрела попала в Вампуса - ПОБЕДА!
				{
					curr_room_out.set_label("ВЫ СЛЫШИТЕ КРИКИ УМИРАЮЩЕГО МОНСТРА. ВАМПУС УБИТ В КОМНАТЕ #" + to_string(r->num));
					room1_out.set_label("");
					room2_out.set_label("");
					room3_out.set_label("");
					msg_out.set_label("ПОЗДРАВЛЯЕМ! ВЫ ПОБЕДИЛИ!");
					plr.arrows = 0;
					full_map_cheat();	//Если игрок победил - даём ему возможность посмотреть всю карту
					redraw();
					return; //return true;
				}
				
				if(plr.arrows == 0)		//Закончились стрелы
				{
					curr_room_out.set_label("ЗАКОНЧИЛИСЬ СТРЕЛЫ. ВЫ ОСТАЛИСЬ БЕЗОРУЖНЫ В ТЕМНОМ ЛАБИРИНТЕ ПЕЩЕР.");
					room1_out.set_label("");
					room2_out.set_label("");
					room3_out.set_label("");
					msg_out.set_label("ХА-ХА-ХА! ВЫ ПРОИГРАЛИ!");
					plr.arrows = 0;
					full_map_cheat();	//Если игрок умер - даём ему возможность посмотреть всю карту
					redraw();
					return; //return false;
				}
				
				msg_out.set_label("ГДЕ-ТО ВДАЛЕКЕ СТРЕЛА УПАЛА С ГЛУХИМ СТУКОМ");
			}
		}
		
		
		look_around();		//Описание окружения
	}

	//Вывод описания окружения
	void Wumpus_GUI::look_around()
	{
		arrows_out.set_label("");
		curr_room_out.set_label("");
		room1_out.set_label("");
		room2_out.set_label("");
		room3_out.set_label("");
		
		
		string msg {"Стрелы: " + to_string(plr.arrows)};		//Сообщения для игрока
		arrows_out.set_label( msg );
		
		msg = "Вы в комнате #" + to_string(plr.loc->num) + ". ТОННЕЛИ ОТСЮДА ВЕДУТ В ПЕЩЕРЫ ##   ";
		
		vector<int> r;
		if(plr.loc->room1)		r.push_back(plr.loc->room1->num);
		if(plr.loc->room2)		r.push_back(plr.loc->room2->num);
		if(plr.loc->room3)		r.push_back(plr.loc->room3->num);
		
		sort(r);
		for(int i : r)		msg += to_string(i) + "   ";
		
		curr_room_out.set_label( msg );
		msg = "";
		
		
		
		bool pb1{ (plr.loc->room1) ? plr.loc->room1->pit : false};
		bool pb2{ (plr.loc->room2) ? plr.loc->room2->pit : false};
		bool pb3{ (plr.loc->room3) ? plr.loc->room3->pit : false};
		
		if(pb1  ||  pb2  ||  pb3)		msg = "ВЫ ЧУВСТВУЕТЕ СКВОЗНЯК";
		
		if(room1_out.label() == ""  &&  msg != "")		{ room1_out.set_label(msg);		msg = ""; }
		if(room2_out.label() == ""  &&  msg != "")		{ room2_out.set_label(msg);		msg = ""; }
		if(room3_out.label() == ""  &&  msg != "")		{ room3_out.set_label(msg);		msg = ""; }
		
		
		
		pb1 = (plr.loc->room1) ? plr.loc->room1->bat : false;
		pb2 = (plr.loc->room2) ? plr.loc->room2->bat : false;
		pb3 = (plr.loc->room3) ? plr.loc->room3->bat : false;
		
		if(pb1  ||  pb2  ||  pb3)		msg = "ВЫ СЛЫШИТЕ ПОРХАНИЕ ЛЕТУЧИХ МЫШЕЙ";
		
		if(room1_out.label() == ""  &&  msg != "")		{ room1_out.set_label(msg);		msg = ""; }
		if(room2_out.label() == ""  &&  msg != "")		{ room2_out.set_label(msg);		msg = ""; }
		if(room3_out.label() == ""  &&  msg != "")		{ room3_out.set_label(msg);		msg = ""; }
		
		
		
		if(!wump.loc->pit  && (wump.loc == plr.loc->room1  ||  wump.loc == plr.loc->room2  ||  wump.loc == plr.loc->room3))
			msg = "ОТКУДА-ТО НЕСЕТ ЗАПАХОМ ВАМПУСА";
		
		if(room1_out.label() == ""  &&  msg != "")		{ room1_out.set_label(msg);		msg = ""; }
		if(room2_out.label() == ""  &&  msg != "")		{ room2_out.set_label(msg);		msg = ""; }
		if(room3_out.label() == ""  &&  msg != "")		{ room3_out.set_label(msg);		msg = ""; }
		
		redraw();
	}

	//Перемещение по лабиринту
	//Если игрок умирает или вызывает выход из игры - ф-ция возвращает false
	//Если игрок остался жив - ф-ция возвращает true
	bool Wumpus_GUI::move()
	{
		const int r1{ (plr.loc->room1) ? plr.loc->room1->num : 0 };
		const int r2{ (plr.loc->room2) ? plr.loc->room2->num : 0 };
		const int r3{ (plr.loc->room3) ? plr.loc->room3->num : 0 };
		
		int usr{ 0 };		//Требуется чтобы игрок ввёл только ту комнату, в которую можно переместить из текущей
		
		istringstream ist { route_in.get_string() };
		ist >> usr;
		if( usr != r1  &&  usr != r2  &&  usr != r3 )		{ msg_out.set_label("ВВЕДИТЕ НОМЕР ОДНОЙ ИЗ СОСЕДНИХ КОМНАТ ДЛЯ ПЕРЕМЕЩЕНИЯ");		return true; }
		
		
		if(plr.loc->pit)			map_btns[plr.loc->num-1]->label = "p" + to_string(plr.loc->num) + "p";
		if(plr.loc->bat)			map_btns[plr.loc->num-1]->label = "b" + to_string(plr.loc->num) + "b";
		if(plr.loc == wump.loc)		map_btns[plr.loc->num-1]->label = "W" + to_string(plr.loc->num) + "W";
		if(!plr.loc->pit  &&  !plr.loc->bat  &&  plr.loc != wump.loc)
									map_btns[plr.loc->num-1]->label = to_string(plr.loc->num);
		
		//Перемещение игрока
		if(usr == r1)			plr.loc = plr.loc->room1;
		else if(usr == r2)		plr.loc = plr.loc->room2;
		else if(usr == r3)		plr.loc = plr.loc->room3;
		
		plr.loc->visited = true;
		if(plr.loc->pit)			map_btns[plr.loc->num-1]->label = "p" + to_string(plr.loc->num) + "p";
		if(plr.loc->bat)			map_btns[plr.loc->num-1]->label = "b" + to_string(plr.loc->num) + "b";
		if(plr.loc == wump.loc)		map_btns[plr.loc->num-1]->label = "W" + to_string(plr.loc->num) + "W";
		if(!plr.loc->pit  &&  !plr.loc->bat  &&  plr.loc != wump.loc)
									map_btns[plr.loc->num-1]->label = to_string(plr.loc->num);
		map_btns[plr.loc->num - 1]->label = "}" + map_btns[plr.loc->num - 1]->label + "{";
		//map_btns[plr.loc->num - 1]->label = "}" + to_string(plr.loc->num) + "{";
		draw_map(plr.loc->num);
		
		//Мышь переносит по лабиринту
		if(plr.loc->bat) {
			srand( time(NULL) );
			int cr = rand() % cave.size();
			//Пока в комнате есть мыши
			while( cave[cr]->bat )		cr = rand() % cave.size();
			
			if(plr.loc->pit)			map_btns[plr.loc->num-1]->label = "p" + to_string(plr.loc->num) + "p";
			if(plr.loc->bat)			map_btns[plr.loc->num-1]->label = "b" + to_string(plr.loc->num) + "b";
			if(plr.loc == wump.loc)		map_btns[plr.loc->num-1]->label = "W" + to_string(plr.loc->num) + "W";
			if(!plr.loc->pit  &&  !plr.loc->bat  &&  plr.loc != wump.loc)
										map_btns[plr.loc->num-1]->label = to_string(plr.loc->num);
			
			plr.loc = cave[cr];
			msg_out.set_label( "ЛЕТУЧАЯ МЫШЬ ХВАТАЕТ ВАС И ПЕРЕНОСИТ ПО ЛАБИРИНТУ ПЕЩЕР В КОМНАТУ #" + to_string(plr.loc->num) );
			
			plr.loc->visited = true;
			if(plr.loc->pit)			map_btns[plr.loc->num-1]->label = "p" + to_string(plr.loc->num) + "p";
			if(plr.loc->bat)			map_btns[plr.loc->num-1]->label = "b" + to_string(plr.loc->num) + "b";
			if(plr.loc == wump.loc)		map_btns[plr.loc->num-1]->label = "W" + to_string(plr.loc->num) + "W";
			if(!plr.loc->pit  &&  !plr.loc->bat  &&  plr.loc != wump.loc)
				map_btns[plr.loc->num-1]->label = to_string(plr.loc->num);
			map_btns[plr.loc->num - 1]->label = "}" + map_btns[plr.loc->num - 1]->label + "{";
			//map_btns[plr.loc->num - 1]->label = "}" + to_string(plr.loc->num) + "{";
			draw_map(plr.loc->num);
		}
		
		//Падение в яму
		if(plr.loc->pit) {
			curr_room_out.set_label("ААААААА... ВЫ СОРВАЛИСЬ В ПРОПАСТЬ.");
			room1_out.set_label("");
			room2_out.set_label("");
			room3_out.set_label("");
			msg_out.set_label("ХА-ХА-ХА! ВЫ ПРОИГРАЛИ!");
			return false;
		}
		
		//Встреча с Вампусом
		if(plr.loc == wump.loc) {
			curr_room_out.set_label("ВАМПУС НАБРАСЫВАЕТСЯ НА ВАС КАК ТОЛЬКО ВЫ ВХОДИТЕ. ВЫ СЪЕДЕНЫ");
			room1_out.set_label("");
			room2_out.set_label("");
			room3_out.set_label("");
			msg_out.set_label("ХА-ХА-ХА! ВЫ ПРОИГРАЛИ!");
			return false;
		}
		
		return true;
	}

	//Стрельба из лука магическими стрелами
	//Возвращает ссылку на комнату куда попадает стрела
	Room* Wumpus_GUI::shoot() {
		int r1{0};
		int r2{0};
		int r3{0};
		
		string usr{ route_in.get_string() };
		
		//Считываем значения комнат
		istringstream iss{usr};
		
		for(int r0 = 0;   iss >> r0; ) {
			if(!r1)			r1 = r0;
			else if(!r2)	r2 = r0;
			else if(!r3)	r3 = r0;
			else			iss.clear(ios_base::failbit);
		}
		
		//Ошибка ввода или уже считаны 3 числа
		if( iss.fail()  &&  !iss.eof() ) {
			msg_out.set_label("ВВЕДИТЕ МАРШРУТ СТРЕЛЫ (номера комнат в кол-ве от 1 до 3 разделённые пробелами)");
			return nullptr;
		}
		
		--plr.arrows;		//Потратили стрелу
		
		int rn1{ (plr.loc->room1) ? plr.loc->room1->num : 0 };
		int rn2{ (plr.loc->room2) ? plr.loc->room2->num : 0 };
		int rn3{ (plr.loc->room3) ? plr.loc->room3->num : 0 };
		
		Room* r{0};
		if(r1 == rn1)			r = plr.loc->room1;
		else if(r1 == rn2)		r = plr.loc->room2;
		else if(r1 == rn3)		r = plr.loc->room3;
		else					r = randroom(plr.loc);	//Если ни с чем не совпало - стрела летит в случайную комнату от её текущего местоположением
		
		if(r == plr.loc  ||  r == wump.loc)		return r;				//Попадание игрока в самого себя или в Вампуса
		else if(r == 0)			{ r1 = 0;		r2 = 0;		r3 = 0; }	//Останавливаем стрелу
		
		
		
		rn1 = (r->room1) ? r->room1->num : 0;
		rn2 = (r->room2) ? r->room2->num : 0;
		rn3 = (r->room3) ? r->room3->num : 0;
		
		if(r2 == rn1)			r = r->room1;
		else if(r2 == rn2)		r = r->room2;
		else if(r2 == rn3)		r = r->room3;
		else if(r2)				r = randroom(r);
		
		if(r == plr.loc  ||  r == wump.loc)		return r;			//Попадание игрока в самого себя или в Вампуса
		else if(r2 == 0)		{ r1 = 0;		r2 = 0;		r3 = 0; }	//Останавливаем стрелу
		
		
		
		rn1 = (r->room1) ? r->room1->num : 0;
		rn2 = (r->room2) ? r->room2->num : 0;
		rn3 = (r->room3) ? r->room3->num : 0;
		
		if(r3 == rn1)			r = r->room1;
		else if(r3 == rn2)		r = r->room2;
		else if(r3 == rn3)		r = r->room3;
		else if(r3)				r = randroom(r);
		
		if(r == plr.loc  ||  r == wump.loc)		return r;				//Попадание игрока в самого себя или в Вампуса
		
		wump_turn();		//ХОД ВАМПУСА!
		
		return r;
	}

	//Ход Вампуса
	//С вероятностью 25% Вампус продолжает сон (не слышит выстрела), либо засыпает снова если ходил
	//В остальных случаях Вампус перемещается в случайную комнату по соседству с той, в которой он находится
	//Так происходит до тех пор пока Вампус снова не уснёт или пока он не окажется в одной комнате с игроком
	void Wumpus_GUI::wump_turn() {
		msg_out.set_label("ПОХОЖЕ ЗВУК СТРЕЛЫ РАЗБУДИЛ ВАМПУСА! ВЫ СЛЫШИТЕ КАК ОН РЫЩЕТ ПО ПОДЗЕМЕЛЬЮ.");
		while (true)
			if( randnum(4) == 0 )		break;	//Только в 1 случае из 4 Вампус засыпает/продолжает спать
			else {
				wump.loc = randroom(wump.loc);		//Перемещение в случайную комнату рядом с текущей (либо остаётся в текущей)
				if(plr.loc == wump.loc)		return;	//Вампус в одной комнате с игроком
			}
		
		msg_out.set_label("Снова тишина. Похоже монстр уснул. Что Вы будете делать?");
	}

//-------------------------------------------------------------------------------------------------------------------------------------------------

	//Остаток от деления на n (число в диапазоне [0; n))
	int Wumpus_GUI::randnum(int n) {
		/*srand( time(NULL) );
		return	rand() % n;*/
		
		//Работает гораздо быстрее первого метода, но может намертво зациклиться
		random_device rd;
		mt19937 mersenne(rd());		// инициализируем Вихрь Мерсенна случайным стартовым числом
		//mt19937 mersenne(static_cast<unsigned int>(time(0)));	// инициализируем Вихрь Мерсенна случайным стартовым числом
		
		return	mersenne() % n;
	}

	//Перемещение в одну из 4 случайных комнат (текущая либо 3 соседних)
	Room* Wumpus_GUI::randroom(Room* r) {
		int rn1{ (r->room1) ? r->room1->num : 0 };
		int rn2{ (r->room2) ? r->room2->num : 0 };
		int rn3{ (r->room3) ? r->room3->num : 0 };
		
		Room* rnew{0};
		switch( randnum(4) ) {
			case 0:		rnew = r;	break;
			case 1:
				if(rn1)			{ rnew = r->room1;	break; }
				else if(rn2)	{ rnew = r->room2;	break; }
				else if(rn3)	{ rnew = r->room3;	break; }
				else			{ rnew = r;			break;}
			
			case 2:
				if(rn2)			{ rnew = r->room2;	break; }
				else if(rn1)	{ rnew = r->room1;	break; }
				else if(rn3)	{ rnew = r->room3;	break; }
				else			{ rnew = r;			break;}
			
			case 3:
				if(rn3)			{ rnew = r->room3;	break; }
				else if(rn1)	{ rnew = r->room1;	break; }
				else if(rn2)	{ rnew = r->room2;	break; }
				else			{ rnew = r;			break;}
			
			default:	error("The room is not connected with another room [Wumpus_GUI::randroom()]");
		}
		
		return rnew;
	}

//-------------------------------------------------------------------------------------------------------------------------------------------------

	//Инструкция к карте:
	//  X  - обозначает что перехода в данном направлении нет
	//  9  - соседняя комната не таит опасностей
	// p2p - в комнате 2 яма
	// b7b - в комнате 7 летучие мыши (^7^)
	// W5W - в комнате 5 находится Вумп
	
	//Отображение статусов соседних комнат находящихся рядом с текущей (комната где находится игрок)
	void Wumpus_GUI::map_cheat(Room* r) {
		if(gmap.loc != plr.loc)		return; //Работает только если отображается комната где находится игрок
		
		if(r->room1) {
			string m {""};
			if(r->room1->pit)			m = "p" + to_string(r->room1->num) + "p";
			if(r->room1->bat)			m = "b" + to_string(r->room1->num) + "b";
			if(r->room1 == wump.loc)	m = "W" + to_string(r->room1->num) + "W";
			
			if(m != "")		room_up.set_label( m );
		}
		
		if(r->room2) {
			string m {""};
			if(r->room2->pit)			m = "p" + to_string(r->room2->num) + "p";
			if(r->room2->bat)			m = "b" + to_string(r->room2->num) + "b";
			if(r->room2 == wump.loc)	m = "W" + to_string(r->room2->num) + "W";
			
			if(m != "")		room_left.set_label( m );
		}
		
		if(r->room3) {
			string m {""};
			if(r->room3->pit)			m = "p" + to_string(r->room3->num) + "p";
			if(r->room3->bat)			m = "b" + to_string(r->room3->num) + "b";
			if(r->room3 == wump.loc)	m = "W" + to_string(r->room3->num) + "W";
			
			if(m != "")		room_right.set_label( m );
		}
	}

	//Вывод полной карты: все комнаты посещены и их статус известен (отображается на кнопках)
	void Wumpus_GUI::full_map_cheat()
	{
		for(int i=0; i<cave.size(); ++i) {
			cave[i]->visited = true;
			
			if(cave[i]->pit)			map_btns[i]->label = "p" + to_string(i+1) + "p";
			if(cave[i]->bat)			map_btns[i]->label = "b" + to_string(i+1) + "b";
			if(cave[i] == wump.loc)		map_btns[i]->label = "W" + to_string(i+1) + "W";
			if(!cave[i]->pit  &&  !cave[i]->bat  &&  cave[i] != wump.loc)
										map_btns[i]->label = to_string(i+1);
			if(plr.arrows  &&  cave[i] == plr.loc)
										map_btns[i]->label = "}" + map_btns[i]->label + "{";
		}
		
		draw_map(gmap.loc->num);		//Отображение карты
	}

//-------------------------------------------------------------------------------------------------------------------------------------------------

	void Wumpus_GUI::generate_cave() {
		//Очищаем все имеющиеся значения
		for(int i=0; i<cave.size(); ++i) {
			cave[i]->num = i+1;
			cave[i]->pit = false;
			cave[i]->bat = false;
			cave[i]->room1 = nullptr;
			cave[i]->room2 = nullptr;
			cave[i]->room3 = nullptr;
		}
		
		plr.loc = nullptr;
		wump.loc = nullptr;
		gmap.loc = nullptr;
		
		//Кол-во уже добавленных ям и комнат с летучими мышами
		//В цикле проверяем чтобы их кол-во не превышало 1/10 от общего кол-ва комнат
		int npit{0};
		int nbat{0};
		
		for(int i=0; i < cave.size(); ++i)
		{
			//cout << "curr i " << i << endl;
			
			//Размещение ям, мышей, монстра или игрока
			switch( randnum(4) )
			{
				//В комнате можно определить пропасть
				case 0:
					if(npit < cave.size()/10)	{ cave[i]->pit = true;		++npit; }
					break;
				
				//В комнате можно разместить летучих мышей
				case 1:
					if(nbat < cave.size()/10)	{ cave[i]->bat = true;		++nbat; }
					break;
				
				case 2:		wump.loc = cave[i];		break;	//Переместить монстра в комнату
				case 3:		plr.loc = cave[i];		break;	//Переместить игрока в комнату
			}
			
			//------------------------------------------------------------------------------
			
			//Построение пещеры происходит по следующему принципу:
			// направление (выход) не должен быть уже ранее занятым (должен иметь значение нулевого указателя)
			//
			// должны иметься комнаты с пустыми входами/выходами, при этом это не должна быть текущая комната
			//
			// если не осталось комнат с пустым входом/выходом - текущая комната лишается выхода в том или ином направлении
			//
			// случайно выбранная комната не должна быть текущей комнатой и должна иметь свободные входы/выходы
			//					!!!хотя бывают корридоры в играх приводящих в ту же комнату!!!
			//
			// случайно выбранная комната не должна иметь более 1 входа в текущую комнату
			//					!!!хотя бывают раздваивающиеся корридоры в играх приводящих в одну и ту же комнату!!!
			
			if( !cave[i]->room1  &&  is_vacancy(cave[i]) ) {
				int cr = randnum( cave.size() );
				//Пока это одна и та же комната ИЛИ если комната уже является соседом текущей
				auto t0 = chrono::steady_clock::now();
				while( cave[cr]==cave[i]  ||  is_neighbor(cave[i], cave[cr])  ||  is_full(cave[cr]) )
				{
					auto t1 = chrono::steady_clock::now() - t0;		//Из-за randnum цикл может зависнуть, поэтому нужно сбрасывать генерацию пещеры
					if( chrono::duration_cast<chrono::seconds>(t1).count() >= 2 )	{ generate_cave();	return; }
					cr = randnum( cave.size() );
				}
				
				cave[i]->room1 = cave[cr];
				
				//Переход в текущую комнату становится одним из входов/выходов случайно выбранной комнаты
				if( !cave[cr]->room1 )			cave[cr]->room1 = cave[i];
				else if( !cave[cr]->room2 )		cave[cr]->room2 = cave[i];
				else if( !cave[cr]->room3 )		cave[cr]->room3 = cave[i];
			}
			
			if( !cave[i]->room2  &&  is_vacancy(cave[i]) ) {
				int cr = randnum( cave.size() );
				//Пока это одна и та же комната ИЛИ если комната уже является соседом текущей
				auto t0 = chrono::steady_clock::now();		//Из-за randnum цикл может зависнуть, поэтому нужно сбрасывать генерацию пещеры
				while( cr==i  ||  is_neighbor(cave[i], cave[cr])  ||  is_full(cave[cr]) )
				{
					auto t1 = chrono::steady_clock::now() - t0;
					if( chrono::duration_cast<chrono::seconds>(t1).count() > 2 )	{ generate_cave();	return; }
					cr = randnum( cave.size() );
				}
				
				cave[i]->room2 = cave[cr];
				
				//Переход в текущую комнату становится одним из входов/выходов случайно выбранной комнаты
				if( !cave[cr]->room1 )			cave[cr]->room1 = cave[i];
				else if( !cave[cr]->room2 )		cave[cr]->room2 = cave[i];
				else if( !cave[cr]->room3 )		cave[cr]->room3 = cave[i];
			}
			
			if( !cave[i]->room3  &&  is_vacancy(cave[i]) ) {
				int cr = randnum( cave.size() );
				//Пока это одна и та же комната ИЛИ если комната уже является соседом текущей
				auto t0 = chrono::steady_clock::now();		//Из-за randnum цикл может зависнуть, поэтому нужно сбрасывать генерацию пещеры
				while( cr==i  ||  is_neighbor(cave[i], cave[cr])  ||  is_full(cave[cr]) )
				{
					auto t1 = chrono::steady_clock::now() - t0;
					if( chrono::duration_cast<chrono::seconds>(t1).count() > 2 )	{ generate_cave();	return; }
					cr = randnum( cave.size() );
				}
				
				cave[i]->room3 = cave[cr];
				
				//Переход в текущую комнату становится одним из входов/выходов случайно выбранной комнаты
				if( !cave[cr]->room1 )			cave[cr]->room1 = cave[i];
				else if( !cave[cr]->room2 )		cave[cr]->room2 = cave[i];
				else if( !cave[cr]->room3 )		cave[cr]->room3 = cave[i];
			}
			
			//cout << "Room " << cave[i]->num << " created" << '\n';
		}
		
		//------------------------------------------------------------------------------
		
		//Монстр и игрок обязательно должны находиться в лабиринте в комнате без ямы или мышей,
		// при этом не в одной и той же, поэтому проверяем
		if(!wump.loc)	wump_relocate();
		if(!plr.loc)	plr_relocate();
		
		//В идеале проверить маршрут на то что каждая комната имеет переход к любой другой
		// т.к. может возникнуть ситуация когда 4 комнаты переходами зацикляться друг на друга
		// и не будут связаны с остальной частью лабиринта,
		//
		// либо менее опасная ситуация если пользователь будет окружён непреодолимыми опасностями
		// и не сможет перемещаться без 100% риска смерти=) В такой ситуации он сможет стрелять 
		// или перезагрузить лабиринт, или перестроить с тем же кол-вом комнат и иметь вероятность
		// оказаться не в такой затруднительной ситуации
	}

	//Перемещение игрока в случайную позицию в лабиринте
	void Wumpus_GUI::plr_relocate() {
		int cr = randnum( cave.size() );
		while( cave[cr]->pit  ||  cave[cr]->bat  ||  cave[cr]==wump.loc )
			cr = randnum( cave.size() );
		
		plr.loc = cave[cr];
	}

	//Перемещение Вампуса в случайную позицию в лабиринте
	//С соблюдением условий что в комнате нет ямы или летучих мышей,
	// при этом игрок и монстр не в одной и той же комнате
	void Wumpus_GUI::wump_relocate() {
		int cr = randnum( cave.size() );
		while( cave[cr]->pit  ||  cave[cr]->bat  ||  cave[cr]==plr.loc )
			cr = randnum( cave.size() );
		
		wump.loc = cave[cr];
	}


	//Проверка есть ли комнаты со свободным входом/выходом, при этом такая комната не должна оказаться той что указана в аргументе
	//Если есть - возвращает количество таковых
	//Иначе возвращает нуль
	int Wumpus_GUI::is_vacancy(Room* r) {
		int num{0};
		
		for(int i=0; i < cave.size(); ++i)
			if(cave[i] != r) {
				if( !cave[i]->room1 )		++num;
				else if( !cave[i]->room2 )	++num;
				else if( !cave[i]->room3 )	++num;
			}
		
		return num;
	}

	//Проверка являются ли комнаты соседями
	//Если да - возврат 'true'
	bool Wumpus_GUI::is_neighbor(Room* a, Room* b) {
		if(a->room1 == b)	return true;
		if(a->room2 == b)	return true;
		if(a->room3 == b)	return true;
		
		return false;
	}

	//Проверка заняты ли все входы/выходы у комнаты 'r'
	//Если да - возврат 'true'
	bool Wumpus_GUI::is_full(Room* r) {
		if( r->room1  &&  r->room2  &&  r->room3 )		return true;
		
		return false;
	}
}