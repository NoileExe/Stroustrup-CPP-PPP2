

#include <cstdlib>
#include <iostream>
#include <ios>
#include <string>
#include <limits>

#ifdef WITHOUT_STD_LIB_FACILITIES_H
	#include <sstream>
	#include <stdexcept>
#endif

//------------------------------------------------------------------------------

inline void clear_screen()
{
//#ifdef WINDOWS
//#ifdef _MSC_VER
#ifdef _WIN32
	std::system("cls");
#else
	// Assume POSIX
	std::system("clear");
#endif
}

/*
Добивается от пользователя ответа на вопрос в передаваемой строке question;
	неверно введённый ответ игнорирует считывая всю строку и предлагает повторно ввести ответ.
	Возвращает ответ пользователя ('да' или 'нет') в виде true или false
*/
inline bool Y_or_N(const std::string& question)
{
	//Считываем остаток строки до встречи перехода на новую строку
	for(char ch = ' '; ch != '\n'; std::cin.get(ch))
		if(std::cin.fail())
			std::cin.clear(std::ios_base::goodbit);
	
	std::string choice = "";
	
	std::cout << "\n\n\n\n" << question << " (enter 'yes' or 'no')\n\n"; //(введите 'да' или 'нет')
	while( choice != "yes" && choice != "no" )
	{
		std::cout << "> ";
		
		std::string tmp {""};
		std::getline(std::cin, tmp);
		
		if(std::cin.good()  &&  (tmp == "yes" || tmp == "no"))
			choice = tmp;
		else
			std::cin.clear(std::ios_base::goodbit);
	}
	
	//Возвращаем ответ введённый пользователем
	if (choice == "yes")	return true;
	else					return false;
}

//Просьба пользователю нажать клавишу Enter
inline void press_Enter_key(bool showMessageFirst = false)
{
	// Если в буфере что-то осталось (например, после cin >>), очищаем его
	if (std::cin.fail())
		std::cin.clear(std::ios_base::goodbit);
	
	char ch{ ' ' };
	
	if (showMessageFirst)
	{
		std::cout << "\nPlease press Enter key to continue..." << std::endl;
		std::cin.get(ch);
	}
	
	
	while(ch != '\n')
	{
		// Игнорируем всё до конца строки
		
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		
		std::cout << "\nPlease press Enter key to continue..." << std::endl;
		
		// Ждем нажатия Enter
		std::cin.get(ch);
	}
}

//------------------------------------------------------------------------------

//Сборка без указания std_lib_facilities.h в исходных файлах в качестве включения
#ifdef WITHOUT_STD_LIB_FACILITIES_H
	inline void keep_window_open()
	{
		std::cin.clear();
		std::cout << "Please enter a character to exit\n";
		
		std::string str;
		while(true)
		{
			std::getline(std::cin, str);
			if(std::cin.good()  &&  str.size()  &&  str[0] != '\n')
				break;
			else
				std::cin.clear(std::ios_base::goodbit);
		}
	}

	inline void keep_window_open(const std::string& s)
	{
		if (s=="")		return;
		
		std::cin.clear();
		std::cin.ignore(120,'\n');
		for (;;) {
			std::cout << "Please enter " << s << " to exit\n";
			std::string ss;
			while (std::cin >> ss && ss!=s)
				std::cout << "Please enter " << s << " to exit\n";
			return;
		}
	}

	// error() simply disguises throws:
	inline void error(const std::string& s)
	{
		throw std::runtime_error(s);
	}

	inline void error(const std::string& s, const std::string& s2)
	{
		error(s + s2);
	}

	inline void error(const std::string& s, int i)
	{
		std::ostringstream os;
		os << s << ": " << i;
		error(os.str());
	}
#endif