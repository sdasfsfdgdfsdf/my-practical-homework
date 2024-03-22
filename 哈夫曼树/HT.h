#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include"��������.h"
typedef struct {
	int weigth;      //Ȩֵ 
	int parent;      //��ĸ 
	int lchild;      //����� 
	int rchild;      //�Ҷ��� 
	//��̬�������� ������������ʾ���ӹ�ϵ�� 
}HTNode, * HuffmanTree;   //���������ṹ 

void select(HuffmanTree p, int n, int* a, int* b)    //ѡ��Ȩֵ��С�� 
{
	*a = 0;
	*b = 0;//����ָ���ȳ�ʼ�� 
	for (int z = 1; z <= n; z++)//���� 
	{
		if (p[z].parent == 0 && *a == 0)//������ڵ�Ϊ�գ���*a��û��ֵ 
		{
			*a = z;
			continue;
		}
		if (p[z].parent == 0)
		{
			*b = z;
			break;
		}
	}
	if (p[*a].weigth >= p[*b].weigth)//a��Ȩֵ���ڵ���b 
	{
		int i = *a;
		*a = *b;
		*b = i;//a,b���� 
	}
	for (int m = 1; m <= n; m++)//���� 
	{
		if (p[m].parent != 0)//������ڵ��Ѿ���Ϊ0�� 
		{
			continue;//���� ���������� 
		}
		if (p[*a].weigth > p[m].weigth && *a != m && *b != m)
		{
			*b = *a;
			*a = m;
		}
		else if (p[*b].weigth > p[m].weigth && *b != m && *a != m)
		{
			*b = m;
		}
	}
}
void HuffmanCoding(HuffmanTree* HT, int* w, int n)     //���������� 
{
	if (n <= 1)
	{
		return;//���������1���ַ���ֱ�ӷ��� 
	}
	int m = 2 * n - 1;//n��Ҷ�ӽڵ㣬��Ҫ���n-1�Σ�����2n-1���ڵ� 
	*HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//Ϊ������ �ռ� ����һ��λ�ò��ã� 
	int i = 1;//����forѭ�� 
	HuffmanTree p = *HT + 1;//ָ�����е����ĺ�һ���ռ� �����ڱ������� 
	for (; i <= n; ++i, ++p, ++w)//���� 
	{
		//��ǰn���ڵ�λ�ã���������Ч�ı��� 
		p->lchild = 0;
		p->parent = 0;
		p->rchild = 0;
		p->weigth = *w;//��ʼ�� 
	}
	for (; i <= m; ++i, ++p)
	{
		//n֮���λ�� ����������ϵĿո� 
		p->lchild = 0;
		p->parent = 0;
		p->rchild = 0;
		p->weigth = 0;
	}
	for (int k = n + 1; k <= m; ++k)
	{
		//n+1�Ŀո���ʼ������ֱ�����еĸ�������� 
		int s1, s2;
		select(*HT, k - 1, &s1, &s2);//k-1�������ѡ�������λ�� 
		(*HT)[s1].parent = k;
		(*HT)[s2].parent = k;//��ѡ�е�����Ȩֵ��С����Ϊk�����Һ��� 
		(*HT)[k].lchild = s1;
		(*HT)[k].rchild = s2;
		(*HT)[k].weigth = (*HT)[s1].weigth + (*HT)[s2].weigth;//�޸�k��Ȩֵ 
	}
}
void coding(char*** p, int n, HuffmanTree t)            //���� 
{
	*p = (char**)malloc((n + 1) * sizeof(char*));//����ռ� 
	char* cd;
	cd = (char*)malloc(n * sizeof(char));//����ռ� 
	cd[n - 1] = '\0'; //�ַ��� 
	for (int i = 1; i <= n; ++i)//���� 
	{
		int start = n - 1;
		for (int c = i, f = t[i].parent; f != 0; c = f, f = t[f].parent)
		{
			if (t[f].lchild == c)
			{
				//���Ӿ͸�ֵΪ0 
				cd[--start] = '0';
			}
			else
			{
				//�Һ��Ӿ͸�ֵΪ1 
				cd[--start] = '1';
			}
		}
		(*p)[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy((*p)[i], &cd[start]);
	}
	free(cd);
}

void decoding(FILE* r, FILE* w, HuffmanTree t, int n, char* a)    //���� 
{
	int num = 2 * n - 1;//���ڵ� 
	for (int i; fscanf(r, "%1d", &i) != EOF;)
	{
		if (i == 0)
		{
			int j = t[num].lchild;//0�������� 
			if (t[j].lchild == 0)//����Ѿ�û�������ˣ��˴���һ��Ϊ���ӣ���Ϊ���ҳɶԳ��֣� 
			{
				fprintf(w, "%c", a[j - 1]);//��� 
				num = 2 * n - 1;//���¸�num 
			}
			else
			{
				num = j;//����������ӣ��ּ�����j��λ������ 
			}
		}
		else if (i == 1)
		{
			int j = t[num].rchild;//1�����Һ��� 
			if (t[j].rchild == 0)//����Ѿ�û�������ˣ��˴���һ��Ϊ�Һ��ӣ���Ϊ���ҳɶԳ��֣� 
			{
				fprintf(w, "%c", a[j - 1]);//��� 
				num = 2 * n - 1;//���¸�num 
			}
			else
			{
				num = j;
			}
		}
	}
}
