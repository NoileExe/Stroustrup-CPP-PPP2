


#include "game.h"

//------------------------------------------------------------------------------

//Собственно сама игра
//Возвращает false если игрок проиграл (умер или закончились стрелы)
//Возвращает true если игрок победил
bool Game::play()
{
	if(cave.size() == 0)		generate_cave();
	
	cout << "THE HUNT HAS BEGUN!\n\n";
	plr.arrows = 5;
	while(true) {
		look_around();		//Описание окружения
		
		char ch{ get_action() };	//Узнаем что игрок хочет сделать
		
		if(ch == 'q')						return false;
		if( ch == 'm'  &&  !move() )		return false;	//После перемещения игрок умер
		if( ch == 's' ) {
			Room* r{ shoot() };
			
			if(plr.loc == wump.loc)	//Встреча с Вампусом
			{
				cout << "WUMPUS ENTERS THE ROOM.\n" << 
						"YOU'VE STUMBLED UPON A WUMPUS. HE EATS YOU\n\n" <<
						"HA-HA-HA YOU LOSE!";
				return false;
			}
			
			if(r == plr.loc)		//Стрела попала в игрока
			{
				cout << "THE ARROW RICOCHET HITS YOU. STUPID DEATH.\n\n" <<
						"HA-HA-HA YOU LOSE!";
				return false;
			}
			
			if(r == wump.loc)		//Стрела попала в Вампуса - ПОБЕДА!
			{
				cout << "YOU HEAR THE CRY OF A DYING MONSTER.\n" <<
						"WUMPUS IS KILLED IN ROOM " << r->num << "\n\n" <<
						"CONGRATULATIONS, YOU HAVE WON!";
				return true;
			}
			
			if(!plr.arrows)			//Закончились стрелы
			{
				cout << "YOU HAVE RUN OUT OF ALL ARROWS.\n" <<
						"YOU WERE LEFT UNARMED IN A DARK DANGEROUS MAZE OF CAVES.\n\n" <<
						"HA-HA-HA YOU LOSE!";
				return false;
			}
			
			cout << "THE ARROW HIT SOMEWHERE WITH A DULL THUD\n\n";
		}
	}
}

//Вывод описания окружения
void Game::look_around() {
	cout << "\n\nYOU ARE IN ROOM " << plr.loc->num << ". YOU HAVE " << plr.arrows << " ARROWS LEFT" << '\n';
	
	bool pb1{ (plr.loc->room1) ? plr.loc->room1->pit : false};
	bool pb2{ (plr.loc->room2) ? plr.loc->room2->pit : false};
	bool pb3{ (plr.loc->room3) ? plr.loc->room3->pit : false};
	
	if(pb1  ||  pb2  ||  pb3) {
		if(wump.loc == plr.loc->room1  ||  wump.loc == plr.loc->room2  ||  wump.loc == plr.loc->room3)
				cout << "YOU FEEL THE SMELLY BREEZE\n";
		else	cout << "YOU FEEL THE DRAFT\n";
	}
	
	pb1 = (plr.loc->room1) ? plr.loc->room1->bat : false;
	pb2 = (plr.loc->room2) ? plr.loc->room2->bat : false;
	pb3 = (plr.loc->room3) ? plr.loc->room3->bat : false;
	
	if(pb1  ||  pb2  ||  pb3)
		cout << "YOU HEAR THE FLUTTERING OF BATS\n";
	
	if(!wump.loc->pit  && (wump.loc == plr.loc->room1  ||  wump.loc == plr.loc->room2  ||  wump.loc == plr.loc->room3))
		cout << "FROM SOMEWHERE COMES THE STINK OF WUMPUS\n";
	
	cout << "\nTUNNELS LEAD TO\t\t";
	
	vector<int> r;
	if(plr.loc->room1)		r.push_back(plr.loc->room1->num);
	if(plr.loc->room2)		r.push_back(plr.loc->room2->num);
	if(plr.loc->room3)		r.push_back(plr.loc->room3->num);
	
	sort(r);
	for(int i : r)		cout << i << ' ';
	cout << "\n\n";
}

