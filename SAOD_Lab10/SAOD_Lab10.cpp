/*
ЛАБОРАТОРНАЯ РАБОТА №10
Раздел 1, Тема 5, Номер 2
Структура данных "дерево"(идеально сбалансированное двоичное дерево, 
нерекурсивный симметричный обход (вспомогательный стек - для хранения последовательности
пройденных вершин от корня до текущей вершины и уровня этих вершин в дереве))
*/

#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;


struct Node
{
	Node* left = nullptr;
	Node* right = nullptr;
	int value = -1;
};


struct Tstack
{
	Node* n = nullptr;
	Tstack* next = nullptr;
	int level = -1;
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


void Add(Tstack** sp, Tstack* elem)
{
	if (*sp == nullptr)
		*sp = elem;
	else
	{
		elem->next = *sp;
		*sp = elem;
	}
}


Tstack* Delete(Tstack** sp)
{
	if (*sp != nullptr)
	{
		Tstack* to_delete = *sp;
		*sp = (*sp)->next;
		to_delete->next = nullptr;
		return to_delete;
	}
	return nullptr;
}

void CreateNode(Node* tree, int count)
{

	count--;
	tree->value = 1 + rand() % 99;
	if (count / 2 + count % 2 > 0)
	{
		tree->left = new Node;
		CreateNode(tree->left, count / 2 + count % 2);
	}
	if (count / 2 > 0)
	{
		tree->right = new Node;
		CreateNode(tree->right, count / 2);
	}
}


void Straight(Node* tree, int level = 0)
{
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(2) << tree->value << endl;
	if (tree->left != nullptr)
		Straight(tree->left, level + 1);
	if (tree->right != nullptr)
		Straight(tree->right, level + 1);
}


void Symmetric(Node* tree, int level = 0)
{
	if (tree->left != nullptr)
		Symmetric(tree->left, level + 1);
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(2) << tree->value << endl;
	if (tree->right != nullptr)
		Symmetric(tree->right, level + 1);
}


void SymmetricBack(Node* tree, int level = 0)
{
	if (tree->right != nullptr)
		SymmetricBack(tree->right, level + 1);
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(2) << tree->value << endl;
	if (tree->left != nullptr)
		SymmetricBack(tree->left, level + 1);
}


void SymmetricNoRecursive(Node* tree)
{
	Tstack* stack = nullptr;
	Tstack* t_s;

	Node* t = tree;
	int level = 0;

	while (true) {
		while (t != nullptr)
		{
			t_s = new Tstack;
			t_s->level = level++;
			t_s->n = t;
			Add(&stack, t_s);
			t = t->left;
		}

		t_s = Delete(&stack);

		if (t_s == nullptr)
			break;
		else {
			level = t_s->level + 1;
			t = t_s->n;

			for (int i = 0; i < level - 1; i++)
				cout << "    ";
			cout << setw(2) << t->value << endl;

			t = t->right;
		}
	}
}


void Delete(Node* tree)
{
	if (tree->left != nullptr)
		Delete(tree->left);
	if (tree->right != nullptr)
		Delete(tree->right);
	delete tree;
}


Node* Create(Node* tree)
{
	srand(time(NULL));
	tree = new Node;

	cout << "Введите количество вершин: ";
	int count = ConsoleReadLine();

	while (count <= 0)
	{
		cout << "Ошибка! Попробуйте снова: ";
		count = ConsoleReadLine();
	}

	CreateNode(tree, count);

	return tree;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	Node* tree = nullptr;

	int Choice;

	do {
		system("cls");

		cout << "\n####################################################################\n\n";
		cout <<
			"1. Создать дерево" << endl <<
			"2. Обход в прямом направлении" << endl <<
			"3. Обход в симметричном направлении" << endl <<
			"4. Обход в обратно-симметричном направлении" << endl <<
			"5. Обход в симметричном направлении (нерекурсивно)" << endl <<
			"0. Выход" << endl;
		cout << "\n####################################################################\n\n";
		Choice = ConsoleReadLine();

		system("cls");

		cout << "\n####################################################################\n\n";
		switch (Choice)
		{
		case 0:
			return 0;
		case 1:
			if (tree != nullptr)
				Delete(tree);
			tree = Create(tree);
			break;
		case 2:
			if (tree != nullptr)
				Straight(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 3:
			if (tree != nullptr)
				Symmetric(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 4:
			if (tree != nullptr)
				SymmetricBack(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 5:
			if (tree != nullptr)
				SymmetricNoRecursive(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		default:
			cout << "Ошибка" << endl;
		}
		cout << "\n####################################################################\n\n";

		system("pause");
	} while (Choice != 0);

	return 0;
}