//Данная программа является решение задания 6 4ой главы
//Сравнение всех поданых на ввод чисел на максимальное и минимальное среди них

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите числа (ТОЧКА для отделения десятичной части), после ввода "
		 << "каждого нажимая Enter. После ввода числа будут сравниваться с ране"
		 << "е введёнными и будут вычисляться наименьшее и наибольшее из введён"
		 << "ных.\nДля завершения работы программы нажмите комбинацию CTRL+Z и "
		 << "затем Enter (то же сделает ввод любого символа отличного от числа)"
		 << "\n\n";
	
	
	double min = -1;
	double max = 1;
	
	/*for (double num; cin >> num; ) {
		if (num < min) {
			min = num;
			cout << num << " - Наименьшее число среди введённых (min)\n\n";
		}
		else if (num > max) {
			max = num;
			cout << num << " - Наибольшее число среди введённых (max)\n\n";
		}
		else cout << num << "\n\n";
	}*/
	
	vector<double> nums;
	
	for (double one_num; cin >> one_num; ) {
		nums.push_back(one_num);
		if (nums.size() == 1) {
			min = nums[0];
			max = nums[0];
			cout << nums[nums.size()-1] << " [" << nums.size()-1 << "]\n\n";
		}
		else if (nums[nums.size()-1] < min) {
			min = nums[nums.size()-1];
			cout << nums[nums.size()-1] << " [" << nums.size()-1 << "] - Наимен"
				 << "ьшее число среди введённых (min)\n\n";
		}
		else if (nums[nums.size()-1] > max) {
			max = nums[nums.size()-1];
			cout << nums[nums.size()-1] << " [" << nums.size()-1 << "] - Наибол"
				 << "ьшее число среди введённых (max)\n\n";
		}
		else cout << nums[nums.size()-1] << " [" << nums.size()-1 << "]\n\n";
	}
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}
