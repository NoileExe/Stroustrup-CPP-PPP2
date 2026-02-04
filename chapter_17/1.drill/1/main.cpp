

#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

const int n = 10;


template <typename T>
ostream& print_vector(ostream& os, const vector<T>& v)
{
	for (int i=0; i < v.size(); ++i) {
		if (i < v.size()-1)		os << v[i] << ", ";
		else					os << v[i] << "\n\n";
	}
	
	return os;
}

ostream& print_array10(ostream& os, int* a)
{
	if (a)
		for (int i=0; i < 10; ++i) {
			if (i < 9)		os << a[i] << ", ";
			else			os << a[i] << "\n\n";
		}
	
	return os;
}

ostream& print_array(ostream& os, int* a, int cn)
{
	if (a)
		for (int i=0; i < cn; ++i) {
			if (i < cn-1)		os << a[i] << ", ";
			else				os << a[i] << "\n\n";
		}
	
	return os;
}


int main()
{
	while (true) {
		try
		{
			int* ints = new int[n];
			
			cout << "Print 'ints' with cycle:\n";
			for (int i=0; i<n; ++i)
				if (i < n-1)		cout << ints[i] << ", ";
				else				cout << ints[i] << "\n\n";
			
			cout << "Print 'ints' with print_array10():\n";
			print_array10(cout, ints);
			
			cout << "Print 'ints' with print_array10() and ostringstream:\n";
			ostringstream oss;
			print_array10(oss, ints);
			cout << oss.str();
			
			delete[] ints;
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			//------------------------------------------------------------------------------
			
			int* hundr1 = new int[n] {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
			
			cout << "Print 'hundr1' and deleted 'ints':\n";
			print_array10(cout, hundr1);
			print_array10(cout, ints);
			
			delete[] hundr1;
			press_Enter_key(true);
			
			cout << "Print deleted 'hundr1' and  also deleted 'ints':\n";
			print_array10(cout, hundr1);
			print_array10(cout, ints);
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			//------------------------------------------------------------------------------
			
			int* hundr2 = new int[n];
			for (int i=0; i < n+1; ++i)			hundr2[i] = 100 + i;
			
			cout << "Print " << n+1 << " nums from 'hundr2' with print_array10():\n";
			print_array10(cout, hundr2);
			
			cout << "Print " << n+1 << " nums from 'hundr2' with print_array():\n";
			print_array(cout, hundr2, n+1);
			
			delete[] hundr2;
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			//------------------------------------------------------------------------------
			
			int* hundr3 = new int[n];
			for (int i=0; i < n+10; ++i)			hundr3[i] = 100 + i;
			
			cout << "Print " << n+10 << " nums from 'hundr3' with print_array():\n";
			print_array(cout, hundr3, n+10);
			
			delete[] hundr3;
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			//------------------------------------------------------------------------------
			
			vector<int> vh10 = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
			
			vector<int> vh11(n+1);
			for (int i=0; i < n+1; ++i)			vh11[i] = 100 + i;
			
			vector<int> vh20;
			for (int i=0; i < n+10; ++i)		vh20.push_back(100 + i);
			
			cout << "PRINT VECTORS:\n";
			print_vector(cout, vh10);
			print_vector(cout, vh11);
			print_vector(cout, vh20);
			
			keep_window_open("~~");
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