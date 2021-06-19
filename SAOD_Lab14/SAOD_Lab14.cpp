/*
ЛАБОРАТОРНАЯ РАБОТА №14
Раздел 2, Тема 2
Алгоритмы сортировки и поиска "улучшенные методы сортировки"
(метод Шелла (вставок), метод быстрой сортировки (обмена), метод пирамидальной сортировки (выбора))
*/

#include <stdio.h>
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <cstdlib>

using namespace std;


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


int* Create(int n)
{
	if (n <= 10000)
	{
		int* mas;
		mas = new int[n];
		for (int i = 0; i < n; i++)
			mas[i] = rand() % 100;
		return mas;
	}
	return NULL;
}


void Copy(int* mas, int* copia, int n)
{
	for (int i = 0; i < n; i++)
		copia[i] = mas[i];
}


void Show(int* mas, int n)
{
	for (int i = 0; i < n; i++)
		cout << mas[i] << " ";
}


void ShowSort(int* mas, int n, int sravn, int moves)
{
	for (int i = 0; i < n; i++)
		cout << mas[i] << " ";
	cout << endl << "Количество сравнений: " << sravn
		<< endl << "Количество перестановок: " << moves;
	cout << endl << endl;;
}


void InsertionMethod_Shell(int* mas, int n, int* steps, int t) //метод вставок (метод Шелла)
{
	int sravn = 0, perestanov = 0;
	for (int m = 0; m < t; m++)
	{
		int k = steps[m];
		for (int i = k; i < n; i++)
		{
			int temp = mas[i];
			int j = i - k;
			perestanov++;
			while (sravn++ && j >= 0 && temp < mas[j])
			{
				mas[j + k] = mas[j];
				j = j - k;
				perestanov++;
			}
			perestanov++;
			mas[j + k] = temp;
		}
	}
	ShowSort(mas, n, sravn, perestanov / 3);
}


void ExchangeMethod_QuickSort(int* mas, int left, int right, int& sravn, int& perestanov) //метод обмена (метод быстрой сортировки)
{
	int i = left;
	int j = right;
	int mid = mas[(left + right) / 2];
	while (i <= j)
	{
		while (++sravn && mas[i] < mid) i++;
		while (++sravn && mas[j] > mid) j--;
		if (i <= j)
		{
			int temp = mas[i];
			mas[i] = mas[j];
			mas[j] = temp;
			i++;
			j--;
			perestanov++;
		}
	}
	if (left < j)
		ExchangeMethod_QuickSort(mas, left, j, sravn, perestanov);
	if (i < right)
		ExchangeMethod_QuickSort(mas, i, right, sravn, perestanov);
}


int sravn = 0, perestanov = 0;

void RyramidalSort(int* mas, int k, int n) //метод выбора (метод пирамидальной сортировки)
{
	while (1)
	{
		int left = 2 * k + 1;
		int right = 2 * k + 2;
		int largest;
		if (left < n && mas[left] > mas[k])
			largest = left;
		else
			largest = k;
		sravn++;
		if (right < n && mas[right] > mas[largest])
			largest = right;
		if (largest == k)
			break;
		int temp = mas[k];
		mas[k] = mas[largest];
		mas[largest] = temp;
		perestanov++;
		k = largest;
	}
}

void SelectionMethod_PyramidalSort(int* mas, int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--)
		RyramidalSort(mas, i, n);
	for (int i = n - 1; i >= 1; i--)
	{
		int temp = mas[0];
		mas[0] = mas[i];
		mas[i] = temp;
		perestanov++;
		RyramidalSort(mas, 0, i);
	}
	ShowSort(mas, n, sravn, perestanov);
	sravn = 0; perestanov = 0;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int num;
	int* unsort = NULL;
	int* sort = NULL;
	int menu_point;
	do
	{
		system("cls");

		cout << "\n####################################################################\n\n";
		cout <<
			"1. Создать массив" << endl <<
			"2. Показать неотсортированный массив" << endl <<
			"3. Метод Шелла" << endl <<
			"4. Метод быстрой сортировки" << endl <<
			"5. Метод пирамидальной сортировки" << endl <<
			"0. Выход" << endl;
		cout << "\n####################################################################\n\n";
		menu_point = ConsoleReadLine();

		system("cls");

		cout << "\n####################################################################\n\n";
		switch (menu_point)
		{
		case 1:
			if (unsort != NULL)
			{
				delete[] unsort;
				delete[] sort;
			}
			cout << "Введите количество элементов для добаления: ";
			cin >> num;
			unsort = Create(num);
			if (unsort != NULL)
			{
				sort = new int[num];
				cout << "Массив создан!" << endl;
			}
			else
				cout << "Массив невозможно создать!" << endl;
			break;
		case 2:
			if (unsort != NULL)
			{
				Show(unsort, num);
				cout << endl;
			}
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 3:
			if (unsort != NULL)
			{
				cout << "Введите количество шагов: ";
				int t;
				cin >> t;
				cout << endl << "Значения шагов: ";
				int* pSteps = new int[t];
				for (int i = 0; i < t; i++)
					cin >> pSteps[i];
				cout << endl;
				Copy(unsort, sort, num);
				InsertionMethod_Shell(sort, num, pSteps, t);
				delete[] pSteps;
			}
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 4:
			if (unsort != NULL)
			{
				int moves = 0, sravn = 0;
				Copy(unsort, sort, num);
				ExchangeMethod_QuickSort(sort, 0, num - 1, sravn, moves);
				ShowSort(sort, num, sravn, moves);
			}
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 5:
			if (unsort != NULL)
			{
				Copy(unsort, sort, num);
				SelectionMethod_PyramidalSort(sort, num);
			}
			else
				cout << endl << "Массив пуст!" << endl;
			break;
		case 0:
			delete[] sort;
			delete[] unsort;
			break;
		default:
			printf("Произошла ошибка!\n");
		}
		cout << "\n####################################################################\n\n";

		system("pause");
	} 	while (menu_point != 0);
}

