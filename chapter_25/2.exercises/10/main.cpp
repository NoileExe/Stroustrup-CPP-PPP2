

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream> и устанавливает using namespace std
//#include <iomanip>						//Для возможности форматирования потока вывода
//#include <sstream>						//Для строкового потока ввода-вывода
#include <bitset>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

struct PPN
{
	unsigned int PFN : 22;
	int : 3;
	unsigned int CCA : 3;
	bool nonreachable : 1;
	bool dirty : 1;
	bool valid : 1;
	bool global : 1;
};

std::ostream& operator<<(ostream& ost, const PPN& ppn)
{
	return ost << "PPN: " << '\n'
			   << "\tPFN: " << ppn.PFN << '\n'
			   << "\tCCA: " << ppn.CCA << '\n'
			   << "\tnonreachable: " << ppn.nonreachable << '\n'
			   << "\tdirty: " << ppn.dirty << '\n'
			   << "\tvalid: " << ppn.valid << '\n'
			   << "\tglobal: " << ppn.global;
}

//------------------------------------------------------------------------------

class uintPPN
{
	const unsigned int size = 8*sizeof(unsigned int);	//Размер занимаемой памяти
	unsigned int pni;									//Сами данные
	
	//Вычисляет длину числа целого типа в битовом представлении начиная с крайней левой единицы
	template <class T> unsigned int num2bit_length(const T& num);
	
public:
	uintPPN() : pni(0)		{  }
	
	uintPPN(unsigned int p, unsigned int c, bool n, bool d, bool v, bool g) : pni(0)
	{
		unsigned int ln = num2bit_length(p);
		if(ln > size - 7)		error("very big 1-st argument PFN ( uintPPN() class initialisation )");		//7 первых битов занимают другие числа и флаги
		pni = p << 7;
		
		ln = num2bit_length(c);
		if(ln > 3)				error("very big 2-nd argument CCA ( uintPPN() class initialisation )");		//CCA не должен занимать больше 3ех бит
		pni |= c << 4;
		
		pni |= ((n) ? 1 : 0) << 3;		// nonreachable
		pni |= ((d) ? 1 : 0) << 2;		// dirty
		pni |= ((v) ? 1 : 0) << 1;		// valid
		pni |= ((g) ? 1 : 0);			// global
	}
	
	
	unsigned int Get_PFN() const { return		(pni >> 7); }
	unsigned int Get_CCA() const { return		(pni >> 4) & 0x7; /* Маска 7 (hex/dec/oct) == 0111 (bin) */ }
	bool Get_nonreachable() const { return		bool((pni >> 3) & 1); /* 4ый справа бит */ }
	bool Get_dirty() const { return				bool((pni >> 2) & 1); /* 3ий справа бит */ }
	bool Get_valid() const { return				bool((pni >> 1) & 1); /* 2ой справа бит */ }
	bool Get_global() const { return			bool(pni & 1);		  /* 1ый справа бит */ }
	
	unsigned int Set_PFN(unsigned int n)
	{
		unsigned int ln = num2bit_length(n);
		if(ln > size - 7)		error("very big argument ( Set_PFN() )");		//7 первых битов занимают другие числа и флаги
		pni &= 0x7F; //Обнуляются все биты кроме 7 крайних справа. Маска 127 (dec) == 0x7F (hex) == 01111111 (bin)
		pni |= n << 7;
		return		Get_PFN();
	}
	
	unsigned int Set_CCA(unsigned int n)
	{
		unsigned int ln = num2bit_length(n);
		if(ln > 3)				error("very big argument ( Set_CCA() )");		//CCA не должен занимать больше 3ех бит
		pni &= 0xFFFFFF8F; //Обнуляются биты отвечающие за CCA (4ый, 5ый, 6ой). Маска 8 (dec) == 0x8 (hex) == 1000 (bin)
		pni |= n << 4;
		return		Get_CCA();
	}
	
	bool Set_nonreachable(bool n)
	{
		pni &= 0xFFFFFFF7; //Обнуляется бит отвечающий за nonreachable (3ий). Маска 7 (dec) == 0x7 (hex) == 0111 (bin)
		pni |= ((n) ? 1 : 0) << 3;
		return		Get_nonreachable();
	}
	
	bool Set_dirty(bool n)
	{
		pni &= 0xFFFFFFFB; //Обнуляется бит отвечающий за dirty (2ой). Маска 11 (dec) == 0xB (hex) == 1011 (bin)
		pni |= ((n) ? 1 : 0) << 2;
		return		Get_dirty();
	}
	
	bool Set_valid(bool n)
	{
		pni &= 0xFFFFFFFD; //Обнуляется бит отвечающий за valid (1ый). Маска 13 (dec) == 0xD (hex) == 1101 (bin)
		pni |= ((n) ? 1 : 0) << 1;
		return		Get_valid();
	}
	
	bool Set_global(bool n)
	{
		pni &= 0xFFFFFFFE; //Обнуляется бит отвечающий за global (0ой). Маска 14 (dec) == 0xE (hex) == 1110 (bin)
		pni |= ((n) ? 1 : 0);
		return		Get_global();
	}
};

//Вычисляет длину числа целого типа в битовом представлении начиная с крайней левой единицы
template <class T>
unsigned int uintPPN::num2bit_length(const T& num)
{
	string str { std::bitset<8*sizeof(T)>(num).to_string() };
	
	if (str.empty())		error("empty num string ( num2bit_length() )");
	
	else while( str[0] == '0' )
		if(str.size() == 0)		break;
		else					str.erase(str.begin());
	
	return str.size();
}

std::ostream& operator<<(ostream& ost, const uintPPN& ppn)
{
	return ost << "uintPPN: " << '\n'
			   << "\tPFN: " << ppn.Get_PFN() << '\n'
			   << "\tCCA: " << ppn.Get_CCA() << '\n'
			   << "\tnonreachable: " << ppn.Get_nonreachable() << '\n'
			   << "\tdirty: " << ppn.Get_dirty() << '\n'
			   << "\tvalid: " << ppn.Get_valid() << '\n'
			   << "\tglobal: " << ppn.Get_global();
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			PPN p1 {0,0,0,0,0,0};
			cout << p1 << "\n\n";

			p1.PFN = 1234;
			p1.CCA = 5;
			p1.nonreachable = 1;
			p1.dirty = 0;
			p1.valid = 1;
			p1.global = 1;
			cout << "p1: " << p1 << "\n\n";
			
			
			uintPPN p2 {};
			cout << "p2: " << p2 << "\n\n";
			
			
			//uintPPN p3 {1001, 5, false, true, true, true};
			uintPPN p3 {1001, 5, 0, 1, 1, 1}; //работает одинаково
			cout << "p3: " << p3 << "\n\n";
			
			p3.Set_PFN(1234);
			p3.Set_CCA(7);				//Максимально допустимое число, т.к. занимает 3 бита (0111 (bin))
			p3.Set_nonreachable(1);		//Всё что отличается от нуля даёт значение true: хоть 10, хоть -2
			p3.Set_dirty(0);
			p3.Set_valid(1);
			p3.Set_global(1);
			cout << "p3: " << p3 << "\n\n";
			
			
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