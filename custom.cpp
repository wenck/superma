#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <graphics.h> 	   
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"kcgl.h"
#include"gkgm.h"
#include "UIpage.h"


struct member
{
	char huiymc[20] = "null";//会员名称
	char dianhhm[15] = "null";//电话号码
	member* pnext = NULL;
};
struct goumxx
{
	member huiyxx;//会员信息
	char shangpmc[20];//商品名称
	float goumsl;//购买数量
	date gmsj;//购买时间
	int i;//是否为会员
	goumxx* pnext;
};
FILE* fp2, * fp3;//2:会员信息文件指针3:购买记录文件指针
member* head2, * rear2;
goumxx* head3, * rear3;
good* head1, * rear1;

void chushgm()//初始化购买信息
{
	fopen_s(&fp3, "shoppinginformation.txt", "r");
	if (fp3 == NULL)
	{
		fopen_s(&fp3, "shoppinginformation.txt", "w");
		if (fp3 == NULL)
		{
			printf("创建购买信息文件失败！\n");
			exit(0);
		}
		printf("初次使用\n");
		//fprintf(fp3, "NULL      null\n");
		fclose(fp3);
	}
	else
	{
		while (!feof(fp3))
		{
			goumxx* p;
			p = (goumxx*)malloc(sizeof(goumxx));
			if (p == NULL)
			{
				printf("购买信息初始化错误！\n");
				exit(1);
			}
			fscanf(fp3, "%s      %s   %.2f   %02d/%02d/%02d   %d\n", &p->shangpmc, &p->huiyxx.huiymc, &p->goumsl, &p->gmsj.yue, &p->gmsj.ri, &p->gmsj.shi, &p->i);
			p->pnext = NULL;
			if (head3 == NULL)
			{
				head3 = p;
			}
			else
				rear3->pnext = p;
			rear3 = p;
			//printf("%d",ftell(fp));测试是否到文件尾
		}
		fclose(fp3);
	}
	return;
}

void chushhy()//初始化会员信息
{
	fopen_s(&fp2, "memberdata.txt", "r");
	if (fp2 == NULL)
	{
		fopen_s(&fp2, "memberdata.txt", "w");
		if (fp2 == NULL)
		{
			printf("创建文件失败！\n");
			exit(0);
		}
		printf("初次使用\n");
		fprintf(fp2, "NULL      null\n");
		fclose(fp2);
	}
	else
	{
		while (!feof(fp2))
		{
			member* p;
			p = (member*)malloc(sizeof(member));
			if (p == NULL)
			{
				printf("会员信息初始化错误！\n");
				exit(1);
			}
			fscanf(fp2, "%s %s\n", &p->huiymc, &p->dianhhm);
			p->pnext = NULL;
			if (head2 == NULL)
			{
				head2 = p;
			}
			else
				rear2->pnext = p;
			rear2 = p;
			//printf("%d",ftell(fp));测试是否到文件尾
		}
		fclose(fp2);
	}
}


void chushjr()//初始化金融系统
{
	chushgm();
	chushhy();
	head1 = kuctzz();
	rear1 = kucwzz();
}

void tianjhy()//添加会员
{
	fopen_s(&fp3, "memberdata.txt", "a");
	member* p;
	p = (member*)malloc(sizeof(member));
	if (p == NULL)
		exit(0);
	wchar_t  s[20], s2[20];
	InputBox(s2, 20, L"请录入会员名称: ", NULL, 0, 0, 0, true);
	while (*s2 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s2, 20, L"请重新录入会员名称: ", NULL, 0, 0, 0, true);
	}
	strcpy(p->huiymc, wtoch(s2));

	InputBox(s, 20, L"请录入电话号码:  ", NULL, 0, 0, 0, true);
	while (*s == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s, 20, L"请重新录入电话号码: ", NULL, 0, 0, 0, true);
	}

	strcpy(p->dianhhm, wtoch(s));

	//scanf_s("%s", &p->huiymc, 20);//录入会员名称
	//scanf_s("%s", &p->dianhhm, 20);//录入电话号码
	if (head2 == NULL)
	{
		head2 = p;
		rear2 = p;
	}
	rear2->pnext = p;
	p->pnext = NULL;
	rear2 = p;
	if (fp3 == NULL)
	{
		//printf("会员信息储存失败！");
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"会员信息储存失败！", L"警告", MB_OK | MB_ICONWARNING);
		return;
	}
	fprintf(fp3, "%s      %s", p->huiymc, p->dianhhm);//向文件中写入会员名称和电话号码
	//printf("已成功录入%s的会员信息！\n", p->huiymc);
	HWND wnd1 = GetHWnd();
	MessageBox(wnd1, L"已成功录入会员信息！", L"提示", MB_OK | MB_ICONINFORMATION);
	fclose(fp3);
}



