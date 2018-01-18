#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

//所有的函数
void save(char *name, int n);
int readout(char *name, char *type);
void insert(char *name);
void deletedata(char *name);
void rankout(char *name);
void deletefile(char *name);
void fileinitialize(char *name);
void update(char *name);
void cleanscreen();
void makechoice(char *name);
int main();

typedef struct student_info           //学生信息结构体
{
    char name[10];      //姓名
    int num;            //学号
    int Chinese;        //语文
    int math;           //数学
    int English;        //英语
    int sum;
} info[100], insertinfo[100];
//info:存储100个学生的信息
//全局变量
char filename[50] = "D:\\programdata.txt";        //路径文件名
char type[10];
char *p;

void save(char *name, int n)         //将数据写入info[100]结构中
{
    //定义写入文件的方法来将内存中的数据写入到指定的文件中
    FILE *fp;
    int i;
    if ((fp = fopen(name, "w")) == NULL)       //判断文件是否为空
    {
        printf("文件打开错误\n");
        printf("检查并确保这台机器上有默认路径所指向的盘符（E）并重试\n");
        exit(0);
    }
    for (i = 0; i < n; i++)
        if (fwrite(&info[i], sizeof (struct student_info), 1, fp) != 1)     //以二进制形式写入文件
            /*fwrite(数据,数据类型大小(字节数),每次写入数据的最大数量,文件指针)
            每次输入的字节数为sizeof（struct student_info)    将info[i]的内容分1次写入fp文件中*/
            printf("文件写入错误");


    fclose(fp);          //关闭文件
}

int readout(char *name, char *type)  //将信息读出
{
    /*定义从文件中读取数据的函数，此函数将指定文件中的数据读取到内存中
    已准备接下来的操作*/
    int i;
    FILE *fp;
    if ((fp = fopen(name, type)) == NULL)
    {
        printf("文件打开错误\n");
        system("pause");
        makechoice(filename);
    }
    printf("\n=========================================\n");
    printf("姓名\t编号\t语文\t数学\t英语 *\n");
    for (i = 0; fread(&info[i], sizeof (struct student_info), 1, fp) != 0; i++) //返回读取数据的个数不等于0
    {
        printf("%s\t%d\t%d\t%d\t%d\t*\n", info[i].name, info[i].num,
                info[i].Chinese, info[i].math, info[i].english);
    }
    printf("=========================================\n");
    printf("共有 %d 条记录\n\n", i);
    fclose(fp);
    return i;
}

