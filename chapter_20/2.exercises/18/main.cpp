


#include <yes_or_no.h>
#include "vctr.h"


#define vector vctr


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename Iter> void out_array(Iter b, Iter e)
{
	cout << "{ ";
	
	for(auto p = b; p != e; ++p) {
		auto tmp = p;
		++tmp;
		
		if(tmp != e)	cout << *p << ", ";
		else			cout << *p;
	}
	
	cout << " }\n";
}

//------------------------------------------------------------------------------

vector<int> fnct()		{ return vector<int>{1,2,3,4,5,6,7,8,9,0}; }

int main()
{
	while (true) {
		try
		{
			vector<int> vi {7, 8, 9};
			vector<int> ve1 (3);
			vector<int> ve2 {vi};
			vector<double> vee {};
			
			
			cout << "vi\t\t";
			for(auto p = vi.begin();   p != vi.end();   ++p)		cout << *p << ' ';
			cout << endl;
			
			cout << "ve1\t\t";
			for(int i = 0;  i < ve1.size();  ++i)					cout << ve1.at(i) << ' ';
			cout << endl;
			
			cout << "ve2 {vi}\t";
			for(int i = 0;  i < ve2.size();  ++i)					cout << ve2.at(i) << ' ';
			cout << endl;
			
			ve2 = ve1;
			cout << "ve2 = ve1\t";
			out_array( ve2.begin(), ve2.end() );
			
			ve2 = fnct();
			cout << "ve2 = fnct()\t";
			out_array( ve2.begin(), ve2.end() );
			
			vector<int> vf {fnct()};
			cout << "vf {fnct()}\t";
			out_array( vf.begin(), vf.end() );
			
			vee.push_back(1.2);
			vee.push_back(2.3);
			vee.push_back(3.4);
			vee.push_back(4.5);
			vee.push_front(0.1);
			vee.resize(8);
			vee.resize(10, 8.8);
			cout << "\n\nempty vector<double> push_back & resize\t";
			out_array( vee.begin(), vee.end() );
			
			
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