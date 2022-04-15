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
good* function(int n)//名字没想好,返回值为打表时对应页码的第一个商品，n为对应页码
{
	
	good* p = head;
	while (n > 1)//n代表页数，第几页就需要p在头指针后移动(n-1)*k次来找到对应页数的第一个商品
	{
		int i = k;
		while (i >= 1&&p!=NULL)//一页有k个,需要跳k次
		{
			p = p->pnext;
			i--;
		}
		n--;
	}
	return p;
}

void kucjh()//库存进货
{
	kucdb();
	printf("请问新进货物是否已在库存列表中？");
	int i = 1;
	scanf_s("%d", &i);//加警告！！
	if (i)
	{
		if (head == NULL)
		{
			printf("库存已空;");
			return;
		}
		int num;
		num = kucdb();
		printf("请选择您所进的货物:\n");//可视化处理
		int j = 0;
		good* p = head;
		scanf_s("%d", &j);
		while (j > 1)
		{
			p = p->pnext;
			j--;
		}//找到对应的结构体
		float add = 0;
		scanf_s("%lf", &add);
		p->kuc += add;
		
		fopen_s(&fp4, "buyininformation.txt", "a");
		if (fp4 == NULL)
		{
			printf("储存入库信息失败!");
			return;
		}
		fprintf(fp4, "%s     %s     %f\n", p->mingc, time/*把时间转换为字符串写入文件*/, add);
		fclose(fp4);
	}
	else
	{
		xinjkc();
	}
}

void kucxg1(good* p) //修改库存中指定一项
{
	xinxsc(p);

	while (1)
	{
		printf("请输入该条信息中存在错误的1个项\n");
		printf("1.名称 2.进货时间 3.库存量 4.进价/售价\n");
		int j = -1;
		scanf_s("%d", &j);
		while (j != 1 && j != 2 && j != 3 && j != 4)
		{
			printf("请输入该条信息中存在错误的1个项\n");
			printf("1.名称 2.进货时间 3.库存量 4.进价/售价\n");
			scanf_s("%d", &j);
		}
		switch (j)
		{
		case 1:printf("请输入您要添加的商品种类名称:\n");
			scanf_s("%s", &p->mingc, 20); break;
		case 2:printf("请您输入进货时间(格式：月/日/时):\n");
			scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
			while ((p->jinhsj.ri) <= 0 || (p->jinhsj.yue) <= 0 || (p->jinhsj.shi) <= 0) //如果填0时也会显示有误
			{
				printf("您输入的信息有误，请重新按格式(月/日/时)输入：\n");
				while (getchar() == '/');//用while循环吃掉上次输入残留的的‘/’
				scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
			}break;
		case 3:printf("请您输入进货量(单位：千克):\n"); scanf_s("%f", &(p->kuc));
			while (p->kuc < 0)
			{
				printf("您输入的信息有误，请重新输入正确的进货量：\n");
				scanf_s("%f", &p->kuc);
			}break;
		case 4: printf("请您分别输入进价 售价:\n");
			scanf_s("%f %f", &(p->jinj), &(p->shouj));
			while (p->jinj < 0 || p->shouj < 0)
			{
				printf("您输入的信息有误，请重新输入正确进价和售价（中间用空格隔开）");
				scanf_s("%f %f", &(p->jinj), &(p->shouj));
			}break;
		}
		printf("\n如该条信息仍存在错误，请输入1，否则输入0\n");
		xinxsc(p);
		int i = -1;
		scanf_s("%d", &i);
		while (i != 1 && i != 0)
		{
			printf("请正确输入1或0 \n");
			scanf_s("%d", &i);
		}
		if (!i)
			break;
	}
}

