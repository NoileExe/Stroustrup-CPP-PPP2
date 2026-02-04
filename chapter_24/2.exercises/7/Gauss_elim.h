

//Включение доступа к функциям keep_window_open() И error() из <yes_or_no.h>
#define WITHOUT_STD_LIB_FACILITIES_H

#include <yes_or_no.h>		//Включает <string>, <iostream>
#include <iomanip>	//Для возможности форматирования потока вывода
#include <random>	//Для рандомизации
#include <typeinfo>

//------------------------------------------------------------------------------

using namespace std;

typedef long Index;

//------------------------------------------------------------------------------

template<class T>
class my_Vector {
public:
	//Инициализация пуcтого вектора
	my_Vector() : sz{0}		{ }
	
	//Инициализация вектора с нулевыми элементами в количестве s
	//Только в круглых скобках
	explicit my_Vector(int s) : sz{s}
	{
		if(sz < 0)		error("bad size [my_Vector(size) INIT]");
		if( sz )		//Больше нуля
		{
			arr = new T[sz];
			for(Index i = 0; i < sz; ++i)		arr[i] = 0;
		}
	}
	
	//Инициализация путём копирования элементов переданного встроенного массива
	//Имя встроенного массива уже является указателем на первый элемент (поэтому при инициализации не нужно указывать что-то вроде &Arr)
	my_Vector(T* a, int s) : sz{s}
	{
		if(sz < 0)			error("bad size [my_Vector(array ptr, size) INIT]");
		if(sz > 0  &&  !a)	error("bad pointer [my_Vector(array ptr, size) INIT]");
		if( sz )		//Больше нуля
		{
			arr = new T[sz];
			for(Index i = 0; i < sz; ++i)		arr[i] = a[i];
		}
	}
	
	//Инициализация в виде привычном для одномерного встроенного массива
	my_Vector(initializer_list<T> lst) : sz{Index(lst.size())}
	{
		if(sz < 0)		error("bad size [my_Vector(init_list) INIT]"); //Скорее всего в данном конструкторе лишняя строчка
		if( sz )		//Больше нуля
		{
			arr = new T[sz];
			for(Index i = 0; i < lst.size(); ++i)		arr[i] = lst.begin()[i];
		}
	}
	
	//Копирующие конструктор и присваивание
	my_Vector(const my_Vector& v) : sz{v.size()}
	{
		arr = new T[v.size()];
		for(Index i = 0; i < sz; ++i)		arr[i] = v.arr[i];
	}
	my_Vector& operator=(const my_Vector & v);	// Копирующее присваивание
	
	//Перемещающие конструктор и присваивание
	my_Vector(my_Vector&& v) : sz{v.sz}
	{
		arr = v.arr; //Копируем
		v.sz = 0;		v.arr = nullptr;
	}
	my_Vector& operator=(my_Vector&& v);	// Перемещающее присваивание
	
	//Доступ к элементам с проверкой выхода за диапазон
	T& operator[](Index n) {
		if (n<0 || n>=sz)		throw out_of_range("my_Vector range error with index [" + to_string(n) + "]");
		return arr[n];
	}
	
	const T& operator[](Index n) const {
		if (n<0 || n>=sz)		throw out_of_range("const my_Vector range error with index [" + to_string(n) + "]");
		return arr[n];
	}
	
	//Первый и последний элемент
	T* begin() { return arr; }
	T*  end()  { return arr+sz; }
	
	//~my_Vector()	{ if(arr)		delete[] arr; }
	
	
	
	T* data()		{ return arr; }
	T* data() const { return arr; }
	Index size() const { return sz; }
	
	//Срезка вектора (элементы от n-ого до последнего)
	//Если n < 0 или n >= sz - возвращается пустой вектор, иначе срезка из элементов размером (sz - n)
	my_Vector<T> slice(Index n);
	const my_Vector<T> slice(Index n) const;
	
