


#include <yes_or_no.h>
#include "vctr.h"


#define vector vctr


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T>
ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	for(int i = 0; i < vt.size(); ++i)
		if(i != vt.size()-1)	ost << vt.at(i) << ", ";
		else					ost << vt.at(i);
	
	ost << " }";
	
	return ost;
}


template<typename Iter>	//Требует Forward_iterator<Iter>
void advnc(Iter& p, int n)
{
	if(n >= 0)
		while(n>0)	{ ++p; --n; }
	else
		while(n<0)	{ --p; ++n; }
}


//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			vector<double> vd0 {1.2, 2.3, 3.4, 4.5};
			
			cout << "\n\n" << "forward\n";
			for(int i=0; i < vd0.size(); ++i) {
				double* d = &vd0[0];
				advnc(d, i);
				cout << *d << endl;
			}
			
			cout << "\n\n" << "back\n";
			for(int i=0; i < vd0.size(); ++i) {
				double* d = &vd0[vd0.size()-1];
				advnc(d, -i);
				cout << *d << endl;
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