/*
	Данная программа находит сумму всех расстояний, наибольшее и наименьшее
	расстояние между 2мя соседними городами, среднее расстояние между 2мя соседними
*/

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


//Объявление функций
string minmax(vector<double>);
void mean(vector<double>);
void route(vector<double>, vector<string>);

int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Данная программа находит общее расстояние, наибольшее и наименьшее"
		 << " расстояния между двумя соседними городами, а также среднее рассто"
		 << "яние между двумя соседними городами. Считается что все данные ввод"
		 << "ятся в километрах\n\nВводите числа (ТОЧКА для отделения десятичной"
		 << " части) и названия городов пунктов назначения (БЕЗ ПРОБЕЛОВ), для "
		 << "подтверждения ввода каждого нажмите Enter;\n\nПример ввода:\n10.1S"
		 << "ochi\n10.1 Sochi\n10.1 <нажатие ENTER> Goryachiy_kluch\n\nДля заве"
		 << "ршения ввода нажмите CTRL+Z и затем Enter\n\n";

	vector<double> nums;	//Вектор для хранения введённых значений расстояний
	vector<string> cities;	//Вектор для хранения введённых названий городов
	double summ = 0;		//summ - cумма всех введенных значений
	int min = 0;			//Индексы минимального и максимального значений
	int max = 0;
	
	string curr_city = "";
	double vvod = 0;
	cout << "Введите город отправления: ";
	cin >> curr_city;
	cities.push_back(curr_city);
	//nums.push_back(0);
	
	cout << "\nВведите расстояние до города назначения и его название:\n";
	for ( ; cin >> vvod >> curr_city; )
	//Считываем расстояния и названия городов на ввод до нажатия CTRL+Z
	{  
		nums.push_back(vvod);
		//Добавляем число в конец вектора как новый элемент
		cities.push_back(curr_city);
		//Добавляем название города в конец вектора как новый элемент
		
		summ = summ + nums[nums.size()-1]; //Суммируем все значения
		cout << "\nОбщее расстояние: " << summ << " км";
		
		cout << "\nРасстояние от " << cities[cities.size()-2]
			 << " [" << cities.size()-2 << "] до "
			 << cities[cities.size()-1] << " ["
			 << cities.size()-1  << "] равно "
			 << nums[nums.size()-1] << " км";
		
		curr_city = minmax(nums);
		//Делаем проверку числа на min/max только если размер массива больше единицы
		if (nums.size() > 1)
		{
			if (curr_city=="min")
			{
				cout << "\nРасстояние является наименьшим среди введённых (min)";
				min = nums.size()-1;
			}
			else if (curr_city=="max")
			{
				cout << "\nРасстояние является наибольшим среди введённых (max)";
				max = nums.size()-1;
			}
		}
		
		route(nums, cities);
		
		cout << "\n\nВведите расстояние до города назначения и его название:\n";
	}
	
	cout << "\nОбщее расстояние: " << summ << " км";
	
	cout << "\nНаименьшее расстояние между 2мя соседними городами " 
		 << cities[min] << " [" << min << "] и "
		 << cities[min+1] << " [" << min+1 << "] равно "
		 << nums[min] << " км";
	cout << "\nНаибольшее расстояние между 2мя соседними городами " 
		 << cities[max] << " [" << max << "] и "
		 << cities[max+1] << " [" << max+1 << "] равно "
		 << nums[max] << " км";
	
	mean(nums);
		 
	route(nums, cities);
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}

string minmax(vector<double> v)
{
	double val = v[v.size()-1];
	//Текущий обрабатываемый элемент для проверки на min/max
	
	sort(v.begin(), v.end());
	if (val <= v[0]) return "min";
	
	else if (val >= v[v.size()-1]) return "max";
	
	else return "no";
}

void mean(vector<double> nums)
{
	int sz = nums.size();
	
	double val = 0;
	for (int i = 0; i < sz; ++i)
		val += nums[i];
	
	val /= sz;
	
	cout << "\nСреднее расстояние между 2мя соседними городами равно "
			 << val << " км\n";
}

void route(vector<double> nums, vector<string> names)
{
	cout << "\n\n";
	for (int i = 0; i < names.size(); ++i)
		cout << "[" << i << "] " << names[i] << '\n';
	
	cout << "\n [0]";
	for (int i = 0; i < nums.size(); ++i)
		cout << "---" << round(nums[i]*10)/10 << "---[" << i+1 << ']';
	
	cout << "\n\n";
}
