


#include "SchoolTable.h"	//Содержит <string>, <iostream>, <fstream>, <sstream>, <regex>, <iomanip>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			constexpr int tb_year {2007};
			
			string file_name {"table.txt"};
			Table one_school {file_name};
			
			cout << "THE NUMBER OF STUDENTS IN " << tb_year << " AT THE SCHOOL WHERE BJARNE STROUSTRUP STUDIED\n\n";
			cout << one_school << "\n\n\n\n";
			
			cin.putback('\n');
			keep_window_open();
			
			//------------------------------------------------------------------------------
			
			cout << "CHANGES IN THE NUMBER OF STUDENTS DEPENDING ON THE YEAR OF ADMISSION\n\n";
			auto it = one_school.end();
			--it;		//Последний элемент последовательности
			
			while( it != one_school.begin() )
			{
				int one_class {it->num};		//Номер текущего перебираемого класса
				int boys {it->boys};			//Количество учеников (мальчиков) для текущего номера
				int girls {it->girls};			//Количество учениц (девочек) для текущего номера
				
				--it;
				if(one_class >= 0)		//Только с числовым обозначением класса
				{
					while( it->num == one_class )
					{
						boys  += it->boys;
						girls += it->girls;
						
						if( it != one_school.begin() )		--it;
						else								break;
					}
					
					cout << left << setw(10) << (tb_year-one_class) << left << setw(10) << (boys+girls);
					for(int i = 0; i < boys+girls; ++i)		cout << '#';
					cout << endl;
				}
			}
			
			cout << "\n\n\n\n";
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