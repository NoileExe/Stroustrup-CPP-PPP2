

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream> и устанавливает using namespace std
//#include <iomanip>						//Для возможности форматирования потока вывода
//#include <sstream>						//Для строкового потока ввода-вывода
#include <bitset>


using namespace std;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

class bitsetPPN
{
	std::bitset<32> pnb;		//Сами данные
	
	//Вычисляет длину числа целого типа в битовом представлении начиная с крайней левой единицы
	template <class T> unsigned int num2bit_length(const T& num);
	
public:
	bitsetPPN() : pnb(0)		{  }
	
	bitsetPPN(unsigned int p, unsigned int c, bool n, bool d, bool v, bool g) : pnb(0)
	{
		unsigned int ln = num2bit_length(p);
		if(ln > pnb.size() - 7)		error("very big 1-st argument PFN ( bitsetPPN() class initialisation )");		//7 первых битов занимают другие числа и флаги
		pnb = p << 7;
		
		ln = num2bit_length(c);
		if(ln > 3)				error("very big 2-nd argument CCA ( bitsetPPN() class initialisation )");		//CCA не должен занимать больше 3ех бит
		pnb |= c << 4;
		
		pnb[3] = n;		// nonreachable
		pnb[2] = d;		// dirty
		pnb[1] = v;		// valid
		pnb[0] = g;		// global
	}
	
	
	unsigned int Get_PFN() const { return		(pnb >> 7).to_ulong(); }
	unsigned int Get_CCA() const { return		(pnb >> 4).to_ulong() & 0x7; /* Маска 7 (hex/dec/oct) == 0111 (bin) */ }
	bool Get_nonreachable() const { return		bool(pnb[3]); /* 4ый справа бит */ }
	bool Get_dirty() const { return				bool(pnb[2]); /* 3ий справа бит */ }
	bool Get_valid() const { return				bool(pnb[1]); /* 2ой справа бит */ }
	bool Get_global() const { return			bool(pnb[0]); /* 1ый справа бит */ }
	
	unsigned int Set_PFN(unsigned int n)
	{
		unsigned int ln = num2bit_length(n);
		if(ln > pnb.size() - 7)		error("very big argument ( Set_PFN() )");		//7 первых битов занимают другие числа и флаги
		pnb &= 0x7F; //Обнуляются все биты кроме 7 крайних справа. Маска 127 (dec) == 0x7F (hex) == 01111111 (bin)
		pnb |= n << 7;
		return		Get_PFN();
	}
	
	unsigned int Set_CCA(unsigned int n)
	{
		unsigned int ln = num2bit_length(n);
		if(ln > 3)				error("very big argument ( Set_CCA() )");		//CCA не должен занимать больше 3ех бит
		pnb &= 0xFFFFFF8F; //Обнуляются биты отвечающие за CCA (4ый, 5ый, 6ой). Маска 8 (dec) == 0x8 (hex) == 1000 (bin)
		pnb |= n << 4;
		return		Get_CCA();
	}
	
	bool Set_nonreachable(bool n)
	{
		pnb[3] = n;
		return		Get_nonreachable();
	}
	
	bool Set_dirty(bool n)
	{
		pnb[2] = n;
		return		Get_dirty();
	}
	
	bool Set_valid(bool n)
	{
		pnb[1] = n;
		return		Get_valid();
	}
	
	bool Set_global(bool n)
	{
		pnb[0] = n;
		return		Get_global();
	}
};

//Вычисляет длину числа целого типа в битовом представлении начиная с крайней левой единицы
template <class T>
unsigned int bitsetPPN::num2bit_length(const T& num)
{
	string str { std::bitset<8*sizeof(T)>(num).to_string() };
	
	if (str.empty())		error("empty num string ( num2bit_length() )");
	
	else while( str[0] == '0' )
		if(str.size() == 0)		break;
		else					str.erase(str.begin());
	
	return str.size();
}

std::ostream& operator<<(ostream& ost, const bitsetPPN& ppn)
{
	return ost << "uintPPN: " << '\n'
			   << "\tPFN: " << ppn.Get_PFN() << '\n'
			   << "\tCCA: " << ppn.Get_CCA() << '\n' << boolalpha
			   << "\tnonreachable: " << ppn.Get_nonreachable() << '\n'
			   << "\tdirty: " << ppn.Get_dirty() << '\n'
			   << "\tvalid: " << ppn.Get_valid() << '\n'
			   << "\tglobal: " << ppn.Get_global() << noboolalpha;
}

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			cout << "\n\n";
			
			bitsetPPN p2 {};
			cout << "p2: " << p2 << "\n\n";
			
			
			bitsetPPN p3 {1001, 5, false, true, true, true};
			//bitsetPPN p3 {1001, 5, 0, 1, 1, 1}; //работает одинаково
			cout << "p3: " << p3 << "\n\n";
			
			
			try { cout << " 123456789  " << std::bitset<8*sizeof(unsigned int)>(123456789) << endl;		cout << "Set_PFN(123456789): " << p3.Set_PFN(123456789) << "\n\n"; }
			catch (exception& e) { cerr << "Error ( main() ): " << e.what() << "\n\n"; }
			catch (...) { cerr << "Oops! Unknown error! ( main() )\n\n"; }
			
			//				0xFFFFFF (24 единицы)
			try { cout << " 16777215   " << std::bitset<8*sizeof(unsigned int)>(16777215) << endl;		cout << "Set_PFN(16777215): "  << p3.Set_PFN(16777215) << "\n\n"; }
			catch (exception& e) { cerr << "Error ( main() ): " << e.what() << "\n\n"; }
			catch (...) { cerr << "Oops! Unknown error! ( main() )\n\n"; }
			
			//				0x1FFFFFF (25 единиц) - максимально допустимое число помещающееся в поле PFN
			try { cout << " 33554431   " << std::bitset<8*sizeof(unsigned int)>(33554431) << endl;		cout << "Set_PFN(33554431): "  << p3.Set_PFN(33554431) << "\n\n"; }
			catch (exception& e) { cerr << "Error ( main() ): " << e.what() << "\n\n"; }
			catch (...) { cerr << "Oops! Unknown error! ( main() )\n\n"; }
			
			//				0x3FFFFFF (26 единиц) - поле PFN заходит на CCA
			try { cout << " 67108863   " << std::bitset<8*sizeof(unsigned int)>(67108863) << endl;		cout << "Set_PFN(67108863): "  << p3.Set_PFN(67108863) << "\n\n"; }
			catch (exception& e) { cerr << "Error ( main() ): " << e.what() << "\n\n"; }
			catch (...) { cerr << "Oops! Unknown error! ( main() )\n\n"; }
			
			//				0x2000000 (1 единица в 26ой позиции) - поле PFN заходит на CCA
			try { cout << " 33554432   " << std::bitset<8*sizeof(unsigned int)>(33554432) << endl;		cout << "Set_PFN(33554432): "  << p3.Set_PFN(33554432) << "\n\n"; }
			catch (exception& e) { cerr << "Error ( main() ): " << e.what() << "\n\n"; }
			catch (...) { cerr << "Oops! Unknown error! ( main() )\n\n"; }
			
			try { cout << " 12345678   " << std::bitset<8*sizeof(unsigned int)>(12345678) << endl;		cout << "Set_PFN(12345678): "  << p3.Set_PFN(12345678) << "\n\n"; }
			catch (exception& e) { cerr << "Error ( main() ): " << e.what() << "\n\n"; }
			catch (...) { cerr << "Oops! Unknown error! ( main() )\n\n"; }
			
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