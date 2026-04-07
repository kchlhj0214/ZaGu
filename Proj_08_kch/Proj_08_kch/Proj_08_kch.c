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
void add(SortedList* L, element item)
{
	if (is_full(L))
		return -1;

	for (int i = 0; i < L->size; ++i) {
		if (L->array[i] > item) {
			for (int k = L->size; k > i; --k) {
				L->array[k] = L->array[k - 1];
			}
			L->array[i] = item;
			L->size++;
			return;
		}
	}

	if (is_empty(L)) {
		L->array[0] = item;
		L->size++;
	}
	else {
		L->array[L->size] = item;
		L->size++;
	}
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
	for (int i = 0; i < L->size; ++i)
		L->array[i] = NULL;
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

		return 0;
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성

#define MAX_LIST_SIZE 100
typedef int element;
typedef { 

}  SortedList;
int main(void) {
	int item;
	char ch;
	SortedList list;
	SortedList* rList;
	//필요한 초기화 코드 추가

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

		return 0;
}

#endif