/*
ЛАБОРАТОРНАЯ РАБОТА №5
Раздел 1, Тема 3, Номер 3
Структура данных “список”(линейный, на базе массива с указателями - индексами)
*/

#include <iostream>
#include <locale.h>

#define SIZE 5

using namespace std;


struct Element
{
	int inf;
	int point;
};


struct List
{
	int count = 0;
	int size = SIZE;
	Element list[SIZE + 1];
};


int ConsoleReadLine() //функция проверка ввода
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


int Search(List *l, int to_search)
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


void Add(List *l)
{
	if (l->count == l->size)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список заполнен!" << endl;
		std::cout << "\n####################################################################\n";
	}
	else
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Введите число для добавления: ";
		int new_inf = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
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
			std::cout << "\n####################################################################\n\n";
			cout <<
				"Добавить: " << endl <<
				"  1. до элемента" << endl <<
				"  2. после элемента" << endl;
			do {
				add_type = ConsoleReadLine();
				if (add_type != 1 && add_type != 2)
					cout << "Ошибка ввода! Попробуйте: ";
			} while (add_type != 1 && add_type != 2);
			std::cout << "\n####################################################################\n\n";
			if (add_type == 1)
				cout << "Добавить до: ";
			else
				cout << "Добавить после: ";
			int data = ConsoleReadLine();
			std::cout << "\n####################################################################\n\n";
			int data_index = Search(l, data);
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
			std::cout << "\n####################################################################\n";
		}
	}
}


void Delete(List *l)
{
	if (l->count == 0)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n";
	}
	else
	{
		std::cout << "\n####################################################################\n";
		cout << "Введите элемент для удаления: ";
		int to_delete = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		int index = Search(l, to_delete);
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
		std::cout << "\n####################################################################\n";
	}
}


void Show(List *l)
{
	if (l->count == 0)
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n";
	}
	else
	{
		std::cout << "\n####################################################################\n\n";
		int i = l->list[0].point;
		while (i != 0)
		{
			cout << l->list[i].inf << " ";
			i = l->list[i].point;
		}
		cout << endl;
		std::cout << "\n####################################################################\n\n";
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

		std::cout << "\n####################################################################\n\n";
		cout <<
			"1. Показать" << endl <<
			"2. Добавить" << endl <<
			"3. Удалить" << endl <<
			"0. Выход" << endl;
		std::cout << "\n####################################################################\n\n";
		choice = ConsoleReadLine();

		system("cls");

		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			Show(&l);
			break;
		case 2:
			Add(&l);
			break;
		case 3:
			Delete(&l);
			break;
		default:
			cout << "Ошибка ввода!" << endl;
		}

		system("pause");
	} while (choice != 0);

	return 0;
}