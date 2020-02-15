#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct CSNode
{
	char data;
	struct CSNode *fch;
	struct CSNode *nsib;
}CSNode, *CSTree;				/*树*/
typedef struct QNode
{
	CSTree data;
	struct QNode *next;
}QNode, *QueueLink;				/*队列结点*/
typedef struct
{
	QueueLink first;
	QueueLink last;
}QLink;								/*队列*/
typedef struct Stack
{
	CSTree data;
	struct Stack *next;
}Stack,*StackLink;				/*栈*/

FILE *IN;

int menu();
void initCSTree(CSTree *T);						/*初始化树*/
void creat_CSTree(CSTree *T);					/*路径创建树*/
void PreOrder(CSTree t);						/*递归先根遍历*/
void everyroadpre1(CSTree t);					/*路径先根遍历1*/
void everyroadpre2(CSTree t,StackLink s);		/*路径先根遍历2*/
void destroyCSTree(CSTree t);					/*销毁树*/
CSTree searchCSTree(CSTree t, char e);			/*搜索树结点*/
void insertCSTree(CSTree t, char e, char h);	/*插入树结点*/
void deleteCSTree(CSTree t, char e);			/*删除树结点*/
//树的操作
void initQueue(QLink *Q);			/*初始化队列*/
void EnQueue(QLink *Q, CSTree x);	/*进队*/
int DeQueue(QLink *Q, CSTree *E);	/*出队*/
int ifEmptyQueue(QLink q);			/*判断队空*/
CSTree GetHead(QLink q);			/*得到队头*/
//队列操作
void initStack(StackLink *S);		/*初始化栈*/
CSTree pop(StackLink s);			/*出栈*/
void push(StackLink s,CSTree t);	/*进栈*/
int ifemptyStack(StackLink s);		/*判断栈空*/
void PrintStack(StackLink s);		/*输出栈中所有元素*/
//栈操作
void main()
{
	CSTree t=NULL;
	StackLink s;
	while (1)
	{
		switch (menu())
		{
		case 0:
			exit(0);
		case 1:
			printf("请在 输入.txt. 中输入形如(father,child)的层次序列\n");
			printf("输入结束请保存，按回车键继续\n");
			getchar();
			IN = fopen("输入.txt", "r");
			creat_CSTree(&t);
			break;
		case 2:
			PreOrder(t);
			printf("\n");
			break;
		case 3:
			everyroadpre1(t);
			printf("\n");
			break;
		case 4:
			initStack(&s);
			everyroadpre2(t,s);
			printf("\n");
			free(s);
			break;
		case 5:
			destroyCSTree(t);
			printf("销毁完成\n");
			break;
		}
		printf("按回车键继续");
		getchar();
		system("cls");
	}
}

void creat_CSTree(CSTree *T)
{
	QLink q;
	CSTree p,s,temp;
	char father, child;
	initCSTree(T);
	initQueue(&q);

	fscanf(IN, "(%c,%c)\n", &father, &child);
	if (father=='#')
	{
		(*T)->data = child;
		EnQueue(&q, (*T));
	}
	else
	{
		return;
	}
	fscanf(IN, "(%c,%c)\n", &father, &child);
	while (child != '#')
	{
		initCSTree(&p);
		p->data = child;
		while (1)
		{
			s = GetHead(q);
			if (s->data == father)
				break;
			if (ifEmptyQueue(q))
				break;
			DeQueue(&q, &s);
			if(s->fch)
				EnQueue(&q, s->fch);
			if(s->nsib)
				EnQueue(&q, s->nsib);
			s = GetHead(q);
		}
		if (s->fch)
		{
			temp = s->fch;
			while (temp->nsib)
			{
				temp = temp->nsib;
			}
			p->nsib = temp->nsib;
			temp->nsib = p;
		}
		else
		{
			s->fch = p;
		}
		fscanf(IN, "(%c,%c)\n", &father, &child);
	}
}

int menu()
{
	int n;
	printf("请选择以下操作\n");
	printf("0.退出\n");
	printf("1.创建树(按边输入)\n");
	printf("2.递归先根遍历\n");
	printf("3.非递归路径先根遍历\n");
	printf("4.递归路径先根遍历\n");
	printf("5.销毁树\n");
	scanf("%d", &n);
	getchar();
	return n;
}

void initCSTree(CSTree *T)
{
	(*T) = (CSTree)malloc(sizeof(CSNode));
	(*T)->fch = (*T)->nsib = NULL;
}

