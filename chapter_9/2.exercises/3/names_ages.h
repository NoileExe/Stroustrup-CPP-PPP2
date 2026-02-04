#include <std_lib_facilities.h>

namespace names_n_ages { //names_n_ages

	class Name_pairs {
		vector<string> name;
		vector<double> age;
		
		void read_names();	//считывает имя и возвращает строку
		void read_ages();	//предлагает ввести и считывает возраст
							//для каждого имени в вектор age
	public:
		Name_pairs() {}		//Конструктор по умолчанию
		
		void read_data();	//работа с read_names() (заполнение при его помощи вектора name)
							//и read_ages()

		void sort();		//упорядочивает name в алфавитном порядке и
							//соответствующе реорганизовывает вектор age

		int name_size() const { return name.size(); }	//Возвращает размер вектора name на момент вызова
		int  age_size() const { return  age.size(); }	//Возвращает размер вектора age на момент вызова
		
		string one_name(int i) const { return name[i]; }	//Возвращает i-ый элемент вектора name
		double  one_age(int i) const { return  age[i]; }	//Возвращает i-ый элемент вектора age

		void operator= (const Name_pairs& b);
	};

	bool operator==(const Name_pairs& a, const Name_pairs& b);
	bool operator!=(const Name_pairs& a, const Name_pairs& b);
	ostream& operator<<(ostream& os, const Name_pairs& np);


} //names_n_ages