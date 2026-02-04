//Данная программа определяет моду (наиболее часто повторяющееся число/числа) для ряда введённых чисел

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите положительные числа (ТОЧКА для отделения десятичной части)"
		 << ", после ввода каждого нажимая Enter. После ввода числа будут сравн"
		 << "иваться с ранее введёнными и будут вычисляться наименьшее и наибол"
		 << "ьшее из введённых.\nДля завершения работы программы нажмите комбин"
		 << "ацию CTRL+Z и затем Enter (то же сделает ввод любого символа отлич"
		 << "ного от числа)\n\n";
	
	vector <double> nums;
	double min = 0;
	double max = 0;
	
	int curr_repeats = 0;	//Для подсчета количества повторяющихся чисел для данного проверяемого числа
	int max_repeats = 1;	//Максимальное достигнутое количество повторений одного числа
	vector<int> mode;		//Индексы чисел обозначающих моду в массиве nums
	
	for (double one_num; cin >> one_num; ) {
		while (one_num < 0) {
			cout << "\nМОЖНО ВВОДИТЬ ТОЛЬКО ПОЛОЖИТЕЛЬНЫЕ ЧИСЛА!\n\n";
			cin >> one_num;
		}
		
		nums.push_back(one_num);
		cout << nums[nums.size()-1] << " [" << nums.size()-1 << "]";
		
		if (nums.size() == 1) { min = nums[0]; max = nums[0]; }
		else if (nums[nums.size()-1] < min) {
			min = nums[nums.size()-1];
			cout << " - Наименьшее число среди введённых (min)";
		}
		else if (nums[nums.size()-1] > max) {
			max = nums[nums.size()-1];
			cout << " - Наибольшее число среди введённых (max)";
		}
		
		cout << "\n\n";
		
		
		
		for (int i = 0; i<nums.size(); ++i) { //Поиск мод
			
			//Вычисляем колво повторов в массиве текущего элемента i
			curr_repeats = 1;
			for (int j = i+1; j<nums.size(); ++j)
				if (nums[j] == nums[i]) ++curr_repeats;
			
			//Если это число уже является одной из мод, то обнуляем результаты предыдущего цикла
			for (int j = 0; j < mode.size(); ++j)
				if (mode.size() > 0 && nums[i] == nums[ mode[j] ]) 
					curr_repeats = 1;
			
			if (curr_repeats > max_repeats && curr_repeats != 1) { //Если найден новый рекордсмен по колву повторов
				max_repeats = curr_repeats;
				mode.clear();
				mode.push_back(i); //Делаем его первым и единственным элементом в массиве мод
			}
			else if (curr_repeats == max_repeats && curr_repeats != 1) //Если одинаковое кол-во повторов у разных чисел
				mode.push_back(i); //Запомиаем ещё одну моду
		}
		
		
		
		if (mode.size() > 1) { //Если несколько мод
			cout << "МОДОЙ среди всех введённых значений являются: " << nums[ mode[0] ];
			for (int i = 1; i < mode.size(); ++i) //Выводим все моды на экран
				cout << ", " << nums[ mode[i] ];
		}
		else if (mode.size() == 1) //Если одна мода
			cout << "МОДОЙ среди всех введённых значений является: " << nums[ mode[0] ];
		else if ( mode.empty() ) //Массив пуст? - Моды нет
			cout << "Не удалось найти моду ряда чисел. Видимо все введённые числа различны";
		
		cout << ".\n\n";
		
		max_repeats = 1;
		mode.clear(); //очищаем вектор. Ниже аналогичные решения
		//mode.erase(mode.begin(), mode.end());
		/*for (int i = 0; i <= mode.size(); ++i)
			mode.pop_back();*/
	}
	
	cout << "\n\n";
	
	press_Enter_key();
	return EXIT_SUCCESS;
}
