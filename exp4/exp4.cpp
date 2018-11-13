#include <iostream>
#include <stdlib.h>
#include <string.h>
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
        delete[] * (int **)(&elems);
        *(int **)(&elems) = new int[s.max];
        *(int *)(&max) = s.max;
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

class QUEUE : public STACK
{
    STACK s2;

  public:
    QUEUE(int m);                             //每个栈最多m个元素，要求实现的队列最多能入2m个元素
    QUEUE(const QUEUE &s);                    //用队列s拷贝初始化队列
    virtual operator int() const;             //返回队列的实际元素个数
    virtual int full() const;                 //返回队列是否已满，满返回1，否则返回0
    virtual int operator[](int x) const;      //取下标为x的元素，第1个元素下标为0
    virtual QUEUE &operator<<(int e);         //将e入队列,并返回队列
    virtual QUEUE &operator>>(int &e);        //出队列到e,并返回队列
    virtual QUEUE &operator=(const QUEUE &s); //赋s给队列,并返回被赋值的队列
    virtual void print() const;               //打印队列
    virtual ~QUEUE();                         //销毁队列
};

QUEUE::QUEUE(int m) : STACK(m), s2(m)
{
}

QUEUE::QUEUE(const QUEUE &s) : STACK(s.size()), s2(s.size())
{
    for(int i = 0; i < (int)s; i++)
    {
        *this << s[i];
    }
}