void kucxg2()//修改库存中任意一项
{
	if (head == NULL)
	{
		HWND wnd = GetHWnd();     //windows原生窗口
		MessageBox(wnd, L"提示", L"库存已空", MB_OK | MB_ICONINFORMATION);
		//printf("库存已空;");
		return;
	}
	
	//outtextxy(180, 120, L"2. 库存量：");
	
	int num, x;
	num = kucdb();
	int n = 1;  //页码；
	int sum = num / 6; //页码总数

	kucdb1(function(n), n,sum);//库存打表UI
	//printf("请输入您所需要修改的项目:\n");//可视化处理
	ExMessage m;//鼠标指针
	int event = 0,i;
	while (true)
	{
		m = getmessage();//获取一条鼠标消息

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(WHITE);//填充颜色为白色
		
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			wchar_t s22[] = L"Hello World";
			HWND wnd = GetHWnd();      //windows原生窗口
			FILE* fp = NULL, * fp1 = NULL;
			wchar_t buff[2550];
			errno_t err = fopen_s(&fp, "test.txt", "a+");

			fgetws(buff, 2550, fp);
			fclose(fp);
			wchar_t* s = NULL;
			s = new wchar_t[20];


			switch (anniu(m.x, m.y))
			{
				//复原按钮原型
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
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 2:
				check1(function(n)->pnext);
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 3:
				check1(function(n)->pnext->pnext);//关闭绘图环境
				flushmessage();
				//exit(0);//正常退出
				break;
			case 4:
				check1(function(n)->pnext->pnext->pnext);
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 5:
				check1(function(n)->pnext->pnext->pnext->pnext );
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 6:
				check1(function(n)->pnext->pnext->pnext->pnext->pnext );
				flushmessage();//单击事件后清空鼠标消息
				break;
			default:

				flushmessage();//单击事件后清空鼠标消息
				break;
			}
			fwprintf(fp, s);
			fclose(fp);
			break;
			flushmessage();//清空鼠标消息缓存区
		}
	}

	system("pause");//暂停，为了显示
	int j = 0;
	good* p = head;
	scanf_s("%d", &j);
	x = j;
	while (j > 1)
	{
		p = p->pnext;
		j--;
	}//找到对应的结构体
	kucxg1(p);//把找到的目标结构体传入修改函数1
}

void xinxsc(good* p)//信息输出
{

	printf("名称：%s", p->mingc);
	printf("   ");
	printf("进货时间：%02d月%02d日%02d时", p->jinhsj.yue, p->jinhsj.ri, p->jinhsj.shi);
	printf("   ");
	printf("库存量：%.2f", p->kuc);
	printf("   ");
	printf("进货价：%.2f   零售价：%.2f\n", p->jinj, p->shouj);
}//输出链表中某果蔬的全部信息（信息输出）//////以后可以修改下格式
void xinxsc1(good* p,int i)//信息输出
{
	// 字符类型转换
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

	//输出各数据
	outtextxy(65, 70+50*i, chtow(p->mingc));
	outtextxy(170, 70 + i * 50, s);
	outtextxy(180, 70 + i * 50, L"/");
	outtextxy(190, 70 + i * 50, s1);
	outtextxy(200, 70 + i * 50, L"/");
	outtextxy(210, 70 + i * 50, s2);
	outtextxy(340, 70 + i * 50, s3);
	outtextxy(430, 70 + i * 50, s4);
	outtextxy(500, 70 + i * 50,s5);

	/*printf("名称：%s", p->mingc);
	printf("   ");
	printf("进货时间：%02d月%02d日%02d时", p->jinhsj.yue, p->jinhsj.ri, p->jinhsj.shi);
	printf("   ");
	printf("库存量：%.2f", p->kuc);
	printf("   ");
	printf("进货价：%.2f   零售价：%.2f\n", p->jinj, p->shouj);*/
}//输出链表中某果蔬的全部信息（信息输出）//////以后可以修改下格式

int kucdb()//库存打表
{
	good* tmpp = head;
	int i = 1;
	while (tmpp != NULL)
	{
		//printf("商品%d.  ", i);
		//xinxsc(tmpp);
		tmpp = tmpp->pnext;
		i++;
	}
	return --i;
}

int anniu(int x, int y)                 //判断按钮的位置函数
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


