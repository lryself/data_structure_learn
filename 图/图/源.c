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
}QNode, *QueueLink;														/*���н��*/
typedef struct QLink
{
	QueueLink first;
	QueueLink last;
}QLink;																	/*����*/
typedef struct Stack
{
	int data;
	struct Stack *next;
}Stack, *StackLink;														/*ջ*/
typedef struct
{
	char vexs[VNUM];
	int arcs[VNUM][VNUM];
	int vexNum, arcNum;
}MGraph;																		/*ͼ���ڽӾ���*/
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
}ALGraph;																/*ͼ���ڽӱ�*/
typedef struct Graph
{
	MGraph M;
	ALGraph A;
}Graph;																	/*ͼ*/
typedef struct
{
	int vi, weigh;
}LowCost;
typedef char ZFC[VNUM];

FILE *TXT;

int menu(int n);
//���в���
void initQueue(QLink *q);																		/*��ʼ������*/
void EnQueue(QLink *q, int t);																	/*����*/
int DeQueue(QLink *q);																			/*����*/
int ifemptyQueue(QLink q);																		/*�ж϶ӿ�*/
int GetQueueHead(QLink q);																		/*�õ���ͷ*/
//ջ����
int initStack(StackLink *l);																	/*��ʼ��ջ*/
int push(StackLink l, int x);																	/*��ջ*/
int pop(StackLink l);																			/*��ջ*/
int ifemptyStack(StackLink l);																	/*�ж�ջ��*/
//ͼ����
void create_no_adjlist(ALGraph *G);																//��������ͼ����ͨͼ���ڽӱ���ṹ
void create_no_matrix(MGraph *G);																//��������ͼ����ͨͼ���ڽӾ��󴢴�ṹ
void create_yes_adjlist(ALGraph *G);															//��������ͼ����ͨͼ���ڽӱ���ṹ
void create_yes_matrix(MGraph *G);																//��������ͼ����ͨͼ���ڽӾ��󴢴�ṹ
void print_adjlistnex(ALGraph G);																//����ڽӱ���ĸ������
void print_adjlist(ALGraph G);																	//�������ͼ���ڽӱ�
void df_traver(ALGraph G, int v, int visited[]);												//�����ȱ����ĸ�������
int df_traverGraph(ALGraph G);																	//��������ڽӱ����ȱ�������
void bf_traver(ALGraph G, int v0, int visited[]);												//�����ȱ����ĸ�������
void bf_traverGraph(ALGraph G);																	//��������ڽӱ�Ĺ�ȱ�������
void prim(MGraph G);																			//����ķ�㷨��һ����С������
void Kruskal(MGraph G);																			//��³˹������һ����С������
int find(ZFC * s, int n, char c);																//�Ͻ�˹������������
void dijkstra(MGraph G, int v);																	//�Ͻ�˹�����㷨��һ��Դ����������ж�������·��
void Floyd(MGraph G);																			//���������㷨������Դ��֮������·��
void DFS(MGraph G, int i, int path[], int visit[], int *n);										//���·��
int top_sort(ALGraph G);																		//����������
void critical_path(ALGraph G);																	//��ؼ�·��
int TopologicalSort(ALGraph G, int index[]);													//Ѱ�ҹؼ�·����ͬ�ڿγ�
void FindiInDegree(ALGraph * G);																//��ʼ���������
void Hamilton(MGraph G);																		//���һ�����ܶ�����

void main()
{
	int graphid = 0;
	int lt, n;
	Graph G;
	printf("��ѡ����Ҫ������ͼ���ͣ�\n1.����ͼ\n2.����ͼ\n");
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
			printf("������һ����Ԫ��:\n");
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
		printf("\n���س�������\n");
		getchar();
		system("cls");
	}
}

int menu(int n)
{
	int i;
	printf("��ѡ����Ҫ���еĲ�������ţ�\n");
	printf("0.�˳�����\n");
	if (n == 1)//����ͼ
	{
		printf("1.�����������ͨͼ���ڽӱ���ڽӾ��󴢴�ṹ��ע�������������еĴ�������������� ����.txt �ж�ȡ\n");
	}
	if (n == 2)
	{
		printf("1.�����������ͨͼ���ڽӱ���ڽӾ��󴢴�ṹ��ע�������������еĴ�������������� ����.txt �ж�ȡ\n");
	}
	printf("2.����ڽӱ�\n");
	printf("3.�����ȱ�������\n");
	printf("4.�����ȱ�������\n");
	printf("5.ͨ������ķ�㷨����С������\n");
	printf("6.ͨ����³˹�����㷨����С������\n");
	printf("7.ͨ���Ͻ�˹�����㷨��λ������·��\n");
	printf("8.ͨ�����������㷨��ÿһ�Զ���֮������·��\n");
	printf("9.��ͼ��һ�����ܶ�����\n");
	printf("10.��ͼ��һ���ؼ�·��\n");
	scanf("%d", &i);
	getchar();
	return i;
}