void insert(char *name)
{
    /*定义插入数据到文件中的方法
        此方法的思想是先将文件中的数据读取到内存中在
        内存中的进行一系列的数据操作之后在将操作处理后的新数据
        利用存数据函数存到文件中*/
    FILE *fp;
    int i, j, k, n, choice, flag, number;
    char insertname[10];


    p = "r";
    strcpy(type, p);
    readout(filename, type);

    printf("请选择插入方式\n");
    printf("1  在所有记录的末尾插入；\t2  指定位置插入\n请您选择（1,2）：");
    scanf("%d", &choice);
    switch (choice) {
        case 1:/*定义直接末未插入的方法这种情况下数据将直接被插入到文件的末尾*/
            printf("请输入您要插入的记录数\nnumber=");
            scanf("%d", &n);
            for (i = 0; i < n; i++) {//get infomation from keybord to memory
                printf(">NO_%d ", i + 1);
                scanf("%s%d%d%d%d", info[i].name, &info[i].num, &info[i].Chinese,
                        &info[i].math, &info[i].english);
            }

            if ((fp = fopen(name, "a+")) == NULL) {//try open the file and ready to write
                printf("cannot open file\n");
                system("pause");
                makechoice(filename);
            }
            for (i = 0; i < n; i++) {//write the data to the file
                if (fwrite(&info[i], sizeof (struct student_info), 1, fp) != 1)
                    printf("文件写入错误");
            }
            fclose(fp);
            break;
        case 2:/*定义任意插入的方法 这种情况下用户要插入的新数据将任意插入到某个数据之前*/
            if ((fp = fopen(name, "r")) == NULL) {
                /*先将原来的数据独到内存中做新数据插入前的准备工作*/
                printf("文件打开错误\n");
                system("pause");
                makechoice(filename);
            }
            for (i = 0; fread(&info[i], sizeof (struct student_info), 1, fp) != 0; i++) {
                number = i;
            }
            fclose(fp);

            printf("您打算将新纪录插入到哪个记录的前面\nname=");
            scanf("%s", insertname);

            printf("请输入要插入的记录数\nnumber=");
            scanf("%d", &n);

            for (i = 0; i < n; i++) {//get infomation from keybord to memory
                printf(">NO_%d ", i + 1);
                scanf("%s%d%d%d%d", insertinfo[i].name, &insertinfo[i].num, &insertinfo[i].Chinese,
                        &insertinfo[i].math, &insertinfo[i].english);
            }

            for (flag = 1, i = 0; flag && i <= number; i++) {//handle(delete) the data in the memory
                /*利用第一个for循环来找出符合条件的位置，位置应该为：若符合条件的位置的数组下标为i则包括i在内的
                （number+n+1）-（i+1）个数将要被后移n个位置单位*/
                if (strcmp(insertname, info[i].name) == 0 && i <= number) {
                    /*利用if条件定位 准备新数据的写入
                     */
                    for (j = number; j > i - 1; j--) {
                        /*利用第二个for循环将目标位置以后的数据后移
                                                number+1是原有的数据个数number是下标*/
                        info[j + n] = info[j];
                        if (j == i) {
                            //判断当条件适合的时候进行数据替换
                            for (k = 0; k < n; k++, j++) {
                                info[j] = insertinfo[k];
                            }

                            /*在数据后移工作以及新数据插入工作完成之后，再次写入文件*/
                            if ((fp = fopen(name, "w")) == NULL) {
                                /*先将原来的数据独到内存中做新数据插入前的准备工作*/
                                printf("文件打开错误\n");
                                system("pause");
                                makechoice(filename);
                            }
                            for (i = 0; i <= number + n; i++) {//write the data to the file
                                if (fwrite(&info[i], sizeof (struct student_info), 1, fp) != 1)
                                    printf("file write error");
                            }
                            fclose(fp);
                            j = i;
                            flag = 0;
                        }
                    }
                    puts(info[1].name);
                }
            }
            break;

    }

    printf("插入新数据后的学生信息如下:\n");
    p = "r";
    strcpy(type, p);
    readout(filename, type);
    system("pause");
    makechoice(filename);
}

void deletedata(char *name)          //删除数据
{
    /*定义删除数据的方法*/
    FILE *fp;
    int i, number;

    p = "r";
    strcpy(type, p);
    number = readout(filename, type) - 1;

    int j, flag;
    char delname[10];
    printf("请输入您要删除的学生的姓名:");
    scanf("%s", delname);
    for (flag = 1, i = 0; flag && i <= number; i++) {//handle(delete) the data in the memory
        if (strcmp(delname, info[i].name) == 0) {
            for (j = i; j <= number; j++) {
                /*利用覆盖的思想将条件之后的数据统统前移以覆盖的实质达到删除的效果*/
                strcpy(info[j].name, info[j + 1].name);
                info[j].num = info[j + 1].num;
                info[j].Chinese = info[j + 1].Chinese;
                info[j].math = info[j + 1].math;
                info[j].english = info[j + 1].english;
                flag = 0;
            }
            printf("您所选的信息以被成功删除!\n");
        }
    }
    if (flag) {
        printf("没有您要删除的信息 请重试!\n");
        deletedata(filename);
    }
    if ((fp = fopen(name, "w")) == NULL) {//try to open the file
        printf("文件打开错误\n");
        exit(0);
    }
    for (i = 0; i < number; i++) {//rewrite the data after the delete handle
        if (fwrite(&info[i], sizeof (struct student_info), 1, fp) != 1)
            printf("文件写入错误");
    }
    fclose(fp);

    printf("删除之后信息如下:\n");
    p = "r";
    strcpy(type, p);
    readout(filename, type);
    system("pause");

    makechoice(filename);
}

