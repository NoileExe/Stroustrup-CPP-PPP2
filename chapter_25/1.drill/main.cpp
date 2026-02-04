
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>			//Для возможности форматирования потока вывода
#include <vector>
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
			
			//1-ое задание
			{
				int v = 1;
				//4 байта по 8 бит - 32 бита занимает переменная типа int
				for(int i = 0; i < sizeof(v)*8; ++i) {
					cout << left << setw(12) << v << ' ' << std::bitset<8*sizeof(v)>(v) << endl;
					v <<= 1; //по аналогии с v += 2, т.е. сокращенная форма v = v<<1
				}
				
				cout << "\n--------------------------------------------------------------------------\n\n";
			}
			
			//2-ое задание
			{
				unsigned int v = 1;
				//4 байта по 8 бит - 32 бита занимает переменная типа int
				for(int i = 0; i < sizeof(v)*8; ++i) {
					cout << left << setw(12) << v << ' ' << std::bitset<8*sizeof(v)>(v) << endl;
					v <<= 1;
				}
				
				cout << "\n--------------------------------------------------------------------------\n\n";
			}
			
			//3-е и 4-ое задания
			{
				//2 байта == 16 бит
				//cout << sizeof(short unsigned int) << ' ' << sizeof(short unsigned int)*8 << "\n\n";
				
				//Одно hex-число (напр., F) занимает 4 бита
				vector<short unsigned int> v {
					0xffff,
					0x01,
					0x8000,
					0xfF,
					0xFF00,
					0xAAAB,
					0xAAAA
				};
				
				cout << dec << uppercase;
				
				for(auto x : v)		cout << setfill(' ') << dec << left << setw(6) << x
										 << " 0x" << setfill('0') << hex << right << setw(4) << x
										 << ' ' << std::bitset<8*sizeof(x)>(x) << endl;
				
				cout << setfill(' ') << dec << nouppercase;
				
				cout << "\n--------------------------------------------------------------------------\n\n";
			}
			
			//5-ое задания
			{
				//2 байта == 16 бит
				//cout << sizeof(short unsigned int) << ' ' << sizeof(short unsigned int)*8 << "\n\n";
				
				//Одно hex-число (напр., F) занимает 4 бита
				vector<short unsigned int> v {
					static_cast<unsigned short>(~0),
					1,
					(1<<15),
					(1 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6 | 1<<7)/*,
					(1<<15 | 1<<14 | 1<<13 | 1<<12 | 1<<11 | 1<<10 | 1<<9 | 1<<8)*/
				};
				
				v.push_back( ~v[v.size()-1] );
				v.push_back( ((v[0]&10)<<12) | ((v[0]&10)<<8) | ((v[0]&10)<<4) | (v[0]&11) );
				v.push_back( ((v[0]&10)<<12) | ((v[0]&10)<<8) | ((v[0]&10)<<4) | (v[0]&10) );
				//v.push_back( (v[0]&11) | ((v[0]&10)<<4) | ((v[0]&10)<<8) | ((v[0]&10)<<12) );
				//v.push_back( (v[0]&10) | ((v[0]&10)<<4) | ((v[0]&10)<<8) | ((v[0]&10)<<12) );
				
				cout << dec << uppercase;
				
				for(auto x : v)		cout << setfill(' ') << dec << left << setw(6) << x
										 << " 0x" << setfill('0') << hex << right << setw(4) << x
										 << ' ' << std::bitset<8*sizeof(x)>(x) << endl;
				
				cout << setfill(' ') << dec << nouppercase;
				
				cout << "\n--------------------------------------------------------------------------\n\n";
			}
			
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