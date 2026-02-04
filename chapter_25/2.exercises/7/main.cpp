
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>		//Для возможности форматирования потока вывода
#include <sstream>		//Для строкового потока ввода-вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

inline int max_int(int a, int b)	{ return (a > b) ? a : b; }

int count_nums(int n)
{
	int count = (n < 0)  ?  1 : 0;
	n = abs(n);
	do { ++count; } while(n /= 10);

	return count;
}

void print_hex(int min = 0, int max = 100)
{
	if(max < min)		swap(min, max);
	
	cout << "\n\n";
	
	int dec_width = max_int(count_nums(min), count_nums(max)) + 1;
	cout << dec_width << endl;
	keep_window_open();
	
	for (int i = min; i <= max; ++i)
		cout << dec << setw(dec_width) << i << "  " << hex << i << endl;
	
	cout << dec << "\n\n";
}


int main()
{
	while (true) {
		try
		{
			print_hex(0,400);
			keep_window_open();
			
			print_hex(-200,200);
			
			cin.putback('\n');
			keep_window_open("~");
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