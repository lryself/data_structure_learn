#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct
{
	char name[20];
	char id[20];
}student;

typedef struct
{
	student *data;
	int length;
	int listsize;
}list;

int menu();
int create(list *l,int max);
int insert(list *l, int i, student x);

int main()
{
	int n,i,num,r,max;
	student x;
	list l;
	char m[20];
	while (1)
	{
		n = menu();
		if (n == 0)
			break;
		switch (n)
		{
		case 1:
			printf("�����봴����ѧ��������\n");
			scanf("%d", &max);
			getchar();
			r = create(&l,max);
			if (r == 1)
				printf("�����ɹ�!\n");
			else
				printf("����ʧ��!\n");
			break;
		case 2:
			for (; l.length > 0; l.length--)
				l.data[l.length - 1] = l.data[l.length];
			printf("������!\n");
			getchar();
			break;
		case 3:
			free(l.data);
			getchar();
			printf("������ɣ�\n");
			break;
		case 4:
			printf("��������Ҫ�����ѧ����λ�ã�������ѧ�ţ��ÿո������\n");
			scanf("%d%s%s", &i, &x.name, &x.id);
			getchar();
			if (insert(&l, i - 1, x) == 1)
				printf("������ɣ�\n");
			else
				printf("����ʧ�ܣ�\n");
			break;
		case 5:
			printf("������Ҫɾ����ѧ��������\n");
			scanf("%s", &x.name);
			getchar();
			if (delete(&l, x) == 1)
				printf("ɾ����ɣ�\n");
			else
				printf("ɾ��ʧ�ܣ�\n");
			break;
		case 6:
			printf("��������Ҫ���ҵ�ѧ����Ϣ��ѧ�ţ�\n");
			scanf("%s", &m);
			getchar();
			i=search(l, m);
			if (strcmp(l.data[i].name, m) == 0 || strcmp(l.data[i].id, m) == 0)
				printf("%s %s", l.data[i].name, l.data[i].id);
			else
				printf("���޴���!\n");
			break;
		case 7:
			printf("������Ҫ���µ�ѧ��������ѧ�ţ�\n");
			scanf("%s", &m);
			getchar();
			i = search(l, m);
			if (strcmp(l.data[i].name, m) != 0 && strcmp(l.data[i].id, m) != 0)
			{
				printf("���޴���!\n");
				break;
			}
			printf("��������º��ѧ��������ѧ�ţ�(�ÿո������\n");
			scanf("%s%s", l.data->name, l.data->id);
			getchar();
			printf("������ɣ�\n");
			break;
		case 8:
			printf("������Ҫ���ҵ�ѧ��λ�ã�\n");
			scanf("%d", &i);
			getchar();
			if (i > l.length)
			{
				printf("��ѯ����!\n");
				break;
			}
			else
				printf("%s %s\n", l.data[i - 1].name, l.data[i - 1].id);
			break;
		case 9:
			for (i = 0; i < l.length; i++)
			{
				printf("%s %s\n", l.data[i].name, l.data[i].id);
			}
			printf("�������!\n");
			getchar();
			break;
		default:
			break;
		}
		printf("�����������\n");
		getchar();
		system("cls");
	}
}

int menu()
{
	int n;
	while(1)
	{
		printf("��ѡ�������\n");
		printf("1.����\n");
		printf("2.���(���ڴ�����֮��ʹ��)\n");
		printf("3.����(���ڴ�����֮��ʹ��)\n");
		printf("4.����\n");
		printf("5.ɾ��\n");
		printf("6.��ֵ����\n");
		printf("7.����ĳ����Ϣ\n");
		printf("8.ָ��λ�ò���\n");
		printf("9.����\n");
		printf("0.�˳�\n");
		scanf("%d", &n);
		if (n < 0 || n>9)
		{
			printf("������������������\n");
		}
		else return n;
	}
}

int create(list *l, int max)
{
	char yn;
	student x;
	int n = 1;
	l->data = (student*)malloc(max * sizeof(student));
	if (l->data == NULL)
		return 0;
	l->length = 0;
	l->listsize = max;
	do
	{
		printf("������Ҫ����ĵ�%d��ѧ����������ѧ�ţ��ÿո������\n",n);
		scanf("%s%s", &x.name, &x.id);
		getchar();
		if (insert(l, n - 1, x) == 1)
		{
			printf("�Ƿ�������룿y/n\n");
			scanf("%c", &yn);
			getchar();
		}
		else return 0;
		n++;
	} while (yn == 'y' || yn == 'Y');
	return 1;
}

int insert(list *l, int i,student x)
{
	int p;
	if (i<0 || i>l->length)
	{
		printf("����λ���쳣��\n");
		return 0;
	}
	if (l->length > l->listsize)
	{
		printf("����������\n");
		return 0;
	}
	for (p = l->length; p > i; p--)
	{
		l->data[p] = l->data[p - 1];
	}
	l->data[i] = x;
	l->length++;
	return 1;
}

int delete(list *l, student x)
{
	int i, p;
	i=search(*l, x.name);
	for (; i<l->length;i++)
	{
		l->data[i] = l->data[i+1];
	}
	return 1;
}

int search(list l, char m[])
{
	int i;
	for (i = 0; i < l.length; i++)
	{
		if (strcmp(m, l.data[i].name) == 0)
			return i;
		if (strcmp(m, l.data[i].id) == 0)
			return i;
	}
}