
//Найдено другое решение на git'е, при котором 8 символов - не предел
//Видимо в зависимости от того в какую область памяти попадёт программа
// работа может завершится на разных этапах без ошибок и предупреждений
//Так же может попасть в область самой выполняемой программы и испортить её саму (см. скриншоты)


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template <typename T> ostream& print_array(ostream& os, T* a, int cn) {
	if (a) {
		for (int i=0; i < cn; ++i) {
			os /*<< "Type: " << typeid(&a[i]).name() << '\t' << &a[i] << '\t'*/ << a[i];
			if (i < cn-1)		os << ", ";
			else				os << "\n\n";
		}
	}
	
	return os;
}


int main()
{
	while (true) {
		try
		{
			cout << "Entering characters from file. Terminate with '!'\n";
			
			char* str = new char;
			char ch {' '};
			
			//istream& ifs = cin;
			string path {"10.txt"};
			ifstream ifs { path };
			if (!ifs)		error("the specified file cannot be opened (" + path + ")");
			ifs.exceptions(ifs.exceptions() | ios_base::badbit);	// Генерация исключения в случае состояния bad ()
			
			unsigned int size {0};		//Размер строки
			
			while (ifs >> ch   &&   ch != '!') {
				str[size] = ch;
				str[size+1] = '\0';
				++size;
				cout << "\n\nArray size: " << size << '\t' << &str[size-1] << '\n';
			}
			
			//Не CTRL+Z, но поток при этом в состоянии fail
			if ( !ifs.eof()  &&  !ifs )		error("bad input");
			while ( !ifs.eof() )		ifs >> ch;
			
			print_array(cout, str, size);
			delete[] str;
			
			keep_window_open("~~");
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