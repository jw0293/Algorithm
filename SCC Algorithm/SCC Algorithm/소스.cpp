#include<iostream>
#include <algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<string>
#include<cstring>
#include<cmath>
#include<map>
#define endl '\n'
#define CUNLINK ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
#define ll long long

using namespace std;
// DFS와 스택을 이용해 구현한 Strongly Connected Component(SCC) 알고리즘
typedef struct GraphNode {
	int dest;
	int cost;
	GraphNode* next;
}GraphNode;

typedef struct Graph {
	int count;
	GraphNode* adj;
}Graph;

int V, E;
int id, address[10003];
bool isComplete[10003];
vector<vector<int>> SCC;
stack<int> stk;

void Init_Graph(Graph* gph, int Cnt) {
	gph->count = Cnt;
	gph->adj = (GraphNode*)malloc(sizeof(GraphNode) * (Cnt + 1));
	for (int i = 1; i <= Cnt; i++) {
		gph->adj[i].next = NULL;
	}
}

int AddDirectedlinkedEdge(Graph* gph, int src, int dst, int cost) {
	GraphNode* Temp = (GraphNode*)malloc(sizeof(GraphNode));
	Temp->cost = cost;
	Temp->dest = dst;
	Temp->next = gph->adj[src].next;
	gph->adj[src].next = Temp;
	return 1;
}

int DFS(Graph* gph, int x) {
	address[x] = ++id;
	stk.push(x);

	int Parent = address[x];
	GraphNode* head = gph->adj[x].next;
	while (head) {
		int y = head->dest;
		if (!address[y])
			Parent = min(Parent, DFS(gph, y));
		else if (!isComplete[y])
			Parent = min(Parent, address[y]);
		head = head->next;
	}

	if (Parent == address[x]) {
		vector<int> scc;
		while (1) {
			int t = stk.top();
			stk.pop();
			scc.push_back(t);
			isComplete[t] = true;
			if (t == x) break;
		}
		SCC.push_back(scc);
	}
	return Parent;
}

int main() {
	CUNLINK;
	Graph graph;
	cin >> V >> E;
	Init_Graph(&graph, V);
	while (E--) {
		int From, To;
		cin >> From >> To;
		AddDirectedlinkedEdge(&graph, From, To, 1);
	}

	for (int i = 1; i <= V; i++) {
		if (!isComplete[i])
			DFS(&graph, i);
	}
	cout << SCC.size() << endl;
	for (int i = 0; i < SCC.size(); i++) {
		sort(SCC[i].begin(), SCC[i].end());
	}
	sort(SCC.begin(), SCC.end());
	for (int i = 0; i < SCC.size(); i++) {
		for (auto g : SCC[i]) cout << g << " ";
		cout << -1 << endl;
	}
	return 0;
}