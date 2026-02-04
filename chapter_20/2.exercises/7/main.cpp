


#include <yes_or_no.h>
#include "document.h"


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

template<typename Iter>		// *Iter яв-ся контейнером с операцией индексирования []
Iter last_alphabet_line(Iter first, Iter last) {
	if(first == last)		return last;
	
	Iter max_alpha {first++};
	//++first;
	while(first != last)
	{
		if( (*max_alpha)[0] < (*first)[0] )			max_alpha = first;
		else if( (*max_alpha)[0] == (*first)[0] )
			for(int i=0;   i < max_alpha->size()  &&  i < first->size();   ++i) {
				if( (*max_alpha)[i] < (*first)[i] )			{ max_alpha = first;	break; }
				else if( (*max_alpha)[i] > (*first)[i] )	break;
			}
		
		++first;
	}
	
	return max_alpha;
}

string last_alphabet_string(vector<string>& vs) {
	if(vs.size() == 0)		error("empty vector [last_alphabet_string(vector<string>&)]");
	
	string max_alpha {vs[0]};
	for(int i = 1; i < vs.size(); ++i)
		if( max_alpha[0] < (vs[i])[0] )			max_alpha = vs[i];
		else if( max_alpha[0] == (vs[i])[0] )
			for(int j=0;   j < max_alpha.size()  &&  j < (vs[i]).size();   ++j) {
				if( max_alpha[j] < (vs[i])[j] )				{ max_alpha = vs[i];	break; }
				else if( max_alpha[j] > (vs[i])[j] )		break;
			}
	
	return max_alpha;
}

istream& operator>>(istream& is, vector<string>& s)
{
	string str {""};
	//Пока не будет достигнут конец документа или пока не возникнет ошибка
	for(char ch; is.get(ch); ) {
		str += ch;		//Добавление символа
		
		//Если строка закончилась - добавить её в вектор
		if(ch == '\n') {
			s.push_back(str);
			str = "";
		}
	}
	
	return is;
}

int main()
{
	while (true) {
		try
		{
			Document abc;
			
			{
				string ioname {"input.txt"};
				ifstream ifs { ioname };
				if (!ifs)	error("Unable to open file '" + ioname + "'");
				ifs.exceptions(ifs.exceptions()|ios_base::badbit);
				
				ifs >> abc;
			}
			
			
			/*
			auto l = abc.begin().get_line();
			//++l;
			advance(l, 1);
			auto s = (*l).begin();
			*/
			
			//auto s = abc.begin().next_line().get_position();
			
			//cout << &*s;
			
			
			auto s1 = last_alphabet_line( abc.begin().get_line(), abc.end().get_line() );
			for(auto ch : *s1)	cout << ch;
			
			//--------------------------------------------------------------------------
			
			vector<string> s;
			
			{
				string ioname {"input.txt"};
				ifstream ifs { ioname };
				if (!ifs)	error("Unable to open file '" + ioname + "'");
				ifs.exceptions(ifs.exceptions()|ios_base::badbit);
				
				ifs >> s;
			}
			
			
			string s2 = last_alphabet_string( s );
			cout << s2;
			
			auto s3 = last_alphabet_line( s.begin(), s.end() );
			cout << *s3;
			
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