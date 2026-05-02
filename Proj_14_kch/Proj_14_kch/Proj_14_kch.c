#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

#define MAX_ELEMENT (SIZE + 1)
typedef struct TreeNode {
	int weight;
	char ch;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;
typedef TreeNode* element;
typedef struct {
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

void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);
	//트리를거슬러올라가면서부모노드와비교하는과정
	while ((i != 1) && (item->weight < h->heap[i / 2]->weight)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; //새로운노드를삽입
}

element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;
	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//현재노드의자식노드중더큰자식노드를찾는다.
		if ((child < h->heap_size) && (h->heap[child]->weight > h->heap[child + 1]->weight))
			child++;
		if (temp->weight <= h->heap[child]->weight) break;
		//한단계아래로이동
		h->heap[parent] = h->heap[child];
		parent = child;//인덱스변경
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//void heap_sort(element* list, element* sorted_list, int size)
//{
//	int i;
//	HeapType* h;
//	h = create();
//	init(h);
//	for (i = 0; i < size; i++) {
//		insert_max_heap(h, list[i]);
//	}
//	for (i = (size - 1); i >= 0; i--) {
//		sorted_list[i] = delete_max_heap(h);
//	}
//	free(h);
//}
//
//void selection_sort(element* list, element* sorted_list, int size)
//{
//	int i, j, least, temp;
//
//	for (i = 0; i < size; i++) {
//		sorted_list[i] = list[i];
//	}
//
//	for (i = 0; i < size - 1; i++) {
//		least = i;
//		for (j = i + 1; j < size; j++) {
//			if (sorted_list[j] < sorted_list[least]) {
//				least = j;
//			}
//		}
//		temp = sorted_list[i];
//		sorted_list[i] = sorted_list[least];
//		sorted_list[least] = temp;
//	}
//}

TreeNode* make_tree(TreeNode* left, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->left = left;
	node->right = right;
	node->ch = 0;
	node->weight = 0;
	if (left && right)
		node->weight = left->weight + right->weight;
	return node;
}

void destroy_tree(TreeNode* root) {
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

int is_leaf(TreeNode* root) {
	return !(root->left) && !(root->right);
}

void print_array(int codes[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d", codes[i]);
	printf("\n");
}

void print_codes(TreeNode* root, int codes[], int top)
{
	// 1을 저장하고 순환호출한다.
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	// 0을 저장하고 순환호출한다.
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}
	// 단말노드이면 코드를 출력한다.
	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

TreeNode* make_huffman_tree(int freq[], char ch_list[], int n)
{
	int i;
	TreeNode* node, * x;
	HeapType* heap;
	element e1, e2;
	int codes[100];
	int top = 0;
	heap = create();
	init(heap);
	for (i = 0; i < n; i++) { // 모든 문자에 대한 min heap 생성
		node = make_tree(NULL, NULL);
		node->ch = ch_list[i];
		node->weight = freq[i];
		insert_min_heap(heap, node);
	}
	for (i = 1; i < n; i++) { //최소노드 두개 노드 삭제 후 합친 1개 노드 추가(n-1번 반복)
		// 최소값을 가지는 두개의 노드를 삭제
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		// 두개의 노드를 합친다.
		x = make_tree(e1, e2); //왼쪽 작은값, 오른쪽 두번째 작은 값
		printf("%d+%d->%d \n", e1->weight, e2->weight, x->weight);
		insert_min_heap(heap, x);
	}
	x = delete_min_heap(heap); // 최종 트리
	printf("\n문자별 허프만 코드\n");
	print_codes(x, codes, top);
	free(heap);

	return x;
}

void huffman_decode(TreeNode* root, char* str) {
	printf("Decode %s\n", str);
	TreeNode* curr = root;
	char temp_bits[100];
	int bit_idx = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		temp_bits[bit_idx++] = str[i];
		temp_bits[bit_idx] = '\0';

		if (str[i] == '1') curr = curr->left;
		else curr = curr->right;

		if (is_leaf(curr)) {
			printf("%s ==> %c\n", temp_bits, curr->ch);
			curr = root;
			bit_idx = 0;
		}
	}
	if (curr != root) {
		printf("%s ==> 입력 문자열 모두 스캔 후 디코딩 미완성\n", temp_bits);
	}
	printf("\n");
}

int main()
{
	char ch_list[] = { 's', 'i', 'n', 't', 'e' };
	int freq[] = { 4, 6, 8, 12, 15 };
	TreeNode* head;
	printf("허프만 코드를 위한 트리 생성\n");
	char* str = "1110101010000101";
	head = make_huffman_tree(freq, ch_list, 5);
	printf("\n허프만 코드를 이용한 디코딩 :\n");
	huffman_decode(head, str);
	printf("\n허프만 코드를 이용한 디코딩 :\n");
	char* str2 = "11111111111";
	huffman_decode(head, str2);
	destroy_tree(head);
	return 0;
}