void kucdb1(good* p, int n,int sum)//库存打表UI
{
	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	wcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(RED);
	outtextxy(300, 20, L"库存打表检查   ");
	settextcolor(BLACK);

	//输出待检查项目及对应值
	outtextxy(8, 80, L"序号");
	outtextxy(65, 80, L"名称");
	outtextxy(140, 80, L"进货时间 (月/日/时)");
	outtextxy(330, 80, L" 库存量");
	outtextxy(430, 80, L"进价");
	outtextxy(500, 80, L"零售价");

	good* tmpp = p;
	int i = (n-1)*6+1;
	TCHAR s[] = _T("Hello World");  //字符转换中间量
	int j = 1;
	//if(n==1){}
	while (tmpp != NULL&&j<=6)
	{
		settextcolor(BLACK);
		//printf("商品%d.  ", i);
		_stprintf(s, _T("%d"), i);
		outtextxy(15, 70+j * 50, s);
		xinxsc1(tmpp,j);  //打印各个数据

		//创建每个修改按钮
		int r1[4] = { 600,60 + 50 * j,700,90 + 50 * j };    
		RECT R1 = { 600,60 + 50 * j,700,90 + 50 * j };

		
		gettextstyle(&f);					//获取字体样式
		wcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋
		f.lfQuality = ANTIALIASED_QUALITY;
		f.lfWeight = FW_BOLD;
		settextstyle(&f);                     // 设置字体样式
		settextcolor(BLACK);
		drawtext(_T("修改"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

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
			drawtext(_T("下一页"), &xiazz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			//drawtext(_T("上一页"), &shangzz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
	else if (n <sum+1) {
		int xia[4] = { 500,500,570,550 };
		int shang[4]= { 200,500,270,550 };
		RECT xiazz = { 500,500,570,550 };
		RECT shangzz= { 200,500,270,550 };
		drawtext(_T("下一页"), &xiazz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		drawtext(_T("上一页"), &shangzz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	if(n==sum+1)
	{
		int shang[4] = { 200,500,270,550 };
		RECT shangzz = { 200,500,270,550 };
		drawtext(_T("上一页"), &shangzz, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	
}

void kucxg(good* p) //修改库存中指定某果蔬的某项信息（修改）
{
	xinxsc(p);

	while (1)
	{
		printf("请输入该条信息中存在错误的1个项\n");
		printf("1.名称 2.进货时间 3.库存量 4.进价/售价\n");
		int j = -1;
		scanf_s("%d", &j);
		while (j != 1 && j != 2 && j != 3 && j != 4)
		{
			printf("请输入该条信息中存在错误的1个项\n");
			printf("1.名称 2.进货时间 3.库存量 4.进价/售价\n");
			scanf_s("%d", &j);
		}
		switch (j)
		{
		case 1:printf("请输入您要添加的商品种类名称:\n");
			scanf_s("%s", &p->mingc, 20); break;
		case 2:printf("请您输入进货时间(格式：月/日/时):\n");
			scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
			while ((p->jinhsj.ri) <= 0 || (p->jinhsj.yue) <= 0 || (p->jinhsj.shi) <= 0)//bug：如果填0时也会显示有误
			{
				printf("您输入的信息有误，请重新按格式(月/日/时)输入：\n");
				while (getchar() == '/');//用while循环吃掉上次输入残留的的‘/’
				scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
			}break;
		case 3:printf("请您输入进货量(单位：千克):\n"); scanf_s("%f", &(p->kuc));
			while (p->kuc < 0)
			{
				printf("您输入的信息有误，请重新输入正确的进货量：\n");
				scanf_s("%f", &p->kuc);
			}break;
		case 4: printf("请您分别输入进价 售价:\n");
			scanf_s("%f %f", &(p->jinj), &(p->shouj));
			while (p->jinj < 0 || p->shouj < 0)
			{
				printf("您输入的信息有误，请重新输入正确进价和售价（中间用空格隔开）");
				scanf_s("%f %f", &(p->jinj), &(p->shouj));
			}break;
		}
		printf("\n如该条信息仍存在错误，请输入1，否则输入0\n");
		xinxsc(p);
		int i = -1;
		scanf_s("%d", &i);
		while (i != 1 && i != 0)
		{
			printf("请正确输入1或0 \n");
			scanf_s("%d", &i);
		}
		if (!i)
			break;
	}
}

void xinjkc()//新生成一项库存
{
	//rear = head;
	//while (rear->pnext != NULL)
	//{
	//	rear = rear->pnext;
	//}//找到链表尾，防止删除了最后一项之后，rear找不到队尾
	good* p;
	p = (good*)malloc(sizeof(good));
	if (p == NULL)
		exit(1);
	wchar_t  s[20], s2[20], s3[20], s4[20], s5[20], s6[20];
	InputBox(s, 20, L"请按顺序输入您要添加的商品种类名称: ", NULL, 0, 0, 0,true);
	while (*s == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s, 20, L"请按顺序输入您要添加的商品种类名称: ", NULL, 0, 0, 0, true);
	}
	 strcpy(p->mingc , wtoch(s));
	//printf("请按顺序输入您要添加的商品种类名称:\n");
	//scanf_s("%s", &(p->mingc), 20);
	        //定义系统时间结构体
	 GetLocalTime(&time);  //获取当前系统时间

	 //当前系统时间作为进货时间保存
	 p->jinhsj.ri = time.wDay;
	 p->jinhsj.yue = time.wMonth;
	 p->jinhsj.shi = time.wHour;

	/*InputBox(s2, 20, L"请您输入进货时间(格式：月/日/时):  ", NULL, 0, 0, 0, false);
	while (*s2 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s2, 20, L"请您输入进货时间(格式：月/日/时):  ", NULL, 0, 0, 0, false);
	}
	//printf("请您输入进货时间(格式：月/日/时):\n");
	//scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
	while ((p->jinhsj.ri) <= 0 || (p->jinhsj.yue) <= 0 || (p->jinhsj.shi) <= 0)//bug：如果填0时也会显示有误
	{
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"您输入的信息有误，请重新按格式(月/日/时)输入：", L"警告", MB_OK | MB_ICONWARNING);
		//printf("您输入的信息有误，请重新按格式(月/日/时)输入：\n");
		while (getchar() == '/');//用while循环吃掉上次输入残留的的‘/’
		scanf_s("%d/%d/%d", &(p->jinhsj.yue), &(p->jinhsj.ri), &(p->jinhsj.shi));
	}
	*/
	InputBox(s3, 20, L"请您输入进货量:  ", NULL, 0, 0, 0, true);
	while (*s3 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s3, 20, L"请您输入进货量：  ", NULL, 0, 0, 0, true);
	}

	//scanf_s("%f", &(p->kuc));
	while (_wtof(s3) < 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s3, 20, L"请您输入进货量： \n", NULL, 0, 0, 0, true);
		//scanf_s("%f", &p->kuc);
	}
	p->kuc = _wtof(s3);

	InputBox(s4, 20, L"请您输入进价: \n", NULL, 0, 0, 0, true);
	while (*s4 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s4, 20, L"请您输入进价: \n", NULL, 0, 0, 0, true);
	}
	while (_wtof(s4) < 0 )
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s4, 20, L"请您输入进价: \n", NULL, 0, 0, 0, true);
		//scanf_s("%f %f", &(p->jinj), &(p->shouj));
	}
	p->jinj=_wtof(s4);
	InputBox(s5, 20, L"请您输入售价:\n", NULL, 0, 0, 0, true);
	while (*s5 == NULL) {
		HWND wnd1 = GetHWnd();
		MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s5, 20, L"请您输入售价: \n", NULL, 0, 0, 0, true);
	}
	
	while (_wtof(s5) < p->jinj)
	{
		HWND wnd5 = GetHWnd();
		MessageBox(wnd5, L"售价不能小于进价！", L"警告", MB_OK | MB_ICONWARNING);
		InputBox(s5, 20, L"请您重新输入售价: \n", NULL, 0, 0, 0, true);
		//scanf_s("%f %f", &(p->jinj), &(p->shouj));
	}
	p->shouj=_wtof(s5);
	//printf("请您分别输入进价 售价:\n");
	//scanf_s("%f %f", &(p->jinj), &(p->shouj));     //草泥马
	/*
	while (p->jinj < 0 || p->shouj < 0)
	{
		HWND wnd = GetHWnd();
		MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
		scanf_s("%f %f", &(p->jinj), &(p->shouj));
	}
	*/
	//printf("请检查已录入信息是否存在错误\n"); 

	int kkk = -1;//   判断是否输入正确
	int j=check(kkk,s,s3,s4,s5,p);  

	//printf("\n如该条信息存在错误，请输入1，否则输入0\n");
	
	//scanf_s("%d", &j);
	/*
	
	while (j != 1 && j != 0)
	{
		printf("请正确输入1或0 \n");
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
	baockc();       //保存到文件中
	storagepage(); //返回库存管理页面
}



void shanc()//删除某项，注意当库存已经不存在时的情况
{
	if (head == NULL)
	{
		HWND wnd = GetHWnd();     //windows原生窗口
		MessageBox(wnd, L"提示", L"库存为空", MB_OK | MB_ICONINFORMATION);
		return;
	}
	int num, x;
	num = kucdb();
	printf("请输入您所需要删除的项目:\n");//可视化处理
	int j = 0;
	good* p = head;
	scanf_s("%d", &j);
	x = j;
	while (j > 1)
	{
		p = p->pnext;
		j--;
	}//找到对应的结构体
	good* pr = head;
	while (x > 2)
	{
		pr = pr->pnext;
		x--;
	}//找到对应的结构体
	printf("\n");
	printf("请问您确定要删除第%d信息吗？\n", j);
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
		HWND wnd = GetHWnd();     //windows原生窗口
		MessageBox(wnd, L"提示", L"删除成功", MB_OK | MB_ICONINFORMATION);
	}
	return;
}

void baockc()//保存库存，将库存信息储存在文件中
{
	good* p = head;
	fopen_s(&fp, "storagedata.txt", "w");
	if (fp == NULL)
	{
		HWND wnd = GetHWnd();     //windows原生窗口
		MessageBox(wnd, L"保存失败", L"警告", MB_OK | MB_ICONWARNING);
		return;
	}
	while (p != NULL)
	{
		fprintf(fp, "%s      %02d/%02d/%02d   %.2f   %.2f  %.2f    %.2f\n", p->mingc, p->jinhsj.yue, p->jinhsj.ri, p->jinhsj.shi, p->kuc, p->jinj, p->shouj, p->lir);//库存名称  日期（月日时） 库存量  售价 进价 当前利润
		p = p->pnext;
	}
	fclose(fp);
}

void shiflbkj(good* p)//释放链表空间
{
	while (p != NULL)
	{
		good* pf = p->pnext;
		free(p);
		p = pf;
	}
}

void chushkc()//初始化库存信息
{
	GetLocalTime(&time);
	HWND wnd = GetHWnd();
	fopen_s(&fp, "storagedata.txt", "r");
	if (fp == NULL)
	{
		fopen_s(&fp, "storagedata.txt", "w");
		if (fp == NULL)
		{
			
			MessageBox(wnd, L"创建文件失败", L"警告", MB_OK | MB_ICONWARNING);
			exit(0);
		}
		MessageBox(wnd, L"提示", L"初次使用", MB_OK | MB_ICONINFORMATION);
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
				MessageBox(wnd, L"程序初始化错误", L"警告", MB_OK | MB_ICONWARNING);
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
			//printf("%d",ftell(fp));测试是否到文件尾

		}
		fclose(fp);
	}
}

good* kuctzz()//传递库存头指针
{
	return head;
};

good* kucwzz()//传递尾指针
{
	return rear;
};

void jiescx()//结束程序，释放链表空间,请把这个函数放在退出程序时调用
{
	shiflbkj(head);
	shiflbkj2();
	shiflbkj3();
}

