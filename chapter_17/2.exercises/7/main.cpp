
//Достаточно 8 символов для переполнения памяти? 9 символ отличается от введёного

#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template <typename T>
ostream& print_array(ostream& os, T* a, int cn)
{
	if (a) {
		for (int i=0; i < cn; ++i) {
			os /*<< "Type: " << typeid(&a[i]).name() << '\t' << &a[i] << '\t'*/ << a[i];
			if (i < cn-1)		os << ", ";
			else				os << "\n\n";
		}
	}
	
	return os;
}


char* add_ptr_array (char* str, char ch)
{
	if (!str)		error("nullptr pointer ( add_ptr_array() )");
	
	int sz {0};	//Размер строки
	while(str  &&  str[sz] != 0)		++sz;
	
	char* new_str = new char[sz+1];
	//Нуль-терминатор не считается как символ строки, так что &str[sz-1] - адрес последнего символа строки;
	// &str[sz] - адрес нуля-терминатора;
	// sz+1 - такой адрес не существует, т.к. не выделен, но потребуется для нуля-терминатора новой строки
	
	//cout << sz << '\t' << &str << '\t' << &new_str << '\n';
	
	//Переносим старую строку на новое место
	for(int i=0; i < sz; ++i)		new_str[i] = str[i];
	
	new_str[sz] = ch;
	new_str[sz + 1] = 0;
	delete[] str;	//Освобождаем ранее занятую память старой строкой
	
	return new_str;
}


int main()
{
	while (true) {
		try
		{
			cout << "Please enter some characters. Terminate with '!'\n";
			
			unsigned int size {0};		//Размер строки
			char* str = new char{'\0'};
			
			char ch {' '};
			
			while( cin >> ch   &&   ch != '!' ) {
				str = add_ptr_array(str, ch);
				++size;
				cout << size << '\t' << &str << '\n';
				print_array(cout, str, size);
			}
			
			//Не CTRL+Z, но поток при этом в состоянии fail
			if ( !cin.eof()  &&  !cin )		error("bad input");
			
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