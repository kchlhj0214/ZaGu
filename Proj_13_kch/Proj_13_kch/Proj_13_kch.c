#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

#define MAX_ELEMENT (SIZE + 1)
typedef int element;
typedef struct{
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType* create()
{
	return(HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);
	//트리를거슬러올라가면서부모노드와비교하는과정
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; //새로운노드를삽입
}

element delete_max_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//현재노드의자식노드중더큰자식노드를찾는다.
		if ((child < h->heap_size) && ((h->heap[child]) < h->heap[child + 1]))
			child++;
		if (temp >= h->heap[child])break;
		//한단계아래로이동
		h->heap[parent] = h->heap[child];
		parent = child;//인덱스변경
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void heap_sort(element* list, element* sorted_list, int size)
{
	int i;
	HeapType* h;
	h = create();
	init(h);
	for (i = 0; i < size; i++) {
		insert_max_heap(h, list[i]);
	}
	for (i = (size - 1); i >= 0; i--) {
		sorted_list[i] = delete_max_heap(h);
	}
	free(h);
}

void selection_sort(element* list, element* sorted_list, int size)
{
	int i, j, least, temp;

	for (i = 0; i < size; i++) {
		sorted_list[i] = list[i];
	}

	for (i = 0; i < size - 1; i++) {
		least = i;
		for (j = i + 1; j < size; j++) {
			if (sorted_list[j] < sorted_list[least]) {
				least = j;
			}
		}
		temp = sorted_list[i];
		sorted_list[i] = sorted_list[least];
		sorted_list[least] = temp;
	}
}

int main()
{
	element* list, * sorted_list; //원데이터와 정렬된 데이터 각각 저장용
	int i, s_time, e_time;
	srand(100);
	list = (element*)malloc(sizeof(element) * SIZE);
	sorted_list = (element*)malloc(sizeof(element) * SIZE);
	for (i = 0; i < SIZE; i++)  list[i] = rand();
	printf("정수형 데이터 %d개 정렬 \n", SIZE);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++)  printf("%d ", list[i]);
		printf("\n\n");
	}
	s_time = clock();
	heap_sort(list, sorted_list, SIZE);
	e_time = clock();
	printf("Heap Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i]);
		printf("\n\n");
	}
	s_time = clock();
	selection_sort(list, sorted_list, SIZE);
	e_time = clock();
	printf("Selection Sort 걸린 시간 : %d msec\n", e_time - s_time);
	if (SIZE < 100) {
		for (int i = 0; i < SIZE; i++) printf("%d ", sorted_list[i]);
		printf("\n");
	}
	return 0;
}