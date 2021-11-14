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

//void Johny_Depp(int** a, int* dist, int current_vertex, int size, int path_length) {
//	dist[current_vertex] = path_length;
//	for (int i = 0; i < size; i++) {
//		if (a[current_vertex][i] != 0 && dist[i] > path_length + 1) {
//			Johny_Depp(a, dist, i, size, path_length + 1);
//		}
//	}
//}
//
//void Craigslist(graf* grafon, int* dist, int current_vertex, int size, int path_length) {
//	dist[current_vertex] = path_length;
//	node* temp = grafon->nodes[current_vertex];
//	while (temp != NULL) {
//		if (dist[temp->numb] > path_length + 1) {
//			Craigslist(grafon, dist, temp->numb, size, path_length + 1);
//		}
//		temp = temp->next;
//	}
//}

void Google_search(int** a, int num, int* dist, int size) {
	queue <int> q;
	dist[num] = 0;
	q.push(num);
	while (!q.empty()) {
		num = q.front();
		q.pop();
		for (int i = 0; i < size; i++) {
			if (a[num][i] > 0 && dist[i] > dist[num] + a[num][i]) {
				q.push(i);
				dist[i] = dist[num] + a[num][i];
			}
		}
	}
}

//void Google_search_spis(graf* grafon, int num, int* dist, int size) {
//	queue <int> q;
//	node* buff;
//	dist[num] = 0;
//	q.push(num);
//	while (!q.empty()) {
//		num = q.front();
//		buff = grafon->nodes[num];
//		q.pop();
//		while(buff != NULL ) {
//			if (dist[buff->numb] == -1) {
//				q.push(buff->numb);
//				dist[buff->numb] = dist[num] + 1;
//			}
//			buff = buff->next;
//		}
//	}
//}
//
//graf* sozdat(int versh) {
//
//	graf* grafon = new graf;
//	grafon->size = versh;
//	grafon->nodes = new node * [versh];
//	for (int i = 0; i < versh; i++) {
//		grafon->nodes[i] = NULL;
//	}
//	return grafon;
//}
//node* sozdatnode(int index) {
//	node* newnode = new node;
//	newnode->numb = index;
//	newnode->next = NULL;
//	return newnode;
//}
//void addgran(graf* grafon, int from, int to) {
//	node* newnode = sozdatnode(from);
//	if (grafon->nodes[to] == 0) {
//		grafon->nodes[to] = newnode;
//		newnode = NULL;
//	}
//	node* buf = grafon->nodes[to];
//	while (buf->next != NULL) {
//		buf = buf->next;
//	}
//	buf->next = newnode;
//
//	newnode = sozdatnode(to);
//	if (grafon->nodes[from] == 0) {
//		grafon->nodes[from] = newnode;
//		return;
//	}
//	buf = grafon->nodes[from];
//	while (buf->next != NULL) {
//		buf = buf->next;
//	}
//	buf->next = newnode;
//}

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
	clock_t start_t, end;
	start_t = clock();
	Google_search(arr, start, distG, size);
	end = clock();
	cout << endl;
	for (int i = 0; i < size; i++)
		if (distG[i] == -1)
			cout << "   Кратчайший путь до вершины " << i << " = " << 0 << endl;
		else
			cout << "   Кратчайший путь до вершины " << i << " = " << distG[i] << endl;
	return 0;
}































/*graf* grafon = sozdat(size);
int j = 1;
for (int i = 0; i < size; i++) {
	for (j; j < size; j++) {
		if (arr[i][j] == 1) {
			addgran(grafon, i, j);
		}
	}
	j = j - size + i + 1;
}

cout << "   ";
for (int i = 0; i < size; i++) {
	node* temp = grafon->nodes[i];
	cout << i << " ";

	while (temp) {
		cout << " -> " << temp->numb;
		temp = temp->next;
	}
	cout << endl << "   ";
}*/










//////////////////////////////////////////////////////////////////
	//cout << "      Поиск кратчайшего пути в графе, представленным через список смежности, реализованный на основе алгоритма поиска в ширину с использованием очереди" << endl << endl;
	//for (int i = 0; i < size; i++)
	//	distG[i] = -1;

	//Google_search_spis(grafon, start, distG, size);
	//for (int i = 0; i < size; i++)
	//	if(distG[i]== -1)
	//		cout << "   Кратчайший путь до вершины " << i << " = " << 0 << endl;
	//	else
	//	cout << "   Кратчайший путь до вершины " << i << " = " << distG[i] << endl;

/////////////////////////////////////////////////////////////
	//	cout << endl << "      Поиск кратчайшего пути, реализованный на основе алгоритма поиска в глубину с использованием рекурсии" << endl;

	//	int* dist = new int[size];
	//	for (int count = 0; count < size; ++count)
	//		dist[count] = INT_MAX;
	//	
	//	start_t = clock();
	//	Johny_Depp(arr, dist, start, size, 0);
	//	end = clock();
	//	
	//	for (int count = 0; count < size; ++count) {
	//		if (dist[count] == INT_MAX)
	//			dist[count] = 0;
	//		cout << endl << "   Кратчайший путь до вершины " << count << " = "<< dist[count];
	//	}
	//cout << endl << endl << "   Время выполнения алгоритма составляет " << (double)difftime(end, start_t) / CLOCKS_PER_SEC << endl;

