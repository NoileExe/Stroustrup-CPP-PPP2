
// Ключ для расшифровки текста из файла "in.txt" - bs


#include "TEA.h"		//Включает <yes_or_no.h>, <iomanip>, <sstream> и <fstream>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Добивается от пользователя ввода исправного числа в диапазоне от min до max
template<class N> //Требует Number<N>
N get_kb_num(const string& question, N min = 0, N max = 100)
{
	N num {min-1};
	while(true)
	{
		cout << "\n" << question << "\n\n> ";
		
		string str {""};
		getline(cin, str);
		
		istringstream iss {str};
		iss >> num;
		
		if( cin.good()  &&  !iss.fail()  &&  (min <= num && num <= max) )
			break;
		else {
			cout << "\n\tRange [" << min << "; " << max << "]\n\n";
			num = -1;
			cin.clear(ios_base::goodbit);
			press_Enter_key();
			clear_screen(); //очистка окна консоли
		}
	}
	
	//Возвращаем ответ введённый пользователем
	return num;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			while(true)
			{
				clear_screen(); //очистка окна консоли
				
				string str { "\n\tMessage encoding program TEA (Tiny Encryption Algorithm)\n\n\n"};
				str += "\nSelect an item by entering its number:\n";
				str += "\n  1. Send (encrypt) message";
				str += "\n  2. Receive (decrypt) message";
				str += "\n  3. Close program\n";
				
				cin.clear(ios_base::goodbit);
				int lib_opt = get_kb_num(str, 1, 3);
				
				clear_screen(); //очистка окна консоли
				cout << "\n\tMessage encoding program TEA (Tiny Encryption Algorithm)\n\n\n";
				
				string fileName1, fileName2, key;
				
				switch(lib_opt) {
				case 1:
					cout << "\n  1. Send (encrypt) message\n\n";
					cout << "Enter input file name: ";		cin >> fileName1;
					cout << "Enter output file name: ";		cin >> fileName2;
					cout << "Enter key file name: ";		cin >> key;
					messageSend(fileName1, fileName2, key);
					
					cout << "\n\nThe message is encrypted\n";
					press_Enter_key();
					break;
				
				case 2:
					cout << "\n  2. Receive (decrypt) message\n\n";
					cout << "Enter name of the encrypted file: ";		cin >> fileName1;
					cout << "Enter output file name: ";					cin >> fileName2;
					cout << "Enter key file name: ";					cin >> key;
					messageGet(fileName1, fileName2, key);
					
					cout << "\n\nThe message is deciphered\n";
					press_Enter_key();
					break;
				
				default:
					cout << "\n  3. Close program\n\n";
					cin.putback('\n');
					if( Y_or_N(quit_question) )		return 0;
					break;
				}
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