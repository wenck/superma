#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <graphics.h> 	   
#include<stdio.h>
#include<stdlib.h>
#include"kcgl.h"
#include"gkgm.h"
#include"UIpage.h"
int anniu(int x,int y);
FILE* fp;
FILE* fp4;
good* head, * rear;

SYSTEMTIME time;
good* function(int n)//����û���,����ֵΪ���ʱ��Ӧҳ��ĵ�һ����Ʒ��nΪ��Ӧҳ��
{
	
	good* p = head;
	while (n > 1)//n����ҳ�����ڼ�ҳ����Ҫp��ͷָ����ƶ�(n-1)*k�����ҵ���Ӧҳ���ĵ�һ����Ʒ
	{
		int i = k;
		while (i >= 1&&p!=NULL)//һҳ��k��,��Ҫ��k��
		{
			p = p->pnext;
			i--;
		}
		n--;
	}
	return p;
}

void kucjh()//������
{
	kucdb();
	printf("�����½������Ƿ����ڿ���б��У�");
	int i = 1;
	scanf_s("%d", &i);//�Ӿ��棡��
	if (i)
	{
		if (head == NULL)
		{
			printf("����ѿ�;");
			return;
		}
		int num;
		num = kucdb();
		printf("��ѡ���������Ļ���:\n");//���ӻ�����
		int j = 0;
		good* p = head;
		scanf_s("%d", &j);
		while (j > 1)
		{
			p = p->pnext;
			j--;
		}//�ҵ���Ӧ�Ľṹ��
		float add = 0;
		scanf_s("%lf", &add);
		p->kuc += add;
		
		fopen_s(&fp4, "buyininformation.txt", "a");
		if (fp4 == NULL)
		{
			printf("���������Ϣʧ��!");
			return;
		}
		fprintf(fp4, "%s     %s     %f\n", p->mingc, time/*��ʱ��ת��Ϊ�ַ���д���ļ�*/, add);
		fclose(fp4);
	}
	else
	{
		xinjkc();
	}
}

void kucxg1(good* p) //�޸Ŀ����ָ��һ��
{
	xinxsc(p);

	while (1)
	{
		printf("�����������Ϣ�д��ڴ����1����\n");
		printf("1.���� 2.����ʱ�� 3.����� 4.����/�ۼ�\n");
		int j = -1;
		scanf_s("%d", &j);
		while (j != 1 && j != 2 && j != 3 && j != 4)
		{
			printf("�����������Ϣ�д��ڴ����1����\n");
			printf("1.���� 2.����ʱ�� 3.����� 4.����/�ۼ�\n");
			scanf_s("%d", &j);
		}
		switch (j)
		{
		case 1:printf("��������Ҫ��ӵ���Ʒ��������:\n");
			scanf_s("%s", &p->mingc, 20); break;
		case 2:printf("�����������ʱ��(��ʽ����/��/ʱ):\n");
			scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
			while ((p->jinhsj.ri) <= 0 || (p->jinhsj.yue) <= 0 || (p->jinhsj.shi) <= 0) //�����0ʱҲ����ʾ����
			{
				printf("���������Ϣ���������°���ʽ(��/��/ʱ)���룺\n");
				while (getchar() == '/');//��whileѭ���Ե��ϴ���������ĵġ�/��
				scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
			}break;
		case 3:printf("�������������(��λ��ǧ��):\n"); scanf_s("%f", &(p->kuc));
			while (p->kuc < 0)
			{
				printf("���������Ϣ����������������ȷ�Ľ�������\n");
				scanf_s("%f", &p->kuc);
			}break;
		case 4: printf("�����ֱ�������� �ۼ�:\n");
			scanf_s("%f %f", &(p->jinj), &(p->shouj));
			while (p->jinj < 0 || p->shouj < 0)
			{
				printf("���������Ϣ����������������ȷ���ۺ��ۼۣ��м��ÿո������");
				scanf_s("%f %f", &(p->jinj), &(p->shouj));
			}break;
		}
		printf("\n�������Ϣ�Դ��ڴ���������1����������0\n");
		xinxsc(p);
		int i = -1;
		scanf_s("%d", &i);
		while (i != 1 && i != 0)
		{
			printf("����ȷ����1��0 \n");
			scanf_s("%d", &i);
		}
		if (!i)
			break;
	}
}