/////////////////////////////////////////////////////////////

		/*int* versh = new int[size];
		for (int count = 0; count < size; ++count)
			versh[count] = 0;

		cout << endl << "      Поиск кратчайшего пути в графе, представленным через список, реализованный на основе алгоритма поиска в глубину с использованием рекурсии" << endl;

		for (int count = 0; count < size; ++count)
			dist[count] = INT_MAX;

		Craigslist(grafon, dist, start, size, 0);

		for (int count = 0; count < size; ++count) {
			if (dist[count] == INT_MAX)
				dist[count] = 0;
			cout << endl << "   Кратчайший путь до вершины " << count << " = " << dist[count];
		}*/































/*int deep(int** a, int* versh, int current_vertex, int destination_vertex, int size, int path_length, int shortest_path) {
	path_order.push(current_vertex);

	versh[current_vertex] = 1;
	for (int i = 0; i < size; i++) {
		if (path_length > shortest_path)
			break;
		if (a[current_vertex][i] != 0 && versh[i] != 1) {
			if (i == destination_vertex) {
				if (shortest_path > path_length+1)
					shortest_path = path_length+1;
				break;
			}
			if (path_length+1 >= shortest_path)
				break;
			shortest_path = deep(a, versh ,i,destination_vertex, size, path_length+1, shortest_path);
		}
	}

	while (path_order.top() != current_vertex) {
		versh[path_order.top()] = 0;
		path_order.pop();
	}

	return shortest_path;
}



shortest_path = deep(arr, versh, num, destination_vertex, size, 0, INT_MAX);
		cout << endl << shortest_path;*/

		///////////////////////////////////////////////////////////////
		//void norec(int** a, int* dist, int current_vertex, int size) {
		//	stack <int> steck;
		//	int path_length = 0, i;
		//	steck.push(current_vertex);
		//	dist[current_vertex] = 0;
		//	do {
		//		for (i = 0; i < size; i++) {
		//			if (a[current_vertex][i] != 0 && dist[i] > path_length + 1) {
		//				dist[i] = path_length + 1;
		//				steck.push(current_vertex);
		//				current_vertex = i;
		//				path_length++;
		//				break;
		//			}
		//		}
		//
		//		if (i == size) {
		//			path_length--;
		//			current_vertex = steck.top();
		//			steck.pop();
		//		}
		//	} while (!steck.empty());
		//}
					/*	int num, destination_vertex, shortest_path;
						int* dist = new int[size];
						for (int count = 0; count < size; ++count)
							dist[count] = INT_MAX;
						cout << "   Введите номер вершины, с которой хотите начать обход: ";													//
						cin >> num;																												// norec рабочий
						cout << endl;																											//
						norec(arr,dist,num, size);
						for (int count = 0; count < size; ++count) {
							if (dist[count] == INT_MAX)
								dist[count] = 0;
							cout << endl << "Кратчайший путь до вершины  " << count << " = " << dist[count];
						}*/
						///////////////////////////////////////////////////////////////


						//int num, destination_vertex, shortest_path;


						//int deepDarkAss(graf* grafon, int current_vertex, int destination_vertex, int path_length, int shortest_path, int* versh) {
						//	node* buf = grafon->nodes[current_vertex];
						//	versh[current_vertex] = 1;
						//
						//	while (buf != NULL) {
						//		if (versh[buf->numb] == 0) {
						//			if (buf->numb == destination_vertex) {
						//				if (shortest_path > path_length + 1)
						//					shortest_path = path_length + 1;
						//				break;
						//			}
						//			int* versh_next = new int[grafon->size];
						//			for (int count = 0; count < grafon->size; ++count)
						//				versh_next[count] = versh[count];
						//			deepDarkAss(grafon, buf->numb, destination_vertex, path_length + 1, shortest_path, versh_next);
						//		}
						//		buf = buf->next;
						//	}
						//	return shortest_path;
						//}

						//void norec(int** a, int current_vertex, int destination_vertex, int shortest_path, int* versh, int size) {
						//	stack <int> steck;
						//	stack <int> path_order;
						//	steck.push(current_vertex);
						//	int i = 0;
						//	int path_length = 0;
						//	while (!steck.empty()) {
						//		current_vertex = steck.top();
						//		versh[current_vertex] = 1;
						//		path_order.push(current_vertex);
						//		path_length++;
						//		for (int i = 0; i < size; i++) {
						//			if (a[current_vertex][i] != 0 && versh[i] != 1) {
						//				if (a[current_vertex][i] != 0 && versh[i] != 1) {
						//					if (i == destination_vertex)
						//						if (shortest_path > path_length+1)
						//							shortest_path = path_length+1;
						//					else
						//						steck.push(i);
						//				}
						//			}
						//		}
						//		if (current_vertex == steck.top()) {
						//			steck.pop();
						//			while (steck.top() != path_order.top()) {
						//				versh[path_order.top()] = 0;
						//				path_order.pop();
						//				path_length--;
						//			}
						//		}
						//	}
						//}

						/*

						switch(strcmp("no"))

						*/