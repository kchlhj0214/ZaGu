#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
} element;

typedef struct STACKNODE {
	element data;
	struct STACKNODE* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedlistStack;

void init(LinkedlistStack* S) {
	S->top = NULL;
}

int is_empty(LinkedlistStack* S) {
	return (S->top == NULL);
}

int is_full(LinkedlistStack* S) {
	return 0;
}

void push(LinkedlistStack* S, element item) {
	StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
	if (new_node == NULL)
		exit(1);

	if (is_empty(S))
		new_node->link = NULL;
	else
		new_node->link = S->top;

	new_node->data = item;
	S->top = new_node;
}

element pop(LinkedlistStack* S) {
	if (is_empty(S)) {
		printf("스택이 비어있음\n");
		element e = { INT_MIN, INT_MIN, INT_MIN };
		return e;
	}
	StackNode* front = S->top;
	element pop_data = front->data;
	S->top = front->link;
	free(front);
	return pop_data;
}

element peek(LinkedlistStack* S) {
	if (is_empty(S))
		exit(1);
	return S->top->data;
}

void print_stack(LinkedlistStack* S) {
	printf("==========스택 내용========\n(");
	if (is_empty(S))
		printf(" NULL ");
	else {
		printf("%d", S->top->data.x);
		printf(", ");
		printf("%d", S->top->data.y);
		printf(", ");
		printf("%d", S->top->data.z);
	}
	printf(") <--- TOP\n");

	StackNode* curr = NULL;
	if (!is_empty(S))
		curr = S->top->link;
	while (curr != NULL) {
		printf("(%d", curr->data.x);
		printf(", ");
		printf("%d", curr->data.y);
		printf(", ");
		printf("%d)\n", curr->data.z);
		curr = curr->link;
	}
	printf("=========================\n");
	return;
}

int main()
{
	LinkedlistStack s;
	element item;

	init(&s);
	print_stack(&s);
	item.x = 1; item.y = 1; item.z = 1;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 2; item.y = 2; item.z = 2;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 3; item.y = 3; item.z = 3;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	item.x = 4; item.y = 4; item.z = 4;
	printf("Push item\n");
	push(&s, item); print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
	printf("PoP item\n");
	item = pop(&s);
	printf("PoP된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_stack(&s);
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

typedef struct WORLD_COORDINATE {
	int x;
	int y;
	int z;
}element;

typedef struct QueueNode {
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, * rear;
} LinkedlistQueue;

void init(LinkedlistQueue* Q) {
	Q->front = NULL;
	Q->rear = NULL;
}

int is_empty(LinkedlistQueue* Q) {
	return (Q->front == NULL);
}

int is_full(LinkedlistQueue* Q) {
	return 0;
}

void enqueue(LinkedlistQueue* Q, element item) {
	QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
	if (new_node == NULL) exit(1);

	new_node->data = item;
	new_node->link = NULL;

	if (is_empty(Q)) {
		Q->front = new_node;
		Q->rear = new_node;
	}
	else {
		Q->rear->link = new_node;
		Q->rear = new_node;
	}
}

element dequeue(LinkedlistQueue* Q) {
	if (is_empty(Q)) {
		element e = { INT_MIN, INT_MIN, INT_MIN };
		printf("큐가 비어있음\n");
		return e;
	}

	QueueNode* temp = Q->front;
	element deq_data = temp->data;

	Q->front = Q->front->link;

	if (Q->front == NULL) {
		Q->rear = NULL;
	}

	free(temp);
	return deq_data;
}

void print_queue(LinkedlistQueue* Q) {
	printf("==========큐 내용========\n(");
	if (is_empty(Q)) {
		printf(" NULL ) <--- Front, Rear\n");
		printf("=========================\n");
		return;
	}
	else if(Q->front == Q->rear){
		printf("%d", Q->front->data.x);
		printf(", ");
		printf("%d", Q->front->data.y);
		printf(", ");
		printf("%d", Q->front->data.z);
		printf(") <--- Front, Rear\n");
		printf("=========================\n");
		return;
	}
	else {
		printf("%d", Q->front->data.x);
		printf(", ");
		printf("%d", Q->front->data.y);
		printf(", ");
		printf("%d", Q->front->data.z);
	}
	printf(") <--- Front");

	QueueNode* curr = NULL;
	if (!is_empty(Q))
		curr = Q->front->link;
	while (curr != NULL) {
		printf("\n(%d", curr->data.x);
		printf(", ");
		printf("%d", curr->data.y);
		printf(", ");
		printf("%d)", curr->data.z);
		curr = curr->link;
	}
	printf(" <--- Rear\n");
	printf("=========================\n");
	return;
}

int main() 
{
	LinkedlistQueue queue;
	element item;

	init(&queue); // 큐 초기화
	print_queue(&queue);
	printf("enqueue item \n");
	item.x = 1, item.y = 1, item.z = 1;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 2, item.y = 2, item.z = 2;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 3, item.y = 3, item.z = 3;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 4, item.y = 4, item.z = 4;
	enqueue(&queue, item); print_queue(&queue);
	printf("enqueue item \n");
	item.x = 5, item.y = 5, item.z = 5;
	enqueue(&queue, item); print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
	printf("dequeue item\n");
	item = dequeue(&queue);
	printf("Dequeue된 data : (%d, %d, %d) \n", item.x, item.y, item.z);
	print_queue(&queue);
}

#endif