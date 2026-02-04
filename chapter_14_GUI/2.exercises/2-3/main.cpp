

//#define _USE_MATH_DEFINES

#include <addition.h>
#include <yes_or_no.h>

using namespace Graph_lib;


const string quit_question = "Close program?";

//------------------------------------------------------------------------------

class empty_base_class {
protected:
	empty_base_class() {}

public:
	virtual double get() const {  return empty_element;  }
	virtual void set(double d) = 0;
	//void set(double d) {  empty_element = d;  }

private:
	double empty_element;
};

//------------------------------------------------------------------------------

int main()
{
	while (true) {
		try
		{
			Point tl{win_centering(500, 500)}; //Расположение ровно по середине экрана
			
			Simple_window win(tl, 500, 500, "Глава 14. Упражнение №2");
			// окно посередине экрана
			// размер окна (500*500)
			// заголовок окна: Глава 14. Упражнение №2
			
			Point cntr{win.x_max()/2, win.y_max()/2}; //Центральная точка окна
			
			Smiley s {cntr, 100};
			
			Smiley s0 {s};
			
			/*
			main.cpp(29): error C2280: "Graph_lib::Smiley::Smiley(const Graph_lib::Smiley &)": предпринята попытка ссылки на удаленную функцию
			note: в этом месте создано компилятором: "Graph_lib::Smiley::Smiley"
			note: "Graph_lib::Smiley::Smiley(const Graph_lib::Smiley &)": функция неявно удалена, так как базовый класс вызывает удаленную или недоступную 
					функцию "Graph_lib::Circle::Circle(const Graph_lib::Circle &)".
			note: "Graph_lib::Circle::Circle(const Graph_lib::Circle &)": функция неявно удалена, так как базовый класс вызывает удаленную или недоступную
					функцию "Graph_lib::Shape::Shape(const Graph_lib::Shape &)".
			note: "Graph_lib::Shape::Shape(const Graph_lib::Shape &)": функция явно удалена.
			*/
			
			
			
			Smiley s1;
			s1 = s;
			
			/*
			error C2280: "Graph_lib::Smiley &Graph_lib::Smiley::operator =(const Graph_lib::Smiley &)": предпринята попытка ссылки на удаленную функцию
			note: в этом месте создано компилятором: "Graph_lib::Smiley::operator ="
			note: "Graph_lib::Smiley &Graph_lib::Smiley::operator =(const Graph_lib::Smiley &)": функция неявно удалена, так как базовый класс вызывает 
					удаленную или недоступную функцию "Graph_lib::Circle &Graph_lib::Circle::operator =(const Graph_lib::Circle &)".
			note: "Graph_lib::Circle &Graph_lib::Circle::operator =(const Graph_lib::Circle &)": функция неявно удалена, так как базовый класс вызывает 
					удаленную или недоступную функцию "Graph_lib::Shape &Graph_lib::Shape::operator =(const Graph_lib::Shape &)".
			note: "Graph_lib::Shape &Graph_lib::Shape::operator =(const Graph_lib::Shape &)": функция явно удалена.
			*/
			
			//------------------------------------------------------------------------------
			
			//Если нет чисто виртуальной ф-ции set и виртуальной ф-ции get (хотя при наличии последней ошибка та же самая)
			//error C2248: empty_base_class::empty_base_class: невозможно обратиться к protected член, объявленному в классе "empty_base_class"
			
			//Если set - чисто виртуальная ф-ция
			//error C2259: "empty_base_class": невозможно создать экземпляр абстрактного класса
			// note:  см. объявление "empty_base_class"
			// note: из-за следующих членов:
			// note: double empty_base_class::set(double): абстрактный
			//note:  см. объявление "empty_base_class::set"
			//error C2248: empty_base_class::empty_base_class: невозможно обратиться к protected член, объявленному в классе "empty_base_class"
			
			//Без protected конструктора и set - не яв-ся виртуальной, но get - просто виртуальная:  всё работает
			
			empty_base_class ebc;
			cout << ebc.get() << '\n';
			ebc.set(1234.5678);
			cout << ebc.get() << '\n';
			
			
			win.set_label("Нажмите кнопку NEXT для завершения программы");
			win.wait_for_button();
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

//------------------------------------------------------------------------------