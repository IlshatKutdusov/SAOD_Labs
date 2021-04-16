/*
ЛАБОРАТОРНАЯ РАБОТА №8
Раздел 1, Тема 4, Номер 3 
Структура данных "список"(список списков, линейный, динамический, двунаправленный, кольцевой, имеет заголовок (оба списка))
*/

#include <iostream>
#include <locale.h>


using namespace std;


struct SublistElement
{
	int inf;
	SublistElement* next = nullptr;
	SublistElement* prev = nullptr;
};


struct ListElement
{
	int num;
	SublistElement* sublist = nullptr;
	ListElement* next = nullptr;
	ListElement* prev = nullptr;
};


int ConsoleReadLine()
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Ошибка!" << endl;
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


bool isEmptyList(ListElement* list)
{
	return list->prev == list && list->next == list;
}


bool isEmptySublist(SublistElement* list)
{
	return list->prev == list && list->next == list;
}


ListElement* SearchList(ListElement* list, int item)
{
	if (isEmptyList(list))
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		ListElement* t = list->next;
		do
		{
			if (t->num == item)
				return t;
			t = t->next;
		} while (t != list->next);
	}
	return nullptr;
}


SublistElement* SearchSublist(SublistElement* list, int inf)
{
	if (isEmptySublist(list))
	{
		std::cout << "\n####################################################################\n\n";
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		SublistElement* t = list->next;
		do
		{
			if (t->inf == inf)
				return t;
			t = t->next;
		} while (t != list->next);
	}
	return nullptr;
}


void AddToList(ListElement* list)
{
	std::cout << "\n####################################################################\n\n";
	cout << "Введите номер списка для добавления: ";
	int new_item = ConsoleReadLine();
	std::cout << "\n####################################################################\n\n";
	ListElement* new_element = new ListElement;
	new_element->num = new_item;

	SublistElement* new_sublist = new SublistElement;
	new_element->sublist = new_sublist;
	new_sublist->next = new_sublist;
	new_sublist->prev = new_sublist;

	if (isEmptyList(list))
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
		int num = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		ListElement* item_element = SearchList(list, num);
		if (item_element == nullptr)
		{
			cout << num << " не найден";
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

			ListElement* prev = item_element;
			ListElement* next = item_element->next;

			prev->next = new_element;
			next->prev = new_element;

			new_element->next = next;
			new_element->prev = prev;
		}
	}
}


void AddToSublist(ListElement* list)
{
	std::cout << "\n####################################################################\n\n";
	cout << "Введите номер списка: ";
	int num = ConsoleReadLine();
	std::cout << "\n####################################################################\n\n";
	ListElement* _list = SearchList(list, num);
	if (_list == nullptr)
	{
		cout << num << " не найден!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		SublistElement* sublist = _list->sublist;

		cout << "Введите значение для добавления: ";
		int new_item = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		SublistElement* new_element = new SublistElement;
		new_element->inf = new_item;

		if (isEmptySublist(sublist))
		{
			sublist->prev = new_element;
			sublist->next = new_element;
			new_element->next = new_element;
			new_element->prev = new_element;
		}
		else
		{
			cout <<
				"Добавить: " << endl <<
				"  1. До" << endl <<
				"  2. После" << endl;
			std::cout << "\n####################################################################\n\n";
			int add_type = Choice();

			system("cls");

			if (add_type == 1)
				cout << "Добавить до: ";
			else
				cout << "Добавить после: ";
			int id = ConsoleReadLine();
			std::cout << "\n####################################################################\n\n";
			SublistElement* item_element = SearchSublist(sublist, id);
			if (item_element == nullptr)
			{
				cout << id << " не найден!";
				std::cout << "\n####################################################################\n\n";
				delete new_element;
			}
			else
			{
				if (add_type == 1 && sublist->next == item_element)
					sublist->next = new_element;

				if (add_type == 2 && sublist->prev == item_element)
					sublist->prev = new_element;

				if (add_type == 1)
					item_element = item_element->prev;

				SublistElement* prev = item_element;
				SublistElement* next = item_element->next;

				prev->next = new_element;
				next->prev = new_element;

				new_element->next = next;
				new_element->prev = prev;
			}
		}
	}
}


void Show(ListElement* list)
{
	std::cout << "\n####################################################################\n\n";
	if (isEmptyList(list))
		cout << "Список пуст!" << endl;
	else
	{
		ListElement* t = list->next;
		do
		{
			cout << t->num << ": ";

			SublistElement* sublist = t->sublist;

			if (isEmptySublist(sublist))
				cout << "пусто";
			else
			{
				SublistElement* t1 = sublist->next;
				do
				{
					cout << t1->inf << " ";
					t1 = t1->next;
				} while (t1 != sublist->next);
			}
			cout << endl;
			t = t->next;
		} while (t != list->next);
	}
	std::cout << "\n####################################################################\n\n";
}


