


#include <yes_or_no.h>
#include "vctr.h"


#define vector vctr


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

namespace ucptr
{
	template< typename T > class unique_ptr {
	public:
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
		
		T* release() {
			T* p = link;
			link = nullptr;
			return p;
		}
		
	private:
		T* link;
	};
}


template<typename T> ostream& operator<<(ostream &ost, const ucptr::unique_ptr<T>& u)
{ return ost << &*u; }

template<typename T> ostream& operator<<(ostream &ost, const vector<T>& vt)
{
	ost << "{ ";
	
	for(int i = 0; i < vt.size(); ++i)
		if(i != vt.size()-1)	ost << vt.at(i) << ", ";
		else					ost << vt.at(i);
	
	ost << " }";
	
	return ost;
}

template<typename T> istream& operator>>(istream &ist, vector<T>& vt) {
	char ch{0};
	ist >> ch;
	if (ch != '{') {
		ist.clear(ios_base::failbit);
		return ist;
	}
	
	//Добавление элеметов к существующему вектору
	/*for(T v; ist >> v; ) {
		vt.push_back(v);
		ist >> ch;
		if (ch != ',')		break;
	}*/
	
	//Перезапись вектора с новыми значениями
	vector<T> buf {};
	for(T v; ist >> v; ) {
		buf.push_back(v);
		ist >> ch;
		if (ch != ',')		break;
	}
	
	if(ist.bad() || ch !='}')		error("bad input ( operator>> FOR vector<T> )");
	ist.clear();
	
	if(buf.size() > 0 )		vt = buf;
	
	return ist;
}


//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			ucptr::unique_ptr< vector<int> > uv { new vector<int> {} };
			
			cout << "Enter new some int values for vector<int> (format '{val, val, val ...}')\n";
			cin >> *uv;
			cout << "\n" << "*uv with " << uv->size() << " elements\n" << *uv << "\n\n";
			
			//uv->operator=(vector<int> {});
			//cout << "\n" << "*uv with " << uv->size() << " elements\n" << *uv << "\n\n";
			
			vector<int> v { *uv.release() };
			cout << "\n" << "vector<int> v {unique_ptr release()}\n" << v << "\n\n";
			
			if(&*uv)	cout << "uv == " << uv << "\n\n";
			else		cout << "*uv is NULLPTR\n\n";
			
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