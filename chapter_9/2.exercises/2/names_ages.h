#include <std_lib_facilities.h>

class Name_pairs {
	vector<string> name;
	vector<double> age;
	
	void read_names();	//считывает имя и возвращает строку
	void read_ages();	//предлагает ввести и считывает возраст
								 //для каждого имени в вектор age
public:
	//Name_pairs();		//Конструктор по умолчанию
	
	void read_data();	//работа с read_names() (заполнение при его помощи вектора name)
						//и read_ages()

	void print();		//выводит пары name[i], age[i] по одной
						//на строку в порядке определённым вектором name

	void sort();		//упорядочивает name в алфавитном порядке и
						//соответствующе реорганизовывает вектор age
};
