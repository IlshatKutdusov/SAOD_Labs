/*
ЛАБОРАТОРНАЯ РАБОТА №17
Раздел 2, Тема 4, Номер 3
Алгоритмы сортировки и поиска "Поиск с использованием хеш-функций"
(метод открытого хеширования, исходные ключи – любые слова,
размер хеш-таблицы должен задаваться в программе с помощью константы M)
*/

#include <stdio.h>
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

const int M = 7;

struct Item
{
	string key;
	Item* next;
};

struct List
{
	string key;
	Item* headitem;
};

List list[M];

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

void Initial()
{
	for (int i = 0; i < M; i++)
	{
		list[i].key.empty();
		list[i].headitem = new Item;
		list[i].headitem->next = NULL;
	}
}

int Hash(string key)
{
	int sum = 0;
	for (unsigned int i = 0; i < key.size(); i++)
		sum += key[i];
	return sum % M;
}

Item* GetItem(int index, int& count)
{
	Item* CurrentItem = list[index].headitem;
	while (++count && CurrentItem->next != NULL)
		CurrentItem = CurrentItem->next;
	return CurrentItem;
}

int Add(string key)
{
	int count = 0;
	int hash = Hash(key);
	if (++count && list[hash].key.empty())
		list[hash].key = key;
	else
	{
		cout << endl << "Возник конфликт" << endl;
		Item* CurrentItem = GetItem(hash, count);
		Item* tmp = new Item;
		tmp->key = key;
		tmp->next = NULL;
		CurrentItem->next = tmp;
		CurrentItem = tmp;
	}
	return count;
}

int Search(string key, int& count)
{
	int flag = 0;
	int hash = Hash(key);
	if (++count && list[hash].key == key)
		flag = 1;
	else
	{
		Item* tmp = list[hash].headitem->next;
		while (++count && tmp != NULL)
		{
			if (tmp->key == key)
			{
				flag = 1;
				break;
			}
			tmp = tmp->next;
		}
	}
	if (flag)
		return 1;
	else
		return 0;
}

void Show()
{
	cout << endl;
	for (int i = 0; i < M; i++)
	{
		cout << "Table[" << i << "] = " << list[i].key << " : ";
		Item* tmp = list[i].headitem->next;
		while (tmp != NULL)
		{
			cout << tmp->key << " ";
			tmp = tmp->next;
		}
		cout << endl;
	}
}

int Del(string key)
{
	int flag = 0;
	int hash = Hash(key);
	if (list[hash].key == key)
	{
		if (list[hash].headitem->next == NULL)
		{
			flag = 1;
			list[hash].key = "";
		}
		else
		{
			list[hash].key = list[hash].headitem->next->key;
			Item* tmp = list[hash].headitem->next;
			list[hash].headitem->next = tmp->next;
			flag = 1;
			delete tmp;
		}
	}
	else
	{
		Item* prev = list[hash].headitem;
		Item* tmp = list[hash].headitem->next;
		while (tmp != NULL)
		{
			if (tmp->key == key)
			{
				prev->next = tmp->next;
				delete tmp;
				flag = 1;
				break;
			}
			else
			{
				prev = tmp;
				tmp = tmp->next;
			}
		}
	}
	return flag;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	string key;
	Initial();
	int count;
	int otv;
	do
	{
		system("cls");

		cout << "\n####################################################################\n\n";
		puts("1. Добавить");
		puts("2. Искать");
		puts("3. Показать");
		puts("4. Удалить");
		puts("0. Выход");

		cout << "\n####################################################################\n\n";
		otv = get_from_cin();

		cout << "\n####################################################################\n\n";
		switch (otv)
		{
		case 1:
			cout << endl << "Введите ключ = ";
			cin >> key;
			count = 0;
			if (Search(key, count) != 0)
				cout << endl << "Ключ был использован, сравнений = " << count << endl;
			else
			{
				count = Add(key);
				cout << endl << "Ключ добавлен. Cравнений = " << count << endl;
			}
			break;
		case 2:
			cout << endl << "Введите ключ = ";
			cin >> key;
			count = 0;
			if (Search(key, count) != 0)
				cout << endl << "Найдено, сравнений = " << count << endl;
			else
				cout << endl << "Не найдено" << endl;
			break;
		case 3:
			Show();
			break;
		case 4:
			cout << endl << "Введите ключ = ";
			cin >> key;
			if (Del(key) == 1)
				cout << endl << "Удалено" << endl;
			else
				cout << endl << "Не найдено" << endl;
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