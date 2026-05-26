#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS
#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
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


#endif
