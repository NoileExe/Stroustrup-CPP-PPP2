


#include <yes_or_no.h>
#include "vctr.h"


#define vector vctr


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename T> ostream& operator<<(ostream &ost, const ucptr::unique_ptr<T>& u)
{ return ost << &*u; }

template<typename T> ostream& operator<<(ostream &ost, const ucptr::counted_ptr<T>& u)
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
			cout << "\n-----------------------Standart test-----------------------\n";
			
			{
				//ucptr::counted_ptr< vector<int> > cpv { vector<int> {1,2,3} }; //Тоже работает
				
				ucptr::counted_ptr< vector<int> > cpv { vector<int> {} };
				cout << "Enter new some int values for vector<int> (format '{val, val, val ...}')\n";
				cin >> *cpv;
				
				cout << "\n" << "*cpv with " << cpv->size() << " elements\n" << *cpv << "\n\n";
				if(&*cpv)	cout << "*cpv == " << cpv << "\n\n";
				else		cout << "*cpv == NULLPTR\n\n";
				
				//Работает
				//cpv->operator=(vector<int> {});
				//cout << "\n" << "*cpv with " << cpv->size() << " elements\n" << *cpv << "\n\n";
				
				vector<int> v { *cpv.release() };
				cout << "\n" << "vector<int> uvv {counted_ptr release()}\n" << v << "\n\n";
				if(&*cpv)	cout << "*cpv == " << cpv << "\n\n";
				else		cout << "*cpv == NULLPTR\n\n";
			}
			
			cout << "\n-------------------------Copy test-------------------------\n";
			{
				ucptr::counted_ptr< vector<int> > cpv0 { vector<int> {100,200,300} };
				cout << "\n" << "*cpv0 with " << cpv0->size() << " elements\n" << *cpv0 << "\n\n";
				
				ucptr::counted_ptr< vector<int> > cpv1 { vector<int> {1,2,3,4,5,6,7,8,9,0} };
				cout << "\n" << "*cpv1 with " << cpv1->size() << " elements\n" << *cpv1 << "\n\n";
				
				ucptr::counted_ptr< vector<int> > cpvc { cpv0 };
				cout << "\n" << "*cpvc (copy constructor) with " << cpvc->size() << " elements\n" << *cpvc << "\n\n";
				
				cpvc = cpv1;
				cout << "\n" << "*cpvc (copy assignment) with "  << cpvc->size() << " elements\n" << *cpvc << "\n\n";
			}
			
			cout << "\n------------------Elem of container test-------------------\n";
			{
				vector< ucptr::counted_ptr<double> > vec_cpv {ucptr::counted_ptr<double> {1.2}, ucptr::counted_ptr<double> {3.4}, 
																ucptr::counted_ptr<double> {5.6}, ucptr::counted_ptr<double> {7.8}};
				vec_cpv.push_back( ucptr::counted_ptr<double> {1.23} );
				vec_cpv.push_back( ucptr::counted_ptr<double> {2.34} );
				vec_cpv.push_back( ucptr::counted_ptr<double> {34.5} );
				
				//cout << vec_cpv << "\n\n";		//Печатает адреса
				for(int i=0; i < vec_cpv.size(); ++i)		cout << *vec_cpv[i] << "\n";
			}
			
			cout << "\n---------------------Function argument---------------------\n";
			{
				ucptr::counted_ptr< vector<double> > cpv1 { vector<double> {1.23, 2.34, 34.5} };
				ucptr::counted_ptr< vector<double> > cpv2 { vector<double> {1.2, 3.4, 5.6, 7.8, 9.0} };
				
				//Не работает
				//ucptr::counted_ptr< vector<double> > cpv2 { };
				//cpv2 = ucptr::counted_ptr< vector<double> > { vector<double> {1.2, 3.4, 5.6, 7.8, 9.0} } ;
				
				
				vector< ucptr::counted_ptr<vector<double>> > vec_cpv;
				vec_cpv.push_back( cpv1 );
				vec_cpv.push_back( cpv2 );
				
				//Не работает
				//vec_cpv.push_back( ucptr::counted_ptr<vector<double>> { vector<double> {1.23, 2.34, 34.5} } );
				//vec_cpv.push_back( ucptr::counted_ptr<vector<double>> { vector<double> {1.2, 3.4, 5.6, 7.8, 9.0} } );
				
				//Оба варианта рабочие
				//for(int i=0; i < vec_cpv.size(); ++i)		cout << *vec_cpv[i] << "\n";
				for(int i=0; i < vec_cpv.size(); ++i)		{ operator<<(cout,*vec_cpv[i]);		cout << "\n"; }
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