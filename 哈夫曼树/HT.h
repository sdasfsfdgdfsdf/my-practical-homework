#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include"哈夫曼树.h"
typedef struct {
	int weigth;      //权值 
	int parent;      //父母 
	int lchild;      //左儿子 
	int rchild;      //右儿子 
	//静态三叉链表 【用数组来表示链接关系】 
}HTNode, * HuffmanTree;   //哈夫曼树结构 

void select(HuffmanTree p, int n, int* a, int* b)    //选择权值最小的 
{
	*a = 0;
	*b = 0;//两个指针先初始化 
	for (int z = 1; z <= n; z++)//遍历 
	{
		if (p[z].parent == 0 && *a == 0)//如果父节点为空，且*a还没赋值 
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
	if (p[*a].weigth >= p[*b].weigth)//a的权值大于等于b 
	{
		int i = *a;
		*a = *b;
		*b = i;//a,b互换 
	}
	for (int m = 1; m <= n; m++)//遍历 
	{
		if (p[m].parent != 0)//如果父节点已经不为0了 
		{
			continue;//跳过 （舍弃掉） 
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
void HuffmanCoding(HuffmanTree* HT, int* w, int n)     //建哈夫曼树 
{
	if (n <= 1)
	{
		return;//如果不超过1个字符，直接返回 
	}
	int m = 2 * n - 1;//n个叶子节点，需要结合n-1次，共有2n-1个节点 
	*HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//为树分配 空间 （第一个位置不用） 
	int i = 1;//用于for循环 
	HuffmanTree p = *HT + 1;//指向已有的树的后一个空间 （用于遍历树） 
	for (; i <= n; ++i, ++p, ++w)//遍历 
	{
		//对前n个节点位置，用来放有效的编码 
		p->lchild = 0;
		p->parent = 0;
		p->rchild = 0;
		p->weigth = *w;//初始化 
	}
	for (; i <= m; ++i, ++p)
	{
		//n之后的位置 ，放用来结合的空根 
		p->lchild = 0;
		p->parent = 0;
		p->rchild = 0;
		p->weigth = 0;
	}
	for (int k = n + 1; k <= m; ++k)
	{
		//n+1的空根开始遍历，直到所有的根遍历完成 
		int s1, s2;
		select(*HT, k - 1, &s1, &s2);//k-1代表的是选择的上限位置 
		(*HT)[s1].parent = k;
		(*HT)[s2].parent = k;//把选中的两个权值最小的置为k的左右孩子 
		(*HT)[k].lchild = s1;
		(*HT)[k].rchild = s2;
		(*HT)[k].weigth = (*HT)[s1].weigth + (*HT)[s2].weigth;//修改k的权值 
	}
}
void coding(char*** p, int n, HuffmanTree t)            //编码 
{
	*p = (char**)malloc((n + 1) * sizeof(char*));//分配空间 
	char* cd;
	cd = (char*)malloc(n * sizeof(char));//分配空间 
	cd[n - 1] = '\0'; //字符串 
	for (int i = 1; i <= n; ++i)//遍历 
	{
		int start = n - 1;
		for (int c = i, f = t[i].parent; f != 0; c = f, f = t[f].parent)
		{
			if (t[f].lchild == c)
			{
				//左孩子就赋值为0 
				cd[--start] = '0';
			}
			else
			{
				//右孩子就赋值为1 
				cd[--start] = '1';
			}
		}
		(*p)[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy((*p)[i], &cd[start]);
	}
	free(cd);
}

void decoding(FILE* r, FILE* w, HuffmanTree t, int n, char* a)    //译码 
{
	int num = 2 * n - 1;//根节点 
	for (int i; fscanf(r, "%1d", &i) != EOF;)
	{
		if (i == 0)
		{
			int j = t[num].lchild;//0就是左孩子 
			if (t[j].lchild == 0)//如果已经没有子树了（此处不一定为左孩子，因为左右成对出现） 
			{
				fprintf(w, "%c", a[j - 1]);//输出 
				num = 2 * n - 1;//重新给num 
			}
			else
			{
				num = j;//如果还有左孩子，又继续从j的位置往下 
			}
		}
		else if (i == 1)
		{
			int j = t[num].rchild;//1就是右孩子 
			if (t[j].rchild == 0)//如果已经没有子树了（此处不一定为右孩子，因为左右成对出现） 
			{
				fprintf(w, "%c", a[j - 1]);//输出 
				num = 2 * n - 1;//重新给num 
			}
			else
			{
				num = j;
			}
		}
	}
}
