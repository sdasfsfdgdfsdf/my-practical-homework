#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HT.h"

void visit(HuffmanTree t, FILE* w, int n)          //打印哈夫曼树 
{
	HuffmanTree p = t + 1;
	for (int m = 0; m < 2 * n - 1; m++)
	{
		printf("%d\t%d\t%d\t%d\n", p->weigth, p->parent, p->lchild, p->rchild);
		fprintf(w, "%d %d %d %d\n", p->weigth, p->parent, p->lchild, p->rchild);
		++p;
	}
}
void read_weigth(int* w, char* ch, int number)          //读取边 
{
	char q;
	for (int n = 0; n < number; n++)
	{
		scanf("%d%c", &w[n], &ch[n]);//权值-字符 
		scanf("%c", &q);//空格 
		//权值存在w,字符存在ch 
	}
}
void found(FILE* r1, FILE* w2, char** p, int n, char* zh)     //将字符串转化为二进制代码 
{
	//r1为原文，w2为编码加密之后的文,r2为哈夫曼树 
	char ch;
	//	fscanf(r2,"%s",zh);//先读取全部的编码 
	for (; (fscanf(r1, "%c", &ch)) != EOF;)
	{//读取原文 
		int i = 0;
		while (zh[i] != ch)//找到对应的编码 
		{
			i++;
		}
		fprintf(w2, "%s", p[i + 1]);//写到r2文件 
	}
}


int main()
{
	FILE* ri, * wi, * re, * we, * rd, * wd, * wp, * wt;//定义一系列文件指针 
	HuffmanTree t=NULL;//创建一个哈夫曼树 
	int n=0;//字符集的大小 
	char name[500];
	for (;;)
	{
		printf("\n请选择: I:初始化   E:编码   D:译码   P:打印代码文件   T:打印赫夫曼树   Q:退出\n");
		char select;//用来存放命令 
		scanf("%c", &select);
		getchar();
		switch (select)
		{
		case 'Q':    //退出 
			return 0;
		case 'I':          //初始化  
			do
			{
				if ((wi = fopen("hfmTree.txt", "w")) == NULL)
				{
					exit(-1);
				}
				printf("请输入字符集大小：");
				scanf("%d", &n);
				getchar();
				int* w=(int*)malloc(sizeof(int)*n);//创建一个大小为n的数组，储存加权字符 S

				char *ch=(char*)malloc(sizeof(char)*(n + 1));
				ch[n] = '\0';//为字符串 
				printf("请输入%d个权值和字符：", n);
				read_weigth(&w[0], &ch[0], n);//读取节点 
				HuffmanCoding(&t, &w[0], n);//哈夫曼编码 
				strcpy(name, ch);
				//	                printf("%s\n",ch);
				//	                printf("%s\n",name);
				fprintf(wi, "字符集长度为：%d\n", n);
				//	                fprintf(wi,"%s\n",ch);
				for (int i = 0; i < n; i++)
				{
					fprintf(wi, "%d. ", i + 1);
					fprintf(wi, "字符%c对应的权值为%d \n", ch[i], w[i]);
				}
				fclose(wi);
				printf("初始化成功！结果存在文件'hfmTree.txt'中！\n");
				//	                fprintf(wi,"%s\n",ch);
				//	                fprintf(wi,"%d\n",n);
				//	                for(int i = 0;i < n;i++)
				//	                {
				//	                	fprintf(wi,"%d ",w[i]);
				//					}
				//					fclose(wi); 
				//					printf("初始化成功！结果存在文件'hfmTree.txt'中！\n");
			} while (0);
			break;
		case 'E':           //编码 
			do
			{
				printf("请将文件放入'ToBeTran.txt'中(放好请按ENTER继续)：");
				getchar();
				if ((ri = fopen("hfmTree.txt", "r")) == NULL)
				{
					exit(-1);
				}
				if ((re = fopen("ToBeTran.txt", "r")) == NULL)
				{
					exit(-1);
				}
				if ((we = fopen("CodeFile.txt", "w")) == NULL)
				{
					exit(-1);
				}
				char** dh;
				coding(&dh, n, t);//编码 ，dh为一个数组，n为字符集的长度，t为一个哈夫曼树 
				found(re, we, dh, n, name);
				fclose(ri);
				fclose(we);
				fclose(re);
				printf("编码成功。结果存在文件'CodeFile.txt'中。\n");
			} while (0);
			break;
		case 'D':          //译码 
			do
			{
				printf("请将文件放入'CodeFile.txt'中(放好请按ENTER继续)：");
				getchar();
				if ((rd = fopen("CodeFile.txt", "r")) == NULL)
				{
					exit(-1);
				}
				if ((wd = fopen("TextFile.txt", "w")) == NULL)
				{
					exit(-1);
				}
				if ((ri = fopen("hfmTree.txt", "r")) == NULL)
				{
					exit(-1);
				}
				char* h = (char*)malloc(sizeof(char) * (n + 1));
				//                	fscanf(ri,"%s",zh);
				decoding(rd, wd, t, n, name);
				fclose(rd);
				fclose(wd);
				fclose(ri);
				printf("译码成功。结果存在文件'TextFile.txt'中。\n");
			} while (0);
			break;
		case 'P':               //打印代码文件 
			do
			{
				if ((ri = fopen("hfmTree.txt", "r")) == NULL)
				{
					exit(-1);
				}
				if ((rd = fopen("CodeFile.txt", "r")) == NULL)
				{
					exit(-1);
				}
				if ((wp = fopen("CodePrint.txt", "w")) == NULL)
				{
					exit(-1);
				}
				char** dh;
				coding(&dh, n, t);
				//	                char zh[n + 1];
				//                	fscanf(ri,"%s",zh);
				for (int z = 0; z < n; z++)
				{
					fprintf(wp, "%c %s\n", name[z], dh[z + 1]);
				}
				int number = 0;
				for (char z; fscanf(rd, "%c", &z) != EOF;)
				{
					if (number >= 49)
					{
						printf("%c\n", z);
						number = 0;
					}
					else
					{
						printf("%c", z);
						number++;
					}
				}
				printf("\n");
				fclose(rd);
				fclose(wp);
				fclose(ri);
				printf("打印代码成功。结果存在文件'CodePrint.txt'中。\n");
			} while (0);
			break;
		case 'T':             //打印哈夫曼树 
			do
			{
				if ((wt = fopen("TreePrint.txt", "w")) == NULL)
				{
					exit(-1);
				}
				printf("weigth\tparent\tlchild\trchild\n");
				visit(t, wt, n);
				fclose(wt);
				printf("打印赫夫曼树成功。结果存在文件'TreePrint.txt'中。\n");
			} while (0);
			break;
		default: {
			printf("你的输入有误！请重试！\n");
			break;
		}
		}
	}
	return 0;
}

