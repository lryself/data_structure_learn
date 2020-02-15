#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	float coef;
	int exp;
}poly;
typedef struct node
{
	poly data;
	struct node *next;
}node,*lnode;

int create(lnode *l);
int insert(lnode l, poly x);
int sort(lnode l);
poly mul(lnode l1, lnode l2);
void show(lnode l);

int main()
{
	lnode l1, l2, l3, l4;
	int n, i = 0;
	poly x;
	char yn;
	if (create(&l1) == 0)
		printf("创建失败！\n");
	if (create(&l2) == 0)
		printf("创建失败！\n");
	if (create(&l3) == 0)
		printf("创建失败！\n");
	if (create(&l4) == 0)
		printf("创建失败！\n");
	lnode k1 = l1, k2 = l2, k3 = l3;
	do
	{
		printf("请输入第一个多项式的第%d个系数和指数（用空格隔开）:\n", ++i);
		scanf("%f%d", &x.coef,&x.exp);
		getchar();
		insert(k1, x);
		printf("是否继续输入？(y/n)\n");
		scanf("%c", &yn);
		getchar();
	} while (yn == 'y' || yn == 'Y');
	sort(l1);

	yn = 'n';
	i = 0;
	do
	{
		printf("请输入第二个多项式的第%d个系数和指数（用空格隔开）:\n", ++i);
		scanf("%f%d", &x.coef, &x.exp);
		getchar();
		insert(k2, x);
		printf("是否继续输入？(y/n)\n");
		scanf("%c", &yn);
	} while (yn == 'y' || yn == 'Y');
	sort(l2);

	for(k1=l1->next;k1 != NULL;k1=k1->next)
		insert(l3, k1->data);
	for(k2=l2->next;k2 != NULL;k2=k2->next)
		insert(l3, k2->data);
	sort(l3);

	for (k1 = l1->next; k1 != NULL; k1 = k1->next)
	{
		for (k2 = l2->next; k2 != NULL; k2 = k2->next)
		{
			x=mul(k1, k2);
			insert(l4, x);
		}
	}
	sort(l4);

	printf("两多项式相加得：\n");
	show(l3);
	printf("两多项式相乘得：\n");
	show(l4);
}

int create(lnode *l)
{
	(*l) = (lnode)malloc(sizeof(node));
	if ((*l) == NULL)
		return 0;
	(*l)->next = NULL;
	return 1;
}

int insert(lnode l, poly x)
{
	lnode s;
	s = (lnode)malloc(sizeof(node));
	if (s == NULL)
		return 0;
	s->data = x;
	s->next = l->next;
	l->next = s;
	return 1;
}

int sort(lnode l)
{
	lnode p;
	if (l->next == NULL)
		return 0;
	p = l->next;
	poly x;
	lnode q;
	while (p->next != NULL)
	{
		if (p->data.exp > p->next->data.exp)
		{
			q = p->next;
			x = q->data;
			q->data = p->data;
			p->data = x;
			p = l;
			continue;
		}
		if (p->data.exp == p->next->data.exp)
		{
			q = p->next;
			p->data.coef = p->data.coef + q->data.coef;
			p->next = q->next;
			free(q);
			p = l;
			continue;
		}
		if (p->next->data.coef == 0)
		{
			q = p->next;
			p->next=q->next;
			free(q);
			p = l;
			continue;
		}
		p = p->next;
	}
	return 1;
}

poly mul(lnode l1, lnode l2)
{
	poly s;
	s.coef = l1->data.coef*l2->data.coef;
	s.exp = l1->data.exp+l2->data.exp;
	return s;
}

void show(lnode l)
{
	lnode p;
	for(p = l->next;p;p=p->next)
	{
		if (p->data.coef < 0)
			printf("%0.2fX^%d", p->data.coef, p->data.exp);
		else
			printf("+%0.2fX^%d", p->data.coef, p->data.exp);
	}
	printf("\n");
}