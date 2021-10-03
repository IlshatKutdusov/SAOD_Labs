/*
ЛАБОРАТОРНАЯ РАБОТА №16
Раздел 2, Тема 4, Номер 1
Алгоритмы сортировки и поиска "Поиск с использованием хеш-функций"
(бесконфликтная хеш-таблица, число ключей и размер таблицы равен 10, ключи - служебные слова языка Паскаль)
*/

#include <stdio.h>
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int Hash(string key, int n)
{
	int sum = 0;
	for (unsigned int i = 0; i < key.size(); i++)
		sum += key[i];
	return sum % n;
}

int get_from_cin()
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

string* Create(int n)
{
	string* Table = new string[n];
	for (int i = 0; i < n; i++)
		Table[i].empty();
	int i = 0;
	while (i < n)
	{
		string key;
		cout << endl << "key = ";
		cin >> key;
		int hash = Hash(key, n);
		if (Table[hash].empty())
			Table[hash] = key;
		else
		{
			cout << endl << "Возник конфликт. Необходимо заменить слово" << endl;
			continue;
		}
		i++;
	}
	return Table;
}

int Search(string key, string* Table, int n)
{
	int hash = Hash(key, n);
	if (Table[hash] == key)
		return hash;
	else
		return -1;
}

void Show(string* Table, int n)
{
	for (int i = 0; i < n; i++)
		cout << "Table[" << i << "] = " << Table[i] << endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string* Table = NULL;
	string key;
	int n = 0;
	int otv;
	do
	{
		system("cls");

		cout << "\n####################################################################\n\n";
		cout
			<< "1. Создать таблицу" << endl
			<< "2. Поиск" << endl
			<< "3. Показать" << endl
			<< "0. Выход" << endl;

		cout << "\n####################################################################\n\n";
		otv = get_from_cin();
		cout << "\n####################################################################\n\n";
		switch (otv)
		{
		case 1:
			if (Table != NULL)
				delete[] Table;
			cout << endl << "Введите размер таблицы: ";
			cin >> n;
			Table = Create(n);
			cout << endl << "Таблица создана" << endl;
			break;
		case 2:
			if (n != 0)
			{
				cout << endl << "Введите значение ключа = ";
				cin >> key;
				if (Search(key, Table, n) != -1)
					cout << endl << "Индекс = " << Search(key, Table, n) << endl;
				else
					cout << endl << "Не найдено" << endl;
			}
			else
				cout << endl << "Создайте таблицу" << endl;
			break;
		case 3:
			if (n != 0)
				Show(Table, n);
			else
				cout << endl << "Создайте таблицу" << endl;
			break;
		case 0:
			break;
		default:
			cout << endl << "Ошибка" << endl;
			break;
		}
		system("pause");
		cout << "\n####################################################################\n\n";
	} while (otv != 0);
}