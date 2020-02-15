#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define VNUM 100
#define MAXNUM 10000

typedef struct Stack
{
	int data;
	struct Stack *next;
}Stack, *StackLink;														/*栈*/
typedef struct ArcNode
{
	int adjvex, info;
	struct ArcNode * nextArc;
}ArcNode;
typedef struct Vertexnode
{
	char data;
	int id;
	ArcNode *firstArc;
}VertexNode;
typedef struct AlGraph
{
	VertexNode adjlist[VNUM];
	int vexNum, arcNum;
}ALGraph;																/*图的邻接表*/

int initStack(StackLink *l)
{
	(*l) = (StackLink)malloc(sizeof(Stack));
	if (*l == NULL)
		return 0;
	(*l)->next = NULL;
	return 1;
}

int push(StackLink l, int x)
{
	StackLink s;
	initStack(&s);
	if (s == NULL)
		return 0;
	s->next = l->next;
	l->next = s;
	s->data = x;
	return 1;
}

int pop(StackLink l)
{
	StackLink p;
	int x;
	x = l->next->data;
	p = l->next;
	l->next = p->next;
	free(p);
	return x;
}

int ifemptyStack(StackLink l)
{
	if (l->next == NULL)
		return 1;
	else
		return 0;
}

void print_adjlistnex(ALGraph G)
{
	int i, j;
	printf("图中结点元素如下:\n");
	for (i = 0; i < G.vexNum; i++)
	{
		printf("%d.%c ", i + 1, G.adjlist[i].data);
	}
}

void print_adjlist(ALGraph G)
{
	int i, j;
	ArcNode *p;
	printf("此图的邻接表是：\n");
	for (i = 0; i < G.vexNum; i++)
	{
		printf("%c", G.adjlist[i].data);
		if (G.adjlist[i].firstArc)
		{
			p = G.adjlist[i].firstArc;
			while (p)
			{
				printf("->%c", G.adjlist[p->adjvex].data);
				p = p->nextArc;
			}
		}
		printf("\n");
	}
}

void create_yes_adjlist(ALGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	ArcNode *p;
	printf("请输入顶点个数和弧数,用空格隔开\n");
	scanf("%d%d", &G->vexNum, &G->arcNum);
	getchar();
	for (i = 0; i < G->vexNum; i++)
	{
		printf("请输入第%d个顶点的数据\n", i + 1);
		scanf("%c", &G->adjlist[i].data);
		getchar();
		G->adjlist[i].firstArc = NULL;
	}
	print_adjlistnex(*G);
	for (k = 0; k < G->arcNum; k++)
	{
		printf("请输入相邻的两个顶点的序号（第一个为出点，第二个为入点）和弧度的权值，用空格隔开（还有%d条边需要输入）\n", G->arcNum - k);
		scanf("%d%d%d", &i, &j, &m);
		getchar();
		i--; j--;
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextArc = G->adjlist[i].firstArc;
		p->info = m;
		G->adjlist[i].firstArc = p;
	}
	printf("邻接表创建成功\n");
}

void critical_path(ALGraph G)
{
	int i, n = G.vexNum, j, k;
	int ve[VNUM], vl[VNUM], ee, el;
	StackLink s1 = NULL, s2 = NULL;
	ArcNode *p;
	char *flag;
	for (i = 0; i < G.vexNum; i++)
		G.adjlist[i].id = 0;
	for (i = 0; i < G.vexNum; i++)
	{
		if (G.adjlist[i].firstArc)
		{
			p = G.adjlist[i].firstArc;
			while (p)
			{
				G.adjlist[p->adjvex].id++;
				p = p->nextArc;
			}
		}
	}
	for (i = 0; i < G.vexNum; i++)
	{
		ve[i] = 0;
	}
	initStack(&s1);
	initStack(&s2);
	for (i = 0; i < G.vexNum; i++)
		if (G.adjlist[i].id == 0)
			push(s1, i);
	while (!ifemptyStack(s1))
	{
		j = pop(s1);
		push(s2, j);
		p = G.adjlist[j].firstArc;
		while (p)
		{
			k = p->adjvex;
			G.adjlist[k].id--;
			if (G.adjlist[k].id == 0)
				push(s1, k);
			if ((ve[j] + p->info) > ve[k])
				ve[k] = ve[j] + p->info;
			p = p->nextArc;
		}
	}
	for (i = 0; i < G.vexNum; i++)
		vl[i] = ve[G.vexNum - 1];
	while (!ifemptyStack(s2))
	{
		j = pop(s2);
		p = G.adjlist[j].firstArc;
		while (p != NULL)
		{
			k = p->adjvex;
			if ((vl[k] - p->info) < vl[j])
				vl[j] = vl[k] - p->info;
			p = p->nextArc;
		}
	}
	printf("图中的关键路径有:\n");
	for (j = 0; j < G.vexNum; j++)
	{
		p = G.adjlist[j].firstArc;
		while (p != NULL)
		{
			k = p->adjvex;
			ee = ve[j];
			el = vl[k] - p->info;
			if (ee == el)
				printf("%c到%c\n", G.adjlist[j].data, G.adjlist[k].data);
			p = p->nextArc;
		}
	}
}

void main()
{
	ALGraph G;
	create_yes_adjlist(&G);
	printf("\n");
	critical_path(G);
	printf("按回车键结束程序");
	getchar();
}