void kucxg2()//�޸Ŀ��������һ��
{
	if (head == NULL)
	{
		HWND wnd = GetHWnd();     //windowsԭ������
		MessageBox(wnd, L"��ʾ", L"����ѿ�", MB_OK | MB_ICONINFORMATION);
		//printf("����ѿ�;");
		return;
	}
	
	//outtextxy(180, 120, L"2. �������");
	
	int num, x;
	num = kucdb();
	int n = 1;  //ҳ�룻
	int sum = num / 6; //ҳ������

	kucdb1(function(n), n,sum);//�����UI
	//printf("������������Ҫ�޸ĵ���Ŀ:\n");//���ӻ�����
	ExMessage m;//���ָ��
	int event = 0,i;
	while (true)
	{
		m = getmessage();//��ȡһ�������Ϣ

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//������ɫΪ����ɫ
			setlinestyle(PS_SOLID, 3);//���û�����ʽΪʵ�֣�10��
			setfillcolor(WHITE);//�����ɫΪ��ɫ
		
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//��Ԫ��դ����NOT(��Ļ��ɫ XOR ��ǰ��ɫ)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//����Բ��ɫ
				circle(m.x, m.y, 2 * i);
				Sleep(30);//ͣ��30ms
				circle(m.x, m.y, 2 * i);//Ĩȥ�ոջ���Բ
			}
			wchar_t s22[] = L"Hello World";
			HWND wnd = GetHWnd();      //windowsԭ������
			FILE* fp = NULL, * fp1 = NULL;
			wchar_t buff[2550];
			errno_t err = fopen_s(&fp, "test.txt", "a+");

			fgetws(buff, 2550, fp);
			fclose(fp);
			wchar_t* s = NULL;
			s = new wchar_t[20];


			switch (anniu(m.x, m.y))
			{
				//��ԭ��ťԭ��
			case 8: 
				n--;
				cleardevice();
				kucdb1(function(n), n, sum);
				flushmessage();
				break;
			case 7:
				n++; 
				cleardevice();
				kucdb1(function(n), n, sum);
				break;
			case 1:
				check1(function(n));
				flushmessage();//�����¼�����������Ϣ
				break;
			case 2:
				check1(function(n)->pnext);
				flushmessage();//�����¼�����������Ϣ
				break;
			case 3:
				check1(function(n)->pnext->pnext);//�رջ�ͼ����
				flushmessage();
				//exit(0);//�����˳�
				break;
			case 4:
				check1(function(n)->pnext->pnext->pnext);
				flushmessage();//�����¼�����������Ϣ
				break;
			case 5:
				check1(function(n)->pnext->pnext->pnext->pnext );
				flushmessage();//�����¼�����������Ϣ
				break;
			case 6:
				check1(function(n)->pnext->pnext->pnext->pnext->pnext );
				flushmessage();//�����¼�����������Ϣ
				break;
			default:

				flushmessage();//�����¼�����������Ϣ
				break;
			}
			fwprintf(fp, s);
			fclose(fp);
			break;
			flushmessage();//��������Ϣ������
		}
	}

	system("pause");//��ͣ��Ϊ����ʾ
	int j = 0;
	good* p = head;
	scanf_s("%d", &j);
	x = j;
	while (j > 1)
	{
		p = p->pnext;
		j--;
	}//�ҵ���Ӧ�Ľṹ��
	kucxg1(p);//���ҵ���Ŀ��ṹ�崫���޸ĺ���1
}

