#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#include <iostream>
#include <cstdio>
using namespace std;
class STACK
{
    int *const elems; //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;          //栈实际已有元素个数，栈空时pos=0;
  public:
    STACK(int m);                             //初始化栈：最多m个元素
    STACK(const STACK &s);                    //用栈s拷贝初始化栈
    virtual int size() const;                 //返回栈的最大元素个数max
    virtual operator int() const;             //返回栈的实际元素个数pos
    virtual int operator[](int x) const;      //取下标x处的栈元素
    virtual STACK &operator<<(int e);         //将e入栈,并返回栈
    virtual STACK &operator>>(int &e);        //出栈到e,并返回栈
    virtual STACK &operator=(const STACK &s); //赋s给栈,并返回被赋值的栈
    virtual void print() const;               //打印栈
    virtual ~STACK();                         //销毁栈
};

STACK::STACK(int m) : elems(new int[m]), max(m)
{
    pos = 0;
}

int STACK::size() const
{
    return max;
}


STACK::STACK(const STACK &s) : elems(new int[s.max]), max(s.max)
{
    int i;
    for (i = 0; i < s.pos; i++)
    {
        elems[i] = s.elems[i];
    }
    pos = s.pos;
}

STACK ::operator int() const
{
    return this->pos;
}

int STACK ::operator[](int x) const
{
    if (x >= pos)
    {
        printf("E  ");
        exit(0);
    }
    return elems[x];
}

STACK &STACK ::operator<<(int e)
{
    if (max == 0)
    {
        cout << "E  ";
        exit(0);
    }
    if (max <= pos)
    {
        cout << "E  ";
        exit(0);
    }
    elems[pos++] = e;
    return *this;
}

STACK &STACK ::operator>>(int &e)
{
    if (pos <= 0)
    {
        cout << "E  ";
        exit(0);
    }
    e = elems[pos--];
    return *this;
}

STACK &STACK ::operator=(const STACK &s)
{
    if (max < s.max)
    {
        delete[] *(int **)(&elems);
        *(int **)(&elems) = new int[s.max];
        *(int*)(&max) = s.max;
    }
    pos = s.pos;
    for (int i = 0; i < s.pos; i++)
    {
        elems[i] = s.elems[i];
    }
    return *this;
}

void STACK::print() const
{
    for (int i = 0; i < pos; i++)
    {
        cout << elems[i] << "  ";
    }
}
STACK ::~STACK()
{
    delete[] elems;
    *(int *)&max = 0;
    pos = 0;
}

int main(int argc, char const *argv[])
{
    STACK *p = NULL;
    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "-S") == 0)
        {
            printf("S  ");
            i++;
            int n = atoi(argv[i]);
            p = new STACK(n);
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
                *p << e;
                i++;
            }
            p->print();
            continue;
        }
        if (strcmp(argv[i], "-O") == 0)
        {
            printf("O  ");
            i++;
            int n = atoi(argv[i]);
            i++;
            int e;
            for (int j = 0; j < n; j++)
            {
                *p >> e;
            }
            p->print();
            continue;
        }
        if (strcmp(argv[i], "-A") == 0)
        {
            printf("A  ");
            i++;
            int n = atoi(argv[i]);
            STACK* q = new STACK(n);
            *q = *p;
            delete p;
            p = q;
            i++;
            p->print();
            continue;
        }
        if (strcmp(argv[i], "-C") == 0)
        {
            printf("C  ");
            i++;
            STACK* q = new STACK(*p);
            delete p;
            p = q;
            p->print();
            continue;
        }
        if (strcmp(argv[i], "-G") == 0)
        {
            printf("G  ");
            i++;
            int n = atoi(argv[i]);
            i++;
            int x = (*p)[n];
            printf("%d  ", x);
            continue;
        }

        if (strcmp(argv[i], "-N") == 0)
        {
            printf("N  ");
            i++;
            int x = int(*p);
            printf("%d  ", x);
            continue;
        }

    }
    delete p;
    return 0;
}
