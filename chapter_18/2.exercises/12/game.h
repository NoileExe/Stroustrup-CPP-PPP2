

#include <std_lib_facilities.h>
#include <ctime> //Для рандомизации по текущему времени (секунде)

//------------------------------------------------------------------------------

struct Room {
	int num{0};				//Номер комнаты
	bool pit{false};		//Наличие пропасти
	bool bat{false};		//Наличие летучих мышей
	//Для просмотра карты во время игры можно добавить ещё одно значение указывающее посещалась ли комната
	
	Room* room1{nullptr};	//Переходы в соседние комнаты
	Room* room2{nullptr};
	Room* room3{nullptr};
};

struct Player {
	int arrows{0};			//Количество стрел
	Room* loc{nullptr};		//Местоположение игрока/монстра
};

struct Game {
	explicit Game(int rooms) {
		if(rooms < 0)		error("negative number of cave rooms [Game initialisation]");
		if(rooms < 10)		error("less than 10 rooms? not interested! [Game initialisation]");
		for(int i=0; i<rooms; ++i)		cave.push_back(new Room); //Заполнение вектора пустыми комнатами
		generate_cave();	//Создание случайной пещеры отталкиваясь от размера вектора
	}
	
	//Копирующий конструктор и присваивание
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	
	//Перемещающий конструктор и присваивание
	Game(const Game&&) = delete;
	Game& operator=(const Game&&) = delete;
	
	~Game() { for(int i=0; i<cave.size(); ++i)		delete cave[i]; }
	
	
	void generate_cave();				//Создание случайной пещеры отталкиваясь от размера вектора
	bool play();						//Собственно сама игра
	void plr_relocate();				//Перемещение игрока в случайную позицию в лабиринте
	void wump_relocate();				//Перемещение Вампуса в случайную позицию в лабиринте
	
private:
	int is_vacancy(Room* r);				//Проверка есть ли комнаты со свободным входом/выходом [вспомогательная ф-ция для generate_cave()]
	bool is_neighbor(Room* a, Room* b);		//Проверка являются ли комнаты соседями [вспомогательная ф-ция для generate_cave()]
	bool is_full(Room* r);					//Проверка заняты ли все входы/выходы у комнаты 'r' [вспомогательная ф-ция для generate_cave()]
	
	void look_around();					//Вывод описания окружения
	char get_action();					//Запрашивает и получает ответ с действием игрока
	bool move();						//Если пользователь решил совершить движение используется данная ф-ция
	Room* shoot();						//Если пользователь решил совершить выстрел из лука используется данная ф-ция
	void wump_turn();					//Ход Вампуса
	int randnum(int n);					//Остаток от деления на n
	Room* randroom(Room* r);			//Перемещение в одну из 4 случайных комнат (текущая либо 3 соседних)
	
	string cheat_room(Room* r) const;	//Строка значения комнаты с обозначением опасности. Используется для вывода карты
	void map_cheat(Room* r) const;		//Вывод соседних комнат рядом с указанной комнатой
	void full_map_cheat() const;		//Вывод полной карты
	
	
	vector<Room*> cave;		//Пещера состоит из комнат
	Player plr;
	Player wump;
};