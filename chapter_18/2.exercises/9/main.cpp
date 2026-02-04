
//Странное поведение с символами: не выводится адрес
//По выводу понятно что данные одинаковых типов располагаются друг за другом как в коде при объявлении переменных
//Опять же ситуация с символами выглядит интересно (в памяти 2 символа подряд, если объявлены рядом)


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

const string mem_table = "            ________________\n"
						 "Memory      |              |\n"
						 "allocation  |     Code     |\n"
						 "scheme      |              |\n"
						 "            |--------------|\n"
						 "            |  Static data |\n"
						 "            |--------------|\n"
						 "            |              |\n"
						 "            |    Dynamic   |\n"
						 "            |    memory    |\n"
						 "            |              |\n"
						 "            |--------------|\n"
						 "            |     Stack    |\n"
						 "            |______________|\n";

//------------------------------------------------------------------------------

//Статические данные
constexpr char ch1 = 'a';
constexpr char ch2 = 'a';

const int i1 {8};
const int i2 {8};

int gai[2] {0,1};

double d1 {2.3};
double d2 {2.3};

double dg {2.3};


template <typename T>
unsigned int ptr2int (T* a)
{
	unsigned int d {0}; //т.к. его верхнее значение равно 4 294 967 295 (максимальный адрес FFFF FFFF)
	
	if (a) {
		ostringstream oss;
		oss << a;
		
		istringstream iss { oss.str() };
		iss >> hex >> d;
		if (!iss)		error("problem reading address");
	}
	
	else		error("nullptr ( pointer2int() )");
	
	return d;
}


//Сравнение двух адресов
//Возвращает отрицательное число если второй больше (старше)
//Возвращает положительное число если перый больше (старше)
//Возвращает нуль если адреса равны
template <typename T>
int addr_cmp(T* a1, T* a2)
{
	int cmp = reinterpret_cast<int>(a1)-reinterpret_cast<int>(a2);
	
	if (cmp < 0)		return -1;		//Второй адрес старше
	else if (cmp > 0)	return 1;		//Первый адрес старше
	else				return 0;		//Равные аргументы
}

//------------------------------------------------------------------------------

//Сравнение двух адресов
//Возвращает строку указывающую в какую сторону произошло увеличение адреса памяти между a1 и a2
template <typename T>
string grow_addr(T* a1, T* a2)
{
	int cmp = addr_cmp(a1, a2);
	
	string s;
	if (cmp < 0)		s = "grows up";		//Второй адрес старше
	else if (cmp > 0)	s = "grows down";	//Первый адрес старше
	else				s = "equal";		//Равные аргументы
	
	return s;
}


