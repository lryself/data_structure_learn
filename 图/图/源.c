#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define VNUM 100
#define MAXNUM 10000

typedef struct QNode
{
	int data;
	struct QNode *next;
}QNode, *QueueLink;														/*队列结点*/
typedef struct QLink
{
	QueueLink first;
	QueueLink last;
}QLink;																	/*队列*/
typedef struct Stack
{
	int data;
	struct Stack *next;
}Stack, *StackLink;														/*栈*/
typedef struct
{
	char vexs[VNUM];
	int arcs[VNUM][VNUM];
	int vexNum, arcNum;
}MGraph;																		/*图的邻接矩阵*/
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
typedef struct Graph
{
	MGraph M;
	ALGraph A;
}Graph;																	/*图*/
typedef struct
{
	int vi, weigh;
}LowCost;
typedef char ZFC[VNUM];

FILE *TXT;

int menu(int n);
//队列操作
void initQueue(QLink *q);																		/*初始化队列*/
void EnQueue(QLink *q, int t);																	/*进队*/
int DeQueue(QLink *q);																			/*出队*/
int ifemptyQueue(QLink q);																		/*判断队空*/
int GetQueueHead(QLink q);																		/*得到队头*/
//栈操作
int initStack(StackLink *l);																	/*初始化栈*/
int push(StackLink l, int x);																	/*进栈*/
int pop(StackLink l);																			/*出栈*/
int ifemptyStack(StackLink l);																	/*判断栈空*/
//图操作
void create_no_adjlist(ALGraph *G);																//创建无向图非连通图的邻接表储存结构
void create_no_matrix(MGraph *G);																//创建无向图非连通图的邻接矩阵储存结构
void create_yes_adjlist(ALGraph *G);															//创建有向图非连通图的邻接表储存结构
void create_yes_matrix(MGraph *G);																//创建有向图非连通图的邻接矩阵储存结构
void print_adjlistnex(ALGraph G);																//输出邻接表结点的附属结点
void print_adjlist(ALGraph G);																	//输出无向图的邻接表
void df_traver(ALGraph G, int v, int visited[]);												//输出深度遍历的附属函数
int df_traverGraph(ALGraph G);																	//输出基于邻接表的深度遍历序列
void bf_traver(ALGraph G, int v0, int visited[]);												//输出广度遍历的附属函数
void bf_traverGraph(ALGraph G);																	//输出基于邻接表的广度遍历序列
void prim(MGraph G);																			//普里姆算法求一个最小生成树
void Kruskal(MGraph G);																			//克鲁斯卡尔求一个最小生成树
int find(ZFC * s, int n, char c);																//迪杰斯特拉附属函数
void dijkstra(MGraph G, int v);																	//迪杰斯特拉算法求一个源点出发到所有顶点的最短路径
void Floyd(MGraph G);																			//弗洛伊德算法求所有源点之间的最短路径
void DFS(MGraph G, int i, int path[], int visit[], int *n);										//求简单路径
int top_sort(ALGraph G);																		//求拓扑序列
void critical_path(ALGraph G);																	//求关键路径
int TopologicalSort(ALGraph G, int index[]);													//寻找关键路径的同期课程
void FindiInDegree(ALGraph * G);																//初始化各点入度
void Hamilton(MGraph G);																		//输出一条哈密尔顿链

void main()
{
	int graphid = 0;
	int lt, n;
	Graph G;
	printf("请选择您要操作的图类型：\n1.无向图\n2.有向图\n");
	scanf("%d", &graphid);
	while (1)
	{
		switch (menu(graphid))
		{
		case 0:
			exit(1);
		case 1:
			if (graphid == 1)
			{
				create_no_adjlist(&G.A);
				create_no_matrix(&G.M);
			}
			if (graphid == 2)
			{
				create_yes_adjlist(&G.A);
				create_yes_matrix(&G.M);
			}
			break;
		case 2:
			print_adjlist(G.A);
			break;
		case 3:
			df_traverGraph(G.A);
			break;
		case 4:
			bf_traverGraph(G.A);
			break;
		case 5:
			prim(G.M);
			break;
		case 6:
			Kruskal(G.M);
			break;
		case 7:
			printf("请输入一个单元点:\n");
			scanf("%d", &n);
			getchar();
			dijkstra(G.M, n);
			break;
		case 8:
			Floyd(G.M);
			break;
		case 9:
			Hamilton(G.M);
			break;
		case 10:
			critical_path(G.A);
			break;
		}
		printf("\n按回车键继续\n");
		getchar();
		system("cls");
	}
}

