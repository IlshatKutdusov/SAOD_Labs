#include <iostream>
#include <locale.h>


using namespace std;


struct sublist_element
{
	int inf;
	sublist_element* next = nullptr;
	sublist_element* prev = nullptr;
};


struct list_element
{
	int num;
	sublist_element* sublist = nullptr;
	list_element* next = nullptr;
	list_element* prev = nullptr;
};


int get_from_cin()
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


bool empty_list(list_element* list)
{
	return list->prev == list && list->next == list;
}


bool empty_sublist(sublist_element* list)
{
	return list->prev == list && list->next == list;
}


list_element* search_list(list_element* list, int item)
{
	if (empty_list(list))
		cout << "Список пуст!" << endl;
	else
	{
		list_element* t = list->next;
		do
		{
			if (t->num == item)
				return t;
			t = t->next;
		} while (t != list->next);
	}
	return nullptr;
}


sublist_element* search_sublist(sublist_element* list, int inf)
{
	if (empty_sublist(list))
		cout << "Список пуст!" << endl;
	else
	{
		sublist_element* t = list->next;
		do
		{
			if (t->inf == inf)
				return t;
			t = t->next;
		} while (t != list->next);
	}
	return nullptr;
}


void add_to_list(list_element* list)
{
	cout << "Введите номер списка для добавления: ";
	int new_item = get_from_cin();

	list_element* new_element = new list_element;
	new_element->num = new_item;

	sublist_element* new_sublist = new sublist_element;
	new_element->sublist = new_sublist;
	new_sublist->next = new_sublist;
	new_sublist->prev = new_sublist;

	if (empty_list(list))
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
		int num = get_from_cin();

		list_element* item_element = search_list(list, num);
		if (item_element == nullptr)
		{
			cout << num << " не найден";
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

			list_element* prev = item_element;
			list_element* next = item_element->next;

			prev->next = new_element;
			next->prev = new_element;

			new_element->next = next;
			new_element->prev = prev;
		}
	}
}


void add_to_sublist(list_element* list)
{
	cout << "Введите номер списка: ";
	int num = get_from_cin();

	list_element* _list = search_list(list, num);
	if (_list == nullptr)
		cout << num << " не найден!" << endl;
	else
	{
		sublist_element* sublist = _list->sublist;

		cout << "Введите значение для добавления: ";
		int new_item = get_from_cin();

		sublist_element* new_element = new sublist_element;
		new_element->inf = new_item;

		if (empty_sublist(sublist))
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
			int add_type = choice();

			system("cls");

			if (add_type == 1)
				cout << "Добавить до: ";
			else
				cout << "Добавить после: ";
			int id = get_from_cin();

			sublist_element* item_element = search_sublist(sublist, id);
			if (item_element == nullptr)
			{
				cout << id << " не найден!";
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

				sublist_element* prev = item_element;
				sublist_element* next = item_element->next;

				prev->next = new_element;
				next->prev = new_element;

				new_element->next = next;
				new_element->prev = prev;
			}
		}
	}
}


void show(list_element* list)
{
	if (empty_list(list))
		cout << "Список пуст!" << endl;
	else
	{
		list_element* t = list->next;
		do
		{
			cout << t->num << ": ";

			sublist_element* sublist = t->sublist;

			if (empty_sublist(sublist))
				cout << "пусто";
			else
			{
				sublist_element* t1 = sublist->next;
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
}


void del_from_list(list_element* list)
{
	if (empty_list(list))
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите номер списка для удаления: ";
		int num = get_from_cin();

		list_element* element_delete = search_list(list, num);
		if (element_delete == nullptr)
			cout << num << " не найден" << endl;

		sublist_element* sublist = element_delete->sublist;

		if (!empty_sublist(sublist)) {
			sublist_element* t = sublist->next;
			do
			{
				sublist_element* next = t->next;
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
			list_element* prev = element_delete->prev;
			list_element* next = element_delete->next;
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


void del_from_sublist(list_element* list)
{
	cout << "Введите номер списка: ";
	int num = get_from_cin();

	list_element* _list = search_list(list, num);
	if (_list == nullptr)
		cout << num << " не найден" << endl;
	else
	{
		sublist_element* sublist = _list->sublist;

		if (empty_sublist(sublist))
			cout << "Вспомогательнвй список пуст!" << endl;
		else
		{
			cout << "Введите значение для удаления: ";
			int to_delete = get_from_cin();

			sublist_element* element_delete = search_sublist(sublist, to_delete);
			if (element_delete == nullptr)
				cout << to_delete << " не найден" << endl;

			if (sublist->prev == sublist->next)
			{
				sublist->prev = sublist;
				sublist->next = sublist;
			}
			else
			{
				sublist_element* prev = element_delete->prev;
				sublist_element* next = element_delete->next;
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


void full_search(list_element* list)
{
	if (list->prev == list && list->next == list)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите значение для поиска: ";
		int to_delete = get_from_cin();

		list_element *t = list->next;
		do
		{
			if (search_sublist(t->sublist, to_delete) != nullptr)
			{
				system("cls");
				cout << to_delete << " найден" << endl;
				return;
			}
			t = t->next;
		} while (t != list->next);

		system("cls");
		cout << to_delete << " не найден" << endl;
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");
	list_element* list = new list_element;
	list->next = list;
	list->prev = list;

	int menu_point;

	do {
		system("cls");

		cout <<
			"1. Добавить в основной список" << endl <<
			"2. Добавить во вспомогательный список" << endl <<
			"3. Удалить из основного списка" << endl <<
			"4. Удалить из вспомогательного списка " << endl <<
			"5. Поиск" << endl <<
			"6. Показать" << endl <<
			"0. Выход" << endl;
		menu_point = get_from_cin();

		system("cls");

		switch (menu_point)
		{
		case 0:
			return 0;
		case 1:
			add_to_list(list);
			break;
		case 2:
			add_to_sublist(list);
			break;
		case 3:
			del_from_list(list);
			break;
		case 4:
			del_from_sublist(list);
			break;
		case 5:
			full_search(list);
			break;
		case 6:
			show(list);
			break;
		default:
			cout << "Ошибка ввода!" << endl;
		}

		system("pause");
	} while (menu_point != 0);

	return 0;
}