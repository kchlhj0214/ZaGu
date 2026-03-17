#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define PROB 2 // 다항식 저장 방법 선택
#if PROB == 1
// 배열을 이용한 다항식 표현 및 덧셈, 곱셈
#define MAX_TERM 101 //최대 차수 100
typedef struct polynomial {
    int degree;
    int coef[MAX_TERM];
}POLY;
// 여기에 필요한 함수 구현

POLY addPoly(const POLY a, const POLY b)
{
    POLY addResult;
    int aDegree = a.degree;
    int bDegree = b.degree;
    if (a.degree >= b.degree) {                 // a 차수 > b 차수
        addResult.degree = a.degree;

        for (int i = 0; i <= a.degree; ++i) {
            if (aDegree - bDegree != 0) {
                addResult.coef[i] = a.coef[i];
                --aDegree;
            }
            else {
                addResult.coef[i] = a.coef[i] + b.coef[b.degree - bDegree];
                --aDegree;
                --bDegree;
            }
        }
    }
    else {
        addResult.degree = b.degree;

        for (int i = 0; i <= b.degree; ++i) {
            if (bDegree - aDegree != 0) {
                addResult.coef[i] = b.coef[i];
                --bDegree;
            }
            else {
                addResult.coef[i] = a.coef[i] + b.coef[i];
                --aDegree;
                --bDegree;
            }
        }
    }
    return addResult;
}

POLY mulPoly(const POLY a, const POLY b)
{
    POLY mulResult = {0};
    mulResult.degree = a.degree + b.degree;
    int mulDegree = 0;

    for (int i = 0; i <= a.degree; ++i) {
        for (int j = 0; j <= b.degree; ++j) {
            mulDegree = (a.degree - i) + (b.degree - j);
            mulResult.coef[8 - mulDegree] += a.coef[i] * b.coef[j];
        }
    }
    return mulResult;
}

void printPoly(const char* str, POLY p)
{
    printf("%s=", str);
    int printDegree = p.degree;
    for (int i = 0; i <= p.degree; ++i) {
        if (p.coef[i] >= 0 && i != 0)
            printf(" +");
        else
            printf(" ");
        printf("%dX^%d", p.coef[i], printDegree);
        --printDegree;
   }
   printf("\n");
}

int main(void) {
    POLY a = { 5, {3, 0, 4, -2, 1, 7} }; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
    POLY b = { 3, {4, 2, -6, -3} }; // b(x) = 4x3 + 2x2 - 6x - 3
    POLY c, d; //for result

    printPoly("a(x)", a);
    printPoly("b(x)", b);
    c = addPoly(a, b);
    printPoly("c(x) = a(x) + b(x) ", c);
    d = mulPoly(a, b);
    printPoly("d(x) = a(x) x b(x) ", d);
    return 0;
}
#elif PROB == 2
#define MAX_TERM 101 //최대 차수 100
typedef struct term { int coef; int exp; } TERM;
typedef struct polynomial {
    int num_of_terms;
    TERM terms[MAX_TERM];
}POLY;
// 여기에 필요한 함수 구현

POLY addPoly(const POLY a, const POLY b)            // 여기부터 계속-------------------------------------------------
{
    POLY addResult;
    addResult.num_of_terms = 0;
    int j = 0;
    int addResult_exp = 0;
    int max = MAX(a.terms[0].exp, b.terms[0].exp);
    for (int i = 0; i < max + 1; ++i) {
        if (a.terms[i].exp > b.terms[j].exp) {
            addResult.terms[addResult_exp].coef = a.terms[i].coef;
            addResult.terms[addResult_exp].exp = a.terms[i].exp;
            ++addResult_exp;
        }
        else if (a.terms[i].exp == b.terms[j].exp) {
            addResult.terms[addResult_exp].coef = a.terms[i].coef + b.terms[i].coef;
            addResult.terms[addResult_exp].exp = a.terms[i].exp + b.terms[i].exp;
            ++addResult_exp;
        }
        else {
            addResult.terms[addResult_exp].coef = b.terms[i].coef;
            addResult.terms[addResult_exp].exp = b.terms[i].exp;
            ++addResult_exp;
        }
    }
    
}

POLY mulPoly(const POLY a, const POLY b)
{

}

void printPoly(const char* str, POLY p)
{

}

int main(void) {
    POLY a = { 5, {3,5, 4,3, -2,2, 1,1,  7,0} }; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
    POLY b = { 4, {4,3, 2,2, -6,1, -3,0} }; // b(x) = 4x3 + 2x2 - 6x - 3
    POLY c, d; //for result
    printPoly("a(x)", a);
    printPoly("b(x)", b);
    c = addPoly(a, b);
    printPoly("c(x) = a(x) + b(x) ", c);
    d = mulPoly(a, b);
    printPoly("d(x) = a(x) x b(x) ", d);
    return 0;
}
#elif PROB == 3
// 0이 아닌 계수를 연결리스트로 다항식 표현
typedef struct poly {
    int coef;
    int exp;
    struct poly* link;
}POLY;
// 여기에 필요한 함수 구현
int main(void) {
    POLY* a = NULL; // a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
    POLY* b = NULL; // b(x) = 4x3 + 2x2 - 6x - 3
    POLY* c = NULL, * d = NULL, * tmp = NULL; //for result
    //A 초기화 a(x) = 3x5 + 4x3 - 2x2 + 1x + 7
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    tmp->coef = 3; tmp->exp = 5; tmp->link = NULL;
    a = add(a, tmp);
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    - 3
        tmp->coef = 4; tmp->exp = 3; tmp->link = NULL;
    a = add(a, tmp);
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    tmp->coef = -2; tmp->exp = 2; tmp->link = NULL;
    a = add(a, tmp);
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    tmp->coef = 1; tmp->exp = 1; tmp->link = NULL;
    a = add(a, tmp);
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    tmp->coef = 7; tmp->exp = 0; tmp->link = NULL;
    a = add(a, tmp);
    printPoly("a(x)", a);
    //B 초기화  b(x) = 4x3 + 2x2 - 6x - 3
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    tmp->coef = 4; tmp->exp = 3; tmp->link = NULL;
    b = add(b, tmp);
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    tmp->coef = 2; tmp->exp = 2; tmp->link = NULL;
    b = add(b, tmp);
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    tmp->coef = -6; tmp->exp = 1; tmp->link = NULL;
    b = add(b, tmp);
    tmp = (POLY*)malloc(sizeof(POLY));
    if (tmp == NULL) { printf("Memory Allocation Error"); exit(-1); }
    tmp->coef = -3; tmp->exp = 0; tmp->link = NULL;
    b = add(b, tmp);
    printPoly("b(x)", b);
    // 다항식 합
    c = addPoly(a, b);
    printPoly("c(x) = a(x) + b(x) ", c);
    // 다항식 곱
    d = mulPoly(a, b);
    printPoly("d(x) = a(x) x b(x) ", d);
    // 연결리스트 삭제
    del(a); del(b); del(c); del(d);
    return 0;
}
#endif