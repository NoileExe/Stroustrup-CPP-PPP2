/*Данная программа принимает на ввод пару Имя Возраст, сверяет с уже внесёнными
элементами и в случае совпадения выводит ошибку. Так же по окончанию работы при
вводе "NoName 0" выводит все введённые пары Имя Возраст*/

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


class Name_value {
public:
	string name;		//что за символ
	int age;	 //для чисел: значение 
	//Name_value(string str)	//объект класса Token из символа
		//:name(str), age(0) { }
	Name_value(string str, int val)	 //объект класса Token из символа и числа double
		:name(str), age(val) { }
};

int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите через пробел (или нажимая Enter после ввода каждого из эле"
		 << "ментов) данные для пары ''ИМЯ ВОЗРАСТ''; для подтверждения ввода н"
		 << "ажмите Enter.\n\nДля завершения ввода и получения на экран всех ра"
		 << "нее введённых пар ''ИМЯ ВОЗРАСТ''; для выхода введите ''NoName 0''.\n\n";

	vector<Name_value> data_store; //вектор для запоминания имён и возраста соответствующего имени
	
	Name_value input("NoName", 0);
	
	cout << "Введите Имя и Возраст:\n";
	
	for ( ; cin >> input.name >> input.age; ) {
		if (input.name == "NoName" && input.age == 0) {
			cout << "Ввод завершён пользователем.\n\n";
			break;
		}
		
		for (int i = 0; i < data_store.size(); ++i) {
			if (input.name == data_store[i].name) {
				cout << "ОШИБКА! Имя " << input.name << " уже есть в списке имён под №"
					 << i+1 << ".\nПопробуйте снова.\n\n";
				break;
			}
			else if ( i == (data_store.size()-1) ) {
				data_store.push_back(input);
				cout << "\n\nВведите Имя и Возраст:\n";
				break;
			}
		}
		
		if (data_store.size() == 0) {
			data_store.push_back(input);
			cout << "\n\nВведите Имя и Возраст:\n";
		}
	}
	
	for (int i = 0; i < data_store.size(); ++i)
		cout << "[" << i+1 << "] " << data_store[i].name << " " << data_store[i].age << '\n';
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}
