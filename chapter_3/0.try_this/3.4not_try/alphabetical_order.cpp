//Ввод и сравнение имён, указание очерёдности в алфавитном порядке

#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Пожалуйста, введите два имени (после ввода каждого нажмите Enter):\n";
	string first;
	string second;
	cin >> first >> second; //Считываем две строки
	cout << '\n';
	
	if (first==second) cout << "имена совпадают\n\n";
	if (first < second)
	   cout << first << " предшествует " << second << " в алфавитном порядке:\n\n"
			<< first << '\n' << second << "\n\n";
	if (first > second)
	   cout << first << " следует за " << second << " в алфавитном порядке:\n\n"
			<< second << '\n' << first << "\n\n";
	
	cin.get();
	cout << "\n\nНажмите Enter чтобы закрыть программу";
	cin.get();
	return EXIT_SUCCESS;
}
