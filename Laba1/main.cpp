#include<iostream>
#include<string>
#include <conio.h> // посвящение в спартанца
#include <io.h> // красота
#include <fcntl.h> // красота
#include <stdexcept> // красота (испытательным путём было понято, что эта библиотека не нужна, но лучше оставим всё как есть)

class Menu // Красиво же
{
private:
	int getvariants(int count); // для считывания циферы (вспомогатльная, для менюшки)
	void menu(); // менюшка

public:
	void start(); // запуск программы и вообще весь существовавший int main :D

};


class Polynom
{
private:
	int m_index = 0;
	int* m_coeff = 0; // выделяем память, мы же не знаем какой там будет массивчик, я не ванга

	wchar_t index_converter(unsigned int index); // вызвал красоту заранее, тут её точно не украдут

public:
	//тактический отступ

	friend Polynom operator+(Polynom& poly1, Polynom& poly2);
	friend Polynom operator-(Polynom& poly1, Polynom& poly2);
	friend Polynom operator*(Polynom& poly1, Polynom& poly2);
	friend bool operator==(Polynom& poly1, Polynom& poly2); // Лучшие друзья полинома, на чай в гости друг к другу ходят
	friend Polynom operator~(Polynom& poly1);

	void inputindex();
	void inputcoeff();
	std::wstring outputPolynom(); // Функции тут всякие
	/*std::wstring optoutput(int i);*/ // можно сделать некрасиво

	Polynom()
	{
		m_coeff = new int[m_index + 1]; // тоже полезные ребята
	}

	Polynom(int index)
	{
		m_index = index; // сохраняем степень     
		m_coeff = new int[m_index + 1];
	}

	Polynom(const Polynom& other) //конструктор копирования, теперь у каждого свой домик, жилищный вопрос решён
	{
		m_index = other.m_index;
		m_coeff = new int[other.m_index + 1];
		for (int i = 0; i < other.m_index + 1; i++)
		{
			m_coeff[i] = other.m_coeff[i];
		}
	}

	~Polynom()
	{
		delete[] m_coeff;
	}

};


int main()
{
	setlocale(LC_ALL, "rus"); // Для русича

	_setmode(_fileno(stdout), _O_U16TEXT); // Для красоты
	_setmode(_fileno(stdin), _O_U16TEXT);  // Всё ещё для красоты
	_setmode(_fileno(stderr), _O_U16TEXT);  // И это... не поверите, для красоты

	Menu menu;
	menu.start();

	system("pause");
	return 0;
}

void Polynom::inputindex()
{
	std::wcout << L"Введите старшую степень многочлена: ";
	std::wcin >> m_index;
	m_coeff = new int[m_index + 1];
}

void Polynom::inputcoeff()
{
	for (int i = 0; i < m_index + 1; i++)
	{
		if (i == 0)
		{
			std::wcout << L"Введите коэффициенты от самой старшей степени многочлена к самой младшей: ";
			std::wcin >> m_coeff[i];
		}
		else if (i == m_index)
		{
			std::wcout << L"Введите свободный член: ";
			std::wcin >> m_coeff[i];
		}
		else
		{
			std::wcin >> m_coeff[i];
		}
	}

}

std::wstring Polynom::outputPolynom()
{
	std::wstring res;

	for (int i = 0; i < m_index + 1; i++) // Коалиция "Анти-if" :D 
	{
		if (m_coeff[i] != 0)
		{
			if (abs(m_coeff[i]) != 1 || m_index - i == 0)
				res += std::to_wstring(m_coeff[i]);
			else if (m_coeff[i] == -1)
				res += L"-";
			if ((m_index - i != 0))
			{
				res += L"x";
				res += index_converter(m_index - i);
			}
		}

		if (i != m_index && m_coeff[i + 1] > 0) // Проверка на свободный член, чтобы после него не ставился +
		{
			res += L"+";
		}
	}

	return res;
}

void Menu::menu()
{
	system("cls");
	std::wcout << L"\nВыберите операцию которую хотите просмотреть:\n";
	std::wcout << L"1. Сумма многочленов.\n";
	std::wcout << L"2. Разность многочленов.\n";
	std::wcout << L"3. Произведение многочленов. \n";
	std::wcout << L"4. Сравнение многочленов. \n";
	std::wcout << L"5. Дифференцирование многочлена. \n";
	std::wcout << L"6. Переписать многочлены\n";
	std::wcout << L"7. Выход.\n";
}

int Menu::getvariants(int count) // "геттер", нужно взять циферу, которую пишет пользователь 
{
	int variants;
	std::wstring s;
	std::wcin >> s;

	variants = std::stoi(s); // stoi - для перевода из string в int

	while (variants < 1 || variants > count) {
		std::wcout << L"Что-то ты напутал, давай ещё раз, у тебя точно получится!\n";
		std::wcin >> s;
		variants = std::stoi(s);
	}

	return variants;
}

