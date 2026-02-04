


#include <yes_or_no.h>
#include "document.h"


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Подсчёт всех символов в документе включая пробелы (with_spaces == true) или без них (только буквы, цифры и знаки)
unsigned int char_count(Document& d, bool with_spaces = false)
{
	unsigned int count {0};
	
	for(auto p = d.begin(); p != d.end(); ++p)
		if (isprint(*p)  &&  !isspace(*p))					++count;
		else if (with_spaces  &&  (*p==' ' || *p=='\t'))	++count;
		//else if (with_spaces  &&  isspace(*p))				++count;
	
	return count;
}

int main()
{
	while (true) {
		try
		{
			Document abc;
			
			{
				//string ioname {"main.cpp"};
				string ioname {"input.txt"};
				ifstream ifs { ioname };
				if (!ifs)	error("Unable to open file '" + ioname + "'");
				ifs.exceptions(ifs.exceptions()|ios_base::badbit);
				
				ifs >> abc;
			}
			
			/*auto s1 = last_alphabet_line( abc.begin().get_line(), abc.end().get_line() );
			for(auto ch : *s1)	cout << ch;*/
			
			cout << "Document characters count without spaces =\t"	<< char_count(abc)		<< endl;
			cout << "Document characters count with spaces =\t\t"	<< char_count(abc, true)	<< endl;
			
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