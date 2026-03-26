#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element *data;
	int capacity;
	int top;
}StackType;

void init_stack(StackType* s) 
{
	s->top = -1;
	s->capacity = 1;
	s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_empty(StackType* s) {
	return (s->top == -1);
}

int is_full(StackType* s) {
	return (s->top == (s->capacity - 1));
}

void push(StackType* s, element item)
{
	if (is_full(s)) {
		s->capacity *= 2;
		s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s)
{
	if (is_empty(s)) {
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

typedef struct {	// 왼쪽 괄호의 정보는 모두 저장하고 오른쪽 괄호의 정보는 오류인 괄호의 정보만 저장
	int pos;		// 괄호 위치
	char c;			// 괄호 종류
	int errnum;		// 1 = 정상, 2 = 왼쪽 괄호, 3 = 오른쪽 괄호, 4 = 양쪽 괄호
} pos_Save;

void check_matching(const char* in)
{
	StackType s;
	char ch, open_ch;
	int i, n = strlen(in);
	init_stack(&s);
	pos_Save ps[MAX_STACK_SIZE] = {0};
	int psnum = 0;						// pos_Save 배열을 관리하는 num
	int clear = 0;						// 0 = 오류 없음, 1 = 오류 있음

	for (int i = 0; i < n; ++i) {
		ch = in[i];
		switch (ch) {
			case '(': case '[': case '{':
				push(&s, ch);
				ps[psnum].pos = i;
				ps[psnum].c = ch;
				ps[psnum].errnum = 2;	// 기본 오류값 2로 설정(기본 1로 설정하고 나중에 2로 바꾸려면 훨씬 많은 정보를 저장해야하고 코드가 복잡해짐, 그때그때 1로 변경)
				++psnum;
				break;
			case ')': case ']': case '}':
				if (is_empty(&s)) {
					ps[psnum].pos = i;
					ps[psnum].c = ch;
					ps[psnum].errnum = 3;
					++psnum;
					clear = 1;
				}
				else {
					open_ch = pop(&s);
					if ((open_ch == '(' && ch != ')') ||
						(open_ch == '[' && ch != ']') ||
						(open_ch == '{' && ch != '}')) {
						ps[psnum].pos = i;
						ps[psnum].c = ch;
						ps[psnum].errnum = 4;
						clear = 1;
						for(int j = psnum - 1; ; --j)			// 양쪽 괄호 오류
							if (ps[j].errnum != 4) {
								ps[j].errnum = 4;
								break;
							}
						++psnum;
					}
					else if((open_ch == '(' && ch == ')') ||
							(open_ch == '[' && ch == ']') ||
							(open_ch == '{' && ch == '}')){
						for (int j = psnum - 1; j >=0 ; --j) {	// 만약 양쪽 괄호가 같다면 해당하는 왼쪽 괄호의 에러코드를 1(정상)로 변경
							if (ps[j].c == open_ch && ps[j].errnum == 2) {
								ps[j].errnum = 1;
								break;
							}
						}
					}
					break;
				}
		}
	}
	if (!is_empty(&s))		// 스택에 남은 데이터가 있다면 왼쪽 괄호 오류
		clear = 1;

	if (clear == 0) {
		printf("오류 없음");
	}
	else {
		int num = 0;
		for (int i = 0; i < n; ++i) {
			if (ps[num].errnum == 1)
				++num;
			if (i == ps[num].pos) {
				printf("^");
				++num;
			}
			else
				printf("-");
		}
		printf("\n");
		for (int i = 0; i <= psnum; ++i) {		// 오류인 괄호에 대한 정보 출력 후 해당 괄호의 오류코드를 1로 변경(괄호 불일치 검사시 중복 검사 되는 문제 방지)
			if (ps[i].errnum == 2) {
				printf("왼쪽 괄호 %c 오류 : 위치 %d\n", ps[i].c, ps[i].pos);
				ps[i].errnum = 1;
			}
			else if (ps[i].errnum == 3) {
				printf("오른쪽 괄호 %c 오류 : 위치 %d\n", ps[i].c, ps[i].pos);
				ps[i].errnum = 1;
			}
			else if (ps[i].errnum == 4) {
				for (int j = psnum; j >= 0; --j) {
					if (ps[j].errnum == 4) {
						printf("양쪽 괄호 %c 괄호와 %c 괄호 불일치 오류 : 위치 %d, %d\n", ps[i].c, ps[j].c, ps[i].pos, ps[j].pos);
						ps[i].errnum = 1;
						ps[j].errnum = 1;
						break;
					}
				}
			}
		}
	}
}

int main()
{
	for (int i = 0; i < 8; ++i)
		printf("0123456789");
	//char *p = "A(x) = 24.5 * ( x + func(x, y)) * ( r * r * 3.14 ) / [ 7%10* sqrt(25)];";		// 정상 수식
	//char* p = "A(x) = 24.5 * ( x + func(x, y)) * ({( r * r * 3.14 ) / [ 7%10* sqrt(25)];";	// 왼쪽 괄호 오류
	//char* p = "A(x) = 24.5 * ( x + func(x, y)) * ( r * r * 3.14 / [ 7%10* sqrt(25)])}));";	// 오른쪽 괄호 오류
	//char* p = "A(x) =({[ }])";																// 양쪽 괄호 오류
	char* p = "A(x) = 24.5 * ( x + func(x, y))] * ( r * r * 3.14 )) / [ 7%10* sqrt(25)];";
	printf("\n%s\n", p);

	check_matching(p);

	return 0;
}