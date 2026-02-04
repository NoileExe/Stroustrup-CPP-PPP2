

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <set>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			{
				ifstream is {"input.txt"};				//Открываем поток ввода
				ofstream os {"output_vector.txt"};		//Открываем поток вывода
				
				istream_iterator<string> ii{is};		//Создаём итератор ввода
				istream_iterator<string> eos;			//Ограничитель ввода (итератор по умолчанию, который означает eof)
				ostream_iterator<string> oo{os,"\n"};	//Создаём итератор вывода
				
				vector<string> b{ii, eos};				//Вектор инициализируется потоком ввода
				sort(b.begin(), b.end());				//Сортировка буфера
				copy(b.begin(), b.end(), oo);			//Копирование буфера в выходной поток
			}
			
			//--------------------------------------------------------------------------
			
			{
				ifstream is {"input.txt"};				//Открываем поток ввода
				ofstream os {"output_set.txt"};			//Открываем поток вывода
				
				set<string> b (istream_iterator<string> {is}, istream_iterator<string> {});
				
				//Копирование буфера в выходной поток
				copy(b.begin(), b.end(), ostream_iterator<string> {os," "});
			}
			
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