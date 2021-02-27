/*
ЛАБОРАТОРНАЯ РАБОТА №4
Раздел 1, Тема 3, Номер 2
Структура данных “список”(упорядоченный, линейный, на основе массива, статическая реализация)
*/

#include "stdafx.h"
#include <iostream>
#include <locale.h>

using namespace std;

#define LIST_SIZE 5


struct IntList
{
	int count = 0;
	int list[LIST_SIZE];
	int size = LIST_SIZE;
};


struct CharList
{
	int count = 0;
	char list[LIST_SIZE][5];
	int size = LIST_SIZE;
};


int ConsoleReadKey()
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


void Show(IntList *l)
{
	if (l->count == 0)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		std::cout << "\n####################################################################\n\n";
		for (int i = 0; i < l->count; i++)
			cout << l->list[i] << " ";
		cout << endl;
		std::cout << "\n####################################################################\n\n";
	}
}


void Show(CharList *l)
{
	if (l->count == 0)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		std::cout << "\n####################################################################\n\n";
		for (int i = 0; i < l->count; i++)
			cout << l->list[i] << " ";
		cout << endl;
		std::cout << "\n####################################################################\n\n";
	}
}


int Find(IntList *l, int to_find)
{
	for (int i = 0; i < l->count; i++)
	{
		if (l->list[i] == to_find)
			return i;
	}
	return -1;
}


int Find(CharList *l, char* to_find)
{
	for (int i = 0; i < l->count; i++)
	{
		if (strcmp(l->list[i], to_find) == 0)
			return i;
	}
	return -1;
}


void Add(IntList *l) // числа
{
	if (l->count == l->size)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список заполнен!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Введите число, чтобы добавить: ";
		int to_add = ConsoleReadKey();
		std::cout << "\n####################################################################\n\n";
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


void Add(CharList *l) // символы
{
	if (l->count == l->size)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список заполнен!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Введите строку, чтобы добавить: ";
		char to_add[5];
		cin >> to_add;
		std::cout << "\n####################################################################\n\n";
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


void ToDelete(IntList *l)//функция удаления
{
	if (l->count == 0)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Введите число для удаления:: ";
		int ToDelete = ConsoleReadKey();
		std::cout << "\n####################################################################\n\n";
		int index = Find(l, ToDelete);
		if (index == -1)
			cout << "Число не найдено!" << endl;
		else
		{
			for (int i = index; i < l->count - 1; i++)
				l->list[i] = l->list[i + 1];
			l->count--;
			cout << ToDelete << " удален!" << endl;
		}
	}
}


void ToDelete(CharList *l)
{
	if (l->count == 0)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Введите строку для удаления: ";
		char ToDelete[5];
		cin >> ToDelete;
		std::cout << "\n####################################################################\n\n";
		int index = Find(l, ToDelete);
		if (index == -1)
			cout << "Строка не найдена!" << endl;
		else
		{
			for (int i = index; i < l->count - 1; i++)
				strcpy_s(l->list[i], l->list[i + 1]);
			l->count--;
			cout << ToDelete << " удален!" << endl;
		}
		std::cout << "\n####################################################################\n\n";
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
		list_type = ConsoleReadKey();
		if (list_type != 1 && list_type != 2)
			cout << "Неправильный ввод! Попробуйте заново: ";
	} while (list_type != 1 && list_type != 2);

	IntList list_i;
	CharList list_c;

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

		choice = ConsoleReadKey();

		system("cls");

		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			if (list_type == 1)
				Show(&list_i);
			else
				Show(&list_c);
			break;
		case 2:
			if (list_type == 1)
				Add(&list_i);
			else
				Add(&list_c);
			break;
		case 3:
			if (list_type == 1)
				ToDelete(&list_i);
			else
				ToDelete(&list_c);
			break;
		default:
			cout << "Неправильный ввод!" << endl;
		}
		system("pause");
	}

	return 0;
}