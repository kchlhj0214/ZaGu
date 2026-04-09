#include<stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

#define MAX_LIST_SIZE 100

typedef int element;

typedef struct{
	element array[MAX_LIST_SIZE];
	int size;
} SortedList;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init(SortedList* L)
{
	L->size = 0;
}
int is_empty(SortedList* L)
{
	return L->size == 0;
}
int is_full(SortedList* L)
{
	return L->size == MAX_LIST_SIZE;
}
//void add(SortedList* L, element item)			// 역순한 배열이 들어가면 정렬 오류 발생
//{
//	if (is_full(L))
//		return -1;
//
//	for (int i = 0; i < L->size; ++i) {
//		if (L->array[i] > item) {
//			for (int k = L->size; k > i; --k) {
//				L->array[k] = L->array[k - 1];
//			}
//			L->array[i] = item;
//			L->size++;
//			return;
//		}
//	}
//
//	if (is_empty(L)) {
//		L->array[0] = item;
//		L->size++;
//	}
//	else {
//		L->array[L->size] = item;
//		L->size++;
//	}
//}
void add(SortedList* L, element item)
{
	if (is_full(L)) return;

	int direction = 1;
	if (L->size >= 2) {
		int first = L->array[0];
		int last = L->array[L->size - 1];

		if (first == last) {
			for (int i = 1; i < L->size; i++) {
				if (L->array[i] != first) {
					last = L->array[i];
					break;
				}
			}
		}

		if (first > last) direction = 0;
	}

	int i;
	for (i = 0; i < L->size; ++i) {
		int condition;
		if (direction == 1) 
			condition = (L->array[i] > item);
		else 
			condition = (L->array[i] < item);

		if (condition) {
			for (int k = L->size; k > i; --k) {
				L->array[k] = L->array[k - 1];
			}
			break;
		}
	}
	L->array[i] = item;
	L->size++;
}
int delete(SortedList* L, element item)
{
	if (is_empty(L))
		return -1;
	int pos;
	for (int i = 0; i < L->size; ++i) {
		if (L->array[i] == item) {
			pos = i;
			for (int k = i; k < L->size; ++k)
				L->array[k] = L->array[k + 1];
			L->size--;
			return pos;
		}
	}
	return -1;
}
void clear(SortedList* L)
{
	L->size = 0;
}
int is_in_list(SortedList* L, element item) {
	for (int i = 0; i < L->size; ++i) {
		if (L->array[i] == item)
			return i;
	}
	return -1;
}
int get_length(SortedList* L)
{
	return L->size;
}
element get_entry(SortedList* L, int pos)
{
	if (pos >= 0 && pos < L->size)
		return L->array[pos];
	else
		return -1;
}
SortedList* reverse(SortedList* L)
{
	SortedList* temp = (SortedList*)malloc(sizeof(SortedList));
	init(temp);
	temp->size = L->size;
	for (int i = 0; i < L->size; ++i) {
		temp->array[i] = L->array[L->size - i - 1];
	}
	return temp;
}
void display(SortedList* L) 
{
	for (int i = 0; i < L->size; ++i) {
		printf("%d->", L->array[i]);
	}
	printf("\n");
}

int main(void) {
	int item;
	char ch;
	SortedList list;
	SortedList* rList;

	init(&list);
	
	srand(100);
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = getch();
		if (ch == 'q') break;
	}

	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n",
		is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	display(&list);
	rList = reverse(&list);
	display(rList);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("get_length : %d \n", get_length(&list));
	//종료하기 전에 수행해야 할 코드 추가
	free(rList);

	return 0;
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

#define MAX_LIST_SIZE 100
typedef int element;

typedef struct Node {
	element data;
	struct Node* link;
} Node;

typedef struct {
	Node* head;
	int size;
} SortedList;

void init(SortedList* L) {
	L->head = NULL;
	L->size = 0;
}

int is_empty(SortedList* L) {
	return (L->size == 0);
}

int is_full(SortedList* L) {
	return (L->size >= MAX_LIST_SIZE);
}

//void add(SortedList* L, element item) {		// 리스트가 리버스되어 현 상태가 역순이라면 오류 발생
//	if (is_full(L)) 
//		return -1;
//
//	Node* new_node = (Node*)malloc(sizeof(Node));
//	new_node->data = item;
//
//	Node* prev = NULL;
//	Node* curr = L->head;
//
//	while (curr != NULL && item > curr->data) {
//		prev = curr;
//		curr = curr->link;
//	}
//
//	if (prev == NULL) {
//		new_node->link = L->head;
//		L->head = new_node;
//	}
//	else {
//		new_node->link = curr;
//		prev->link = new_node;
//	}
//	L->size++;
//}