void rankout(char *name)
{
    /*定义总分排名的方法*/
    FILE *fp;
    int i, j, number, choice;
    if ((fp = fopen(name, "r")) == NULL) {//try to open the file
        printf("文件打开错误\n");
        exit(0);
    }
    printf("准备中...\n当前学生信息如下\n\n");
    printf("=================================================\n");
    printf("name\tid\tchinese\tmath\tenglish\tsum\t*\n");
    for (i = 0; fread(&info[i], sizeof (struct student_info), 1, fp) != 0; i++) {
        info[i].sum = info[i].Chinese + info[i].math + info[i].english;
        printf("%s\t%d\t%d\t%d\t%d\t%d\t*\n", info[i].name, info[i].num,
                info[i].Chinese, info[i].math, info[i].english, info[i].sum);
        number = i + 1;
    }
    printf("=================================================\n");
    printf("共有 %d 条记录\n\n", i);
    fclose(fp);
    printf("按 1 逆序排序:按 2 顺序排序!\n请您选择（1,2）：");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            if ((fp = fopen(name, "r")) == NULL) {//try to open the file
                printf("cannot open file\n");
                exit(0);
            }
            for (i = 0; fread(&info[i], sizeof (struct student_info), 1, fp) != 0; i++) {
                info[i].sum = info[i].Chinese + info[i].math + info[i].english;

            }
            fclose(fp);
            //printf("%d",number);
            for (j = 0; j < number; j++) {//sort by the sum backformation
                //printf("%d",number);
                /*排名的核心算法 类冒泡排序*/
                for (i = 0; i < number - 1; i++) {
                    if (info[i].sum < info[i + 1].sum) {
                        info[number] = info[i];
                        info[i] = info[i + 1];
                        info[i + 1] = info[number];
                    }
                }
            }
            if ((fp = fopen(name, "w")) == NULL) {//try to open the file
                printf("文件打开错误\n");
                exit(0);
            }
            for (i = 0; i < number; i++) {//rewrite the data after the delete handle
                if (fwrite(&info[i], sizeof (struct student_info), 1, fp) != 1)
                    printf("文件写入错误");
            }
            fclose(fp);

            if ((fp = fopen(name, "r")) == NULL) {//try to open the file
                printf("cannot open file\n");
                exit(0);
            }
            printf("准备中...\n当前学生信息如下\n\n");
            printf("=================================================\n");
            printf("姓名\t编号\t语文\t数学\t英语\tsum\t*\n");
            for (i = 0; fread(&info[i], sizeof (struct student_info), 1, fp) != 0; i++) {
                info[i].sum = info[i].Chinese + info[i].math + info[i].english;
                printf("%s\t%d\t%d\t%d\t%d\t%d\t*\n", info[i].name, info[i].num,
                        info[i].Chinese, info[i].math, info[i].english, info[i].sum);
                number = i + 1;
            }
            printf("=================================================\n");
            printf("共有 %d 条记录\n\n", i);
            fclose(fp);
            system("pause");
            break;
        case 2:
            p = "r";
            strcpy(type, p);
            number = readout(filename, type);

            for (j = 0; j < number; j++) {//sort by the sum orderly
                for (i = 0; i < number - 1; i++) {
                    if (info[i].sum > info[i + 1].sum) {
                        info[number] = info[i];
                        info[i] = info[i + 1];
                        info[i + 1] = info[number];
                    }
                }
            }
            if ((fp = fopen(name, "w")) == NULL) {//try to open the file
                printf("文件打开错误\n");
                exit(0);
            }
            for (i = 0; i < number; i++) {//rewrite the data after the delete handle
                if (fwrite(&info[i], sizeof (struct student_info), 1, fp) != 1)
                    printf("文件打开错误");
            }
            fclose(fp);

            if ((fp = fopen(name, "r")) == NULL) {//try to open the file
                printf("cannot open file\n");
                exit(0);
            }
            printf("准备中...\n当前学生信息如下\n\n");
            printf("=================================================\n");
            printf("n姓名\t编号\t语文\t数学\t英语\t总分\t*\n");
            for (i = 0; fread(&info[i], sizeof (struct student_info), 1, fp) != 0; i++) {
                info[i].sum = info[i].Chinese + info[i].math + info[i].english;
                printf("%s\t%d\t%d\t%d\t%d\t%d\t*\n", info[i].name, info[i].num,
                        info[i].Chinese, info[i].math, info[i].english, info[i].sum);
                number = i + 1;
            }
            printf("=================================================\n");
            printf("共有 %d 条记录\n\n", i);
            fclose(fp);
            system("pause");
            break;
        default:
            printf("错误选项 请重试!\n");
            makechoice(filename);
    }
    makechoice(filename);

}

void deletefile(char *name)           //删除文件
{
    FILE *fp;
    int choice;
    char delfilename[50];
    printf("选择删除方式?\n");
    printf("1 删除当前文件: 2 删除其他文件\n请您选择（0-9）：");
    scanf("%d", &choice);
    switch (choice) {
        case 2:
            printf("请输入要删除的文件的路径\npath=");
            scanf("%s", delfilename);
            if (remove(filename) == 0)
                printf("文件删除成功!\n");
            else
                printf("文件删除失败!\n");
            break;
        case 1:
            if (remove(filename) == 0)
                printf("文件删除成功!\n");
            else
                printf("文件删除失败!\n");
            break;
        default:
            printf("选择错误 !\n");
            break;
    }
    makechoice(filename);
}

