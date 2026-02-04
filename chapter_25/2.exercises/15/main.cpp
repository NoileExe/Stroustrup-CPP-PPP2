


#include "ps.h"		//Включает <yes_or_no.h>, <iomanip>, <sstream> и <fstream>
#include<chrono>
#include<vector>
#include<random>
#include <algorithm>



#pragma comment(linker, "/STACK:104857600")		//изменяет при сборке максимальный размер стека в байтах (100 МБ)
//#pragma comment(linker, "/STACK:16777216")		//изменяет при сборке максимальный размер стека в байтах (16 МБ)

const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Остаток от деления на n (число в диапазоне [0; n))
int randnum_mersen(int n) {
	
	//Работает гораздо быстрее первого метода, но может намертво зациклиться
	random_device rd;
	mt19937 mersenne(rd());		// инициализируем Вихрь Мерсенна случайным стартовым числом
	//mt19937 mersenne(static_cast<unsigned int>(time(0)));	// инициализируем Вихрь Мерсенна случайным стартовым числом
	
	return		mersenne() % n;
}

//------------------------------------------------------------------------------

struct Obj_500 { char data[500]; };

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			const int reps = 10000;		//Кол-во объектов для теста
			const int loops = 10;		//Кол-во повторов (циклов)

			{
				vector<char*> data(reps);	//Указатели на объекты (массивы) случайных размеров
				
				cout << "\n\n";
				double t_alloc = 0;
				double t_dealloc = 0;
				for(int i=0; i < loops; ++i)
				{
					clock_t t1 = clock();
					// размещение в памяти при помощи оператора new
					for(int j=0; j < reps; ++j)		data[j] = new char[randnum_mersen(1000)+1];
					clock_t t2 = clock();
					t_alloc += double(t2-t1) / CLOCKS_PER_SEC;

					// очистка памяти при помощи оператора delete; в обратном направлении
					t1 = clock();
					for(int j = reps-1; j >= 0; --j)		{ delete[] data[j];		data[j] = nullptr; }
					t2 = clock();
					t_dealloc += double(t2-t1) / CLOCKS_PER_SEC;
				}
				
				/*{
					auto t1 = chrono::system_clock::now();
					// размещение в памяти при помощи оператора new
					for(int j=0; j < reps; ++j)		data[j] = new char[randnum_mersen(1000)+1];
					auto t2 = chrono::system_clock::now();
					t_alloc += chrono::duration_cast< chrono::milliseconds >(t2-t1).count();

					// очистка памяти при помощи оператора delete; в обратном направлении
					t1 = chrono::system_clock::now();
					for(int j = reps-1; j >= 0; --j)		{ delete[] data[j];		data[j] = nullptr; }
					t2 = chrono::system_clock::now();
					t_dealloc += chrono::duration_cast< chrono::milliseconds >(t2-t1).count();
				}*/
				
				//Средние значения времени для 10 циклов
				t_alloc /= loops;
				t_dealloc /= loops;
				cout << "Time to allocate with new: " << t_alloc*1000.0 << " ms\n";
				cout << "Time to deallocate with delete, REVERSE order: " << t_dealloc*1000.0 << " ms\n";
			}

			//------------------------------------------------------------------------------
			
			{
				vector<char*> data(reps);	//Указатели на объекты (массивы) случайных размеров

				cout << "\n\n";
				double t_alloc = 0;
				double t_dealloc = 0;
				{
					clock_t t1 = clock();
					// размещение в памяти при помощи оператора new
					for(int j=0; j < reps; ++j)		data[j] = new char[randnum_mersen(1000)+1];
					clock_t t2 = clock();
					t_alloc += double(t2-t1) / CLOCKS_PER_SEC;

					// очистка памяти при помощи оператора delete; случайный доступ
					random_shuffle(data.begin(),data.end());
					t1 = clock();
					//for (int j = 0; j > data.size(); ++j)		{ delete[] data[j];		data[j] = nullptr; }
					for(int j = reps-1; j >= 0; --j)		{ delete[] data[j];		data[j] = nullptr; }
					t2 = clock();
					t_dealloc += double(t2-t1) / CLOCKS_PER_SEC;
				}
				
				//Средние значения времени для 10 циклов
				t_alloc /= loops;
				t_dealloc /= loops;
				cout << "Time to allocate with new: " << t_alloc*1000.0 << " ms\n";
				cout << "Time to deallocate with delete, RANDOM order: " << t_dealloc*1000.0 << " ms\n";
			}

			//------------------------------------------------------------------------------

			{
				//Pool<Obj_500,reps> pool;
				//vector<Obj_500*> data(reps);	//Указатели на объекты (массивы) размером 500 байт
				pvctr<Obj_500,reps> data;	//Указатели на объекты (массивы) размером 500 байт

				cout << "\n\n";
				double t_alloc = 0;
				double t_dealloc = 0;
				for(int i=0; i < loops; ++i)
				{
					clock_t t1 = clock();
					// размещение в пуле
					for(int j=0; j < reps; ++j)		data.push_back( Obj_500{} );
					clock_t t2 = clock();
					t_alloc += double(t2-t1) / CLOCKS_PER_SEC;

					// освобождение памяти из пула
					t1 = clock();
					for(int j = reps-1; j >= 0; --j)		data.pop_back();
					t2 = clock();
					t_dealloc += double(t2-t1) / CLOCKS_PER_SEC;
				}
				
				/*{
					clock_t t1 = clock();
					// размещение в пуле
					for(int j=0; j < reps; ++j)		data[j] = pool.get();
					clock_t t2 = clock();
					t_alloc += double(t2-t1) / CLOCKS_PER_SEC;

					// освобождение памяти из пула
					t1 = clock();
					for(int j = reps-1; j >= 0; --j)		{ pool.free(data[j]);		data[j] = nullptr; }
					t2 = clock();
					t_dealloc += double(t2-t1) / CLOCKS_PER_SEC;
				}*/
				
				//Средние значения времени для 10 циклов
				t_alloc /= loops;
				t_dealloc /= loops;
				cout << "Time to allocate from pool: " << t_alloc*1000.0 << " ms\n";
				cout << "Time to deallocate (free) from pool: " << t_dealloc*1000.0 << " ms\n";
			}

			//------------------------------------------------------------------------------

			{
				Stack<6000000> stack;

				cout << "\n\n";
				double t_alloc = 0;
				double t_dealloc = 0;
				for(int i=0; i < loops; ++i)
				{
					clock_t t1 = clock();
					// размещение в стеке
					for(int j=0; j < reps; ++j)		stack.get(randnum_mersen(1000)+1);
					clock_t t2 = clock();
					t_alloc += double(t2-t1) / CLOCKS_PER_SEC;

					// освобождение памяти из стека
					t1 = clock();
					for (int j = 0; j<reps; ++j)		stack.free();
					t2 = clock();
					t_dealloc += double(t2-t1) / CLOCKS_PER_SEC;
				}
				
				//Средние значения времени для 10 циклов
				t_alloc /= loops;
				t_dealloc /= loops;
				cout << "Time to allocate from stack: " << t_alloc*1000.0 << " ms\n";
				cout << "Time to deallocate (free) from stack: " << t_dealloc*1000.0 << " ms\n";
			}
			
			//При повторах при некотором превышении 100 МБ ОЗУ занимаемой программой (примерно на 3ем повторе) программа крашится
			//Скорее всего просто нужно чтобы массивы размещались в куче (в динамической памяти при помощи оператора new)
			if ( !Y_or_N("Repeat?") )
			{
				cin.putback('\n');
				keep_window_open("~");
				return 0;
			}
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