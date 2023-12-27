#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <iostream>


using namespace std;

void BFSD(int v_start, int n, int** G, int* dist) {
	int v;

	using namespace std;
	queue <int> Q;

	Q.push(v_start);
	dist[v_start] = 0;
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();

		for (int i = 1; i <= n; i++) {
			if ((G[v][i] > 0) && (dist[v] + G[v][i] < dist[i])) {
				Q.push(i);
				dist[i] = dist[v] + G[v][i];
			}
		}
	}

	return;
}



void process(int n, int** G, int* dist){
	int v_start;
	printf("\n Введите стартовую вершину -> ");
	scanf("%d", &v_start);

	printf("\n");
	BFSD(v_start, n, G, dist);
	for (int i = 1; i <= n; i++) {						//вывод результата
		if (dist[i] == 1000) printf(" Кратчайшего пути от вершины %d до вершины %d не существует\n", v_start, i);
		else printf(" Кратчайший путь от вершины %d до вершины %d = %d\n", v_start, i, dist[i]);
	}

	int max_dist = 0;
	int diametr = 0;
	int radius = 1000;
	for (int i = 1; i <= n; i++) {
		BFSD(i, n, G, dist);
		max_dist = 0;
		for (int i_4_diam_rad = 1; i_4_diam_rad <= n; i_4_diam_rad++) {
			if (dist[i_4_diam_rad] > max_dist) max_dist = dist[i_4_diam_rad];				//поиск максимального расстояния в массиве	
		}

		if (diametr < max_dist) diametr = max_dist;											//поиск максимального эксцентрисита - диаметра
		if (radius > max_dist) radius = max_dist;											//поиск минимального эксцентрисита - радиуса

		for (int i_4_dist = 1; i_4_dist <= n; i_4_dist++) {									//восстановление массива для след вызова BFSD
			dist[i_4_dist] = 1000;
		}
	}

	printf("\n Диаметр графа, заданного матрицей М1 = %d\n", diametr);
	printf(" Радиус графа, заданного матрицей М1 = %d\n\n", radius);



	for (int i = 1; i <= n; i++) {
		BFSD(i, n, G, dist);

		max_dist = 0;
		for (int i_4_find = 1; i_4_find <= n; i_4_find++) {
			if (dist[i_4_find] > max_dist) max_dist = dist[i_4_find];						//поиск максимального расстояния в массиве - эксцентриситет 
		}

		if (max_dist == diametr) printf(" Вершина %d - периферийная вершина\n", i);
		if (max_dist == radius) printf(" Вершина %d - центральная вершина\n", i);

		for (int i_4_dist = 1; i_4_dist <= n; i_4_dist++) {									//восстановление массива для след вызова BFSD
			dist[i_4_dist] = 1000;
		}
	}


	
	return;
}



int main() {			
	int n;
	int n_orient;

	setlocale(0, "rus");
	printf(" Введите размер матрицы М1 для неориентированного графа -> ");					//неориентированный граф
	scanf("%d", &n);
	printf("\n");

	int** G = (int**)malloc(n * sizeof(int*));
	for (int i = 1; i <= n; i++) {
		G[i] = (int*)malloc(n * sizeof(int));
	}

	int* dist = (int*)malloc(n * sizeof(int*));
	for (int i = 1; i <= n; i++) {
		dist[i] = 1000;
	}

	printf(" Матрица М1 для неориентированного графа:\n");			
	srand(time(0));
	for (int i = 1; i <= n; i++) {						
		for (int j = 1; j <= n; j++) {
			if (j >= i) {
				if (i == j) G[i][j] = 0;
				else {
					G[i][j] = rand() % 10;
					G[j][i] = G[i][j];
				}
			}
			printf(" %d", G[i][j]);
		}
		printf("\n");
	}
	
	process(n, G, dist);

	
	printf("\n\n Введите размер матрицы М2 для ориентированного графа -> ");				//ориентированный граф
	scanf("%d", &n_orient);
	printf("\n");

	int** G_orient = (int**)malloc(n_orient * sizeof(int*));
	for (int i = 1; i <= n_orient; i++) {
		G_orient[i] = (int*)malloc(n_orient * sizeof(int));
	}

	int* dist_orient = (int*)malloc(n_orient * sizeof(int*));
	for (int i = 1; i <= n_orient; i++) {
		dist_orient[i] = 1000;
	}

	printf(" Матрица М2 для ориентированного графа:\n");			
	srand(time(0));
	for (int i = 1; i <= n_orient; i++) {
		for (int j = 1; j <= n_orient; j++) {
			if (i == j) G_orient[i][j] = 0;
			else G_orient[i][j] = rand() % 10;
			printf(" %d", G_orient[i][j]);
		}
		printf("\n");
	}

	process(n_orient, G_orient, dist_orient);
	
	return 0;
}

