#pragma once
//char*转换wchar_t*
wchar_t* chtow(const char* szStr);

//wchar_t*转换char*
char* wtoch(const wchar_t* szStr);

void frontpage();
void storagepage();
void sellingpage();
void vippage();
void storagemodify();
void kucdb1(good* p ,int n,int sum);//库存打表UI
int check(int x, wchar_t* a, wchar_t* b, wchar_t* c, wchar_t* d,good* p);
void check1(good* p);