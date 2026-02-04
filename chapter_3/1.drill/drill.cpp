//Автоматизация набора письма

#include <console_encoding.h>
#include <std_lib_facilities.h>


int main()
{
	ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора
	
	cout << "Введите имя адресата и нажмите Enter: ";
	string first_name; //fisrst_name - переменная типа string
	cin >> first_name; // считываем символы в fisrst_name
	
	cout << "Введите возраст адресата и нажмите Enter: ";
	int age;
	cin >> age;
	if ((age <= 0) || (age >= 110)) {
		cout << "\n\nОШИБКА!!!\n\n" << age << "? Серьёзно!? Ты наверно шутишь.";
		
		cin.get();
		cout << "\n\nНажмите Enter чтобы закрыть программу";
		cin.get();
		return EXIT_SUCCESS;
	}
	
	cout << "Введите имя общего знакомого и нажмите Enter: ";
	string friend_name;
	cin >> friend_name;
	
	cout << "Введите пол общего знакомого и нажмите Enter (m - мужчина, f - женщина): ";
	char friend_sex = {0};
	cin >> friend_sex;
	if ((friend_sex != 'm') && (friend_sex != 'f')) {
		simple_error("Вы не ввели пол общего знакомого в требуемом формате");
		return EXIT_SUCCESS;
	}
	
	cout << "\n\nДорогая " << first_name << ",\n"
		 << "Как у тебя дела? У меня всё хорошо. Я скучаю по тебе. ";
		 
	if (friend_sex == 'm') {
		cout << "Если ты увидишь " << friend_name << ", пожалуйста, попроси его";
	}
	else if (friend_sex == 'f') {
		cout << "Если ты увидишь " << friend_name << ", пожалуйста, попроси её";
	}
		
	cout << " позвонить мне.\nЯ помню, что у тебя недавно был день рождения и "
		 << "тебе исполнилось " << age << " лет вот мои своевременные "
		 << "поздравления тебе! ";
		 
	if (age <= 12)
		cout << "На следующий год тебе исполнится " << age+1 << ".";
		
	if (age == 17)
		cout << "В следующем году ты сможешь голосовать.";
		
	if (age >= 70)
		cout << "Я надеюсь, что ты не скучаешь на пенсии.";
		 
	cout << "\nЕсть много интересных вещей, "
		 << "которые я бы хотел  рассказать, но всё же это лучше в живую, "
		 << "скажу лишь одно: скоро я буду рядом!\n\nИскренне твой\n\n\nЯ =P\n\n";
	
	keep_window_open();
	return EXIT_SUCCESS;
}
