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
			if (i == 0)printf("����ʧ��!\n");
			else printf("�������!\n");
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
					printf("���ʧ��!\n");
					break;
				}
			}
			if (i == 1)
				printf("��ճɹ�!\n");
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
					printf("����ʧ��!\n");
					break;
				}
			}
			free(l);
			l = NULL;
			printf("�������!\n");
			break;
		case 4:
			if (l == NULL)
			{
				printf("���ȴ�������\n");
				break;
			}
			printf("��������Ҫ�����ѧ����Ϣ��������ѧ�ţ��ÿո��������\n");
			scanf("%s%s", &x.name, &x.id);
			i = insert(l, 1, x);
			if (i == 0)
			{
				printf("����ʧ��!\n");
			}
			if (i == 1)
			{
				printf("����ɹ�!\n");
			}
			break;
		case 5:
			printf("��������Ҫɾ����ѧ��λ��:\n");
			scanf("%d", &i);
			j = delete(l, i);
			if (i == 0)
			{
				printf("ɾ��ʧ��!\n");
			}
			if (i == 1)
			{
				printf("ɾ���ɹ�!\n");
			}
			break;
		case 6:
			printf("��ѡ��\n");
			printf("1.����������\n");
			printf("2.��ѧ�Ų���\n");
			scanf("%d", &j);
			if (j == 1)
			{
				printf("������Ҫ���ҵ�ѧ����������\n");
				scanf("%s", &x.name);
			}
			if (j == 2)
			{
				printf("������Ҫ���ҵ�ѧ����ѧ�ţ�\n");
				scanf("%s", &x.id);
			}
			x = search(l, x);
			if (x.name == NULL || x.id == NULL)
			{
				printf("����û�����ѧ����Ϣ��\n");
				break;
			}
			printf("%s %s\n", x.name, x.id);
			break;
		case 7:
			printf("��������Ҫ���µ�ѧ��������\n");
			scanf("%s", &x.name);
			i = updata(l, x);
			if (i == 0)
				printf("����ʧ�ܣ�\n");
			if (i == 1)
				printf("���³ɹ���\n");
			break;
		case 8:
			p = l;
			printf("��������Ҫ���ҵ�ѧ����λ��\n");
			scanf("%d", &i);
			for (j = 0; j < i&&p != NULL; j++)
			{
				p = p->next;
			}
			if (p == NULL)
			{
				printf("λ�ô���\n");
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
				printf("������ɣ�\n");
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
		printf("�������%d��ѧ��������ѧ�ţ��ÿո������\n", i);
		scanf("%s%s", &x.name, &x.id);
		getchar();
		insert(*l, i, x);
		i++;
		printf("�Ƿ�Ҫ�������룿��Y/N��\n");
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
	printf("��ѡ�����в���:\n");
	printf("1.�������\n");
	printf("2.�������\n");
	printf("3.��������\n");
	printf("4.��������\n");
	printf("5.ɾ������\n");
	printf("6.��ֵ����\n");
	printf("7.����ĳ����Ϣ\n");
	printf("8.ָ��λ�ò���\n");
	printf("9.����\n");
	printf("0.�˳�\n");
	int n;
	scanf("%d", &n);
	if (n >= 0 && n <= 9)
		return n;
	printf("�����������������\n");
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
	printf("��������º��ѧ�ţ�\n");
	scanf("%s", p->data.id);
	return 1;
}