void xinxsc(good* p)//��Ϣ���
{

	printf("���ƣ�%s", p->mingc);
	printf("   ");
	printf("����ʱ�䣺%02d��%02d��%02dʱ", p->jinhsj.yue, p->jinhsj.ri, p->jinhsj.shi);
	printf("   ");
	printf("�������%.2f", p->kuc);
	printf("   ");
	printf("�����ۣ�%.2f   ���ۼۣ�%.2f\n", p->jinj, p->shouj);
}//���������ĳ���ߵ�ȫ����Ϣ����Ϣ�����//////�Ժ�����޸��¸�ʽ
void xinxsc1(good* p,int i)//��Ϣ���
{
	// �ַ�����ת��
	TCHAR s[]=_T("helloworld");   
	TCHAR s1[] = _T("jinhsj.ri");
	TCHAR s2[] = _T("jinhsj.shi");
	TCHAR s3[] = _T("jinhsj.shi");
	TCHAR s4[] = _T("jinhsj.shi");
	TCHAR s5[] = _T("jinhsj.shi");

	_stprintf(s, _T("%d"), p->jinhsj.yue);		
	_stprintf(s1, _T("%d"), p->jinhsj.ri);
	_stprintf(s2, _T("%d"), p->jinhsj.shi);
	_stprintf(s3, _T("%.2lf"), p->kuc);
	_stprintf(s4, _T("%.2lf"), p->jinj);
	_stprintf(s5, _T("%.2lf"), p->shouj);

	//���������
	outtextxy(65, 70+50*i, chtow(p->mingc));
	outtextxy(170, 70 + i * 50, s);
	outtextxy(180, 70 + i * 50, L"/");
	outtextxy(190, 70 + i * 50, s1);
	outtextxy(200, 70 + i * 50, L"/");
	outtextxy(210, 70 + i * 50, s2);
	outtextxy(340, 70 + i * 50, s3);
	outtextxy(430, 70 + i * 50, s4);
	outtextxy(500, 70 + i * 50,s5);

	/*printf("���ƣ�%s", p->mingc);
	printf("   ");
	printf("����ʱ�䣺%02d��%02d��%02dʱ", p->jinhsj.yue, p->jinhsj.ri, p->jinhsj.shi);
	printf("   ");
	printf("�������%.2f", p->kuc);
	printf("   ");
	printf("�����ۣ�%.2f   ���ۼۣ�%.2f\n", p->jinj, p->shouj);*/
}//���������ĳ���ߵ�ȫ����Ϣ����Ϣ�����//////�Ժ�����޸��¸�ʽ

int kucdb()//�����
{
	good* tmpp = head;
	int i = 1;
	while (tmpp != NULL)
	{
		//printf("��Ʒ%d.  ", i);
		//xinxsc(tmpp);
		tmpp = tmpp->pnext;
		i++;
	}
	return --i;
}

int anniu(int x, int y)                 //�жϰ�ť��λ�ú���
{

	if (x >600&& x<700 && y>110 && y < 140)    return 1;
	if (x > 600 && x<700 && y>160 && y < 190)  return 2;
	if (x > 600 && x<700 && y>210 && y < 240)return 3;
	if (x > 600 && x<700 && y>260 && y < 290)return 4;
	if (x > 600 && x < 700 && y>310 && y < 340)return 5;
	if (x > 600 && x < 700 && y>360 && y < 390)return 6;
	if (x > 500 && x < 570 && y>500 && y < 550)return 7;
	if (x > 200 && x < 270 && y>500 && y < 550)return 8;

	return 0;
}


