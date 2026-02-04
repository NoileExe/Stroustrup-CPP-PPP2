
#include <std_lib_facilities.h>


//--------------------------------------------- Строка <-> Число ---------------------------------------------

							  // 1    5    10    50    100   500   1000
const vector<char> primitives { 'I', 'V',  'X',  'L',  'C',  'D',  'M' };

bool check_primitives (char);	//Поиск примитива в векторе primitives. Если примитив присутсвует возвращает true

int term2int(string);			//Перевод составной части (терма) римского числа из строкового представления в целочисленное
string int2term(int);			//Перевод целого числа в терм

string int2romanstr(int);		//Перевод из int в строковое представление римского числа
int romanstr2int(string);		//Перевод строкового представления римского числа в int, так же проверка корректности строки

//--------------------------------------------- Строка <-> Число ---------------------------------------------


class Roman_int {
public:
	Roman_int(int n);			//Проверка корректности и инициализация арабским числом
	Roman_int(string n);		//Проверка корректности и инициализация строкой с римским числом
	Roman_int();				//Конструктор по умолчанию
	
	
	//Перевод из Roman_int в int
	int as_int() const { return num; }

private:
	int num;		//римское представление числа разбитое последовательно на составные части
};


//<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>> Ввод/Вывод <<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>
ostream& operator<<(ostream& ost, const Roman_int& ri);
istream& operator>>(istream& is, Roman_int& ri);
//<<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>> Ввод/Вывод <<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>><<>>


//==!===!===!===!===!===!===!===!===!===!===!===!= Сравнение ==!===!===!===!===!===!===!===!===!===!===!===!=
bool operator==(const Roman_int& a, const Roman_int& b);
bool operator!=(const Roman_int& a, const Roman_int& b);
//==!===!===!===!===!===!===!===!===!===!===!===!= Сравнение ==!===!===!===!===!===!===!===!===!===!===!===!=


//+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/% Математические операции +-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%
Roman_int operator+(const Roman_int& a, const Roman_int& b);	//сложение (Roman_int+Roman_int)
Roman_int operator-(const Roman_int& a, const Roman_int& b);	//вычитание (Roman_int-Roman_int)
Roman_int operator*(const Roman_int& a, const Roman_int& b);	// Roman_int*Roman_int
Roman_int operator/(const Roman_int& a, const Roman_int& b);	// Roman_int/Roman_int
Roman_int operator%(const Roman_int& a, const Roman_int& b);	// Roman_int%Roman_int
//+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/% Математические операции +-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%+-*/%