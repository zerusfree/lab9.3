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
	SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

	int N;
	cout << "������ ������� �������� N: "; cin >> N;

	Route* p = new Route[N];
	
	string selectedItem;
	char filename[100];

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� ������������� �����" << endl;
		cout << " [4] - ���� �� ����� ���������� ��� ��������, �� ����������� ��� ����������� � ��������� �����" << endl;
		cout << " [5] - ����� ����� � ����" << endl;
		cout << " [6] - ���������� ����� �� �����" << endl << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
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
			cout << "������ ����� �����������/�����������: "; getline(cin, selectedItem);
			cout << endl;
			PrintRoutes(p, N, selectedItem);
			break;
		case 5:
			cin.get(); // ������� ����� ��������� � �� ����������� �������
			cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			SaveToFile(p, N, filename);
			break;
		case 6:
			cin.get(); 
			cin.sync(); 

			cout << "������ ��'� �����: "; cin.getline(filename, 99);
			LoadFromFile(p, N, filename);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);

	return 0;
}

void Create(Route* p, const int N)
{
	for (int i = 0; i < N; i++)
	{
		cout << "������ ����� ��������: ";cin >> p[i].numberOfRoute;
		cin.get();
		cin.sync();
		cout << endl;
		cout << "������ ����� ����������� ������ ��������: "; getline(cin, p[i].startPoint);
		
		cout << "������ ����� �������� ������ ��������: "; getline(cin, p[i].endPoint);
		cout << endl;
	}
}

void Print(Route* p, const int N)
{
	cout << "========================================================================"
		<< endl;
	cout << "| ����� �������� | ���������� ����� �������� | ʳ������ ����� �������� |"
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
	int* I = new int[N]; // ��������� ��������� �����
	int index = 0;
	for (int i = 0; i < N; i++)
	{
		if (p[i].endPoint == selectedItem || p[i].startPoint == selectedItem)
		{
			I[index] = i;
			index++;
		}
	}
	if (index > 0) // ���� �������� ��������
	{
		cout << "========================================================================" << endl;
		cout << "| ����� �������� | ���������� ����� �������� | ʳ������ ����� �������� |" << endl;
		cout << "------------------------------------------------------------------------" << endl;
		for (int i = 0; i < index; i++)
		{
			cout << "| " << setw(15) << left << p[I[i]].numberOfRoute
				<< "| " << setw(26) << right << p[I[i]].startPoint
				<< "| " << setw(24) << right << p[I[i]].endPoint << "|" << endl;
		}
		cout << "========================================================================" << endl;
	}
	else // ���� �� �������� ��������
	{
		cout << "�������� ���� ����� �������� ������� � ������� ��������" << endl;
	}
	delete[] I; // ��������� ���'���, ������� �� ��������� �����
}

void SaveToFile(Route* p, const int N, const char* filename)
{
	ofstream fout(filename, ios::binary); // ������� ������� ���� ������
	fout.write((char*)&N, sizeof(N)); // �������� ������� ��������
	for (int i = 0; i < N; i++)
		fout.write((char*)&p[i], sizeof(Route)); // �������� �������� ������
	fout.close(); // ������� ����
}

void LoadFromFile(Route*& p, int& N, const char* filename)
{
	delete[] p; // ������� �������� ���
	ifstream fin(filename, ios::binary); // ������� ������� ���� ����������
	fin.read((char*)&N, sizeof(N)); // ��������� ������� ��������
	p = new Route[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		fin.read((char*)&p[i], sizeof(Route)); // ��������� �������� ������
	fin.close(); // ������� ����
}