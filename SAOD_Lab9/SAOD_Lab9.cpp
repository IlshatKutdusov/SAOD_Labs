/*
ЛАБОРАТОРНАЯ РАБОТА №9
Раздел 1, Тема 5, Номер 1
Структура данных "дерево"(идеально сбалансированное двоичное дерево)
*/

#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;


struct Node
{
	int value = -1;
	Node* left = nullptr;
	Node* right = nullptr;
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
		cout << "Попробуйте заново: ";
		cin >> result;
	}
	return result;
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


void Delete(Node* tree)
{
	if (tree->left != nullptr)
		Delete(tree->left);
	if (tree->right != nullptr)
		Delete(tree->right);
	delete tree;
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


Node* Create(Node* tree)
{
	tree = new Node;

	cout << "Введите количество вершин: ";
	int count = ConsoleReadLine();

	while (count <= 0)
	{
		cout << "Ошибка! Попробуйте заново: ";
		count = ConsoleReadLine();
		cout << "\n####################################################################\n\n";
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
			default:
				cout << "Ошибка ввода!" << endl;
		}
		cout << "\n####################################################################\n\n";

		system("pause");
	} while (Choice != 0);

	return 0;
}