int menu(int n)
{
	int i;
	printf("请选择您要进行的操作的序号：\n");
	printf("0.退出程序\n");
	if (n == 1)//无向图
	{
		printf("1.创建无向非连通图的邻接表和邻接矩阵储存结构（注：本程序中所有的创建操作输入均从 输入.txt 中读取\n");
	}
	if (n == 2)
	{
		printf("1.创建有向非连通图的邻接表和邻接矩阵储存结构（注：本程序中所有的创建操作输入均从 输入.txt 中读取\n");
	}
	printf("2.输出邻接表\n");
	printf("3.输出深度遍历序列\n");
	printf("4.输出广度遍历序列\n");
	printf("5.通过普里姆算法求最小生成树\n");
	printf("6.通过克鲁斯卡尔算法求最小生成树\n");
	printf("7.通过迪杰斯特拉算法求单位点的最短路径\n");
	printf("8.通过弗洛伊德算法求每一对顶点之间的最短路径\n");
	printf("9.求图中一条哈密尔顿链\n");
	printf("10.求图中一条关键路径\n");
	scanf("%d", &i);
	getchar();
	return i;
}

void create_no_adjlist(ALGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	ArcNode *p;
	TXT = fopen("输入.txt", "r");
	printf("请输入顶点个数和弧数,用空格隔开\n");
	fscanf(TXT, "%d%d", &G->vexNum, &G->arcNum);
	fgetc(TXT);
	for (i = 0; i < G->vexNum; i++)
	{
		printf("请输入第%d个顶点的数据\n", i + 1);
		fscanf(TXT, "%c", &G->adjlist[i].data);
		fgetc(TXT);
		G->adjlist[i].firstArc = NULL;
	}
	print_adjlistnex(*G);
	for (k = 0; k < G->arcNum; k++)
	{
		printf("请输入相邻的两个顶点的序号和弧度的权值，用空格隔开（还有%d条边需要输入）\n", G->arcNum - k);
		fscanf(TXT, "%d%d%d", &i, &j, &m);
		i--; j--;
		fgetc(TXT);
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextArc = G->adjlist[i].firstArc;
		p->info = m;
		G->adjlist[i].firstArc = p;
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = i;
		p->nextArc = G->adjlist[j].firstArc;
		p->info = m;
		G->adjlist[j].firstArc = p;
	}
	fclose(TXT);
	printf("邻接表创建成功\n");
}

void create_no_matrix(MGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	TXT = fopen("输入.txt", "r");
	printf("请输入顶点个数和弧数，用空格隔开\n");
	fscanf(TXT, "%d%d", &G->vexNum, &G->arcNum);
	fgetc(TXT);
	for (i = 0; i < G->vexNum; i++)
	{
		printf("请输入第%d个顶点的数据\n", i + 1);
		fscanf(TXT, "%c", &G->vexs[i]);
		fgetc(TXT);
	}
	for (i = 0; i < G->vexNum; i++)
		for (j = 0; j < G->vexNum; j++)
			G->arcs[i][j] = MAXNUM;
	for (i = 0; i < G->vexNum; i++)
		G->arcs[i][i] = 0;
	for (k = 0; k < G->arcNum; k++)
	{
		printf("请输入相邻的两个顶点的序号和弧度的权值，用空格隔开（还有%d条边需要输入）\n", G->arcNum - k);
		fscanf(TXT, "%d%d%d", &i, &j, &m);
		G->arcs[i - 1][j - 1] = m;
		G->arcs[j - 1][i - 1] = m;
	}
	fclose(TXT);
	printf("邻接矩阵创建成功\n");
}

