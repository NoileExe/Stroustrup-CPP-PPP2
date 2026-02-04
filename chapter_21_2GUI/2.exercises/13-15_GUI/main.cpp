



#include <yes_or_no.h>
#include "clr_srch_words_GUI.h"



const string quit_question = "Close program?";
const string lew = "Pneumonoultramicroscopicsilicovolcanoconiosis";	//longest english word

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

void menu_prg()
{
	while(true)
	{
		
		cout << "\n\nPlease, select one of the following options by entering its number\n\n"
			 << "1. CLEAR words in file\n"
			 << "2. QUANTITY of words\n"
			 << "3. ALL WORDS BEGINNING with the LETTER ...\n"
			 << "4. ALL words with LETTER COUNT equal to ...\n"
			 << "5. Close program\n\n";
		
		int choice = get_opt(1, 5);
		
		string file_name {};
		if( choice != 5 ) {
			cout << "\n\n";
			file_name = get_file();
			cout << file_name << endl;
			clear_screen();
		}
		
		
		switch(choice) {
			case 1:		//1. CLEAR words in file
			{
				clear_file(file_name);
				cout << "\nSuccess";
				keep_window_open("=");
				break;
			}
			
			case 2:		//2. QUANTITY of words
			{
				/*cout << "\n\nPlease, enter a word to search in the text:\n";
				string word;
				getline(cin, word);
				word_qty(file_name, word);
				
				keep_window_open("=");*/
				
				Graph_lib::Word_qty_window wqw {file_name};
				Graph_lib::gui_main();
				break;
			}
			
			case 3:		//3. ALL WORDS BEGINNING with the LETTER ...
			{
				/*cout << "\n\nPlease, enter the letter (or sequence of letters), which is the beginning of the desired words:\n";
				string word;
				getline(cin, word);
				search_1st_letter(file_name, word);
				
				keep_window_open("=");*/
				
				Graph_lib::Letter_srch_window lsw {file_name};
				Graph_lib::gui_main();
				break;
			}
			
			case 4:		//4. ALL words with LETTER COUNT equal to ...
			{
				/*cout << "\n\nPlease, enter the number of letters (words how length it is worth looking for a program):\n";
				search_lngth_word(file_name, get_opt(1, lew.size()));
				
				keep_window_open("=");*/
				
				Graph_lib::Length_srch_window lsw {file_name};
				Graph_lib::gui_main();
				break;
			}
			
			case 5:		//5. Close program
			{
				cout << "\n\nProgram exit initialized by user\n";
				cin.putback('\n');	//Чтобы не нажимать Enter перед появлением сообщения от keep_window_open("~");
				return;
				break;
			}
			
			
			default:
				error("entered number of non-existent item (" + to_string(choice) + ")");
				break;
		}
		
		clear_screen();
	}
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			menu_prg();
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