#include <std_lib_facilities.h>

//------------------------------------------------------------------------------

struct struct_minmaxmid {
	double min;
	double max;
	double mid;
	double medi;
};

//------------------------------------------------------------------------------

double minv_proc(const vector<double>& v);
double maxv_proc(const vector<double>& v);
double midv_proc(const vector<double>& v);
double mediv_proc(vector<double> v);
struct_minmaxmid search_4m (const vector<double>& v);

double common_check (const vector<double>& price, const vector<double>& count);

void print_until_s (const vector<string>& v, string quit);
void print_until_ss (const vector<string>& v, string quit, int k);
void print_vdouble(const string& s, const vector<double>& v);
void print_vint(const string& s, const vector<int>& v);
void print_vstr(const string& s, const vector<string>& v);

vector<int> vector_int1 (vector<int> v);
void vector_int2 (vector<int>& v);

vector<string> vector_str1 (vector<string> v);
void vector_str2 (vector<string>& v);

vector<double> vector_double1 (vector<double> v);
void vector_double2 (vector<double>& v);

//------------------------------------------------------------------------------
