#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<queue>
#include<stdio.h>
#include<algorithm>
#define INF 2147483647

using namespace std;

// 프림 알고리즘을 사용한 최소 스패닝 트리
struct cmp {
	bool operator()(pair<int, int> lhs, pair<int, int> rhs) {
		if (lhs.first == rhs.first)
			return lhs.second > rhs.second;
		else
			return lhs.first > rhs.first;
	}
};
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

int ans[10003] = { INF };
bool visited[10003] = { false };
int V, E;

typedef struct graphNode {
	int dest;
	int cost;
	struct graphNode* next;
}GraphNode;

typedef struct graph {
	int count;
	GraphNode* adj;
}Graph;

void graph_init(Graph* gph, int count) {
	gph->count = count;
	gph->adj = (GraphNode*)malloc((count + 1) * sizeof(GraphNode));
	for (int i = 1; i <= count; i++)
		gph->adj[i].next = NULL;
}

int AddDirectedEdge(Graph* gph, int src, int dst, int cost) {
	GraphNode* temp = (GraphNode*)malloc(sizeof(GraphNode));
	temp->cost = cost;
	temp->dest = dst;
	temp->next = gph->adj[src].next;
	gph->adj[src].next = temp;
	return 1;
}

int AddUnDirectedEdge(Graph* gph, int src, int dst, int cost) {
	return AddDirectedEdge(gph, src, dst, cost) && AddDirectedEdge(gph, dst, src, cost);
}

void PrintGraph(Graph* gph) {
	GraphNode* head;

	for (int i = 1; i <= V; i++) {
		head = gph->adj[i].next;
		printf("Node [ %d ] : ", i);
		while (head) {
			printf(" %d(%d) ", head->dest, head->cost);
			head = head->next;
		}
		cout << '\n';
	}
}

void FindminValue(Graph* gph, int start) {
	GraphNode* head = gph->adj[start].next;
	while (head) {
		if (visited[head->dest]==false && head->cost < ans[head->dest]) {
			ans[head->dest] = head->cost;
			pq.push({ ans[head->dest], head->dest });
		}
		head = head->next;
	}
}

long long result() {
	long long total = 0;
	for (int i = 1; i <= V; i++) {
		total += ans[i];
	}
	return total;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Graph graph;
	cin >> V >> E;
	graph_init(&graph, V);


	for (int i = 0; i < E; i++) {
		int from, to, value;
		cin >> from >> to >> value;
		AddUnDirectedEdge(&graph, from, to, value);
	}
	//PrintGraph(&graph);
	// 아무 시작 지점을 선정, 난 1로 하겠음
	for (int i = 1; i <= V; i++) ans[i] = INF;
	ans[1] = 0;
	pq.push({ ans[1], 1 });

	while (!pq.empty()) {
		int start = pq.top().second;
		pq.pop();
		visited[start] = true;

		FindminValue(&graph, start);
	}
	cout << result() << '\n';

	return 0;
}