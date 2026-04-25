#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct ELEMENT {
	int id_num;
	char name[10];
} element;

typedef struct TreeNode {
	element std;
	struct TreeNode* left, * right;
} TreeNode;

#define MAX_QUEUE_SIZE 100

typedef struct {
	TreeNode* node;
	int parent_id;
} QueueElement;

typedef struct {
	QueueElement data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType* q, QueueElement item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

QueueElement dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode* ptr)
{
	QueueType q;
	init_queue(&q);
	if (ptr == NULL) {
		printf("공백 트리입니다.");
		return;
	}

	int level = 1;
	QueueElement current_element = { ptr, 0 };
	enqueue(&q, current_element);

	while (!is_empty(&q)) {
		int size = (q.rear - q.front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
		printf("\n Level %d : ", level++);

		for (int i = 0; i < size; i++) {
			QueueElement curr = dequeue(&q);

			if (curr.parent_id == 0) {
				printf("[%d] ", curr.node->std.id_num);
			}
			else {
				printf("(%d)->[%d] ", curr.parent_id, curr.node->std.id_num);
			}

			if (curr.node->left) {
				QueueElement left_child = { curr.node->left, curr.node->std.id_num };
				enqueue(&q, left_child);
			}
			if (curr.node->right) {
				QueueElement right_child = { curr.node->right, curr.node->std.id_num };
				enqueue(&q, right_child);
			}
		}
	}
}

TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
	temp->std = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* node, element item)
{
	if (node == NULL) return new_node(item);

	if (item.id_num < node->std.id_num)
		node->left = insert_node(node->left, item);
	else if(item.id_num > node->std.id_num)
		node->right = insert_node(node->right, item);

	return node;
}

TreeNode* min_value_node(TreeNode* node)
{
	TreeNode* current = node;
	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->left != NULL)
		current = current->left;
	return current;
}

TreeNode* delete_node(TreeNode* root, int key)
{
	if (root == NULL) return root;
	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	if (key < root->std.id_num)
		root->left = delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (key > root->std.id_num)
		root->right = delete_node(root->right, key);
	else {// 키가 루트와 같으면 이 노드를 삭제하면 됨
		// 첫 번째나 두 번째 경우
		if (root->left == NULL) {
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		// 세 번째 경우
		TreeNode* temp = min_value_node(root->right);
		// 중외 순회시 후계 노드를 복사한다.
		root->std = temp->std;
		// 중외 순회시 후계 노드를 삭제한다.
		root->right = delete_node(root->right, temp->std.id_num);
	}
	return root;
}

int get_node_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}

int get_leaf_count(TreeNode* node)
{
	int count = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}
	return count;
}

int get_height(TreeNode* node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left), get_height(node->right));
	return height;
}

TreeNode* search(TreeNode* node, int key)
{
	if (node == NULL) return NULL;
	if (key == node->std.id_num) return node;
	else if (key < node->std.id_num)
		return search(node->left, key);
	else
		return search(node->right, key);
}

void inorder(TreeNode* root)
{
	if (root) {
		inorder(root->left);
		printf("[%d] ", root->std.id_num);
		inorder(root->right);
	}
}

TreeNode* delete_tree(TreeNode* root)
{
	if (root) {
		delete_tree(root->left);
		delete_tree(root->right);
		printf("[%d] ", root->std.id_num);
		free(root);
	}
}

int main(void)
{
	TreeNode* root = NULL;
	TreeNode* tmp = NULL;
	element item;
	item.id_num = 2021006; strcpy(item.name, "name6");
	root = insert_node(root, item);
	item.id_num = 2021001; strcpy(item.name, "name1");
	root = insert_node(root, item);
	item.id_num = 2021009; strcpy(item.name, "name9");
	root = insert_node(root, item);
	item.id_num = 2021007; strcpy(item.name, "name7");
	root = insert_node(root, item);
	item.id_num = 2021003; strcpy(item.name, "name3");
	root = insert_node(root, item);
	item.id_num = 2021002; strcpy(item.name, "name2");
	root = insert_node(root, item);
	item.id_num = 2021005; strcpy(item.name, "name5");
	root = insert_node(root, item);
	item.id_num = 2021004; strcpy(item.name, "name4");
	root = insert_node(root, item);
	item.id_num = 2021008; strcpy(item.name, "name8");
	root = insert_node(root, item);
	item.id_num = 2021010; strcpy(item.name, "name10");
	root = insert_node(root, item);
	printf("이진 탐색 트리의 노드 수, leaf노드 수, 높이 구하기\n");
	printf("노드 수 = %d \nleaf 노드 수 = %d \n높이 = %d \n\n",
		get_node_count(root), get_leaf_count(root), get_height(root));
	printf("이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root);
	printf("\n\n이진 탐색 트리에서 2021010 검색\n");
	tmp = search(root, 2021010);
	if (tmp != NULL)
		printf("검색 성공 : 학번 %d, 이름 %s \n", tmp->std.id_num,
			tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");
	printf("\n이진 탐색 트리에서 2021006 삭제\n");
	delete_node(root, 2021006);
	printf("\n\n이진 탐색 트리에서 2021006 검색\n");
	tmp = search(root, 2021006);
	if (tmp != NULL)
		printf("검색 성공 : 학번 %d, 이름 %s \n", tmp->std.id_num,
			tmp->std.name);
	else
		printf("이진 탐색 트리에서 검색 학생을 발견못함 \n");
	printf("\n\n이진 탐색 트리 레벨 탐색 순회 결과 \n");
	level_order(root);
	printf("\n\n");
	printf("\n\n이진 탐색 트리 전체 삭제 \n");
	root = delete_tree(root);
	printf("\n\n이진 탐색 트리 레벨 탐색 순회 결과\n");
	level_order(root);
	printf("\n\n");
	return 0;
}