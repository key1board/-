#include <stdio.h> 
#include<malloc.h>
#include<stdlib.h>

typedef struct list
{
	int num;
	struct list *next;
}List;

List *creat()
{
	List *head, *p1, *p2;
	int i;
	if ((head = (List *)malloc(sizeof(List))) == NULL)
	{
		printf("Error");
		exit(0);
	}
	p1 = p2 = head;
	printf("输入创建链表的长度：");
	scanf("%d", &head->num);//创建列表，带头结点，头结点数据域表示输入的个数
	if (head->num == 0)
	{
		head->next = NULL;
		printf("已创建带头结点的空链表");
	}
	else
	{
		printf("输入数据：\n");
		for (i = 0; i<head->num; i++)
		{
			if ((p1 = (List *)malloc(sizeof(List))) == NULL)
			{
				printf("Error");
				exit(0);
			}
			scanf("%d", &p1->num);
			p2->next = p1;
			p2 = p1;
		}
		p1->next = head;
	}
	return(head);
}
void print(List *head)  //遍历表
{
	List *p;
	p = head->next;
	while(p != head)
	{
		printf("%d ", p->num);
		p = p->next;
	}
	printf("\n");
}
void main()
{
	List *head;
	head = creat();
	print(head);
}