void initQueue(QLink *Q)
{
	QueueLink s;
	s = (QueueLink)malloc(sizeof(QNode));
	s->next = NULL;
	Q->first = s;
	Q->last = s;
}

void EnQueue(QLink *Q, CSTree x)
{
	QueueLink s;
	s = (QueueLink)malloc(sizeof(QNode));
	s->data = x;
	s->next = Q->last->next;
	Q->last->next = s;
	Q->last = s;
}

int DeQueue(QLink *Q, CSTree *E)
{
	QueueLink s;
	s = Q->first->next;
	Q->first->next = s->next;
	(*E) = s->data;
	free(s);
	if (ifEmptyQueue(*Q))
	{
		Q->last = Q->first;
		return 0;
	}
	return 1;
}

int ifEmptyQueue(QLink q)
{
	if (q.first->next == NULL)
		return 1;
	return 0;
}

CSTree GetHead(QLink q)
{
	CSTree s;
	s= q.first->next->data;
	return s;
}

void initStack(StackLink * S)
{
	(*S) = (StackLink)malloc(sizeof(Stack));
	(*S)->next=NULL;
}

CSTree pop(StackLink s)
{
	CSTree t;
	StackLink q;
	initStack(&q);
	q = s->next;
	s->next = q->next;
	t = q->data;
	free(q);
	return t;
}

void push(StackLink s,CSTree t)
{
	StackLink p;
	initStack(&p);
	p->data = t;
	p->next = s->next;
	s->next = p;
}

int ifemptyStack(StackLink s)
{
	if (s->next)
		return 0;
	return 1;
}

void PrintStack(StackLink s)
{
	StackLink p;
	CSTree q;
	initStack(&p);
	while (!ifemptyStack(s))
		push(p, pop(s));
	while (!ifemptyStack(p))
	{
		q = pop(p);
		push(s, q);
		printf("%c", q->data);
	}
}

void PreOrder(CSTree t)
{
	printf("%c", t->data);
	if (t->fch)
		PreOrder(t->fch);
	if (t->nsib)
		PreOrder(t->nsib);
}

void everyroadpre1(CSTree t)
{
	StackLink s;
	initStack(&s);
	while (1)
	{
		push(s, t);
		if (t->fch)
		{
			push(s, t->fch);
		}
		else
		{
			PrintStack(s);
			printf("\n");
			while (!ifemptyStack(s))
			{
				t = pop(s);
				if (t->nsib)
				{
					push(s,t->nsib);
					break;
				}
			}
			if (ifemptyStack(s))
				break;
		}
		t = pop(s);
	}
}

void everyroadpre2(CSTree t,StackLink s)
{
	if (t)
	{
		push(s, t);
		if (t->fch)
		{
			everyroadpre2(t->fch, s);
			pop(s);
		}
		else
		{
			PrintStack(s);
			printf("\n");
		}
		if (t->nsib)
			everyroadpre2(pop(s)->nsib,s);
	}
}

void destroyCSTree(CSTree t)
{
	if (t->fch)
		destroyCSTree(t->fch);
	if (t->nsib)
		destroyCSTree(t->nsib);
	free(t);
}

CSTree searchCSTree(CSTree t, char e)
{
	StackLink s;
	initStack(&s);
	while (1)
	{
		if (t->data == e)
		{
			return t;
		}
		if (t->nsib)
			push(s, t);
		if (t->fch)
			t = t->fch;
		else
		{
			if (ifemptyStack(s))
				break;
			t = pop(s);

		}
	}
}

void insertCSTree(CSTree t, char e, char h)
{
	CSTree p;
	initCSTree(&p);
	p->data = h;
	t = searchCSTree(t, e);
	if (t->fch)
	{
		p->nsib = t->fch->nsib;
		t->fch->nsib = p;
	}
	else
		t->fch = p;
}

void deleteCSTree(CSTree t, char e)
{
	StackLink s;
	initStack(&s);
	if (t->data == e)
		destroyCSTree(t);
	else
	{
		while (1)
		{
			if (t->fch->data == e)
			{
				destroyCSTree(t->fch);
				t->fch = NULL;
				return;
			}
			if (t->nsib->data == e)
			{
				destroyCSTree(t->nsib);
				t->nsib = NULL;
				return;
			}
			if (t->nsib)
				push(s, t->nsib);
			if (t->fch)
				t = t->fch;
			else
			{
				if (ifemptyStack(s))
					break;
				t = pop(s);
			}
		}
	}
}