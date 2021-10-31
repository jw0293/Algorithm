#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<queue>
#include<stdio.h>
#include<algorithm>
#define INF 98765432

using namespace std;

// 다익스트라 알고리즘
int V, E, start;
bool visited[20003];
int ans[20003] = { INF };

struct cmp {
	bool operator()(pair<int, int> lhs, pair<int, int> rhs) {
		if (lhs.first == rhs.first)
			return lhs.second > rhs.second;
		else
			return lhs.first > rhs.first;
	}
};

priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
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
	for (int i = 1; i <= count; i++) {
		gph->adj[i].next = NULL;
	}
}

int addDirectedEdge(Graph* gph, int src, int dst, int cost) {
	GraphNode* temp = (GraphNode*)malloc(sizeof(GraphNode));
	temp->cost = cost;
	temp->dest = dst;
	temp->next = gph->adj[src].next;
	gph->adj[src].next = temp;
	return 1;
}

int addUnDirectedEdge(Graph* gph, int src, int dst, int cost) {
	return addDirectedEdge(gph, src, dst, cost) && addDirectedEdge(gph, dst, src, cost);
}

void printGraph(Graph* gph) {
	GraphNode* head;
	printf("Graph count count : %d\n", gph->count);

	for (int i = 1; i <= gph->count; i++) {
		head = gph->adj[i].next;
		printf("Node [ %d ] : ", i);
		while (head) {
			printf(" %d(%d) ", head->dest, head->cost);
			head = head->next;
		}
		printf("\n");
	}
}

void FindminValue(Graph* gph, int start, int prev) {
	GraphNode* head = gph->adj[start].next;
	while (head) {
		if (prev + head->cost < ans[head->dest]) {
			ans[head->dest] = head->cost + prev;
			pq.push({ ans[head->dest], head->dest });
		}
		head = head->next;
	}
}

void Output_result() {
	for (int i = 1; i <= V; i++) {
		if (ans[i] == INF) {
			cout << "INF" << '\n';
			continue;
		}
		cout << ans[i] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	Graph graph;
	cin >> V >> E;
	graph_init(&graph, V);
	cin >> start;
	//최단거리를 최신화하며 저장할 배열 필요

	for (int i = 1; i <= V; i++) {
		if (i == start) {
			ans[i] = 0;
			continue;
		}
		ans[i] = INF;
	}

	for (int i = 0; i < E; i++) {
		int from, to, len;
		cin >> from >> to >> len;
		addDirectedEdge(&graph, from, to, len);
	}
	//printGraph(&graph);
	pq.push({ 0,start });
	int prev_cost, re_start;

	while (!pq.empty()) {
		prev_cost = pq.top().first;
		re_start = pq.top().second;
		visited[re_start] = true;
		pq.pop();

		FindminValue(&graph, re_start, prev_cost);
	}
	Output_result();

	return 0;
}