void create_no_adjlist(ALGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	ArcNode *p;
	TXT = fopen("����.txt", "r");
	printf("�����붥������ͻ���,�ÿո����\n");
	fscanf(TXT, "%d%d", &G->vexNum, &G->arcNum);
	fgetc(TXT);
	for (i = 0; i < G->vexNum; i++)
	{
		printf("�������%d�����������\n", i + 1);
		fscanf(TXT, "%c", &G->adjlist[i].data);
		fgetc(TXT);
		G->adjlist[i].firstArc = NULL;
	}
	print_adjlistnex(*G);
	for (k = 0; k < G->arcNum; k++)
	{
		printf("���������ڵ������������źͻ��ȵ�Ȩֵ���ÿո����������%d������Ҫ���룩\n", G->arcNum - k);
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
	printf("�ڽӱ����ɹ�\n");
}

void create_no_matrix(MGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	TXT = fopen("����.txt", "r");
	printf("�����붥������ͻ������ÿո����\n");
	fscanf(TXT, "%d%d", &G->vexNum, &G->arcNum);
	fgetc(TXT);
	for (i = 0; i < G->vexNum; i++)
	{
		printf("�������%d�����������\n", i + 1);
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
		printf("���������ڵ������������źͻ��ȵ�Ȩֵ���ÿո����������%d������Ҫ���룩\n", G->arcNum - k);
		fscanf(TXT, "%d%d%d", &i, &j, &m);
		G->arcs[i - 1][j - 1] = m;
		G->arcs[j - 1][i - 1] = m;
	}
	fclose(TXT);
	printf("�ڽӾ��󴴽��ɹ�\n");
}

void create_yes_adjlist(ALGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	ArcNode *p;
	TXT = fopen("����.txt", "r");
	printf("�����붥������ͻ���,�ÿո����\n");
	fscanf(TXT, "%d%d", &G->vexNum, &G->arcNum);
	fgetc(TXT);
	for (i = 0; i < G->vexNum; i++)
	{
		printf("�������%d�����������\n", i + 1);
		fscanf(TXT, "%c", &G->adjlist[i].data);
		fgetc(TXT);
		G->adjlist[i].firstArc = NULL;
	}
	print_adjlistnex(*G);
	for (k = 0; k < G->arcNum; k++)
	{
		printf("���������ڵ������������ţ���һ��Ϊ���㣬�ڶ���Ϊ��㣩�ͻ��ȵ�Ȩֵ���ÿո����������%d������Ҫ���룩\n", G->arcNum - k);
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
	printf("�ڽӱ����ɹ�\n");
}

void create_yes_matrix(MGraph *G)
{
	int i = 0, j = 0, k = 0, m = 0;
	TXT = fopen("����.txt", "r");
	printf("�����붥������ͻ������ÿո����\n");
	fscanf(TXT, "%d%d", &G->vexNum, &G->arcNum);
	fgetc(TXT);
	for (i = 0; i < G->vexNum; i++)
	{
		printf("�������%d�����������\n", i + 1);
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
		printf("���������ڵ������������ţ���һ��Ϊ���㣬�ڶ���Ϊ��㣩�ͻ��ȵ�Ȩֵ���ÿո����������%d������Ҫ���룩\n", G->arcNum - k);
		fscanf(TXT, "%d%d%d", &i, &j, &m);
		G->arcs[i - 1][j - 1] = m;
	}
	fclose(TXT);
	printf("�ڽӾ��󴴽��ɹ�\n");
}

void print_adjlistnex(ALGraph G)
{
	int i, j;
	printf("ͼ�н��Ԫ������:\n");
	for (i = 0; i < G.vexNum; i++)
	{
		printf("%d.%c ", i + 1, G.adjlist[i].data);
	}
}

void print_adjlist(ALGraph G)
{
	int i, j;
	ArcNode *p;
	printf("��ͼ���ڽӱ��ǣ�\n");
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
	printf("����������İ������Ϊ��\n");
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
	printf("��С�������ı�Ϊ��\n");
	printf("%7s%7s%6s\n", "����", "����", "Ȩֵ");
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
		printf("��%d�����·������Ϊ%d--(", ++n, min);
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
			printf("%c��%c����·��Ϊ��", G.vexs[v], G.vexs[i]);
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
	printf("ͼ�е�һ�����ܶ�����Ϊ��");
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
	TXT = fopen("��������.txt", "w");
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
	printf("ͼ�еĹؼ�·����:\n");
	for (j = 0; j < G.vexNum; j++)
	{
		p = G.adjlist[j].firstArc;
		while (p != NULL)
		{
			k = p->adjvex;
			ee = ve[j];
			el = vl[k] - p->info;
			if (ee == el)
				printf("%c��%c\n", G.adjlist[j].data, G.adjlist[k].data);
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
			printf("\n���¿γ̿��԰�����ͬһѧ�ڣ�\n");
			for (i = 0; i < k; i++)
			{
				printf("��%s��", G.adjlist[x[i]].data);
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
				printf("\n���µĿγ̿��԰�����ͬһѧ��;\n");
				for (i = 0; i < w; i++)
					printf("��%s��", G.adjlist[x[i]].data);
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