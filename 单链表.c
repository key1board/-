/*版本1.0*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElemType;

typedef struct Node
{
	char name[20];  //名字
	int num;	 //学号
	int CH;      //语文
	int MA;      //数学
	int EN;      //英语
	struct Node *next;
}Node;

Node * NewLink(int n) //尾插法建立新表
{
	Node *p, *h;
	int i;
	h = NULL;
	for (i = 0; i < n; i++)
	{
		if ((p = (Node *)malloc(sizeof(Node))) == NULL)
		{
			printf("不能分配空间！");
			exit(0);
		}
		p->next = h;		
		h = p;
		printf("\n请输入第%d位学生姓名:", i + 1);
		scanf("%s",p->name);
		printf("\n请输入学号:");
		scanf("%d", &p->num);
		printf("\n请输入语文成绩:");
		scanf("%d", &p->CH);
		printf("\n请输入数学成绩:");
		scanf("%d", &p->MA);
		printf("\n请输入英语成绩:");
		scanf("%d", &p->EN);

	}
	if (h != NULL)
		printf("申请成功！");
	return (h);
}

Node * CreateList_End(int n)  //尾插法，头结点为NULL
{
	Node *head, *p, *e;
	int i;

	head = NULL;
	e = NULL;
	for(i=0;i<n;i++)
	{
		p = (Node*)malloc(sizeof(Node));
		printf("\n请输入第%d位学生姓名:", i + 1);
		scanf("%s", p->name);
		printf("\n请输入学号:");
		scanf("%d", &p->num);
		printf("\n请输入语文成绩:");
		scanf("%d", &p->CH);
		printf("\n请输入数学成绩:");
		scanf("%d", &p->MA);
		printf("\n请输入英语成绩:");
		scanf("%d", &p->EN);
		if (head == NULL)        //先判断输入的是不是第一个节点  
			head = p;
		else
			e->next = p;     //e始终指向输入的最后一个节点  
		e = p;
	}
	if (e != NULL)               //如果链表不为空，则最后节点的下一个节点为空  
		e->next = NULL;

	return head;                //尾插法比头插法复杂一些，程序中要做两次判断，分别是判断第一个节点和最后一个节点的判断。且消耗多一个指针变量e。  
}

Node * search(Node * head, char *name) //对单个元素进行查找
{
	Node *p;
	char *y;
	p = head->next;
	while (p != NULL)
	{
		y = p->name;
		if (strcmp(y, name) == 0)
		{
			printf("姓名：%s\n", p->name);
			printf("\n学号: %d\n", p->num);
			printf("\n 语文:%d  数学:%d  英语:%d\n",p->CH,p->MA,p->EN);
			return (p);
		}
		else p = p->next;
	}
	if (p == NULL)
		printf("没有查找到该数据！");
	return 0;
}

void insert(Node *head)  //头插法插入新信息
{
	Node *p,*s;
	char x[20];
	char *y;
	p = head->next;        //p=head的头结点
	while (p != NULL)
	{
		printf("名字：%s学号：%d语文：%d数学：%d英语：%d\n", p->name, p->num, p->CH, p->MA, p->EN);
		p = p->next;     //指向下一个结点
	}
	printf("\n请问在那位学生的后面插入信息：");
	scanf("%s",x);
	s = (Node *)malloc(sizeof(Node));
	while (p != NULL)
	{
		y = p->name;
		if (strcmp(y,x)==0)        //在x同学的后面插入信息
		{
			printf("\n请输入你要插入的信息!");
			printf("\n请输入学生姓名:");
			scanf("%s", &p->name);
			printf("\n请输入学生学号:");
			scanf("%d", &p->num);
			printf("\n请输入语文成绩:");
			scanf("%d", &p->CH);
			printf("\n请输入数学成绩:");
			scanf("%d", &p->MA);
			printf("\n请输入英语成绩:");
			s->next = p->next;
			p->next = s;
		}
		else p = p->next;
	}
}

Node * search2(Node *h,char  *x)   //求出当前结点的前驱结点
{
	Node *p, *s;
	char *y;
	p = h->next;
	s = h;
	while (p != NULL)
	{
		y = p->name;
		if (strcmp(y,x) == 0)
			return(s);
		else
		{
			p = p->next;
			s = s->next;
		}
	}
	if (p == NULL)
		printf("没有查找到数据!");
	return 0;
}

void del(Node *x, Node *y)  //删除结点
{
	Node *s;
	s = y;
	x->next = y->next;
	free(s);
}

void change(Node * head,char *x)
{
	Node *p = head->next;
	char *y;
	while (p != NULL)
	{
		y = p->name;
		if (strcmp(y, x) == 0)
		{
			printf("\n请输入你要修改的信息!");
			printf("\n请输入学生姓名:");
			scanf("%s", &p->name);
			printf("\n请输入学生学号:");
			scanf("%d", &p->num);
			printf("\n请输入语文成绩:");
			scanf("%d", &p->CH);
			printf("\n请输入数学成绩:");
			scanf("%d", &p->MA);
			printf("\n请输入英语成绩:");
		}
		else p = p->next;
	}
}

int main()
{
	int n;
	Node *head, *searchpoint,*forepoint;  //searchpoint为前驱结点，forepoint为当前结点
	char name[20];

	printf("需要录入多少位同学的信息：");
	scanf("%d", &n);
	//head = NewLink(n);  //建立初始化函数
	head = CreateList_End(n);
	system("cls");
	while (1)
	{

		printf("\t\t\t1)查找信息\n\n");
		printf("\t\t\t2)修改信息\n\n");
		printf("\t\t\t3)删除信息\n\n");
		printf("\t\t\t4)增加信息\n\n");
		printf("\n请输入要要执行的命令: ");
		scanf("%d", &n);
		if (n == 1)
		{
			printf("\n请输入你要查找的人的姓名：");
			scanf("%s", &name);
			search(head, name);
			system("cls");
		}
		else if (n == 2)
		{
			printf("\n请输入要更改的学生信息：");
			scanf("%s", &name);
			change(head, name);
			system("cls");
		}
		else if (n == 3)
		{
			printf("\n请输入你要删除的人的信息：");
			scanf("%s", &name);
			forepoint = search(head, name);
			searchpoint = search2(head, name);
			del(searchpoint, forepoint);
			system("cls");
		}
		else if (n == 4)
		{
			printf("\n请输入要增加的信息：\n");
			insert(head);
			system("cls");
		}
	}
}
