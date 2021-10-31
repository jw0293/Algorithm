#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int number = 4;
int INF = 10000000;

// 자료 배열 초기화
int a[4][4] = {
	{0, 5, INF, 8},
	{7,0,9,INF},
	{2, INF, 0,4},
	{INF, INF, 3, 0}
};

void floydWarshall() {
	int ans[4][4];

	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			ans[i][j] = a[i][j];
		}
	}

	for (int k = 0; k < number; k++) {
		for (int i = 0; i < number; i++) {
			for (int j = 0; j < number; j++) {
				if (ans[i][k] + ans[k][j] < ans[i][j]) {
					ans[i][j] = ans[i][k] + ans[k][j];
				}
			}
		}
	}

	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++) {
			printf("%d ", ans[i][j]);
		}
		printf("\n");
	}
}

int main() {
	floydWarshall();

	return 0;
}