


#include <yes_or_no.h>
#include "ovctr.h"
#include <typeinfo>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename Iter> void out_ptr_array(Iter b, Iter e)
{
	cout << "{ ";
	
	for(auto p = b; p != e; ++p) {
		auto tmp = p;
		++tmp;
		
		if(tmp != e)	cout << **p << ", ";
		else			cout << **p;
	}
	
	cout << " }\n";
}

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

ovector<int> fnct()		{ return ovector<int>{1,2,3,4,5,6,7,8,9,0}; }

int main()
{
	while (true) {
		try
		{
			ovector<int> vn {new int {1}, new int {2}, new int {3}};
			ovector<int> vi {7, 8, 9};
			ovector<int> ve1 (3);
			ovector<int> ve2 {vi};
			ovector<double> vee {};
			
			cout << "vn\t\t";
			for(int i = 0;  i < vn.size();  ++i)					cout << vn[i] << ' ';
			cout << endl;
			
			cout << "vi\t\t";
			for(auto p = vi.begin();   p != vi.end();   ++p)		cout << *p << ' ';
			cout << endl;
			
			cout << "ve1\t\t";
			for(int i = 0;  i < ve1.size();  ++i)					cout << ve1.at(i) << ' ';
			cout << endl;
			
			cout << "ve2 {vi}\t";
			for(int i = 0;  i < ve2.size();  ++i)					cout << ve2.at(i) << ' ';
			cout << endl;
			
			ve2 = vn;
			cout << "ve2 = vn\t";
			out_array( ve2.begin(), ve2.end() );
			
			ve2 = fnct();
			cout << "ve2 = fnct()\t";
			out_array( ve2.begin(), ve2.end() );
			
			
			vee.push_back(1.2);
			vee.push_back(2.3);
			vee.push_back(3.4);
			vee.push_back(4.5);
			vee.resize(6);
			vee.resize(8, 8.8);
			cout << "\n\nempty ovector<double> push_back & resize\t";
			out_array( vee.begin(), vee.end() );
			
			/*vn.~ovector();
			vi.~ovector();
			ve1.~ovector();
			ve2.~ovector();
			vee.~ovector();*/
			
			
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