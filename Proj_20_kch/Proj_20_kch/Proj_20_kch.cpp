#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 10000 // 해싱 테이블의 크기
// 적재율 조절을 위한 SIZE 설정 (0.1, 0.2, 0.5 등에 따라 main에서 변경 가능)
#define SIZE (TABLE_SIZE / 2) 
#define SEARCH_COUNT 1000000

typedef struct {
    int key;
} element;

struct list {
    element item;
    struct list* link;
};

struct list** Chash_table; // 체이닝 기법 테이블
element* Lhash_table;      // 선형 기법 테이블

// 1. 테이블 초기화 함수 구현
void init_Lhash_table(element ht[], int size) {
    for (int i = 0; i < size; i++) {
        ht[i].key = -1; // -1을 빈 상태(empty)로 정의
    }
}

void init_Chash_table(struct list* ht[], int size) {
    for (int i = 0; i < size; i++) {
        ht[i] = NULL;
    }
}

// 2. 이중 해시 등에 사용될 소수 구하기 함수 구현
int get_prime_number(int size) {
    int i, j, is_prime;
    for (i = size - 1; i > 1; i--) {
        is_prime = 1;
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) return i;
    }
    return 3;
}

// 기본 해시 함수 (제산 함수)
int hash_function(int key) {
    return abs(key) % TABLE_SIZE;
}

// 3. 메인 함수 이름에 맞춘 선형 기법(또는 이중해시) 구현
void hash_linear_add(element item, element ht[], int h_prime) {
    int i, hash_value;
    hash_value = i = hash_function(item.key);

    int step = 1;

    while (ht[i].key != -1) {
        if (ht[i].key == item.key) {
            return; // 중복 키는 무시
        }
        i = (i + step) % TABLE_SIZE;
        if (i == hash_value) {
            return; // 테이블 가득 참
        }
    }
    ht[i] = item;
}

void hash_linear_search(element item, element ht[], int h_prime) {
    int i, hash_value;
    hash_value = i = hash_function(item.key);
    int step = 1;

    // 빈 칸을 만나더라도 테이블을 한 바퀴 다 돌 때까지는 계속 찾도록 제어
    do {
        if (ht[i].key == item.key) {
            return; // 탐색 성공
        }
        i = (i + step) % TABLE_SIZE;
    } while (i != hash_value); // 출발 위치로 다시 돌아올 때까지 계속 순회
}

// 4. 체이닝 기법 구현
void hash_chain_add(element item, struct list* ht[]) {
    int hash_value = hash_function(item.key);
    struct list* ptr;
    struct list* node_before = NULL;
    struct list* node = ht[hash_value];

    for (; node; node_before = node, node = node->link) {
        if (node->item.key == item.key) {
            return; // 이미 존재하면 무시
        }
    }

    ptr = (struct list*)malloc(sizeof(struct list));
    ptr->item = item;
    ptr->link = NULL;

    if (node_before)
        node_before->link = ptr;
    else
        ht[hash_value] = ptr;
}

void hash_chain_search(element item, struct list* ht[]) {
    struct list* node;
    int hash_value = hash_function(item.key);

    for (node = ht[hash_value]; node; node = node->link) {
        if (node->item.key == item.key) {
            return; // 탐색 성공
        }
    }
}

int main(void)
{
    int s_time, e_time;
    int h_prime;
    element e;

    Lhash_table = (element*)malloc(sizeof(element) * TABLE_SIZE);
    Chash_table = (struct list**)malloc(sizeof(struct list*) * TABLE_SIZE);

    init_Lhash_table(Lhash_table, TABLE_SIZE);
    init_Chash_table(Chash_table, TABLE_SIZE);

    srand(100);
    h_prime = get_prime_number(TABLE_SIZE);

    // 데이터 삽입 (적재율만큼)
    for (int i = 0; i < SIZE; i++) {
        e.key = rand();
        hash_linear_add(e, Lhash_table, h_prime);
        hash_chain_add(e, Chash_table);
    }

    // --- 선형 기법 테스트 ---
    srand(200);
    s_time = clock();
    for (int i = 0; i < SEARCH_COUNT; i++) {
        e.key = rand();
        hash_linear_search(e, Lhash_table, h_prime);
    }
    e_time = clock();

    printf("선형기법\n");
    printf("적재율 %f 인경우 %d회 검색 시 소요 시간 %d\n",
        (float)SIZE / TABLE_SIZE,
        SEARCH_COUNT, (int)(e_time - s_time));

    // --- 체인 기법 테스트 ---
    srand(200);
    s_time = clock();
    for (int i = 0; i < SEARCH_COUNT; i++) {
        e.key = rand();
        hash_chain_search(e, Chash_table);
    }
    e_time = clock();

    printf("체인기법\n");
    printf("적재율 %f 인경우 %d회 검색 시 소요 시간 %d\n",
        (float)SIZE / TABLE_SIZE,
        SEARCH_COUNT, (int)(e_time - s_time));

    free(Lhash_table);
    free(Chash_table);

    return 0;
}