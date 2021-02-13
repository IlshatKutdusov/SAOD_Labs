#include <iostream>
#include <iomanip>
#include <locale.h>

using namespace std;


struct node
{
	node* left = nullptr;
	node* right = nullptr;
	int inf = -1;
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
		cout << "Попробуйте заново: ";
		cin >> result;
	}
	return result;
}


void create(node* tree, int count)
{
	count--;
	tree->inf = 1 + rand() % 99;
	if (count / 2 + count % 2 > 0)
	{
		tree->left = new node;
		create(tree->left, count / 2 + count % 2);
	}
	if (count / 2 > 0)
	{
		tree->right = new node;
		create(tree->right, count / 2);
	}
}


void forward(node* tree, int level = 0) //обход в прямом направлении
{
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(2) << tree->inf << endl;
	if (tree->left != nullptr)
		forward(tree->left, level + 1);
	if (tree->right != nullptr)
		forward(tree->right, level + 1);
}


void symmetric(node* tree, int level = 0) //симметричный обход
{
	if (tree->left != nullptr)
		symmetric(tree->left, level + 1);
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(2) << tree->inf << endl;
	if (tree->right != nullptr)
		symmetric(tree->right, level + 1);
}


void back_symmetric(node* tree, int level = 0) //обратно-симметричный обход
{
	if (tree->right != nullptr)
		back_symmetric(tree->right, level + 1);
	for (int i = 0; i < level; i++)
		cout << "    ";
	cout << setw(2) << tree->inf << endl;
	if (tree->left != nullptr)
		back_symmetric(tree->left, level + 1);
}


void del(node* tree)
{
	if (tree->left != nullptr)
		del(tree->left);
	if (tree->right != nullptr)
		del(tree->right);
	delete tree;
}


node* make(node* tree)
{
	tree = new node;

	cout << "Введите количество вершин: ";
	int count = get_from_cin();

	while (count <= 0)
	{
		cout << "Ошибка! Попробуйте заново: ";
		count = get_from_cin();
	}

	create(tree, count);

	return tree;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	node* tree = nullptr;

	int menu_point;

	do {
		system("cls");

		cout <<
			"1. Создать дерево" << endl <<
			"2. Обход в прямом направлении" << endl <<
			"3. Обход в симметричном направлении" << endl <<
			"4. Обход в обратно-симметричном направлении" << endl <<
			"0. Выход" << endl;
		menu_point = get_from_cin();

		system("cls");

		switch (menu_point)
		{
		case 0:
			return 0;
		case 1:
			if (tree != nullptr)
				del(tree);
			tree = make(tree);
			break;
		case 2:
			if (tree != nullptr)
				forward(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 3:
			if (tree != nullptr)
				symmetric(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		case 4:
			if (tree != nullptr)
				back_symmetric(tree);
			else
				cout << "Дерево не создано!" << endl;
			break;
		default:
			cout << "Ошибка ввода!" << endl;
		}

		system("pause");
	} while (menu_point != 0);

	return 0;
}