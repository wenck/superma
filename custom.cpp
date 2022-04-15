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
	char huiymc[20] = "null";//��Ա����
	char dianhhm[15] = "null";//�绰����
	member* pnext = NULL;
};
struct goumxx
{
	member huiyxx;//��Ա��Ϣ
	char shangpmc[20];//��Ʒ����
	float goumsl;//��������
	date gmsj;//����ʱ��
	int i;//�Ƿ�Ϊ��Ա
	goumxx* pnext;
};
FILE* fp2, * fp3;//2:��Ա��Ϣ�ļ�ָ��3:�����¼�ļ�ָ��
member* head2, * rear2;
goumxx* head3, * rear3;
good* head1, * rear1;

void chushgm()//��ʼ��������Ϣ
{
	fopen_s(&fp3, "shoppinginformation.txt", "r");
	if (fp3 == NULL)
	{
		fopen_s(&fp3, "shoppinginformation.txt", "w");
		if (fp3 == NULL)
		{
			printf("����������Ϣ�ļ�ʧ�ܣ�\n");
			exit(0);
		}
		printf("����ʹ��\n");
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
				printf("������Ϣ��ʼ������\n");
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
			//printf("%d",ftell(fp));�����Ƿ��ļ�β
		}
		fclose(fp3);
	}
	return;
}

void chushhy()//��ʼ����Ա��Ϣ
{
	fopen_s(&fp2, "memberdata.txt", "r");
	if (fp2 == NULL)
	{
		fopen_s(&fp2, "memberdata.txt", "w");
		if (fp2 == NULL)
		{
			printf("�����ļ�ʧ�ܣ�\n");
			exit(0);
		}
		printf("����ʹ��\n");
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
				printf("��Ա��Ϣ��ʼ������\n");
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
			//printf("%d",ftell(fp));�����Ƿ��ļ�β
		}
		fclose(fp2);
	}
}


void chushjr()//��ʼ������ϵͳ
{
	chushgm();
	chushhy();
	head1 = kuctzz();
	rear1 = kucwzz();
}

void tianjhy()//��ӻ�Ա
{
	fopen_s(&fp3, "memberdata.txt", "a");
	member* p;
	p = (member*)malloc(sizeof(member));
	if (p == NULL)
		exit(0);
	wchar_t  s[20], s2[20];
	InputBox(s2, 20, L"��¼���Ա����: ", NULL, 0, 0, 0, true);
	while (*s2 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"��������հ���Ϣ", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s2, 20, L"������¼���Ա����: ", NULL, 0, 0, 0, true);
	}
	strcpy(p->huiymc, wtoch(s2));

	InputBox(s, 20, L"��¼��绰����:  ", NULL, 0, 0, 0, true);
	while (*s == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"��������հ���Ϣ", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s, 20, L"������¼��绰����: ", NULL, 0, 0, 0, true);
	}

	strcpy(p->dianhhm, wtoch(s));

	//scanf_s("%s", &p->huiymc, 20);//¼���Ա����
	//scanf_s("%s", &p->dianhhm, 20);//¼��绰����
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
		//printf("��Ա��Ϣ����ʧ�ܣ�");
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"��Ա��Ϣ����ʧ�ܣ�", L"����", MB_OK | MB_ICONWARNING);
		return;
	}
	fprintf(fp3, "%s      %s", p->huiymc, p->dianhhm);//���ļ���д���Ա���ƺ͵绰����
	//printf("�ѳɹ�¼��%s�Ļ�Ա��Ϣ��\n", p->huiymc);
	HWND wnd1 = GetHWnd();
	MessageBox(wnd1, L"�ѳɹ�¼���Ա��Ϣ��", L"��ʾ", MB_OK | MB_ICONINFORMATION);
	fclose(fp3);
}



void chuchy()//�����Ա��Ϣ//
{
	member* p = head2;
	fopen_s(&fp2, "memberdata.txt", "w");
	if (fp2 == NULL)
	{
		printf("����ʧ��!\n");
		return;
	}
	while (p != NULL)
	{
		fprintf(fp2, "%s      %s\n", p->huiymc, p->dianhhm);
		p = p->pnext;
	}
	fclose(fp2);
}

