#include "varconst.h"

//------------------------------------------------------------------------------

//инициализация констант
/*Symbol_table::Symbol_table()
{
	vector_names.push_back( Variable("pi", 3.1415926535, true) );
	vector_names.push_back( Variable("e", 2.7182818284, true) );
	vector_names.push_back( Variable("k", 1000, true) );
}*/

void Symbol_table::table_out() //Вывод на экран всех констант и переменных подряд
{
	for (int i = 0; i < vector_names.size(); ++i) {
		cout << '\t' << i+1 << ". "; 
		
		if (vector_names[i].constant)		cout << "const ";
		else							cout << "var   ";
		
		cout << ' ' << vector_names[i].name << " = " << vector_names[i].value << ";\n";
	}
}

double Symbol_table::get(string s)
//получить значение существующей переменной
//на вход: имя переменной
//на выходе: значение переменной с указанным именем (если таковая существует)
{
	for (int i = 0; i < vector_names.size(); ++i)
		if (vector_names[i].name == s) return vector_names[i].value;
	
	error ("попытка получить значение необъявленной переменной ( Symbol_table::get() )");
}

void Symbol_table::set(string s, double d)
//изменить (установить) значение существующей переменной
//на вход: имя переменной и её новое значение
{
	for (int i = 0; i < vector_names.size(); ++i)
		if ( vector_names[i].constant && vector_names[i].name == s )
			error ("попытка изменить константу ( Symbol_table::set() )");
		
		else if ( vector_names[i].name == s ) {
			vector_names[i].value = d;
			return;
		}
	
	error ("попытка установить значение для необъявленной переменной ( Symbol_table::set() )");
}

bool Symbol_table::is_declared(string s)
//проверка существует ли уже переменная с таким именем
//на вход: имя переменной
//на выходе: true - если переменная с таким именем существует / false - если нет
{
	for (int i = 0; i < vector_names.size(); ++i)
		if ( vector_names[i].name == s )	return true;
	
	return false;
}

void Symbol_table::define(string name, double d, bool cnst)
//добавление не объявленной ранее переменной/константы в массив переменных
//на вход: имя несуществующей переменной, её значение и яв-ся ли она константой или нет (true - если да)
{
	//Если такой переменной/константы ещё не существует в массиве
	if ( is_declared(name) == false )
		vector_names.push_back(Variable(name, d, cnst));
	
	//Если переменная с таким именем уже существует..
	else
		error ("попытка объявления уже существующей переменной ( Symbol_table::define() )"); //..ошибка
		//set(string name, double d); //..изменяем её значение
}