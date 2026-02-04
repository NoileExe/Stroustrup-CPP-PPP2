


#include <yes_or_no.h>
#include "document.h"


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Document abc;
			
			{
				string ioname {"input.txt"};
				ifstream ifs { ioname };
				if (!ifs)	error("Unable to open file '" + ioname + "'");
				ifs.exceptions(ifs.exceptions()|ios_base::badbit);
				
				ifs >> abc;
			}
			
			/*auto s1 = last_alphabet_line( abc.begin().get_line(), abc.end().get_line() );
			for(auto ch : *s1)	cout << ch;*/
			
			cout << "Document words count (sequence of characters separated by whitespace characters) =\t"	<< words_count_whitespaces(abc)	<< endl;
			cout << "Document words count       (unbreakable sequence of alphabetic characters) =\t\t"		<< words_count_alphabetic(abc)	<< endl;
			
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