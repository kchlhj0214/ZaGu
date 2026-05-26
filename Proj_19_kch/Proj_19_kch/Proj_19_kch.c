#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

#define SIZE 1000000// 저장된 데이터의 갯수
#define DATA 586321 // 찾는 키 값
//#define DATA 802 // 찾는 키 값

int seqsearch(int list[], int low, int high, int key, int *count)
{
	int i;
	*count = 0;
	for (i = low; i <= high; i++) {
		(*count)++;
		if (list[i] == key)
			return i; // 탐색성공
	}
	return -1;    // 탐색실패
}

int binsearch(int list[], int low, int high, int key, int *count)
{
	int middle;
	*count = 0;
	while (low <= high) { // 아직숫자들이남아있으면
		(*count)++;
		middle = (low + high) / 2;
		if (key == list[middle]) return middle; // 탐색성공
		else if (key > list[middle]) low = middle + 1; // 왼쪽부분리스트탐색
		else high = middle - 1; // 오른쪽부분리스트탐색
	}
	return -1; // 탐색실패
}

int search_interpolation(int list[], int low, int high, int key, int *count)
{
	int j;
	*count = 0;
	while ((list[high] >= key) && (key > list[low])) {
		(*count)++;
		j = ((float)(key - list[low]) / (list[high] - list[low])
			* (high - low)) + low;
		if (key > list[j]) low = j + 1;
		else if (key < list[j]) high = j - 1;
		else low = j;
	}
	if (list[low] == key) return(low);  // 탐색성공
	else return -1;  // 탐색실패
}

int main(void)
{
	int i, s_time, e_time, count, result;
	int* list = (int*)malloc(sizeof(int) * SIZE);
	if (list == NULL) { printf("메모리 할당 오류 \n"); exit(-1); }

	// 오름차순으로 정수 데이터 생성 및 저장
	list[0] = 0;
	for (i = 1; i < SIZE; i++)
		list[i] = list[i - 1] + (rand() % 3);
	printf("Data 크기 : %d, 검색 데이터 : %d \n", SIZE, DATA);
	printf("----------------------------------------------\n");

	s_time = clock();
	result = seqsearch(list, 0, SIZE - 1, DATA, &count); //순차탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("순차탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);

	s_time = clock();
	result = binsearch(list, 0, SIZE - 1, DATA, &count); //이진탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("이진탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);

	s_time = clock();
	result = search_interpolation(list, 0, SIZE - 1, DATA, &count);//보간탐색 호출 
	e_time = clock();
	if (result == -1) printf("검색 결과 : 검색 데이터 없음 \n");
	else printf("검색결과 : %d 위치에서 찾음 \n", result);
	printf("보간탐색 소요시간 %d, 비교횟수 : %d\n\n", e_time - s_time, count);

	free(list);

	return 0;
}


#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

