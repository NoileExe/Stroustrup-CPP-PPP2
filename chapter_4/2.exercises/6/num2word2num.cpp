//Данная программа переводит число в слово и наоборот

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>
#include <cstring>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Данная программа переводит число в слово и наоборот.\nДля начала в"
		 << "ведите целое число от 0 до 9 или число словом в том же диапазоне, "
		 << "например, zero или six.\nПосле ввода нажмите Enter для подтвержден"
		 << "ия\n\nДля завершения работы программы нажмите комбинацию клавиш CT"
		 << "RL+Z и затем Enter\n\n";
	
	//vector<string> wnums (10);
	//wnums[0]= "zero";
	//wnums[1]= "one";
	
	//vector<string> wnums;
	//wnums.push_back("zero");
	//wnums.push_back("one");

	vector<string> wnums = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	
	for (string word; cin >> word; ) {
		
		for (int i=0; i<10; ++i) {
			if (word==wnums[i] && word.size()<8)
				cout << i << "\n\n";
			else if (i==word[0]-48 && word.size()<2)
			//если i = первый символ в строке минус 48 (т.к. код 0 в ASCII = 48)
				cout << wnums[i] << "\n\n";
		}
	}
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}