	//Срезка вектора (элементы от элемента с индексом first до элемента с индексом last)
	//Может возвращать пустой вектор, либо срезку из элементов размером от first до last
	my_Vector<T> slice(Index first, Index last);
	const my_Vector<T> slice(Index first, Index last) const;
	
	//Совершение одной и той же операции над каждым элементом вектора
	//f модифицирует каждый элемент вектора
	template<class F> void apply(F f) { for(Index i = 0; i < sz; ++i)	f(arr[i]); }
	template<class F> void apply(F f, const T& c) { for(Index i = 0; i < sz; ++i)	f(arr[i],c); }
	
protected:
	T* arr {nullptr};	//Указатель на классический массив в динамической памяти
	Index sz;			//Размер
};

//Копирующее присваивание
template<typename T>
my_Vector<T>& my_Vector<T>::operator=(const my_Vector<T>& v)
{
	if (this == &v)		return *this;	//Проверка на самоприсваивание
	
	if( sz < v.sz  &&  arr )		delete[] arr;
	if( !arr )		arr = new T[v.size()];
	
	sz = v.sz;
	for (Index i = 0; i < sz; ++i)		{ arr[i] = v.arr[i]; }
	
	return *this;
}

//Перемещающее присваивание
template<typename T>
my_Vector<T>& my_Vector<T>::operator=(my_Vector<T>&& v)
{
	if(arr)		delete[] arr;
	arr = v.arr;		sz = v.sz;
	v.arr = nullptr;	v.sz = 0;
	return *this;
}

//Срезка вектора (элементы от n-ого до последнего)
//Если n < 0 или n >= sz - возвращается пустой вектор, иначе срезка из элементов размером (sz - n)
template<typename T>
my_Vector<T> my_Vector<T>::slice(Index n)
{
	my_Vector<T> sl;
	
	if( sz >= 0  &&  n < sz )
	{
		my_Vector<T> tmp (sz - n);
		for(Index i = 0; i < tmp.sz; ++i)		tmp[i] = arr[n+i];
		sl = tmp;
	}
	
	return sl;
}

template<typename T>
const my_Vector<T> my_Vector<T>::slice(Index n) const
{
	my_Vector<T> sl;
	
	if( sz >= 0  &&  n < sz )
	{
		my_Vector<T> tmp (sz - n);
		for(Index i = 0; i < tmp.sz; ++i)		tmp[i] = arr[n+i];
		sl = tmp;
	}
	
	return sl;
}

//Срезка вектора (элементы от элемента с индексом first до элемента с индексом last)
//Может возвращать пустой вектор, либо срезку из элементов размером от first до last
template<typename T>
my_Vector<T> my_Vector<T>::slice(Index first, Index last)
{
	my_Vector<T> sl;
	
	if( first >= 0  &&  last >= 0  &&  first < sz  &&  first <= last )
	{
		Index new_sz {sz - first}; //Если last >= sz
		if(last < sz)		new_sz = last - first + 1;
		
		my_Vector<T> tmp (new_sz);
		for(Index i = 0; i < tmp.sz; ++i)		tmp[i] = arr[first+i];
		sl = tmp;
	}
	
	return sl;
}

template<typename T>
const my_Vector<T> my_Vector<T>::slice(Index first, Index last) const
{
	my_Vector<T> sl;
	
	if( first >= 0  &&  last >= 0  &&  first < sz  &&  first <= last )
	{
		Index new_sz {sz - first}; //Если last >= sz
		if(last < sz)		new_sz = last - first + 1;
		
		my_Vector<T> tmp (new_sz);
		for(Index i = 0; i < tmp.sz; ++i)		tmp[i] = arr[first+i];
		sl = tmp;
	}
	
	return sl;
}

//------------------------------------------------------------------------------

