#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;
// Full Binary Tree node number  1~15(root : 1)
TreeNode n15 = { 15,  NULL, NULL };
TreeNode n14 = { 14,  NULL, NULL };
TreeNode n13 = { 13,  NULL, NULL };
TreeNode n12 = { 12,  NULL,  NULL };
TreeNode n11 = { 11, NULL, NULL };
TreeNode n10 = { 10, NULL, NULL };
TreeNode n9 = { 9, NULL,  NULL };
TreeNode n8 = { 8, NULL,  NULL };
TreeNode n7 = { 7, &n14, &n15 };
TreeNode n6 = { 6, &n12, &n13 };
TreeNode n5 = { 5, &n10, &n11 };
TreeNode n4 = { 4, &n8, &n9 };
TreeNode n3 = { 3, &n6, &n7 };
TreeNode n2 = { 2, &n4, &n5 };
TreeNode n1 = { 1, &n2, &n3 };
TreeNode* root = &n1;
// 배열로 이진트리 구성
typedef struct NODE { int data; int leaf; } node; // leaf의 값이 1이면 child가 있음

// 중위순회
void inorder_rec(TreeNode* root) {
	if (root) {
		inorder_rec(root->left); // 왼쪽서브트리순회
		printf("[%d] ", root->data); // 노드방문
		inorder_rec(root->right); // 오른쪽서브트리순회
	}
}
// 전위순회
void preorder_rec(TreeNode* root) {
	if (root) {
		printf("[%d] ", root->data); // 노드방문
		preorder_rec(root->left); // 왼쪽서브트리순회
		preorder_rec(root->right); // 오른쪽서브트리순회
	}
}
// 후위순회
void postorder_rec(TreeNode* root) {
	if (root) {
		postorder_rec(root->left); // 왼쪽서브트리순회
		postorder_rec(root->right); // 오른쪽서브트리순회
		printf("[%d] ", root->data); // 노드방문
	}
}

#define SIZE 100
int top = -1;
TreeNode* stack[SIZE];
void push(TreeNode* p)
{
	if (top < SIZE - 1)
		stack[++top] = p;
}
TreeNode* pop()
{
	TreeNode* p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

void inorder_iter(TreeNode* root)
{
	while (1) {
		for (; root; root = root->left)
			push(root);
		root = pop();
		if (!root) break;
		printf("[%d] ", root->data);
		root = root->right;
	}
}

void preorder_iter(TreeNode* root) {
	while (1) {
		for (; root; root = root->left) {
			printf("[%d] ", root->data);
			push(root);
		}
		root = pop();
		if (!root) break;
		root = root->right;
	}
}

void postorder_iter(TreeNode* root) {
	if (!root) return;

	int temp_stack[SIZE]; // 출력값을 저장할 임시 스택
	int temp_top = -1;

	push(root);
	while (top >= 0) {
		root = pop();
		temp_stack[++temp_top] = root->data; // 바로 출력하지 않고 임시 스택에 저장

		if (root->left) push(root->left);    // 왼쪽 먼저 push (나중에 나옴)
		if (root->right) push(root->right);  // 오른쪽 나중에 push (먼저 나옴)
	}

	// 임시 스택에 저장된 값을 거꾸로 출력
	while (temp_top >= 0) {
		printf("[%d] ", temp_stack[temp_top--]);
	}
}

#define MAX_TREE_SIZE 15
// Full Binary Tree node number 1~15(root 1, left child n*2, right child n*2+1
node arr[MAX_TREE_SIZE + 1] = { {0,0}, {1,1}, {2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {7,1}, {8,0}, {9,0}, {10,0}, {11,0},
{12,0}, {13,0}, {14,0}, {15,0} };

void inorder_rec_arr(node* ary, int idx) {
	if (idx > MAX_TREE_SIZE) return;

	inorder_rec_arr(ary, idx * 2);

	printf("[%d] ", ary[idx].data);

	inorder_rec_arr(ary, idx * 2 + 1);
}

void preorder_rec_arr(node* ary, int idx) {
	if (idx > MAX_TREE_SIZE) return;

	printf("[%d] ", ary[idx].data);

	preorder_rec_arr(ary, idx * 2);

	preorder_rec_arr(ary, idx * 2 + 1);
}

void postorder_rec_arr(node* ary, int idx) {
	if (idx > MAX_TREE_SIZE) return;

	postorder_rec_arr(ary, idx * 2);

	postorder_rec_arr(ary, idx * 2 + 1);

	printf("[%d] ", ary[idx].data);
}

int main()
{
	printf("중위 순회(rec)      = ");
	inorder_rec(root);
	printf("\n");
	printf("중위 순회(itr)      = ");
	inorder_iter(root);
	printf("\n");
	printf("배열 중위 순회(rec) = ");
	inorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("전위 순회(rec)      = ");
	preorder_rec(root);
	printf("\n");
	printf("전위 순회(itr)      = ");
	preorder_iter(root);
	printf("\n");
	printf("배열 전위 순회(rec) = ");
	preorder_rec_arr(arr, 1);
	printf("\n\n");
	printf("후위 순회(rec)      = ");
	postorder_rec(root);
	printf("\n");
	printf("후위 순회(itr)      = ");
	postorder_iter(root);
	printf("\n");
	printf("배열 후위 순회(rec) = ");
	postorder_rec_arr(arr, 1);
	printf("\n\n");
	return 0;
}