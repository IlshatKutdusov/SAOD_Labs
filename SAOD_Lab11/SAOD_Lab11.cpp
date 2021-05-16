/*
ЛАБОРАТОРНАЯ РАБОТА №11
Раздел 1, Тема 5, Номер 3
Структура данных "дерево"(произвольное двоичное дерево)
*/

#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;


struct Node
{
	Node* left = nullptr;
	Node* right = nullptr;
	int inf = -1;
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
			cout << "Ошибка! Попробуйте снова: ";
	} while (result != 1 && result != 2);
	return result;
}

Node* Search(Node* tree, int toSearch)
{
	if (tree->inf == toSearch)
		return tree;

	if (tree->left != nullptr) {
		Node* result = Search(tree->left, toSearch);
		if (result != nullptr)
			return result;
	}

	if (tree->right != nullptr) {
		Node* result = Search(tree->right, toSearch);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

void SearchNode(Node* tree)
{
	cout << "Введите вершину для поиска: ";
	int to_search = ConsoleReadLine();

	Node* result = Search(tree, to_search);
	if (result == nullptr)
		cout << to_search << " не найдено!" << endl;
	else
		cout << to_search << " найдено!" << endl;
}

void Create(Node* tree, int count, Node* mainNode)
{
	count--;
	int r;
	do {
		r = 1 + rand() % 99;
	} while (Search(mainNode, r) != nullptr);
	tree->inf = r;
	if (count / 2 + count % 2 > 0)
	{
		tree->left = new Node;
		Create(tree->left, count / 2 + count % 2, mainNode);
	}
	if (count / 2 > 0)
	{
		tree->right = new Node;
		Create(tree->right, count / 2, mainNode);
	}
}

Node* CreateTree(Node* tree)
{
	srand(time(nullptr));
	tree = new Node;

	cout << "Введите количество вершин: ";
	int node_count = ConsoleReadLine();

	while (node_count <= 0)
	{
		cout << "Ошибка! Попробуйте снова: ";
		node_count = ConsoleReadLine();
	}

	Create(tree, node_count, tree);

	return tree;
}

void AddNode(Node** tree)
{
	Node* t;
	if (*tree == nullptr)
	{
		*tree = new Node;
		t = *tree;
	}
	else
	{
		cout << "Введите вершину для добавления: ";
		int to_search = ConsoleReadLine();

		Node* result = Search(*tree, to_search);
		if (result == nullptr)
		{
			cout << to_search << " не найдено!" << endl;
			return;
		}
		else
		{
			if (result->left == nullptr && result->right == nullptr)
			{
				cout << "Добавить:" << endl <<
					"1. влево" << endl <<
					"2. вправо" << endl;
				int type = Choice();

				if (type == 1)
				{
					result->right = new Node;
					t = result->right;
				}
				else
				{
					result->left = new Node;
					t = result->left;
				}
			}
			else if (result->left != nullptr && result->right == nullptr)
			{
				result->right = new Node;
				t = result->right;
			}
			else if (result->right != nullptr && result->left == nullptr)
			{
				result->left = new Node;
				t = result->left;
			}
			else
			{
				cout << "Добавление невозможно!" << endl;
				return;
			}
		}
	}

	cout << "Введите число, которое нужно добавить: ";
	int r = ConsoleReadLine();
	t->inf = r;
	cout << r << " добавлено!" << endl;
}

void Delete(Node* tree)
{
	if (tree->left != nullptr)
		Delete(tree->left);
	if (tree->right != nullptr)
		Delete(tree->right);
	delete tree;
}

void Stright(Node* tree, int level = 0)
{
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(3) << tree->inf << endl;
	if (tree->left != nullptr)
		Stright(tree->left, level + 1);
	if (tree->right != nullptr)
		Stright(tree->right, level + 1);
}


void Symmetric(Node* tree, int level = 0)
{
	if (tree->left != nullptr)
		Symmetric(tree->left, level + 1);
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(3) << tree->inf << endl;
	if (tree->right != nullptr)
		Symmetric(tree->right, level + 1);
}


void SymmetricBack(Node* tree, int level = 0)
{
	if (tree->right != nullptr)
		SymmetricBack(tree->right, level + 1);
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(3) << tree->inf << endl;
	if (tree->left != nullptr)
		SymmetricBack(tree->left, level + 1);
}


int main()
{
	setlocale(LC_ALL, "Rus");
	Node* tree = nullptr;

	int choice;

	do {
		system("cls");

		cout << "\n####################################################################\n\n";
		cout <<
			"1. Создать дерево" << endl <<
			"2. Добавить вершину" << endl <<
			"3. Найти вершину" << endl <<
			"4. Обход в прямом направлении" << endl <<
			"5. Обход в симметричном направлении" << endl <<
			"6. Обход в обратно-симметричном направлении" << endl <<
			"7. Удалить дерево" << endl <<
			"0. Выход" << endl;
		cout << "\n####################################################################\n\n";
		choice = ConsoleReadLine();

		system("cls");

		cout << "\n####################################################################\n\n";
		switch (choice)
		{
		case 0:
			return 0;
		case 1:
			if (tree != nullptr)
				Delete(tree);
			tree = CreateTree(tree);
			break;
		case 2:
			AddNode(&tree);
			break;
		case 3:
			if (tree != nullptr)
				SearchNode(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 4:
			if (tree != nullptr)
				Stright(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 5:
			if (tree != nullptr)
				Symmetric(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 6:
			if (tree != nullptr)
				SymmetricBack(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 7:
			if (tree != nullptr) {
				Delete(tree);
				tree = nullptr;
				cout << "Дерево успешно удалено!" << endl;
			}
			else
				cout << "Дерево не создано!" << endl;
			break;
		default:
			cout << "Ошибка" << endl;
		}
		cout << "\n####################################################################\n\n";

		system("pause");
	} while (choice != 0);

	return 0;
}