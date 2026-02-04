/*
	Подсчет суммы денег по количеству монет разных номиналов..
	Также предусматривает правильное склонение слов "копейка" и "рубль".
*/

#include <console_encoding.h>
#include <std_lib_facilities.h>


string endingcoin(int);
string endingrub(int);
string endingkop(int);

int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Для работы программы отвечайте на вопросы вводя ответы в виде целых "
		 << "чисел. Подтверждение ввода производится по нажатию клавиши Enter\n";
	
	cout << "\nСколько у вас монет номиналом 1 копейка? \n";
	int kop1 = 0;
	cin >> kop1;
	
	cout << "\nСколько у вас монет номиналом 5 копеек? \n";
	int kop5 = 0;
	cin >> kop5;
	
	cout << "\nСколько у вас монет номиналом 10 копеек? \n";
	int kop10 = 0;
	cin >> kop10;
	
	cout << "\nСколько у вас монет номиналом 50 копеек? \n";
	int kop50 = 0;
	cin >> kop50;
	
	cout << "\nСколько у вас монет номиналом 1 рубль? \n";
	int rub1 = 0;
	cin >> rub1;
	
	cout << "\nСколько у вас монет номиналом 2 рубля? \n";
	int rub2 = 0;
	cin >> rub2;
	
	cout << "\nСколько у вас монет номиналом 5 рублей? \n";
	int rub5 = 0;
	cin >> rub5;
	
	cout << "\nСколько у вас монет номиналом 10 рублей? \n";
	int rub10 = 0;
	cin >> rub10;
	
	cout << "\n\nУ вас " <<	kop1	<< endingcoin(kop1)	<< "номиналом 1 копейка.\n"
		 << "У вас " <<		kop5	<< endingcoin(kop5)	<< "номиналом 5 копеек.\n"
		 << "У вас " <<		kop10	<< endingcoin(kop10)	<< "номиналом 10 копеек.\n"
		 << "У вас " <<		kop50	<< endingcoin(kop50)	<< "номиналом 50 копеек.\n"
		 << "У вас " <<		rub1	<< endingcoin(rub1)	<< "номиналом 1 рубль.\n"
		 << "У вас " <<		rub2	<< endingcoin(rub2)	<< "номиналом 2 рубля.\n"
		 << "У вас " <<		rub5	<< endingcoin(rub5)	<< "номиналом 5 рублей.\n"
		 << "У вас " <<		rub10	<< endingcoin(rub10)	<< "номиналом 10 рублей.\n";
	
	int summ = kop1 + kop5*5 + kop10*10 + kop50*50 + rub1*100 + rub2*200
			   + rub5*500 + rub10*1000;
	int count_rub = summ/100;
	int count_kop = summ%100;
	
	cout << "\nОбщая стоимость ваших монет равна "
		 << count_rub << endingrub(count_rub)
		 << count_kop << endingkop(count_kop) << "\n";
	
	keep_window_open();
	return EXIT_SUCCESS;
}

string endingcoin(int val)
{
	if ((val == 1 || (val%10) == 1) && val != 11)
		return " монета ";
	else if ((val == 2 || (val%10) == 2 || val == 3 || (val%10) == 3
			|| val == 4 || (val%10) == 4) && val != 12 && val != 13
			&& val != 14)
		return " монеты ";
	else
		return " монет ";
}

string endingrub(int val)
{
	if ((val == 1 || (val%10) == 1) && val != 11)
		return " рубль ";
	else if ((val == 2 || (val%10) == 2 || val == 3 || (val%10) == 3
			|| val == 4 || (val%10) == 4) && val != 12 && val != 13
			&& val != 14)
		return " рубля ";
	else
		return " рублей ";
}

string endingkop(int val)
{
	if ((val == 1 || (val%10) == 1) && val != 11)
		return " копейка.";
	else if ((val == 2 || (val%10) == 2 || val == 3 || (val%10) == 3
			|| val == 4 || (val%10) == 4) && val != 12 && val != 13
			&& val != 14)
		return " копейки.";
	else
		return " копеек.";
}