void create_yes_adjlist(ALGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	ArcNode *p;
	TXT = fopen("输入.txt", "r");
	printf("请输入顶点个数和弧数,用空格隔开\n");
	fscanf(TXT, "%d%d", &G->vexNum, &G->arcNum);
	fgetc(TXT);
	for (i = 0; i < G->vexNum; i++)
	{
		printf("请输入第%d个顶点的数据\n", i + 1);
		fscanf(TXT, "%c", &G->adjlist[i].data);
		fgetc(TXT);
		G->adjlist[i].firstArc = NULL;
	}
	print_adjlistnex(*G);
	for (k = 0; k < G->arcNum; k++)
	{
		printf("请输入相邻的两个顶点的序号（第一个为出点，第二个为入点）和弧度的权值，用空格隔开（还有%d条边需要输入）\n", G->arcNum - k);
		fscanf(TXT, "%d%d%d", &i, &j, &m);
		fgetc(TXT);
		i--; j--;
		p = (ArcNode *)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextArc = G->adjlist[i].firstArc;
		p->info = m;
		G->adjlist[i].firstArc = p;
	}
	fclose(TXT);
	printf("邻接表创建成功\n");
}

void create_yes_matrix(MGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	TXT = fopen("输入.txt", "r");
	printf("请输入顶点个数和弧数，用空格隔开\n");
	fscanf(TXT, "%d%d", &G->vexNum, &G->arcNum);
	fgetc(TXT);
	for (i = 0; i < G->vexNum; i++)
	{
		printf("请输入第%d个顶点的数据\n", i + 1);
		fscanf(TXT, "%c", &G->vexs[i]);
		fgetc(TXT);
	}
	for (i = 0; i < G->vexNum; i++)
		for (j = 0; j < G->vexNum; j++)
			G->arcs[i][j] = MAXNUM;
	for (i = 0; i < G->vexNum; i++)
		G->arcs[i][i] = 0;
	for (k = 0; k < G->arcNum; k++)
	{
		printf("请输入相邻的两个顶点的序号（第一个为出点，第二个为入点）和弧度的权值，用空格隔开（还有%d条边需要输入）\n", G->arcNum - k);
		fscanf(TXT, "%d%d%d", &i, &j, &m);
		G->arcs[i - 1][j - 1] = m;
	}
	fclose(TXT);
	printf("邻接矩阵创建成功\n");
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

void df_traver(ALGraph G, int v, int visited[])
{
	int w = -1;
	ArcNode *p;
	printf("%c ", G.adjlist[v].data);
	visited[v] = 1;
	p = G.adjlist[v].firstArc;
	if (p)
		w = G.adjlist[v].firstArc->adjvex;
	while (w != -1)
	{
		if (visited[w] == 0)
		{
			df_traver(G, w, visited);
		}
		if (p->nextArc)
		{
			p = p->nextArc;
			w = p->adjvex;
		}
		else w = -1;
	}
}

int df_traverGraph(ALGraph G)
{
	int v, x = 0;
	int visited[VNUM];
	for (v = 0; v < G.vexNum; v++)
		visited[v] = 0;
	for (v = 0; v < G.vexNum; v++)
	{
		if (visited[v] == 0)
		{
			df_traver(G, v, visited);
			x++;
		}
	}
	return x;
}

void bf_traver(ALGraph G, int v0, int visited[])
{
	QLink Q;
	ArcNode *p;
	int v, w;
	initQueue(&Q);
	printf("%c ", G.adjlist[v0].data);
	visited[v0] = 1;
	EnQueue(&Q, v0);
	while (!ifemptyQueue(Q))
	{
		v = DeQueue(&Q);
		p = G.adjlist[v].firstArc;
		while (p != NULL)
		{
			w = p->adjvex;
			if (visited[w] == 0)
			{
				printf("%c ", G.adjlist[w].data);
				visited[w] = 1;
				EnQueue(&Q, w);
			}
			p = p->nextArc;
		}
	}
}

void bf_traverGraph(ALGraph G)
{
	int v, x = 0;
	int visited[VNUM];
	for (v = 0; v < G.vexNum; v++)
		visited[v] = 0;
	for (v = 0; v < G.vexNum; v++)
	{
		if (visited[v] == 0)
		{
			bf_traver(G, v, visited);
			x++;
		}
	}
	return x;
}

void prim(MGraph G)
{
	int mincost, i, j, k;
	LowCost *lowcost = (LowCost *)malloc(sizeof(LowCost)*G.vexNum);
	for (i = 0; i < G.vexNum; i++)
	{
		lowcost[i].vi = 0;
		lowcost[i].weigh = G.arcs[0][i];
	}
	lowcost[0].weigh = 0;
	printf("最短生成树的按边输出为：\n");
	for (i = 1; i < G.vexNum; i++)
	{
		mincost = MAXNUM;
		for (j = 0; j < G.vexNum; j++)
		{
			if (lowcost[j].weigh < mincost&&lowcost[j].weigh != 0)
			{
				mincost = lowcost[j].weigh;
				k = j;
			}
		}
		printf("%c %c %d\n", G.vexs[lowcost[k].vi], G.vexs[k], mincost);
		lowcost[k].weigh = 0;
		for (j = 0; j < G.vexNum; j++)
		{
			if (G.arcs[k][j] < lowcost[j].weigh)
			{
				lowcost[j].weigh = G.arcs[k][j];
				lowcost[j].vi = k;
			}
		}
	}
}

void Kruskal(MGraph G)
{
	int i, j, k, t, p, q, x[VNUM][4];
	ZFC c[VNUM];
	for (i = 0; i < G.vexNum; i++)
	{
		c[i][0] = i + 48;
		c[i][1] = '\0';
	}
	for (i = 0, k = 0; i < G.vexNum; i++)
	{
		for (j = i; j < G.vexNum; j++)
		{
			if (G.arcs[i][j] != 0 && G.arcs[i][j] != MAXNUM)
			{
				x[k][0] = i;
				x[k][1] = j;
				x[k][2] = G.arcs[i][j];
				x[k][3] = 0;
				k++;
			}
		}
	}
	for (i = 0; i < G.arcNum; i++)
	{
		for (j = 0; j < G.arcNum - 1 - i; j++)
		{
			if (x[j][2] > x[j + 1][2])
			{
				for (p = 0; p < 4; p++)
				{
					t = x[j][p];
					x[j][p] = x[j + 1][p];
					x[j + 1][p] = t;
				}
			}
		}
	}
	for (i = 0, k = 0; i < G.arcNum; i++)
	{
		p = find(c, G.vexNum, x[i][0] + 48);
		q = find(c, G.vexNum, x[i][1] + 48);
		if (p != q)
		{
			strcat(c[p], c[q]);
			c[q][0] = 0;
			k++;
			x[i][3] = 1;
		}
		if (k == G.vexNum - 1)
			break;
	}
	printf("最小生成树的边为：\n");
	printf("%7s%7s%6s\n", "顶点", "顶点", "权值");
	for (i = 0; i < G.arcNum; i++)
		if (x[i][3] == 1)
			printf("%7c%7c%6d\n", G.vexs[x[i][0]], G.vexs[x[i][1]], x[i][2]);
}

int find(ZFC *s, int n, char c)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < strlen(s[i]); j++)
			if (s[i][j] == c)
				return i;
	return -1;
}

