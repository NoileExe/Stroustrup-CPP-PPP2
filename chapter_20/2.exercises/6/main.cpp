


#include <yes_or_no.h>
#include "document.h"


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			//string ioname {"main.cpp"};
			string ioname {"input.txt"};
			ifstream ifs { ioname };
			if (!ifs)	error("Unable to open file '" + ioname + "'");
			ifs.exceptions(ifs.exceptions()|ios_base::badbit);
			
			Document abc;
			ifs >> abc;
			
			{
				ioname = "output0.txt";
				ofstream ofs { ioname };
				if (!ofs)	error("Unable to open file '" + ioname + "'");
				
				ofs << abc;
				ofs.close();
			}
			
			
			{
				Document del_line_doc {abc};
				
				//Выясняем номер строки
				auto p = ( find_txt(del_line_doc.begin(), del_line_doc.end(), "//#include \"std_lib_facilities.h\"") ).get_line();
				int line_num {0};
				for(auto tmp = del_line_doc.begin().get_line();   tmp != p;   ++tmp, ++line_num)		{  }
				
				erase_line(del_line_doc, line_num);		//строка '//#include <yes_or_no.h>'
				
				ioname = "output1.txt";
				ofstream ofs { ioname };
				if (!ofs)	error("Unable to open file '" + ioname + "'");
				
				ofs << del_line_doc;
				ofs.close();
			}
			
			
			{
				Document replace_doc {abc};
				replace_words(replace_doc, "error", "ERROR");
				
				ioname = "output2.txt";
				ofstream ofs { ioname };
				if (!ofs)	error("Unable to open file '" + ioname + "'");
				
				ofs << replace_doc;
				ofs.close();
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