/*template<class T> class Row : public my_Vector<T> {
public:
	Row(my_Vector<T>& vsrc) : my_Vector<T>{}
	{
		this->sz = vsrc.size();
		this->arr = vsrc.data();
	}

	~Row() {  }

	my_Vector<T>& operator=(const T& n)
	{
		for(Index i=0; i < this->sz; ++i)		this->arr[i] = n;
		return *this;
	}

	my_Vector<T>& operator=(const my_Vector<T>& v)
	{
		if(v.size() != this->sz)
		{
			string str {"it is impossible to equate a one-dimensional matrix to a row if their sizes differ"};
			str += " Matrix row size = " + to_string(this->sz) + " Vector elements count = " + to_string(v.size());
			str += "   [ Row::operator=(const my_Vector<T>&) ]";
			cout << *this << endl;
			error(str);
		}
		for(Index i=0; i < this->sz; ++i)		this->arr[i] = v[i];
		return *this;
	}
};*/

//------------------------------------------------------------------------------

template<class T>
class my_Matrix {
public:
	//Инициализация пуcтого вектора
	my_Matrix() : rows{0}, cols{0}		{ }
	
	//Инициализация вектора с нулевыми элементами в количестве d1*d2 (d2 - кол-во строк, d1 - кол-во элементов в строке (столбцов))
	//Только в круглых скобках
	explicit my_Matrix(int d1, int d2) : cols{d1}, rows{d2}
	{
		if(cols <= 0)		error("bad count of columns [my_Matrix(rows_num, columns_num) INIT]");
		if(rows <= 0)		error("bad count of rows [my_Matrix(rows_num, columns_num) INIT]");
		
		mtrx = new my_Vector<T>[rows];
		
		my_Vector<T> tmp (cols);
		for(int i = 0; i < rows; ++i)		mtrx[i] = tmp;
	}
	
	//Для передачи двумерного массива по указателю.
	//Например, Arr - двумерный массив 3*3 чисел int, тогда инициализация принимает вид:
	// my_Matrix<int> m {&Arr[0][0],3,3};
	my_Matrix(T* a, int d1, int d2) : cols{d1}, rows{d2}
	{
		if(cols <= 0)			error("bad count of columns [my_Matrix(array, rows_num, columns_num) INIT]");
		if(rows <= 0)			error("bad count of rows [my_Matrix(array, rows_num, columns_num) INIT]");
		
		mtrx = new my_Vector<T>[rows];
		
		my_Vector<T> tmp (cols);
		for(int i = 0; i < rows; ++i)
		{
			mtrx[i] = tmp;
			for(int j = 0; j < cols; ++j)		mtrx[i][j] = *(a + i*rows + j);
		}
	}
	
	//Инициализация в виде привычном для одномерного встроенного массива
	my_Matrix(initializer_list< my_Vector<T> > lst) : cols{ (lst.begin()[0]).size() }, rows{ Index(lst.size()) }
	{
		if(cols <= 0)			error("bad count of columns [my_Matrix(init_list) INIT]");
		if(rows <= 0)			error("bad count of rows [my_Matrix(init_list) INIT]");
		if(rows != lst.size())	error("bad initializer list size (not equ for count of rows) [my_Matrix(init_list) INIT]");
		
		mtrx = new my_Vector<T>[rows];
		
		my_Vector<T> tmp (cols);
		for(int i = 0; i < rows; ++i)
		{
			if( (lst.begin()[i]).size() != cols )		error("bad initializer list size (not equ for count of columns) [my_Matrix(init_list) INIT]");
			mtrx[i] = tmp;
			for(int j = 0; j < cols; ++j)		mtrx[i][j] = lst.begin()[i][j];
		}
	}
	
	//Копирующие конструктор и присваивание
	my_Matrix(const my_Matrix& mt) : cols{mt.cols}, rows{mt.rows}
	{
		mtrx = new my_Vector<T>[rows];
		for(int i = 0; i < rows; ++i)		this->mtrx[i] = mt.mtrx[i];	//Вызывается копирующее присваивание для каждой строки (вектора)
	}
	my_Matrix& operator=(const my_Matrix & mt);	// Копирующее присваивание
	
	
	//Перемещающие конструктор и присваивание
	my_Matrix(my_Matrix&& mt) : cols{mt.cols}, rows{mt.rows}
	{
		mtrx = mt.mtrx; //Копируем
		mt.cols = 0;	mt.rows = 0;		mt.mtrx = nullptr;
	}
	my_Matrix& operator=(my_Matrix&& mt);	// Перемещающее присваивание
	
	
	