void dijkstra(MGraph G, int v)
{
	int dist[VNUM];
	int path[VNUM][VNUM];
	int i, j, k, m, min, n, flag;
	for (i = 0; i < G.vexNum; i++)
		for (j = 0; j < G.vexNum; j++)
			path[i][j] = -1;
	for (i = 0; i < G.vexNum; i++)
	{
		if (i != v)
		{
			path[i][0] = v;
		}
	}
	for (i = 0; i < G.vexNum; i++)
	{
		dist[i] = G.arcs[v][i];
		if (dist[i] != 0 && dist[i] != MAXNUM)
		{
			path[i][0] = v;
			path[i][1] = i;
		}
	}
	n = 0;
	flag = 1;
	while (flag)
	{
		k = 0;
		min = MAXNUM;
		for (j = 0; j < G.vexNum; j++)
			if (dist[j] != 0 && dist[j] < min)
			{
				k = j;
				min = dist[j];
			}
		printf("第%d条最短路径长度为%d--(", ++n, min);
		for (j = 0; j < G.vexNum; j++)
			if (path[k][j] != -1)
				printf("%c,", G.vexs[path[k][j]]);
		printf("\b)\n");
		for (j = 0; j < G.vexNum; j++)
			if (j != k && dist[j] != 0)
				if (dist[k] + G.arcs[k][j] < dist[j])
				{
					dist[j] = dist[k] + G.arcs[k][j];
					for (m = 0; m < G.vexNum; m++)
						path[j][m] = path[k][m];
					for (m = 0; m < G.vexNum&&path[j][m] != -1;)
						m++;
					path[j][m] = j;
				}
		dist[k] = 0;
		flag = 0;
		for (j = 0; j < G.vexNum; j++)
			if (dist[j] != 0 && dist[j] < MAXNUM)
			{
				flag = 1;
				break;
			}
	}
}