void kucdb1(good* p, int n,int sum)//�����UI
{
	LOGFONT f;//������ʽָ��
	gettextstyle(&f);					//��ȡ������ʽ
	wcscpy_s(f.lfFaceName, _T("����"));	//��������Ϊ����
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // ����������ʽ
	settextcolor(RED);
	outtextxy(300, 20, L"�������   ");
	settextcolor(BLACK);

	//����������Ŀ����Ӧֵ
	outtextxy(8, 80, L"���");
	outtextxy(65, 80, L"����");
	outtextxy(140, 80, L"����ʱ�� (��/��/ʱ)");
	outtextxy(330, 80, L" �����");
	outtextxy(430, 80, L"����");
	outtextxy(500, 80, L"���ۼ�");

	good* tmpp = p;
	int i = (n-1)*6+1;
	TCHAR s[] = _T("Hello World");  //�ַ�ת���м���
	int j = 1;
	//if(n==1){}
	while (tmpp != NULL&&j<=6)
	{
		settextcolor(BLACK);
		//printf("��Ʒ%d.  ", i);
		_stprintf(s, _T("%d"), i);
		outtextxy(15, 70+j * 50, s);
		xinxsc1(tmpp,j);  //��ӡ��������

		//����ÿ���޸İ�ť
		int r1[4] = { 600,60 + 50 * j,700,90 + 50 * j };    
		RECT R1 = { 600,60 + 50 * j,700,90 + 50 * j };

		
		gettextstyle(&f);					//��ȡ������ʽ
		wcscpy_s(f.lfFaceName, _T("����"));	//��������Ϊ��
		f.lfQuality = ANTIALIASED_QUALITY;
		f.lfWeight = FW_BOLD;
		settextstyle(&f);                     // ����������ʽ
		settextcolor(BLACK);
		drawtext(_T("�޸�"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 2, 0, 0);
		rectangle(600, 60 + 50 * j, 700, 90 + 50 * j);
		tmpp = tmpp->pnext;
		i++;
		j++;
	}
	if (n == 1) {
		if (n < sum) {
			int xia[4] = { 500,500,570,550 };
			//int shang[4] = { 200,500,270,550 };
			RECT xiazz = { 500,500,570,550 };
			//RECT shangzz = { 200,500,270,550 };
			drawtext(_T("��һҳ"), &xiazz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			//drawtext(_T("��һҳ"), &shangzz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
	else if (n <sum+1) {
		int xia[4] = { 500,500,570,550 };
		int shang[4]= { 200,500,270,550 };
		RECT xiazz = { 500,500,570,550 };
		RECT shangzz= { 200,500,270,550 };
		drawtext(_T("��һҳ"), &xiazz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("��һҳ"), &shangzz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	if(n==sum+1)
	{
		int shang[4] = { 200,500,270,550 };
		RECT shangzz = { 200,500,270,550 };
		drawtext(_T("��һҳ"), &shangzz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	
}

void kucxg(good* p) //�޸Ŀ����ָ��ĳ���ߵ�ĳ����Ϣ���޸ģ�
{
	xinxsc(p);

	while (1)
	{
		printf("�����������Ϣ�д��ڴ����1����\n");
		printf("1.���� 2.����ʱ�� 3.����� 4.����/�ۼ�\n");
		int j = -1;
		scanf_s("%d", &j);
		while (j != 1 && j != 2 && j != 3 && j != 4)
		{
			printf("�����������Ϣ�д��ڴ����1����\n");
			printf("1.���� 2.����ʱ�� 3.����� 4.����/�ۼ�\n");
			scanf_s("%d", &j);
		}
		switch (j)
		{
		case 1:printf("��������Ҫ��ӵ���Ʒ��������:\n");
			scanf_s("%s", &p->mingc, 20); break;
		case 2:printf("�����������ʱ��(��ʽ����/��/ʱ):\n");
			scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
			while ((p->jinhsj.ri) <= 0 || (p->jinhsj.yue) <= 0 || (p->jinhsj.shi) <= 0)//bug�������0ʱҲ����ʾ����
			{
				printf("���������Ϣ���������°���ʽ(��/��/ʱ)���룺\n");
				while (getchar() == '/');//��whileѭ���Ե��ϴ���������ĵġ�/��
				scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
			}break;
		case 3:printf("�������������(��λ��ǧ��):\n"); scanf_s("%f", &(p->kuc));
			while (p->kuc < 0)
			{
				printf("���������Ϣ����������������ȷ�Ľ�������\n");
				scanf_s("%f", &p->kuc);
			}break;
		case 4: printf("�����ֱ�������� �ۼ�:\n");
			scanf_s("%f %f", &(p->jinj), &(p->shouj));
			while (p->jinj < 0 || p->shouj < 0)
			{
				printf("���������Ϣ����������������ȷ���ۺ��ۼۣ��м��ÿո������");
				scanf_s("%f %f", &(p->jinj), &(p->shouj));
			}break;
		}
		printf("\n�������Ϣ�Դ��ڴ���������1����������0\n");
		xinxsc(p);
		int i = -1;
		scanf_s("%d", &i);
		while (i != 1 && i != 0)
		{
			printf("����ȷ����1��0 \n");
			scanf_s("%d", &i);
		}
		if (!i)
			break;
	}
}

void xinjkc()//������һ����
{
	//rear = head;
	//while (rear->pnext != NULL)
	//{
	//	rear = rear->pnext;
	//}//�ҵ�����β����ֹɾ�������һ��֮��rear�Ҳ�����β
	good* p;
	p = (good*)malloc(sizeof(good));
	if (p == NULL)
		exit(1);
	wchar_t  s[20], s2[20], s3[20], s4[20], s5[20], s6[20];
	InputBox(s, 20, L"�밴˳��������Ҫ��ӵ���Ʒ��������: ", NULL, 0, 0, 0,true);
	while (*s == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"��������հ���Ϣ", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s, 20, L"�밴˳��������Ҫ��ӵ���Ʒ��������: ", NULL, 0, 0, 0, true);
	}
	 strcpy(p->mingc , wtoch(s));
	//printf("�밴˳��������Ҫ��ӵ���Ʒ��������:\n");
	//scanf_s("%s", &(p->mingc), 20);
	        //����ϵͳʱ��ṹ��
	 GetLocalTime(&time);  //��ȡ��ǰϵͳʱ��

	 //��ǰϵͳʱ����Ϊ����ʱ�䱣��
	 p->jinhsj.ri = time.wDay;
	 p->jinhsj.yue = time.wMonth;
	 p->jinhsj.shi = time.wHour;

	/*InputBox(s2, 20, L"�����������ʱ��(��ʽ����/��/ʱ):  ", NULL, 0, 0, 0, false);
	while (*s2 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"��������հ���Ϣ", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s2, 20, L"�����������ʱ��(��ʽ����/��/ʱ):  ", NULL, 0, 0, 0, false);
	}
	//printf("�����������ʱ��(��ʽ����/��/ʱ):\n");
	//scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
	while ((p->jinhsj.ri) <= 0 || (p->jinhsj.yue) <= 0 || (p->jinhsj.shi) <= 0)//bug�������0ʱҲ����ʾ����
	{
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"���������Ϣ���������°���ʽ(��/��/ʱ)���룺", L"����", MB_OK | MB_ICONWARNING);
		//printf("���������Ϣ���������°���ʽ(��/��/ʱ)���룺\n");
		while (getchar() == '/');//��whileѭ���Ե��ϴ���������ĵġ�/��
		scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
	}
	*/
	InputBox(s3, 20, L"�������������:  ", NULL, 0, 0, 0, true);
	while (*s3 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"��������հ���Ϣ", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s3, 20, L"���������������  ", NULL, 0, 0, 0, true);
	}

	//scanf_s("%f", &(p->kuc));
	while (_wtof(s3) < 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, L"���������Ϣ����", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s3, 20, L"��������������� \n", NULL, 0, 0, 0, true);
		//scanf_s("%f", &p->kuc);
	}
	p->kuc = _wtof(s3);

	InputBox(s4, 20, L"�����������: \n", NULL, 0, 0, 0, true);
	while (*s4 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"��������հ���Ϣ", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s4, 20, L"�����������: \n", NULL, 0, 0, 0, true);
	}
	while (_wtof(s4) < 0 )
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, L"���������Ϣ����", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s4, 20, L"�����������: \n", NULL, 0, 0, 0, true);
		//scanf_s("%f %f", &(p->jinj), &(p->shouj));
	}
	p->jinj=_wtof(s4);
	InputBox(s5, 20, L"���������ۼ�:\n", NULL, 0, 0, 0, true);
	while (*s5 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"��������հ���Ϣ", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s5, 20, L"���������ۼ�: \n", NULL, 0, 0, 0, true);
	}
	
	while (_wtof(s5) < p->jinj)
	{
		HWND wnd5 = GetHWnd();
		MessageBox(wnd5, L"�ۼ۲���С�ڽ��ۣ�", L"����", MB_OK | MB_ICONWARNING);
		InputBox(s5, 20, L"�������������ۼ�: \n", NULL, 0, 0, 0, true);
		//scanf_s("%f %f", &(p->jinj), &(p->shouj));
	}
	p->shouj=_wtof(s5);
	//printf("�����ֱ�������� �ۼ�:\n");
	//scanf_s("%f %f", &(p->jinj), &(p->shouj));     //������
	/*
	while (p->jinj < 0 || p->shouj < 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, L"���������Ϣ����", L"����", MB_OK | MB_ICONWARNING);
		scanf_s("%f %f", &(p->jinj), &(p->shouj));
	}
	*/
	//printf("������¼����Ϣ�Ƿ���ڴ���\n"); 

	int kkk = -1;//   �ж��Ƿ�������ȷ
	int j=check(kkk,s,s3,s4,s5,p);  

	//printf("\n�������Ϣ���ڴ���������1����������0\n");
	
	//scanf_s("%d", &j);
	/*
	
	while (j != 1 && j != 0)
	{
		printf("����ȷ����1��0 \n");
		scanf_s("%d", &j);
	}

	*/
	
	if (j)
	{
		kucxg1(p);
	}
	
	if (head == NULL)
	{
		head = p;
		rear = p;
	}
	rear->pnext = p;
	p->pnext = NULL;
	rear = p;
	baockc();       //���浽�ļ���
	storagepage(); //���ؿ�����ҳ��
}



void shanc()//ɾ��ĳ�ע�⵱����Ѿ�������ʱ�����
{
	if (head == NULL)
	{
		HWND wnd = GetHWnd();     //windowsԭ������
		MessageBox(wnd, L"��ʾ", L"���Ϊ��", MB_OK | MB_ICONINFORMATION);
		return;
	}
	int num, x;
	num = kucdb();
	printf("������������Ҫɾ������Ŀ:\n");//���ӻ�����
	int j = 0;
	good* p = head;
	scanf_s("%d", &j);
	x = j;
	while (j > 1)
	{
		p = p->pnext;
		j--;
	}//�ҵ���Ӧ�Ľṹ��
	good* pr = head;
	while (x > 2)
	{
		pr = pr->pnext;
		x--;
	}//�ҵ���Ӧ�Ľṹ��
	printf("\n");
	printf("������ȷ��Ҫɾ����%d��Ϣ��\n", j);
	xinxsc(p);
	printf("Yes:1 No: 0\n");
	int i = 1;
	scanf_s("%d", &i);
	if (i)
	{
		if (p == rear)
		{
			rear = pr;
		}
		if (p == head)
		{
			if (rear == head)
			{
				rear = NULL;
				head = NULL;
			}
			else
			{
				head = p->pnext;
			}
		}
		pr->pnext = NULL;
		free(p);
		HWND wnd = GetHWnd();     //windowsԭ������
		MessageBox(wnd, L"��ʾ", L"ɾ���ɹ�", MB_OK | MB_ICONINFORMATION);
	}
	return;
}

void baockc()//�����棬�������Ϣ�������ļ���
{
	good* p = head;
	fopen_s(&fp, "storagedata.txt", "w");
	if (fp == NULL)
	{
		HWND wnd = GetHWnd();     //windowsԭ������
		MessageBox(wnd, L"����ʧ��", L"����", MB_OK | MB_ICONWARNING);
		return;
	}
	while (p != NULL)
	{
		fprintf(fp, "%s      %02d/%02d/%02d   %.2f   %.2f  %.2f    %.2f\n", p->mingc, p->jinhsj.yue, p->jinhsj.ri, p->jinhsj.shi, p->kuc, p->jinj, p->shouj, p->lir);//�������  ���ڣ�����ʱ�� �����  �ۼ� ���� ��ǰ����
		p = p->pnext;
	}
	fclose(fp);
}

void shiflbkj(good* p)//�ͷ�����ռ�
{
	while (p != NULL)
	{
		good* pf = p->pnext;
		free(p);
		p = pf;
	}
}

void chushkc()//��ʼ�������Ϣ
{
	GetLocalTime(&time);
	HWND wnd = GetHWnd();
	fopen_s(&fp, "storagedata.txt", "r");
	if (fp == NULL)
	{
		fopen_s(&fp, "storagedata.txt", "w");
		if (fp == NULL)
		{
			
			MessageBox(wnd, L"�����ļ�ʧ��", L"����", MB_OK | MB_ICONWARNING);
			exit(0);
		}
		MessageBox(wnd, L"��ʾ", L"����ʹ��", MB_OK | MB_ICONINFORMATION);
		//fprintf(fp, "NULL      %02d/%02d/%02d   %.2f   %.2f  %.2f\n", 0, 0, 0, 0.0, 0.0, 0.0);//6/3/3/2
		fclose(fp);
	}
	else
	{
		while (!feof(fp))
		{
			good* p;
			p = (good*)malloc(sizeof(good));
			if (p == NULL)
			{
				MessageBox(wnd, L"�����ʼ������", L"����", MB_OK | MB_ICONWARNING);
				exit(1);
			}
			fscanf(fp, "%s %d/%d/%d %f %f %f %f\n", &p->mingc, &p->jinhsj.yue, &p->jinhsj.ri, &p->jinhsj.shi, &p->kuc, &p->jinj, &p->shouj, &p->lir);
			p->pnext = NULL;
			if (head == NULL)
			{
				head = p;
			}
			else
				rear->pnext = p;
			rear = p;
			//printf("%d",ftell(fp));�����Ƿ��ļ�β

		}
		fclose(fp);
	}
}

good* kuctzz()//���ݿ��ͷָ��
{
	return head;
};

good* kucwzz()//����βָ��
{
	return rear;
};

void jiescx()//���������ͷ�����ռ�,���������������˳�����ʱ����
{
	shiflbkj(head);
	shiflbkj2();
	shiflbkj3();
}