//Запрашивает и получает ответ с действием игрока
//Возвращает выбранное действие:
// q - завершить текущее приключение (выход из игры)
// m - передвижение
// s - стрельба
char Game::get_action() {
	char ch{0};		//Ввод действия
	while(ch != 'm'  &&  ch != 's'  &&  ch != 'q')
	{
		cout << "SHOOT OR MOVE OR QUIT? (s-m-q)?\t";
		cin.get(ch);
		if(!cin  &&  !cin.eof())	error("problem with input stream [Game::play()]");
		if(cin.eof())				cin.clear();
		
		if(ch == 'c') {
			cin.unget();
			string str;
			cin >> str;
			if(str == "cheat1")		map_cheat(plr.loc);
			if(str == "cheat2")		full_map_cheat();
		}
		
		for(char tmp=ch; tmp != '\n'; )		{ cin.get(tmp);		cin.clear(); }
	}
	
	return ch;
}

//Перемещение по лабиринту
//Если игрок умирает или вызывает выход из игры - ф-ция возвращает false
//Если игрок остался жив - ф-ция возвращает true
bool Game::move() {
	const int r1{ (plr.loc->room1) ? plr.loc->room1->num : 0 };
	const int r2{ (plr.loc->room2) ? plr.loc->room2->num : 0 };
	const int r3{ (plr.loc->room3) ? plr.loc->room3->num : 0 };
	
	int usr{0};		//Требуется чтобы игрок ввёл только ту комнату, в которую можно переместить из текущей
	while( (usr != r1  &&  usr != r2  &&  usr != r3)  ||  usr==0 ) {
		cout << "WHERE TO?\t";
		cin >> usr;
		if(cin.eof() || cin.fail())		{ cin.clear();		cin.putback('$'); }
		else if(cin.bad())				error("problem with input stream [Game::move()]");
		
		for(char ch=0; ch != '\n'; )		{ cin.get(ch);		cin.clear(); }
	}
	
	//Перемещение игрока
	if(usr == r1)			plr.loc = plr.loc->room1;
	else if(usr == r2)		plr.loc = plr.loc->room2;
	else if(usr == r3)		plr.loc = plr.loc->room3;
	
	//Мышь переносит по лабиринту
	if(plr.loc->bat) {
		cout << "A HUGE BAT GRABBED YOU AND CARRIED YOU THROUGH THE MAZE TO ROOM ";
		
		srand( time(NULL) );
		int cr = rand() % cave.size();
		//Пока в комнате есть мыши
		while( cave[cr]->bat )		cr = rand() % cave.size();
		
		plr.loc = cave[cr];
		cout << plr.loc->num << '\n';
	}
	
	//Падение в яму
	if(plr.loc->pit) {
		cout << "YYYIIIIEEEE... FELL IN PIT\n\n" <<
				"HA-HA-HA YOU LOSE!";
		return false;
	}
	
	//Встреча с Вампусом
	if(plr.loc == wump.loc) {
		cout << "YOU'VE STUMBLED UPON A WUMPUS. HE EATS YOU\n\n" <<
				"HA-HA-HA YOU LOSE!";
		return false;
	}
	
	return true;
}

