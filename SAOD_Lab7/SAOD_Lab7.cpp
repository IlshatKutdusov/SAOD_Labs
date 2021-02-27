/*
ЛАБОРАТОРНАЯ РАБОТА №7
Раздел 1, Тема 4, Номер 1

*/

#include <iostream>
#include <locale.h>

using namespace std;

struct element
{
	int inf;
	element* prev;
	element* next;
};

element* list = new element;


int get_from_cin()
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Ошибка ввода!" << endl;
		system("pause");
		cout << "Попробуйте снова: ";
		cin >> result;
	}
	return result;
}


int choice()
{
	int result;
	do {
		result = get_from_cin();
		if (result != 1 && result != 2)
			cout << "Ошибка ввода! Попробуйте снова: ";
	} while (result != 1 && result != 2);
	return result;
}


element* search(int item, bool step = false)
{
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else
	{
		int i = 0;
		element*t = list->next;
		do
		{
			if (t->inf == item) {
				if (step)
					cout << i << " шаг" << endl;
				return t;
			}
			t = t->next;
			i++;
		} while (t != list->next);
	}
	return nullptr;
}


element* search_back(int item, bool step = false)
{
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else
	{
		int i = 0;
		element*t = list->prev;
		do
		{
			if (t->inf == item) {
				if (step)
					cout << i << " шаг" << endl;
				return t;
			}
			t = t->prev;
			i++;
		} while (t != list->prev);
	}
	return nullptr;
}


void add()
{
	cout << "Введите значение для добавления: ";
	int new_item = get_from_cin();

	element* new_element = new element;
	new_element->inf = new_item;

	if (list->prev == list && list->next == list)
	{
		list->prev = new_element;
		list->next = new_element;
		new_element->next = new_element;
		new_element->prev = new_element;
	}
	else
	{
		cout <<
			"Добавить: " << endl <<
			"  1. До" << endl <<
			"  2. После" << endl;
		int add_type = choice();

		system("cls");

		if (add_type == 1)
			cout << "Добавить до: ";
		else
			cout << "Добавить после: ";
		int item = get_from_cin();

		element* item_element = search(item);
		if (item_element == nullptr)
		{
			cout << item << " не найден!";
			delete new_element;
		}
		else
		{
			if (add_type == 1 && list->next == item_element)
				list->next = new_element;

			if (add_type == 2 && list->prev == item_element)
				list->prev = new_element;

			if (add_type == 1)
				item_element = item_element->prev;

			element* prev = item_element;
			element* next = item_element->next;

			prev->next = new_element;
			next->prev = new_element;

			new_element->next = next;
			new_element->prev = prev;
		}
	}
}


void del()
{
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите значение для удаления: ";
		int to_delete = get_from_cin();

		element* elem_delete = search(to_delete);
		if (elem_delete == nullptr)
			cout << to_delete << " не найден!" << endl;

		if (list->prev == list->next)
		{
			list->prev = list;
			list->next = list;
		}
		else
		{
			element* prev = elem_delete->prev;
			element* next = elem_delete->next;
			prev->next = next;
			next->prev = prev;

			if (list->next == elem_delete)
				list->next = elem_delete->next;
			if (list->prev == elem_delete)
				list->prev = elem_delete->prev;
		}

		delete  elem_delete;
	}
}


void search_menu()
{
	cout <<
		"Поиск: " << endl <<
		"  1. прямой" << endl <<
		"  2. обратный" << endl;
	int search_type = choice();

	system("cls");

	cout << "Введите элемент для поиска: ";
	int to_delete = get_from_cin();

	element* elem;
	if (search_type == 1)
		elem = search(to_delete, true);
	else
		elem = search_back(to_delete, true);

	if (elem == nullptr)
		cout << to_delete << " не найден" << endl;
	else
		cout << to_delete << " найден" << endl;
}


void show()
{
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else {
		cout <<
			"Показать: " << endl <<
			"  1. в прямом направлении" << endl <<
			"  2. в обратном направлении" << endl;
		int show_type = choice();

		system("cls");

		if (show_type == 2)
		{
			cout << "Список: ";
			element* t = list->prev;
			do
			{
				cout << t->inf << " ";
				t = t->prev;
			} while (t != list->prev);
			cout << endl;
		}
		else {
			cout << "Список: ";
			element* t = list->next;
			do
			{
				cout << t->inf << " ";
				t = t->next;
			} while (t != list->next);
			cout << endl;
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	list->prev = list;
	list->next = list;

	int menu_point;

	do {
		system("cls");

		cout <<
			"1. Добавить" << endl <<
			"2. Удалить" << endl <<
			"3. Поиск" << endl <<
			"4. Показать" << endl <<
			"0. Выход" << endl;
		menu_point = get_from_cin();

		system("cls");

		switch (menu_point)
		{
		case 0:
			return 0;
		case 1:
			add();
			break;
		case 2:
			del();
			break;
		case 3:
			search_menu();
			break;
		case 4:
			show();
			break;
		default:
			cout << "Ошибка ввода!" << endl;
		}

		system("pause");
	} while (menu_point != 0);

	return 0;
}