void check_mems(int var1, int var2)
{
	const char* pch1 = &ch1;
	const char* pch2 = &ch2;
	const int* cpint1 = &i1;
	const int* cpint2 = &i2;
	double* pdbl1 = &d1;
	double* pdbl2 = &d2;
	
	
	cout << "STATIC DATA (global constants & variables)\n\n" << left;
	cout << setw(20) << "2 constexpr chars: "	<< setw(9) << grow_addr(&ch1, &ch2)			<< "\t(" << pch1 << ", " << pch2 << ")\n";
	cout << setw(20) << "2 const ints: "		<< setw(9) << grow_addr(cpint1, cpint2)		<< "\t(" << cpint1 << ", " << cpint2 << ")\n";
	cout << setw(20) << "2 ints (array): "		<< setw(9) << grow_addr(&gai[0], &gai[1])	<< "\t(" << &gai[0] << ", " << &gai[1] << ")\n";
	cout << setw(20) << "2 doubles: "			<< setw(9) << grow_addr(pdbl1, pdbl2)		<< "\t(" << pdbl1 << ", " << pdbl2 << ")\n";
	cout << setw(20) << "2 doubles EQU: "		<< setw(9) << grow_addr(pdbl1, pdbl1)		<< "\n";		//EQU
	cout << "\n\n";
	
	//------------------------------------------------------------------------------
	
	char* ch = new char[] {'a', 'a'};
	int*  ii = new int[]  {8, 8};
	double* num1 = new double {8.0};
	double* num2 = new double {8};
	
	cout << setw(20) << "DYNAMIC MEMORY (operator 'new')\n\n";
	cout << setw(20) << "2 chars (array): "		<< setw(9) << grow_addr(&ch[0], &ch[1])	<< "\t(" << &ch[0] << ", " << &ch[1] << ")\n";
	//cout << "2 chars (array): " << grow_addr(ch, ch+1) << "\t(" << ch << ", " << ch+1 << ")\n";
	cout << setw(20) << "2 ints (array): "		<< setw(9) << grow_addr(&ii[0], &ii[1])	<< "\t(" << ii << ", " << ii+1 << ")\n";
	cout << setw(20) << "2 doubles: "			<< setw(9) << grow_addr(num1, num2)		<< "\t(" << num1 << ", " << num2 << ")\n";
	cout << "\n\n";
	
	delete[] ch;
	delete[] ii;
	delete num1;
	delete num2;
	
	//------------------------------------------------------------------------------
	
	constexpr char abc1 = 'a';
	constexpr char abc2 = 'a';
	
	const int n1 {8};
	const int n2 {8};
	
	int ai[2] {0,1};
	
	int var3{88};
	int var4{88};
	
	pch1 = &abc1;
	pch2 = &abc2;
	cpint1 = &n1;
	cpint2 = &n2;
	int* pint1 = &var1;
	int* pint2 = &var2;
	int* pint3 = &var3;
	int* pint4 = &var4;
	
	
	cout << setw(20) << "STACK (function's arguments and local variables)\n\n";
	cout << setw(20) << "2 constexpr chars: "	<< setw(9) << grow_addr(pch1, pch2)		<< "\t(" << pch1 << ", " << pch2 << ")\n";
	cout << setw(20) << "2 const ints: "		<< setw(9) << grow_addr(cpint1, cpint2)	<< "\t(" << cpint1 << ", " << cpint2 << ")\n";
	cout << setw(20) << "2 ints (array): "		<< setw(9) << grow_addr(&ai[0], &ai[1])	<< "\t(" << &ai[0] << ", " << &ai[1] << ")\n";
	
	cout << setw(20) << "2 ints var1 & var2: " << setw(9) << grow_addr(pint1, pint2) << "\t(" << pint1 << ", " << pint2 << ")\n";
	cout << setw(20) << "2 ints var2 & var3: " << setw(9) << grow_addr(pint2, pint3) << "\t(" << pint2 << ", " << pint3 << ")\n";
	cout << setw(20) << "2 ints var3 & var4: " << setw(9) << grow_addr(pint3, pint4) << "\t(" << pint3 << ", " << pint4 << ")\n";
	cout << setw(20) << "2 ints var1 & var4: " << setw(9) << grow_addr(pint1, pint4) << "\t(" << pint1 << ", " << pint4 << ")\n";
	
	cout << setw(20) << "2 ints var1 & var2: " << setw(9) << grow_addr(&var1, &var2) << "\t(" << &var1 << ", " << &var2 << ")\n";
	cout << setw(20) << "2 ints var2 & var3: " << setw(9) << grow_addr(&var2, &var3) << "\t(" << &var2 << ", " << &var3 << ")\n";
	cout << setw(20) << "2 ints var3 & var4: " << setw(9) << grow_addr(&var3, &var4) << "\t(" << &var3 << ", " << &var4 << ")\n";
	cout << setw(20) << "2 ints var1 & var4: " << setw(9) << grow_addr(&var1, &var4) << "\t(" << &var1 << ", " << &var4 << ")\n";
	cout << "\n\n";
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n" << mem_table << "\n\n\n\n";
			check_mems(8, 8);
			cout << "\n\n" << mem_table << "\n\n\n\n";
			
			double d0{8.8};
			double* pd0 = &d0;
			double* pd = new double {7.77};
			
			//Переменная из глобальной области (статические данные) и определённая оператором new (динамическая память)
			cout << "STATIC" << "\t\t" << "DYNAMIC" << "\n";
			cout << &dg << '\t' << pd << "\n";
			cout << ptr2int(&dg) << '\t' << ptr2int(pd) << "\n";
			if ( addr_cmp(&dg, pd) < 0 )
				cout << "the STATIC data area comes before the DYNAMIC memory area\n\n";
			else if ( addr_cmp(&dg, pd) > 0 )
				cout << "the DYNAMIC memory area comes before the STATIC data area\n\n";
			
			
			
			//Переменная из глобальной области (статические данные) и локальная переменная (стек)
			cout << "STATIC" << "\t\t" << "STACK" << "\n";
			cout << &dg << '\t' << pd0 << "\n";
			cout << ptr2int(&dg) << '\t' << ptr2int(pd0) << "\n";
			
			if ( addr_cmp(&dg, pd0) < 0 )
				cout << "the STATIC data area comes before the STACK\n\n";
			else if ( addr_cmp(&dg, pd0) > 0 )
				cout << "the STACK area comes before the STATIC data area\n\n";
			
			
			
			//Переменная определённая оператором new (динамическая память) и локальная переменная (стек)
			cout << "DYNAMIC" << "\t\t" << "STACK" << "\n";
			cout << pd << '\t' << pd0 << "\n";
			cout << ptr2int(pd) << '\t' << ptr2int(pd0) << "\n";
			
			if ( addr_cmp(pd, pd0) < 0 )
				cout << "the DYNAMIC memory area comes before the STACK\n\n";
			else if ( addr_cmp(pd, pd0) > 0 )
				cout << "the STACK area comes before the DYNAMIC memory area\n\n";
			
			
			delete pd;
			
			keep_window_open();
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}