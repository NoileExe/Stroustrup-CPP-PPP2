

#include <cstdio>
#include <yes_or_no.h>
#include <std_lib_facilities.h>

#ifdef _WIN32
	#include <windows.h>
	#include <io.h>
#else
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/file.h>
#endif


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

class File_handle {
	FILE* f;
	string n;		//Полный путь к файлу (либо имя если в одной папке с программой)
	
public:
	File_handle(const string ioname, const char* mode = "r+") : f{fopen(ioname.c_str(), mode)}, n{ioname}
	{
		string s {mode};
		if (!f  ||  (s != "r"  &&  s != "w"  &&  s != "a"  &&  s != "r+"  &&  s != "w+"  &&  s != "b"))
		{
			if(f)		fclose(f);
			error("File '" + ioname + "' could not be opened with '" + to_string(mode) + "' mode!");
		}
		
		
		#ifdef _WIN32
			// Windows: Блокируем первые 100 ГБ файла (хватит для любого файла)
			HANDLE hFile = (HANDLE)_get_osfhandle(_fileno(f));
			if (!LockFile(hFile, 0, 0, MAXDWORD, MAXDWORD)) {
				std::fclose(f);
				error("File '" + ioname + "' is locked by another process!");
			}
		#else
			// Linux/POSIX: LOCK_EX (эксклюзивная блокировка), LOCK_NB (не ждать, если занято)
			int fd = fileno(f);
			if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
				std::fclose(f);
				error("File '" + ioname + "' is locked by another process!");
			}
		#endif
	}
	
	//Копирующие конструктор и присваивание
	File_handle(const File_handle& v) = delete;
	File_handle& operator=(const File_handle& v) = delete;
	
	//Перемещающие конструктор и присваивание
	File_handle(File_handle&& v) = delete;
	File_handle& operator=(File_handle&& v) = delete;
	
	~File_handle()		{ if (f && fclose(f))		error("File stream could not close!"); }
	
	FILE* file() const { return f; }
	const string& name() const { return n; }
};

//------------------------------------------------------------------------------

void out_file(const File_handle& fh)
{
	FILE* fp = fh.file();
	if (!fp)		error("File '" + fh.name() + "' could not be opened");

	std::rewind(fp);	// Сбрасываем указатель чтения в начало (если файл уже читали)

	// fscanf возвращает количество успешно считанных элементов
	// %1023s считывает строку до пробела (макс 1023 символа + \0)
	for (char word[1024];   std::fscanf(fp, "%1023s", word) == 1;   )
		std::cout << word << '\n';

	// Проверка на ошибки после чтения
	if (ferror(fp))
		error("Error reading file '" + fh.name() + "'");
}

int main()
{
	while (true) {
		try
		{
			File_handle fh {"file.txt"};
			out_file(fh);
			keep_window_open("1");
			
			//В целом выдаст ошибку из-за блокировки файла системой
			try
			{
				//File_handle fh0 {"file.txt", "y"};	//Ошибочный режим открытия файла - программа вылетает
				File_handle fh0 {"file.txt"};
				out_file(fh0);
			}
			catch (exception& e) {
				cerr << "Error ( main() ): " << e.what() << '\n';
			}
			
			keep_window_open("2");
			
			try
			{
				File_handle fh0 {"out.txt", "a"};
				fputs("New text line\n", fh0.file());
				
				cout << "Try write text to 'out.txt'\n";
			}
			catch (exception& e) {
				cerr << "Error ( main() ): " << e.what() << '\n';
			}
			
			keep_window_open("~");
			return 0;
		}

		catch (exception& e) {
			cerr << "Error ( main() ): " << e.what() << '\n';
			
			if ( Y_or_N(quit_question) )	return 1001;
		}

		catch (...) {
			cerr << "Oops! Unknown error! ( main() )\n";
			
			if ( Y_or_N(quit_question) )	return 1002;
		}
	}
}
