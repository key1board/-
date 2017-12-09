#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;     //Status 是函数返回值类型，其值是函数结果状态代码。
#define MAXSIZE 100

typedef struct
{
    char name[20];//姓名
    char no[10];//学号
    double score;//成绩
}Student;
typedef Student ElemType;

typedef struct
{
    ElemType *elem; //存储空间的基地址
    int length;//当前长度
}SqList;

void input(ElemType *e)//输入学生信息
{
    printf("输入学号");
    scanf("%s",e->no);
    printf("输入姓名\n");
    scanf("%s",e->name);
    printf("输入成绩\n");
    scanf("%lf",&e->score);
}

void output(ElemType *e)//输出学生信息
{
    printf("学号: %-10s, 姓名: %-20s,  成绩: %-10.2lf\n\n", e->no, e->name, e->score);
}

Status InitList(SqList *L)//创建顺序表
{
    L->elem=(ElemType*)malloc(sizeof(ElemType)*MAXSIZE);//为顺序表分配一个大小为MAXSIZE的空间
    if(!L->elem)                         //存储空间分配失败
    exit(OVERFLOW);
    L->length=0;                         //空表长度为0
    return OK;
}

int LocateElem(SqList *L,ElemType e)//按名字查询学生信息
{
    int i;
    for(i=0;i<L->length;i++)
        if(!strcmp(L->elem[i].name,e.name))
        {
            return i+1;
        }
    return 0;
}

Status ListInsert(SqList *L,int i,ElemType e) //插入学生信息
{
    int j;
    system("cls");
    if(i<1||i>L->length+1)//插入位置不合法
    {
        return ERROR;
    }
    if(L->length==MAXSIZE)//储存空间已满
    {
        return ERROR;
    }
    for(j=L->length-1;j>=i-1;j--)
        L->elem[j+1]=L->elem[j];
    L->elem[i-1]=e;
    ++L->length;//长度加一
    return OK;
}

Status ListDelete(SqList *L,int j,char *e)//删除指定位置的学生信息
{
    if(j!=L->length&&j>0)
    {
        strcpy(e,L->elem[j].name);
        for(;j<=L->length;j++)
        L->elem[j-1]=L->elem[j];
    }
    else//位置不合法
    return ERROR;
    --L->length;//长度减一
    return OK;
}
int main()
{
    int i,j,len,m,temp,a;
    char res[20];
    ElemType e,b;
    SqList L;
    int n;
    printf("******欢迎来到学生信息管理系统******\n");//功能选项
    printf("1.创建顺序表。\n");
    printf("2.输入数据。\n");
    printf("3.输出所有新生成绩。\n");
    printf("4.根据姓名查询新生成绩。\n");
    printf("5.显示指定位置学生信息。\n");
    printf("6.插入新生数据。\n");
    printf("7.删除新生数据。\n");
    printf("8.统计信息表中学生人数。\n");
    printf("0.退出。\n");

    n=-1;
    while(n!=0)
    {
        printf("请选择功能编号:\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:           //创建顺序表
                    if(InitList(&L))
                       printf("成功创建顺序表\n\n");
                    else
                       printf("创建顺序表失败\n\n");
                    break;
            case 2:        //输入学生信息
                    printf("请输入学生的数量(<100)\n");
                    scanf("%d",&len);
                    for(i=0;i<len;i++)
                    {
                        printf("第%d个人:\n",i+1);
                        input(&L.elem[i]);
                    }
                    L.length=len;
                    putchar('\n');
                    break;
            case 3:     //输出所有学生信息
                   for(i=0;i<L.length;i++)
                   {
                        output(&L.elem[i]);
                   }
                   putchar('\n');
                   break;
            case 4:    //按名字查询
                    printf("请输入需要查询的新生的姓名。\n");
                    scanf("%s",e.name);
                    temp=LocateElem(&L,e);
                    if(temp!=0)
                       output(&L.elem[temp-1]);
                    else
                        printf("查询失败！没有此学生信息\n\n");
                    break;
            case 5:   //按位置查询
                    printf("请输入需要查询数据的位置。\n");
                    scanf("%d",&i);
                    output(&L.elem[i-1]);
                    break;
            case 6:  //插入学生信息
                    printf("请输入一个数，代表插入的位置:\n");
                    scanf("%d",&a);
                    printf("请输入所要插入学生的信息:\n");
                    printf("学号:");
                    scanf("%s",b.no);
                    printf("姓名:");
                    scanf("%s",b.name);
                    printf("成绩:");
                    scanf("%lf",&b.score);
                    if(ListInsert(&L,a,b))
                        printf("插入成功.\n\n");
                    else
                        printf("插入失败.\n\n");
                    break;
            case 7:   //删除学生信息
                    printf("请输入所要删除的学生位置:");
                    scanf("%d",&m);
                    if(ListDelete(&L,m,res))
                        printf("删除成功.\n被删除的学生姓名为:%s\n\n",res);
                    else
                        printf("删除失败.\n\n");
                    break;
            case 8:  //统计学生总人数
                    printf("学生总人数为 %d\n",L.length);
                    break;
            case 0:exit(0); //退出系统
        }
    }
    return 0;
}
/*
#define MAXSIZE 20        //存储空间初始分配量
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
typedef int Status;  //Status时函数的类型，其值是函数结果状态码，如ok等
typedef int ElemType;     //ElemType,类型根据实际情况而定，这里假设为int

typedef struct
{
	ElemType data[MAXSIZE];
	int length;                 //线性表长度
}SqList;
Status GetElem(SqList L, int i, ElemType *e)
{
	if (L.length == 0 || i<1 || i>L.length)        //判断列表是否为空
		return ERROR;
	*e = L.data[i - 1];
	return OK;
}
Status ListInsert(SqList *L, int i, ElemType e)         //列表插入
{
	int k;
	if (L->length == MAXSIZE)    //顺序表已满
		return ERROR;
	if (i<1 || i>L->length + 1)   //当i不在使用范围内
		return ERROR;
	if (i <= L->length)     //若插入数据位置不在表尾
	{
		for (i <= L->length - 1; k >= i - 1; k--)   //将要插入位置后数据元素向后移动一位
			L->data[k + 1] = L->data[k];
	}
	L->data[i - 1] = e;          //将新元素插入
	L->length++;
	return OK;
}
Status ListDelet(SqList *L, int i, ElemType *e)         //列表删除
{
	int k;
	if (L->length == 0)           //线性表为空
		return ERROR;
	if (i<1 || i>L->length)         //删除位置不正确
		return ERROR;
	*e = L->data[i - 1];
	if (i < L->length)        //如果删除不是最后位置
	{
		for (k = i; k < L->length; k++) //将删除位置后继元素前移
			L->data[k - 1] = L->data[k];
	}
	L->length--;
	return OK;
}
int main()
{

}
*/