	//Срезка матрицы (строки от n-ой до последней)
	//Если n < 0 или n >= rows - возвращается пустая матрица
	my_Matrix<T> slice(Index n);
	const my_Matrix<T> slice(Index n) const;
	
	//Срезка матрицы (строки от строки с индексом first до строки с индексом last)
	//Может возвращать пустую матрицу, либо срезку из строк от first до last
	my_Matrix<T> slice(Index first, Index last);
	const my_Matrix<T> slice(Index first, Index last) const;
	
	//Совершение одной и той же операции над каждым элементом матрицы (просто вызывает ту же самую функцию но для каждого вектора (строки))
	//f модифицирует каждый элемент матрицы
	template<class F> void apply(F f) { for(Index i = 0; i < rows; ++i)		mtrx[i].apply(f); }
	template<class F> void apply(F f, const T& c) { for(Index i = 0; i < rows; ++i)		mtrx[i].apply(f,c); }


	my_Matrix<T>& swap_rows(Index a, Index b)
	{
		my_Vector<T> tmp = operator[](a);		//С проверкой индекса на выход из диапазона
		operator[](a) = operator[](b);
		operator[](b) = tmp;
		return *this;
	}


	
	//Срезка по строкам матрицы с проверкой выхода за диапазон
	//Возвращает отдельный вектор, но не ссылку на строку матрицы
	my_Vector<T>& operator[](Index n) {
		if(n<0 || n>=rows)		throw out_of_range("my_Matrix rows range error with index [" + to_string(n) + "]");
		return mtrx[n];
	}
	
	const my_Vector<T>& operator[](Index n) const {
		if(n<0 || n>=rows)		throw out_of_range("const my_Matrix rows range error with index [" + to_string(n) + "]");
		return mtrx[n];
	}


	~my_Matrix()	{ delete[] mtrx; }
	
	Index size() const { return rows*cols; }
	Index dim1() const { return cols; }
	Index dim2() const { return rows; }
	
private:
	my_Vector<T>* mtrx{nullptr};
	
	Index cols;		//Кол-во столбцов (ячеек в строке)
	Index rows;		//Кол-во строк
};


//Копирующее присваивание
template<typename T>
my_Matrix<T>& my_Matrix<T>::operator=(const my_Matrix<T>& mt)
{
	if (this == &mt)		return *this;	//Проверка на самоприсваивание
	
	if( this->rows < mt.rows  &&  mtrx )		delete[] mtrx;
	if( !mtrx )		mtrx = new my_Vector<T>[mt.rows];
	
	cols = mt.cols;
	rows = mt.rows;
	for (Index i = 0; i < rows; ++i)		{ mtrx[i] = mt.mtrx[i]; }
	
	return *this;
}

//Перемещающее присваивание
template<typename T>
my_Matrix<T>& my_Matrix<T>::operator=(my_Matrix<T>&& mt)
{
	if(mtrx)		delete[] mtrx;
	mtrx = mt.mtrx;		cols = mt.cols;		rows = mt.rows;
	mt.mtrx = nullptr;	mt.cols = 0;		mt.rows = 0;
	return *this;
}


//Срезка матрицы (строки от n-ой до последней)
//Если n < 0 или n >= rows - возвращается пустая матрица
template<typename T>
my_Matrix<T> my_Matrix<T>::slice(Index n)
{
	my_Matrix<T> sl;
	
	if( n < rows )
	{
		my_Matrix<T> tmp (cols, rows - n);
		for(Index i = 0; i < tmp.rows; ++i)		tmp[i] = this->mtrx[n+i];
		sl = tmp;
	}
	
	return sl;
}

