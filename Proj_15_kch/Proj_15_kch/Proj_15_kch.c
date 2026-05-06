#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_WARNINGS

#define PROB 2 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성
#define MAX_QUEUE_SIZE 1000
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

#define MAX_VERTICES 50
typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
// 그래프초기화
void init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// 정점삽입연산
void set_vertex(GraphType* g, int n)
{
	if (n > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n = n;
}
// 간선삽입연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점번호오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
void printf_graph_matrix(GraphType* g)
{
	int r, c, i;
	printf("그래프 행렬 출력\n");
	printf("   |");
	for (i = 0; i < g->n; ++i) {
		printf("%2d ", i);
	}
	printf("\n-------------------------------------\n");
	for (r = 0; r < g->n; r++) {
		printf("%2d |", r);
		for (c = 0; c < g->n; c++) {
			printf(" %d ", g->adj_mat[r][c]);
		}
		printf("\n");
	}
	printf("\n");
}
void dfs_mat(GraphType* g, int v, int visited[])
{
	int w;
	visited[v] = 1;// 정점v의방문표시
	printf("[%d] -> ", v);// 방문한정점출력
	for (w = 0; w < g->n; w++) // 인접정점탐색
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w, visited);//정점w에서DFS 새로시작
}
void bfs_mat(GraphType* g, int v, int visited[])
{
	int w;
	QueueType q;
	init_queue(&q); // 큐초기화
	visited[v] = 1; // 정점v 방문표시
	printf("[%d] -> ", v);
	enqueue(&q, v);// 시작정점을큐에저장
	while (!is_empty(&q)) {
		v = dequeue(&q);// 큐에정점추출
		for (w = 0; w < g->n; w++)// 인접정점탐색
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = 1; // 방문표시
				printf("[%d] -> ", w);
				enqueue(&q, w); // 방문한정점을큐에저장
			}
	}
}
int main(void)
{
	GraphType* g;
	int i;
	int visited[MAX_VERTICES];
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	//그래프 초기화 및 간선 추가 : 에지 u, v가 입력되면 (u,v), (v,u)에 모두 간선 추가
	set_vertex(g, 11); // 정점의 개수 설정
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	//print matrix of graph
	printf_graph_matrix(g);
	//깊이 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_mat(g, 0, visited);
	printf("\n\n");
	//너비 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_mat(g, 0, visited);
	printf("\n");
	free(g);
	return 0;
}
#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성
#define MAX_QUEUE_SIZE 1000
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

#define MAX_VERTICES 50
typedef struct GraphNode
{
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;
// 그래프 초기화
void init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}
// 정점 삽입 연산
void set_vertex(GraphType* g, int n) {
	if (n > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n = n;
}
// 간접 삽입 연산, v를 u의 인접 리스트에 삽입한다
void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;

	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = u;
	node->link = g->adj_list[v];
	g->adj_list[v] = node;
}
void print_adj_list(GraphType* g) {
	for (int i = 0; i < g->n; ++i) {
		GraphNode* p = g->adj_list[i];
		printf(" %2d :", i);
		while (p != NULL) {
			printf(" %2d ->", p->vertex);
			p = p->link;
		}
		printf(" NULL\n");
	}
}
void dfs_list(GraphType* g, int v, int visited[])
{
	GraphNode* w;
	visited[v] = 1; // 정점v의방문표시
	printf("[%d] -> ", v);// 방문한정점출력
	for (w = g->adj_list[v]; w; w = w->link)// 인접정점탐색
		if (!visited[w->vertex])
			dfs_list(g, w->vertex, visited); //정점w에서DFS 새로시작
}
void bfs_list(GraphType* g, int v, int visited[])
{
	GraphNode* w;
	QueueType q;
	init_queue(&q); // 큐초기화
	visited[v] = 1; // 정점v 방문표시
	printf("[%d] -> ", v);
	enqueue(&q, v);// 시작정점을큐에저장
	while (!is_empty(&q)) {
		v = dequeue(&q);// 큐에저장된정점선택
		for (w = g->adj_list[v]; w; w = w->link) //인접정점탐색
			if (!visited[w->vertex]) {// 미방문정점탐색
				visited[w->vertex] = 1; // 방문표시
				printf("[%d] -> ", w->vertex);
				enqueue(&q, w->vertex);//정점을큐에삽입
			}
	}
}
int main(void)
{
	GraphType* g;
	int i;
	int visited[MAX_VERTICES];
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	//그래프 초기화 및 간선 추가, 에지 u, v가 입력되면 (u,v), (v,u)에 모두 간선 추가
	set_vertex(g, 11); //정점의 개수 설정
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 1, 3);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 7);
	insert_edge(g, 4, 8);
	insert_edge(g, 5, 6);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 10);
	insert_edge(g, 7, 9);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	// 그래프 출력
	print_adj_list(g);
	// 깊이 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("깊이 우선 탐색\n");
	dfs_list(g, 0, visited);
	printf("\n\n");
	// 너비 우선 탐색
	for (i = 0; i < MAX_VERTICES; i++) visited[i] = 0;
	printf("너비 우선 탐색\n");
	bfs_list(g, 0, visited);
	printf("\n");
	free(g);
	return 0;
}
#endif