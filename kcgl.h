#pragma once
//��������,����ϵͳʱ��(��ѡ)
struct good;
struct date;
struct date
{
	int yue = 0;
	int ri = 0;
	int shi = 0;
};//������Ϣ�ṹ��
struct good
{
	char mingc[20] = "null";
	date jinhsj;//����ʱ��
	float kuc = 0;//�����
	float jinj = 0;//����
	float shouj = 0;//�ۼ�
	float lir = 0;//����
	good* pnext = 0;
};//���ṹ��
void xinxsc(good* p);//��Ϣ���
int kucdb();//�����

void xinjkc();//������һ����
//void kucxg(good* p); //�޸Ŀ����ָ��ĳ���ߵ�ĳ����Ϣ���޸ģ�
void shanc();//ɾ��ĳ����
void baockc();//�����棬�������Ϣ�������ļ���
void shiflbkj(good* p);//�ͷ�����ռ�
void chushkc();//��ʼ�������Ϣ
void jiescx();//���������ͷ�����ռ�,���������������˳�����ʱ����
good* kuctzz();//���ݿ��ͷָ��
good* kucwzz();//���ݿ��βָ��
void kucxg1(good* p); //�޸Ŀ����ָ��һ��
void kucxg2();//�޸Ŀ��������һ��
void kucjh();//������

#define k 6;//ÿҳ����Ϣ������
good* function(int n);//����û���,����ֵΪ���ʱ��Ӧҳ��ĵ�һ����Ʒ��nΪ��Ӧҳ��