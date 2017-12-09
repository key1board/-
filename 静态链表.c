#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 100          //假设链表最大长度为100

typedef int ElemType;
typedef int Status;

typedef struct
{
	ElemType data;
	int cur;             //游标
}Component, LinkList[MAXSIZE];

ElemType InitList(LinkList space)         //初始化
{
	int i;
	for (i = 0; i < MAXSIZE - 1; i++)
		space[i].cur = i + 1;
	space[MAXSIZE - 1].cur = 0;   //目前静态链表为空，最后一个元素的cur为0
	return 0;
}

//将下标为k的空闲结点回收到备用链表
void Free_SSL(LinkList space, int k)
{
	space[k].cur = space[0].cur;    //把第一个元素cur的值赋给要删除的分量cur
	space[0].cur = k;               //把要删除的分量下标赋值给第一个元素的cur
}

//若备用空间链表非空，则返回分配的结点下表，否则返回0
int Malloc_SSL(LinkList space)    //插入操作
{
	int i = space[0].cur;  //当前数组第一个元素的cur存的值
	                       //就是要返回的第一个备用空闲的下标
	if (space[0].cur)
		space[0].cur = space[i].cur;          //由于要拿出一个分量来使用，所以我们
	                                          //就得把它的下一个分量用来做备用
	return i;
}

//在L中第i个元素之前插入新的数据元素e
Status ListInsert(LinkList L, int i, ElemType e)
{
	int j, k;
	//k = MAXSIZE - 1;        //注意k首先是最后一个元素的下标
	if (i<1 || i>MAXSIZE - 1)
		return 1;
	j = Malloc_SSL(L);     //获得空闲分量的下标
	if (j)
	{
 		L[j].data = e;     //将数据赋值给此分量的data
		//for (l = 1; l <= i - 1; l++) //找到第i个元素之前的位置
			//k = L[k].cur;
		k = i - 1;
		L[j].cur = L[k].cur;      //把第i个元素之前的cur赋值给新元素的cur
		L[k].cur = j;              //把新元素的下表赋值给第i个元素之前的元素的cur
		return 0;
	}
	return 1;
}

//删除在L中第i个数据元素e
Status ListDelete(LinkList L, int i)
{
	int j, k;
	//k = MAXSIZE - 1;
	if (i<1 || i>MAXSIZE - 1)
		return 1;
	//k = MAXSIZE - 1;
	//for (j = 1; j <= i - 1; j++)
		//k = L[k].cur;
	k = i - 1;
	j = L[k].cur;
	L[k].cur = L[j].cur;   //将k所指的下标等于j所指的下表
	Free_SSL(L, j);
	return 0;
}

int main()
{
	srand((unsigned)time(NULL));
	LinkList space;
	int reception,e,L;
	InitList(space);
	while (1)
	{
		reception = rand() % 81 + 10;
		e = rand() % 1000;
		L = ListInsert(space, reception, e);
		scanf("%d", &e);
		ListDelete(space, e);
	}
}