void add(SortedList* L, element item) {
	if (is_full(L)) return;

	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = item;

	Node* prev = NULL;
	Node* curr = L->head;

	int direction = 1;
	if (L->head != NULL && L->head->link != NULL) {
		Node* first = L->head;
		Node* second = L->head->link;

		while (second != NULL && first->data == second->data) {
			second = second->link;
		}

		if (second != NULL && first->data > second->data) {
			direction = 0;
		}
	}

	curr = L->head;
	while (curr != NULL) {
		if (direction == 1) { // 오름차순 모드
			if (item <= curr->data) break;
		}
		else {              // 내림차순 모드
			if (item >= curr->data) break;
		}
		prev = curr;
		curr = curr->link;
	}
	new_node->link = curr;

	if (prev == NULL) 
		L->head = new_node;
	else 
		prev->link = new_node;

	L->size++;
}

int delete(SortedList* L, element item) {
	if (is_empty(L))
		return -1;

	int count = 0;

	Node* prev = NULL;
	Node* curr = L->head;

	while (curr != NULL && curr->data != item) {
		prev = curr;
		curr = curr->link;
		++count;
	}

	if (curr == NULL)
		return -1;

	if (prev == NULL)
		L->head = curr->link;
	else
		prev->link = curr->link;

	free(curr);
	L->size--;
	return count;
}

void clear(SortedList* L) {
	Node* curr = L->head;
	Node* next;

	while (curr != NULL) {
		next = curr->link;
		free(curr);
		curr = next;
	}
	L->head = NULL;
	L->size = 0;
}

int is_in_list(SortedList* L, element item) {
	Node* curr = L->head;
	int count = 0;

	while (curr != NULL && curr->data != item) {
		curr = curr->link;
		count++;
	}
	if (curr == NULL)
		return -1;
	else
		return count;
}

int get_length(SortedList* L) {
	return L->size;
}

element get_entry(SortedList* L, int pos) {
	Node* curr = L->head;
	int curpos = 0;

	if (L->size <= pos || pos < 0)
		return -1;

	while (curpos != pos) {
		curr = curr->link;
		curpos++;
	}
	return curr->data;
}

//SortedList* reverse(SortedList* L) {		// 원본을 변경해버림
//	Node* p = L->head;
//	Node* q = NULL;
//	Node* r = NULL;
//
//	while (p != NULL) {
//		r = q;
//		q = p;
//		p = p->link;
//		q->link = r;
//	}
//	L->head = q;
//
//	return L;
//}

SortedList* reverse(SortedList* L) {
	SortedList* newList = (SortedList*)malloc(sizeof(SortedList));
	newList->head = NULL;
	newList->size = 0;

	Node* curr = L->head;

	while (curr != NULL) {
		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->data = curr->data;

		new_node->link = newList->head;
		newList->head = new_node;

		newList->size++;
		curr = curr->link;
	}

	return newList;
}

void display(SortedList* L) {
	Node* curr = L->head;
	while (curr != NULL) {
		printf("%d->", curr->data);
		curr = curr->link;
	}
	printf("\n");
}

int main(void) {
	int item;
	char ch;
	SortedList list;
	SortedList* rList;
	//필요한 초기화 코드 추가

	init(&list);

	srand(100);
	while (1) {
		item = rand();
		add(&list, item);
		display(&list);
		ch = getch();
		if (ch == 'q') break;
	}
	/*for (int i = 0; i < 11; ++i) {
		item = rand();
		add(&list, item);
		display(&list);
	}*/
	printf("get_length : %d \n", get_length(&list));
	printf("is_empty : %d, is_full : %d \n", is_empty(&list), is_full(&list));
	printf("get_entry : %d위치의 데이터는 %d\n", 5, get_entry(&list, 5));
	printf("is_in_list : %d의 위치는 %d \n", 5415, is_in_list(&list, 5415));
	printf("is_in_list : %d의 위치는 %d \n", 10, is_in_list(&list, 10));
	printf("delete : %d의 위치는 %d \n", 5415, delete(&list, 5415));
	display(&list);
	rList = reverse(&list);
	display(rList);
	printf("call clear\n");
	clear(&list);
	display(&list);
	printf("get_length : %d \n", get_length(&list));
	//종료하기 전에 수행해야 할 코드 추가

	if (rList != NULL) {
		clear(rList);
		free(rList);
	}

	return 0;
}

#endif