// AVL 트리 노드 정의
typedef struct AVLNode
{
	int key;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;

// --- 트리의 높이 계산 함수 ---
int get_height(AVLNode* node)
{
	if (node == NULL) return 0;
	int left_h = get_height(node->left);
	int right_h = get_height(node->right);
	return 1 + ((left_h > right_h) ? left_h : right_h);
}

int get_balance(AVLNode* node)
{
	if (node == NULL) return 0;
	return get_height(node->left) - get_height(node->right);
}

// --- 노드 생성 함수 ---
AVLNode* create_node(int key)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// --- 회전 함수 (회전 매커니즘 로그 출력 포함) ---
// 오른쪽 회전 (LL 회전)
AVLNode* rotate_right(AVLNode* parent)
{
	AVLNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}

// 왼쪽 회전 (RR 회전)
AVLNode* rotate_left(AVLNode* parent)
{
	AVLNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}

// --- AVL 삽입 함수 ---
AVLNode* AVL_insert(AVLNode* node, int key)
{
	if (node == NULL)
		return create_node(key);

	if (key < node->key)
		node->left = AVL_insert(node->left, key);
	else if (key > node->key)
		node->right = AVL_insert(node->right, key);
	else
		return node;

	int balance = get_balance(node);

	// LL 타입
	if (balance > 1 && key < node->left->key) {
		printf("LL : %d\n", node->key);
		return rotate_right(node);
	}

	// RR 타입
	if (balance < -1 && key > node->right->key) {
		printf("RR : %d\n", node->key);
		return rotate_left(node);
	}

	// LR 타입
	if (balance > 1 && key > node->left->key) {
		printf("LR : %d\n", node->key);
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	// RL 타입
	if (balance < -1 && key < node->right->key) {
		printf("RL : %d\n", node->key);
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}

	return node;
}

// --- AVL 삭제 도우미: 최솟값 노드 찾기 ---
AVLNode* min_value_node(AVLNode* node)
{
	AVLNode* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}

// --- AVL 삭제 함수 ---
AVLNode* AVL_remove(AVLNode* root, int key)
{
	if (root == NULL) return root;

	if (key < root->key)
		root->left = AVL_remove(root->left, key);
	else if (key > root->key)
		root->right = AVL_remove(root->right, key);
	else {
		if ((root->left == NULL) || (root->right == NULL)) {
			AVLNode* temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else {
			AVLNode* temp = min_value_node(root->right);
			root->key = temp->key;
			root->right = AVL_remove(root->right, temp->key);
		}
	}

	if (root == NULL) return root;

	int balance = get_balance(root);

	// LL 상태 회전
	if (balance > 1 && get_balance(root->left) >= 0) {
		printf("LL : %d\n", root->key);
		return rotate_right(root);
	}

	// LR 상태 회전
	if (balance > 1 && get_balance(root->left) < 0) {
		printf("LR : %d\n", root->key);
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	// RR 상태 회전
	if (balance < -1 && get_balance(root->right) <= 0) {
		printf("RR : %d\n", root->key);
		return rotate_left(root);
	}

	// RL 상태 회전
	if (balance < -1 && get_balance(root->right) > 0) {
		printf("RL : %d\n", root->key);
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}

// --- 레벨 순회용 요소 정의 (부모 관계 추적용) ---
typedef struct {
	AVLNode* node;
	AVLNode* parent;
} QueueElement;

#define QUEUE_SIZE 200
typedef struct {
	QueueElement data[QUEUE_SIZE];
	int front, rear;
} QueueType;

void init_queue(QueueType* q) { q->front = q->rear = 0; }
int is_empty(QueueType* q) { return q->front == q->rear; }
void enqueue(QueueType* q, QueueElement item) {
	q->rear = (q->rear + 1) % QUEUE_SIZE;
	q->data[q->rear] = item;
}
QueueElement dequeue(QueueType* q) {
	q->front = (q->front + 1) % QUEUE_SIZE;
	return q->data[q->front];
}

// --- 이미지의 출력 구조를 그대로 구현한 레벨 순회 함수 ---
void level_order(AVLNode* root)
{
	if (root == NULL) return;

	printf("\nLevle Print\n"); // 이미지의 오타 'Levle' 그대로 반영

	QueueType q;
	init_queue(&q);

	QueueElement first = { root, NULL };
	enqueue(&q, first);

	int level = 1;

	while (!is_empty(&q)) {
		int count = (q.rear - q.front + QUEUE_SIZE) % QUEUE_SIZE; // 현재 레벨의 노드 수
		printf("Levle %d : ", level);

		for (int i = 0; i < count; i++) {
			QueueElement current = dequeue(&q);

			// 출력 포맷 맞추기: 부모가 없으면 루트 노드 값만, 있으면 (부모)--> 자식 ,
			if (current.parent == NULL) {
				printf("%d ", current.node->key);
			}
			else {
				printf("(%d)--> %d , ", current.parent->key, current.node->key);
			}

			// 자식 노드들을 부모 정보와 함께 큐에 삽입
			if (current.node->left != NULL) {
				QueueElement left_child = { current.node->left, current.node };
				enqueue(&q, left_child);
			}
			if (current.node->right != NULL) {
				QueueElement right_child = { current.node->right, current.node };
				enqueue(&q, right_child);
			}
		}
		printf("\n");
		level++;
	}
	printf("\n");
}

// 테스트를 위한 main 함수
int main(void)
{
	AVLNode* root = NULL;
	// 60 50 20 80 90 70 55 10 40 35
	// 예제 트리 구축
	printf("Insert %d\n", 60); root = AVL_insert(root, 60);
	printf("Insert %d\n", 50); root = AVL_insert(root, 50);
	printf("Insert %d\n", 20); root = AVL_insert(root, 20);
	level_order(root);
	printf("Insert %d\n", 80); root = AVL_insert(root, 80);
	level_order(root);
	printf("Insert %d\n", 90); root = AVL_insert(root, 90);
	level_order(root);
	printf("Insert %d\n", 70); root = AVL_insert(root, 70);
	level_order(root);
	printf("Insert %d\n", 55); root = AVL_insert(root, 55);
	level_order(root);
	printf("Insert %d\n", 10); root = AVL_insert(root, 10);
	level_order(root);
	printf("Insert %d\n", 40); root = AVL_insert(root, 40);
	level_order(root);
	printf("Insert %d\n", 35); root = AVL_insert(root, 35);
	level_order(root);
	printf("Remove %d\n", 50); root = AVL_remove(root, 50);
	level_order(root);
	printf("Remove %d\n", 55); root = AVL_remove(root, 55);
	level_order(root);
	return 0;
}


#endif