//Стрельба из лука магическими стрелами
//Возвращает ссылку на комнату куда попадает стрела
Room* Game::shoot() {
	int r1{0};
	int r2{0};
	int r3{0};
	while( r1==0 )		//Требуется чтобы игрок ввёл маршрут из не более чем 3 комнат
	{
		cout << "NO. OF ROOMS (1-3 WITH SPACE)?\t";
		string usr{""};
		getline(cin, usr);
		if(!cin  &&  !cin.eof())	error("problem with input stream [Game::shoot()]");
		if(cin.eof())				{ cin.clear();		usr = "";	r1 = 0; }
		
		//Считываем значения комнат
		if(usr != "") {
			istringstream iss{usr};
			
			for(int r0 = 0;   iss >> r0; ) {
				if(!r1)			r1 = r0;
				else if(!r2)	r2 = r0;
				else if(!r3)	r3 = r0;
				else			iss.clear(ios_base::failbit);
			}
			
			//Ошибка ввода или уже считаны 3 числа
			if( iss.fail()  &&  !iss.eof() )		{ r1 = 0;		r2 = 0;		r3 = 0; }
			else if(iss.bad())						error("problem with input string stream [Game::shoot()]");
		}
	}
	
	--plr.arrows;		//Потратили стрелу
	
	int rn1{ (plr.loc->room1) ? plr.loc->room1->num : 0 };
	int rn2{ (plr.loc->room2) ? plr.loc->room2->num : 0 };
	int rn3{ (plr.loc->room3) ? plr.loc->room3->num : 0 };
	
	Room* r{0};
	if(r1 == rn1)			r = plr.loc->room1;
	else if(r1 == rn2)		r = plr.loc->room2;
	else if(r1 == rn3)		r = plr.loc->room3;
	else					r = randroom(plr.loc);	//Если ни с чем не совпало
	
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
	else if(r == 0)		{ r1 = 0;		r2 = 0;		r3 = 0; }	//Останавливаем стрелу
	
	
	
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
void Game::wump_turn() {
	cout << "THE SOUND OF THE ARROW WOKE WUMPUS. DO YOU HEAR? WUMPUS PROWLING THROUGH THE MAZE!\n";
	while (true)
		if( randnum(4) == 0 )		break;	//Только в 1 случае из 4 Вампус засыпает/продолжает спать
		else {
			wump.loc = randroom(wump.loc);		//Перемещение в случайную комнату рядом с текущей (либо остаётся в текущей)
			if(plr.loc == wump.loc)		break;	//Вампус в одной комнате с игроком
		}
	
	cout << "SILENCE FELL AGAIN. LOOKS LIKE THE MONSTER IS SLEEPING.\n\n";
}

//------------------------------------------------------------------------------

//Остаток от деления на n (число в диапазоне [0; n))
int Game::randnum(int n) {
	/*srand( time(NULL) );
	return	rand() % n;*/
	
	//Работает гораздо быстрее первого метода, но может намертво зациклиться
	random_device rd;
	mt19937 mersenne(rd());		// инициализируем Вихрь Мерсенна случайным стартовым числом
	//mt19937 mersenne(static_cast<unsigned int>(time(0)));	// инициализируем Вихрь Мерсенна случайным стартовым числом
	
	return	mersenne() % n;
}

//Перемещение в одну из 4 случайных комнат (текущая либо 3 соседних)
Room* Game::randroom(Room* r) {
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
		
		default:	error("The room is not connected with another room [Game::randroom()]");
	}
	
	return rnew;
}

//------------------------------------------------------------------------------

//Инструкция к карте:
//  X  - обозначает что перехода в данном направлении нет
//  9  - соседняя комната не таит опасностей
// p2p - в комнате 2 яма
// ^7^ - в комнате 7 летучие мыши
// w5w - в комнате 5 находится Вумп
// }8{ - местоположение игрока


//Вывод значения комнаты с обозначением опасности
string Game::cheat_room(Room* r) const {
	ostringstream oss;
	
	if(plr.loc == r)		oss << '}' << r->num << '{';
	else if(wump.loc == r)	oss << 'w' << r->num << 'w';
	else if( !r )			oss << ' ' <<   'X'  << ' ';
	else if( r->pit )		oss << 'p' << r->num << 'p';
	else if( r->bat )		oss << '^' << r->num << '^';
	else					oss << ' ' << r->num << ' ';
	
	return oss.str();
}

//Вывод соседних комнат рядом с указанной комнатой
void Game::map_cheat(Room* r) const {
	cout << right << setw(12) << cheat_room(r->room1) << '\n';
	cout << right << setw(10) << '|' << '\n';
	cout << left << setw(5) << cheat_room(r->room2) << "--"
		 << cheat_room(r) << "--"
		 << right << setw(5) << cheat_room(r->room3) << "\n\n";
}

//Вывод полной карты
void Game::full_map_cheat() const {
	cout << "Instructions for the map:\n" <<
			"  X  - indicates that there is no way in this direction\n" <<
			"  9  - the next room is not fraught with danger\n" <<
			" p2p - there is a pit in room 2\n" <<
			" ^7^ - there are bats in room 7\n" <<
			" w5w - Wump is in room 5\n" <<
			" }8{ - player location\n";
	
	for(int i=0; i<cave.size(); ++i)		map_cheat(cave[i]);
}

