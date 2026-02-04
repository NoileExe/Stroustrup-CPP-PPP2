//Перевод гривен, рублей, юаней, евро и фунтов стерлинга в доллары
//по курсу на 08.03.2019 19:00

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


string correct_ending(int, char); //Объявление функции

int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Вводите числа (можно дробные) и, через пробел, валюту (гривна (g),"
		 << " рубль (r), юань (y), евро (e) или фунт стерлинга (f)) нажимайте E"
		 << "nter для преобразования\nСУММА ? - вызов справки\n\nЧтобы завершит"
		 << "ь работу с программой на пустой строчке любой текст или нажмите ко"
		 << "мбинацию CTRL+Z и затем клавишу Enter.\n\n"; //Приглашение пользователю
	
	const double ua2doll = 0.038; //укр.гривна
	const double rub2doll = 0.015;//росс.рубль
	const double chn2doll = 0.15; //кит.юань
	const double eu2doll = 1.12;  //евро
	const double fun2doll = 1.31; //фунт стерлинга
	//Курсы валют (количество доллара в 1 денежной единице)
	
	double summ = 0; //вводимая сумма
	char currency; //Вводимое значение валюты
	//Валюта: гривна (или g), рубль (r), юань (y), евро (e) или фунт стерлинга (f)
	
	while (cin >> summ >> currency)   //Повторяем след. инструкции пока производится ввод
	{
		switch (currency) //Выбор по введённому значению валюты
		{
		case '?':
		//При вводе ЛЮБАЯСУММА ? - выводится справка
		//Значения для case константные, т.е. не изменяются в ходе работы программы
			cout << "\nСПРАВКА\n\nВвод производится в виде:\n	СУММА ВАЛЮТА\n"
				 << ",где СУММА - денежная сумма в заданной валюте для преобра"
				 << "зования, а ВАЛЮТА - текстовое представление гривна (g), р"
				 << "убль (r), юань (y), евро (e) или фунт стерлинга (f)\nСУМ"
				 << "МА ? - вызов справки\n\nЧтобы завершить работу с программо"
				 << "й на пустой строчке любой текст или нажмите комбинацию CTR"
				 << "L+Z и затем клавишу Enter.\n\n";
			break;
		
		case 'g':
			cout << summ << correct_ending(int(summ), currency) << "<=> "
			/*Выводим сумму и, относительно цифры, значение валюты в правильном
			 склонении (функция correct_ending). Обязательно отсекаем десятичную часть,
			 конвертируя переменную в тип int*/
				 << int(summ*ua2doll) << correct_ending(int(summ*ua2doll), 'd')
			//Выводим результат в долларах (целая часть) и, относительно цифры, 
			//значение валюты в правильном склонении
				 << int((summ*ua2doll-int(summ*ua2doll))*100)
			/*Число с десятичной частью МИНУС целая часть затем УМНОЖИТЬ НА 100
			чтобы получить целое число центов и т.к. 100 центов = 1 доллар,
			остальная часть не имеет значения*/
				 << correct_ending(int((summ*ua2doll-int(summ*ua2doll))*100), 'c')
				 << "\n\n";
			//Выводим результат в центах (десятичная часть) и, относительно цифры, 
			//значение валюты в правильном склонении
			break;
		
		case 'r':
			cout << summ << correct_ending(int(summ), currency) << "<=> "
				 << int(summ*rub2doll) << correct_ending(int(summ*rub2doll), 'd')
				 << int((summ*rub2doll-int(summ*rub2doll))*100)
				 << correct_ending(int((summ*rub2doll-int(summ*rub2doll))*100), 'c')
				 << "\n\n";
			break;
			
		case 'y':
			cout << summ << correct_ending(int(summ), currency) << "<=> "
				 << int(summ*chn2doll) << correct_ending(int(summ*chn2doll), 'd')
				 << int((summ*chn2doll-int(summ*chn2doll))*100)
				 << correct_ending(int((summ*chn2doll-int(summ*chn2doll))*100), 'c')
				 << "\n\n";
			break;
		
		case 'e':
			cout << summ << " евро <=> " << int(summ*eu2doll)
				 << correct_ending(int(summ*eu2doll), 'd')
				 << int((summ*eu2doll-int(summ*eu2doll))*100)
				 << correct_ending(int((summ*eu2doll-int(summ*eu2doll))*100), 'c')
				 << "\n\n";
			break;
			
		case 'f':
			cout << summ << correct_ending(int(summ), currency) << "<=> "
				 << int(summ*fun2doll) << correct_ending(int(summ*fun2doll), 'd')
				 << int((summ*fun2doll-int(summ*fun2doll))*100)
				 << correct_ending(int((summ*fun2doll-int(summ*fun2doll))*100), 'c')
				 << "\n\n";
			break;
		
		default:
		//Если с суммой будет введено что-то помимо предусмотренных валют или "?"
		//выводим ошибку
			cout << "Тут какая-то ошибка! Вводите в виде:\n	СУММА ВАЛЮТА\n,г"
				 << "де СУММА - денежная сумма в заданной валюте для преобразо"
				 << "вания, а ВАЛЮТА - текстовое представление гривна (g), руб"
				 << "ль (r), юань (y), евро (e) или фунт стерлинга (f)\n\n";
			break;
		}
	}
	
	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}

string correct_ending(int num, char unit)
//Получаем на вход сумму и значение валюты. Евро - не склоняется
{
	switch (unit) //Выбор по переданному из функции main() значению валюты
	{
	case 'g':
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " гривна ";
		/*
Если СУММА=1 или единица на её конце (напр. 471) и значение введённой суммы не 11,
то выводится значение валюты в нужном склонении (правильная форма склонения
названия валюты в зависимости от цифры, т.е. в данном конкретном случае
"471 гривНА", а не "471 гривен")
		*/
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " гривны ";
		/*
Если СУММА=2, 3, 4 или эти цифры на её конце (напр. 471) и значение введённой
суммы не 12, 13 или 14, то выводится значение валюты в нужном склонении
		*/
		else return " гривен "; //Значение валюты во всех остальных случаях
		break;
		
	case 'r':
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " рубль ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " рубля ";
		else return " рублей ";
		break;
			
	case 'y':
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " юань ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " юаня ";
		else return " юаней ";
		break;
			
	case 'f':
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " фунт стерлинга ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " фунта стерлинга ";
		else return " фунтов стерлинга ";
		break;
			
	case 'd':
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " доллар ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " доллара ";
		else return " долларов ";
		break;
		
	case 'c':
		if ((num == 1 || (num%10) == 1) && num != 11)
			return " цент ";
		else if ((num == 2 || (num%10) == 2 || num == 3 || (num%10) == 3 || 
				  num == 4 || (num%10) == 4) && num != 12 && num != 13 && num != 14)
			return " цента ";
		else return " центов ";
		break;
	}
}
