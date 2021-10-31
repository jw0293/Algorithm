#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <unordered_set>
#include <map> 
#include <algorithm>
#include <cmath>
#include <ctime>
#define CUNLINK ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define ENDL cout << endl
#define ll long long
#define ull unsigned long long
#define INF 987654321987654
#define Mod 1000000009
#define endl '\n'
#define pil pair<int,int>

using namespace std;

int n, T;
const int MAX = 17;
vector<int> adj[50001];
int depth[50001];
int parent[50001][MAX];

void DFS_Depth(int node) {
	for (int next : adj[node]) {
		if (depth[next] == -1) {
			depth[next] = depth[node] + 1;
			parent[next][0] = node;
			DFS_Depth(next);
		}
	}
	return;
}

void Depth_Link() {
	for (int power = 1; power < MAX; ++power) 
		for (int node = 1; node <= n; ++node) 
			parent[node][power] = parent[parent[node][power - 1]][power - 1];
	return;
}

int LCA(int node1, int node2) {
	if (depth[node1] < depth[node2]) swap(node1, node2);
	int diff = depth[node1] - depth[node2];
	for (int count = 0; diff != 0; ++count) {
		if (diff % 2 == 1) node1 = parent[node1][count];
		diff /= 2;
	}

	if (node1 != node2) {
		for (int i = MAX - 1; i >= 0; --i) {
			if (parent[node1][i] != -1 && parent[node1][i] != parent[node2][i]) {
				node1 = parent[node1][i];
				node2 = parent[node2][i];
			}
		}
		node1 = parent[node1][0];
	}
	return node1;
}

int main() {
	CUNLINK;
	cin >> n;
	fill(depth, depth + n + 1, -1);
	memset(parent, -1, sizeof(parent));
	for (int i = 0; i < n - 1; ++i) {
		int From, To;
		cin >> From >> To;
		adj[From].push_back(To);
		adj[To].push_back(From);
	}

	for (int i = 0; i < MAX - 1; i++) parent[1][i] = 1;
	// root 노드의 깊이는 0
	depth[1] = 0;
	// 자식-부모 관계를 이용하여 깊이 설정 및 부모 설정
	DFS_Depth(1);
	// logn 시간복잡도를 위해 2^x승 부모노드 알아내기
	Depth_Link();

	cin >> T;
	for(int i=0;i<T;++i){
		int node_1, node_2;
		cin >> node_1 >> node_2;
		cout << LCA(node_1, node_2) << endl;
	}
	
	return 0;
}