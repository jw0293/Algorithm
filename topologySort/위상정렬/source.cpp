#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define Mod 32000

typedef struct GraphNode {
	int dest;
	int cost;
	struct GraphNode* next;
}GraphNode;

typedef struct graph {
	int count;
	GraphNode* adj;
}Graph;

typedef struct Node {
	int x;
}Node;

int head = 0, tail = 0;
struct Node queue[320003];
int inDegree[32001];

void push(int data) {
	struct Node Temp;
	Temp.x = data;
	queue[tail] = Temp;
	tail = (tail + 1) % Mod;
}

struct Node pop() {
	struct Node Temp = queue[head];
	head = (head + 1) % Mod;
	return Temp;
}

int Is_empty() {
	if (head == tail) return 1;
	else return 0;
}

void Init_Graph(Graph* gph, int count) {
	gph->count = count;
	gph->adj = (GraphNode*)malloc((count + 1) * sizeof(GraphNode));
	for (int i = 1; i <= count; i++) {
		gph->adj[i].next = NULL;
	}
}

int AddLinkedDirectedEdge(Graph* gph, int src, int dst, int cost) {
	GraphNode* Temp = (GraphNode*)malloc(sizeof(GraphNode));
	Temp->dest = dst;	
	Temp->cost = cost;
	Temp->next = gph->adj[src].next;
	gph->adj[src].next = Temp;
	return 1;
}

int AddLinkedUnDirectedEdge(Graph* gph, int src, int dst, int cost) {
	return AddLinkedDirectedEdge(gph, src, dst, cost) && AddLinkedDirectedEdge(gph, dst, src, cost);
}

void topologySort(Graph* gph, int Size_t) {
	int Answer[32002] = { 0, };
	for (int i = 1; i <= Size_t; i++) {
		if (!inDegree[i]) {
			push(i);
		}
	}

	for (int i = 1; i <= Size_t; i++) {
		// 싸이클이 존재한다는 뜻
		if (Is_empty()) break;
		struct Node Tmp = pop();
		Answer[i] = Tmp.x;
		GraphNode* head = gph->adj[Tmp.x].next;
		while (head) {
			--inDegree[head->dest];
			if (inDegree[head->dest] == 0) {
				push(head->dest);
			}
			head = head->next;
		}
	}

	for (int i = 1; i <= Size_t; i++) {
		printf("%d ", Answer[i]);
	}
}

int main() {
	Graph graph;
	int N, M;
	scanf("%d %d", &N, &M);
	Init_Graph(&graph, N);
	for (int i = 0; i < M; i++) {
		int from, to;
		scanf("%d %d", &from, &to);
		AddLinkedDirectedEdge(&graph, from, to, 1);
		inDegree[to]++;
	}
	topologySort(&graph, N);

	return 0;
}