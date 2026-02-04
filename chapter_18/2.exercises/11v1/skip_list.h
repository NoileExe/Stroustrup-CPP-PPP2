

#include <std_lib_facilities.h>
#include <ctime> //Для рандомизации по текущему времени (секунде)

//------------------------------------------------------------------------------

struct Unit {
	Unit(int v, int l, Unit* r = nullptr, Unit* d = nullptr);
	
	int val;		//Значение текущей ячейки списка
	int lvl;		//Текущий уровень списка
	Unit* right;	//Элемент правее (со значение больше текущего)
	Unit* down;		//Элемент ниже
};


class Skip_list {
public:
	//Получает количество уровней и максимальное значение списка (крайний правый)
	//Хранит указатель на верхний элемент заголовочного списка (value = 0)
	Skip_list(int lvl, int max = 0);
	Skip_list(const Skip_list& sl);		//Копирующий конструктор
	~Skip_list();
	
	Skip_list& operator=(const Skip_list& sl);	//Копирующее присваивание
	
	const Unit* find(int v) const;			//Поиск в списке значения
	const Unit* find(int v, int l) const;	//Поиск в списке значения на определённом уровне
	
	
	/*
	void insert(int v);		//Вставляет список со значением v после значения меньше v, но
							// обязательно перед списком со значением больше v
	void erase(int v);		//Удаляет список со значением v меня ссылки списка перед списком со значением v
	*/
	
	const Unit* header() const { return head; }
	int level() const { return head->lvl; }

private:
	Unit* head{nullptr};		//Указатель на верхний элемент (макс. уровень) заголовочного списка (val = 0)
};

//Вывод списка с пропусками по ссылке в поток ost
ostream& operator<<(ostream& ost, const Skip_list& s);