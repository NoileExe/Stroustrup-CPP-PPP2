

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream> и устанавливает using namespace std
#include <iomanip>		//Для возможности форматирования потока вывода
#include <sstream>		//Для строкового потока ввода-вывода
#include <fstream>		//Для файлового потока ввода-вывода


using namespace std;

//------------------------------------------------------------------------------

// Шифровка
void encipher(const unsigned long *const v, unsigned long *const w, const unsigned long *const k);

// Расшифровка
void decipher(const unsigned long *const v, unsigned long *const w, const unsigned long *const k);

//------------------------------------------------------------------------------

//Зашифровывает с ключом key текст из файла infile в файл outfile
void messageSend(const string& infile, const string& outfile, string& key);

//Расшифровывает с ключом key текст из файла infile в файл outfile
void messageGet(const string& infile, const string& outfile, string& key);

//------------------------------------------------------------------------------