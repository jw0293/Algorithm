#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
// ��������Ʈ�� ��Ÿ���� �׷��� 
typedef struct graphNode {
	int cost;
	int dest;
	struct graphNode* next;
}GraphNode;

typedef struct graph {
	int size;
	GraphNode* adj;
}Graph;

void Init_Graph(Graph* gph, int size) {
	gph->size = size;
	gph->adj = (GraphNode*)malloc(size * sizeof(GraphNode));
	
	for (int i = 0; i < size; i++) {
		gph->adj[i].next = NULL;
	}
}

// ���⼺�� ������ ����ġ�� �ξ���� ��
int addDirectedEdge(Graph* gph, int src, int dst, int cost) {
	GraphNode* temp = (GraphNode*)malloc(sizeof(GraphNode));
	if (!temp) {
		printf("Memory Allocation Error!");
		return 0;
	}

	temp->cost = cost;
	temp->dest = dst;
	temp->next = gph->adj[src].next;
	gph->adj[src].next = temp;
	return 1;
}

// ���⼺ ���� ����ġ�� �ξ���� ��
// �� �������� ��� ������ �������־�� �ϱ� ������ ���� �ٲ� 2���� ���ش�
int addUndirectedEdge(Graph* gph, int src, int dst, int cost) {
	return addDirectedEdge(gph, src, dst, cost) && addDirectedEdge(gph, dst, src, cost);
}

void PrintGraph(Graph* gph) {
	GraphNode* head;
	if (!gph) {
		puts("Not Exist In Graph!");
		return;
	}
	printf("Graph Size >>> : %d\n", gph->size);
	for (int i = 0; i < gph->size; i++) {
		head = gph->adj[i].next;
		printf(" ��� [ %d ] :", i);
		while (head) {
			printf("  %d(%d)  ", head->dest, head->cost);
			head = head->next;
		}
		printf("\n");
	}
}

int main() {
	Graph graph;
	Init_Graph(&graph, 4);
	addDirectedEdge(&graph, 0, 1, 1);
	addDirectedEdge(&graph, 0, 2, 1);
	addDirectedEdge(&graph, 1, 2, 1);
	addDirectedEdge(&graph, 2, 3, 1);
	addDirectedEdge(&graph, 3, 2, 4);
	PrintGraph(&graph);

	return 0;
}