void Floyd(MGraph G)
{
	int road[VNUM][VNUM][VNUM];
	int shortway[VNUM][VNUM];
	int i, j, k, m, n, v;
	for (i = 0; i < G.vexNum; i++)
	{
		for (j = 0; j < G.vexNum; j++)
		{
			shortway[i][j] = G.arcs[i][j];
			for (k = 0; k < G.vexNum; k++)
				road[i][j][k] = -1;
		}
	}
	for (i = 0; i < G.vexNum; i++)
	{
		for (j = 0; j < G.vexNum; j++)
		{
			if (shortway[i][j] != 10000 && shortway[i][j] != 0)
			{
				road[i][j][0] = i;
				road[i][j][1] = j;
			}
		}
	}
	for (k = 0; k < G.vexNum; k++)
	{
		for (i = 0; i < G.vexNum; i++)
		{
			for (j = 0; j < G.vexNum; j++)
			{
				if (shortway[i][k] + shortway[k][j] < shortway[i][j])
				{
					shortway[i][j] = shortway[i][k] + shortway[k][j];
					for (m = 0; m < G.vexNum&&road[i][k][m] != -1; m++)
					{
						road[i][j][m] = road[i][k][m];
					}
					for (n = 1; n < G.vexNum; m++, n++)
					{
						road[i][j][m] = road[k][j][n];
					}
				}
			}
		}
	}
	for (v = 0; v < G.vexNum; v++)
	{
		for (i = 0; i < G.vexNum; i++)
		{
			if (i == v)
				continue;
			printf("%c到%c的最路径为：", G.vexs[v], G.vexs[i]);
			for (j = 0; j < G.vexNum; j++)
			{
				if (road[v][i][j] == -1)
					break;
				printf("%c", G.vexs[road[v][i][j]]);
			}
			printf("\n");
		}
		printf("\n");
	}
}

void Hamilton(MGraph G)
{
	int m;
	int i, n = 0;
	int visit[VNUM], path[VNUM];
	for (i = 0; i < G.vexNum; i++)
		visit[i] = 0;
	for (i = 0; i < G.vexNum; i++)
		if (!visit[i])
			DFS(G, i, path, visit, &n);
	printf("图中的一个哈密尔顿链为：");
	for (i = 0; i < G.vexNum; i++)
		printf("%c", G.vexs[path[i]]);
	printf("\n");
}

