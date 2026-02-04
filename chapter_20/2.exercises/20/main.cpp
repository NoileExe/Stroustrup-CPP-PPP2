


#include <yes_or_no.h>
#include "lst.h"
#include "vctr.h"
//#include <ctime>		//Для рандомизации по текущему времени (секунде)
#include <chrono>


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

//Вставка значения в последовательность в порядке возрастания (пред. <= и следующее > val)
//Container должен иметь функции-члены begin(), end(), push_back(val), push_front(val), insert(p, val),
// при чём условие составлено так, что предполагается добавление элемента ф-цией insert после элемента, на который указывает p
template<class Conteiner, class V> void ordered_insertion(Conteiner& cntr, V val)
{
	auto b = cntr.begin();
	auto e = cntr.end();
	
	//Если последовательность пуста, создаём в ней первый элемент
	if(b == e)								{ cntr.push_back(val);		return; }
	
	for(auto p = b; p != e; ++p) {
		auto next = p;
		++next;
		
		//Если значение нового элемента меньше первого в последовательности - добавляем в начало
		if(p == b  &&  val < *p)
			{ cntr.push_front(val);		return; }
		
		//Добавляем новое число в последовательность если значение нового элемента >= перебираемого И < следующего за ним - 
		if( next == e  ||  ( *p <= val && val < *(next) ) )
			{ cntr.insert(p, val);		return; }
	}
}


//Вставка значения в последовательность в порядке возрастания (пред. <= и следующее > val)
//Container должен иметь функции-члены begin(), end(), push_back(val), insert(p, val),
// при чём условие составлено так, что предполагается добавление элемента ф-цией insert перед элементом, на который указывает p
//Для версий vector и list из STL
template<class Conteiner, class V> void ordered_insertion_orig(Conteiner& cntr, V val)
{
	auto b = cntr.begin();
	auto e = cntr.end();
	
	//Если последовательность пуста, создаём в ней первый элемент
	if(b == e)								{ cntr.push_back(val);		return; }
	
	for(auto p = b; p != e; ++p) {
		auto next = p;
		++next;
		
		//Если достигли конца последовательности - добавляем новый элемент в конец
		if(next == e  &&  val >= *p)		{ cntr.push_back(val);		return; }
		
		//Если в последовательности встретилось значение больше значения нового элемента - добавляем новый элемент перед ним
		if( val < *p )					{ cntr.insert(p, val);		return; }
	}
}

//------------------------------------------------------------------------------

//Остаток от деления на n (число в диапазоне [0; n))
int randnum_mersen(int n) {
	/*srand( time(NULL) );
	return	rand() % n;*/
	
	//Работает гораздо быстрее первого метода, но может намертво зациклиться
	random_device rd;
	mt19937 mersenne(rd());		// инициализируем Вихрь Мерсенна случайным стартовым числом
	//mt19937 mersenne(static_cast<unsigned int>(time(0)));	// инициализируем Вихрь Мерсенна случайным стартовым числом
	
	return		mersenne() % n;
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

template<typename Iter>		//Требует Input_iterator<Iter>()
Iter high(Iter first, Iter last)
//Возвращает итератор, указывающий на элемент из диапазона [first, last), имеющий наибольшее значение
{
	//cout << to_string(&*first) << "\t" << &*last << endl;
	//keep_window_open("0");
	
	if(!&*first  ||  !&*last)		error("nullptr in function high(iter, iter) arguments");
	if( first == last )				return last;
	
	Iter high = first;
	for(Iter p = first; p != last; ++p)
		if(*p > *high)		high = p;
	
	return high;
}

int main()
{
	while (true) {
		try
		{
			int N {0};
			while(!N)		N = randnum_mersen(10);
			cout << "\ncount: " << N << "\n\n\n";
			
			{
				vctr<int> vi;
				my_list::list<int> li;
				
				auto tv01 = chrono::system_clock::now();
				
				for(int i = N; i > 0; --i) {
					auto t1 = chrono::system_clock::now();
					int num = randnum_mersen(N);
					ordered_insertion(vi, num);
					auto t2 = chrono::system_clock::now();
					
					out_array(vi.begin(), vi.end());
					cout << "for add _" << num << "_ time: "
						 << chrono::duration_cast< chrono::milliseconds >(t2-t1).count() << "(ms) | "
						 << chrono::duration_cast< chrono::microseconds >(t2-t1).count() << "(mcs) | "
						 << chrono::duration_cast< chrono::nanoseconds >(t2-t1).count() << "(ns)" << "\n\n";
				}
				
				auto tv02 = chrono::system_clock::now();
				cout << "for add " << N << " objects in vctr<int> time (ms): " << chrono::duration_cast< chrono::milliseconds >(tv02-tv01).count() << "\n\n\n\n";
				
				
				auto tl01 = chrono::system_clock::now();
				
				for(auto i = N; i > 0; --i) {
					auto t1 = chrono::system_clock::now();
					int num = randnum_mersen(N);
					ordered_insertion(li, num);
					auto t2 = chrono::system_clock::now();
					
					out_array(li.begin(), li.end());
					cout << "for add _" << num << "_ time: "
						 << chrono::duration_cast< chrono::milliseconds >(t2-t1).count() << "(ms) | "
						 << chrono::duration_cast< chrono::microseconds >(t2-t1).count() << "(mcs) | "
						 << chrono::duration_cast< chrono::nanoseconds >(t2-t1).count() << "(ns)" << "\n\n";
				}
				
				auto tl02 = chrono::system_clock::now();
				cout << "for add " << N << " objects in my_list::list<int> time (ms): " << chrono::duration_cast< chrono::milliseconds >(tl02-tl01).count() << "\n\n\n\n";
			}
			
			keep_window_open("0");
			
			{ 
				vector<int> vi;
				list<int> li;
				
				auto tv01 = chrono::system_clock::now();
				
				for(int i = N; i > 0; --i) {
					auto t1 = chrono::system_clock::now();
					int num = randnum_mersen(N);
					ordered_insertion_orig(vi, num);
					auto t2 = chrono::system_clock::now();
					
					out_array(vi.begin(), vi.end());
					cout << "for add _" << num << "_ time: "
						 << chrono::duration_cast< chrono::milliseconds >(t2-t1).count() << "(ms) | "
						 << chrono::duration_cast< chrono::microseconds >(t2-t1).count() << "(mcs) | "
						 << chrono::duration_cast< chrono::nanoseconds >(t2-t1).count() << "(ns)" << "\n\n";
				}
				
				auto tv02 = chrono::system_clock::now();
				cout << "for add " << N << " objects in vctr<int> time (ms): " << chrono::duration_cast< chrono::milliseconds >(tv02-tv01).count() << "\n\n\n\n";
				
				
				auto tl01 = chrono::system_clock::now();
				
				for(auto i = N; i > 0; --i) {
					auto t1 = chrono::system_clock::now();
					int num = randnum_mersen(N);
					ordered_insertion_orig(li, num);
					auto t2 = chrono::system_clock::now();
					
					out_array(li.begin(), li.end());
					cout << "for add _" << num << "_ time: "
						 << chrono::duration_cast< chrono::milliseconds >(t2-t1).count() << "(ms) | "
						 << chrono::duration_cast< chrono::microseconds >(t2-t1).count() << "(mcs) | "
						 << chrono::duration_cast< chrono::nanoseconds >(t2-t1).count() << "(ns)" << "\n\n";
				}
				
				auto tl02 = chrono::system_clock::now();
				cout << "for add " << N << " objects in my_list::list<int> time (ms): " << chrono::duration_cast< chrono::milliseconds >(tl02-tl01).count() << "\n\n\n\n";
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