//Почему-то занимает память если сделать вечный цикл
//Во втором цикле и вовсе программа может повиснуть (судя по всему из-за деструктора)


#include <yes_or_no.h>
#include "skip_list.h"



const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "Enter the characters for next Skip_list gen (find test). CTRL+Z for end test\n\n";
			
			char ch{0};
			//int ii{0};
			//Проверка класса и поиска элемента в нём
			while(cin >> ch)		//cin >> ch //true
			{
				Skip_list slst{6, 6};
				//slst.header()->lvl = 8;		//Выдаёт ошибку, т.к. константа
				
				const Unit* ul5 = slst.find(5);
				const Unit* ul53 = slst.find(5, 3);
				cout << "find(5) " << ul5->val << ' ' << ul5->lvl << "\n";
				if(ul53)	cout << "find(5, 3) " << ul53->val << ' ' << ul53->lvl << "\n";
				else		cout << "value 5 on 3rd level not found\n";
				
				cout << "\n" << slst << "\n\n";
				/*++ii;
				if(ii == 10)	clear_screen();*/
			}
			
			while(ch != '\n')		{ cin.get(ch);		cin.clear(); }
			cin.clear();
			
			cout << "Enter the characters for next Skip_list gen (copy and destructor test). CTRL+Z for end test\n\n";
			//Проверка копирующих операций и деструктора
			while(cin >> ch)		//cin >> ch //true
			{
				Skip_list slst{6, 6};
				Skip_list sl1{slst};
				Skip_list sl2{8};
				
				cout << "\n\nslst\n" << slst << "\n\n";
				cout << "sl1{slst}\n"  << sl1  << "\n\n";
				cout << "sl2{8}\n"  << sl2  << "\n\n";
				//keep_window_open();
				
				sl2 = slst;
				cout << "sl1\n"  << sl1  << "\n\n";
				cout << "sl2 = slst\n"  << sl2  << "\n\n";
			}
			
			while(ch != '\n')		{ cin.get(ch);		cin.clear(); }
			cin.clear();
			
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