void DFS(MGraph G, int i, int path[], int visit[], int *n)
{
	int j;
	visit[i] = 1;
	path[(*n)++] = i;
	if ((*n) == G.vexNum)
		return;
	for (j = 0; j < G.vexNum; j++)
		if (G.arcs[i][j] != 0 && !visit[j] && G.arcs[i][j] != 10000)
		{
			DFS(G, j, path, visit, n);
		}
	if ((*n) == G.vexNum)
		return;
	visit[i] = 0;
	(*n)--;
}

int top_sort(ALGraph G)
{
	StackLink s;
	int m = 0,i=0,v,w;
	ArcNode *p;
	TXT = fopen("拓扑序列.txt", "w");
	initStack(&s);
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
		if (G.adjlist[i].id == 0)
			push(s, i);
	}
	while (!ifemptyStack(s))
	{
		v = pop(s);
		fprintf(TXT, "%c", G.adjlist[v].data);
		m++;
		p = G.adjlist[v].firstArc;
		while (p)
		{
			w = p->adjvex;
			G.adjlist[w].id--;
			if (G.adjlist[w].id == 0)
				push(s, w);
			p = p->nextArc;
		}
	}
	fprintf(TXT,"\n");
	fclose(TXT);
	if (m < G.vexNum)
		return 0;
	else
		return 1;
}

void critical_path(ALGraph G)
{
	int i,n=G.vexNum,j,k;
	int ve[VNUM],vl[VNUM],ee,el;
	StackLink s1=NULL, s2=NULL;
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
			p=p->nextArc;
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

int TopologicalSort(ALGraph G, int index[])
{
	StackLink s;
	int count = 0, i, k, w, x[10];
	ArcNode *p;
	FindiInDegree(&G);
	initStack(&s);
	for (i = 0, k = 0; i < G.vexNum; i++)
	{
		if (G.adjlist[i].id == 0)
		{
			x[k++] = i;
			push(s, i);
		}
		if (k != 0)
		{
			printf("\n如下课程可以安排在同一学期：\n");
			for (i = 0; i < k; i++)
			{
				printf("《%s》", G.adjlist[x[i]].data);
			}
		}
		while (!ifemptyStack(s))
		{
			i=pop(s);
			index[count++] = i;
			w = 0;
			for (p = G.adjlist[i].firstArc; p; p->nextArc)
			{
				k = p->adjvex;
				if (!(--G.adjlist[k].id))
				{
					x[w++] = k;
					push(s, k);
				}
			}
			if (w != 0)
			{
				printf("\n如下的课程可以安排在同一学期;\n");
				for (i = 0; i < w; i++)
					printf("《%s》", G.adjlist[x[i]].data);
			}
		}
		if (count < G.vexNum)
			return 0;
		else
			return 1;
	}
}

void FindiInDegree(ALGraph *G)
{
	int k, i;
	ArcNode *p;
	for (k = 0; k < G->vexNum; k++)
	{
		G->adjlist[k].id = 0;
		for (i = 0; i < G->vexNum; i++)
		{
			p = G->adjlist[i].firstArc;
			while (p)
			{
				if (p->adjvex == k)
					G->adjlist[k].id++;
				p = p->nextArc;
			}
		}
	}
}

void initQueue(QLink *q)
{
	(*q).first = (*q).last = (QueueLink)malloc(sizeof(QNode));
	(*q).first->next = NULL;
}

void EnQueue(QLink *q, int t)
{
	QueueLink p;
	p = (QueueLink)malloc(sizeof(QNode));
	p->data = t;
	p->next = NULL;
	(*q).last->next = p;
	(*q).last = p;
}

int DeQueue(QLink *q)
{
	QueueLink p;
	int t;
	p = (*q).first->next;
	(*q).first->next = p->next;
	t = p->data;
	if (ifemptyQueue((*q)) == 0)
		(*q).last = (*q).first;
	free(p);
	return t;
}

int ifemptyQueue(QLink q)
{
	if (q.first->next == NULL)
		return 0;
	else
		return 1;
}

int GetQueueHead(QLink q)
{
	int t;
	t = q.first->next->data;
	return t;
}

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