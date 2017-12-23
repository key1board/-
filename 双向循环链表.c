#include <stdio.h>
#include <stdlib.h>

#define FALSE 1
typedef int ElemType;

typedef struct Node
{
	ElemType data;
	struct Node *prior;
	struct Node *next;
}Node;

Node *InitList(int n)         //数据初始化
{
	Node*head,*s,*p;
	int i;
	if ((head = (Node *)malloc(sizeof(Node))) == NULL)
	{
		printf("Error");
		exit(0);
	}
	head->data = 0;
	s = head;
	for (i = 0; i < n; i++)
	{
		if ((p = (Node *)malloc(sizeof(Node))) == NULL)
		{
			printf("Error");
			exit(0);
		}
		scanf("%d", &p->data);
		s->next = p;
		p->prior = s;
		p->next = head;
		head->prior = p;
		s = p;
	}
	return head;
}

int ListLength(Node *head)       //判断数据长度
{
	Node *p;
	int n = 0;
	if ((p = (Node *)malloc(sizeof(Node))) == NULL)
	{
		printf("Error");
		exit(0);
	}
	p = head->next;
	while (p->data != 0)
	{
		p = p->next;
		n++;
	}
	return n;
}

Node *insert(Node *head,int n)    //在结点n后插入数据
{
	Node *s,*p;
	int i;
	if (n > ListLength(head)||n < 0)
	{
		printf("Input Error!");
		return 0;
	}
	p = head;
	if ((s = (Node *)malloc(sizeof(Node))) == NULL)
	{
		printf("Error");
		exit(0);
	}
	printf("输入要插入的数据：");
	scanf("%d", &s->data);
	
	for (i = 0; i <= n; i++)
	{
		if (i == n)
		{
			s->prior = p;
			s->next = p->next;
			p->next->prior = s;
			p->next = s;
		}
		p = p->next;
	}
	return head;

}

 void output(Node *head)       //输出数据
{
	Node *p;
	p = head->next;
	printf("输出全部数据：");
	while (1)
	{
		if (p->data == 0)
			break;
		printf("%d ", p->data);
		p = p->next;
	}
}

Node *amendList(Node *head,int n)       //修改数据
{
	Node *p = head;
	int i,num;
	
	printf("输入修改的数据：");
	scanf("%d", &num);
	for (i = 0; i <= n; i++)
	{
		if (i == n)
			p->data = num;
		p = p->next;
	}
	return head;
}

Node *ListDelet(Node *head, int n)     //删除数据
{
	int i;
	Node *p = head;
	
	if (n > ListLength(head) || n < 0)
	{
		printf("input Error");
		return 0;
	}
	for (i = 0; i <= n; i++)
	{
		if (i == n)
		{
			p->prior->next = p->next;
			p->next->prior = p->prior;
		}
		p = p->next;
	}
	return head;
}

int main()
{
	Node *head;
	int num,n;

	if ((head = (Node *)malloc(sizeof(Node))) == NULL)
	{
		printf("Error");
		exit(0);
	}
	while (1)
	{
		printf("\n\t\t 1) 初始化数据 -\n");
		printf("\n\t\t 2) 插入数据 -\n");
		printf("\n\t\t 3) 输出数据 -\n");
		printf("\n\t\t 4) 修改数据 -\n");
		printf("\n\t\t 5) 删除数据 -\n");
		printf("\n\t\t 6) 退出程序 -\n");
		printf("请输入选择(1-6):");
		scanf("%d", &n);
		
		switch (n)
		{
		case 1:
		{
			printf("\n需要输入多少次数据：");
			scanf("%d", &num);
			head = InitList(num);
			printf("保存成功！");
			break;
		}
		case 2:
		{
			printf("\n输入插入位置：");
			scanf("%d", &num);
			head = insert(head, num);
			break;
		}
		case 3:
		{
			output(head);
			break;
		}
		case 4:
		{
			printf("\n输入修改的位置:");
			scanf("%d", &num);
			head = amendList(head, num);
			break;
		}
		case 5:
		{
			printf("\n输入删除位置：");
			scanf("%d", &num);
			head = ListDelet(head, num);
			break;
		}
		case 6: return 0;

		default: 
		{
			printf("\n输入错误!"); 
			break; 
		}
		}
	}
}
