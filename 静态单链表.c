#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef int DataType;

//---------线性表的静态单链表存储结构--------
#define MAXSIZE 100
typedef struct
{
    ElemType data;
    int cur;
}SLinkList[MAXSIZE];

//将下标为k的空闲结点回收到备用链表
void Free_SL(SLinkList space, int k)
{
    space[k].cur = space[0].cur;    //将备用链表链到k之后
    space[0].cur = k;               //将k链到备用链表头之后
}

//分配备用链表的一个结点,返回下标
//若为0，则说明备用链表用完
int Malloc_SL(SLinkList space)
{
    int i = space[0].cur;
    if(space[0].cur)                 //判断备用链表是否非空
        space[0].cur = space[i].cur; //备用链表头指针指向第二个空结点
    return i;                        //返回第一个空结点
}

void SListInit(SLinkList space)
{
    int i;
    for(i = 0; i < MAXSIZE; i++)
        space[i].cur = i+1;         //将所有结点链入备用链表

    space[0].cur = space[1].cur;    //备用链表头指针链像第二个结点
    space[1].cur = 0;               //第一个结点作为链表的头结点
}

//获取链表的长度
int SListLength(SLinkList space)
{
    int len = 0;
    int i = space[1].cur;           //用头指针第一个结点的下标
    while(i)
    {
        ++len;
        i = space[i].cur;
    }
    return len;
}

//在链表的第i个位置插入元素e
void SlistInsert(SLinkList space, int i, ElemType e)
{
    if(i < 1 || i > SListLength(space)+1) //超出范围
        return;

    int k = 1, j;
    for(j = 0; j <i-1; j++)         //使k指示要删除的结点的前一个结点
        k = space[k].cur;

    int v = Malloc_SL(space);
    if(v)                           //如果有空间
    {
        space[v].data = e;
        space[v].cur = space[k].cur;
        space[k].cur = v;           //链入链表
    }
}

//删除第i个位置的元素
void SListDelete(SLinkList space, int i)
{
    if(i < 1 || i > SListLength(space))  //超出范围退出
        return ;
    int k = 1, j;
    for(j = 0; j <i-1; j++)         //使k指示要删除的结点的前一个结点
        k = space[k].cur;

    int temp = space[k].cur;
    space[k].cur = space[temp].cur;
    Free_SL(space, temp);
}

void SListTraverse(SLinkList space)
{
    int i = space[1].cur;
    while(i)
    {
        printf("%d\n", space[i].data);
        i = space[i].cur;
    }
}
int main()
{
    SLinkList space;
    SListInit(space);   //初始化
    int i;
    for(i = 1; i <= 10; i ++)
        SlistInsert(space, 1, i);
    SListDelete(space, 10);

    SListTraverse(space);
    return 0;
}
