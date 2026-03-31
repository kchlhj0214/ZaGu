#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
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
#define MAX_QUEUE_SIZE 1000000

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
void dead_people(int n, int k)
{
	QueueType q;
	init_queue(&q);
	int loop_num = 1;

	for (int i = 0; i < n; ++i)
		enqueue(&q, i + 1);

	while (!is_empty(&q)) {
		if (loop_num % 3 == 0) {

		}
		else {

		}
	}
}


int main()
{
	int n, k;
	printf("게임에 참여하는 사람의 수 n과 선택하는 k값 입력 : ");
	scanf_s("%d %d", &n, &k);
	printf("선택된 사람의 번호 :");
	dead_people(n, k);
		
}

#elif PROB == 3
// 3번 문제를 해결하기 위한 프로그램 작성



#endif