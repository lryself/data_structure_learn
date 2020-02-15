#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define max 100

typedef struct
{
	int front;
	int rear;
	int qsize;
	char data[max];
}sq;

typedef struct node
{
	char data;
	struct node *next;
}stack,*lstack;

int initsq(sq *l);
int sqempty(sq l);
int sqgethead(sq l, char *e);
int sqen(sq *l, char e);
int sqde(sq *l, char *e);
int create(lstack *l);
int push(lstack l, char x);
char pop(lstack l);

int main()
{
	sq q;
	int i, j, n,front,rear;
	char x='0', x1,x2;
	lstack l;
	initsq(&q);
	create(&l);
	char yn='y';
	printf("请输入（以@结束）\n");
	while (x= getchar() != '@')
	{
		sqen(&q, x);
		push(l, x);
	}
	while (sqempty(q) != 1)
	{
		x1 = pop(l);
		sqde(&q, &x2);
		if (x1 != x2)
		{
			yn = 'n';
			break;
		}
	}
	if (yn == 'y')
		printf("这是回文");
	if (yn == 'n')
		printf("这不是回文");
}

int initsq(sq *l)
{
	l->front = l->rear = 0;
	l->qsize = max;
	return 1;
}

int sqempty(sq l)
{
	if (l.front == l.rear)
		return 1;
	else return 0;
}

int sqgethead(sq l, char *e)
{
	if (l.rear == l.front)
		return 0;
	*e = l.data[l.front];
	return 1;
}

int sqen(sq *l, char e)
{
	if ((l->rear + 1) % l->qsize == l->front)
		return 0;
	l->data[l->rear] = e;
	l->rear = (l->rear + 1) % l->qsize;
	return 1;
}

int sqde(sq *l, char *e)
{
	if (l->rear == l->front)
		return 0;
	*e = l->data[l->front];
	l->front = (l->front + 1) % l->qsize;
	return 1;
}

int create(lstack *l)
{
	(*l) = (lstack)malloc(sizeof(stack));
	(*l)->next = NULL;
	return 0;
}

int push(lstack l, char x)
{
	lstack s;
	create(&s);
	if (s == NULL)
		return 1;
	s->data = x;
	s->next = l->next;
	l->next = s;
	return 1;
}

char pop(lstack l)
{
	char x;
	lstack q;
	q = l->next;
	x = q->data;
	l->next = q->next;
	free(q);
	return x;
}