#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 3 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
#define MAX_QUEUE_SIZE 1000000
typedef struct {
	int N, T;
} VIRUS;

typedef VIRUS element;
typedef struct{
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_queue(QueueType* q)
{
	q->rear = 0;
	q->front = 0;
}
int is_full(QueueType* q)
{
	// 단순히 rear == front로 비교하면 front가 0, rear가 끝자리일때 오류 발생
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}
void enqueue(QueueType* q, element item)
{
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
element dequeue(QueueType* q)
{
	if (is_empty(q)) {
		error("큐가 공백상태입니다.");
		return;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
int ary[MAX_QUEUE_SIZE];		// ary[n] == 1이면 n은 중복되는 숫자
int computeTime(int goal_virus)
{
	if (goal_virus == 1) return 0;

	QueueType* q = (QueueType*)malloc(sizeof(QueueType));

	init_queue(q);

	VIRUS v = { 1, 0 };
	enqueue(q, v);
	ary[1] = 1;

	int result = -1;
	while (!is_empty(q)) {
		VIRUS curr = dequeue(q);
		int next_n[2] = { curr.N * 2, curr.N / 3 };

		for (int i = 0; i < 2; i++) {
			int n = next_n[i];
			int t = curr.T + 1;
			if (n == goal_virus) {
				result = t;
				goto end;
			}
			if (n > 0 && n < MAX_QUEUE_SIZE && !ary[n]) {
				ary[n] = 1;
				VIRUS next_v = { n, t };
				enqueue(q, next_v);
			}
		}
	}

end:
	free(q);
	return result;
}

int main()
{
	int v;
	printf("현재 바이러스 수 입력 : ");
	scanf_s("%d", &v);
	printf("%d 마리가 되는 데 필요한 최소 시간 : %d", v, computeTime(v));
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
#define MAX_QUEUE_SIZE 10000

typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_queue(QueueType* q)
{
	q->rear = 0;
	q->front = 0;
}
int is_full(QueueType* q)
{
	// 단순히 rear == front로 비교하면 front가 0, rear가 끝자리일때 오류 발생
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}
void enqueue(QueueType* q, element item)
{
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
element dequeue(QueueType* q)
{
	if (is_empty(q)) {
		error("큐가 공백상태입니다.");
		return;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
int dead_people(int n, int k)
{
	QueueType q;
	init_queue(&q);
	int loop_num = 1;
	int temp;

	for (int i = 1; i <= n; ++i)
		enqueue(&q, i);

	while (!is_empty(&q)) {
		temp = dequeue(&q);
		if (loop_num % k == 0) {
			printf(" %d ", temp);
			if (is_empty(&q))
				return temp;
		}
		else
			enqueue(&q, temp);
		++loop_num;
	}
}

int main()
{
	int n, k;
	int final_alive;
	printf("게임에 참여하는 사람의 수 n과 선택하는 k값 입력 : ");
	scanf_s("%d %d", &n, &k);
	printf("선택된 사람의 번호 :");
	final_alive = dead_people(n, k);
	printf("\n최종 살아남은 사람은 %d 위치에 줄을 선 사람임", final_alive);
}

#elif PROB == 3
// 3번 문제를 해결하기 위한 프로그램 작성
#define MAX_QUEUE_SIZE 10000

typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
} QueueType;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
void init_queue(QueueType* q)
{
	q->rear = 0;
	q->front = 0;
}
int is_full(QueueType* q)
{
	// 단순히 rear == front로 비교하면 front가 0, rear가 끝자리일때 오류 발생
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}
void enqueue(QueueType* q, element item)
{
	if (is_full(q)) {
		error("큐가 포화상태입니다.");
		return;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
element dequeue(QueueType* q)
{
	if (is_empty(q)) {
		error("큐가 공백상태입니다.");
		return;
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

typedef struct {
	element* data;
	int capacity;
	int top;
}StackType;

void init_stack(StackType* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_emptys(StackType* s) {
	return (s->top == -1);
}

int is_fulls(StackType* s) {
	return (s->top == (s->capacity - 1));
}

void push(StackType* s, element item)
{
	if (is_fulls(s)) {
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_emptys(s)) {
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

element peek(StackType* s)
{
	if (is_emptys(s)) {
		exit(1);
	}
	else
		return s->data[s->top];
}

void stack_su(int n, int* p)
{
	QueueType lq, rq;
	StackType ms;
	int t = 0;
	int queue_temp;

	init_queue(&lq);
	init_queue(&rq);
	init_stack(&ms);

	for (int i = 1; i <= n; ++i)
		enqueue(&rq, i);

	while (t < n) {
		if (!is_emptys(&ms) && peek(&ms) == p[t]) {
			enqueue(&lq, pop(&ms));
			++t;
		}
		else if (!is_empty(&rq)) {
			queue_temp = dequeue(&rq);
			if (p[t] == queue_temp) {
				enqueue(&lq, queue_temp);
				++t;
			}
			else
				push(&ms, queue_temp);
		}
		else {
			printf("불가능");
			free(ms.data);
			return;
		}
			
	}
	printf("가능");
	return 0;
}

int main()
{
	//int n = 10;		// 불가능
	//int testNumberSquence[MAX_QUEUE_SIZE] = { 3, 4, 6, 7, 8, 5, 10, 2, 1, 9 };

	//int n = 9;		// 가능
	//int testNumberSquence[MAX_QUEUE_SIZE] = { 1, 3, 2, 8, 7, 9, 6, 5, 4 };

	//int n = 3;		// 가능
	//int testNumberSquence[MAX_QUEUE_SIZE] = { 1, 3, 2 };

	//int n = 3;		// 불가능
	//int testNumberSquence[MAX_QUEUE_SIZE] = { 3, 1, 2 };

	//printf("생성 가능 여부 : ");

	//stack_su(n, testNumberSquence);


	int n;
	int* p;
	printf("n값 입력 : ");
	scanf("%d", &n);

	p = (int*)malloc(sizeof(int) * n);
	printf("배열 입력 : ");

	for (int i = 0; i < n; ++i) {
		scanf("%d", &p[i]);
	}

	printf("생성 가능 여부 : ");

	stack_su(n, p);

	free(p);
}

#endif