void chgmxx()//���湺����Ϣ(��β��)
{
	goumxx* p = head3;
	fopen_s(&fp3, "shoppinginformation.txt", "w");
	if (fp3 == NULL)
	{
		printf("����ʧ��!\n");
		return;
	}
	while (p != NULL)
	{
		fprintf(fp3, "%s      %s   %.2f   %02d/%02d/%02d   %d\n", p->shangpmc, p->huiyxx.huiymc, p->goumsl, p->gmsj.yue, p->gmsj.ri, p->gmsj.shi, p->i);
		p = p->pnext;
	}
	fclose(fp3);
}

void xiaosedb()//���۶���
{
	goumxx* gp = head3;
	good* p = head1;
	while (p != NULL)
	{
		printf("���ƣ�%s      ", p->mingc);
		printf("��ǰ������%f\n", p->lir);
		p = p->pnext;
	}

}

void lirjs(good* p, int j, float n) //�������
{
	p->lir = n * (p->shouj - p->jinj);
	if (j)
	{
		p->lir = p->lir * (COUNT);
	}
}


void goum()//������
{

	int num;
	good* p;//�������ͷ
	member* mp = head2;//��Ա����ͷ
	goumxx* gp = head3;//������Ϣ����ͷ
	p = head1;
	num = kucdb();
	printf("��ѡ����Ļ�Ʒ:\n");
	int i = 0;
	scanf_s("%d", &i);
	while (i <= 0 || i > num)
	{
		printf("��������Ʒ%d����������:\n", i);
		scanf_s("%d", &i);
	}
	while (i > 1)
	{
		p = p->pnext;
		i--;
	}
	printf("�����빺���������С��%.2fǧ�ˣ�:\n", p->kuc);
	float shul;
	scanf_s("%f", &shul);
	if (p->kuc < shul)
	{
		printf("%s��治��!\n", p->mingc);
		return;
	}
	printf("�������빺��ʱ��(��ʽ����/��/ʱ):\n");
	scanf_s("%d/%d/%d", &(gp->gmsj.yue), &(gp->gmsj.ri), &(gp->gmsj.shi));
	while ((gp->gmsj.ri) <= 0 || (gp->gmsj.yue) <= 0 || (gp->gmsj.shi) <= 0)//bug�������0ʱҲ����ʾ����
	{
		printf("���������Ϣ���������°���ʽ(��/��/ʱ)���룺\n");
		while (getchar() == '/');//��whileѭ���Ե��ϴ���������ĵġ�/��
		scanf_s("%d/%d/%d", &(gp->gmsj.yue), &(gp->gmsj.ri), &(gp->gmsj.shi));
	}
	printf("�����Ƿ�Ϊ��Ա��\n");
	printf("Yes:1 No: 0\n");
	int j = 0;
	scanf_s("%d", &j);
	if (j)
	{
		char s[20];
		printf("�������Ա�����ƻ�绰����\n");
		scanf_s("%s", &s, 20);
		while (strcmp(mp->huiymc, s) != 0 && strcmp(mp->dianhhm, s) != 0)
		{
			if (mp == NULL)
			{
				printf("δ�ҵ���Ա��Ϣ\n");
				j = 0;
				break;
			}
			mp = mp->pnext;
		}
		printf("���Զ�����\n");
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
		printf("���湺����Ϣʧ��!\n");
		return;
	}
	fprintf(fp3, "%s      %s   %.2f   %02d/%02d/%02d         %d\n", gp->shangpmc, gp->huiyxx.huiymc, gp->goumsl, gp->gmsj.yue, gp->gmsj.ri, gp->gmsj.shi, gp->i);
	fclose(fp3);
	//���������ʾһ�¹�����Ϣ һ������ 
	return;
}//��¼���۶�
void shiflbkj2()//�ͷŻ�Ա��Ϣ����
{
	member* p = head2;
	while (p != NULL)
	{
		member* pf = p->pnext;
		free(p);
		p = pf;
	}
}

void shiflbkj3()//�ͷŹ�����Ϣ����
{
	goumxx* p = head3;
	while (p != NULL)
	{
		goumxx* pf = p->pnext;
		free(p);
		p = pf;
	}
}

long double jiszlr()//����������
{
	long double zonglr = 0;//������
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