void chuchy()//储存会员信息//
{
	member* p = head2;
	fopen_s(&fp2, "memberdata.txt", "w");
	if (fp2 == NULL)
	{
		printf("保存失败!\n");
		return;
	}
	while (p != NULL)
	{
		fprintf(fp2, "%s      %s\n", p->huiymc, p->dianhhm);
		p = p->pnext;
	}
	fclose(fp2);
}

void chgmxx()//储存购买信息(结尾用)
{
	goumxx* p = head3;
	fopen_s(&fp3, "shoppinginformation.txt", "w");
	if (fp3 == NULL)
	{
		printf("保存失败!\n");
		return;
	}
	while (p != NULL)
	{
		fprintf(fp3, "%s      %s   %.2f   %02d/%02d/%02d   %d\n", p->shangpmc, p->huiyxx.huiymc, p->goumsl, p->gmsj.yue, p->gmsj.ri, p->gmsj.shi, p->i);
		p = p->pnext;
	}
	fclose(fp3);
}

void xiaosedb()//销售额打表
{
	goumxx* gp = head3;
	good* p = head1;
	while (p != NULL)
	{
		printf("名称：%s      ", p->mingc);
		printf("当前净利润：%f\n", p->lir);
		p = p->pnext;
	}

}

void lirjs(good* p, int j, float n) //利润计算
{
	p->lir = n * (p->shouj - p->jinj);
	if (j)
	{
		p->lir = p->lir * (COUNT);
	}
}


void goum()//购买函数
{

	int num;
	good* p;//库存链表头
	member* mp = head2;//会员链表头
	goumxx* gp = head3;//购买信息链表头
	p = head1;
	num = kucdb();
	printf("请选择购买的货品:\n");
	int i = 0;
	scanf_s("%d", &i);
	while (i <= 0 || i > num)
	{
		printf("不存在商品%d请重新输入:\n", i);
		scanf_s("%d", &i);
	}
	while (i > 1)
	{
		p = p->pnext;
		i--;
	}
	printf("请输入购买的数量（小于%.2f千克）:\n", p->kuc);
	float shul;
	scanf_s("%f", &shul);
	if (p->kuc < shul)
	{
		printf("%s库存不足!\n", p->mingc);
		return;
	}
	printf("请您输入购买时间(格式：月/日/时):\n");
	scanf_s("%d/%d/%d", &(gp->gmsj.yue), &(gp->gmsj.ri), &(gp->gmsj.shi));
	while ((gp->gmsj.ri) <= 0 || (gp->gmsj.yue) <= 0 || (gp->gmsj.shi) <= 0)//bug：如果填0时也会显示有误
	{
		printf("您输入的信息有误，请重新按格式(月/日/时)输入：\n");
		while (getchar() == '/');//用while循环吃掉上次输入残留的的‘/’
		scanf_s("%d/%d/%d", &(gp->gmsj.yue), &(gp->gmsj.ri), &(gp->gmsj.shi));
	}
	printf("请问是否为会员？\n");
	printf("Yes:1 No: 0\n");
	int j = 0;
	scanf_s("%d", &j);
	if (j)
	{
		char s[20];
		printf("请输入会员的名称或电话号码\n");
		scanf_s("%s", &s, 20);
		while (strcmp(mp->huiymc, s) != 0 && strcmp(mp->dianhhm, s) != 0)
		{
			if (mp == NULL)
			{
				printf("未找到会员信息\n");
				j = 0;
				break;
			}
			mp = mp->pnext;
		}
		printf("已自动打折\n");
	}
	lirjs(p, j, shul);
	p->kuc -= shul;
	gp->huiyxx = *mp;
	strcpy(gp->shangpmc, p->mingc);
	gp->goumsl = shul;
	gp->i = j;
	if (head3 == NULL)
	{
		head3 = gp;
		rear3 = gp;
	}
	rear3->pnext = gp;
	gp->pnext = NULL;
	rear3 = gp;
	fopen_s(&fp3, "shoppinginformation.txt", "a");
	if (fp3 == NULL)
	{
		printf("保存购买信息失败!\n");
		return;
	}
	fprintf(fp3, "%s      %s   %.2f   %02d/%02d/%02d         %d\n", gp->shangpmc, gp->huiyxx.huiymc, gp->goumsl, gp->gmsj.yue, gp->gmsj.ri, gp->gmsj.shi, gp->i);
	fclose(fp3);
	//这里可以显示一下购买信息 一串那种 
	return;
}//记录销售额
void shiflbkj2()//释放会员信息链表
{
	member* p = head2;
	while (p != NULL)
	{
		member* pf = p->pnext;
		free(p);
		p = pf;
	}
}

void shiflbkj3()//释放购买信息链表
{
	goumxx* p = head3;
	while (p != NULL)
	{
		goumxx* pf = p->pnext;
		free(p);
		p = pf;
	}
}

long double jiszlr()//计算总利润
{
	long double zonglr = 0;//总利润
	good* p = head1;
	while (p != NULL)
	{
		if (p->lir >= 0)
			zonglr += p->lir;
		else
			zonglr += 0;
		p = p->pnext;
	}
	return zonglr;
}