
#include <yes_or_no.h>
#include <std_lib_facilities.h>


void swap_v(int a, int b);
void swap_r(int& a, int& b);
void swap_cr(const int& a, const int& b);

int main(int argc, char *argv[])
{
	int x = 7;
	int y = 9;
	
	cout << "     X     |     Y\n";
	cout << "-----------+-----------\n";
	cout << "     " << x << "     |     " << y << "\n";
	cout << "-----------+-----------\n";
	swap_v(x,y);
		cout << "main       |" << endl;
		cout << "     " << x << "     |     " << y << "\n";
		cout << "-----------+-----------\n";
	swap_r(x,y);
		cout << "main       |" << endl;
		cout << "     " << x << "     |     " << y << "\n";
		cout << "-----------+-----------\n";
	/*swap_cr(x,y); //впринципе не рабочая ф-ция
		cout << "main" << endl;
		cout << "     " << x << "     |     " << y << "\n";
		cout << "-----------+-----------\n";*/
	
	swap_v(7,9);
		cout << "main       |" << endl;
		cout << "     " << 7 << "     |     " << 9 << "\n";
		cout << "-----------+-----------\n";
	/*swap_r(7,9); //работает только с int переменными
		cout << "main       |" << endl;
		cout << "     " << 7 << "     |     " << 9 << "\n";
		cout << "-----------+-----------\n";
	swap_cr(7,9); //впринципе не рабочая ф-ция
		cout << "main       |" << endl;
		cout << "     " << 7 << "     |     " << 9 << "\n";
		cout << "-----------+-----------\n";*/
	
	
	cout << "---------------------------------------------------------------\n";
	press_Enter_key(true);
	
	const int cx = 7;
	const int cy = 9;
	
	cout << "     CX    |     CY\n";
	cout << "-----------+-----------\n";
	cout << "     " << cx << "     |     " << cy << "\n";
	cout << "-----------+-----------\n";
	
	swap_v(cx,cy);
		cout << "main       |" << endl;
		cout << "     " << cx << "     |     " << cy << "\n";
		cout << "-----------+-----------\n";
	/*swap_r(cx,cy); //работает только с int переменными
		cout << "main       |" << endl;
		cout << "     " << cx << "     |     " << cy << "\n";
		cout << "-----------+-----------\n";
	swap_cr(cx,cy); //впринципе не рабочая ф-ция
		cout << "main       |" << endl;
		cout << "     " << cx << "     |     " << cy << "\n";
		cout << "-----------+-----------\n";*/
	
	swap_v(7.7,9.9);
		cout << "main       |" << endl;
		cout << "    " << 7.7 << "    |    " << 9.9 << "\n";
		cout << "-----------+-----------\n";
	/*swap_r(7.7,9.9); //работает только с int переменными
		cout << "main       |" << endl;
		cout << "    " << 7.7 << "    |    " << 9.9 << "\n";
		cout << "-----------+-----------\n";
	swap_cr(7.7,9.9); //впринципе не рабочая ф-ция
		cout << "main       |" << endl;
		cout << "    " << 7.7 << "    |    " << 9.9 << "\n";
		cout << "-----------+-----------\n";*/
	
	
	cout << "---------------------------------------------------\n";
	press_Enter_key();
	
	double dx = 7.7;
	double dy = 9.9;
	
	cout << "     DX    |     DY\n";
	cout << "-----------+------------\n";
	cout << "     " << dx << "   |     " << dy << "\n";
	cout << "-----------+------------\n";
	
	swap_v(dx,dy);
		cout << "main       |" << endl;
		cout << "     " << dx << "   |     " << dy << "\n";
		cout << "-----------+------------\n";
	/*swap_r(dx,dy); //работает только с int переменными
		cout << "main       |" << endl;
		cout << "     " << dx << "   |     " << dy << "\n";
		cout << "-----------+------------\n";
	swap_cr(dx,dy); //впринципе не рабочая ф-ция
		cout << "main       |" << endl;
		cout << "     " << dx << "   |     " << dy << "\n";
		cout << "-----------+------------\n";*/
	
	swap_v(7.7,9.9);
		cout << "main       |" << endl;
		cout << "     " << 7.7 << "   |    " << 9.9 << "\n";
		cout << "-----------+------------\n";
	/*swap_r(7.7,9.9); //работает только с int переменными
		cout << "main       |" << endl;
		cout << "     " << 7.7 << "   |    " << 9.9 << "\n";
		cout << "-----------+------------\n";
	swap_cr(7.7,9.9); //впринципе не рабочая ф-ция
		cout << "main       |" << endl;
		cout << "     " << 7.7 << "   |    " << 9.9 << "\n";
		cout << "-----------+------------\n";*/
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}

void swap_v(int a, int b)
//меняет местами всё что угодно, но лишь в пределах самой ф-ции, аргументы за 
//функцией не изменяются
{
	cout << "swap_v     |" << endl;
	cout << "-    " << a << "     |     " << b << endl;
	
	
	int temp;
	temp = a;
	a = b;
	b = temp;
	
	cout << "+    " << a << "     |     " << b << endl;
}

void swap_r(int& a, int& b)
//Будет работать только с именованной областью памяти и менять её, но не будет 
//работать при подаче обычных цифр в качестве аргумента (т.к. это не именновая область памяти)
{
	cout << "swap_r     |" << endl;
	cout << "-    " << a << "     |     " << b << endl;
	
	
	int temp;
	temp = a;
	a = b;
	b = temp;
	
	cout << "+    " << a << "     |     " << b << endl;
}

/*void swap_cr(const int& a, const int& b)
//не будет компилироваться ни в одной реализации, т.к. аргументы подаются
//по константым ссылкам и соотв. доступны только для чтения (нельзя a приравнять b!!!)
{
	cout << "swap_cr    |" << endl;
	cout << "-    " << a << "     |     " << b << endl;
	
	
	int temp;
	temp = a;
	a = b;
	b = temp;
	
	cout << "+    " << a << "     |     " << b << endl;
}*/
