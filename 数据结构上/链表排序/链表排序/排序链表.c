#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node,*lnode;

int create(lnode *l);
int insert(lnode l, int x);
int sort(lnode l);

int main()
{
	lnode l1, l2, l3;
	int n, i=0;
	int x;
	char yn;
	create(&l1);
	create(&l2);
	create(&l3);
	lnode k1=l1, k2=l2, k3=l3;
	do
	{
		printf("�������һ�ĵ�%d�����ݣ��ÿո������:\n",++i);
		scanf("%d", &x);
		getchar();
		insert(k1, x);
		printf("�Ƿ�������룿(y/n)\n");
		scanf("%c", &yn);
		getchar();
	} while (yn == 'y' || yn == 'Y');
	sort(l1);

	yn = 'n';
	i = 0;
	do
	{
		printf("���������ĵ�%d�����ݣ��ÿո������:\n",++i);
		scanf("%d", &x);
		getchar();
		insert(k2, x);
		printf("�Ƿ�������룿(y/n)\n");
		scanf("%c", &yn);
	} while (yn == 'y' || yn == 'Y');
	sort(l2);

	l3->next = l1->next;
	while (k3->next != NULL)
		k3 = k3->next;
	k3->next = l2->next;
	sort(l3);

	if (l3->next == NULL)
		printf("����Ϊ��\n");
	else
	{
		printf("�ϲ�������Ϊ��\n");
		for (k3 = l3->next; k3 != NULL; k3 = k3->next)
		{
			printf("%d ", k3->data);
		}
	}
}

int create(lnode *l)
{
	(*l) = (lnode)malloc(sizeof(node));
	if ((*l) == NULL)
		return 0;
	(*l)->next = NULL;
	return 1;
}

int insert(lnode l,int x)
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
	int x;
	while (p->next != NULL)
	{
		if (p->data > p->next->data)
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