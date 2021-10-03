/*
ЛАБОРАТОРНАЯ РАБОТА №15
Раздел 2, Тема 3
Алгоритмы сортировки и поиска "специальные методы сортировки"
(карманная сортировка (с/без доп. массива), обобщенная карманная сортировка, поразрядная сортировка)
*/

#include <stdio.h>
#include "stdafx.h"
#include <conio.h> 
#include <iostream>
#include <cstdlib>

using namespace std;
int check;


int ConsoleReadLine()
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Ошибка ввода!" << endl;
		system("pause");
		cout << "Попробуйте еще раз: ";
		cin >> result;
	}
	return result;
}


int* CreateWith(int n) //массив с повторяющимися значениями
{
	if (n <= 10000 && n > 1)
	{
		check = 0;
		int* mas = new int[n];
		for (int i = 0; i < n; i++)
			mas[i] = rand() % n;
		return mas;
	}
	else
		return NULL;
}


int* CreateWithout(int n) //массива без повторяющихся значений
{
	if (n <= 10000 && n > 1)
	{
		check = 1;
		int* mas = new int[n];
		int i = 0;
		for (int i = 0; i < n; i++)
			mas[i] = i;

		for (int i = 0; i < n * 100; i++)
			swap(mas[rand() % (n - 1)], mas[rand() % (n - 1)]);
		return mas;
	}
	else
		return NULL;
}


void Show(int* mas, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << mas[i] << " ";
	cout << endl;
}

void Copy(int* mas, int* copia, int n)
{
	for (int i = 0; i < n; i++)
		copia[i] = mas[i];
}


void KarmanSortWith(int* mas, int n) //карманная сортировка с дополнительным массивом
{
	int perestan = 0;
	int* sort = new int[n];
	for (int i = 0; i < n; i++, perestan++)
		sort[mas[i]] = mas[i];
	Show(sort, n);
	cout << endl << "Сравнений не проводилось." << endl
		<< "Количество пересылок: " << perestan << endl;
	delete[] sort;
}


void KarmanSortWithout(int* mas, int n) //карманная сортировка без дополнительного массива
{
	int perestan = 0, srav = 0;
	for (int i = 0; i < n; i++)
		while (++srav && mas[i] != i)
		{
			int temp = mas[i];
			mas[i] = mas[temp];
			mas[temp] = temp;
			perestan++;
		}
	Show(mas, n);
	cout << endl << "Количество сравнений: " << srav << endl
		<< "Количество перестановок: " << perestan << endl;
}

struct list
{
	int inf;
	list* next;
};

void AddItem(list* plist, int inf)
{
	while (plist->next != NULL)
		plist = plist->next;
	plist->next = new list;
	plist->next->inf = inf;
	plist->next->next = NULL;
}

void Clear(list* head)
{
	while (head != NULL)
	{
		list* temp = head;
		head = head->next;
		delete temp;
	}
}


void ShowKarmanCommonSort(list* mas, int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		list* cur = mas[i].next;
		while (cur != NULL)
		{
			cout << cur->inf << " ";
			cur = cur->next;
		}
	}
	cout << endl;
}

void KarmanCommonSort(int* mas, int n) //Обобщенная карманная сортировка
{
	list* sort = new list[n];
	int perestan = 0;
	for (int i = 0; i < n; i++)
		sort[i].next = NULL;
	for (int i = 0; i < n; i++, perestan++)
		AddItem(&sort[mas[i]], mas[i]);
	ShowKarmanCommonSort(sort, n);
	cout << endl << "Количество пересылок: " << perestan << endl;
	for (int i = 0; i < n; i++)
		Clear(sort[i].next);
	delete[] sort;
}


void RadixSort(int* mas, int n) //Поразрядная сортировка
{
	list* sort = new list[10];
	int k = n - 1;
	int i = 0;
	int perestan = 0;
	while (k >= 1)
	{
		i++;
		k /= 10;
		for (int j = 0; j < 10; j++)
			sort[j].next = NULL;
		for (int j = 0; j < n; j++)
		{
			int div = 1;
			for (int l = 0; l < i; l++, div *= 10);
			AddItem(&sort[((mas[j] % div) * 10) / div], mas[j]);
			perestan++;
		}
		for (int j = 0, l = 0; l < n; j++)
		{
			list* temp = sort[j].next;
			while (temp != NULL)
			{
				mas[l] = temp->inf;
				temp = temp->next;
				l++;
				perestan++;
			}
		}
		for (int j = 0; j < 10; j++)
			Clear(sort[j].next);
	}
	Show(mas, n);
	cout << endl << "Количество пересылок: " << perestan << endl;
	delete[] sort;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int* unsort = NULL;
	int* sort = NULL;
	int n = 0;
	int point;
	do
	{
		system("cls");

		cout << "\n####################################################################\n\n";
		cout <<
			"1. Автоматическое создание массива с неповторяющимися значениями" << endl <<
			"2. Автоматическое создание массива с повторяющимися значениями" << endl <<
			"3. Показать исходный массив" << endl <<
			"4. Карманная сортировка с дополнительным массивом" << endl <<
			"5. Карманная сортировка без дополнительного массива" << endl <<
			"6. Обобщенная карманная сортировка" << endl <<
			"7. Поразрядная сортировка" << endl <<
			"0. Выход" << endl;
		cout << "\n####################################################################\n\n";
		point = ConsoleReadLine();

		system("cls");

		cout << "\n####################################################################\n";

		switch (point)
		{
		case 1:
			if (n > 0)
			{
				delete[] unsort;
				delete[] sort;
			}
			cout << endl << "Введите размер массива: ";
			cin >> n;
			cout << "\n####################################################################\n";
			unsort = CreateWithout(n);
			if (unsort != NULL)
			{
				sort = new int[n];
				cout << endl << "Массив создан" << endl;
			}
			else
			{
				cout << endl << "Невозможно создать массив" << endl;
				n = 0;
			}
			break;
		case 2:
			if (n > 0)
			{
				delete[] unsort;
				delete[] sort;
			}
			cout << endl << "Введите размер массива: ";
			cin >> n;
			cout << "\n####################################################################\n";
			unsort = CreateWith(n);
			if (unsort != NULL)
			{
				sort = new int[n];
				cout << endl << "Массив создан" << endl;
			}
			else
			{
				cout << endl << "Невозможно создать массив" << endl;
				n = 0;
			}
			break;
		case 3:
			if (n > 0)
				Show(unsort, n);
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 4:
			if (n > 0)
			{
				if (check)
				{
					Copy(unsort, sort, n);
					KarmanSortWith(sort, n);
				}
				else
					cout << endl << "Создайте массив с неповторяющимися значениями" << endl;
			}
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 5:
			if (n > 0)
			{
				if (check)
				{
					Copy(unsort, sort, n);
					KarmanSortWithout(sort, n);
				}
				else
					cout << endl << "Создайте массив с неповторяющимися значениями" << endl;
			}
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 6:
			if (n > 0)
			{
				KarmanCommonSort(unsort, n);
			}
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 7:
			if (n > 0)
			{
				Copy(unsort, sort, n);
				RadixSort(sort, n);
			}
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 0:
			break;
		default:
			cout << endl << "Ошибка" << endl;
			break;
		}
		cout << "\n####################################################################\n\n";

		system("pause");
	} 	while (point != 0);
}