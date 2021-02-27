/*
ЛАБОРАТОРНАЯ РАБОТА №2
Раздел 1, Тема 2, Номер 5
Структура данных “очередь”(кольцевая, на основе массива, статистическая реализация)
*/

#include <iostream>

using namespace std;
const int ArraySizeConst = 3; //Максимальное число эелементов очереди

//Описание структуры "Очередь", где first - указатель на первый элемент очереди, а last - на последний
struct MyQueue {
	int first, last;
	int ArrayForQueue[ArraySizeConst];
	int count;

	void initEmptyQueue() { //Инициализация пустой очереди
		first = last = 0;
	}

	int EmptyCheck() { //Проверка пустоты очереди: есть ли элементы в очереде
		if (count == 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int FullCheck() { //Проверка заполненности очереди: текущее значение элементов не превысилило максимально допустимое число 
		if (count >= ArraySizeConst) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void AddToQueue(int value) { //Добавление элемента в конец очереди

		if (!FullCheck()) { //Проверка возможности добавления: есть ли в массиве свободные места для записи
			ArrayForQueue[last] = value;
			last++;
			if (last == ArraySizeConst) last = 0; //Проверка вхождения last'а в границы массива
			count++;
		}
		else {
			std::cout << "\n####################################################################\n\n";
			std::cout << "Добавление невозможно, так как очередь переполнена.\n";
		}

	}

	int DeleteFromQueue() { //Удаление элемента из начала очереди

		if (!EmptyCheck()) { //Проверить возможности удаления: есть ли что удалять
			int value = ArrayForQueue[first];
			first++;
			if (first == ArraySizeConst)
				first = 0; //Проверка вхождения first'а в границы массива
			count--;
			return value;
		}
		else {
			std::cout << "Удаление невозмжно, так как очеред пустая.\n";
			return -1;
		}
	}

	void ShowMyQueue() { //Вывод текущего состояния очереди
		if (!EmptyCheck()) {
			std::cout << "\n";
			int current = first;
			int  i = 1;
			do {
				std::cout << i << ") " << ArrayForQueue[current] << "\n";
				current++;
				if (current == ArraySizeConst)
					current = 0; //Проверка current'а: выходит за пределы массива

				i++;
			} while (current != last);
		}
		else {
			std::cout << "пустая.";
		}
	}

} myQueue; //Объявление объекта типа MyQueue

//Метод обработки ошибок ввода команды (проверку пройдут только цифры)
int ConsoleReadLine() {
	int a;
	while (!(cin >> a) || (cin.peek() != '\n'))
	{
		cin.clear(); //очищает флаг ошибки cin (так что будущие операции ввода-вывода будут работать правильно)
		while (cin.get() != '\n');
		std::cout << "\n####################################################################\n";
		std::cout << "\nВведено ошибочное значение. Необходимо повторить ввод.\n";
		std::cout << "\nВведите номер команды: ";
	}
	return a;
}

//Диалоговой цикл с пользователем
void ShowMenu() {
	int number, value;
	while (true) {
		std::cout << "\n####################################################################\n";
		std::cout << "\nПрограмма способна выполнять следующие команды:\n";
		std::cout << "1. Выполнить проверку пустоты очереди.\n";
		std::cout << "2. Выполнить проверку заполненности очереди.\n";
		std::cout << "3. Добавить элемент в конец очереди.\n";
		std::cout << "4. Удалить элемент из начала очереди.\n";
		std::cout << "5. Вывести текущее состояние очереди.\n";
		std::cout << "0. Прекратить работу.\n\n";
		std::cout << "Введите номер команды: ";
		number = ConsoleReadLine();
		std::cout << "\n####################################################################\n\n";

		if (number == 1) { //Выполнить проверку пустоты очереди
			if (myQueue.EmptyCheck() == 1) {
				std::cout << "Состояние очереди: пустая.\n";
			}
			else {
				std::cout << "Состояние очереди: не пустая.\n";
			}
		}
		else if (number == 2) { //Выполнить проверку заполненности очереди
			if (myQueue.FullCheck() == 1) {
				std::cout << "Состояние очереди: полная.\n";
			}
			else {
				std::cout << "Состояние очереди: не полная.\n";
			}
		}
		else if (number == 3) { //Добавить элемент в конец очереди

			if (myQueue.FullCheck() == 0) {
				std::cout << "Введите целое число: ";
				value = ConsoleReadLine();
				myQueue.AddToQueue(value);
				std::cout << "\n####################################################################\n\n";
				std::cout << "Число добавлено в очередь.\n";
			}
			else {
				std::cout << "Добавление невозможно, так как очередь переполнена.\n";
			}

		}
		else if (number == 4) { //Удалить элемент из начала очереди

			value = myQueue.DeleteFromQueue();
			if (value != -1) {
				std::cout << "Элемент '" << value << "' был удален.\n";
			}

		}
		else if (number == 5) { //Вывести текущее состояние очереди
			std::cout << "Состояние очереди: ";
			myQueue.ShowMyQueue();
		}

		else if (number == 0) //Прекратить работу
			break;
		else {
			std::cout << "Возникла ошибка. Команды с таким номером не существует.\nНеобходимо повторить ввод.\n";
		}

	}
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	myQueue.initEmptyQueue(); //Инициализация пустой очереди
	ShowMenu(); //Вызов диалогового цикла с пользователем
	return 0;
}