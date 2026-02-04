

#include "skip_list.h"

//------------------------------------------------------------------------------

Unit::Unit(int v, int l, Unit* r, Unit* d) : val{v}, lvl{l}, right{r}, down{d}
{
	if(val < 0)		error("negative Unit value [Unit() init]");
	if(lvl < 0)		error("negative value of the number of levels [Unit() init]");
	if(lvl == 0)	error("zero value of number of levels [Unit() init]");
}

//------------------------------------------------------------------------------

//Получает количество уровней и максимальное значение списка (крайний правый)
//Хранит указатель на верхний элемент заголовочного списка (value = 0)
Skip_list::Skip_list(int lvl, int max)
{
	if(lvl < 0)		error("negative value of the number of levels [Skip_list() init]");
	if(lvl == 0)	error("zero value of number of levels [Skip_list() init]");
	//if(max <= 0)	error("the number of lists must be greater than zero [Skip_list() init]");
	if(max < 0)		error("negative value of the number of lists [Skip_list() init]");
	
	//-----------------------------Составление списков------------------------------
	
	srand( time(NULL) );
	
	//МОЖНО ТАКЖЕ СДЕЛАТЬ ЧЕРЕЗ МАССИВ УКАЗАТЕЛЕЙ В ДИНАМИЧЕСКОЙ ПАМЯТИ
	//Но тогда придётся каждый раз дополнительно искать крайний правый список от p=find(0,1) след.образом while(p->right)	p = p->right;
	vector<Unit*> vu;		//Верхушки списков (крайний верхний элемент)
	for(int i=0; i <= max; ++i)
	{
		int curr_list_lvl{lvl-1};						//Заголовочный (стартовый, крайний левый) список с максимальным кол-вом уровней
		if(i > 0)		curr_list_lvl = rand() % lvl;	//Случайное целое положительное значение в диапазоне [0; lvl)
		
		//Составляем отдельно взятый список снизу вверх (от 0+1 уровня до curr_list_lvl)
		Unit* ul{nullptr};
		for(int j=0; j <= curr_list_lvl; ++j) {
			Unit* next_down = ul;
			ul = new Unit{i, j+1, nullptr, next_down};		//Поднимаемся вверх по уровням. down == пред. перебираемому элементу
			
			//Сохраняем ссылку на самый верхний юнит заголовочного списка в текущем объекте
			if(i == 0  &&  j == curr_list_lvl)		head = ul;
		}
		
		vu.push_back(ul);
	}
	
	/*for(int i=0; i < vu.size(); ++i)
		cout << *vu[i] << '\n';
	
	cout << "\n\n";*/
	
	//-----------------------------Составление списков------------------------------
	//------------------Указание элементов справа на том же уровне------------------
	
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
	
	//------------------Указание элементов справа на том же уровне------------------
	
	if(!head)		error("head NULLPTR [Skip_list() init]");
}

//Копирующий конструктор
Skip_list::Skip_list(const Skip_list& sl)
{
	const Unit* p{sl.head};
	
	//Поиск максимального значения списка
	while(p->down)		p = p->down;	//Самый нижний
	while(p->right)		p = p->right;	//Самый правый
	int max{p->val};
	
	//-----------------------------Составление списков------------------------------
	
	vector<Unit*> vu;		//Верхушки списков (крайний верхний элемент)
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
				
				//Сохраняем ссылку на самый верхний юнит заголовочного списка в текущем объекте
				if(i == 0  &&  j ==  p->lvl-1)		head = ul;
			}
		}
		
		if(ul)		vu.push_back(ul);
	}
	
	//-----------------------------Составление списков------------------------------
	//------------------Указание элементов справа на том же уровне------------------
	
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
	
	//------------------Указание элементов справа на том же уровне------------------
	
	if(!head)		error("head NULLPTR [Skip_list() init]");
}

//Деструктор
Skip_list::~Skip_list() {
	Unit* p{head};
	
	//Поиск максимального значения списка
	while(p->down)		p = p->down;	//Самый нижний
	while(p->right)		p = p->right;	//Самый правый
	int max{p->val};
	
	while(max >= 0) {
		Unit* prev{nullptr};
		if(max>0)	prev = const_cast<Unit*>( find(max-1) );	//Верхний уровень списка предшествующего максимальному
		
		//Удаляем связи
		while(prev)		{ prev->right = 0;		prev = prev->down; }
		
		//Удаляем самый правый список (с максимальным не удалённым значением)
		//Удаление сверху вниз (когда формирование списка снизу вверх происходит)
		p = const_cast<Unit*>( find(max) );				//Верхний уровень текущего(не удалённого) максимального по значению списка
		prev = p;
		while(prev) {
			prev = prev->down;
			delete p;
			p = prev;
		}
		
		--max;
	}
}

//Копирующее присваивание
Skip_list& Skip_list::operator=(const Skip_list& sl)
{
	this->~Skip_list();		//Уничтожаем текущий список
	
	//При копировании лишь следующими двумя строками в вечном цике программа может повиснуть
	//Создаём в динамической памяти новый список и не удаляя просто копируем ссылку на его заголовочный список
	//Список из динамической памяти будет удалён при вызове деструктора текущего объекта
	//Skip_list* new_sl = new Skip_list(sl);
	//head = new_sl->head;
	
	//------------------------------------------------------------------------------
	
	const Unit* p{sl.head};
	
	//Поиск максимального значения списка
	while(p->down)		p = p->down;	//Самый нижний
	while(p->right)		p = p->right;	//Самый правый
	int max{p->val};
	
	//-----------------------------Составление списков------------------------------
	
	vector<Unit*> vu;		//Верхушки списков (крайний верхний элемент)
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
				
				//Сохраняем ссылку на самый верхний юнит заголовочного списка в текущем объекте
				if(i == 0  &&  j ==  p->lvl-1)		head = ul;
			}
		}
		
		if(ul)		vu.push_back(ul);
	}
	
	//-----------------------------Составление списков------------------------------
	//------------------Указание элементов справа на том же уровне------------------
	
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
	
	//------------------Указание элементов справа на том же уровне------------------
	
	
	if(!head)		error("head NULLPTR [Skip_list() init]");
	return *this;
}

//------------------------------------------------------------------------------

//Поиск в списке значения
//Возвращает nullptr если не было найдено
const Unit* Skip_list::find(int v) const {
	const Unit* p{head};
	
	while(p)
	{
		while(p->right)
			if(p->val > v  ||  p->val == v)		break;
			else								p = p->right;
		
		
		//Спускаемся в заголовочном списке на уровень ниже
		if(p->val != v) {
			const Unit* next{head};
			for(int i=0; i <= head->lvl - p->lvl; ++i)		next = next->down;
			p = next;
		}
		else		break;
	}
	
	return p;
}

//Поиск в списке значения на определённом уровне
//Возвращает nullptr если не было найдено
const Unit* Skip_list::find(int v, int l) const {
	const Unit* p{find(v)};
	while(p && p->lvl != l)		p = p->down;
	
	//if(p==0)	cerr << "\nNULLPTR [const Unit* find const ()] val/lvl\t" << v << ' ' << l << "\n\n";
	return p;
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
			if(pr = pr->right)		while(pr->val != lst+1)		{ ost << '\t';		++lst; }
			else					while(lst < max)			{ ost << '\t';		++lst; }
		}
		
		ost << "|\n";
		p = p->down;
	}
	
	return ost;
}