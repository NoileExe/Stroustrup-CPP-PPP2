

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <map>
#include <numeric>
#include <yes_or_no.h>


using namespace std;


const string quit_question = "Close program?";


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
	
	cout << " }";
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\nIntroduce the words to calculate their quantity\n\n";
			
			/*C++ is а general purpose programming language designed to make
			programming more enjoyable for the serious programmer. Except for minor
			details, C++ is а superset of the C programming language. In addition to
			the facilities provided by C, C++ provides flexible and efficient facilities for
			defining new types.*/
			
			map<string, int> words;		//Поддержка пар (слово, частота); индексируется строками
			for(string s;   cin>>s;   )
				++words[s];
			
			//Поиск максимального кол-ва (значения int)
			int max = (words.begin() != words.end()) ? words.begin()->second : 0;
			for(const auto& p : words)
				if(p.second > max)		max = p.second;
			
			while(max > 0)
			{
				for(const auto& p : words)
					if(p.second == max)		cout << p.second << " : " << p.first << '\n';
				
				--max;
			}
			
			cout << "\n\n--------------------------------------------------------------------------\n";
			
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