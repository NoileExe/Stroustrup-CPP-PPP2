//Данная программа "поглощает" заранее указанные слова, заменяя их на ФУУУУ!

#include <yes_or_no.h>
#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Данная программа ''поглощает'' заранее указанные слова\nВводите сл"
		 << "ова, для подтверждения ввода каждого нажмите Enter; для завершения"
		 << " ввода нажмите CTRL+Z и затем Enter\n\n";

	//vector<string> censor (2);
	//censor[0]= "ass";
	//censor[1]= "pelephone";
	
	//vector<string> censor;
	//censor.push_back("ass");
	//censor.push_back("pelephone");

	vector<string> censor = { "ass", "pelephone" };
	//Все варианты работают в C++11, но последний вариант не работает в wxDev-C++
	//(возможно из-за поддержки компилятором только старого стандарта C++98)

	//почему ты жопа не поднимаешь телепон свой
	vector<string> words;
	for (string one_word; cin >> one_word; )
		words.push_back(one_word);

	cout << "\n\nКоличество введённых слов: " << words.size() << "\n\n";
	
	//sort(words.begin(), words.end());
	sort(words);
	//Оба варианта работают в C++11, но последний вариант не работает в wxDev-C++
	//(возможно из-за поддержки компилятором только старого стандарта C++98)
	
	for (int i = 0; i < words.size(); ++i) //Перебор уже отсортированных введённых слов
		if (i == 0 || words[i - 1] != words[i]) //Если это не первы элемент массива и слово не повторяется то...
			for (int j = 0; j < censor.size(); ++j) //Перебор массива нежелательных слов для сверки и цензуры
				if (words[i] == censor[j])
				{//Если  текущее проверяемое слово из введённых совпадает с одним из списка нежелательных
					cout << "ФУУУУ!\n"; //Запикиваем его и...
					j = censor.size(); //...завершаем перебор нежелательных слов
				}
				else if (j == (censor.size()-1))
				//Если весь массив нежелательных слов перебран (и не найдено совпадений - начальное условие)
					cout << words[i] << '\n';

	cout << "\n\n";
	press_Enter_key();
	return EXIT_SUCCESS;
}