


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
			
			cout << "Document' full text:\n\n" << abc << "\n\n";
			
			cout << "Document words count (separated by whitespace characters: space, tab, newline) =\t" << words_count_custom(abc, " \t\n") << endl;
			cout << "Document words count (separated by .,!?@#$%&*{}[]()/\\-+\"') =\t\t\t\t"             << words_count_custom(abc, ".,!?@#$%&*{}[]()/\\-+\"'") << endl;
			
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