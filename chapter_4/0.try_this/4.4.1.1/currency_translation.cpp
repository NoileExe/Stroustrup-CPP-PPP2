//Перевод гривен, рублей, юаней в доллары по курсу на 07.03.2019 23:00

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


string correct_ending(int, string);

int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите числа (можно дробные) и, через пробел, валюту (гривна (g),"
		 << " рубль (r) или юань (y)) нажимайте Enter для преобразования.\n\n"
		 << "Чтобы завершить работу с программой на пустой строчке любой текст "
		 << "или нажмите комбинацию CTRL+Z и затем клавишу Enter.\n\n";
	
	const double ua2doll = 0.038;
	const double rub2doll = 0.015;
	const double chn2doll = 0.15; //Курсы валют (количество доллара в ден. ед.)
	double summ = 0;
	string currency = ""; //Валюта: гривна (или g), рубль (r) или юань (y)
	
	//Повторяем след. инструкции пока вводятся числа
	while (cin >> summ >> currency)
	{
		//cin >> currency;
		if (currency == "g")
			cout << summ << correct_ending(int(summ), currency) << "<=> "
			//Выводим сумму и, относительно цифры, значение валюты в правильном склонении
			//Обязательно отсекаем десятичную часть
				 << int(summ*ua2doll) << correct_ending(int(summ*ua2doll), "d")
			//Выводим результат в долларах (целая часть) и, относительно цифры, 
			//значение валюты в правильном склонении
				 << int((summ*ua2doll-int(summ*ua2doll))*100)
				 //Число с десятичной частью МИНУС целая часть затем УМНОЖИТЬ НА 100
				 //чтобы получить целое число центов и т.к. 100 центов = 1 доллар,
				 //остальная часть не имеет значения
				 << correct_ending(int((summ*ua2doll-int(summ*ua2doll))*100), "c")
				 << "\n\n";
			//Выводим результат в центах (десятичная часть) и, относительно цифры, 
			//значение валюты в правильном склонении
		else if (currency == "r")
			cout << summ << correct_ending(int(summ), currency) << "<=> "
				 << int(summ*rub2doll) << correct_ending(int(summ*rub2doll), "d")
				 << int((summ*rub2doll-int(summ*rub2doll))*100)
				 << correct_ending(int((summ*rub2doll-int(summ*rub2doll))*100), "c")
				 << "\n\n";
		else if (currency == "y")
			cout << summ << correct_ending(int(summ), currency) << "<=> "
				 << int(summ*chn2doll) << correct_ending(int(summ*chn2doll), "d")
				 << int((summ*chn2doll-int(summ*chn2doll))*100)
				 << correct_ending(int((summ*chn2doll-int(summ*chn2doll))*100), "c")
				 << "\n\n";
		else cout << "Тут какая-то ошибка! Вводите в виде:\n	СУММА ВАЛЮТА\n,"
				  << "где СУММА -  денежная сумма в заданной валюте для преобра"
				  << "зования, а ВАЛЮТА - текстовое представление гривна (g), "
				  << "рубль (r) или юань (y)\n\n";
	}
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}

string correct_ending(int num, string unit)
{
	if (unit == "g")
	{
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " гривна ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " гривны ";
		else
			return " гривен ";
	}
	else if (unit == "r")
	{
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " рубль ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " рубля ";
		else
			return " рублей ";
	}
	else if (unit == "y")
	{
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " юань ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " юаня ";
		else
			return " юаней ";
	}
	else if (unit == "d")
	{
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " доллар ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " доллара ";
		else
			return " долларов ";
	}
	else if (unit == "c")
	{
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " цент ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " цента ";
		else
			return " центов ";
	}
}
