#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct STACK
{
    int *elems; //申请内存用于存放栈的元素
    int max;    //栈能存放的最大元素个数
    int pos;    //栈实际已有元素个数，栈空时pos=0;
} STACK;
void initSTACK(STACK *const p, int m);               //初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK &s);      //用栈s初始化p指向的栈
int size(const STACK *const p);                      //返回p指向的栈的最大元素个数max
int howMany(const STACK *const p);                   //返回p指向的栈的实际元素个数pos
int getelem(const STACK *const p, int x);            //取下标x处的栈元素
STACK *const push(STACK *const p, int e);            //将e入栈，并返回p
STACK *const pop(STACK *const p, int &e);            //出栈到e，并返回p
STACK *const assign(STACK *const p, const STACK &s); //赋s给p指的栈,并返回p
void print(const STACK *const p);                    //打印p指向的栈
void destroySTACK(STACK *const p);                   //销毁p指向的栈

int main(int argc, char const *argv[])
{
    printf("%d\n", argc);
    STACK *const p = (STACK *)malloc(sizeof(STACK));
    int i = 1;
    while (i < argc)
    {
        printf("debug:%s  ", argv[i]);
        if (strcmp(argv[i], "-S") == 0)
        {
            printf("S  ");
            i++;
            int n = atoi(argv[i]);
            initSTACK(p, n);
            i++;
            printf("%d  ", n);
            continue;
        }
        if (strcmp(argv[i], "-I") == 0)
        {
            printf("I  ");
            i++;
            while (i < argc && argv[i][0] >= '0' && argv[i][0] <= '9')
            {
                int e = atoi(argv[i]);
                push(p, e);
                i++;
            }
            print(p);
            continue;
        }
        if (strcmp(argv[i], "-O") == 0)
        {
            printf("O  ");
            i++;
            int n = atoi(argv[i]);
            i++;
            int e;
            for (int j = 0; i < n; j++)
            {
                pop(p, e);
            }
            printf("%d  ", size(p));
        }
        if (strcmp(argv[i], "-A") == 0)
        {
            printf("A  ");
            i++;
            int n = atoi(argv[i]);
            i++;
            print(p);
        }
        if (strcmp(argv[i], "-C") == 0)
        {
            printf("C  ");
            i++;
            print(p);
        }
        if (strcmp(argv[i], "-G") == 0)
        {
            printf("G  ");
            i++;
            int n = atoi(argv[i]);
            i++;
            int x = getelem(p, n);
            printf("%d  ", x);
        }

        if (strcmp(argv[i], "-N") == 0)
        {
            printf("N  ");
            i++;
            int x = howMany(p);
            printf("%d  ", x);
        }
    }
    destroySTACK(p);
    free(p);
    return 0;
}

void initSTACK(STACK *const p, int m)
{
    p->elems = (int *)malloc(m * sizeof(int));
    p->max = m;
    p->pos = 0;
}

void initSTACK(STACK *const p, const STACK &s)
{
    initSTACK(p, s.max);
    p->pos = s.pos;
    memcpy(p->elems, s.elems, s.max * sizeof(int));
}

int size(const STACK *const p)
{
    return p->max;
}

int howMany(const STACK *const p)
{
    return p->pos;
}

int getelem(const STACK *const p, int x)
{
    if (x >= p->pos)
    {
        printf("E  ");
        exit(0);
    }
    return p->elems[x];
}

STACK *const push(STACK *const p, int e)
{
    if (p->max == 0)
    {
        printf("E  ");
        exit(0);
    }
    if (p->pos < p->max)
    {
        p->elems[p->pos++] = e;
        return p;
    }
    printf("E  ");
    exit(0);
}

STACK *const pop(STACK *const p, int &e)
{
    if (p->pos > 0)
    {
        e = p->elems[p->pos--];
        return p;
    }
    printf("E  ");
    exit(0);
}

STACK *const assign(STACK *const p, const STACK &s)
{
    destroySTACK(p);
    initSTACK(p, s);
    return p;
}

void print(const STACK *const p)
{
    for (int i = 0; i < p->pos; i++)
    {
        printf("%d  ", p->elems[i]);
    }
}

void destroySTACK(STACK *const p)
{
    free(p->elems);
    p->pos = p->max = 0;
}