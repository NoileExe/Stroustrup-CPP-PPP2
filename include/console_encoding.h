
#include <iostream>
#include <string>
#include <clocale>

#ifdef _WIN32
	#include <windows.h>
#endif

//Console Code Page для установки UTF-8 кодировки в консоли
// на время существования объекта
class ConsoleCP
{
public:
	ConsoleCP()
	{
		// 1. Сохраняем текущую C-локаль (общая часть для всех систем)
		const char* currentLocale = std::setlocale(LC_ALL, nullptr);
		if (currentLocale)
			oldLocale = currentLocale;

	#ifdef _WIN32
		// 2. Сохраняем кодовые страницы Windows
		oldInCP = GetConsoleCP();
		oldOutCP = GetConsoleOutputCP();

		// 3. Устанавливаем UTF-8 для консоли
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);

		// 4. Устанавливаем UTF-8 локаль для корректной работы cin/cout
		std::setlocale(LC_ALL, ".UTF8");
	#else
		// В Linux просто устанавливаем системную локаль (обычно UTF-8)
		std::setlocale(LC_ALL, "");
	#endif
	}

	~ConsoleCP()
	{
	#ifdef _WIN32
		// Восстанавливаем кодовые страницы Windows
		SetConsoleCP(oldInCP);
		SetConsoleOutputCP(oldOutCP);
	#endif
		// Восстанавливаем C-локаль
		if (!oldLocale.empty())
			std::setlocale(LC_ALL, oldLocale.c_str());
	}

private:
	std::string oldLocale;
#ifdef _WIN32
	unsigned int oldInCP = 0;
	unsigned int oldOutCP = 0;
#endif
};

