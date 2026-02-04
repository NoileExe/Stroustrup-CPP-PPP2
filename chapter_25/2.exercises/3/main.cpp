
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>		//Для возможности форматирования потока вывода
#include <sstream>		//Для строкового потока ввода-вывода
#include <bitset>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			constexpr int bytesInInt = 4;
			constexpr int bitsInByte = 8;
			const size_t nBits = bitsInByte * sizeof(int);
			static_assert(sizeof(int) == bytesInInt, "Number of bytes in signed (long) int does not match");
			
			std::bitset<nBits> a {string{"00000000000000000000000000000000"}};
			std::bitset<nBits> b {string{"11111111111111111111111111111111"}};
			std::bitset<nBits> c {string{"10101010101010101010101010101010"}};
			std::bitset<nBits> d {string{"01010101010101010101010101010101"}};
			std::bitset<nBits> e {string{"11001100110011001100110011001100"}};
			std::bitset<nBits> f {string{"00110011001100110011001100110011"}};
			std::bitset<nBits> g {string{"00000000111111110000000011111111"}};
			std::bitset<nBits> h {string{"11111111000000001111111100000000"}};
			
			
			//signed int int_a = std::bitset<nBits>(string{"00000000000000000000000000000000"}).to_ulong();
			signed int int_a = a.to_ulong();
			signed int int_b = b.to_ulong();
			signed int int_c = c.to_ulong();
			signed int int_d = d.to_ulong();
			signed int int_e = e.to_ulong();
			signed int int_f = f.to_ulong();
			signed int int_g = g.to_ulong();
			signed int int_h = h.to_ulong();
			
			//Максимальная длина (кол-во символов) занимаемое числом signed int при печати (с учетом минуса)
			int maxln {0};
			{
				ostringstream oss;
				oss << (signed int)(std::bitset<nBits>(string{"10000000000000000000000000000000"}).to_ulong());
				maxln = oss.str().size() + 1;
				//cout << "MaxSize signed int: " << maxln << "\n\n";
			}
			
			//cout << right << setw(maxln) << int_a << ' ' << std::bitset<nBits>(int_a) << endl;
			cout << right << setw(maxln) << int_a << ' ' << a << endl;
			cout << right << setw(maxln) << int_b << ' ' << b << endl;
			cout << right << setw(maxln) << int_c << ' ' << c << endl;
			cout << right << setw(maxln) << int_d << ' ' << d << endl;
			cout << right << setw(maxln) << int_e << ' ' << e << endl;
			cout << right << setw(maxln) << int_f << ' ' << f << endl;
			cout << right << setw(maxln) << int_g << ' ' << g << endl;
			cout << right << setw(maxln) << int_h << ' ' << h << endl;
			
			
			cout << "\n\n";
			
			unsigned int uint_a = a.to_ulong();
			unsigned int uint_b = b.to_ulong();
			unsigned int uint_c = c.to_ulong();
			unsigned int uint_d = d.to_ulong();
			unsigned int uint_e = e.to_ulong();
			unsigned int uint_f = f.to_ulong();
			unsigned int uint_g = g.to_ulong();
			unsigned int uint_h = h.to_ulong();
			
			//Максимальная длина (кол-во символов) занимаемое числом signed int (с учетом минуса) или unsigned int при печати 
			// в зависимости от того что длиннее
			{
				ostringstream oss;
				oss << (unsigned int)(b.to_ulong());
				if(oss.str().size() + 1 > maxln)		maxln = oss.str().size() + 1;
				//cout << "MaxSize unsigned int: " << maxln << "\n\n";
			}
			
			cout << right << setw(maxln) << uint_a << ' ' << a << endl;
			cout << right << setw(maxln) << uint_b << ' ' << b << endl;
			cout << right << setw(maxln) << uint_c << ' ' << c << endl;
			cout << right << setw(maxln) << uint_d << ' ' << d << endl;
			cout << right << setw(maxln) << uint_e << ' ' << e << endl;
			cout << right << setw(maxln) << uint_f << ' ' << f << endl;
			cout << right << setw(maxln) << uint_g << ' ' << g << endl;
			cout << right << setw(maxln) << uint_h << ' ' << h << endl;
			
			cout << "\n\n";
			
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