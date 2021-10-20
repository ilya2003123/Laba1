#include<iostream>
#include<string>
#include <conio.h> // ���������� � ���������
#include <io.h> // �������
#include <fcntl.h> // �������
#include <stdexcept> // ������� (������������� ���� ���� ������, ��� ��� ���������� �� �����, �� ����� ������� �� ��� ����)

class Menu // ������� ��
{
private:
	int getvariants(int count); // ��� ���������� ������ (��������������, ��� �������)
	void menu(); // �������

public:
	void start(); // ������ ��������� � ������ ���� �������������� int main :D

};


class Polynom
{
private:
	int m_index = 0;
	int* m_coeff = 0; // �������� ������, �� �� �� ����� ����� ��� ����� ���������, � �� �����

	wchar_t index_converter(unsigned int index); // ������ ������� �������, ��� � ����� �� �������

public:
	//����������� ������

	friend Polynom operator+(Polynom& poly1, Polynom& poly2);
	friend Polynom operator-(Polynom& poly1, Polynom& poly2);
	friend Polynom operator*(Polynom& poly1, Polynom& poly2);
	friend bool operator==(Polynom& poly1, Polynom& poly2); // ������ ������ ��������, �� ��� � ����� ���� � ����� �����
	friend Polynom operator~(Polynom& poly1);

	void inputindex();
	void inputcoeff();
	std::wstring outputPolynom(); // ������� ��� ������
	/*std::wstring optoutput(int i);*/ // ����� ������� ���������

	Polynom()
	{
		m_coeff = new int[m_index + 1]; // ���� �������� ������
	}

	Polynom(int index)
	{
		m_index = index; // ��������� �������     
		m_coeff = new int[m_index + 1];
	}

	Polynom(const Polynom& other) //����������� �����������, ������ � ������� ���� �����, �������� ������ �����
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
	setlocale(LC_ALL, "rus"); // ��� ������

	_setmode(_fileno(stdout), _O_U16TEXT); // ��� �������
	_setmode(_fileno(stdin), _O_U16TEXT);  // �� ��� ��� �������
	_setmode(_fileno(stderr), _O_U16TEXT);  // � ���... �� ��������, ��� �������

	Menu menu;
	menu.start();

	system("pause");
	return 0;
}

void Polynom::inputindex()
{
	std::wcout << L"������� ������� ������� ����������: ";
	std::wcin >> m_index;
	m_coeff = new int[m_index + 1];
}

