

#include "skip_list.h"

//------------------------------------------------------------------------------

Unit::Unit(int v, int l, Unit* r, Unit* d) : val{v}, lvl{l}, right{r}, down{d}
{
	if(val < 0)		error("negative Unit value [Unit() init]");
	if(lvl < 0)		error("negative value of the number of levels [Unit() init]");
	if(lvl == 0)	error("zero value of number of levels [Unit() init]");
}

//------------------------------------------------------------------------------

//Идентификация наследников (указание элементов справа от каждого в списках на каждом уровне)
//Требуется в 5 местах: при инициализациях объекта Skip_list, при копирующем присваивании, при вставке нового элемента и при удалении имеющегося
void Skip_list::ident_succ()
{
	//Затирание списков
	for(int i=0; i < vu.size(); ++i) {
		Unit* ul{vu[i]};
		while(ul) {
			ul->right = 0;
			ul = ul->down;
		}
	}
	
	
	//Перебор списков
	for(int lst=0; lst < vu.size(); ++lst) {
		Unit* ul{vu[lst]};
		
		//Перебор уровней в текущем списке (пока есть куда спускаться)
		while(ul) {
			//Поиск списка с максимальным уровнем больше или равным текущему перебираемому
			for(int j=lst+1; j < vu.size(); ++j)
				if( vu[j]->lvl >= ul->lvl )
				{
					Unit* ulr{vu[j]};
					while(ul->lvl != ulr->lvl)		ulr = ulr->down;
					
					ul->right = ulr;
					break;
				}
			
			ul = ul->down;
		}
	}
}


//Получает количество уровней и максимальное значение списка (крайний правый)
//Хранит указатель на верхний элемент заголовочного списка (value = 0)
Skip_list::Skip_list(int lvl, int max)
{
	if(lvl < 0)		error("negative value of the number of levels [Skip_list() init]");
	if(lvl == 0)	error("zero value of number of levels [Skip_list() init]");
	//if(max <= 0)	error("the number of lists must be greater than zero [Skip_list() init]");
	if(max < 0)		error("negative value of the number of lists [Skip_list() init]");
	
	//-----------------------------Составление списков------------------------------
	
	vu.clear();
	srand( time(NULL) );
	for(int i=0; i <= max; ++i)
	{
		int curr_list_lvl{lvl-1};						//Заголовочный (стартовый, крайний левый) список с максимальным кол-вом уровней
		if(i > 0)		curr_list_lvl = rand() % lvl;	//Случайное целое положительное значение в диапазоне [0; lvl)
		
		//Составляем отдельно взятый список снизу вверх (от 0+1 уровня до curr_list_lvl)
		Unit* ul{nullptr};
		for(int j=0; j <= curr_list_lvl; ++j) {
			Unit* next_down = ul;
			ul = new Unit{i, j+1, nullptr, next_down};		//Поднимаемся вверх по уровням. down == пред. перебираемому элементу
		}
		
		vu.push_back(ul);
	}
	
	//-----------------------------Составление списков------------------------------
	
	ident_succ();	//Указание элементов справа на том же уровне для каждого элемента каждого списка
	
	if(!vu[0])		error("head NULLPTR [Skip_list() init]");
}

//Копирующий конструктор
Skip_list::Skip_list(const Skip_list& sl)
{
	int max{ sl.vu[sl.vu.size()-1]->val }; //Максимальное значение списка
	
	//-----------------------------Составление списков------------------------------
	
	vu.clear();
	const Unit* p{nullptr};
	for(int i=0; i <= max; ++i)
	{
		p = sl.find(i);		//Проверяем есть ли список с таким значением
		
		Unit* ul{nullptr};
		if(p)
		{
			//Составляем отдельно взятый список снизу вверх (от 0+1 уровня до p->lvl)
			for(int j=0; j < p->lvl; ++j) {
				Unit* next_down = ul;
				ul = new Unit{p->val, j+1, nullptr, next_down};		//Поднимаемся вверх по уровням. down == пред. перебираемому элементу
			}
		}
		
		if(ul)		vu.push_back(ul);
	}
	
	//-----------------------------Составление списков------------------------------
	
	ident_succ();	//Указание элементов справа на том же уровне для каждого элемента каждого списка
	
	if(!vu[0])		error("head NULLPTR [Skip_list() init]");
}

//Деструктор
Skip_list::~Skip_list() {
	Unit* p{nullptr};
	for(int i=vu.size()-1; i>=0; --i) {
		p = vu[i];
		
		while(p) {
			Unit* prev{p->down};
			delete p;
			p = prev;
		}
	}
}

//Копирующее присваивание
Skip_list& Skip_list::operator=(const Skip_list& sl)
{
	this->~Skip_list();		//Уничтожаем текущий список
	
	//При копировании лишь следующими двумя строками в вечном цикле происходит утечка памяти, т.к. постепенно растёт
	// объем занятого программой пространства ОЗУ
	//Создаём в динамической памяти новый список и не удаляя просто копируем ссылку на его заголовочный список
	//Список из динамической памяти будет удалён при вызове деструктора текущего объекта
	/*Skip_list* new_sl = new Skip_list(sl);
	vu.clear();
	vu = new_sl->vu;*/
	
	
	//------------------------------------------------------------------------------
	
	int max{ sl.vu[sl.vu.size()-1]->val }; //Максимальное значение списка
	
	//-----------------------------Составление списков------------------------------
	
	vu.clear();
	const Unit* p{nullptr};
	for(int i=0; i <= max; ++i)
	{
		p = sl.find(i);
		
		Unit* ul{nullptr};
		if(p)
		{
			//Составляем отдельно взятый список снизу вверх (от 0+1 уровня до p->lvl)
			for(int j=0; j < p->lvl; ++j) {
				Unit* next_down = ul;
				ul = new Unit{p->val, j+1, nullptr, next_down};		//Поднимаемся вверх по уровням. down == пред. перебираемому элементу
			}
		}
		
		if(ul)		vu.push_back(ul);
	}
	
	//-----------------------------Составление списков------------------------------
	
	ident_succ();	//Указание элементов справа на том же уровне для каждого элемента каждого списка
	
	if(!vu[0])		error("head NULLPTR [Skip_list() init]");
	return *this;
}

