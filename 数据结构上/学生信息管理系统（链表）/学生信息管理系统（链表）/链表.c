#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

typedef struct
{
	char name[20];
	char id[20];
}student;

typedef struct node
{
	student data;
	struct node * next;
}node, *lnode;

int menu();
int create(lnode *l);
int insert(lnode l, int i, student x);
int delete(lnode l, int i);
int length(lnode l);
student search(lnode l, student x);
int updata(lnode l, student x);

int main()
{
	int n = 0;
	char name[20];
	char id[20];
	int num;
	int i, j;
	student x;
	lnode l = NULL;
	node s;
	lnode p = NULL;
	while (1)
	{
		n = menu();
		if (n == 0)break;
		switch (n)
		{
		case 1:
			i = create(&l);
			if (i == 0)printf("创建失败!\n");
			else printf("创建完成!\n");
			break;
		case 2:
			p = l;
			while (l->next != NULL)
			{
				while (p->next->next != NULL)
					p = p->next;
				i = delete(p, 1);
				if (i == 0)
				{
					printf("清空失败!\n");
					break;
				}
			}
			if (i == 1)
				printf("清空成功!\n");
			break;
		case 3:
			p = l;
			while (l->next != NULL)
			{
				while (p->next->next != NULL)
					p = p->next;
				i = delete(p, 1);
				if (i == 0)
				{
					printf("销毁失败!\n");
					break;
				}
			}
			free(l);
			l = NULL;
			printf("销毁完成!\n");
			break;
		case 4:
			if (l == NULL)
			{
				printf("请先创建链表！\n");
				break;
			}
			printf("请输入你要插入的学生信息（姓名，学号，用空格隔开）：\n");
			scanf("%s%s", &x.name, &x.id);
			i = insert(l, 1, x);
			if (i == 0)
			{
				printf("插入失败!\n");
			}
			if (i == 1)
			{
				printf("插入成功!\n");
			}
			break;
		case 5:
			printf("请输入您要删除的学生位置:\n");
			scanf("%d", &i);
			j = delete(l, i);
			if (i == 0)
			{
				printf("删除失败!\n");
			}
			if (i == 1)
			{
				printf("删除成功!\n");
			}
			break;
		case 6:
			printf("请选择：\n");
			printf("1.按姓名查找\n");
			printf("2.按学号查找\n");
			scanf("%d", &j);
			if (j == 1)
			{
				printf("请输入要查找的学生的姓名：\n");
				scanf("%s", &x.name);
			}
			if (j == 2)
			{
				printf("请输入要查找的学生的学号：\n");
				scanf("%s", &x.id);
			}
			x = search(l, x);
			if (x.name == NULL || x.id == NULL)
			{
				printf("表中没有这个学生信息。\n");
				break;
			}
			printf("%s %s\n", x.name, x.id);
			break;
		case 7:
			printf("请输入您要更新的学生姓名：\n");
			scanf("%s", &x.name);
			i = updata(l, x);
			if (i == 0)
				printf("更新失败！\n");
			if (i == 1)
				printf("更新成功！\n");
			break;
		case 8:
			p = l;
			printf("请输入您要查找的学生的位置\n");
			scanf("%d", &i);
			for (j = 0; j < i&&p != NULL; j++)
			{
				p = p->next;
			}
			if (p == NULL)
			{
				printf("位置错误！\n");
				free(p);
				break;
			}
			printf("%s %s\n", p->data.name, p->data.id);
			break;
		case 9:
			p = l->next;
			while (p != NULL)
			{
				printf("%s %s\n", p->data.name, p->data.id);
				p = p->next;
			}
			if (p == NULL)
			{
				printf("遍历完成！\n");
				break;
			}
		}
	}
}

int create(lnode *l)
{
	*l = (lnode)malloc(sizeof(node));
	if (*l == NULL)return 0;
	(*l)->next = NULL;
	int i = 1;
	student x;
	char yn;
	do
	{
		printf("请输入第%d个学生姓名和学号，用空格隔开：\n", i);
		scanf("%s%s", &x.name, &x.id);
		getchar();
		insert(*l, i, x);
		i++;
		printf("是否要继续输入？（Y/N）\n");
		yn = getchar();
	} while (yn == 'y' || yn == 'Y');
	return 1;
}

int insert(lnode l, int i, student x)
{
	lnode p = l, s;
	int n;
	s = (lnode)malloc(sizeof(node));
	s->data = x;
	for (n = 0; p != NULL, n < i - 1; n++)
	{
		p = p->next;
	}
	s->next = p->next;
	p->next = s;
}

int menu()
{
	printf("请选择下列操作:\n");
	printf("1.创建表格\n");
	printf("2.清空数据\n");
	printf("3.销毁链表\n");
	printf("4.插入数据\n");
	printf("5.删除数据\n");
	printf("6.按值查找\n");
	printf("7.更新某人信息\n");
	printf("8.指定位置查找\n");
	printf("9.遍历\n");
	printf("0.退出\n");
	int n;
	scanf("%d", &n);
	if (n >= 0 && n <= 9)
		return n;
	printf("输入错误请重新输入\n");
	return 0;
}

int delete(lnode l, int i)
{
	int n;
	lnode p = l, q;
	for (n = 0; n < i - 1 && p->next != NULL; n++)
	{
		p = p->next;
	}
	if (p->next == NULL && n >= i)
	{
		return 0;
	}
	q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

int length(lnode l)
{
	int n;
	lnode p = l;
	for (n = 0; p->next != NULL; n++)
	{
		p = p->next;
	}
	return n;
}

student search(lnode l, student x)
{
	lnode p = l;
	while (p != NULL)
	{
		if (strcmp(p->data.name, x.name) == 0)
		{
			strcpy(x.id, p->data.id);
			return x;
		}
		if (strcmp(p->data.id, x.id) == 0)
		{
			strcpy(x.name, p->data.name);
			return x;
		}
		p = p->next;
	}
	return x;
}

int updata(lnode l, student x)
{
	lnode p = l;
	while (p != NULL)
	{
		if (strcmp(x.name, p->data.name) == 0)break;
		p = p->next;
	}
	if (p == NULL)
		return 0;
	printf("请输入更新后的学号：\n");
	scanf("%s", p->data.id);
	return 1;
}