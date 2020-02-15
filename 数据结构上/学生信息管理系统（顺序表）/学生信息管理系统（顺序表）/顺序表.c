#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct
{
	char name[20];
	char id[20];
}student;

typedef struct
{
	student *data;
	int length;
	int listsize;
}list;

int menu();
int create(list *l,int max);
int insert(list *l, int i, student x);

int main()
{
	int n,i,num,r,max;
	student x;
	list l;
	char m[20];
	while (1)
	{
		n = menu();
		if (n == 0)
			break;
		switch (n)
		{
		case 1:
			printf("请输入创建的学生人数：\n");
			scanf("%d", &max);
			getchar();
			r = create(&l,max);
			if (r == 1)
				printf("创建成功!\n");
			else
				printf("创建失败!\n");
			break;
		case 2:
			for (; l.length > 0; l.length--)
				l.data[l.length - 1] = l.data[l.length];
			printf("清空完成!\n");
			getchar();
			break;
		case 3:
			free(l.data);
			getchar();
			printf("销毁完成！\n");
			break;
		case 4:
			printf("请输入您要插入的学生的位置，姓名，学号（用空格隔开）\n");
			scanf("%d%s%s", &i, &x.name, &x.id);
			getchar();
			if (insert(&l, i - 1, x) == 1)
				printf("插入完成！\n");
			else
				printf("插入失败！\n");
			break;
		case 5:
			printf("请输入要删除的学生姓名：\n");
			scanf("%s", &x.name);
			getchar();
			if (delete(&l, x) == 1)
				printf("删除完成！\n");
			else
				printf("删除失败！\n");
			break;
		case 6:
			printf("请输入您要查找的学生信息或学号：\n");
			scanf("%s", &m);
			getchar();
			i=search(l, m);
			if (strcmp(l.data[i].name, m) == 0 || strcmp(l.data[i].id, m) == 0)
				printf("%s %s", l.data[i].name, l.data[i].id);
			else
				printf("查无此人!\n");
			break;
		case 7:
			printf("请输入要更新的学生姓名或学号：\n");
			scanf("%s", &m);
			getchar();
			i = search(l, m);
			if (strcmp(l.data[i].name, m) != 0 && strcmp(l.data[i].id, m) != 0)
			{
				printf("查无此人!\n");
				break;
			}
			printf("请输入更新后的学生姓名和学号：(用空格隔开）\n");
			scanf("%s%s", l.data->name, l.data->id);
			getchar();
			printf("更新完成！\n");
			break;
		case 8:
			printf("请输入要查找的学生位置：\n");
			scanf("%d", &i);
			getchar();
			if (i > l.length)
			{
				printf("查询错误!\n");
				break;
			}
			else
				printf("%s %s\n", l.data[i - 1].name, l.data[i - 1].id);
			break;
		case 9:
			for (i = 0; i < l.length; i++)
			{
				printf("%s %s\n", l.data[i].name, l.data[i].id);
			}
			printf("遍历完成!\n");
			getchar();
			break;
		default:
			break;
		}
		printf("按任意键继续\n");
		getchar();
		system("cls");
	}
}

int menu()
{
	int n;
	while(1)
	{
		printf("请选择操作：\n");
		printf("1.创建\n");
		printf("2.清空(请在创建表之后使用)\n");
		printf("3.销毁(请在创建表之后使用)\n");
		printf("4.插入\n");
		printf("5.删除\n");
		printf("6.按值查找\n");
		printf("7.更新某人信息\n");
		printf("8.指定位置查找\n");
		printf("9.遍历\n");
		printf("0.退出\n");
		scanf("%d", &n);
		if (n < 0 || n>9)
		{
			printf("输入有误！请重新输入\n");
		}
		else return n;
	}
}

int create(list *l, int max)
{
	char yn;
	student x;
	int n = 1;
	l->data = (student*)malloc(max * sizeof(student));
	if (l->data == NULL)
		return 0;
	l->length = 0;
	l->listsize = max;
	do
	{
		printf("请输入要插入的第%d个学生的姓名，学号（用空格隔开）\n",n);
		scanf("%s%s", &x.name, &x.id);
		getchar();
		if (insert(l, n - 1, x) == 1)
		{
			printf("是否继续输入？y/n\n");
			scanf("%c", &yn);
			getchar();
		}
		else return 0;
		n++;
	} while (yn == 'y' || yn == 'Y');
	return 1;
}

int insert(list *l, int i,student x)
{
	int p;
	if (i<0 || i>l->length)
	{
		printf("插入位置异常！\n");
		return 0;
	}
	if (l->length > l->listsize)
	{
		printf("容量不够！\n");
		return 0;
	}
	for (p = l->length; p > i; p--)
	{
		l->data[p] = l->data[p - 1];
	}
	l->data[i] = x;
	l->length++;
	return 1;
}

int delete(list *l, student x)
{
	int i, p;
	i=search(*l, x.name);
	for (; i<l->length;i++)
	{
		l->data[i] = l->data[i+1];
	}
	return 1;
}

int search(list l, char m[])
{
	int i;
	for (i = 0; i < l.length; i++)
	{
		if (strcmp(m, l.data[i].name) == 0)
			return i;
		if (strcmp(m, l.data[i].id) == 0)
			return i;
	}
}