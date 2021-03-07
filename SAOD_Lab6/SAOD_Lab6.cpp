/*
ЛАБОРАТОРНАЯ РАБОТА №6
Раздел 1, Тема 3, Номер 5
Структура данных "список"(линейный, динамический, удаление - перемеение из основного списка во вспомогательный,
работа с ним по стековому принципу)
*/

#include <iostream>
#include <locale.h>

using namespace std;


struct Element
{
	int inf;
	Element* next = nullptr;
};


Element* list = new Element;
Element* additional = new Element;


int ConsoleReadLine()
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


Element* Search(int data)
{
	for (Element* t = list; t != nullptr; t = t->next)
		if (t->next != nullptr && t->next->inf == data)
			return t;
	return nullptr;
}


void Show()
{
	std::cout << "\n####################################################################\n\n";
	if (list->next == nullptr)
		cout << "Основной список пуст!" << endl;
	else
	{
		cout << "Основной список: ";
		for (Element*t = list->next; t != nullptr; t = t->next)
			cout << t->inf << " ";
		cout << endl;
	}
	std::cout << "\n####################################################################\n\n";
}


void ShowAdditional()
{
	std::cout << "\n####################################################################\n\n";
	if (additional->next == nullptr)
		cout << "Дополнительный список пуст!" << endl;
	else
	{
		cout << "Дополнительный список: ";
		for (Element*t = additional->next; t != nullptr; t = t->next)
			cout << t->inf << " ";
		cout << endl;
	}
	std::cout << "\n####################################################################\n\n";
}


void Add()
{
	std::cout << "\n####################################################################\n\n";
	cout << "Введите число для добавления: ";
	int new_inf = ConsoleReadLine();
	std::cout << "\n####################################################################\n\n";
	Element* new_element = new Element;
	new_element->inf = new_inf;

	if (list->next == nullptr)
		list->next = new_element;
	else
	{
		int add_type;
		std::cout << "\n####################################################################\n\n";
		cout <<
			"Добавить: " << endl <<
			"  1. до" << endl <<
			"  2. после" << endl;
		do {
			std::cout << "\n####################################################################\n\n";
			add_type = ConsoleReadLine();
			std::cout << "\n####################################################################\n\n";
			if (add_type != 1 && add_type != 2)
				cout << "Ошибка ввода! Попробуйте снова: ";
		} while (add_type != 1 && add_type != 2);

		std::cout << "\n####################################################################\n\n";
		if (add_type == 1)
			cout << "Добавить до: ";
		else
			cout << "Добавить после: ";
		int data = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		Element* item_element = Search(data);
		if (item_element == nullptr)
		{
			cout << data << " элемент не найден!";
			std::cout << "\n\n####################################################################\n\n";
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


void PushAdditional(Element* n)
{
	n->next = additional->next;
	additional->next = n;
}


void Delete()
{
	std::cout << "\n####################################################################\n\n";
	if (list->next == nullptr)
		cout << "Список пуст!" << endl;
	else
	{
		cout << "Введите число для удаления: ";
		int to_delete = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";
		Element* index = Search(to_delete);
		if (index == nullptr)
			cout << to_delete << " элемент не найден!" << endl;
		else
		{
			Element* t = index->next;
			index->next = t->next;
			PushAdditional(t);
		}
	}
	std::cout << "\n####################################################################\n\n";
}


int main()
{
	setlocale(LC_ALL, "Rus");
	int choice;

	do {
		system("cls");
		std::cout << "\n####################################################################\n\n";
		cout <<
			"1. Показать основной список" << endl <<
			"2. Показать дополнительный список" << endl <<
			"3. Добавить" << endl <<
			"4. Удалить" << endl <<
			"0. Выход" << endl;
		std::cout << "\n####################################################################\n\n";
		choice = ConsoleReadLine();

		system("cls");

		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			Show();
			break;
		case 2:
			ShowAdditional();
			break;
		case 3:
			Add();
			break;
		case 4:
			Delete();
			break;
		default:
			cout << "Ошибка ввода!" << endl;
			std::cout << "\n####################################################################\n\n";
		}

		system("pause");
	} while (choice != 0);

	return 0;
}