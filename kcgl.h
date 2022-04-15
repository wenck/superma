#pragma once
//日期问题,调用系统时间(可选)
struct good;
struct date;
struct date
{
	int yue = 0;
	int ri = 0;
	int shi = 0;
};//日期信息结构体
struct good
{
	char mingc[20] = "null";
	date jinhsj;//进货时间
	float kuc = 0;//库存量
	float jinj = 0;//进价
	float shouj = 0;//售价
	float lir = 0;//利润
	good* pnext = 0;
};//库存结构体
void xinxsc(good* p);//信息输出
int kucdb();//库存打表

void xinjkc();//新生成一项库存
//void kucxg(good* p); //修改库存中指定某果蔬的某项信息（修改）
void shanc();//删除某项库存
void baockc();//保存库存，将库存信息储存在文件中
void shiflbkj(good* p);//释放链表空间
void chushkc();//初始化库存信息
void jiescx();//结束程序，释放链表空间,请把这个函数放在退出程序时调用
good* kuctzz();//传递库存头指针
good* kucwzz();//传递库存尾指针
void kucxg1(good* p); //修改库存中指定一项
void kucxg2();//修改库存中任意一项
void kucjh();//库存进货

#define k 6;//每页中信息的条数
good* function(int n);//名字没想好,返回值为打表时对应页码的第一个商品，n为对应页码