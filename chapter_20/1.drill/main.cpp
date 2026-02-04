

#include <typeinfo>
#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
void out_conteiner(const T& ivl)
{
	cout << "{ ";
	
	for(auto p = begin(ivl); p != end(ivl); ++p) {
		auto tmp = p;
		++tmp;
		
		if(tmp != end(ivl))		cout << *p << ", ";
		else					cout << *p;
	}
	
	cout << " }\n";
}

template<typename Iter1, typename Iter2>	//Требует Input_iterator<Iter1>() и Output_iterator<Iter2>()
Iter2 cpy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	if(f1 == e1)	return f2;
	
	Iter2 e2 = f2;
	for(auto p = f1; p != e1; ++p)
		{ *e2 = *p;		++e2; }
	
	return e2;
	//return f2+(e1-f1);	//Не работает
}

int main()
{
	while (true) {
		try
		{
			const int sz {10};
			
			array<int,sz>	i_arr0 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			vector<int>		i_vct0 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			list<int>		i_lst0 {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
			
			array<int,sz>	i_arr1 {i_arr0};
			vector<int>		i_vct1 {i_vct0};
			list<int>		i_lst1 {i_lst0};
			
			cout << "i_arr0, i_arr1:\n";
			out_conteiner(i_arr0);
			out_conteiner(i_arr1);
			cout << "\n\n";
			
			cout << "i_vct0, i_vct1:\n";
			out_conteiner(i_vct0);
			out_conteiner(i_vct1);
			cout << "\n\n";
			
			cout << "i_lst0, i_lst1:\n";
			out_conteiner(i_lst0);
			out_conteiner(i_lst1);
			cout << "\n\n";
			
			cout << "------------------------------------------------------------------------------\n\n";
			
			for(auto& v : i_arr1)	v += 2;
			cout << "i_arr1 each +2\t";
			out_conteiner(i_arr1);
			cout << "\n\n";
			
			for(auto& v : i_arr1)	v += 3;
			cout << "i_arr1 each +3\t";
			out_conteiner(i_arr1);
			cout << "\n\n";
			
			for(auto& v : i_lst1)	v += 5;
			cout << "i_lst1 each +5\t";
			out_conteiner(i_lst1);
			cout << "\n\n";
			
			cout << "------------------------------------------------------------------------------\n\n";
			
			//Массив в вектор
			cpy(i_arr1.begin(), i_arr1.end(), i_vct1.begin());
			cout << "cpy i_arr1 to i_vct1:\n";
			out_conteiner(i_arr1);
			out_conteiner(i_vct1);
			cout << "\n\n";
			
			//Список в массив
			cpy(i_lst0.begin(), i_lst0.end(), i_arr1.begin());
			cout << "cpy i_lst0 to i_arr1:\n";
			out_conteiner(i_lst0);
			out_conteiner(i_arr1);
			cout << "\n\n";
			
			cout << "------------------------------------------------------------------------------\n\n";
			
			cout << "find in i_vct0 position of number 3. POSITION: ";
			
			auto f1 = find( i_vct0.begin(), i_vct0.end(), int(3) );
			if( f1 != i_vct0.end() ) {
				int i = 0;
				for (auto p = i_vct0.begin(); p != f1; ++p)		++i;
				cout << i;
			}
				
			else	cout << "not found";
			
			cout << "\n\n";
			
			
			cout << "find in i_lst1 position of number 27. POSITION: ";
			
			auto f2 = find( i_lst1.begin(), i_lst1.end(), int(27) );
			if( f2 != i_lst1.end() ) {
				int i = 0;
				for (auto p = i_lst1.begin(); p != f2; ++p)		++i;
				cout << i;
			}
			
			else	cout << "not found";
			
			cout << "\n\n";
			
			
			cout << "find in i_lst1 position of number 14. POSITION: ";
			
			f2 = find( i_lst1.begin(), i_lst1.end(), int(14) );
			if( f2 != i_lst1.end() ) {
				int i = 0;
				for (auto p = i_lst1.begin(); p != f2; ++p)		++i;
				cout << i;
			}
			
			else	cout << "not found";
			
			cout << "\n\n";
			
			
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