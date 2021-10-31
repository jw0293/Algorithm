/*
#define MAX_SIZE 9999999
#define swap(type,x,y) do{type t=x;x=y;y=t;} while(0)
typedef struct Heap {
	int size;
	int heap[MAX_SIZE];
}heap;
heap p;

void Init_Tree(heap* p) {
	p->size = 0;
}

int Push_tree(heap* p, int data) {
	if (p->size + 1 > MAX_SIZE) return 0;

	p->heap[p->size] = data;

	int cur = p->size;
	int parent = (p->size - 1) / 2;

	while (cur > 0 && p->heap[cur] < p->heap[parent]) {
		swap(int, p->heap[cur], p->heap[parent]);
		cur = parent;
		parent = (parent - 1) / 2;
	}
	p->size++;
	return 1;

}

int Pop_tree(heap* p) {
	if (p->size <= 0) return 0;

	int cut_data = p->heap[0];

	p->size--;
	p->heap[0] = p->heap[p->size];

	int cur = 0, minNode = 0;
	int left_child = cur * 2 + 1;
	int right_child = cur * 2 + 2;

	while (left_child < p->size) {
		if (p->heap[left_child] < p->heap[minNode]) {
			minNode = left_child;
		}
		if (right_child < p->size && p->heap[right_child] < p->heap[minNode]) {
			minNode = right_child;
		}
		if (cur == minNode)
			break;
		else {
			swap(int, p->heap[cur], p->heap[minNode]);
			cur = minNode;
			left_child = cur * 2 + 1;
			right_child = cur * 2 + 2;
		}
	}
	return cut_data;
}

int Is_Empty_tree(heap* p) {
	if (p->size == 0) return 0;
	else return 1;
}*/  //우선순위 큐// 
/*
// 큐를 이용한 BFS 구현
struct node {
	int x;
	int y;
};

struct node queue[2500];
int head = 0, tail = 0;

void Enque(int x, int y) {
	struct node temp;
	temp.x = x;
	temp.y = y;
	queue[tail] = temp;
	tail = (tail + 1) % 2500;
}

struct node Deque() {
	struct node temp = queue[head];
	head = (head + 1) % 2500;
	return temp;
}

int Is_Empty() {
	if (head == tail) return 0;
	else return 1;
}

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<iostream>
#define dep(i,a,b) for(int i=a;i<b;i++)
#define fep(i,a,b) for(int i=a;i<=b;i++)
#define swap(type,x,y) do{type t=x; x=y; y=t;} while(0)
#define MAX(a,b) a<b?b:a
#define MIN(a,b) a<b?a:b
#define INF 987654321
using namespace std;

typedef struct binary_node {
	int data;
	struct binary_node* left;
	struct binary_node* right;
}BinNode;

BinNode* Init_Node(void) {
	BinNode* newNode = (BinNode*)malloc(sizeof(BinNode));
	newNode->data = 0;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

void set_BinNode(BinNode* ps, int data, BinNode* left_child, BinNode* right_child) {
	ps->data = data;
	ps->left = left_child;
	ps->right = right_child;
}

BinNode* insert_Node(BinNode* node, int value) {
	if (node == NULL) {
		node = Init_Node();
		set_BinNode(node, value, NULL, NULL);
		// printf(" Root Node 생성 완료\n");
	}
	else if (node->data > value) {
		node->left = insert_Node(node->left, value);
	}
	else {
		node->right = insert_Node(node->right, value);
	}
	return node;
}

BinNode* search_Node(BinNode* ptr, int key) {
	if (ptr == NULL)
		return NULL;
	else {
		if (ptr->data == key)
			return ptr;
		else {
			if (ptr->data > key) {
				search_Node(ptr->left, key);
			}
			else {
				search_Node(ptr->right, key);
			}
		}
	}
}

void Preorder_Traverse(BinNode* root) {
	if (root) {
		printf("%d\n", root->data);
		Preorder_Traverse(root->left);
		Preorder_Traverse(root->right);
	}
}

void Inorder_Traverse(BinNode* root) {
	if (root) {
		Inorder_Traverse(root->left);
		printf("%d\n", root->data);
		Inorder_Traverse(root->right);
	}
}

void Postorder_Traverse(BinNode* root) {
	if (root) {
		Postorder_Traverse(root->left);
		Postorder_Traverse(root->right);
		printf("%d\n", root->data);
	}
}

void Delete_Tree(BinNode* root) {
	if (root != NULL) {
		Delete_Tree(root->left);
		Delete_Tree(root->right);
		free(root);
	}
}

BinNode* minValue_Node(BinNode* node) {
	BinNode* cur = node;
	while (cur && cur->left != NULL) {
		cur = cur->left;
	}
	return cur;
}

BinNode* Delete_Node(BinNode* root, int key) {
	if (root == NULL) {
		return root;
	}

	if (key < root->data) {
		root->left = Delete_Node(root->left, key);
	}
	else if (key > root->data) {
		root->right = Delete_Node(root->right, key);
	}
	else {
		if (root->left == NULL) {
			BinNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			BinNode* temp = root->left;
			free(root);
			return temp;
		}

		BinNode* temp = minValue_Node(root->right);
		root->data = temp->data;
		root->right = Delete_Node(root->right, temp->data);
	}
	return root;
}
int num[15];
int main() {
	BinNode* root = NULL;

	/*
	root = insert_Node(root, 50);
	root = insert_Node(root, 30);
	root = insert_Node(root, 24);
	root = insert_Node(root, 5);
	root = insert_Node(root, 28);
	root = insert_Node(root, 45);
	root = insert_Node(root, 98);
	root = insert_Node(root, 52);
	root = insert_Node(root, 60);

	Delete_Node(root, 5);
	Delete_Node(root, 28);
	Postorder_Traverse(root);
	*/

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num[i];
		root = insert_Node(root, num[i]);
	}
	Delete_Node(root, num[1]);
	Inorder_Traverse(root);

	return 0;
}