//Срезка матрицы (строки от n-ой до последней)
//Если n < 0 или n >= rows - возвращается пустая матрица
template<typename T>
const my_Matrix<T> my_Matrix<T>::slice(Index n) const
{
	my_Matrix<T> sl;
	
	if( n < rows )
	{
		my_Matrix<T> tmp (cols, rows - n);
		for(Index i = 0; i < tmp.rows; ++i)		tmp[i] = this->mtrx[n+i];
		sl = tmp;
	}
	
	return sl;
}

//Срезка матрицы (строки от строки с индексом first до строки с индексом last)
//Может возвращать пустую матрицу, либо срезку из строк от first до last
template<typename T>
my_Matrix<T> my_Matrix<T>::slice(Index first, Index last)
{
	my_Matrix<T> sl;
	
	if( first >= 0  &&  last >= 0  &&  first < rows  &&  first <= last )
	{
		Index new_sz {rows - first}; //Если last >= rows
		if(last < rows)		new_sz = last - first + 1;
		
		my_Matrix<T> tmp (cols, new_sz);
		for(Index i = 0; i < tmp.rows; ++i)		tmp[i] = this->mtrx[first+i];
		sl = tmp;
	}
	
	return sl;
}

//Срезка матрицы (строки от строки с индексом first до строки с индексом last)
//Может возвращать пустую матрицу, либо срезку из строк от first до last
template<typename T>
const my_Matrix<T> my_Matrix<T>::slice(Index first, Index last) const
{
	my_Matrix<T> sl;
	
	if( first >= 0  &&  last >= 0  &&  first < rows  &&  first <= last )
	{
		Index new_sz {rows - first}; //Если last >= rows
		if(last < rows)		new_sz = last - first + 1;
		
		my_Matrix<T> tmp (cols, new_sz);
		for(Index i = 0; i < tmp.rows; ++i)		tmp[i] = this->mtrx[first+i];
		sl = tmp;
	}
	
	return sl;
}


//------------------------------------------------------------------------------

//Функции для операторов вывода для классов my_Vector и my_Matrix

template<class T>
ostream& operator<<(ostream& os, const my_Vector<T>& v)
{
	os << " { ";
	for(int i = 0; i < v.size(); ++i)		os << v[i] << " ";
	return os << "}";
}

template<class T>
ostream& operator<<(ostream& os, const my_Matrix<T>& mt)
{
	os << " {\n";
	for(int i = 0; i < mt.dim2(); ++i)
	{
		os << "\t{ ";
		for(int j = 0; j < mt.dim1(); ++j)		os << mt[i][j] << " ";
		os << "}\n";
	}
			
	return os << "}";
}

//------------------------------------------------------------------------------

//Исключение данного типа вызывается при ошибке в работе алгоритма классического исключения Гаусса.
struct Elim_failure : std::domain_error {
	Elim_failure(string s) : std::domain_error(s) { }
};

//Исключение данного типа вызывается при ошибке в работе алгоритма обратной подстановки
struct Back_subst_failure : std::domain_error {
	Back_subst_failure(string s) : std::domain_error(s) { }
};

//------------------------------------------------------------------------------

//Сумма произведений элементов с одинаковыми индексами
template<class T>
T my_dot_product(const my_Vector<T>& a, const my_Vector<T>& b)
{
	if(a.size() != b.size())		error("different sizes of vectors [ my_dot_product(my_Vector a, my_Vector b) ]");
	
	T res = 0;
	errno = 0;
	for(Index i = 0; i < a.size(); ++i)		res += a[i] * b[i];
	if(errno==ERANGE)		error("when calculating, the number is out of range for the vector element type [ my_dot_product(my_Vector a, my_Vector b) ]");
	
	return res;
}


