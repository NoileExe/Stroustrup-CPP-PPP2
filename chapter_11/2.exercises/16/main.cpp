

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";

//------------------------------------------------------------------------------------------------------------

int main() {
	while(true)
	try {
		string ioname {""};
		
		cout << "Укажите файл-источник ввода: ";
		getline(cin, ioname);
		
		ifstream ifs { ioname };
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		ifs.exceptions(ifs.exceptions()|ios_base::badbit);
		
		//----------------------------------------------------------------------------------------------------
		
		double one_num {0};
		vector<double> nums;
		
		while (ifs >> one_num) //при возникновении ошибки прекращает считывание
			nums.push_back(one_num);
		
		sort(nums);
		
		//----------------------------------------------------------------------------------------------------
		
		for (int i = 0; i < nums.size(); ++i)
		{
			int count {1};
			
			while ( i < nums.size()-1  &&  nums[i] == nums[i+1] ) {
				++count;
				++i;
			}
			
			if ( count == 1 )
				cout << nums[i] << '\n';
			else
				cout << nums[i] << ' ' << count << '\n';
		}
		
		
		
		if ( Y_or_N(quit_question) )	return 0;
	}
	
	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		
		if ( Y_or_N(quit_question) )	return 1001;
	}
	
	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		
		if ( Y_or_N(quit_question) )	return 1002;
	}
}