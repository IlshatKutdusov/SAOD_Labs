/*
ЛАБОРАТОРНАЯ РАБОТА №5
Раздел 1, Тема 3, Номер 3
ЛИНЕЙНЫЙ СПИСОК НА БАЗЕ МАССИВА С УКАЗАТЕЛЯМИ - ИНДЕКСАМИ
*/

#include <iostream>
#include <locale.h>

#define SIZE 5

using namespace std;


struct element
{
	int inf;
	int point;
};


struct List
{
	int count = 0;
	int size = SIZE;
	element list[SIZE + 1];
};


int get_from_cin() //функция проверка ввода
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Неправильный ввод!" << endl;
		system("pause");
		cout << "Попробуйте еще раз: ";
		cin >> result;
	}
	return result;
}


int search(List *l, int to_search)
{
	int i = 0;
	do
	{
		if (l->list[i].inf == to_search)
		{
			for (int j = 0;; j++)
			{
				if (l->list[j].point == i) {
					return j;
				}
			}
		}
		i = l->list[i].point;
	} while (i != 0);
	return -1;
}


void add(List *l)
{
	if (l->count == l->size)
		cout << "Список заполнен!" << endl;
	else
	{
		cout << "Введите число для добавления: ";
		int new_inf = get_from_cin();

		if (l->count == 0)
		{
			l->list[1].point = l->list[0].point;
			l->list[0].point = 1;
			l->list[1].inf = new_inf;
			l->count++;
		}
		else
		{
			int free_index;
			for (free_index = 1; l->list[free_index].point != -1; free_index++) {}

			int add_type;
			cout <<
				"Добавить: " << endl <<
				"  1. до элемента" << endl <<
				"  2. после элемента" << endl;
			do {
				add_type = get_from_cin();
				if (add_type != 1 && add_type != 2)
					cout << "Ошибка ввода! Попробуйте: ";
			} while (add_type != 1 && add_type != 2);

			if (add_type == 1)
				cout << "Добавить до: ";
			else
				cout << "Добавить после: ";
			int data = get_from_cin();

			int data_index = search(l, data);
			if (data_index == -1)
				cout << data << " элемент не найден!" << endl;
			else
			{
				if (add_type == 2)
					data_index = l->list[data_index].point;

				l->list[free_index].inf = new_inf;
				l->list[free_index].point = l->list[data_index].point;
				l->list[data_index].point = free_index;
				l->count++;
			}
		}
	}
}


void del(List *l)
{
	if (l->count == 0)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите элемент для удаления: ";
		int to_delete = get_from_cin();

		int index = search(l, to_delete);
		if (index == -1)
			cout << to_delete << " элемент не найден!" << endl;
		else
		{
			int next = l->list[l->list[index].point].point;
			l->list[l->list[index].point].point = -1;
			l->list[index].point = next;
			l->count--;
			cout << to_delete << " удален!" << endl;
		}
	}
}


void show(List *l)
{
	if (l->count == 0)
		cout << "Список пуст!" << endl;
	else
	{
		int i = l->list[0].point;
		while (i != 0)
		{
			cout << l->list[i].inf << " ";
			i = l->list[i].point;
		}
		cout << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	List l;

	l.list[0].point = 0;
	for (int i = 1; i < l.size + 1; i++)
		l.list[i].point = -1;

	int choice;

	do {
		system("cls");

		cout <<
			"1. Добавить" << endl <<
			"2. Удалить" << endl <<
			"3. Показать" << endl <<
			"0. Выход" << endl;
		choice = get_from_cin();

		system("cls");

		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			add(&l);
			break;
		case 2:
			del(&l);
			break;
		case 3:
			show(&l);
			break;
		default:
			cout << "Ошибка ввода!" << endl;
		}

		system("pause");
	} while (choice != 0);

	return 0;
}