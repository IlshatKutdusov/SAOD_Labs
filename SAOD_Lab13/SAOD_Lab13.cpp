/*
ЛАБОРАТОРНАЯ РАБОТА №13
Раздел 2, Тема 1
Алгоритмы сортировки и поиска "простейшие методы сортировки"
(сортировка обменом (метод пузырька), сортировка выбором, сортировка вставками)
*/

#include <stdio.h>
#include "stdafx.h"
#include <conio.h>
#include <iostream>

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
		printf("%d ", mas[i]);
}


void ExchangeMethod(int* mas, int n) //метод обмена (метод пузырька)
{
	int sravn = 0, perestanov = 0;
	for (int i = 0; i < n; i++)
		for (int j = n - 1; j > i; j--, sravn++)
			if (mas[j] < mas[j - 1])
			{
				int temp = mas[j];
				mas[j] = mas[j - 1];
				mas[j - 1] = temp;
				perestanov++;
			}
	Show(mas, n);
	printf("\nКоличество перестановок: %d", perestanov);
	printf("\nКоличество сравнений: %d", sravn);
	printf("\n");
}

void InsertionMethod(int* mas, int n) //метод вставок
{
	int sravn = 0, perestanov = 0;
	for (int i = 1; i < n; i++)
	{
		int temp = mas[i];
		perestanov++;
		int j = i - 1;
		while (sravn++ && j >= 0 && temp < mas[j])
		{
			mas[j + 1] = mas[j];
			j--;
			perestanov++;
		}
		mas[j + 1] = temp;
		perestanov++;
	}
	Show(mas, n);
	printf("\nКоличество перестановок: %d", perestanov / 3);
	printf("\nКоличество сравнений: %d", sravn);
	printf("\n");
}

void SelectionMethod(int* mas, int n) //метод выбора
{
	int sravn = 0, perestanov = 0;
	int Min = 0;
	for (int i = 0; i < n; i++)
	{
		Min = i;
		for (int j = Min + 1; j < n; j++, sravn++)
		{
			if (mas[j] < mas[Min])
				Min = j;
		}
		if (Min != i)
		{
			int temp = mas[Min];
			mas[Min] = mas[i];
			mas[i] = temp;
			perestanov++;
		}
	}
	Show(mas, n);
	printf("\nКоличество перестановок: %d", perestanov);
	printf("\nКоличество сравнений: %d", sravn);
	printf("\n");
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
			"3. Метод пузырька" << endl <<
			"4. Метод вставок" << endl <<
			"5. Метод выбора" << endl <<
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
			printf("Введите количество элементов для добаления: ");
			scanf_s("%d", &num);
			unsort = Create(num);
			if (unsort != NULL)
			{
				sort = new int[num];
				printf("Массив создан!\n");
			}
			else
				printf("Массив невозможно создать!\n");
			break;
		case 2:
			if (unsort != NULL)
			{
				Show(unsort, num);
				printf("\n");
			}
			else
				printf("\nМассив пуст!\n");
			break;
		case 3:
			if (unsort != NULL)
			{
				Copy(unsort, sort, num);
				ExchangeMethod(sort, num);
			}
			else
				printf("\nМассив пуст!\n");
			break;
		case 4:
			if (unsort != NULL)
			{
				Copy(unsort, sort, num);
				InsertionMethod(sort, num);
			}
			else
				printf("\nМассив пуст!\n");
			break;
		case 5:
			if (unsort != NULL)
			{
				Copy(unsort, sort, num);
				SelectionMethod(sort, num);
			}
			else
				printf("\nМассив пуст!\n");
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
	return 0;
}