void DeleteFromList(ListElement* list)
{
	std::cout << "\n####################################################################\n\n";
	if (isEmptyList(list))
	{
		cout << "Список пуст!" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		cout << "Введите номер списка для удаления: ";
		int num = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		ListElement* element_delete = SearchList(list, num);
		if (element_delete == nullptr)
		{
			cout << num << " не найден" << endl;
			std::cout << "\n####################################################################\n\n";
		}
		else 
		{
			SublistElement* sublist = element_delete->sublist;

			if (!isEmptySublist(sublist)) {
				SublistElement* t = sublist->next;
				do
				{
					SublistElement* next = t->next;
					delete t;
					t = next;
				} while (t != sublist->next);
			}

			delete element_delete->sublist;

			if (list->prev == list->next)
			{
				list->prev = list;
				list->next = list;
			}
			else
			{
				ListElement* prev = element_delete->prev;
				ListElement* next = element_delete->next;
				prev->next = next;
				next->prev = prev;

				if (list->next == element_delete)
					list->next = element_delete->next;
				if (list->prev == element_delete)
					list->prev = element_delete->prev;
			}

			delete  element_delete;
		}

		
	}
}


void DeleteFromSublist(ListElement* list)
{
	std::cout << "\n####################################################################\n\n";
	cout << "Введите номер списка: ";
	int num = ConsoleReadLine();
	std::cout << "\n####################################################################\n\n";
	ListElement* _list = SearchList(list, num);
	if (_list == nullptr)
	{
		cout << num << " не найден" << endl;
		std::cout << "\n####################################################################\n\n";
	}
	else
	{
		SublistElement* sublist = _list->sublist;

		if (isEmptySublist(sublist))
		{
			cout << "Вспомогательнвй список пуст!" << endl;
			std::cout << "\n####################################################################\n\n";
		}
		else
		{
			cout << "Введите значение для удаления: ";
			int to_delete = ConsoleReadLine();
			std::cout << "\n####################################################################\n\n";
			SublistElement* element_delete = SearchSublist(sublist, to_delete);
			if (element_delete == nullptr)
				cout << to_delete << " не найден" << endl;

			if (sublist->prev == sublist->next)
			{
				sublist->prev = sublist;
				sublist->next = sublist;
			}
			else
			{
				SublistElement* prev = element_delete->prev;
				SublistElement* next = element_delete->next;
				prev->next = next;
				next->prev = prev;

				if (sublist->next == element_delete)
					sublist->next = element_delete->next;
				if (sublist->prev == element_delete)
					sublist->prev = element_delete->prev;
			}

			delete  element_delete;
		}
	}
}


void FullSearch(ListElement* list)
{
	std::cout << "\n####################################################################\n\n";
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите значение для поиска: ";
		int to_delete = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		ListElement *t = list->next;
		do
		{
			if (SearchSublist(t->sublist, to_delete) != nullptr)
			{
				system("cls");
				cout << to_delete << " найден" << endl;
				std::cout << "\n####################################################################\n\n";
				return;
			}
			t = t->next;
		} while (t != list->next);

		system("cls");
		cout << to_delete << " не найден" << endl;
		std::cout << "\n####################################################################\n\n";
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	ListElement* list = new ListElement;
	list->next = list;
	list->prev = list;

	int choice;

	do {
		system("cls");
		std::cout << "\n####################################################################\n\n";
		cout <<
			"1. Добавить в основной список" << endl <<
			"2. Добавить во вспомогательный список" << endl <<
			"3. Удалить из основного списка" << endl <<
			"4. Удалить из вспомогательного списка " << endl <<
			"5. Поиск" << endl <<
			"6. Показать" << endl <<
			"0. Выход" << endl;
		std::cout << "\n####################################################################\n\n";
		choice = ConsoleReadLine();

		system("cls");

		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			AddToList(list);
			break;
		case 2:
			AddToSublist(list);
			break;
		case 3:
			DeleteFromList(list);
			break;
		case 4:
			DeleteFromSublist(list);
			break;
		case 5:
			FullSearch(list);
			break;
		case 6:
			Show(list);
			break;
		default:
			cout << "Ошибка ввода!" << endl;
			std::cout << "\n####################################################################\n\n";
		}

		system("pause");
	} while (choice != 0);

	return 0;
}