void Polynom::inputcoeff()
{
	for (int i = 0; i < m_index + 1; i++)
	{
		if (i == 0)
		{
			std::wcout << L"������� ������������ �� ����� ������� ������� ���������� � ����� �������: ";
			std::wcin >> m_coeff[i];
		}
		else if (i == m_index)
		{
			std::wcout << L"������� ��������� ����: ";
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

	for (int i = 0; i < m_index + 1; i++) // �������� "����-if" :D 
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

		if (i != m_index && m_coeff[i + 1] > 0) // �������� �� ��������� ����, ����� ����� ���� �� �������� +
		{
			res += L"+";
		}
	}

	return res;
}

void Menu::menu()
{
	system("cls");
	std::wcout << L"\n�������� �������� ������� ������ �����������:\n";
	std::wcout << L"1. ����� �����������.\n";
	std::wcout << L"2. �������� �����������.\n";
	std::wcout << L"3. ������������ �����������. \n";
	std::wcout << L"4. ��������� �����������. \n";
	std::wcout << L"5. ����������������� ����������. \n";
	std::wcout << L"6. ���������� ����������\n";
	std::wcout << L"7. �����.\n";
}

int Menu::getvariants(int count) // "������", ����� ����� ������, ������� ����� ������������ 
{
	int variants;
	std::wstring s;
	std::wcin >> s;

	variants = std::stoi(s); // stoi - ��� �������� �� string � int

	while (variants < 1 || variants > count) {
		std::wcout << L"���-�� �� �������, ����� ��� ���, � ���� ����� ���������!\n";
		std::wcin >> s;
		variants = std::stoi(s);
	}

	return variants;
}

void Menu::start()
{
	std::wcout << L"������ ���������:\n";
	Polynom* poly1 = new Polynom;
	poly1->inputindex();
	poly1->inputcoeff();
	std::wcout << L"��������� ��������� ����: ";
	std::wcout << poly1->outputPolynom() << "\n"; // �� ��� �� ��������

	std::wcout << L"������ ���������:\n";
	Polynom* poly2 = new Polynom;
	poly2->inputindex();
	poly2->inputcoeff();
	std::wcout << L"��������� ��������� ����: ";
	std::wcout << poly2->outputPolynom() << "\n";

	int variants;

	do
	{
		_getch();  // ����� ����� ��������, ��� ���������!
		menu();
		variants = getvariants(7);
		switch (variants)
		{
		case 1:
		{
			std::wcout << L"����� ����������� �����:\n";
			Polynom poly3 = *poly1 + *poly2;
			std::wcout << poly3.outputPolynom();
			std::wcout << "\n\n\n\n";
			break;
		}
		case 2:
		{
			std::wcout << L"�������� ����������� �����:\n";
			Polynom poly3 = *poly1 - *poly2;
			std::wcout << poly3.outputPolynom();
			std::wcout << "\n\n\n\n";
			break;
		}
		case 3:
		{
			std::wcout << L"������������ ����������� �����:\n";
			Polynom poly3 = *poly1 * *poly2;
			std::wcout << poly3.outputPolynom();
			std::wcout << "\n\n\n\n";
			break;
		}
		case 4:
		{
			if (poly1 == poly2)
			{
				std::wcout << L"��������� �����������:";
				std::wcout << poly1->outputPolynom() << " " << "=" << " " << poly2->outputPolynom(); // ���������!
			}
			else
			{
				std::wcout << L"��������� �����������:\n";
				std::wcout << poly1->outputPolynom() << " " << (wchar_t)(0x2260) << " " << poly2->outputPolynom(); // ��, � ��� �� �����!!!
			}
			break;
		}
		case 5:
		{
			std::wcout << L"����������������� ����������:\n";
			std::wcout << (~(*poly1)).outputPolynom();  // ������� ����� ����, ������ ��� ��������!
			break;
		}
		case 6:
		{
			std::wcout << L"������ ���������:\n";
			poly1->inputindex();
			poly1->inputcoeff();
			std::wcout << L"��������� ��������� ����: ";
			std::wcout << poly1->outputPolynom() << "\n"; // �� ��� �� ��������

			std::wcout << L"������ ���������:\n";
			poly2->inputindex();
			poly2->inputcoeff();
			std::wcout << L"��������� ��������� ����: ";
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
		poly3.m_coeff[i] = 0; // ������ if-�� ���!
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
		poly3.m_coeff[i] = 0; // ����������
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

	return poly3; // ����������� � ��� ������
}

bool operator==(Polynom& poly1, Polynom& poly2)
{
	return poly1.outputPolynom() == poly2.outputPolynom(); // ����� �������� ������� ���� � ���������� ��� �������
}

Polynom operator~(Polynom& poly1)
{
	const int d = poly1.m_index - 1; // �������� ������ (����� ������� �����)
	Polynom diff(d);
	for (int i = 0; i <= d; i++) // ����� ��������� ���������, � ������ ������ (�� ���������� � ����)
	{
		diff.m_coeff[i] = 0;
	}
	for (int i = 0; i <= d; i++)
	{
		diff.m_coeff[i] = (poly1.m_index - i) * poly1.m_coeff[i];
	}

	return diff;
}



// �� ��� �� �� �������, ���� ��� ������ �����?
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

wchar_t Polynom::index_converter(unsigned int index) // ������� ���������, �� � ������� ��� ����, ���� ������ ����...
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