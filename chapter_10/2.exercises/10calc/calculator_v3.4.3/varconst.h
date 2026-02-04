#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

struct Variable { //Структура для представления именованных переменных и констант
	string name;
	double value;
	bool constant;
	
	Variable(string n, double v)
		:name(n), value(v), constant(false)	{ }
	Variable(string n, double v, bool c)
		:name{n}, value{v}, constant{c}		{ }
};


class Symbol_table {
public:
	Symbol_table() { }   //создаём Symbol_table, который читает из потока ввода cin лексемы
	
	void table_out();				//Вывод на экран всех констант и переменных
	double get(string s);			//получить значение существующей переменной
	void set(string s, double d);	//изменить (установить) значение существующей переменной
	bool is_declared(string s);		//проверка существует ли уже переменная с таким именем
	void define(string name, double d, bool cnst);	//добавление не объявленной ранее переменной/константы в массив переменных
private:
	vector<Variable> vector_names;
	//вектор для хранения всех именованных переменных и констант, а так же обращения к ним
};