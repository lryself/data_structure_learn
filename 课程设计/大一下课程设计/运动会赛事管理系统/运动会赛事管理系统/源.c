#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100

typedef struct
{
	char id[MAX];
	char name[MAX];
	char college[MAX];
	char sport[MAX];
	float sorce;
}student;								/*运动员*/
typedef struct linklist
{
	student data;
	struct linklist *next;
}linklist,*List;				/*用户链表*/
typedef struct sportlist
{
	char name[MAX];
	struct sportlist *next;
	linklist *data;
}sportlist,*Slist;			/*项目链表*/

FILE *TXT;

void lock(List l);

int menu();

int menu1();

int menu2();

int menu3();

int menu6();

int initList(List * l);

int inseartList(List l, student x);

int deleteList(List l, char name[]);

List searchList(List l, char name[]);

void readpeople(Slist t);

void writepeople(Slist t);

void writesport(Slist t);

void writeid(List t);

void readsport(Slist t);

void readid(List t);

int sortSlist(Slist l);

int sortcollege(List l);

int sortsorce(List l);

int initSlist(Slist * l);

int inseartSlist(Slist l, char a[]);

int deleteSlist(Slist l, char name[]);

Slist searchSlist(Slist l, char name[]);

void 用户管理(List l);

void 运动员管理(Slist l);

void 项目管理(Slist l);

void 报名管理(Slist l,Slist g);

void 成绩管理(Slist l);

int updataList(List l, char name[], char a[]);

void main()
{
	Slist 项目,运动员;
	List 用户;
	initList(&用户);
	TXT = fopen("用户储存.txt", "r");
	readid(用户);
	fclose(TXT);
	lock(用户);
	initSlist(&项目);
	initSlist(&运动员);
	TXT = fopen("项目储存.txt", "r");
	readsport(项目);
	fclose(TXT);
	TXT = fopen("运动员储存.txt", "r");
	readpeople(运动员);
	fclose(TXT);
	while (1)
	{
		switch (menu())
		{
		case 0:
			exit("1");
		case 1:
			TXT = fopen("用户储存.txt", "w");
			用户管理(用户);
			fclose(TXT);
			break;
		case 2:
			TXT = fopen("项目储存.txt", "w");
			项目管理(项目);
			fclose(TXT);
			break;
		case 3:
			运动员管理(运动员);
			break;
		case 4:
			报名管理(项目,运动员);
			break;
		case 5:
			TXT = fopen("项目储存.txt", "w");
			成绩管理(项目);
			fclose(TXT);
			break;
		}
		printf("按回车键继续\n");
		getchar();
	}
}

void lock(List l)
{
	char name[1000], id[1000];
	student x;
	printf("请输入用户名和密码，用空格隔开\n");
	scanf("%s%s", name, id);
	getchar();
	x=searchList(l, name)->next->data;
	if (strcmp(x.id, id) == 0)
		return;
	printf("密码或用户名有误\n");
	printf("按回车键退出程序\n");
	getchar();
	exit(1);
}

int menu()
{
	int n;
	system("cls");
	printf("欢迎来到运动会管理系统！\n");
	printf("请选择下列操作：\n");
	printf("0.退出\n");
	printf("1.用户管理\n");
	printf("2.项目管理\n");
	printf("3.运动员管理\n");
	printf("4.报名管理\n");
	printf("5.成绩管理\n");
	scanf("%d", &n);
	getchar();
	return n;
}

int menu1()
{
	int n;
	system("cls");
	printf("运动员管理:");
	printf("请选择您要进行的操作:\n");
	printf("0.退出运动员管理\n");
	printf("1.查找人员信息\n");
	printf("2.遍历运动员信息\n");
	scanf("%d", &n);
	getchar();
	return n;
}

int menu2()
{
	int n;
	system("cls");
	printf("项目管理:");
	printf("请选择您要进行的操作:\n");
	printf("0.退出项目管理\n");
	printf("1.添加项目\n");
	printf("2.删除项目\n");
	printf("3.遍历项目信息\n");
	scanf("%d", &n);
	getchar();
	return n;
}

int menu3()
{
	int n;
	system("cls");
	printf("用户管理:");
	printf("请选择您要进行的操作:\n");
	printf("0.退出用户管理\n");
	printf("1.添加用户\n");
	printf("2.删除用户\n");
	printf("3.查询用户信息\n");
	scanf("%d", &n);
	getchar();
	return n;
}

int menu4()
{
	int n;
	system("cls");
	printf("用户管理:");
	printf("请选择您要进行的操作:\n");
	printf("0.退出用户管理\n");
	printf("1.添加用户\n");
	printf("2.删除用户\n");
	printf("3.遍历用户信息\n");
	scanf("%d", &n);
	getchar();
	return n;
}

