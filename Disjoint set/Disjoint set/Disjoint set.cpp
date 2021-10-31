#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 203

using namespace std;

// �θ� ��带 ã�� �Լ�
int getParent(int parent[], int x) {
	if (parent[x] == x) return x;
	return parent[x] = getParent(parent, parent[x]);
}

// �� �θ� ��带 ��ġ�� �Լ�
void unionParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a < b) 
		parent[b] = a;
	else 
		parent[a] = b;
}

// ���� �θ� �������� Ȯ��
int findParent(int parent[], int a, int b) {
	a = getParent(parent, a);
	b = getParent(parent, b);
	if (a == b)
		return 1;
	return 0;
}

int main() {
	int parent[203];
	int N, M, want, possible;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) parent[i] = i;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int link; cin >> link;
			if (link) unionParent(parent, i, j);
		}
	}
	cin >> want;
	possible = getParent(parent, want);
	for (int i = 1; i < M; i++) {
		cin >> want;
		if (possible != getParent(parent, want)) {
			cout << "NO" << '\n';
			return 0;
		}
	}
	cout << "YES" << '\n';

	return 0;
}