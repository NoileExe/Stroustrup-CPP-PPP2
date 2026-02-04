
#include "Points.h"
#include <yes_or_no.h>
#include <console_encoding.h>

//------------------------------------------------------------------------------

ConsoleCP cp {};	//Включает русский если не включен в настройках компилятора

//------------------------------------------------------------------------------

const string quit_question = "Закрыть программу?";


//Получение от пользователя имени файла для ввода или вывода
string get_file_name(string greetings) {
	cout << greetings;
	
	string ioname;
	cin >> ioname;
	
	return ioname;
}

//Выводит в поток вывода ost все элементы вектора объектов Point
void print_points(ostream& ost, const vector<points::Point>& p)
{
	for (int i=0; i < p.size(); ++i)
		if ( i != p.size()-1 )		ost << p[i] << '\n';
		else						ost << p[i];
	
	//for (const auto &i : p)
	//for (Point i : p)
	//	ost << i << '\n';
}


int main()
{
	while (true)
	try {
		using namespace points;
	
		cout << "\nПустой объект Point(): " << Point() << "\n";
		cout << "\nPoint (x=150, y=300): "  << Point(150, 300) << "\n\n";
		
		press_Enter_key(true);
		
		//------------------------ЗАПОЛНЕНИЕ ВЕКТОРА (клава, файл, цикл)------------------------
		
		vector<Point> original_points;
		
		do { //Ввод в вектор определённого кол-ва значений с клавиатуры
			
			cout << "\nВведите координаты в виде [ ЦЕЛОЕ_ЧИСЛО_X ; ЦЕЛОЕ_ЧИСЛО_Y ]: ";
			
			Point p;
			cin >> p;
			
			original_points.push_back( p );
			cout << "\nВведённый с клавиатуры объект Point(): " << original_points [original_points.size()-1] << "\n\n";
		
		} while (original_points.size() < 1);
		
		
		//Берём координаты из файла
		ifstream ifs { "points.txt" };
		if (!ifs)	error("Невозможно открыть файл 'points.txt' (должен лежать рядом с программой)");
		
		for (Point p; ifs >> p; )
			original_points.push_back(p);
		
		ifs.close(); //ifs.close(ioname, ios_base::in)
		
		
		//Автозаполнение вектора определённым кол-вом значений
		for (int i = 0; i < 7; ++i)
		{
			Point p = {i, i*i};
			original_points.push_back(p);
		}
		
		press_Enter_key();
		
		//------------------------ЗАПОЛНЕНИЕ ВЕКТОРА (клава, файл, цикл)------------------------
		//--------------------------------------------------------------------------------------
		//--------------------------------ВЫВОД КООРДИНАТ В ФАЙЛ--------------------------------
		
		string ioname = get_file_name("Введите имя файла для работы: ");
		
		
		ofstream ofs { ioname };
		if (!ofs)	error("Невозможно открыть файл '" + ioname + "'");
		
		print_points(ofs, original_points); //вывод пар координат в файл
		
		cout << "\nВыполнен вывод значений в файл\n";
		ofs.close(); //ofs.close(ioname, ios_base::out)
		press_Enter_key();
		
		//--------------------------------ВЫВОД КООРДИНАТ В ФАЙЛ--------------------------------
		//--------------------------------------------------------------------------------------
		//------------------ЗАПОЛНЕНИЕ ВЕКТОРА ИЗ ФАЙЛА ВЫВОДА ДРУГОГО ВЕКТОРА------------------
		
		ifs.open(ioname);
		if (!ifs)	error("Невозможно открыть файл '" + ioname + "'");
		
		vector<Point> processed_points;
		
		for (Point p; ifs >> p; )
			processed_points.push_back(p);
		
		if ( processed_points.size() > 0 )
			cout << "\nЗаполнен вектор processed_points\n";
		
		ifs.close(); //ifs.close(ioname, ios_base::in)
		
		//------------------ЗАПОЛНЕНИЕ ВЕКТОРА ИЗ ФАЙЛА ВЫВОДА ДРУГОГО ВЕКТОРА------------------
		//--------------------------------------------------------------------------------------
		//--------------------------------ПЕЧАТЬ ОБОИХ ВЕКТОРОВ---------------------------------
		
		cout << "\nВектор original_points:\n";
		print_points(cout, original_points);	//вывод пар координат на экран
		
		cout << "\n\nВектор processed_points:\n";
		print_points(cout, processed_points);	//вывод пар координат на экран
		
		press_Enter_key();
		
		//--------------------------------ПЕЧАТЬ ОБОИХ ВЕКТОРОВ---------------------------------
		//--------------------------------------------------------------------------------------
		//---------------------------СРАВНЕНИЕ ВЕКТОРОВ НА РАВЕНСТВО----------------------------
		
		const vector<Point>& a { original_points };
		const vector<Point>& b { processed_points };
		
		for (int i=0; i < a.size(); ++i)
			if ( a.size() != b.size() || a[i] != b[i] )
				{ cout << "Что-то не так!";		break; }
			
			else if ( i == a.size()-1 )
				cout << "Векторы равны!";
		
		//---------------------------СРАВНЕНИЕ ВЕКТОРОВ НА РАВЕНСТВО----------------------------
		
		
		if ( Y_or_N(quit_question) )    return 0;
		//press_Enter_key();
	}

	catch (points::CTRL_Z_throw) {
		cerr << "\nПрограмма завершена пользователем.";
		press_Enter_key();
		/*if ( Y_or_N(quit_question) )*/	return 1001;
	}

	catch (exception& e) { //Для системных исключений при работе с программой
		cerr << "Ошибка: " << e.what() << '\n';
		
		if ( Y_or_N(quit_question) )	return 1002;
	}

	catch (...) { //Для непредвиденных исключений
		cerr << "Упс! Неизвестное исключение!\n";
		
		if ( Y_or_N(quit_question) )	return 1003;
	}
}
