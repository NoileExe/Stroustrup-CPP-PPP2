//Вывод суммы первых N чисел

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


constexpr char end_symb = '|';
//..............................................................................
double input_check (string); //Проверяет допустимость ввода
//..............................................................................
int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите числа (точка ('.') - для отделения десятичной части)\nДля "
			"подтверждения ввода - Enter\nДля завершения ввода используйте комб"
			"инацию клавиш CTRL+Z на ввод\n\nПо завершению введите какое количе"
			"ство чисел начиная с начала требуется суммировать\n\n";
	
	vector<double> nums; //Вектор для запоминания вводимых чисел
	int n = 0; //Сюда будет записано сколько элементов от начала стоит суммировать
	double summ = 0; //Переменная для суммирования
	
	vector<double> diff_neighbours; //Вектор для запоминания вводимых чисел (разность соседних чисел)
	
	string str; //Строка для проверки значений на то яв-ся ли ввёденное Целым числом и яв-ся ли вообще числом
	
	try
	{
		cout << "Введите " << n+1 << " число ('|' для завершения ввода): ";
		while ( cin >> str || cin.eof() ) {
			if ( cin.eof() ) {
				cin.clear(); //Очищает поток символов cin
				cout << "Введите " << n+1 << " число ('|' для завершения ввода): ";
			}
			
			else if ( str.size() == 1 && str[0] == end_symb ) {
				cout << "\nВвод завершён пользователем.\n";
				cin.clear(); //Очищает поток символов cin
				break;
			}
			
			else {
				nums.push_back( input_check(str) );
				++n;
				cout << "Введите " << n+1 << " число ('|' для завершения ввода): ";
			}
		}
		
		for (int i = 1; i < nums.size(); ++i)
			diff_neighbours.push_back(nums[i-1] - nums[i]);
		
		
		
		n = -1;
		cout << "\nВведите кол-во суммируемых значений: ";
		
		while ( cin >> str || cin.eof() ) {
			if ( cin.eof() ) {
				cin.clear(); //Очищает поток символов cin
				cout << "\nВведите кол-во суммируемых значений: ";
			}
			
			else if ( str.size() == 1 && str[0] == end_symb ) {
				cout << "\nВвод завершён пользователем.\n";
				cin.clear(); //Очищает поток символов cin
				break;
			}
			
			else if (input_check(str) < 0)
				cout << "\nВведите положительное целое число.\n\nВведите кол-во"
						" суммируемых значений: ";
			
			else if (input_check(str) > nums.size())
				cout << "\nВведённое число не может быть больше кол-ва введённы"
						"х чисел.\n\nВведите кол-во суммируемых значений: ";
			
			else if (input_check(str) >= 0) { n = input_check(str); break; }
		}
		
		cin.clear(); //Очищает поток символов cin
		
		
		
		cout << "Сумма первых чисел в кол-ве " << n << " (";
		
		for (int i = 0; i < n; ++i)
			summ += nums[i];
		
		cout << ") равна " << summ << ".\n\n";
		
		
		
		for (int i = 0; i < diff_neighbours.size(); ++i)
		{
			cout << nums[i] << " - " << nums[i+1] << " = " << diff_neighbours[i] << "\n";
		}
	}
	catch (overflow_error)
	{
		cerr << "\n\n\nОшибка: overflow_error\n\n";
		press_Enter_key();
		return 1;
	}
	catch (out_of_range)
	{
		cerr << "\n\n\nОшибка: out_of_range\n\n";
		press_Enter_key();
		return 2;
	}
	catch (runtime_error& e)
	{
		cerr << "\n\n\nОшибка runtime_error: " << e.what() << "\n\n";
		press_Enter_key();
		return 3;
	}
	catch (exception& e)
	{
		cerr << "\n\n\nОшибка: " << e.what() << "\n\n";
		press_Enter_key();
		return 4;
	}
	catch (...)
	{
		cerr << "\n\n\nНеизвестное исключение!\n\n";
		press_Enter_key();
		return 5;
	}
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}
//..............................................................................
double input_check(string str)
/*Проверяем введено ли целое число (допустимость ввода)
При вводе считывается строка и посимвольно проверяет является ли введённое
целым числом, наличие недопустимых символов, а также проверяет не вышло ли
число за диапазон INT*/
{
	double num = 0;
	bool is_negative = false;	//Является ли число отрицательным
	
	string after_dot = "";		//Текст после точки
	
	//Поиск десятичной ЗПТ. При наличии отделение десятичной части от целой в разные строковые переменные
	for (int i = 0; i < str.size(); ++i) {
		
		//Cъедаем минусы из строки если они стоят в её начале. В is_negative помечаем что число отрицательное
		while ( i == 0 && str[i] == 45 ) { is_negative = true; str.erase(i,1); }
		
		//Cъедаем нули из строки если они стоят в её начале
		while ( i == 0 && str[i] == 48 )	str.erase(i,1);
		
		
		//Если единственный символ - символ остановки ввода
		if ( i == 0 && str.size() == 1 && str[i] == int(end_symb) ) {
			string err_str = "" + end_symb;
			throw err_str;
		}
		
		else if ( cin.eof() ) {
			string err_str = "Нажата комбинация CTRL+Z";
			throw err_str;
		}
		
		//Съели нули и не осталось символов - возвращаем нуль
		else if (str.size() == 0)	return 0;
		
		//i-ый символ строки равен символу десятичной ЗПТ (".")
		//(Если число не является целым)
		else if ( str[i] == '.' ) {
			if ( after_dot == "" ) { //Точка пока не встречалась в строке
				after_dot = str;
				
				if ( i == 0 ) { //Десятичная ЗПТ - первый символ (число меньше единицы)
					str = "0";
					after_dot = after_dot.substr(i+1); //Возвращает подстроку данной строки начиная с символа с указанным индексом и до конца строки
				}
				
				else {
					str.erase(i, str.size()-i);
					after_dot = after_dot.substr(i+1); //Возвращает подстроку данной строки начиная с символа с указанным индексом и до конца строки
				}
			}
			
			else {
				string err_str = "Вы ввели что-то не то (повтор десятичной ЗПТ).";
				throw runtime_error(err_str);
			}
		}
	}
	
	//Посимвольно проверяем введёную строку на то число ли введено
	for (int i = 0; i < str.size(); ++i) {
		
		//если текущий символ проверяемой строки по таблице ASCII от 0 до 9 и десятичная ЗПТ пока не была найдена
		if ( str[i] >= 48 && str[i] <= 57 )
															//тек. индекс
						//число УМНОЖИТЬ на 10^ (длина строки - (i+1))
			num = num + (str[i]-48) * pow(10, ( str.size()-(i+1) ));
			
		//Если символ не является ".", ",", "-" (минус может быть только 1ый символом в строке) или числом 0-9
		else {
			string err_str = "Вы ввели что-то не то.";
			throw runtime_error(err_str);
		}
	}
	
	//Посимвольно проверяем десятичную часть введёной строки на то число ли введено
	for (int i = 0; i < after_dot.size(); ++i) {
		
		//если текущий символ проверяемой строки по таблице ASCII от 0 до 9 и десятичная ЗПТ была найдена
		if ( after_dot[i] >= 48 && after_dot[i] <= 57 )
											//тек. индекс
							//число УМНОЖИТЬ на 10^(-i)
			num = num + (after_dot[i]-48) / pow(10, i+1);
		
		else {
			string err_str = "Вы ввели что-то не то.";
			throw runtime_error(err_str);
		}
	}
	
	//2147483647
	//2144444444
	//2199999999
	
	//Значение вне диапазона int
	if ( isinf(num) ) {
		string err_str = "Число за пределами диапазона DOUBLE и равняется бесконечности.";
		throw overflow_error(err_str);
	}
	
	//Если 1ый символ - символ МИНУС
	else if ( is_negative )	return num*(-1);
	
	else	return num; //Если всё допустимо - передаём данное число как корректно введённое
}
