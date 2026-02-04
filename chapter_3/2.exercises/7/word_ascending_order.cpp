//Ввод слов и выведение на экран их в порядке расположения по алфавиту

#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Данная программа выводит слова в порядке расположения по алфавиту "
		 << "через запятую\n\nПожалуйста, "
		 << "введите три слова (после ввода каждого нажмите Enter):\n";

	//вводимые слова
	string word1 = "";
	string word2 = "";
	string word3 = "";
	
	string buff4 = ""; //буфер обмена
	cin >> word1 >> word2 >> word3;
	
	if (word1 > word2)
	{
		buff4 = word1;
		word1 = word2;
		word2 = buff4;
	}
	
	if (word1 > word3)
	{
		buff4 = word1;
		word1 = word3;
		word3 = buff4;
	}
	
	if (word2 > word3)
	{
		buff4 = word2;
		word2 = word3;
		word3 = buff4;
	}
	
	cout << '\n' << word1 << ", " << word2 << ", " << word3;
	
	keep_window_open();
	return EXIT_SUCCESS;
}
