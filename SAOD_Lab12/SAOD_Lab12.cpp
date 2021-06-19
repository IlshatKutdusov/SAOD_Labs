/*
ЛАБОРАТОРНАЯ РАБОТА №12
Раздел 1, Тема 6, Номер 1
Структура данных "дерево"(двоичное дерево поиска)
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;


char HeadUp = 35; // #
char HeadDown = 35; // #
char HeadHorizontal = 45; // ─ 
char HeadVertical = 124; // │


struct Node
{
	Node* left = nullptr;
	Node* right = nullptr;
	int inf = -1;
	int count = 1;
};


int ConsoleReadLine()
{
	int result;
	cin >> result;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Ошибка ввода!" << endl;
		system("pause");
		cout << "Попробуйте еще раз: ";
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
			cout << "Ошибка ввода! Попробуйте еще раз: ";
	} while (result != 1 && result != 2);
	return result;
}


void Stright(Node* tree)
{
	if (tree->left != nullptr)
		Stright(tree->left);
	cout << tree->inf << "(" << tree->count << ") ";
	if (tree->right != nullptr)
		Stright(tree->right);
}


void Back(Node* tree, int deep = 0, int paints[3][100] = nullptr)
{
	int t_paints[3][100];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 100; j++)
		{
			if (paints == nullptr)
				t_paints[i][j] = 0;
			else
				t_paints[i][j] = paints[i][j];
		}
	}

	for (int i = 0; i < deep - 1; i++)
		t_paints[0][i] = 0;

	int last_t_paint = -1;

	if (deep > 0) {
		last_t_paint = t_paints[2][deep - 1];
		t_paints[2][deep - 1] = 0;
	}

	if (tree->right != nullptr) {
		t_paints[0][deep] = 1;
		t_paints[2][deep] = 1;
		Back(tree->right, deep + 1, t_paints);
		t_paints[2][deep] = 0;
	}

	if (deep > 0) {
		t_paints[1][deep - 1] = 0;
		t_paints[2][deep - 1] = last_t_paint;
	}

	for (int i = 0; i < deep; i++) {
		if (t_paints[0][i] == 0) {
			if (t_paints[1][i] == 1 || t_paints[2][i] == 1)
				cout << HeadVertical << "  ";
			else
				cout << "   ";
		}
		else if (t_paints[0][i] == 1) {
			cout << HeadUp;
			if (i != deep - 1)
				cout << "  ";
			else
				cout << HeadHorizontal << HeadHorizontal;
		}
		else if (t_paints[0][i] == -1) {
			cout << HeadDown;
			if (i != deep - 1)
				cout << "  ";
			else
				cout << HeadHorizontal << HeadHorizontal;
		}
		else if (t_paints[0][i] == 2)
			cout << HeadVertical << "  ";
	}
	cout << setw(2) << std::left << tree->inf << endl;

	if (tree->left != nullptr) {
		t_paints[0][deep] = -1;
		t_paints[1][deep] = 1;
		Back(tree->left, deep + 1, t_paints);
	}
}


Node* Search(Node* tree, int to_search)
{
	if (tree->inf == to_search)
		return tree;
	else if (to_search < tree->inf)
	{
		if (tree->left == nullptr)
			return nullptr;
		else
			return Search(tree->left, to_search);
	}
	else
	{
		if (tree->right == nullptr)
			return nullptr;
		else
			return Search(tree->right, to_search);
	}
}


void SearchNode(Node* tree)
{
	cout << "Введите ключ вершины для поиска: ";
	int to_search = ConsoleReadLine();

	Node* result = Search(tree, to_search);
	if (result == nullptr)
		cout << to_search << " не найдено!" << endl;
	else
		cout << to_search << " найдено! Количество: " << result->count << "!" << endl;
}


void AddRecursive(Node* tree, int key)
{
	if (tree->inf == key)
		tree->count++;
	else if (tree->inf > key)
	{
		if (tree->left == nullptr) {
			tree->left = new Node;
			tree->left->inf = key;
		}
		else
			AddRecursive(tree->left, key);
	}
	else
	{
		if (tree->right == nullptr)
		{
			tree->right = new Node;
			tree->right->inf = key;
		}
		else
			AddRecursive(tree->right, key);
	}
}



void AddNoRecursive(Node* tree, int key)
{
	Node* t = tree;

	while (true)
	{
		if (t->inf == key) {
			t->count++;
			return;
		}
		else if (t->inf > key)
		{
			if (t->left == nullptr) {
				t->left = new Node;
				t->left->inf = key;
				return;
			}
			else
				t = t->left;
		}
		else
		{
			if (t->right == nullptr)
			{
				t->right = new Node;
				t->right->inf = key;
				return;
			}
			else
				t = t->right;
		}
	}
}


Node* Create(Node* tree)
{
	srand(time(nullptr));
	tree = new Node;
	tree->inf = 1 + rand() % 99;


	cout << "Введите количество вершин: ";
	int node_count = ConsoleReadLine();

	while (node_count <= 0)
	{
		cout << "Ошибка! Попробуйте снова: ";
		node_count = ConsoleReadLine();
	}

	for (node_count--; node_count > 0; node_count--)
	{
		int r;
		do {
			r = 1 + rand() % 99;
		} while (Search(tree, r) != nullptr);
		AddRecursive(tree, r);
	}

	return tree;
}


void Delete(Node* tree)
{
	if (tree->left != nullptr)
		Delete(tree->left);
	if (tree->right != nullptr)
		Delete(tree->right);
	delete tree;
}


void AddNode(Node** tree)
{
	cout << "Введите ключ: ";
	int key = ConsoleReadLine();

	if (*tree == nullptr) {
		*tree = new Node;
		(*tree)->inf = key;
	}
	else
	{
		cout << "Добавить " << endl <<
			"1. рекурсивный метод" << endl <<
			"2. нерекурсивный метод" << endl;
		int t = Choice();

		if (t == 1)
			AddRecursive(*tree, key);
		else
			AddNoRecursive(*tree, key);
	}
}


void Delete(Node* tree, int to_delete)
{
	Node* t = tree;
	Node* t_from = nullptr;

	while (t->inf != to_delete)
	{
		t_from = t;
		if (to_delete < t->inf)
			t = t->left;
		else
			t = t->right;
	}

	if (t->left == nullptr && t->right == nullptr)
	{
		if (t_from->left == t)
			t_from->left = nullptr;
		else
			t_from->right = nullptr;
		delete t;
	}
	else if (t->left == nullptr && t->right != nullptr) {
		if (t_from->left == t)
			t_from->left = t->right;
		else
			t_from->right = t->right;
		delete t;
	}
	else if (t->right == nullptr && t->left != nullptr)
	{
		if (t_from->left == t)
			t_from->left = t->left;
		else
			t_from->right = t->left;
		delete t;
	}
	else if (t->right != nullptr && t->left != nullptr)
	{
		Node* tt = t->right;
		Node* tt_from = tt;
		while (tt->left != nullptr)
		{
			tt_from = tt;
			tt = tt->left;
		}

		t->inf = tt->inf;
		if (tt == t->right)
			t->right = tt->right;
		else
			tt_from->left = tt->right;
		delete tt;
	}
}


void DeleteNode(Node* tree)
{
	cout << "Введите ключ вершины: ";
	int key = ConsoleReadLine();

	Node* res = Search(tree, key);

	if (res == nullptr)
		cout << key << " не найдено!" << endl;
	else {
		Delete(tree, key);
	}
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
			"3. Поиск вершины" << endl <<
			"4. Удалить вершину" << endl <<
			"5. Показать дерево" << endl <<
			"6. Вывести все вершины в одну строку по порядку" << endl <<
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
			tree = Create(tree);
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
			if (tree != nullptr) {
				DeleteNode(tree);
				cout << endl;
			}
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 5:
			if (tree != nullptr)
				Back(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 6:
			if (tree != nullptr) {
				Stright(tree);
				cout << endl;
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

