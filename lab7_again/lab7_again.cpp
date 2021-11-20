#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <stack> 
#include <queue>
using namespace std;

struct node {
	int numb;
	node* next;
};
struct graf {
	node** nodes;
	int size;
};

struct que_node {
	int numb;
	int weight;
	que_node* next;
};
struct quqech {
	que_node* front;
	int size;
};

quqech* create_que() {

	quqech* que = new quqech;
	que->size = NULL;
	que->front = NULL;
	return que;
}
void push(quqech* que, int index, int weight) {
	que_node* newnode = new que_node;
	newnode->numb = index;
	newnode->weight = weight;
	newnode->next = NULL;

	if (que->front == NULL) {
		que->front = newnode;
		que->size++;
		return;
	}
	if (que->front->next == NULL) {
		if (que->front->weight > newnode->weight) {
			newnode->next = que->front;
			que->front = newnode;
		}
		else
			que->front->next = newnode;
		que->size++;
		return;
	}

	que_node* temp_prev = NULL;
	que_node* temp = que->front;


	while (temp && temp->weight < newnode->weight) {
		temp_prev = temp;
		temp = temp->next;
	}

	if (temp == que->front) {
		newnode->next = que->front;
		que->front = newnode;
	}
	else {
		temp_prev->next = newnode;
		newnode->next = temp;
	}

	que->size++;
}
void pop(quqech* que) {
	if (que->size) {
		que_node* temp = que->front;
		que->front = que->front->next;
		que->size--;
		delete(temp);
	}
}

void Google_search(int** a, int num, int* dist, int size) {
	quqech* que = create_que();
	dist[num] = 0;
	push(que,num,0);
	while (que->size) {
		num = que->front->numb;
		printf("%d ", num);
		pop(que);
		for (int i = 0; i < size; i++) {
			if (a[num][i] > 0 && dist[i] > dist[num] + a[num][i]) {
				push(que, i, a[num][i]);
				dist[i] = dist[num] + a[num][i];
			}
		}
	}
}

int main(int argc, char* argv[]) {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int rand_limit;

	if (strcmp(argv[1], "no"))
		rand_limit = 100;
	else
		rand_limit = 2;

	int size;

	cout << "   Введите размерность матрицы: ";
	cin >> size;
	cout << endl;

	int** arr = new int* [size];
	for (int count = 0; count < size; ++count)
		arr[count] = new int[size];

	if (strcmp(argv[2], "no")) {
		for (int row = 0; row < size; row++) {
			arr[row][row] = 0;
			for (int col = row + 1; col < size; col++) {
				arr[row][col] = rand() % rand_limit;
				arr[col][row] = rand() % rand_limit;
			}
		}
	}
	else {
		for (int row = 0; row < size; row++) {
			arr[row][row] = 0;
			for (int col = row + 1; col < size; col++) {
				arr[row][col] = rand() % rand_limit;
				arr[col][row] = arr[row][col];
			}
		}
	}
	cout << "   ";

	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++) {
			cout << arr[row][col] << " ";
		}
		cout << endl << "   ";
	}
	cout << endl;


	auto distG = new int[size];
	for (int i = 0; i < size; i++)
		distG[i] = INT_MAX;
	cout << endl << "      Поиск кратчайшего пути в графе, представленным через матрицу смежности, реализованный на основе алгоритма поиска в ширину с использованием очереди" << endl << endl;
	cout << "   Введите номер вершины, с которой хотите начать обход: ";
	int start;
	cin >> start;
	
	Google_search(arr, start, distG, size);

	cout << endl;
	for (int i = 0; i < size; i++)
		if (distG[i] == -1)
			cout << "   Кратчайший путь до вершины " << i << " = " << 0 << endl;
		else
			cout << "   Кратчайший путь до вершины " << i << " = " << distG[i] << endl;
	return 0;
}