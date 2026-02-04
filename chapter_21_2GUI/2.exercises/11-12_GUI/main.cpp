


#include <yes_or_no.h>
#include "Order_GUI.h"


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Добивается от пользователя ввод значения от min до max
int get_opt(int min, int max)
{
	int choice {min-1};
	
	cin.clear(ios_base::failbit);
	while( !cin  ||  choice < min  ||  choice > max )
	{
		cin.clear(ios_base::goodbit);
		int tmp;
		cout << "> ";
		cin >> tmp;
		
		if( cin )				choice = tmp;
		else					cin.clear(ios_base::goodbit);
		
		for(char ch = ' '; ch != '\n'; cin.get(ch))		{  }
	}
	
	return choice;
}

//Добивается от пользователя ввод пути к существующему файлу
string get_file()
{
	string name {""};
	/*FILE* file = nullptr;
	while(!file)
	{
		cout << "Enter the name of an existing file with extension or full path to it\n\n> ";
		getline(cin, name);
		
		if(!cin) {
			name = "";
			cin.clear(ios_base::goodbit);
			for(char ch = ' '; ch != '\n'; cin.get(ch))		{  }
		}
		
		file = fopen(name.c_str(), "r");
	}
	
	fclose(file);*/
	
	ifstream file {name};
	while(!file)
	{
		cout << "\nEnter the name of an existing file with extension or full path to it\n\n> ";
		getline(cin, name);
		
		if( !cin ) {
			name = "";
			cin.clear(ios_base::goodbit);
			for(char ch = ' '; ch != '\n'; cin.get(ch))		{  }
		}
		
		file.open(name);
	}
	
	file.close();
	return name;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			while(true)
			{
				
				cout << "\n\nPlease, select one of the following options by entering its number\n\n"
					 << "1. SHOW orders in file\n"
					 << "2. SORT orders in file or SORTed view\n"
					 << "3. ADD order/purchase to file\n"
					 << "4. TOTAL cost of orders in file\n"
					 << "5. SEARCH for orders in a file by criteria\n"
					 << "6. Close program\n\n";
				
				int choice = get_opt(1, 6);
				if( choice == 6 )		//6. Close program
				{
					cout << "\n\nProgram exit initialized by user\n";
					cin.putback('\n');	//Чтобы не нажимать Enter перед появлением сообщения от keep_window_open("~");
					break;
				}
				
				cout << "\n\n";
				string file_name = get_file();
				cout << file_name << endl;
				clear_screen();
				
				switch(choice) {
					case 1:		//1. SHOW orders in file
					{
						Graph_lib::Show_window win {file_name};
						Graph_lib::gui_main();
						break;
					}
					
					case 2:		//2. SORT orders in file or SORTed view
					{
						cout << "\n\nFor open sorted view clear output file field\n\n";
						Graph_lib::Sort_window win {file_name};
						Graph_lib::gui_main();
						break;
					}
					
					case 3:		//3. ADD order/purchase to file
					{
						Graph_lib::Add_window win {file_name};
						Graph_lib::gui_main();
						break;
					}
					
					case 4:		//4. TOTAL cost of orders in file
					{
						Graph_lib::Summ_window win {file_name};
						Graph_lib::gui_main();
						break;
					}
					
					case 5:		//5. SEARCH for orders in a file by criteria
					{
						Graph_lib::Search_window win {file_name};
						Graph_lib::gui_main();
						break;
					}
					
					default:
						error("entered number of non-existent item (" + to_string(choice) + ")");
						break;
				}
				
				clear_screen();
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