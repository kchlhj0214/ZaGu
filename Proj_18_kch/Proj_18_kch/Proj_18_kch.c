#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int* sorted;

#define SIZE 100000 // 데이터크기를 변경하며 테스트

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) // 최솟값탐색
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);
	}
}

void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] > key; j--)
			list[j + 1] = list[j]; // 레코드의오른쪽이동
		list[j + 1] = key;
	}
}

void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i > 0; i--) {
		for (j = 0; j < i; j++) // 앞뒤의레코드를비교한후교체
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
void shell_sort(int list[], int n)   // n = size
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
			// 부분 리스트의개수는gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;
	// 분할 정렬된list의 합병
	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) sorted[k++] = list[i++];
		else sorted[k++] = list[j++];
	}
	if (i > mid) // 남아있는레코드의일괄복사
		for (l = j; l <= right; l++)
			sorted[k++] = list[l];
	else // 남아있는레코드의일괄복사
		for (l = i; l <= mid; l++)
			sorted[k++] = list[l];
	// 배열sorted[]의리스트를배열list[]로복사
	for (l = left; l <= right; l++)
		list[l] = sorted[l];
}
void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right)
	{
		mid = (left + right) / 2;              // 리스트의균등분할
		merge_sort(list, left, mid);     // 부분리스트정렬
		merge_sort(list, mid + 1, right);//부분리스트정렬
		merge(list, left, mid, right);    // 합병
	}
}

int partition(int list[], int left, int right) {
	int pivot, temp;
	int low, high;
	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);
	SWAP(list[left], list[high], temp);
	return high;
}
void quick_sort(int list[], int left, int right)
{
	if (left < right) {
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

#define BUCKETS 10
#define DIGITS 5
#define MAX_QUEUE_SIZE (SIZE + 10)

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
void init(QueueType* q)
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
void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	static QueueType queues[BUCKETS];		// 스택오버플로우 방지를 위해 전역변수로 선언
	for (b = 0; b < BUCKETS; b++) init(&queues[b]); // 큐들의 초기화
	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i] / factor) % 10], list[i]);
		for (b = i = 0; b < BUCKETS; b++)
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;
	}
}

void heapify(int list[], int n, int i) {
	int largest = i;          // 부모 노드
	int left = 2 * i + 1;     // 왼쪽 자식 노드
	int right = 2 * i + 2;    // 오른쪽 자식 노드
	int temp;

	// 왼쪽 자식이 부모보다 크다면
	if (left < n && list[left] > list[largest])
		largest = left;

	// 오른쪽 자식이 현재 가장 큰 값보다 크다면
	if (right < n && list[right] > list[largest])
		largest = right;

	// 가장 큰 값이 부모가 아니라면 교환 후 서브트리 재귀 호출
	if (largest != i) {
		SWAP(list[i], list[largest], temp);
		heapify(list, n, largest);
	}
}
void heap_sort(int list[], int n)
{
	int i, temp;

	// 1. 초기 배열을 최대 힙 구조로 만듦 (반복문은 내부 노드 끝에서부터 시작)
	for (i = n / 2 - 1; i >= 0; i--) {
		heapify(list, n, i);
	}

	// 2. 힙에서 하나씩 요소를 꺼내어 배열 뒤부터 정렬
	for (i = n - 1; i > 0; i--) {
		// 현재 루트(가장 큰 값)를 배열의 끝과 교환
		SWAP(list[0], list[i], temp);

		// 줄어든 힙 크기(i)만큼 다시 최대 힙 속성을 만족하도록 재조정
		heapify(list, i, 0);
	}
}

int main(void)
{
	int i, s_time, e_time;
	int* data = (int*)malloc(sizeof(int) * SIZE); // 각 정렬을 동일한 데이터로 테스트하기 위한 원데이터
		int* list = (int*)malloc(sizeof(int) * SIZE); // 원데이터 -> 정렬된 데이터
	sorted = (int*)malloc(sizeof(int) * SIZE); //병합정렬을 위한 추가 메모리로 글로벌 변수로 선언
		if (data == NULL || list == NULL || sorted == NULL) {
			printf("데이터 저장을 위한 메모리 할당 오류\n"); exit(-1);
		}
	printf("정렬 기법 비교 \n");
	printf("Data 크기 : %d \n\n", SIZE);
	srand(100);
	for (i = 0; i < SIZE; i++)
		// 난수 생성 및 출력 
		data[i] = rand();
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	selection_sort(list, SIZE); // 선택정렬 호출 
	// 난수 발생
	e_time = clock();
	printf("선택정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	insertion_sort(list, SIZE);
	e_time = clock();
	printf("삽입정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	bubble_sort(list, SIZE);
	e_time = clock();
	printf("버블정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	shell_sort(list, SIZE);
	e_time = clock();
	printf("셸정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	merge_sort(list, 0, SIZE - 1);
	e_time = clock();
	printf("병합정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	quick_sort(list, 0, SIZE - 1);
	e_time = clock();
	printf("퀵정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	heap_sort(list, SIZE);
	e_time = clock();
	printf("힙정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	memcpy(list, data, sizeof(int) * SIZE);
	s_time = clock();
	radix_sort(list, SIZE); // 기수정렬 호출 
	e_time = clock();
	printf("기수정렬 시간 : %d\n", e_time - s_time);
	if (SIZE <= 100) {
		for (i = 0; i < SIZE; i++)
			printf("%d ", list[i]);
		printf("\n\n");
	}
	free(data); free(list); free(sorted);
	return 0;
}
