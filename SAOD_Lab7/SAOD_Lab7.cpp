/*
ЛАБОРАТОРНАЯ РАБОТА №7
Раздел 1, Тема 4, Номер 1
Структура данных "список"(линейный, динамический, двунаправленный, кольцевой, должен иметь заголовок)
*/

#include <iostream>
#include <locale.h>

using namespace std;

struct Element
{
	int inf;
	Element* prev;
	Element* next;
};

Element* list = new Element;


int ConsoleReadLine()
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


int Choice()
{
	int result;
	do {
		result = ConsoleReadLine();
		if (result != 1 && result != 2)
			cout << "Ошибка ввода! Попробуйте снова: ";
	} while (result != 1 && result != 2);
	return result;
}


Element* Search(int item, bool step = false)
{
	std::cout << "\n####################################################################\n\n";
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else
	{
		int i = 0;
		Element*t = list->next;
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
	std::cout << "\n####################################################################\n\n";
	return nullptr;
}


Element* SearchBack(int item, bool step = false)
{
	std::cout << "\n####################################################################\n\n";
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else
	{
		int i = 0;
		Element*t = list->prev;
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
	std::cout << "\n####################################################################\n\n";
	return nullptr;
}


void Add()
{
	std::cout << "\n####################################################################\n\n";
	cout << "Введите значение для добавления: ";
	int new_item = ConsoleReadLine();
	std::cout << "\n####################################################################\n\n";
	Element* new_element = new Element;
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
		std::cout << "\n####################################################################\n\n";
		cout <<
			"Добавить: " << endl <<
			"  1. До" << endl <<
			"  2. После" << endl;
		std::cout << "\n####################################################################\n\n";
		int add_type = Choice();

		system("cls");
		std::cout << "\n####################################################################\n\n";
		if (add_type == 1)
			cout << "Добавить до: ";
		else
			cout << "Добавить после: ";
		int item = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		Element* item_element = Search(item);
		if (item_element == nullptr)
		{
			cout << item << " не найден!";
			std::cout << "\n####################################################################\n\n";
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

			Element* prev = item_element;
			Element* next = item_element->next;

			prev->next = new_element;
			next->prev = new_element;

			new_element->next = next;
			new_element->prev = prev;
		}
	}
}


void Delete()
{
	std::cout << "\n####################################################################\n\n";
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите значение для удаления: ";
		int to_delete = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		Element* elem_delete = Search(to_delete);
		if (elem_delete == nullptr)
		{
			cout << to_delete << " не найден!" << endl;
			std::cout << "\n####################################################################\n\n";
		}

		if (list->prev == list->next)
		{
			list->prev = list;
			list->next = list;
		}
		else
		{
			Element* prev = elem_delete->prev;
			Element* next = elem_delete->next;
			prev->next = next;
			next->prev = prev;

			if (list->next == elem_delete)
				list->next = elem_delete->next;
			if (list->prev == elem_delete)
				list->prev = elem_delete->prev;
		}

		delete elem_delete;
	}
}


void SearchMenu()
{
	std::cout << "\n####################################################################\n\n";
	cout <<
		"Поиск: " << endl <<
		"  1. прямой" << endl <<
		"  2. обратный" << endl;
	std::cout << "\n####################################################################\n\n";
	int search_type = Choice();
	std::cout << "\n####################################################################\n\n";
	system("cls");
	std::cout << "\n####################################################################\n\n";
	cout << "Введите элемент для поиска: ";
	int to_delete = ConsoleReadLine();
	std::cout << "\n####################################################################\n\n";
	Element* elem;
	if (search_type == 1)
		elem = Search(to_delete, true);
	else
		elem = SearchBack(to_delete, true);
	std::cout << "\n####################################################################\n\n";
	if (elem == nullptr)
		cout << to_delete << " не найден" << endl;
	else
		cout << to_delete << " найден" << endl;
	std::cout << "\n####################################################################\n\n";
}


void Show()
{
	std::cout << "\n####################################################################\n\n";
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else {
		cout <<
			"Показать: " << endl <<
			"  1. в прямом направлении" << endl <<
			"  2. в обратном направлении" << endl;
		std::cout << "\n####################################################################\n\n";
		int show_type = Choice();
		std::cout << "\n####################################################################\n\n";
		system("cls");
		std::cout << "\n####################################################################\n\n";
		if (show_type == 2)
		{
			cout << "Список: ";
			Element* t = list->prev;
			do
			{
				cout << t->inf << " ";
				t = t->prev;
			} while (t != list->prev);
			cout << endl;
		}
		else {
			cout << "Список: ";
			Element* t = list->next;
			do
			{
				cout << t->inf << " ";
				t = t->next;
			} while (t != list->next);
			cout << endl;
		}
	}
	std::cout << "\n####################################################################\n\n";
}


int main()
{
	setlocale(LC_ALL, "Rus");
	list->prev = list;
	list->next = list;

	int menu_point;

	do {
		system("cls");
		std::cout << "\n####################################################################\n\n";
		cout <<
			"1. Показать" << endl <<
			"2. Добавить" << endl <<
			"3. Удалить" << endl <<
			"4. Поиск" << endl <<
			"0. Выход" << endl;
		std::cout << "\n####################################################################\n\n";
		menu_point = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		system("cls");

		switch (menu_point)
		{
		case 0:
			return 0;
		case 1:
			Show();
			break;
		case 2:
			Add();
			break;
		case 3:
			Delete();
			break;
		case 4:
			SearchMenu();
			break;
		default:
			cout << "Ошибка ввода!" << endl;
			std::cout << "\n####################################################################\n\n";
		}

		system("pause");
	} while (menu_point != 0);

	return 0;
}