//------------------------------------------------------------------------------

//Поиск в списке значения
//Возвращает nullptr если не было найдено
const Unit* Skip_list::find(int v) const {
	if(v < 0)		error("negative value of list [Skip_list::find(int)]");
	
	const Unit* p{vu[0]};
	while(p)
	{
		while(p->right)
			if(p->val > v  ||  p->val == v)		break;
			else								p = p->right;
		
		
		//Спускаемся в заголовочном списке на уровень ниже
		if(p->val != v) {
			const Unit* next{vu[0]};
			for(int i=0; i <= vu[0]->lvl - p->lvl; ++i)		next = next->down;
			p = next;
		}
		else		break;
	}
	
	return p;
}

//Поиск в списке значения на определённом уровне
//Возвращает nullptr если не было найдено
const Unit* Skip_list::find(int v, int l) const {
	if(l <= 0)		error("negative or zero value of list level [Skip_list::find(int, int)]");
	
	const Unit* p{find(v)};
	while(p && p->lvl != l)		p = p->down;
	return p;
}

//------------------------------------------------------------------------------

//Вставляет список со значением v после значения меньше v, но обязательно перед списком со значением больше v
void Skip_list::insert(int v) {
	const Unit* next{find(v)};
	if(next)		error("attempt to insert an already existing element " + to_string(v) + " [Skip_list::insert(int)]");
	
	int max{ vu[vu.size()-1]->val };
	next = vu[0];
	
	//Поиск элемента, который будет находится после текущего добавляемого
	for(int i=1; next->val+i <= max; ++i) {
		const Unit* p{ find(next->val+i) };
		
		//Найден список со значением больше добавляемого
		if(p  &&  p->val > v)		{ next = p;		break; }
		
		//Достигнут конец списка
		if(next->val+i == max)		{ next = 0;		break; }
	}
	
	const Unit* prev{find(0, 1)};	//Низ заголовочного списка
	while(prev->right != next)		prev = prev->right;
	
	//------------------------------------------------------------------------------
	
	srand( time(NULL) );
	int curr_list_lvl{ rand() % vu[0]->lvl };		//Случайное целое положительное значение в диапазоне [0; lvl)
	
	vector<Unit*> tmp;
	if(v < max)		//Если новый элемент вставляется посередине
		for(int i=0; vu[i]->val < v; ++i)		tmp.push_back(vu[i]);
	else
		for(int i=0; i < vu.size(); ++i)		tmp.push_back(vu[i]);
	
	//Составляем отдельно взятый список снизу вверх (от 0+1 уровня до curr_list_lvl)
	Unit* ul{nullptr};
	for(int i=0; i <= curr_list_lvl; ++i) {
		Unit* next_down = ul;
		ul = new Unit{v, i+1, nullptr, next_down};		//Поднимаемся вверх по уровням. down == пред. перебираемому элементу
	}
	
	tmp.push_back(ul);
	
	if(v < max)
		for(int i=tmp.size()-1; i < vu.size(); ++i)		tmp.push_back(vu[i]);
	
	vu.clear();
	vu = tmp;
	
	ident_succ();	//Указание элементов справа на том же уровне для каждого элемента каждого списка
}

//Удаляет список со значением v меня ссылки списка перед списком со значением v
void Skip_list::erase(int v) {
	if(v == 0)		error("attempt to remove a Skip_list header list [Skip_list::erase( 0 )]");
	
	const Unit* p{find(v)};
	if(!p)		error("attempt to remove a non-existent element " + to_string(v) + " [Skip_list::erase(int)]");
	
	for(int i=0; i < vu.size(); ++i)
		if(vu[i] == p)
		{
			while(p) {
				Unit* prev{p->down};
				delete p;
				p = prev;
			}
			
			vu.erase(vu.begin()+i);
			break;
		}
	
	ident_succ();	//Указание элементов справа на том же уровне для каждого элемента каждого списка
}

//------------------------------------------------------------------------------

//Вывод списка с пропусками по ссылке в поток ost
ostream& operator<<(ostream& ost, const Skip_list& s)
{
	const Unit* p{s.header()};
	
	//Поиск максимального значения списка
	while(p->down)		p = p->down;	//Самый нижний
	while(p->right)		p = p->right;	//Самый правый
	int max{p->val};
	
	p = s.header();
	for(int lvl=0; lvl < s.header()->lvl; ++lvl) {
		ost << p->lvl << " |\t";
		
		const Unit* pr{p};
		for(int lst=0; lst <= max; ++lst) {
			ost << pr->val << '\t';
			
			//Есть элемент правее?
			if(pr = pr->right)
				while(pr->val != lst+1)		{ if(s.find(lst+1)) ost << '\t';		++lst; }
			else
				while(lst < max)			{ if(s.find(lst+1)) ost << '\t';		++lst; }
		}
		
		ost << "|\n";
		p = p->down;
	}
	
	return ost;
}