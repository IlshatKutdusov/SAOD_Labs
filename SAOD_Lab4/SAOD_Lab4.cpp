/*
ЛАБОРАТОРНАЯ РАБОТА №4
Раздел 1, Тема 3, Номер 2
МОДЕЛИРОВАНИЕ УПОРЯДОЧЕННОГО ЛИНЕЙНОГО СПИСКА С ПОМОЩЬЮ МАССИВА
*/

#include "stdafx.h"
#include <iostream>
#include <locale.h>

using namespace std;

#define LIST_SIZE 5


struct list_int
{
	int count = 0;
	int list[LIST_SIZE];
	int size = LIST_SIZE;
};


struct list_char
{
	int count = 0;
	char list[LIST_SIZE][5];
	int size = LIST_SIZE;
};


int get_from_cin()
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Ошибка ввода!" << endl;
		system("pause");
		cout << "Попробуйте заново: ";
		cin >> result;
	}
	return result;
}


void show(list_int *l)
{
	if (l->count == 0)
		cout << "Список пуст!" << endl;
	else
	{
		for (int i = 0; i < l->count; i++)
			cout << l->list[i] << " ";
		cout << endl;
	}
}


void show(list_char *l)
{
	if (l->count == 0)
		cout << "Список пуст!" << endl;
	else
	{
		for (int i = 0; i < l->count; i++)
			cout << l->list[i] << " ";
		cout << endl;
	}
}


int find(list_int *l, int to_find)
{
	for (int i = 0; i < l->count; i++)
	{
		if (l->list[i] == to_find)
			return i;
	}
	return -1;
}


int find(list_char *l, char* to_find)
{
	for (int i = 0; i < l->count; i++)
	{
		if (strcmp(l->list[i], to_find) == 0)
			return i;
	}
	return -1;
}


void add(list_int *l) // числа
{
	if (l->count == l->size)
		cout << "Список заполнен!" << endl;
	else
	{
		cout << "Введите число, чтобы добавить: ";
		int to_add = get_from_cin();

		bool has_added = false;

		for (int i = 0; i < l->count; i++)
		{
			if (to_add < l->list[i])
			{
				for (int j = l->count; j >= i; j--)
					l->list[j] = l->list[j - 1];

				l->list[i] = to_add;
				has_added = true;
				break;
			}
		}

		if (!has_added)
			l->list[l->count] = to_add;

		l->count++;
		cout << to_add << " добавлен!" << endl;
	}
}


void add(list_char *l) // символы
{
	if (l->count == l->size)
		cout << "Список заполнен!" << endl;
	else
	{
		cout << "Введите строку, чтобы добавить: ";
		char to_add[5];
		cin >> to_add;

		bool has_added = false;

		for (int i = 0; i < l->count; i++)
		{
			if (strcmp(to_add, l->list[i]) < 0)
			{
				for (int j = l->count; j >= i; j--)
					strcpy_s(l->list[j], l->list[j - 1]);
				strcpy_s(l->list[i], to_add);
				has_added = true;
				break;
			}
		}

		if (!has_added)
			strcpy_s(l->list[l->count], to_add);

		l->count++;
		cout << to_add << " добавлен!" << endl;
	}
}


void to_delete(list_int *l)//функция удаления
{
	if (l->count == 0)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите число для удаления:: ";
		int to_delete = get_from_cin();

		int index = find(l, to_delete);
		if (index == -1)
			cout << "Число не найдено!" << endl;
		else
		{
			for (int i = index; i < l->count - 1; i++)
				l->list[i] = l->list[i + 1];
			l->count--;
			cout << to_delete << " удален!" << endl;
		}
	}
}


void to_delete(list_char *l)
{
	if (l->count == 0)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите строку для удаления: ";
		char to_delete[5];
		cin >> to_delete;

		int index = find(l, to_delete);
		if (index == -1)
			cout << "Строка не найдена!" << endl;
		else
		{
			for (int i = index; i < l->count - 1; i++)
				strcpy_s(l->list[i], l->list[i + 1]);
			l->count--;
			cout << to_delete << " удален!" << endl;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	int list_type = -1;
	std::cout << "\n####################################################################\n\n";
	cout << "1. Список чисел" << endl <<
		"2. Список строк " << endl;
	std::cout << "\n####################################################################\n";
	do
	{
		list_type = get_from_cin();
		if (list_type != 1 && list_type != 2)
			cout << "Неправильный ввод! Попробуйте заново: ";
	} while (list_type != 1 && list_type != 2);

	list_int list_i;
	list_char list_c;

	int choice = -1;

	while (choice != 0)
	{
		system("cls");
		std::cout << "\n####################################################################\n\n";
		cout <<
			"1. Показать" << endl <<
			"2. Добавить" << endl <<
			"3. Удалить" << endl <<
			"0. Выход" << endl;
		std::cout << "\n####################################################################\n";

		choice = get_from_cin();

		system("cls");

		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			if (list_type == 1)
				show(&list_i);
			else
				show(&list_c);
			break;
		case 2:
			if (list_type == 1)
				add(&list_i);
			else
				add(&list_c);
			break;
		case 3:
			if (list_type == 1)
				to_delete(&list_i);
			else
				to_delete(&list_c);
			break;
		default:
			cout << "Неправильный ввод!" << endl;
		}
		system("pause");
	}

	return 0;
}