void fileinitialize(char *name)       //文件数据初始化
{
    int i, n;

    printf("请输入班级的人数?\n>Number=");
    scanf("%d", &n);

    printf("\n您将会将 %d 信息记录存储到 %s 文件中\n\n", n, filename);

    printf("请依次输入学生的姓名、学号以及语文、数学、英语的学科成绩:\n");
    for (i = 0; i < n; i++)
    {
        printf(">NO_%d ", i + 1);
        scanf("%s%d%d%d%d", info[i].name, &info[i].num, &info[i].Chinese,
                &info[i].math, &info[i].English);//是否将info[i]等于.name .num .....？
        save(filename, n);
    }
    p = "r";
    strcpy(type, p);
    readout(filename, type);
    makechoice(filename);
}

void update(char *name)
{
    puts("当前文件内数据\n");
    p = "r";
    strcpy(type, p);
    readout(filename, type);
    printf("Update successfully!");
    system("pause");
    makechoice(filename);
}

void makechoice(char *name)          //子目录
{
    time_t now;
    time(&now);
    int choice;

    printf("\n          按 <1> 初始化文件数据----------------1\n");
    printf("          按 <2> 插入记录到文件中--------------2\n");
    printf("          按 <3> 删除记录----------------------3\n");
    printf("          按 <4> 排名并输出--------------------4\n");
    printf("          按 <5> 删除文件----------------------5\n");
    printf("          按 <6> 文件更新----------------------6\n");
    printf("          按 <7> 重新运行改程序----------------7\n");
    printf("          按 <8> 清屏--------------------------8\n");
    printf("          按 <9> 显示已有数据------------------9\n");
    printf("          按 <0> 退出--------------------------0\n");
    printf("          按 Ctrl+C 组合键立即中断程序!\n");
    printf("\n                                        当前时间:%s\n", ctime(&now));
    printf("请您选择（0-9）：");
    scanf("%d", &choice);
    switch (choice) {
        case 1:printf("正在执行初始化操作$\n");
            fileinitialize(filename);
            break;
        case 2:printf("正在执行插入操作$\n");
            insert(filename);
            break;
        case 3:printf("正在执行删除数据操作$\n");
            deletedata(filename);
            break;
        case 4:printf("正在执行排名输出操作$\n");
            rankout(filename);
            break;
        case 5:printf("正在执行删除文件操作$\n");
            deletefile(filename);
            break;
        case 6:printf("正在执行文件更新操作$\n");
            update(filename);
            break;
        case 7:system("cls");
            main();
            break;
        case 8:system("cls");
            makechoice(filename);
            break;
        case 9:printf("数据显示$\n");
            p = "r";
            strcpy(type, p);
            readout(filename, type);
            system("pause");
            makechoice(filename);
            break;
        case 0:printf("退出$\n");
            exit(0);
            break;
        default:printf("错误选项 请重试!\n");
            system("pause");
            makechoice(filename);
            break;
    }
}

int main() {
    int i, choice;
    printf("=========================================================================\n");
    printf("\t\t\t欢迎来到学生成绩管理系统\n");
    printf("=========================================================================\n");
    printf("程序数据将存储到文件中，请先做出路径设置的相关选择以确定文件的路径\n");
    printf("           1--------------------使用默认路径\n");
    printf("           2--------------------输入自定义路径\n");
    printf("           3--------------------重新设置默认路径\n");
    printf("           0--------------------退出\n");
    printf("请您选择（0-3）：");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            makechoice(filename);
            break;
        case 2:
            printf("Enter new path=");
            scanf("%s", filename);
            printf("\n应为路径被更新，文件内容为空，要操作请先初始化数据，请先执行 1选项 操作!\n");
            makechoice(filename);
            break;
        case 3:
            printf("当前默认路径:%s\n请输入新路径:", filename);
            scanf("%s", filename);
            printf("路劲重设成功\t当前路径 :%s\n", filename);
            system("pause");
            makechoice(filename);
            break;
        case 0:
            exit(0);
        default:
            printf("错误选项 请重试!\n");
            system("pause");
            main();
    }
}