//Скалярное произведение
template<class T>
my_Vector<T> my_scale_and_add(const my_Vector<T>& arg1, T arg2, const my_Vector<T>& arg3)
{
	if(arg1.size() != arg3.size())		error("different sizes of matrices [ my_scale_and_add(my_Vector arg1, arg2, my_Vector arg3) ]");
	
	my_Vector<T> res(arg1.size());
	for(Index i = 0; i < arg1.size(); ++i) {
		errno = 0;
		res[i] = arg1[i] * arg2 + arg3[i];
		if(errno==ERANGE)		error("when calculating, the number is out of range for the vector element type [ my_scale_and_add(my_Vector arg1, arg2, my_Vector arg3) ]");
	}
	
	return res;
}

//------------------------------------------------------------------------------

//Классическое исключение Гаусса без перестановки строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
template<class T> void classical_elimination(my_Matrix<T>& A, my_Vector<T>& b);

//Классическое исключение Гаусса  с перестановкой строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
template<class T> void elim_with_partial_pivot(my_Matrix<T>& A, my_Vector<T>& b);

//Обратная подстановка для вычисления неизвестных
template<class T> my_Vector<T> back_substitution(const my_Matrix<T>& A, const my_Vector<T>& b);

//Классическое исключение Гаусса без перестановки строк
//Возвращает вектор (одномерную матрицу) значений переменных
template<class T>
my_Vector<T> classical_gaussian_elimination(my_Matrix<T> A, my_Vector<T> b)
{
	classical_elimination(A, b);
	cout << " A matrix after elimination = " << A << endl;
	return back_substitution(A, b);
}

//Классическое исключение Гаусса с перестановкой строк
//Возвращает вектор (одномерную матрицу) значений переменных
template<class T>
my_Vector<T> pivotal_elimination(my_Matrix<T> A, my_Vector<T> b)
{
	elim_with_partial_pivot(A, b);
	cout << " A matrix after elimination = " << A << endl;
	return back_substitution(A, b);
}

//------------------------------------------------------------------------------

//Классическое исключение Гаусса без перестановки строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
template<class T>
void classical_elimination(my_Matrix<T>& A, my_Vector<T>& b)
{
	const Index n = A.dim1();

	//Проходим от первого столбца до предпоследнего,
	// обнуляя элементы, стоящие ниже диагонали
	for (Index j = 0; j < n-1; ++j)
	{
		const double pivot = A[j][j];	//Опорный элемент
		if (pivot == 0) {
			cout << "\n A matrix after elimination = " << A << endl;
			throw Elim_failure("\tELIMINATION FAILURE IN ROW " + to_string(j));
		}

		//Обнуляем каждый элемент, стощий ниже в строке i
		for (Index i = j+1; i < n; ++i)
		{
			const double mult = A[i][j] / pivot;
			my_Vector<T> tmp { my_scale_and_add(A[j].slice(j), -mult, A[i].slice(j)) };
			for(Index k = 0; k < tmp.size(); ++k)		A[i][j+k] = tmp[k];
			//A[i].slice(j) = my_scale_and_add(A[j].slice(j), -mult, A[i].slice(j)); // - A[i].slice(j) ссылается уже на новый объект и не внесёт изменения в существующую матрицу или вектор
			b[i] -= mult * b[j];	//Изменяем вектор 'b' (расширенная часть матрицы - свободные числа)
		}
	}
}

//Классическое исключение Гаусса с перестановкой строк (приведение матрицы к треугольному виду, где ниже главной диагонали нули)
template<class T>
void elim_with_partial_pivot(my_Matrix<T>& A, my_Vector<T>& b)
{
	const Index n = A.dim1();

	for (Index j = 0; j < n; ++j) {
		Index pivot_row = j;

		//Поиск подходящего опорного элемента
		for (Index k = j + 1; k < n; ++k)
			if( abs(A[k][j]) > abs(A[pivot_row][j]) )		pivot_row = k;

		//Обмен строк для лучего опорного элемента
		if(pivot_row != j) {
			A.swap_rows(j, pivot_row);
			std::swap(b[j], b[pivot_row]);
		}
		
		const double pivot = A[j][j];
		if(pivot==0)
		{
			cout << "\n A matrix after elimination = " << A << endl;
			error("\tCAN'T SOLVE: pivot==0");
		}
		
		//Исключение Гаусса
		for (Index i = j + 1; i < n; ++i)
		{
			const double mult = A[i][j] / pivot;
			my_Vector<T> tmp { my_scale_and_add(A[j].slice(j), -mult, A[i].slice(j)) };
			for(Index k = 0; k < tmp.size(); ++k)		A[i][j+k] = tmp[k];
			//A[i].slice(j) = my_scale_and_add<T>(A[j].slice(j), -mult, A[i].slice(j)); // - A[i].slice(j) ссылается уже на новый объект и не внесёт изменения в существующую матрицу или вектор
			b[i] -= mult * b[j];
		}
	}
}

