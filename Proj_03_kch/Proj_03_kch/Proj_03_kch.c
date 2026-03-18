#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define PROB 3 // 다항식 저장 방법 선택
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

POLY addPoly(const POLY a, const POLY b)
{
    POLY addResult;
    addResult.num_of_terms = 0;
    int n = 0;
    int m = 0;
    int addResult_i = 0;
    int max = 0;
    if (a.terms[0].exp >= b.terms[0].exp)
        max = a.terms[0].exp;
    else
        max = b.terms[0].exp;
    for (int i = 0; i < max + 1; ++i) {
        if (m > sizeof(a.num_of_terms)) {                           // 두 다항식의 끝항이 다를경우의 예외처리
            addResult.terms[addResult_i].coef = b.terms[n].coef;
            addResult.terms[addResult_i].exp = b.terms[n].exp;
            ++addResult_i;
            ++addResult.num_of_terms;
            ++n;
        }
        else if (n > sizeof(b.num_of_terms)) {                      // 두 다항식의 끝항이 다를경우의 예외처리
            addResult.terms[addResult_i].coef = a.terms[m].coef;
            addResult.terms[addResult_i].exp = a.terms[m].exp;
            ++addResult_i;
            ++addResult.num_of_terms;
            ++m;
        }
        else if (a.terms[m].exp > b.terms[n].exp) {
            addResult.terms[addResult_i].coef = a.terms[m].coef;
            addResult.terms[addResult_i].exp = a.terms[m].exp;
            ++addResult_i;
            ++addResult.num_of_terms;
            ++m;
        }
        else if (a.terms[m].exp == b.terms[n].exp) {
            if (a.terms[m].coef + b.terms[n].coef != 0) {
                addResult.terms[addResult_i].coef = a.terms[m].coef + b.terms[n].coef;
                addResult.terms[addResult_i].exp = a.terms[m].exp;
                ++addResult_i;
                ++addResult.num_of_terms;
            }
            ++n;
            ++m;
        }
        else {
            addResult.terms[addResult_i].coef = b.terms[n].coef;
            addResult.terms[addResult_i].exp = b.terms[n].exp;
            ++addResult_i;
            ++addResult.num_of_terms;
            ++n;
        }
    }
    return addResult;
}

POLY mulPoly(const POLY a, const POLY b)
{
    POLY mulResult;
    POLY tempResult = { 0 };
    tempResult.num_of_terms = a.terms[0].exp + b.terms[0].exp + 1;
    for (int i = 0; i < tempResult.num_of_terms; ++i)
        tempResult.terms[i].exp = 8 - i;

    for (int i = 0; i < a.num_of_terms; ++i) {
        for (int j = 0; j < b.num_of_terms; ++j) {
            tempResult.terms[8 - (a.terms[i].exp + b.terms[j].exp)].coef += a.terms[i].coef * b.terms[j].coef;
            tempResult.terms[8 - (a.terms[i].exp + b.terms[j].exp)].exp = a.terms[i].exp + b.terms[j].exp;
        }
    }
    int n = 0;
    for (int i = 0; i < tempResult.num_of_terms; ++i) {
        if (tempResult.terms[i].coef != 0) {
            mulResult.terms[n].coef = tempResult.terms[i].coef;
            mulResult.terms[n].exp = tempResult.terms[i].exp;
            ++n;
        }
    }
    mulResult.num_of_terms = n;
    return mulResult;
}

void printPoly(const char* str, POLY p)
{
    printf("%s=", str);
    for (int i = 0; i < p.num_of_terms; ++i) {
        if (p.terms[i].coef >= 0 && i != 0)
            printf(" +");
        else
            printf(" ");
        printf("%dX^%d", p.terms[i].coef, p.terms[i].exp);
    }
    printf("\n");
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

POLY* add(POLY* head, POLY* newNode)
{
    if (head == NULL)
        return newNode;

    POLY* curr = head;
    while (curr->link != NULL)
        curr = curr->link;
    curr->link = newNode;

    return head;
}

POLY* addPoly(POLY* a, POLY* b) {
    POLY* addResult = NULL;
    POLY* currA = a;
    POLY* currB = b;

    while (currA != NULL && currB != NULL) {
        POLY* tmp = (POLY*)malloc(sizeof(POLY));
        tmp->link = NULL;

        if (currA->exp > currB->exp) {
            tmp->coef = currA->coef;
            tmp->exp = currA->exp;
            currA = currA->link;
        }
        else if (currA->exp < currB->exp) {
            tmp->coef = currB->coef;
            tmp->exp = currB->exp;
            currB = currB->link;
        }
        else { 
            int sum = currA->coef + currB->coef;
            if (sum != 0) {
                tmp->coef = sum;
                tmp->exp = currA->exp;
            }
            else {
                free(tmp);
                tmp = NULL;
            }
            currA = currA->link;
            currB = currB->link;
        }

        if (tmp != NULL) addResult = add(addResult, tmp);
    }

    while (currA != NULL) {
        POLY* tmp = (POLY*)malloc(sizeof(POLY));
        tmp->coef = currA->coef;
        tmp->exp = currA->exp;
        tmp->link = NULL;
        addResult = add(addResult, tmp);
        currA = currA->link;
    }

    while (currB != NULL) {
        POLY* tmp = (POLY*)malloc(sizeof(POLY));
        tmp->coef = currB->coef;
        tmp->exp = currB->exp;
        tmp->link = NULL;
        addResult = add(addResult, tmp);
        currB = currB->link;
    }

    return addResult;
}

POLY* mulPoly(POLY* a, POLY* b)
{
    POLY* mulResult = NULL;
    POLY* curResult = mulResult;
    POLY* prev = NULL;
    POLY* currA = a;
    POLY* currB = b;
    POLY* tmp = NULL;
    while (currA != NULL) {
        currB = b;
        while (currB != NULL) {
            tmp = (POLY*)malloc(sizeof(POLY));
            tmp->coef = currA->coef * currB->coef;
            tmp->exp = currA->exp + currB->exp;
            tmp->link = NULL;
            if (mulResult == NULL)
                mulResult = add(mulResult, tmp);
            else {
                curResult = mulResult;
                int found = 0;
                while (curResult != NULL) {
                    if (curResult->exp == tmp->exp) {       // 추가하는 항이 지수가 같은 항이면
                        curResult->coef += tmp->coef;
                        ++found;
                        break;
                    }
                    else if (curResult->exp <= tmp->exp) {  // 추가하는 항이 사이에 낀다면
                        tmp->link = curResult;
                        prev->link = tmp;
                        ++found;
                        break;
                    }
                    prev = curResult;
                    curResult = curResult->link;
                }
                if (found == 0) {                           // 추가하는 항이 맨 뒤에 온다면
                    prev->link = tmp;
                }
            }
            currB = currB->link;
        }
        currA = currA->link;
    }
    return mulResult;
}

void printPoly(const char* str, POLY* p)
{
    POLY* prt = p;
    printf("%s=", str);
    printf(" %dX^%d", prt->coef, prt->exp);
    prt = prt->link;
    while (prt != NULL) {
        if (prt->coef >= 0)
            printf(" +");
        else
            printf(" ");
        printf("%dX^%d", prt->coef, prt->exp);
        prt = prt->link;
    }
    printf("\n");
}

void del(POLY* head)
{
    POLY* erase = head;
    while (erase != NULL) {
        POLY* next = erase->link;
        free(erase);
        erase = next;
    }
}

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
    printPoly("a(x) ", a);
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
    printPoly("b(x) ", b);
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