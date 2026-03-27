#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROB 1 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
#if PROB == 1
// 1번 문제를 해결하기 위한 프로그램 작성

#define MAX_STACK_SIZE 100
//typedef struct {
//	char operator;
//	int operand;
//}element;

typedef int element;

typedef struct {
	element* data;
	int capacity;
	int top;
}StackTypeInt;

void init_stack(StackTypeInt* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_empty(StackTypeInt* s) {
	return (s->top == -1);
}

int is_full(StackTypeInt* s) {
	return (s->top == (s->capacity - 1));
}

void push(StackTypeInt* s, element item)
{
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
}

element pop(StackTypeInt* s)
{
	if (is_empty(s)) {
		exit(1);
	}
	else
		return s->data[(s->top)--];
}
//-----------------------------------------------
typedef struct {
	char* data;
	int capacity;
	int top;
}StackTypeChar;

void init_stackc(StackTypeChar* s)
{
	s->top = -1;
	s->capacity = 1;
	s->data = (char*)malloc(s->capacity * sizeof(char));
}

int is_emptyc(StackTypeChar* s) {
	return (s->top == -1);
}

int is_fullc(StackTypeChar* s) {
	return (s->top == (s->capacity - 1));
}

void pushc(StackTypeChar* s, char item)
{
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (char*)realloc(s->data, s->capacity * sizeof(char));
	}
	s->data[++(s->top)] = item;
}

char popc(StackTypeChar* s)
{
	if (is_empty(s)) {
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

char peekc(StackTypeChar* s)
{
	if (is_emptyc(s)) {
		exit(1);
	}
	else
		return s->data[s->top];
}

int prec(char op) {
	switch (op) {
	case '(': case ')': return 0;
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	}
	return -1;
}

void compute(const char* in)
{
	StackTypeInt s;
	StackTypeChar c;
	char ch;
	char ch_in;
	int num = 0, len = strlen(in);
	int first, second;
	int result;
	int has_num = 0;
	init_stack(&s);
	init_stackc(&c);

	for (int i = 0; i <= len; ++i) {
		ch = in[i];

		if (ch >= '0' && ch <= '9') {
			num = num * 10 + (ch - '0');
			has_num = 1;
			continue;
		}

		if (has_num) {
			push(&s, num);
			printf(" %d", num);
			num = 0;
			has_num = 0;
		}

		if (ch == '\0' || ch == ' ') continue;
		
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			while (!is_emptyc(&c) && peekc(&c) != '(' && prec(peekc(&c)) >= prec(ch)) {
				ch_in = popc(&c);
				printf(" %c", ch_in);

				second = pop(&s);
				first = pop(&s);
				if (ch_in == '+') push(&s, first + second);
				else if (ch_in == '-') push(&s, first - second);
				else if (ch_in == '*') push(&s, first * second);
				else if (ch_in == '/') push(&s, first / second);
			}
			pushc(&c, ch);
		}
		else if (ch == '(') {
			pushc(&c, ch);
		}
		else if (ch == ')') {
			while (peekc(&c) != '(') {
				ch_in = popc(&c);
				printf(" %c", ch_in);
				second = pop(&s);
				first = pop(&s);
				if (ch_in == '+') push(&s, first + second);
				else if (ch_in == '-') push(&s, first - second);
				else if (ch_in == '*') push(&s, first * second);
				else if (ch_in == '/') push(&s, first / second);
			}
			if (!is_emptyc(&c)) popc(&c);
		}
	}

	while (!is_emptyc(&c)) {
		ch_in = popc(&c);
		printf(" %c", ch_in);
		second = pop(&s);
		first = pop(&s);
		if (ch_in == '+') 
			push(&s, first + second);
		else if (ch_in == '-') 
			push(&s, first - second);
		else if (ch_in == '*') 
			push(&s, first * second);
		else if (ch_in == '/') 
			push(&s, first / second);
	}

	result = pop(&s);
	if (is_empty(&s))
		printf("\n연산 결과 : %d", result);
	else
		printf("\n수식 오류");
}

int main()
{
	char* expr = "100 + 11 * 20 * (20 + 10) / 100 + 5 -3";	// 문제 파일에는 11과 20 사이의 *가 빠져있음(출력 예시엔 정상적으로 포함되어있음)
	//char* expr = "30 - 25 * (2 3 * 3)";					// 수식오류 테스트를 위한 수식
	printf("중위표기 수식 : %s\n후위표기 수식 :", expr);

	compute(expr);

	return 0;
}

#elif PROB == 2
// 2번 문제를 해결하기 위한 프로그램 작성



#endif