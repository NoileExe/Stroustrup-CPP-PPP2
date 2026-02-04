
//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>	//Для возможности форматирования потока вывода
#include <sstream>	//Для строкового потока ввода-вывода


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

struct Node
{
	Node* prev;
	Node* succ;
	
	Node(Node* p, Node* n) : prev{p}, succ{n}		{  }
	Node() : prev{nullptr}, succ{nullptr}		{  }
};

//Отдельно взятая строка знающая о строках предшествующей и следующей за текущей
class Message {
	Node pos;		//Строки-соседи
	string msg;		//Текст строки
	
public:
	Message() : pos{}/*, msg{""}*/		{  }
	Message(Node* p, Node* n, const string& txt) : pos{p,n}/*, msg{txt}*/		{  }
	
	Node*& prev() { return pos.prev; }
	Node*& next() { return pos.succ; }
	
	string& text() { return msg; }
	const string& text() const { return msg; }
};

//------------------------------------------------------------------------------

inline Message* get_input(std::istream& is)
{
	Node* prev = nullptr;
	Node* next = nullptr;
	
	string buffer {"yes"};
	//getline(is, buffer);
	return new Message{prev,next,buffer};
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			do {
				Node* n1 = new Node;
				Node* n2 = new Node;
				//cout << "\n\nEnter message:\n> ";
				cout << "\n\n";
				Message* p = get_input(cin);
				
				ostringstream oss;
				oss << n1;
				auto max = oss.str().size();
				
				cout << left << setw(max) << "n1" << "   " << left << setw(max) << "n2" << "   " << left << setw(max) << "p" << endl;
				cout << left << setw(max) << (to_string(sizeof(*n1)) + " byte") << "   "
					 << left << setw(max) << (to_string(sizeof(*n2)) + " byte") << "   "
					 << left << setw(max) << (to_string(sizeof(*p)) + " byte")  << endl;
				cout << n1 << "   " << n2 << "   " << p << endl;
				cout << left << setw(max) << int(n1) << " - " << left << setw(max) << int(n2) << "   " << left << setw(max) << int(p) << endl;
				cout << right << setw(max+2) << abs(int(n2)-int(n1)) << " byte\n";
				
				
				oss.str("");
				oss.clear();
				
				Node* rnode = (int(n2) > int(n1)) ? n2 : n1;
				Node* lnode = (int(n2) > int(n1)) ? n1 : n2;
				
				//Размещение в памяти с расстояними от конца левого объекта до начала левого
				if( rnode == n2 )			oss << "[ n1 ] " << ( int(n2)-(int(n1)+sizeof(*n1)) ) << "B [ n2 ]";
				else if( rnode == n1 )		oss << "[ n2 ] " << ( int(n1)-(int(n2)+sizeof(*n2)) ) << "B [ n1 ]";
				else						error("bad rnode pointer");
				
				
				if( int(p) > int(n2) )
					cout << oss.str() << "  " << ( int(p)-(int(rnode)+sizeof(*rnode)) ) << "B    [        p       ]\n";
				
				else if( int(p) < int(n1) )
					cout << "[        p       ]  " << ( int(lnode)-(int(p)+sizeof(*p)) ) << "B    " << oss.str() << endl;
					
				else
				{
					if( rnode == n2 )		cout << "[ n1 ] ";
					else					cout << "[ n2 ] ";
					
					cout << ( int(p)-(int(lnode)+sizeof(*lnode)) ) << "B [        p       ]" << ( int(rnode)-(int(p)+sizeof(*p)) );
					
					if( rnode == n2 )		cout << "B [ n2 ] ";
					else					cout << "B [ n1 ] ";
				}
				
				
				
				delete p;
				
				cout << "\n--------------------------------------------------------------------------";
			} while( Y_or_N("Repeat?") );
			
			
			cin.putback('\n');
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