void Menu::start()
{
	std::wcout << L"Первый многочлен:\n";
	Polynom* poly1 = new Polynom;
	poly1->inputindex();
	poly1->inputcoeff();
	std::wcout << L"Получился многочлен вида: ";
	std::wcout << poly1->outputPolynom() << "\n"; // ну тут всё ясненько

	std::wcout << L"Второй многочлен:\n";
	Polynom* poly2 = new Polynom;
	poly2->inputindex();
	poly2->inputcoeff();
	std::wcout << L"Получился многочлен вида: ";
	std::wcout << poly2->outputPolynom() << "\n";

	int variants;

	do
	{
		_getch();  // чтобы экран держался, как спартанец!
		menu();
		variants = getvariants(7);
		switch (variants)
		{
		case 1:
		{
			std::wcout << L"Сумма многочленов равна:\n";
			Polynom poly3 = *poly1 + *poly2;
			std::wcout << poly3.outputPolynom();
			std::wcout << "\n\n\n\n";
			break;
		}
		case 2:
		{
			std::wcout << L"Разность многочленов равна:\n";
			Polynom poly3 = *poly1 - *poly2;
			std::wcout << poly3.outputPolynom();
			std::wcout << "\n\n\n\n";
			break;
		}
		case 3:
		{
			std::wcout << L"Произведение многочленов равно:\n";
			Polynom poly3 = *poly1 * *poly2;
			std::wcout << poly3.outputPolynom();
			std::wcout << "\n\n\n\n";
			break;
		}
		case 4:
		{
			if (poly1 == poly2)
			{
				std::wcout << L"Сравнение многочленов:";
				std::wcout << poly1->outputPolynom() << " " << "=" << " " << poly2->outputPolynom(); // Красотища!
			}
			else
			{
				std::wcout << L"Сравнение многочленов:\n";
				std::wcout << poly1->outputPolynom() << " " << (wchar_t)(0x2260) << " " << poly2->outputPolynom(); // Ой, а это то какая!!!
			}
			break;
		}
		case 5:
		{
			std::wcout << L"Дифференцирование многочлена:\n";
			std::wcout << (~(*poly1)).outputPolynom();  // Слишком умная вещь, опасна для здоровья!
			break;
		}
		case 6:
		{
			std::wcout << L"Первый многочлен:\n";
			poly1->inputindex();
			poly1->inputcoeff();
			std::wcout << L"Получился многочлен вида: ";
			std::wcout << poly1->outputPolynom() << "\n"; // ну тут всё ясненько

			std::wcout << L"Второй многочлен:\n";
			poly2->inputindex();
			poly2->inputcoeff();
			std::wcout << L"Получился многочлен вида: ";
			std::wcout << poly2->outputPolynom() << "\n";
		}
		}
	} while (variants != 7);

	std::wcout << "\n\n\n\n";
}

Polynom operator+(Polynom& poly1, Polynom& poly2)
{
	const int n = std::max(poly1.m_index, poly2.m_index);
	Polynom poly3(n);
	for (int i = 0; i <= n; i++)
	{
		poly3.m_coeff[i] = 0; // Скажем if-ам нет!
	}
	for (int i = 0; i <= poly1.m_index; i++)
	{
		const int m = poly1.m_index;
		poly3.m_coeff[n - m + i] += poly1.m_coeff[i];
	}
	for (int i = 0; i <= poly2.m_index; i++)
	{
		const int m = poly2.m_index;
		poly3.m_coeff[n - m + i] += poly2.m_coeff[i];
	}

	return poly3;
}

Polynom operator-(Polynom& poly1, Polynom& poly2)
{
	const int n = std::max(poly1.m_index, poly2.m_index);
	Polynom poly3(n);
	for (int i = 0; i <= n; i++)
	{
		poly3.m_coeff[i] = 0; // Аналогично
	}
	for (int i = 0; i <= poly1.m_index; i++)
	{
		const int m = poly1.m_index;
		poly3.m_coeff[n - m + i] += poly1.m_coeff[i];
	}
	for (int i = 0; i <= poly2.m_index; i++)
	{
		const int m = poly2.m_index;
		poly3.m_coeff[n - m + i] -= poly2.m_coeff[i];
	}

	return poly3;
}

Polynom operator*(Polynom& poly1, Polynom& poly2)
{
	const int p = poly1.m_index + poly2.m_index;
	Polynom poly3(p);
	for (int i = 0; i <= p; i++)
	{
		poly3.m_coeff[i] = 0;
	}
	for (int i = 0; i <= poly1.m_index; i++)
	{
		for (int j = 0; j <= poly2.m_index; j++)
		{
			poly3.m_coeff[i + j] += poly1.m_coeff[i] * poly2.m_coeff[j];
		}
	}

	return poly3; // Повазюкался с ним знатно
}

bool operator==(Polynom& poly1, Polynom& poly2)
{
	return poly1.outputPolynom() == poly2.outputPolynom(); // Самая полезная функция берём и сравниваем две строчки
}

Polynom operator~(Polynom& poly1)
{
	const int d = poly1.m_index - 1; // Бабушкин сервиз (очень хрупкая штука)
	Polynom diff(d);
	for (int i = 0; i <= d; i++) // зачем создавать массивчик, с лишним членом (он обращается в ноль)
	{
		diff.m_coeff[i] = 0;
	}
	for (int i = 0; i <= d; i++)
	{
		diff.m_coeff[i] = (poly1.m_index - i) * poly1.m_coeff[i];
	}

	return diff;
}



// Всё так же не красиво, кому это вообще нужно?
//std::wstring Polynom::optoutput(int i)
//{
//	std::wstring a;
//	if (i == 1)
//	{
//		a = L"x";
//	}
//	else if (i == 0)
//	{
//		a = L"";
//	}
//	else if (i >= 2)
//	{
//		a = L"x^" + std::to_wstring(i);
//	}
//	return a;
//}

wchar_t Polynom::index_converter(unsigned int index) // Пытался исправить, но у самурая нет цели, есть только путь...
{
	char s = '\0';
	switch (index)
	{
	case 0:
		return s;
	case 1:
		return s;
	case 2:
		return 0x00B2;
	case 3:
		return 0x00B3;
	default:
		return 0x2070 + index;
	}
}