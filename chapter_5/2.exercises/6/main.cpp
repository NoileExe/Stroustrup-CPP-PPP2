/*Программа для перевода градусов из Фаренгейта в Цельсии и обратно*/

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


double conversion(double degrees, char fc)
{
	switch (fc)
		{
			case 'f': case 'F':
				return (5.0/9) * (degrees-32);
				break;
				
			case 'c': case 'C':
				return ((9.0/5) * degrees)+32;
				break;
				
			default:
				string err_str = "conversion(): Введен неодопустимый символ (" + fc + ')';
				error (err_str);
				break;
	}
}

int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	//\xC2\xB0 - значок градуса в Unicode
	cout << "Программа для перевода Цельсий -> Фаренгейт И Фаренгейт -> Цельсий"
		 << ".\n\nВводите значения температуры и далее, через пробел или без, е"
		 << "диницу измерения 'f', 'F' - Фаренгейт (\xC2\xB0" << "F); 'c', 'C' "
		 << "- Цельсий (\xC2\xB0" << "C). Для отделения десятичной части исполь"
		 << "зуется точка (.)\nДля завершения ввода комбинация клавиш CTRL+Z\n"
		 << "Для подтверждения ввода - Enter\n\nПример:\n24C\n17.1 f\n\n";
	
	double gradus = 0;
	char fc = ' ';
	
	while (cin >> gradus >> fc)
	{
		
		switch (fc)
		{
			case 'f': case 'F':
				if ( conversion(gradus, fc)  < -273.15 )
				{
					cout << "Не может быть температуры ниже абсолютной по " 
						 << "Кельвину (-273.15 \xC2\xB0" << "C"
						 << "или 0 \xC2\xB0" << "K)."
						 << " У вас получилось: "
						 << conversion(gradus, fc) << "\n\n";
					break;
				}
					
				cout << gradus << " \xC2\xB0" << "F = "
					 << conversion(gradus, fc) << " \xC2\xB0" << "C\n\n";
				cin.clear();
				break;
				
			case 'c': case 'C':
				if (gradus < -273.15)
				{
					cout << "Не может быть температуры ниже абсолютной по Кельвину (-273.15 \xC2\xB0" << "C или 0 \xC2\xB0" << "K).\n\n";
					break;
				}
					
				cout << gradus << " \xC2\xB0" << "C = "
					 << conversion(gradus, fc) << " \xC2\xB0" << "F\n\n";
					
				cin.clear();
				break;
				
			default:
				cout << "Неверно введена единица измерения! Допустимые вари"
					 << "анты: 'f', 'F' - Фаренгейт ("<< " \xC2\xB0" << "F); "
					 << "'c', 'C' - Цельсий (\xC2\xB0" << "C).\n";
				cin.clear();
				break;
		}
		
		
	}
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}