//------------------------------------------------------------------------------

//Обратная подстановка для вычисления неизвестных
template<class T>
my_Vector<T> back_substitution(const my_Matrix<T>& A, const my_Vector<T>& b)
{
	const Index n = A.dim1();	//Количество элементов в строке (столбцов)
	my_Vector<T> x(n);

	for (Index i = n - 1; i >= 0; --i)
	{
		double s = b[i] - my_dot_product<T>(A[i].slice(i+1), x.slice(i+1));

		if (double m = A[i][i])		x[i] = s / m;
		else						throw Back_subst_failure("Back substitution failure in row " + to_string(i));
		//else						error("can't solve: diagonal element is zero during back substitution");
	}

	return x;
}

//------------------------------------------------------------------------------

//Генерация одномерной матрицы размерностью n (кол-во элементов / столбцов)
template<class T>
my_Vector<T> random_vector(Index n)
{
	my_Vector<T> v(n);

	random_device rd;
	mt19937 mersenne( rd() );		// инициализируем Вихрь Мерсенна случайным стартовым числом
	//mt19937 mersenne(static_cast<unsigned int>(time(0)));	// инициализируем Вихрь Мерсенна случайным стартовым числом
	
	for(Index i = 0; i < n; ++i)
		v[i] = mersenne() % 10;
	
	return v;
}


//Генерация двумерной матрицы размерностью n*n
template<class T>
my_Matrix<T> random_matrix(Index n)
{
	my_Matrix<T> m(n,n);

	for (Index i = 0; i < n; ++i)
		m[i] = random_vector<T>(n);

	return m;
}


//Генерация двумерной матрицы размерностью n1*n2
// (n1 - количество столбцов (элементов в строке), n2 - количество строк)
template<class T>
my_Matrix<T> random_matrix(Index n1, Index n2)
{
	my_Matrix<T> m(n1,n2);

	for (Index i = 0; i < n2; ++i)
		m[i] = random_vector<T>(n1);

	return m;
}


template<class T>
my_Vector<T> operator*(const my_Matrix<T>& m, const my_Vector<T>& u)
{
	const Index n = m.dim1();
	my_Vector<T> v(n);	//Каждый эллемент вектора 'v' равен сумме произведений соответствующей строки матрицы 'm' на вектор 'u'
	for (Index i = 0; i < n; ++i)		v[i] = my_dot_product(m[i], u);
	return v;
}

//------------------------------------------------------------------------------

template<class T>
void solve_random_system(Index n)
{
	my_Matrix<T> A = random_matrix<T>(n);
	my_Vector<T> b = random_vector<T>(n);
	
	cout << "\n\nSolving A*x=B" << endl;
	cout << "A = " << A << endl;
	cout << "b = " << b << endl;

	try {
		my_Vector<T> x = classical_gaussian_elimination(A, b);
		cout << "classical elim solution is x = " << x << endl;
		my_Vector<T> v = A * x;
		cout << " A * x = " << v << endl;
	}
	catch(const exception& e) {
		cerr << e.what() << "\n\n";
		
		try {
			my_Vector<T> x = pivotal_elimination(A, b);
			cout << "elim with partial pivot is x = " << x << endl;
			my_Vector<T> v = A * x;
			cout << " A * x = " << v << endl;
		}
		catch(const exception& e) {
			cerr << e.what() << std::endl;
		}
	}
}