int menu5()
{
	int n;
	system("cls");
	printf("报名管理:");
	printf("请选择您要进行的操作:\n");
	printf("0.退出报名管理\n");
	printf("1.添加运动员\n");
	printf("2.删除运动员\n");
	printf("3.遍历报名信息\n");
	scanf("%d", &n);
	getchar();
	return n;
}

int menu6()
{
	int n;
	system("cls");
	printf("成绩管理:");
	printf("请选择您要进行的操作:\n");
	printf("0.退出成绩管理\n");
	printf("1.添加运动员成绩\n");
	printf("2.删除运动员成绩\n");
	printf("3.查询某一项目中某一运动员的成绩信息\n");
	printf("4.遍历所有成绩\n");
	scanf("%d", &n);
	getchar();
	return n;
}

int initList(List *l)
{
	(*l) = (List)malloc(sizeof(linklist));
	if (*l)
	{
		(*l)->next = NULL;
		return 1;
	}
	else
		return 0;
}

int inseartList(List l, student x)
{
	List p;
	initList(&p);
	if (!p)
		return 0;
	p->data = x;
	p->next = l->next;
	l->next = p;
	return 1;
}

int deleteList(List l, char name[])
{
	List p = searchList(l, name);
	List q;
	if (!p)
		return 0;
	q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

List searchList(List l, char name[])
{
	while(l->next != NULL)
	{
		if (strcmp(l->next->data.name,name)==0)
			return l;
		l = l->next;
	}
	return NULL;
}

void readpeople(Slist t)
{
	Slist p=NULL;
	char ch;
	student *stu;
	List s=NULL;
	while ((ch = fgetc(TXT)) != EOF)
	{
		fgetc(TXT);
		if (ch == '!')
		{
			p = (Slist)malloc(sizeof(sportlist));
			p->next = t->next;
			t->next = p;
			fscanf(TXT, "%s", &p->name);
			fgetc(TXT);
			initList(&s);
			p->data = s;
		}
		if (ch == '@')
		{
			(stu) = (student*)malloc(sizeof(student));
			fscanf(TXT, "%s", stu->name);
			fgetc(TXT);
			fscanf(TXT, "%s", stu->id);
			fgetc(TXT);
			fscanf(TXT, "%s", stu->sport);
			fgetc(TXT);
			strcpy(stu->college,p->name);
			inseartList(s, *stu);
		}
	}
}

void writepeople(Slist t)
{
	List p;
	while (t)
	{
		fprintf(TXT, "! %s\n", t->name);
		p = t->data->next;
		sortid(p);
		while (p)
		{
			fprintf(TXT, "@ %s %s %s\n", p->data.name, p->data.id, p->data.sport);
			p = p->next;
		}
		t = t->next;
	}
}

void writesport(Slist t)
{
	List p;
	while (t)
	{
		fprintf(TXT, "! %s\n", t->name);
		p = t->data->next;
		sortsorce(p);
		sortcollege(p);
		while (p)
		{
			fprintf(TXT, "@ %s %s %f %s\n", p->data.name, p->data.id, p->data.sorce,p->data.college);
			p = p->next;
		}
		t = t->next;
	}
}

void writeid(List t)
{
	while (t)
	{
		fprintf(TXT, "%s %s\n", t->data.name,t->data.id);
		t = t->next;
	}

}

void readsport(Slist t)
{
	Slist p=NULL;
	char ch;
	student *stu;
	List s=NULL;
	while ((ch = fgetc(TXT)) != EOF)
	{
		fgetc(TXT);
		if (ch == '!')
		{
			p = (Slist)malloc(sizeof(sportlist));
			p->next = t->next;
			t->next = p;
			fscanf(TXT, "%s", &p->name);
			fgetc(TXT);
			initList(&s);
			p->data = s;
		}
		if (ch == '@')
		{
			(stu) = (student*)malloc(sizeof(student));
			fscanf(TXT, "%s", stu->name);
			fgetc(TXT);
			fscanf(TXT, "%s", stu->id);
			fgetc(TXT);
			fscanf(TXT, "%f", &stu->sorce);
			fgetc(TXT);
			fscanf(TXT, "%s", stu->college);
			fgetc(TXT);
			inseartList(s, *stu);
		}
	}
}

void readid(List t)
{
	List p = NULL;
	char ch;
	student *stu;
	initList(&p);
	(stu) = (student*)malloc(sizeof(student));
	while (1)
	{
		if (fscanf(TXT, "%s%s", stu->name,stu->id) == EOF)
		{
			break;
		}
		fgetc(TXT);
		inseartList(t, *stu);
		(stu) = (student*)malloc(sizeof(student));
	}
}

int sortSlist(Slist l)
{
	Slist p;
	if (l->next == NULL)
		return 0;
	p = l->next;
	while (p->next != NULL)
	{
		sortcollege(p->data);
		p = p->next;
	}
	return 1;
}

int sortcollege(List l)
{
	List p;
	if (l->next == NULL)
		return 0;
	p = l->next;
	student x;
	while (p->next != NULL)
	{
		if (strcmp(p->data.college,p->next->data.college)>0)
		{
			x = p->next->data;
			p->next->data = p->data;
			p->data = x;
			p = l;
			continue;
		}
		p = p->next;
	}
	return 1;
}

int sortid(List l)
{
	List p;
	if (l->next == NULL)
		return 0;
	p = l->next;
	student x;
	while (p->next != NULL)
	{
		if (strcmp(p->data.id,p->next->data.id)>0)
		{
			x = p->next->data;
			p->next->data = p->data;
			p->data = x;
			p = l;
			continue;
		}
		p = p->next;
	}
	return 1;
}

int sortsorce(List l)
{
	List p;
	if (l->next == NULL)
		return 0;
	p = l->next;
	student x;
	while (p->next != NULL)
	{
		if (p->data.sorce < p->next->data.sorce)
		{
			x = p->next->data;
			p->next->data = p->data;
			p->data = x;
			p = l;
			continue;
		}
		p = p->next;
	}
	return 1;
}

int initSlist(Slist *l)
{
	(*l) = (Slist)malloc(sizeof(sportlist));
	if (*l)
	{
		(*l)->next = NULL;
		return 1;
	}
	else
		return 0;
}

int inseartSlist(Slist l, char a[])
{
	Slist p;
	List q;
	initSlist(&p);
	initList(&q);
	if (!p)
		return 0;
	strcpy(p->name, a);
	p->next = l->next;
	l->next = p;
	p->data = q;
	return 1;
}

int deleteSlist(Slist l, char name[])
{
	Slist p = searchSlist(l, name);
	Slist q;
	if (!p)
		return 0;
	q = p->next;
	p->next = q->next;
	free(q);
	return 1;
}

Slist searchSlist(Slist l, char name[])
{
	l = l->next;
	while (l!=NULL)
	{
		if (strcmp(l->name,name)==0)
			return l;
		l = l->next;
	}
	return NULL;
}

void 用户管理(List l)
{
	student x;
	List p;
	while (1)
	{
		switch (menu4())
		{
		case 0:
			writeid(l->next);
			return;
			break;
		case 1:
			printf("请输入您要添加的用户名称和密码，用空格隔开\n");
			scanf("%s%s", &x.name,&x.id);
			getchar();
			inseartList(l, x);
			break;
		case 2:
			printf("请输入您要删除的用户名称(用户已存在)\n");
			scanf("%s", &x.name);
			getchar();
			p = l;
			while (p->next)
			{
				if (strcmp(p->next->data.name, x.name) == 0)
				{
					p->next = p->next->next;
					break;
				}
			}
			break;
		case 3:
			p = l->next;
			while (p)
			{
				printf("%s %s\n", p->data.name,p->data.id);
				p = p->next;
			}
		}
		printf("按回车键继续\n");
		getchar();
	}
}

void 运动员管理(Slist l)
{
	student x;
	Slist p;
	List q;
	while (1)
	{
		switch (menu1())
		{
		case 0:
			return;
			break;
		case 1:
			p = l->next;
			printf("请输入您要查找的用户的姓名\n");
			scanf("%s", &x.name);
			getchar();
			strcpy(x.id,"-1");
			while (p)
			{
				if (searchList(p->data, x.name))
				{
					x = (searchList(p->data, x.name)->next->data);
					break;
				}
				p = p->next;
			}
			if (strcmp(x.id,"-1")==0)
				printf("用户不存在\n");
			else
				printf("用户的姓名：%s,学号：%s,院系：%s\n", x.name, x.id, x.college);
		case 2:
			p = l->next;
			while (p)
			{
				printf("%s\n", p->name);
				if (p->data)
				{
					q = p->data->next;
					while (q)
					{
						x = q->data;
						printf(" %s %s %s\n", x.name, x.id, x.sport);
						q = q->next;
					}
				}
				p = p->next;
			}
		}
		printf("按回车键继续\n");
		getchar();
	}
}

void 项目管理(Slist l)
{
	student x;
	Slist p;
	while (1)
	{
		switch (menu2())
		{
		case 0:
			writesport(l->next);
			return;
			break;
		case 1:
			printf("请输入您要添加的项目名称\n");
			scanf("%s",&x.sport);
			getchar();
			inseartSlist(l, x.sport);
			break;
		case 2:
			printf("请输入您要删除的项目名称(项目已存在)\n");
			scanf("%s", &x.sport);
			getchar();
			p = l;
			while (p->next)
			{
				if (strcmp(p->next->name, x.sport) == 0)
				{
					p->next = p->next->next;
					break;
				}
			}
			break;
		case 3:
			p = l->next;
			while (p)
			{
				printf("%s\n", p->name);
				p = p->next;
			}
		}
		printf("按回车键继续\n");
		getchar();
	}
}

void 报名管理(Slist l,Slist g)
{
	student x;
	Slist p;
	List q;
	while (1)
	{
		switch (menu5())
		{
		case 0:
			TXT = fopen("运动员储存.txt", "w");
			writepeople(g->next);
			fclose(TXT);
			TXT = fopen("项目储存.txt", "w");
			writesport(l->next);
			fclose(TXT);
			return;
			break;
		case 1:
			printf("请输入您要添加的用户的姓名，学号，院系，项目，用空格隔开\n");
			scanf("%s%s%s%s", &x.name, &x.id, &x.college,&x.sport);
			getchar();
			x.sorce = 0;
			if (searchSlist(l, x.sport))
				inseartList(searchSlist(l, x.sport)->data, x);
			else
			{
				inseartSlist(l, x.sport);
				inseartList((searchSlist(l, x.sport)->data), x);
			}
			if (searchSlist(g, x.college))
				inseartList(searchSlist(g, x.college), x);
			else
			{
				inseartSlist(g, x.college);
				inseartList((searchSlist(g, x.college)->data), x);
			}
			break;
		case 2:
			printf("请输入您要删除的用户的姓名，院系，项目，用空格隔开\n");
			scanf("%s%s%s", &x.name, &x.college,&x.sport);
			getchar();
			deleteList(searchSlist(l, x.sport)->data, x.name);
			deleteList(searchSlist(g, x.college)->data, x.name);
			break;
		case 3:
			p = l->next;
			while (p)
			{
				printf("%s\n", p->name);
				if (p->data)
				{
					q = p->data->next;
					while (q)
					{
						x = q->data;
						printf(" %s %s %s\n", x.name, x.id, x.college);
						q = q->next;
					}
				}
				p = p->next;
			}
		}
		printf("按回车键继续\n");
		getchar();
	}
}

void 成绩管理(Slist l)
{
	student x;
	Slist p;
	List q;
	while (1)
	{
		switch (menu6())
		{
		case 0:
			writesport(l->next);
			return;
			break;
		case 1:
			printf("请输入您要添加的运动员的姓名，成绩，项目，用空格隔开\n");
			scanf("%s%f%s", &x.name, &x.sorce, &x.sport);
			getchar();
			if (searchSlist(l, x.sport))
				searchList(searchSlist(l, x.sport)->data, x.name)->next->data.sorce=x.sorce;
			else
			{
				inseartSlist(l, x.sport);
				inseartList(searchSlist(l, x.sport)->data, x);
			}
			break;
		case 2:
			printf("请输入您要删除的用户的姓名，项目，用空格隔开\n");
			scanf("%s%s", &x.name, &x.sport);
			getchar();
			searchList(searchSlist(l, x.sport), x.name)->next->data.sorce = 0;
			break;
		case 3:
			p = l;
			printf("请输入您要查找的用户的姓名,项目，用空格隔开\n");
			scanf("%s%s", &x.name,&x.sport);
			getchar();
			strcpy(x.id, "-1");
			while (p)
			{
				if (searchSlist(p, x.sport))
				{
					x = searchList(searchSlist(p, x.sport)->data,x.name)->next->data;
					break;
				}
				p = p->next;
			}
			if (strcmp(x.id, "-1") == 0)
				printf("用户不存在\n");
			else
				printf("用户的姓名：%s,学号：%s,院系：%s,成绩：%f\n", x.name, x.id, x.college,x.sorce);
		case 4:
			p = l->next;
			while (p)
			{
				printf("%s\n", p->name);
				if (p->data)
				{
					q = p->data->next;
					sortsorce(q);
					sortcollege(q);
					while (q)
					{
						x = q->data;
						printf(" %s %s %s %f\n", x.name, x.id, x.college, x.sorce);
						q = q->next;
					}
				}
				p = p->next;
			}
		}
		printf("按回车键继续\n");
		getchar();
	}
}

int updataList(List l,char name[], char a[])
{
	l = searchList(l, name)->next;
	if (!l->data.name)
		return 0;
	strcpy(l->data.sport, a);
	return 1;
}