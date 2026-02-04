

#include <typeinfo>
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
void f(const T& cvls) {
	//Такой поиск размера работает аналогично
	/*auto b { begin(cvls) };
	auto e {  end(cvls)  };
	int sz {0};
	
	for(auto i = b; i != e; ++i)		++sz;
	
	//Не учитываем нуль-терминатор во встроенном массиве (char[]) символов
	if( typeid(T).name() == typeid(char[sizeof(cvls)]).name() )		--sz;
	cout << "\nsize: " << sz << endl;*/
	
	int sz {0};
	
	//string h {"Hell"};	//NOT EQU with 'Hell' string
	//string h {"Helloo"};	//NOT EQU with 'Helloo' string
	string h {"Hello"};
	string n {"Howdy"};
	string arg {""};
	
	//Работают так же хорошо как и вариант ниже
	//for(auto v : cvls)
	//for(const auto& v : cvls)
		//if(v != 0)	{ arg += v;		++sz; }
	
	for(auto p = begin(cvls); p!=end(cvls); ++p)
		if(*p != 0)	{ arg += *p;		++sz; }
	
	cout << "\nsize: " << sz << "\n\t";
	
	if(h != arg)	cout << "NOT ";
	cout << "equale with '" << h << "' string" << "\n\t";
	
	if(n != arg)	cout << "NOT ";
	cout << "equale with '" << n << "' string" << "\n\n";
	
	auto cpy {cvls};
	cout << "fnct arg object type is:\t" << typeid(cvls).name() << endl;
	cout << "copied object type is:\t\t" << typeid(cpy).name() << endl;
	
	//Унифицировать получение данных из cpy для всех типов не получилось
}


int main()
{
	while (true) {
		try
		{
			char			h_chr[] {"Hello"};
			vector<char>	h_vct   {'H', 'e', 'l', 'l', 'o'};
			list<char>		h_lst   {'H', 'e', 'l', 'l', 'o'};
			string			h_str   {"Hello"};
			
			f(h_chr);
			f(h_vct);
			f(h_lst);
			f(h_str);
			
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