/*
ЛАБОРАТОРНАЯ РАБОТА №3
Раздел 1, Тема 2, Номер 7
Структура данных “очередь”(кольцевая, случайное добавление и удаление элементов, динамическая реализация)
*/

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <locale.h>

using namespace std;

struct QueueElement
{
	char data;
	QueueElement* next = nullptr;
	QueueElement* prev = nullptr;
};


struct Queue
{
	QueueElement* first = nullptr;
	QueueElement* last = nullptr;
};


bool EmptyCheck(Queue* q)
{
	return q->first == nullptr || q->last == nullptr;
}


void Push(Queue* q, char inf)
{
	QueueElement* temp = new QueueElement;
	temp->data = inf;

	if (EmptyCheck(q)) {
		q->first = temp;
		q->last = temp;
	}
	else {
		temp->prev = q->last;
		q->last->next = temp;
		q->last = temp;
	}

}


void Pop(Queue* q)
{

	if (!EmptyCheck(q)) {
		QueueElement* ToDelete = q->first;

		if (q->first == q->last)
		{
			q->first = nullptr;
			q->last = nullptr;
		}
		else
		{
			q->first = q->first->next;
			q->first->prev = nullptr;

		}

		delete ToDelete;
	}
}


void Show(Queue* q)
{
	cout << "Статус: ";
	if (EmptyCheck(q)) {
		cout << "Очередь пуста!" << endl;
		return;
	}

	QueueElement* temp = q->first;

	while (temp)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}


char GetRandomChar()
{
	return rand() % 26 + 65;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	Queue q;

	srand(time(nullptr));
	std::cout << "\n####################################################################\n" << endl;

	char p = 'a';

	while (p != 'q') {
		int r = rand() % 101;

		if (r % 2 == 0) {
			const int count = rand() % 3 + 1;
			std::cout << "\n####################################################################\n\n";
			cout << "Добавлено: " << count << endl;
			for (int i = 0; i < count; i++)
				Push(&q, GetRandomChar());
		}
		else {
			if (EmptyCheck(&q) == false) {
				const int count = rand() % 3 + 1;
				cout << "Удалено: " << count << endl;
				for (int i = 0; i < count; i++)
					Pop(&q);
			}
			else {
				cout << "Удалено: 0" << endl;
			}
		}

		Show(&q);

		std::cout << "\n####################################################################\n";

		p = getchar();
	}

	return 0;
}