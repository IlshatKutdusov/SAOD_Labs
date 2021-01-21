/*
ЛАБОРАТОРНАЯ РАБОТА №1
Раздел 1, Тема 2, Номер 4
Структуры данных “стек”(на основе динамического расрпделения памяти)

4566585316
Пароль 7JYbgX
*/

#include <iostream>
#include <time.h>

using namespace std;

//Описание стека, где head - указатель вершины главного стека, а head_second - вспомогательного
struct MyStack {
	int value;
	MyStack *next;
} *head, *head_second;

//Создание пустого главного и вспомогательного стеков
inline void initEmptyMyStack() {
	head = NULL;
	head_second = NULL;
}

//Проверка пустоты главного стека
bool EmptyCheck() {
	if (head == NULL) return 1;
	else return 0;
}

//Проверка пустоты вспомогательного стека
bool SecondEmptyCheck() {
	if (head_second == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

//Вывод состояния стека
void ShowMyStack(MyStack *_head) {
	if (_head != NULL) {
		std::cout << "\n";
		MyStack *current;
		current = _head;
		int i = 1;
		do {
			std::cout << "[" << i << "] " << current->value << "\n";
			current = current->next;
			i++;
		} while (current != NULL);
	}
	else {
		std::cout << "пустой.\n";
	}
}

//Добавление в стек
MyStack *AddToStack(MyStack *_head, int _value) {
	//возвращает новую ссылку на head стека
	MyStack *item = new MyStack;
	item->value = _value;
	item->next = _head;
	_head = item;
	return _head;
}

//Метод обработки ошибок ввода команды (проверку пройдут только цифры)
int ConsoleReadLine() {
	int n;
	while (!(cin >> n) || (cin.peek() != '\n'))
	{
		cin.clear(); //очищает флаг ошибки cin (будущие операции ввода-вывода будут работать правильно)
		while (cin.get() != '\n');
		std::cout << "\n####################################################################\n";
		std::cout << "\nВведено ошибочное значение. Необходимо повторить ввод.\n";
		std::cout << "\nВведите номер команды: ";
	}
	return n; //возвращает только число
}

//Добавление рандомного числа элементов в стек
void AddRandomToStack() {
	int RandomCount;
	std::cout << "Введите количесто добавляемых чисел: ";
	RandomCount = ConsoleReadLine();
	for (int i = 0; i < RandomCount; i++)
		head = AddToStack(head, rand());
}

//Удаление из стека
int DeleteFromStack() {
	if (!EmptyCheck()) {
		int value = head->value;
		MyStack *current; current = head;
		head = head->next;
		delete current;
		return value;
	}
	else
		return -1;
}

//Перемещение во вспомогательный стек
void MoveToSecondStack() {
	MyStack *current = head;
	head = head->next;
	current->next = head_second;
	head_second = current;
}

//Добавление из вершины вспомогательного стека
void AddFromSecondStack() {
	MyStack *current = head_second;
	head_second = head_second->next;
	current->next = head;
	head = current;
}

//Диалоговой цикл с пользователем
void ShowMenu() {
	int number, number1, value;
	while (true) {
		std::cout << "\n####################################################################\n";
		std::cout << "\nПрограмма способна выполнять следующие команды:\n";
		std::cout << "1. Вывести состояние главного стека\n";
		std::cout << "2. Вывести состояние вспомогательного стека\n";
		std::cout << "3. Добавить элемент в главный стек\n";
		std::cout << "4. Добавить несколько рандомных чисел в главный стек\n";
		std::cout << "5. Удалить элемент из главного стека\n";
		std::cout << "0. Прекратить работу\n";
		std::cout << "\nВведите номер команды: ";
		number = ConsoleReadLine(); //ввод номера команды
		std::cout << "\n####################################################################\n\n";

		if (number == 1) { //Вывести состояние главного стека
			std::cout << "Состояние главного стека: ";
			ShowMyStack(head);
		}
		else if (number == 2) { //Вывести состояние вспомогательного стека
			std::cout << "Состояние вспомогательного стека: ";
			ShowMyStack(head_second);
		}
		else if (number == 3) { //Добавить элемент в главный стек
			std::cout << "Необходимо выполнить: \n 1. Создание нового элемента \n 2. Выбор его из вершины вспомогательного стека\n\nВведите номер команды: ";
			number1 = ConsoleReadLine();
			if (number1 == 1) {
				std::cout << "\nВведите целое число: ";
				value = ConsoleReadLine();
				head = AddToStack(head, value);
				std::cout << "\n####################################################################\n";
				std::cout << "\nНовый элемент создан и добавлен в главный стек.\n";
			}
			else if (number1 == 2) {
				if (!SecondEmptyCheck()) {
					AddFromSecondStack();
					std::cout << "\n####################################################################\n";
					std::cout << "\nЭлемент перемещен из вспомогательного стека в главный.\n";
				}
				else {
					std::cout << "\n####################################################################\n\n";
					std::cout << "Команда не выполнена, так как вспомогательный стек пустой.\n";
				}
			}
			else {
				std::cout << "\n####################################################################\n\n";
				std::cout << "Возникла ошибка. Команды с таким номером не существует.\nНеобходимо повторить ввод.\n";
			}
		}
		else if (number == 4) { //Добавить несколько рандомных чисел в главный стек
			AddRandomToStack();
			std::cout << "\n####################################################################\n";
			std::cout << "\nРандомные числа добавлены в главный стек.\n";
		}
		else if (number == 5) { //Удалить элемент из главного стека
			if (!EmptyCheck()) {
				std::cout << "Необходимо выполнить: \n 1. Удаление элемента с полным освобождением памяти \n 2. Включение его в вершину вспомогательного стека удаленных элементов\n\nВведите номер команды: ";
				number1 = ConsoleReadLine();
				if (number1 == 1) {
					value = DeleteFromStack();
					if (value != -1) {
						std::cout << "\n####################################################################\n";
						std::cout << "Элемент '" << value << "' был удален.\n";
					}
					else {
						std::cout << "\n####################################################################\n";
						std::cout << "Стек пустой.\n";
					}
				}
				else if (number1 == 2) {
					if (head != NULL) {
						MoveToSecondStack();
					}
					else {
						std::cout << "\n####################################################################\n";
						std::cout << "Стек пустой.\n";
					}
				}
				else {
					std::cout << "\n####################################################################\n\n";
					std::cout << "Возникла ошибка. Команды с таким номером не существует.\nНеобходимо повторить ввод.\n";
				}
			}
			else {
				std::cout << "Стек пустой. Удаление невозможно.\n";
			}
		}
		else if (number == 0) //Прекратить работу
			break;
		else
			std::cout << "Возникла ошибка. Команды с таким номером не существует.\nНеобходимо повторить ввод.\n";
	}
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	initEmptyMyStack(); //Инициализация пустого стека
	srand(1000); //Инициализация генератора случайных чисел rand
	ShowMenu(); //Вызов диалогового цикла с пользователем
	return 0;
}
