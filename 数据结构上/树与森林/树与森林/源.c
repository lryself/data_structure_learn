#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct CSNode
{
	char data;
	struct CSNode *fch;
	struct CSNode *nsib;
}CSNode, *CSTree;				/*��*/
typedef struct QNode
{
	CSTree data;
	struct QNode *next;
}QNode, *QueueLink;				/*���н��*/
typedef struct
{
	QueueLink first;
	QueueLink last;
}QLink;								/*����*/
typedef struct Stack
{
	CSTree data;
	struct Stack *next;
}Stack,*StackLink;				/*ջ*/

FILE *IN;

int menu();
void initCSTree(CSTree *T);						/*��ʼ����*/
void creat_CSTree(CSTree *T);					/*·��������*/
void PreOrder(CSTree t);						/*�ݹ��ȸ�����*/
void everyroadpre1(CSTree t);					/*·���ȸ�����1*/
void everyroadpre2(CSTree t,StackLink s);		/*·���ȸ�����2*/
void destroyCSTree(CSTree t);					/*������*/
CSTree searchCSTree(CSTree t, char e);			/*���������*/
void insertCSTree(CSTree t, char e, char h);	/*���������*/
void deleteCSTree(CSTree t, char e);			/*ɾ�������*/
//���Ĳ���
void initQueue(QLink *Q);			/*��ʼ������*/
void EnQueue(QLink *Q, CSTree x);	/*����*/
int DeQueue(QLink *Q, CSTree *E);	/*����*/
int ifEmptyQueue(QLink q);			/*�ж϶ӿ�*/
CSTree GetHead(QLink q);			/*�õ���ͷ*/
//���в���
void initStack(StackLink *S);		/*��ʼ��ջ*/
CSTree pop(StackLink s);			/*��ջ*/
void push(StackLink s,CSTree t);	/*��ջ*/
int ifemptyStack(StackLink s);		/*�ж�ջ��*/
void PrintStack(StackLink s);		/*���ջ������Ԫ��*/
//ջ����
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
			printf("���� ����.txt. ����������(father,child)�Ĳ������\n");
			printf("��������뱣�棬���س�������\n");
			getchar();
			IN = fopen("����.txt", "r");
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
			printf("�������\n");
			break;
		}
		printf("���س�������");
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
	printf("��ѡ�����²���\n");
	printf("0.�˳�\n");
	printf("1.������(��������)\n");
	printf("2.�ݹ��ȸ�����\n");
	printf("3.�ǵݹ�·���ȸ�����\n");
	printf("4.�ݹ�·���ȸ�����\n");
	printf("5.������\n");
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