//------------------------------------------------------------------------------

void Game::generate_cave() {
	cout << "Building a dungeon. Please, wait!" << '\n';
	
	//Очищаем все имеющиеся значения
	for(int i=0; i<cave.size(); ++i) {
		cave[i]->num = i+1;
		cave[i]->pit = false;
		cave[i]->bat = false;
		cave[i]->room1 = nullptr;
		cave[i]->room2 = nullptr;
		cave[i]->room3 = nullptr;
	}
	
	//Кол-во уже добавленных ям и комнат с летучими мышами
	//В цикле проверяем чтобы их кол-во не превышало 1/10 от общего кол-ва комнат
	int npit{0};
	int nbat{0};
	
	for(int i=0; i < cave.size(); ++i)
	{
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
			while( cave[cr]==cave[i]  ||  is_neighbor(cave[i], cave[cr])  ||  is_full(cave[cr]) )
				cr = randnum( cave.size() );
			
			cave[i]->room1 = cave[cr];
			
			//Переход в текущую комнату становится одним из входов/выходов случайно выбранной комнаты
			if( !cave[cr]->room1 )			cave[cr]->room1 = cave[i];
			else if( !cave[cr]->room2 )		cave[cr]->room2 = cave[i];
			else if( !cave[cr]->room3 )		cave[cr]->room3 = cave[i];
		}
		
		if( !cave[i]->room2  &&  is_vacancy(cave[i]) ) {
			int cr = randnum( cave.size() );
			//Пока это одна и та же комната ИЛИ если комната уже является соседом текущей
			while( cr==i  ||  is_neighbor(cave[i], cave[cr])  ||  is_full(cave[cr]) )
				cr = randnum( cave.size() );
			
			cave[i]->room2 = cave[cr];
			
			//Переход в текущую комнату становится одним из входов/выходов случайно выбранной комнаты
			if( !cave[cr]->room1 )			cave[cr]->room1 = cave[i];
			else if( !cave[cr]->room2 )		cave[cr]->room2 = cave[i];
			else if( !cave[cr]->room3 )		cave[cr]->room3 = cave[i];
		}
		
		if( !cave[i]->room3  &&  is_vacancy(cave[i]) ) {
			int cr = randnum( cave.size() );
			//Пока это одна и та же комната ИЛИ если комната уже является соседом текущей
			while( cr==i  ||  is_neighbor(cave[i], cave[cr])  ||  is_full(cave[cr]) )
				cr = randnum( cave.size() );
			
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
void Game::plr_relocate() {
	//cout << "Place a player" << '\n';
	int cr = randnum( cave.size() );
	while( cave[cr]->pit  ||  cave[cr]->bat  ||  cave[cr]==wump.loc )
		cr = randnum( cave.size() );
	
	plr.loc = cave[cr];
}

//Перемещение Вампуса в случайную позицию в лабиринте
//С соблюдением условий что в комнате нет ямы или летучих мышей,
// при этом игрок и монстр не в одной и той же комнате
void Game::wump_relocate() {
	//cout << "Place a monster" << '\n';
	int cr = randnum( cave.size() );
	while( cave[cr]->pit  ||  cave[cr]->bat  ||  cave[cr]==plr.loc )
		cr = randnum( cave.size() );
	
	wump.loc = cave[cr];
}


//Проверка есть ли комнаты со свободным входом/выходом, при этом такая комната не должна оказаться той что указана в аргументе
//Если есть - возвращает количество таковых
//Иначе возвращает нуль
int Game::is_vacancy(Room* r) {
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
bool Game::is_neighbor(Room* a, Room* b) {
	if(a->room1 == b)	return true;
	if(a->room2 == b)	return true;
	if(a->room3 == b)	return true;
	
	return false;
}

//Проверка заняты ли все входы/выходы у комнаты 'r'
//Если да - возврат 'true'
bool Game::is_full(Room* r) {
	if( r->room1  &&  r->room2  &&  r->room3 )		return true;
	
	return false;
}