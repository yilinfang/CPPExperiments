#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
using namespace std;
class STACK
{
    int *const elems; //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个�?
    int pos;          //栈实际已有元素个数，栈空时pos=0;
  public:
    STACK(int m);                             //初始化栈：最多m个元�?
    STACK(const STACK &s);                    //用栈s拷贝初始化栈
    virtual int size() const;                 //返回栈的最大元素个数max
    virtual operator int() const;             //返回栈的实际元素个数pos
    virtual int operator[](int x) const;      //取下标x处的栈元�?
    virtual STACK &operator<<(int e);         //将e入栈,并返回栈
    virtual STACK &operator>>(int &e);        //出栈到e,并返回栈
    virtual STACK &operator=(const STACK &s); //赋s给栈,并返回被赋值的�?
    virtual void print() const;               //打印�?
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
    e = elems[--pos];
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
    QUEUE(int m);                             //每个栈最多m个元素，要求实现的队列最多能�?2m个元�?
    QUEUE(const QUEUE &s);                    //用队列s拷贝初始化队�?
    virtual operator int() const;             //返回队列的实际元素个�?
    virtual int full() const;                 //返回队列是否已满，满返回1，否则返�?0
    virtual int operator[](int x) const;      //取下标为x的元素，�?1个元素下标为0
    virtual QUEUE &operator<<(int e);         //将e入队�?,并返回队�?
    virtual QUEUE &operator>>(int &e);        //出队列到e,并返回队�?
    virtual QUEUE &operator=(const QUEUE &s); //赋s给队�?,并返回被赋值的队列
    virtual void print() const;               //打印队列
    virtual ~QUEUE();                         //销毁队�?
};

//初始化队�?
QUEUE::QUEUE(int m) : STACK(m), s2(m)
{
    return;
}

QUEUE::QUEUE(const QUEUE &s) : STACK(s), s2(s.s2)
{
}

QUEUE::operator int() const
{
    return (int)s2 + STACK::operator int();
}

int QUEUE::full() const
{
    if (s2 != 0 && STACK::operator int() == size())
    {
        return 1;
    }
    return 0;
}

int QUEUE::operator[](int x) const
{
    if (x >= int(*this))
    {
        printf("E  ");
        exit(0);
    }
    if ((int)s2 == 0)
    {
        return STACK::operator[](x);
    }
    else
    {
        if (x < (int)s2)
        {
            return s2[(int)s2 - x - 1];
        }
        else
        {
            return STACK::operator[](x - int(s2));
        }
    }
}

QUEUE &QUEUE::operator<<(int e)
{
    {
        if (full())
        {
            printf("E  ");
            exit(0);
        }
        if (int(s2) != 0 && STACK::operator int() != STACK::size())
        {
            STACK::operator<<(e);
            return *this;
        }
        else
        {
            if (STACK::operator int() == STACK::size())
            {
                int m = STACK::operator int();
                for (int i = 0; i < m; i++)
                {
                    int temp;
                    STACK::operator>>(temp);
                    s2 << (temp);
                }
                STACK::operator<<(e);
                return *this;
            }
            else
            {
                STACK::operator<<(e);
                return *this;
            }
        }
    }
}
QUEUE &QUEUE::operator>>(int &e)
{
    {
        if (STACK::operator int() == 0 && int(s2) == 0)
        {
            printf("E  ");
            exit(0);
        }
        if (int(s2))
        {
            s2 >> e;
        }
        else if (!int(s2) && STACK::operator int())
        {
            int m = STACK::operator int();
            for (int i = 0; i < m; i++)
            {
                int temp;
                STACK::operator>>(temp);
                s2 << temp;
            }
            s2 >> e;
        }
        return *this;
    }
}

QUEUE &QUEUE::operator=(const QUEUE &s)
{
    s2 = s.s2;
    STACK::operator=(s);
    return *this;
}

void QUEUE::print() const
{
    for (int i = 0; i < int(*this); i++)
    {
        printf("%d  ", (*this)[i]);
    }
}

QUEUE::~QUEUE()
{
}

int main(int argc, char const *argv[])
{
    /*命令行测试部�?*/
    QUEUE *p = NULL;
    int i = 1;
    while (i < argc)
    {
        if (strcmp(argv[i], "-S") == 0)
        {
            printf("S  ");
            i++;
            int n = atoi(argv[i]);
            p = new QUEUE(n);
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
            QUEUE *q = new QUEUE(n);
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
            QUEUE *q = new QUEUE(*p);
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
    if (p)
    {
        delete p;
    }
    /*舞伴问题*/
    int M, F;
    int m, f;
    printf("请输入男士人数：");
    cin >> M;
    printf("请输入女士人数：");
    cin >> F;
    printf("请输入男士编号：");
    cin >> m;
    printf("请输入女士编号：");
    cin >> f;
    QUEUE *mQueue = new QUEUE(M);
    QUEUE *fQueue = new QUEUE(F);
    for (int i = 1; i <= M; i++)
    {
        if (i != m)
        {
            *mQueue << 1;
        }
        else
        {
            *mQueue << 0;
        } 
    }
    for (int i = 1; i <= F; i++)
    {
        if (i != f)
        {
           *fQueue << 1; 
        }
        else
        {
            *fQueue << 0;
        }
    }
    int mOut = 1, fOut = 1;
    int count = 0;
    while (mOut == 1 || fOut == 1)
    {
        *mQueue >> mOut;
        *mQueue << mOut;
        *fQueue >> fOut;
        *fQueue << fOut;
        count++;
    }
    printf("�?%d男士与第%d女士在第%d支舞相遇！\n", m, f, count);
    delete mQueue;
    delete fQueue;

    return 0;
}