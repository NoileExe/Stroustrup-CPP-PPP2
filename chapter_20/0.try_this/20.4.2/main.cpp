


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


//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			vector<double> vd0 {1.2, 2.3, 3.4, 4.5};
			vector<double> vd1 {};
			
			cout << "vd0\t\t\t\t\t" << vd0 /*<< " space: " << vd0.capacity()*/ << endl;
			
			for(auto x : vd0)	vd1.push_front(x);
			/*vd1.push_front(8.8);
			vd1.push_front(8.8);
			vd1.push_front(8.8);
			vd1.push_back(8.8);
			vd1.push_back(double {7.7});*/
			cout << "vd1 (revers vd0 with push_front)\t" << vd1 /*<< " space: " << vd1.capacity()*/ << endl;
			
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