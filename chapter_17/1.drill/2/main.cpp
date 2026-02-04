

#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

const int n = 10;


template <typename T>
ostream& print_vector(ostream& os, const vector<T>& v)
{
	for (int i=0; i < v.size(); ++i) {
		if (i < v.size()-1)		os << &v[i] << '\t' << v[i] << ", ";
		else					os << &v[i] << '\t' << v[i] << "\n\n";
	}
	
	return os;
}

template <typename T>
ostream& print_array(ostream& os, T* a, int cn)
{
	if (a) {
		os << a << '\t';
		
		for (int i=0; i < cn; ++i) {
			if (i < cn-1)		os << a[i] << ", ";
			else				os << a[i] << "\n\n";
		}
	}
	
	return os;
}

template <typename T>
ostream& print_array_addr(ostream& os, T* a, int cn)
{
	if (a) {
		for (int i=0; i < cn; ++i) {
			if (i < cn-1)		os << &a[i] << '\t' << a[i] << ", ";
			else				os << &a[i] << '\t' << a[i] << "\n\n";
		}
	}
	
	return os;
}


int main()
{
	while (true) {
		try
		{
			cout << "\tp1:\n";
			int* p1 = new int {7};
			print_array(cout, p1, 1);
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			
			cout << "\tarray p2:\n";
			int* p2 = new int[7];
			for (int i=0; i < 7; ++i)		p2[i] = pow(2,i);
			print_array(cout, p2, 7);
			//cout << "\tarray p2 with cells addr:\n";
			//print_array_addr(cout, p2, 7);
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			
			cout << "\tarray p3 {p2} + 3 overrange addr:\n";
			int* p3 {p2};
			print_array(cout, p3, 10);
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			
			//не удаляется p2, т.к. его старое значение продублированно в p3
			cout << "\tp2 = p1:\n";
			p2 = p1;
			print_array(cout, p2, 7);
			
			cout << "\tp2 = p3:\n";
			p2 = p3;
			print_array(cout, p2, 7);
			
			cout << "\tp1:\n";
			print_array(cout, p1, 1);
			
			delete p1;
			delete[] p2;
			//delete[] p3;
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			
			p1 = new int[10];
			for (int i=0; i < 10; ++i)		p1[i] = pow(2,i);
			cout << "\tnew array in p1:\n";
			print_array(cout, p1, 10);
			print_array_addr(cout, p1, 10);
			
			p2 = new int[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			//p2 = new int[10] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			cout << "\tnew array in p2:\n";
			print_array(cout, p2, 10);
			print_array_addr(cout, p2, 10);
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			
			for (int i=0; i < 10; ++i)		p2[i] = p1[i];
			
			cout << "\tcopy p1 values in p2 values:\n";
			print_array(cout, p2, 10);
			print_array_addr(cout, p2, 10);
			
			delete[] p1;
			delete[] p2;
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			
			cout << "\tvectors v1 and v2:\n";
			vector<int> v1;
			for (int i=0; i < 10; ++i)		v1.push_back( pow(2,i) );
			
			vector<int> v2 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			
			print_vector(cout, v1);
			print_vector(cout, v2);
			press_Enter_key(true);
			
			//------------------------------------------------------------------------------
			
			cout << "\tcopy v1 values in v2 values:\n";
			for (int i=0; i < 10; ++i)		v2[i] = v1[i];
			print_vector(cout, v2);
			
			keep_window_open("~~");
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )    return 1002;
		}
	}
}