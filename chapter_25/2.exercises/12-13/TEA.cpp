


#include "TEA.h"		//Включает <yes_or_no.h>, <iomanip>, <sstream> и <fstream>



//------------------------------------------------------------------------------

void encipher(
	const unsigned long *const v,
	unsigned long *const w,
	const unsigned long *const k)
{
	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0;
	unsigned long delta = 0x9E3779B9;
	unsigned long n = 32;
	while(n-->0) {
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
	}
	w[0]=y; w[1]=z;
}

//------------------------------------------------------------------------------

// Here is the corresponding deciphering function:
void decipher(
	const unsigned long *const v,
	unsigned long *const w,
	const unsigned long *const k)
{ 
	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0xC6EF3720;
	unsigned long delta = 0x9E3779B9;
	unsigned long n = 32;
	// sum = delta<<5, in general sum = delta * n
	while(n-->0) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum&3];
	}
	w[0]=y; w[1]=z;
}

//------------------------------------------------------------------------------

void messageSend(const string& infile, const string& outfile, string& key)
{
	const int nchar = 2*sizeof(long);	// 64 bits
	const int kchar = 2*nchar;			// 128 bits
	
	while(key.size() < kchar)	key += '0'; // Дополнение ключа
	
	ifstream inf(infile.c_str());
	if(!inf)		error("wrong input file name [ messageGet() ]");
	
	ofstream outf(outfile.c_str());
	if(!outf)		error("wrong output file name [ messageGet() ]");

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());
	unsigned long outptr[2];    
	char inbuf[nchar];
	unsigned long* inptr = reinterpret_cast<unsigned long*>(inbuf);
	int count = 0;

	while( inf.get(inbuf[count]) )
	{
		outf << hex;	// �?спользуется 16-ричный вывод
		if (++count == nchar)
		{
			encipher(inptr, outptr, k);
			
			// Заполнение ведущими нулями
			outf << setw(8) << setfill('0') << outptr[0] << ' '
				 << setw(8) << setfill('0') << outptr[1] << ' ';
			
			count = 0;
		}
	}

	if(count) // Заполнение
		while(count != nchar)
		{
			inbuf[count++] = '0';
			encipher(inptr, outptr, k);
			outf << outptr[0] << ' ' << outptr[1] << ' ';
		}
}

//------------------------------------------------------------------------------

void messageGet(const string& infile, const string& outfile, string& key)
{
	const int nchar = 2*sizeof(long);	// 64 bits
	const int kchar = 2*nchar;			// 128 bits
	
	while(key.size() < kchar)	key += '0'; // Дополнение ключа
	
	ifstream inf(infile.c_str());
	if(!inf)		error("wrong input file name [ messageGet() ]");
	
	ofstream outf(outfile.c_str());
	if(!outf)		error("wrong output file name [ messageGet() ]");

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());
	unsigned long inptr[2];    
	char outbuf[nchar + 1];
	outbuf[nchar] = 0; // нуль-терминатор
	unsigned long* outptr = reinterpret_cast<unsigned long*>(outbuf);
	inf.setf(ios_base::hex, ios_base::basefield); // �?спользуется 16-ричный ввод

	while (inf >> inptr[0] >> inptr[1])
	{
		decipher(inptr,outptr,k);
		outf << outbuf;
	}
}

//------------------------------------------------------------------------------