/*
ЛАБОРАТОРНАЯ РАБОТА №6
Раздел 1, Тема 3, Номер 5

*/

#include <iostream>
#include <locale.h>

using namespace std;


struct element
{
	int inf;
	element* next = nullptr;
};


element* list = new element;
element* additional = new element;


int get_from_cin()
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


element* search(int data)
{
	for (element* t = list; t != nullptr; t = t->next)
		if (t->next != nullptr && t->next->inf == data)
			return t;
	return nullptr;
}


void show()
{
	if (list->next == nullptr)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Основной список: ";
		for (element*t = list->next; t != nullptr; t = t->next)
			cout << t->inf << " ";
		cout << endl;
	}
}


void show_additional()
{
	if (additional->next == nullptr)
		cout << "Дополнительный список пуст!" << endl;
	else
	{
		cout << "Дополнительный список: ";
		for (element*t = additional->next; t != nullptr; t = t->next)
			cout << t->inf << " ";
		cout << endl;
	}
}


void add()
{
	cout << "Введите число для добавления: ";
	int new_inf = get_from_cin();

	element* new_element = new element;
	new_element->inf = new_inf;

	if (list->next == nullptr)
		list->next = new_element;
	else
	{
		int add_type;
		cout <<
			"Добавить: " << endl <<
			"  1. до" << endl <<
			"  2. после" << endl;
		do {
			add_type = get_from_cin();
			if (add_type != 1 && add_type != 2)
				cout << "Ошибка ввода! Попробуйте снова: ";
		} while (add_type != 1 && add_type != 2);

		if (add_type == 1)
			cout << "Добавить до: ";
		else
			cout << "Добавить после: ";
		int data = get_from_cin();

		element* item_element = search(data);
		if (item_element == nullptr)
		{
			cout << data << " элемент не найден!";
			delete new_element;
		}
		else
		{
			if (add_type == 2)
				item_element = item_element->next;

			new_element->next = item_element->next;
			item_element->next = new_element;
		}

	}
}


void push_additional(element* n)
{
	n->next = additional->next;
	additional->next = n;
}


void del()
{
	if (list->next == nullptr)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите число для удаления: ";
		int to_delete = get_from_cin();

		element* index = search(to_delete);
		if (index == nullptr)
			cout << to_delete << " элемент не найден!" << endl;
		else
		{
			element* t = index->next;
			index->next = t->next;
			push_additional(t);
		}
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	int choice;

	do {
		system("cls");

		cout <<
			"1. Добавить" << endl <<
			"2. Удалить" << endl <<
			"3. Показать основной список" << endl <<
			"4. Показать дополнительный список" << endl <<
			"0. Выход" << endl;
		choice = get_from_cin();

		system("cls");

		switch (choice)
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
			show();
			break;
		case 4:
			show_additional();
			break;
		default:
			cout << "Ошибка ввода!" << endl;
		}

		system("pause");
	} while (choice != 0);

	return 0;
}