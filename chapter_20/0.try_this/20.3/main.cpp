


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

void cpy(int* f1, int* e1, int* f2)
{
	if(!f1  ||  !e1  ||  !f2)		error("nullptr [copy()]");
	
	if(f1 > e1) {
		int* tmp = f1;
		f1 = e1;
		e1 = tmp;
	}
	
	//for(int i=0; i < e1-f1; ++i)			*(f2+i) = *(f1+i);
	for(int* p = f1; p != e1; ++p)		{ *f2 = *p;		++f2; }
}

int main()
{
	while (true) {
		try
		{
			const int sz {8};
			int orig[sz] {1,2,3,4,5,6,7,8};
			int empt[sz];
			
			//cpy(orig, orig+sz, empt);
			cpy(orig+sz, orig, empt);
			
			for(int i=0; i<sz; ++i)		cout << empt[i] << endl;
			
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