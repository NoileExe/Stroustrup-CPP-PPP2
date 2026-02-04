//Данная программа вычисляет и выводит все первые N простых чисел от 1 до 2 000 000 000

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Данная программа вычисляет и выводит первые N простых чисел от 1 д"
		 << "о 2`147`483`646.\n\n";
	
	vector<int> prime_nums; //Вектор простых чисел
	int N = 0;

TryAgain:
	cout << "Сколько простых чисел вам нужно найти: ";
	cin >> N;
	if (N < 1) {
		cout << "\nОШИБКА! Введённое число должно быть целым и больше единицы\n\n";
		while (cin.get() != '\n') cin.clear(); //Очищает поток символов cin
		goto TryAgain;
	}
	
	if (N > 10000)
		cout << "\nПридётся подождать, это довольно долго и вам может не хватить ресурсов ПК!\n\n";
		
	for (int i = 1; i<2147483646 && prime_nums.size()<N; ++i) {
		for (int j = 1; j<=i; ++j) {
			if ( (i == 1) || ((j > 1) && ((i%j) == 0) && (j < i)) )
			//Если текущее число единица ИЛИ j не единица И числа делятся без остатка И j меньше (не равно) i
				break;
			else if ( (i > 1) && (j == i) )
				prime_nums.push_back(i);
		}
	}
	
	if (prime_nums.size()<N) {
		cout << "\nОШИБКА! Введённое кол-во выходит за рамки от 1 до  2`000`000"
			 << "`000. Будут выведены не все значения\n\n";
	}
	
	cout << "\nПростые числа в кол-ве N = " << N << ":\n";
	
	for (int i = 0; i<prime_nums.size(); ++i)
		cout << prime_nums[i] << "\n";
	
	press_Enter_key();
	return EXIT_SUCCESS;
}
