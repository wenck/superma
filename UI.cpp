#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <graphics.h> 	             // 引用图形库头文件
#include <conio.h>
#include <stdio.h>
#include "kcgl.h"
#include "gkgm.h"
#include "UIpage.h"
#include <comdef.h> 

int r1[4][4] = { {230,445,560,490},{230,505,560,550},{230,565,560,610},{230,625,560,670} };
//首页四个按钮的二维数组

int button_judge(int x, int y)                 //判断按钮的位置函数
{
    if (x > r1[0][0] && x<r1[0][2] && y>r1[0][1] && y < r1[0][3])return 1;
    if (x > r1[1][0] && x<r1[1][2] && y>r1[1][1] && y < r1[1][3])return 2;
    if (x > r1[2][0] && x<r1[2][2] && y>r1[2][1] && y < r1[2][3])return 3;
    if (x > r1[3][0] && x<r1[3][2] && y>r1[3][1] && y < r1[3][3])return 4;
    return 0;
}

void frontpage() {      //首页
    
    int i, event=0;
    initgraph(760, 760);       //窗口大小

    for (i = 0; i < 256; i += 5)
    {
        setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
        cleardevice();//清屏（取决于背景色）
        //Sleep(10);//延时10ms
    }
    
	//创建四个按钮的指针
    RECT R1 = { r1[0][0],r1[0][1],r1[0][2],r1[0][3] };
    RECT R2 = { r1[1][0],r1[1][1],r1[1][2],r1[1][3] };
    RECT R3 = { r1[2][0],r1[2][1],r1[2][2],r1[2][3] };
    RECT R4 = { r1[3][0],r1[3][1],r1[3][2],r1[3][3] };
    
    LOGFONT f;
    gettextstyle(&f);					//获取字体样式
    wcscpy_s(f.lfFaceName, _T("宋体"));
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
    settextstyle(&f);                     // 设置字体样式
    settextcolor(BLACK);

	//为按钮填充内容
    drawtext(_T("库存"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T("售货"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T("会员"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T("退出"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    setlinecolor(BLACK);

	//画四个空心矩形作为按钮
    rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
    rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);
    rectangle(r1[2][0], r1[2][1], r1[2][2], r1[2][3]);
    rectangle(r1[3][0], r1[3][1], r1[3][2], r1[3][3]);
    
	//大标题
    wchar_t FirstTitle[] = L"大 脚 超 市";
    settextstyle(70, 0, _T("黑体"));
    outtextxy(200, 100, FirstTitle);
	
	ExMessage m;//鼠标指针

	
	//chushjr();

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
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r1[event - 1][0], r1[event - 1][1], r1[event - 1][2], r1[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r1[event - 1][0], r1[event - 1][1], r1[event - 1][2], r1[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
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

			switch (button_judge(m.x, m.y))
			{
				//复原按钮原型
			case 1:
				cleardevice();
				storagepage();
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 2:
				cleardevice();
				sellingpage();
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 3:
				cleardevice();
				vippage();
				flushmessage();//单击事件后清空鼠标消息
			case 4:
				closegraph();//关闭绘图环境
				baockc();
				exit(0);//正常退出
				break;
			default:
				flushmessage();//单击事件后清空鼠标消息
				break;
			}
			break;
			flushmessage();//清空鼠标消息缓存区
		}
	}
}

int r2[4][4] = { {100,200,400,230},{100,260,400,290},{100,320,400,350},{100,380,400,410} };
//库存四个按钮的二维数组

int button_judge2(int x, int y)                 //判断按钮的位置函数
{
	if (x > r2[0][0] && x<r2[0][2] && y>r2[0][1] && y < r2[0][3])return 1;
	if (x > r2[1][0] && x<r2[1][2] && y>r2[1][1] && y < r2[1][3])return 2;
	if (x > r2[2][0] && x<r2[2][2] && y>r2[2][1] && y < r2[2][3])return 3;
	if (x > r2[3][0] && x<r2[3][2] && y>r2[3][1] && y < r2[3][3])return 4;
	if (x > 10 && x<70&& y>10&& y < 55)return 5;
	return 0;
}
void storagepage() {

	cleardevice();
    FlushMouseMsgBuffer();
    int i, event = 0;
    initgraph(500, 430);       //窗口大小

    for (i = 0; i < 256; i += 5)
    {
        setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
        cleardevice();//清屏（取决于背景色）
        //Sleep(15);//延时15ms
    }

    //创建四个按钮的指针
    RECT R1 = { r2[0][0],r2[0][1],r2[0][2],r2[0][3] };
    RECT R2 = { r2[1][0],r2[1][1],r2[1][2],r2[1][3] };
    RECT R3 = { r2[2][0],r2[2][1],r2[2][2],r2[2][3] };
    RECT R4 = { r2[3][0],r2[3][1],r2[3][2],r2[3][3] };
    
    LOGFONT f;
    gettextstyle(&f);					//获取字体样式
    wcscpy_s(f.lfFaceName, _T("宋体"));
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
    settextstyle(&f);                     // 设置字体样式
    settextcolor(BLACK);

    //为按钮填充内容
    drawtext(_T("新建库存"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T("修改库存"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T("删除库存"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    drawtext(_T("库存打表"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    setlinecolor(BLACK);

    //画四个空心矩形作为按钮
    rectangle(r2[0][0], r2[0][1], r2[0][2], r2[0][3]);
    rectangle(r2[1][0], r2[1][1], r2[1][2], r2[1][3]);
    rectangle(r2[2][0], r2[2][1], r2[2][2], r2[2][3]);
    rectangle(r2[3][0], r2[3][1], r2[3][2], r2[3][3]);

    //大标题
    wchar_t FirstTitle[] = L"库存管理";
    settextstyle(55, 0, _T("黑体"));
    outtextxy(130, 50, FirstTitle);
    // cleardevice();
    ExMessage m;   //鼠标指针
    fillrectangle(10, 10, 70, 55);
    setbkmode(OPAQUE);
    settextstyle(20, 0, L"黑体");
    outtextxy(20, 20, L"返回");
	
	while (true)
	{
		m = getmessage();//获取一条鼠标消息

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(BLUE);//填充颜色为白色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r2[event - 1][0], r2[event - 1][1], r2[event - 1][2], r2[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r2[event - 1][0], r2[event - 1][1], r2[event - 1][2], r2[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				//Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}

			switch (button_judge2(m.x, m.y))
			{
				//复原按钮原型
			case 1:                                      //新建库存操作的界面交互
				xinjkc();
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 2:
				cleardevice();
				storagemodify();
				//kucxg2();
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 3:
				cleardevice();
				vippage();
				flushmessage();//单击事件后清空鼠标消息
			case 4:
				cleardevice();;//关闭绘图环境
				exit(0);//正常退出
				break;
			case 5:
				frontpage();                      //回到主菜单
				flushmessage();//单击事件后清空鼠标消息
				break;
			default:
				flushmessage();//单击事件后清空鼠标消息
				break;
			}
			break;
			flushmessage();//清空鼠标消息缓存区
		}
	}
   
}


void sellingpage() {

	cleardevice();
	flushmessage();
	int i, event = 0;
	initgraph(500, 430);       //窗口大小

	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
		cleardevice();//清屏（取决于背景色）
		//Sleep(15);//延时15ms
	}

	//创建四个按钮的指针
	RECT R1 = { r2[0][0],r2[0][1],r2[0][2],r2[0][3] };
	RECT R2 = { r2[1][0],r2[1][1],r2[1][2],r2[1][3] };
	RECT R3 = { r2[2][0],r2[2][1],r2[2][2],r2[2][3] };
	RECT R4 = { r2[3][0],r2[3][1],r2[3][2],r2[3][3] };

	LOGFONT f;
	gettextstyle(&f);					//获取字体样式
	wcscpy_s(f.lfFaceName, _T("宋体"));
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);

	//为按钮填充内容
	drawtext(_T("新建库存"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改库存"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("删除库存"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("库存打表"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setlinecolor(BLACK);

	//画四个空心矩形作为按钮
	rectangle(r2[0][0], r2[0][1], r2[0][2], r2[0][3]);
	rectangle(r2[1][0], r2[1][1], r2[1][2], r2[1][3]);
	rectangle(r2[2][0], r2[2][1], r2[2][2], r2[2][3]);
	rectangle(r2[3][0], r2[3][1], r2[3][2], r2[3][3]);

	//大标题
	wchar_t FirstTitle[] = L"售货系统";
	settextstyle(55, 0, _T("黑体"));
	outtextxy(130, 50, FirstTitle);
	// cleardevice();
	ExMessage m;   //鼠标指针
	fillrectangle(10, 10, 70, 55);
	setbkmode(OPAQUE);
	settextstyle(20, 0, L"黑体");
	outtextxy(20, 20, L"返回");
	while (true)
	{
		m = getmessage();//获取一条鼠标消息

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(BLUE);//填充颜色为蓝色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r2[event - 1][0], r2[event - 1][1], r2[event - 1][2], r2[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r2[event - 1][0], r2[event - 1][1], r2[event - 1][2], r2[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				//Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}

			switch (button_judge2(m.x, m.y))
			{
				//复原按钮原型
			case 1:                                      //新建库存操作的界面交互
				xinjkc();
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 2:
				cleardevice();
				sellingpage();
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 3:
				cleardevice();
				vippage();
				flushmessage();//单击事件后清空鼠标消息
			case 4:
				cleardevice();;//关闭绘图环境
				exit(0);//正常退出
				break;
			case 5:
				frontpage();                      //回到主菜单
				flushmessage();//单击事件后清空鼠标消息
				break;
			default:
				flushmessage();//单击事件后清空鼠标消息
				break;
			}
			break;
			flushmessage();//清空鼠标消息缓存区
		}
	}

}

void vippage() {

	cleardevice();
	flushmessage();
	int i, event = 0;
	initgraph(500, 430);       //窗口大小

	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));//设置背景色，原来默认黑色
		cleardevice();//清屏（取决于背景色）
		//Sleep(15);//延时15ms
	}

	//创建四个按钮的指针
	RECT R1 = { r2[0][0],r2[0][1],r2[0][2],r2[0][3] };
	RECT R2 = { r2[1][0],r2[1][1],r2[1][2],r2[1][3] };
	RECT R3 = { r2[2][0],r2[2][1],r2[2][2],r2[2][3] };
	RECT R4 = { r2[3][0],r2[3][1],r2[3][2],r2[3][3] };

	LOGFONT f;
	gettextstyle(&f);					//获取字体样式
	wcscpy_s(f.lfFaceName, _T("宋体"));
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);

	//为按钮填充内容
	drawtext(_T("新建会员"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("会员信息汇总"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//drawtext(_T("删除库存"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	//drawtext(_T("库存打表"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setlinecolor(BLACK);

	//画二个空心矩形作为按钮
	rectangle(r2[0][0], r2[0][1], r2[0][2], r2[0][3]);
	rectangle(r2[1][0], r2[1][1], r2[1][2], r2[1][3]);
	//rectangle(r2[2][0], r2[2][1], r2[2][2], r2[2][3]);
	//rectangle(r2[3][0], r2[3][1], r2[3][2], r2[3][3]);

	//大标题
	wchar_t FirstTitle[] = L"会员管理";
	settextstyle(55, 0, _T("黑体"));
	outtextxy(130, 50, FirstTitle);
	// cleardevice();
	ExMessage m;   //鼠标指针
	fillrectangle(10, 10, 70, 50);
	setbkmode(OPAQUE);
	settextstyle(20, 0, L"黑体");
	outtextxy(20, 20, L"返回");
	while (true)
	{
		m = getmessage();//获取一条鼠标消息

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(BLUE);//填充颜色为蓝色
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);//记录这一次触发的按钮
					fillrectangle(r2[event - 1][0], r2[event - 1][1], r2[event - 1][2], r2[event - 1][3]);//有框填充矩形（X1,Y1,X2,Y2）
				}
			}
			else
			{
				if (event != 0)//上次触发的按钮未被修正为原来的颜色
				{
					fillrectangle(r2[event - 1][0], r2[event - 1][1], r2[event - 1][2], r2[event - 1][3]);//两次同或为原来颜色
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				//Sleep(30);//停顿30ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}

			switch (button_judge2(m.x, m.y))
			{
				//复原按钮原型
			case 1:                                      //新建库存操作的界面交互
				tianjhy();
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 2:
				cleardevice();
				sellingpage();
				flushmessage();//单击事件后清空鼠标消息
				break;
			case 3:
				cleardevice();
				vippage();
				flushmessage();//单击事件后清空鼠标消息
			case 4:
				cleardevice();;//关闭绘图环境
				exit(0);//正常退出
				break;
			case 5:
				frontpage();                      //回到主菜单
				flushmessage();//单击事件后清空鼠标消息
				break;
			default:
				flushmessage();//单击事件后清空鼠标消息
				break;
			}
			break;
			flushmessage();//清空鼠标消息缓存区
		}
	}

}

int check(int x , wchar_t* a, wchar_t* b,wchar_t* c,wchar_t* d,good *p)

{
	int i;
	initgraph(500, 370);

	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(WHITE);
		cleardevice();//清屏（取决于背景色）
		//Sleep(3);//延时15ms
	}
	// 设置颜色

	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	wcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(RED);
	outtextxy(100, 20, L"请检查已录入信息是否存在错误：   ");

	//字体样式 

	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_LIGHT;
	settextstyle(&f);
	settextcolor(BLACK);

	//输出待检查项目及对应值
	outtextxy(80, 70, L"1. 名称:      ");
	outtextxy(80, 120, L"2. 库存量：");
	outtextxy(80, 170, L"3. 进价：   ");
	outtextxy(80, 220, L"4. 售价：   ");

	outtextxy(180, 70, a);
	outtextxy(180, 120, b);
	outtextxy(180, 170, c);
	outtextxy(180, 220,d);

	//创建两个按钮
	int r1[][4] = { {140,280,300,320}, {300,60,400,90} ,{300,110,400,140},{300,160,400,190},{300,210,400,240} };

	RECT R1 = { r1[0][0],r1[0][1],r1[0][2],r1[0][3] };
	RECT R2 = { r1[1][0],r1[1][1],r1[1][2],r1[1][3] };
	RECT R3 = { r1[2][0],r1[2][1],r1[2][2],r1[2][3] };
	RECT R4 = { r1[3][0],r1[3][1],r1[3][2],r1[3][3] };
	RECT R5 = { r1[4][0],r1[4][1],r1[4][2],r1[4][3] };



	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);

	drawtext(_T("修改"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("保存"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2, 0, 0);

	rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
	rectangle(r1[2][0], r1[2][1], r1[2][2], r1[2][3]);
	rectangle(r1[3][0], r1[3][1], r1[3][2], r1[3][3]);
	rectangle(r1[4][0], r1[4][1], r1[4][2], r1[4][3]);
	rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);



	ExMessage m;   //鼠标指针
	int event = 0;
	while (true)
	{
		m = getmessage();//获取一条鼠标消息

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(BLUE);//填充颜色为白色
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿3ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			if (m.x >= r1[0][0] && m.y >= r1[0][1] && m.x <= r1[0][2] && m.y <= r1[0][3])
			{
				setlinecolor(RED);
				rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					HWND wnd2 = GetHWnd();     //windows原生窗口
					MessageBox(wnd2, L"已成功加入库存", L"提示", MB_OK | MB_ICONINFORMATION);
					//storagepage();
					return 0; //调用库存修改函数,更改那个值//调用库存修改函数,更改那个值
				}
			}
			else if (m.x >= r1[1][0] && m.y >= r1[1][1] && m.x <= r1[1][2] && m.y <= r1[1][3])
			{
				setlinecolor(RED);
				rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);
				outtextxy(180, 70, L"         ");
				if (m.message == WM_LBUTTONDOWN)
				{
					InputBox(a, 20, L"请按顺序输入您要添加的商品种类名称: ", NULL, 0, 0, 0, true);
					while (*a == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(a, 20, L"请按顺序输入您要添加的商品种类名称: ", NULL, 0, 0, 0, true);
					}
					
					outtextxy(180, 70, a);
					strcpy(p->mingc, wtoch(a));
				}
			}
			else if (m.x >= r1[2][0] && m.y >= r1[2][1] && m.x <= r1[2][2] && m.y <= r1[2][3])
			{
				setlinecolor(RED);
				rectangle(r1[2][0], r1[2][1], r1[2][2], r1[2][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 120, L"         ");
					InputBox(b, 20, L"请您重新输入进货量:  ", NULL, 0, 0, 0, true);
					while (*b == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(b, 20, L"请您重新输入进货量：  ", NULL, 0, 0, 0, true);
					}

					//scanf_s("%f", &(p->kuc));
					while (_wtof(b) < 0)
					{
						HWND wnd = GetHWnd();
						MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(b, 20, L"请您重新输入进货量： \n", NULL, 0, 0, 0, true);
						//scanf_s("%f", &p->kuc);
					}
					outtextxy(180, 120, b);
					p->kuc = _wtof(b);
				}
			}
			else if (m.x >= r1[3][0] && m.y >= r1[3][1] && m.x <= r1[3][2] && m.y <= r1[3][3])
			{
				setlinecolor(RED);
				rectangle(r1[3][0], r1[3][1], r1[3][2], r1[3][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 170, L"         ");
					InputBox(c, 20, L"请您重新输入进价: \n", NULL, 0, 0, 0, true);
					while (*c == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(c, 20, L"请您重新输入进价: \n", NULL, 0, 0, 0, true);
					}
					while (_wtof(c) < 0)
					{
						HWND wnd = GetHWnd();
						MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(c, 20, L"请您输入进价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					while (_wtof(c) > p->shouj)
					{
						HWND wnd5 = GetHWnd();
						MessageBox(wnd5, L"售价不能小于进价！", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(c, 20, L"请您重新输入售价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					outtextxy(180, 170, c);
					p->jinj = _wtof(c);
					//调用库存修改函数,更改那个值
				}
			}
			else if (m.x >= r1[4][0] && m.y >= r1[4][1] && m.x <= r1[4][2] && m.y <= r1[4][3])
			{
				setlinecolor(RED);
				rectangle(r1[4][0], r1[4][1], r1[4][2], r1[4][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 220, L"         ");
					InputBox(d, 20, L"请您输入售价:\n", NULL, 0, 0, 0, true);
					while (*d == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(d, 20, L"请您输入售价: \n", NULL, 0, 0, 0, true);
					}

					while (_wtof(d) < p->jinj)
					{
						HWND wnd5 = GetHWnd();
						MessageBox(wnd5, L"售价不能小于进价！", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(d, 20, L"请您重新输入售价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					p->shouj = _wtof(d);
					outtextxy(180, 220, d);
					//调用库存修改函数,更改那个值
				}
			}
			break;

			flushmessage();//清空鼠标消息缓存区
		}
	}


	system("pause");//显示界面

	return 0;

}
/*
 {
	int i;
	initgraph(500, 430);

	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(WHITE);
		cleardevice();//清屏（取决于背景色）
		//Sleep(3);//延时15ms
	}
	// 设置颜色

	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	wcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(RED);
	outtextxy(100, 20, L"请检查已录入信息是否存在错误：   ");

	//字体样式 

	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_LIGHT;
	settextstyle(&f);
	settextcolor(BLACK);

	//输出待检查项目及对应值
	outtextxy(80, 70, L"1. 名称:      ");
	outtextxy(80, 120, L"2. 库存量：");
	outtextxy(80, 170, L"3. 进价：   ");
	outtextxy(80, 220, L"4. 售价：   ");

	outtextxy(180, 70, a);
	outtextxy(180, 120, b);
	outtextxy(180, 170, c);
	outtextxy(180, 220, d);

	//创建两个按钮
	int r1[2][4] = { {140,280,300,320},{140,350,300,390} };

	RECT R1 = { r1[0][0],r1[0][1],r1[0][2],r1[0][3] };
	RECT R2 = { r1[1][0],r1[1][1],r1[1][2],r1[1][3] };

	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);

	drawtext(_T("修改"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("保存"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2, 0, 0);

	rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
	rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);

	ExMessage m;   //鼠标指针
	int event = 0;
	while (true)
	{
		m = getmessage();//获取一条鼠标消息

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(BLUE);//填充颜色为白色
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
			if (m.x >= r1[0][0] && m.y >= r1[0][1] && m.x <= r1[0][2] && m.y <= r1[0][3])
			{
				setlinecolor(RED);
				rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
				if (m.message == WM_LBUTTONDOWN)
				{

					return 1; //调用库存修改函数,更改那个值
				}
			}
			else if (m.x >= r1[1][0] && m.y >= r1[1][1] && m.x <= r1[1][2] && m.y <= r1[1][3])
			{
				setlinecolor(RED);
				rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					HWND wnd2 = GetHWnd();     //windows原生窗口
					MessageBox(wnd2, L"已成功加入库存", L"提示", MB_OK | MB_ICONINFORMATION);
					//storagepage();
					return 0;//调用库存修改函数,更改那个值
				}
			}
			break;



			flushmessage(-1);//清空鼠标消息缓存区
		}
	}







	system("pause");

	return 0;

}*/
void check1(good* p)

{
	int i;
	initgraph(500, 370);

	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(WHITE);
		cleardevice();//清屏（取决于背景色）
		//Sleep(3);//延时15ms
	}
	// 设置颜色

	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	wcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(RED);
	outtextxy(100, 20, L"请检查已录入信息是否存在错误：   ");

	//字体样式 

	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_LIGHT;
	settextstyle(&f);
	settextcolor(BLACK);

	//输出待检查项目及对应值
	outtextxy(80, 70, L"1. 名称:      ");
	outtextxy(80, 120, L"2. 库存量：");
	outtextxy(80, 170, L"3. 进价：   ");
	outtextxy(80, 220, L"4. 售价：   ");

	TCHAR s[] = _T("helloworld");
	TCHAR s1[] = _T("jinhsj.ri");
	TCHAR s2[] = _T("jinhsj.shi");
	TCHAR s3[] = _T("jinhsj.shi");
	TCHAR s4[] = _T("jinhsj.shi");
	TCHAR s5[] = _T("jinhsj.shi");

		
	
	_stprintf(s2, _T("%d"), p->jinhsj.shi);
	_stprintf(s3, _T("%.2lf"), p->kuc);
	_stprintf(s4, _T("%.2lf"), p->jinj);
	_stprintf(s5, _T("%.2lf"), p->shouj);

	outtextxy(180, 70,chtow(p->mingc) );
	outtextxy(180, 120, s3);
	outtextxy(180, 170, s4);
	outtextxy(180, 220, s5);

	//创建两个按钮
	int r1[][4] = { {140,280,300,320}, {300,60,400,90} ,{300,110,400,140},{300,160,400,190},{300,210,400,240} };

	RECT R1 = { r1[0][0],r1[0][1],r1[0][2],r1[0][3] };
	RECT R2 = { r1[1][0],r1[1][1],r1[1][2],r1[1][3] };
	RECT R3 = { r1[2][0],r1[2][1],r1[2][2],r1[2][3] };
	RECT R4 = { r1[3][0],r1[3][1],r1[3][2],r1[3][3] };
	RECT R5 = { r1[4][0],r1[4][1],r1[4][2],r1[4][3] };



	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);

	drawtext(_T("修改"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("保存"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2, 0, 0);

	rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
	rectangle(r1[2][0], r1[2][1], r1[2][2], r1[2][3]);
	rectangle(r1[3][0], r1[3][1], r1[3][2], r1[3][3]);
	rectangle(r1[4][0], r1[4][1], r1[4][2], r1[4][3]);
	rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);



	ExMessage m;   //鼠标指针
	int event = 0;
	while (true)
	{
		m = getmessage();//获取一条鼠标消息

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(BLUE);//填充颜色为白色
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿3ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			if (m.x >= r1[0][0] && m.y >= r1[0][1] && m.x <= r1[0][2] && m.y <= r1[0][3])
			{
				setlinecolor(RED);
				rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					HWND wnd2 = GetHWnd();     //windows原生窗口
					MessageBox(wnd2, L"已成功加入库存", L"提示", MB_OK | MB_ICONINFORMATION);
					storagepage();
					//调用库存修改函数,更改那个值//调用库存修改函数,更改那个值
				}
			}
			else if (m.x >= r1[1][0] && m.y >= r1[1][1] && m.x <= r1[1][2] && m.y <= r1[1][3])
			{
				setlinecolor(RED);
				rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);
				outtextxy(180, 70, L"         ");
				if (m.message == WM_LBUTTONDOWN)
				{
					InputBox(s, 20, L"请按顺序输入您要添加的商品名称: ", NULL, 0, 0, 0, true);
					while (*s == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(s, 20, L"请按顺序输入您要添加的商品名称: ", NULL, 0, 0, 0, true);
					}

					outtextxy(180, 70, s);
					strcpy(p->mingc, wtoch(s));
				}
			}
			else if (m.x >= r1[2][0] && m.y >= r1[2][1] && m.x <= r1[2][2] && m.y <= r1[2][3])
			{
				setlinecolor(RED);
				rectangle(r1[2][0], r1[2][1], r1[2][2], r1[2][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 120, L"         ");
					InputBox(s1, 20, L"请您重新输入进货量:  ", NULL, 0, 0, 0, true);
					while (*s1 == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(s1, 20, L"请您重新输入进货量：  ", NULL, 0, 0, 0, true);
					}

					//scanf_s("%f", &(p->kuc));
					while (_wtof(s2) < 0)
					{
						HWND wnd = GetHWnd();
						MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(s2, 20, L"请您重新输入进货量： \n", NULL, 0, 0, 0, true);
						//scanf_s("%f", &p->kuc);
					}
					outtextxy(180, 120, s2);
					p->kuc = _wtof(s2);
				}
			}
			else if (m.x >= r1[3][0] && m.y >= r1[3][1] && m.x <= r1[3][2] && m.y <= r1[3][3])
			{
				setlinecolor(RED);
				rectangle(r1[3][0], r1[3][1], r1[3][2], r1[3][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 170, L"         ");
					InputBox(s3, 20, L"请您重新输入进价: \n", NULL, 0, 0, 0, true);
					while (*s3 == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(s3, 20, L"请您重新输入进价: \n", NULL, 0, 0, 0, true);
					}
					while (_wtof(s3) < 0)
					{
						HWND wnd = GetHWnd();
						MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(s3, 20, L"请您输入进价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					while (_wtof(s3) > p->shouj)
					{
						HWND wnd5 = GetHWnd();
						MessageBox(wnd5, L"售价不能小于进价！", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(s3, 20, L"请您重新输入售价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					outtextxy(180, 170, s3);
					p->jinj = _wtof(s3);
					//调用库存修改函数,更改那个值
				}
			}
			else if (m.x >= r1[4][0] && m.y >= r1[4][1] && m.x <= r1[4][2] && m.y <= r1[4][3])
			{
				setlinecolor(RED);
				rectangle(r1[4][0], r1[4][1], r1[4][2], r1[4][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 220, L"         ");
					InputBox(s4, 20, L"请您输入售价:\n", NULL, 0, 0, 0, true);
					while (*s4 == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(s4, 20, L"请您输入售价: \n", NULL, 0, 0, 0, true);
					}

					while (_wtof(s4) < p->jinj)
					{
						HWND wnd5 = GetHWnd();
						MessageBox(wnd5, L"售价不能小于进价！", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(s4, 20, L"请您重新输入售价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					p->shouj = _wtof(s4);
					outtextxy(180, 220, s4);
					//调用库存修改函数,更改那个值
				}
			}
			break;

			flushmessage();//清空鼠标消息缓存区
		}
	}


	system("pause");//显示界面

	

}
void messageoutput(good* tmpp) {

}

void storagemodify()
{
	int i;
	initgraph(720, 600);

	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(WHITE);
		cleardevice();//清屏（取决于背景色）
		//Sleep(3);//延时15ms
	}
	// 设置颜色

	LOGFONT f;//字体样式指针
	gettextstyle(&f);					//获取字体样式
	wcscpy_s(f.lfFaceName, _T("宋体"));	//设置字体为宋体
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(RED);
	outtextxy(300, 20, L"库存打表检查   ");

	//字体样式 

	/*f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_LIGHT;
	settextstyle(&f);*/
	settextcolor(BLACK);

	//输出待检查项目及对应值
	outtextxy(8, 80, L"序号");
	outtextxy(65,80, L"名称");
	outtextxy(140, 80, L"进货时间 (月/日/时)");
	outtextxy(330, 80, L" 库存量");
	outtextxy(430, 80, L"进价");
	outtextxy(500, 80, L"零售价");


	//创建两个按钮
	int r1[][4] = { {500,500,570,550} ,{600,110,700,140},{600,160,700,190},{600,210,700,240}, {600,260,700,290}, {600,310,700,340},{600,360,700,390},{600,410,700,440} };

	RECT R1 = { r1[0][0],r1[0][1],r1[0][2],r1[0][3] };
	RECT R2 = { r1[1][0],r1[1][1],r1[1][2],r1[1][3] };
	RECT R3 = { r1[2][0],r1[2][1],r1[2][2],r1[2][3] };
	RECT R4 = { r1[3][0],r1[3][1],r1[3][2],r1[3][3] };
	RECT R5 = { r1[4][0],r1[4][1],r1[4][2],r1[4][3] };
	RECT R6 = { r1[5][0],r1[5][1],r1[5][2],r1[5][3] };
	RECT R7 = { r1[6][0],r1[6][1],r1[6][2],r1[6][3] };

	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_BOLD;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(BLACK);

	//drawtext(_T("下一页"), &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	/*drawtext(_T("修改"), &R4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(_T("修改"), &R7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2, 0, 0);

	rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
	rectangle(r1[2][0], r1[2][1], r1[2][2], r1[2][3]);
	rectangle(r1[3][0], r1[3][1], r1[3][2], r1[3][3]);
	rectangle(r1[4][0], r1[4][1], r1[4][2], r1[4][3]);
	rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);
	rectangle(r1[5][0], r1[5][1], r1[5][2], r1[5][3]);
	rectangle(r1[6][0], r1[6][1], r1[6][2], r1[6][3]);*/
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2, 0, 0);
	rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
	kucxg2();
	
	ExMessage m;   //鼠标指针
	int event = 0;
	while (true) {}/*

	{
		m = getmessage();//获取一条鼠标消息

		switch (m.message)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);//线条颜色为亮青色
			setlinestyle(PS_SOLID, 3);//设置画线样式为实现，10磅
			setfillcolor(BLUE);//填充颜色为白色
			break;
		case WM_LBUTTONDOWN:
			setrop2(R2_NOTXORPEN);//二元光栅——NOT(屏幕颜色 XOR 当前颜色)
			for (i = 0; i <= 10; i++)
			{
				setlinecolor(RGB(25 * i, 25 * i, 25 * i));//设置圆颜色
				circle(m.x, m.y, 2 * i);
				Sleep(30);//停顿3ms
				circle(m.x, m.y, 2 * i);//抹去刚刚画的圆
			}
			if (m.x >= r1[0][0] && m.y >= r1[0][1] && m.x <= r1[0][2] && m.y <= r1[0][3])
			{
				setlinecolor(RED);
				rectangle(r1[0][0], r1[0][1], r1[0][2], r1[0][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					HWND wnd2 = GetHWnd();     //windows原生窗口
					MessageBox(wnd2, L"已成功加入库存", L"提示", MB_OK | MB_ICONINFORMATION);
					//storagepage();
					 //调用库存修改函数,更改那个值//调用库存修改函数,更改那个值
				}
			}
			else if (m.x >= r1[1][0] && m.y >= r1[1][1] && m.x <= r1[1][2] && m.y <= r1[1][3])
			{
				setlinecolor(RED);
				rectangle(r1[1][0], r1[1][1], r1[1][2], r1[1][3]);
				outtextxy(180, 70, L"         ");
				if (m.message == WM_LBUTTONDOWN)
				{
					InputBox(a, 20, L"请按顺序输入您要添加的商品种类名称: ", NULL, 0, 0, 0, true);
					while (*a == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(a, 20, L"请按顺序输入您要添加的商品种类名称: ", NULL, 0, 0, 0, true);
					}

					outtextxy(180, 70, a);
					strcpy(p->mingc, wtoch(a));
				}
			}
			else if (m.x >= r1[2][0] && m.y >= r1[2][1] && m.x <= r1[2][2] && m.y <= r1[2][3])
			{
				setlinecolor(RED);
				rectangle(r1[2][0], r1[2][1], r1[2][2], r1[2][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 120, L"         ");
					InputBox(b, 20, L"请您重新输入进货量:  ", NULL, 0, 0, 0, true);
					while (*b == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(b, 20, L"请您重新输入进货量：  ", NULL, 0, 0, 0, true);
					}

					//scanf_s("%f", &(p->kuc));
					while (_wtof(b) < 0)
					{
						HWND wnd = GetHWnd();
						MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(b, 20, L"请您重新输入进货量： \n", NULL, 0, 0, 0, true);
						//scanf_s("%f", &p->kuc);
					}
					outtextxy(180, 120, b);
					p->kuc = _wtof(b);
				}
			}
			else if (m.x >= r1[3][0] && m.y >= r1[3][1] && m.x <= r1[3][2] && m.y <= r1[3][3])
			{
				setlinecolor(RED);
				rectangle(r1[3][0], r1[3][1], r1[3][2], r1[3][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 170, L"         ");
					InputBox(c, 20, L"请您重新输入进价: \n", NULL, 0, 0, 0, true);
					while (*c == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(c, 20, L"请您重新输入进价: \n", NULL, 0, 0, 0, true);
					}
					while (_wtof(c) < 0)
					{
						HWND wnd = GetHWnd();
						MessageBox(wnd, L"您输入的信息有误", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(c, 20, L"请您输入进价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					while (_wtof(c) > p->shouj)
					{
						HWND wnd5 = GetHWnd();
						MessageBox(wnd5, L"售价不能小于进价！", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(c, 20, L"请您重新输入售价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					outtextxy(180, 170, c);
					p->jinj = _wtof(c);
					//调用库存修改函数,更改那个值
				}
			}
			else if (m.x >= r1[4][0] && m.y >= r1[4][1] && m.x <= r1[4][2] && m.y <= r1[4][3])
			{
				setlinecolor(RED);
				rectangle(r1[4][0], r1[4][1], r1[4][2], r1[4][3]);
				if (m.message == WM_LBUTTONDOWN)
				{
					outtextxy(180, 220, L"         ");
					InputBox(d, 20, L"请您输入售价:\n", NULL, 0, 0, 0, true);
					while (*d == NULL) {
						HWND wnd1 = GetHWnd();
						MessageBox(wnd1, L"请勿输入空白信息", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(d, 20, L"请您输入售价: \n", NULL, 0, 0, 0, true);
					}

					while (_wtof(d) < p->jinj)
					{
						HWND wnd5 = GetHWnd();
						MessageBox(wnd5, L"售价不能小于进价！", L"警告", MB_OK | MB_ICONWARNING);
						InputBox(d, 20, L"请您重新输入售价: \n", NULL, 0, 0, 0, true);
						//scanf_s("%f %f", &(p->jinj), &(p->shouj));
					}
					p->shouj = _wtof(d);
					outtextxy(180, 220, d);
					//调用库存修改函数,更改那个值
				}
			}
			break;

			flushmessage();//清空鼠标消息缓存区
		}
	}
	*/

	system("pause");//显示界面


}


int main() {
	chushkc();
	chushjr();
	chushhy();
    frontpage();	
    return 0;
}