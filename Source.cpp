#include<iostream>
#include<iomanip>
#include<Windows.h>
#include <fstream>
#include<string>

using namespace std;

struct Route
{
	string startPoint;
	string endPoint;
	int numberOfRoute;
};

void Create(Route* p, const int N);
void Print(Route* p, const int N);
void Sort(Route* p, const int N);
void PrintRoutes(Route* p, const int N, const string selectedItem);
void SaveToFile(Route* p, const int N, const char* filename);
void LoadFromFile(Route*& p, int& N, const char* filename);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість маршрутів N: "; cin >> N;

	Route* p = new Route[N];
	
	string selectedItem;
	char filename[100];

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - вивід на екран інформації про маршрути, які починаються або закінчуються у вибраному пункті" << endl;
		cout << " [5] - запис даних у файл" << endl;
		cout << " [6] - зчитування даних із файлу" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			Print(p, N);
			break;
		case 4:
			cin.get();
			cin.sync();
			cout << "Введіть пункт призначення/відправлення: "; getline(cin, selectedItem);
			cout << endl;
			PrintRoutes(p, N, selectedItem);
			break;
		case 5:
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 6:
			cin.get(); 
			cin.sync(); 

			cout << "Введіть ім'я файлу: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	return 0;
}

void Create(Route* p, const int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << "Введіть номер маршруту: ";cin >> p[i].numberOfRoute;
		cin.get();
		cin.sync();
		cout << endl;
		cout << "Введіть назву початкового пункту маршруту: "; getline(cin, p[i].startPoint);
		
		cout << "Введіть назву кінцевого пункту маршруту: "; getline(cin, p[i].endPoint);
		cout << endl;
	}
}

void Print(Route* p, const int N)
{
	cout << "========================================================================"
		<< endl;
	cout << "| Номер маршруту | Початковий пункт маршруту | Кінцевий пункт маршруту |"
		<< endl;
	cout << "------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(15) << left << p[i].numberOfRoute
			<< "| " << setw(26) << right << p[i].startPoint 
			<< "| " << setw(24) << right << p[i].endPoint << "|" << endl;
	}
	cout << "========================================================================"
		<< endl;
	cout << endl;
}

void Sort(Route* p, const int N)
{
	Route tmp;
	for (int i0 = 0; i0 < N; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
		{
			if (p[i1].numberOfRoute > p[i1 + 1].numberOfRoute)
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
		}
}

void PrintRoutes(Route* p, const int N, const string selectedItem)
{
	int* I = new int[N]; // створюємо індексний масив
	int index = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].endPoint == selectedItem || p[i].startPoint == selectedItem)
		{
			I[index] = i;
			index++;
		}
	}
	if (index > 0) // якщо знайдено маршрути
	{
		cout << "========================================================================" << endl;
		cout << "| Номер маршруту | Початковий пункт маршруту | Кінцевий пункт маршруту |" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		for (int i = 0; i < index; i++)
		{
			cout << "| " << setw(15) << left << p[I[i]].numberOfRoute
				<< "| " << setw(26) << right << p[I[i]].startPoint
				<< "| " << setw(24) << right << p[I[i]].endPoint << "|" << endl;
		}
		cout << "========================================================================" << endl;
	}
	else // якщо не знайдено маршрутів
	{
		cout << "Вибраний вами пункт маршруту відсутній у таблиці маршрутів" << endl;
	}
	delete[] I; // звільнюємо пам'ять, виділену під індексний масив
}

void SaveToFile(Route* p, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // відкрили бінарний файл запису
	fout.write((char*)&N, sizeof(N)); // записали кількість елементів
	for (int i = 0; i < N; i++)
		fout.write((char*)&p[i], sizeof(Route)); // записали елементи масиву
	fout.close(); // закрили файл
}

void LoadFromFile(Route*& p, int& N, const char* filename)
{
	delete[] p; // знищили попередні дані
	ifstream fin(filename, ios::binary); // відкрили бінарний файл зчитування
	fin.read((char*)&N, sizeof(N)); // прочитали кількість елементів
	p = new Route[N]; // створили динамічний масив
	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Route)); // прочитали елементи масиву
	fin.close(); // закрили файл
}