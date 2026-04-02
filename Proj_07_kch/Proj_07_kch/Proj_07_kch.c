#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
#define MAX_QUEUE_SIZE 5
typedef struct {
	char* c;
	int t;
}SCHEDULE;
typedef struct {
	int n;
	SCHEDULE s[6];
}CLASS_TIME;
typedef struct {
	char class_name[20];
	char professor_name[20];
	CLASS_TIME class_time;
}CLASS_INFO;

typedef CLASS_INFO element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// 공백상태검출함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// 포화상태검출함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형데큐출력함수
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) :\n", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("교과목명 : %s, 담당교수 : %s, 수업시간 : ", q->data[i].class_name, q->data[i].professor_name);
			for (int k = 0; k < q->data[i].class_time.n; ++k) {
				printf("%s요일 %d교시 ", q->data[i].class_time.s[k].c, q->data[i].class_time.s[k].t);
			}
			printf("\n");
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	else {
		printf("데큐가 비었음\n");
	}
	printf("\n");
}
// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// 삭제함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가공백상태입니다");
	return q->data[q->rear];
}

int main()
{
	DequeType queue;
	element data1 = { "자료구조","오황석", {4, {"화", 1, "화", 2, "수", 1, "수", 2}} };
	element data2 = { "컴퓨터구조","김경철",{4, {"월", 3, "월", 4, "목", 6, "목", 7}} };
	element data3 = { "선형대수","이용희",{3, {"월", 8, "월", 9, "금", 3}} };
	// { 과목명, 담당교수, 시간, {요일, 교시, 시간수만큼 반복}}}
	// 3학점 최대 6시간까지 저장할 수 있음
	init_deque(&queue); deque_print(&queue);
	add_front(&queue, data1); deque_print(&queue);
	add_rear(&queue, data2); deque_print(&queue);
	add_front(&queue, data3); deque_print(&queue);
	delete_rear(&queue); deque_print(&queue);
	delete_front(&queue); deque_print(&queue);
	delete_front(&queue); deque_print(&queue);
	delete_rear(&queue); deque_print(&queue);
	return 0;
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
#define MAX_QUEUE_SIZE 10
#define WORK_TIME 10000

typedef int element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} DequeType;
// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// 공백상태검출함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// 포화상태검출함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// 삭제함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}
void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}
element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가공백상태입니다");
	return q->data[q->rear];
}

typedef struct {
	int menu_code;
	int menu_count;
	int total_waiting_time;
}MENU;

typedef struct {
	int menu_code;
	int remain_time;
	int order_time;
	int fin_time;
}MENU_ORDERD;

void Hamburger_Simulator()
{
	int time = 0;
	int isBusyServer1 = 0;
	int isBusyServer2 = 0;
	MENU menu[5] = {0};

	 while (time < WORK_TIME) { // time을 1씩 증가시키면서
		if (time % 5 == 0) {// 새로운 손님 5시간 마다 도착하여 주문
			//주문을 생성하여 큐에 넣기
		}
		if (!isBusyServer1) { //놀고 있다가 새로운 서비스 시작
							...
		}
		else if (isBusyServer1 && server1.processing_time == 0) {//작업 끝남.  
							...
		}
		if (!isBusyServer2) { //놀고 있다가 새로운 서비스 시작
							 ...
						 }
		else if (isBusyServer2 && server2.processing_time == 0) {//작업 끝남.  
							 ...
		}
		// 시간 업데이트
		time++;
		// server1이 서비스 중이면 시간 1 감소
		// server2가 서비스 중이면 시간 1 감소
	}
	// 결과 출력
	printf("=========== Results ============\n");
	for (i = 0; i < 5; i++) {
		printf("MENU %d %d개 서비스, 누적대기시간 %d, 평균서비스시간 %f\n", ...);
	}
	printf("취소된 주문 %d 개\n", ...);
	printf("================================\n");
}

int main()
{
	Hamburger_Simulator();
}

#endif