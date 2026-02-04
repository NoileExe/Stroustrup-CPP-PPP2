


#include <typeinfo>
#include <yes_or_no.h>
#include <std_lib_facilities.h>


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

template<typename T>
istream& operator>>(istream &ist, vector<T>& vt) {
	//Добавление элеметов к существующему вектору
	//for(T v; ist >> v; )		vt.push_back(v);
	
	//Перезапись вектора с новыми значениями
	vector<T> buf {};
	for(T v; ist >> v; )		buf.push_back(v);
	
	if( ist.bad()  &&  !ist.eof() )		error("bad input ( operator>> FOR vector<" + to_string( typeid(T).name() ) + "> )"); //
	ist.clear();
	
	if(buf.size() > 0 )		vt = buf;
	
	return ist;
}

//------------------------------------------------------------------------------

namespace uptr {
	template< typename T >
	class unique_ptr {
	public:
		unique_ptr() : link{nullptr}		{  }
		explicit unique_ptr(T* p) : link{p}		{  }
		~unique_ptr() { if(link)	delete link; }
		
		//Копирующие конструктор и присваивание запрещены
		unique_ptr(const unique_ptr& u) = delete;
		unique_ptr& operator=(const unique_ptr& v) = delete;
		
		//Перемещающие конструктор и присваивание запрещены
		unique_ptr(unique_ptr&& v) = delete;
		unique_ptr& operator=(unique_ptr&& v) = delete;
		
		T& operator*() const		{ return *link; }
		T* operator->() const		{ return link; }
		
		T* reset(T* p) {
			this->~unique_ptr();
			link = p;
			return link;
		}
		
		T* release() {
			T* p = link;
			link = nullptr;
			return p;
		}
		
	private:
		T* link;
	};
}

//Джек записывает числа типа double в массив, возвращая их кол-во в count
double* get_from_jack(int* count)
{
	int sz {0};
	int space {8};
	
	string ioname {"jack.txt"};
	ifstream ifs { ioname };
	if (!ifs)	error("Unable to open file '" + ioname + "'");
	ifs.exceptions(ifs.exceptions()|ios_base::badbit);
	
	uptr::unique_ptr<double> jack_array {new double[space]};
	for(double din {0.0};  ifs >> din;  )
	{
		if(sz == space) {
			space *= 2;
			uptr::unique_ptr<double> tmp {new double[space]};
			for(int i=0; i<sz; ++i)		(&*tmp)[i] = (&*jack_array)[i];
			jack_array.reset( tmp.release() );
		}
		
		(&*jack_array)[sz] = din;
		++sz;
	}
	
	/*cout << "\nsize: " << sz << "\nspace: " << space << "\n{ ";
	for(int i=0; i<sz; ++i)		cout << (&*jack_array)[i] << " ";
	cout << "}";*/
	
	*count = sz;
	return jack_array.release();
}

//------------------------------------------------------------------------------

//Джилл заполняет вектор
vector<double>* get_from_jill()
{
	string ioname {"jill.txt"};
	ifstream ifs { ioname };
	if (!ifs)	error("Unable to open file '" + ioname + "'");
	ifs.exceptions(ifs.exceptions()|ios_base::badbit);
	
	uptr::unique_ptr< vector<double> > jill_vector {new vector<double>};
	ifs >> *jill_vector;
	
	return jill_vector.release();
}

//------------------------------------------------------------------------------

template<typename Iter>
void out_array(Iter b, Iter e)
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


template<typename Iter>
double* high(Iter first, Iter last)
{
	if(!&*first  ||  !&*last)		error("nullptr in function high(iter, iter) arguments");
	if( first == last )				return first;
	
	Iter h = first;
	for(Iter p = first; p != last; ++p)
		if(*p > *h)		h = p;
	
	return h;
}

int main()
{
	while (true) {
		try
		{
			int jack_count = 0;
			double* jack_data = get_from_jack(&jack_count);
			vector<double>* jill_data = get_from_jill();
			
			double* jack_high = high(jack_data,   jack_data+jack_count);
			double* jill_high = high( &((*jill_data)[0]), &((*jill_data)[jill_data->size()-1]) );
			
			cout << "Jill max: " << *jill_high << ";\t\tJack max: " << *jack_high << endl;
			cout << "Jill vector size: " << jill_data->size() << ";\tJack array size: " << jack_count << endl;
			
			cout << "Jill vector:\t" << *jill_data;
			cout << "\nJack array:\t";
			out_array(jack_data, jack_data+jack_count);
			
			cout << "\n--------------------------------------------------------------------------\n\n";
			
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