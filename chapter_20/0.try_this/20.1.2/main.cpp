


#include <yes_or_no.h>
#include <std_lib_facilities.h>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

double* get_from_jack(int* count);		//Джек записывает числа типа double в массив, возвращая их кол-во в count
vector<double>* get_from_jill();		//Джилл заполняет вектор

double* high(double* first, double* last)
{
	if(!first  ||  !last)		error("nullptr in function high(ptr, ptr) arguments");
	
	double* h = first;
	for(double* p = first; p != last; ++p)
		if(*p > *h)		h = p;
	
	return h;
}

double* get_from_jack(int* count)
{
	int sz = 4;
	double* jack_array = new double[4] {1, 2, 3, 4};
	*count = sz;
	return jack_array;
}

vector<double>* get_from_jill()		{ return new vector<double> {5, 6, 7, 8}; }

int main()
{
	while (true) {
		try
		{
			int jack_count = 0;
			double* jack_data = get_from_jack(&jack_count);
			vector<double>* jill_data = get_from_jill();
			
			double* jack_high = high(jack_data,   jack_data+jack_count);
			vector<double>& v = *jill_data;
			double* jill_high = high(  &v[0],        &v[0]+v.size()   );
			
			cout << "Jill max: " << *jill_high << ";\tJack max: " << *jack_high << endl;
			cout << "Jill vector size: " << jill_data->size() << ";\tJack array size: " << jack_count;
			
			
			delete[] jack_data;
			delete jill_data;
			
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