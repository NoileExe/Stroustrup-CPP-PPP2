//Данная программа вывод на экран символы и их числовое значение по табл. ASCII

#include <yes_or_no.h>
#include <std_lib_facilities.h>
#include <locale>

int main()
{
	std::locale::global(std::locale("")); 
	//std::wcin.imbue(std::locale());
	std::wcout.imbue(std::locale());
	
	wcout << L"Данная программа вывод на экран символы и их числовое значение по "
		  << L"табл. ASCII.\n\nЧтобы начать выберите (введите номер подходящего "
		  << L"пункта и нажмите Enter) один из следующих вариантов:\n"
		  << L"1. Символы от 0 до 255\n" << L"2. Символы от -128 до 127\n"
		  << L"3. Символы от -255 до -1\n"
		  << L"4. Символы в последовательности установленной для текущего устройства"
		  << L" по умолчанию\n\n";
	
	int i = 0;
	wcin >> i;
	
	//Русские буквы в UTF находятся в диапазоне 1040 - 1105
	switch (i) {
		case 1: // от 0 до 255
			i = 0;
			while (i<256)
			{
				wcout << wchar_t(i) << L'\t' << i << L'\n';
				++i;
			}
			break;
		
		case 2: // от -128 до 127
			i = -128;
			while (i<128)
			{
				wcout << wchar_t(i) << L'\t' << i << '\n';
				++i;
			}
			break;
		
		case 3: // от -256 до -1
			i = -256;
			while (i<0)
			{
				wcout << wchar_t(i) << L'\t' << i << L'\n';
				++i;
			}
			break;
			
		case 4: // отталкиваясь от того какой код у символа нуль
			i = int('0')-48;
			while (i < int('0')+208)
			{
				wcout << wchar_t(i) << L'\t' << i << L'\n';
				++i;
			}
			break;
		
		default:
			wcout << L"Нужно быть внимательнее. К вводу принимаются только номера перечисленных пунктов!\n";
			break;
	}


	wcin.get();
	wcout << L"\n\nНажмите Enter чтобы закрыть программу";
	wcin.get();
	return EXIT_SUCCESS;
}