#pragma once
#include<time.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
class localtime_
{
	int year;
	int month;
	int day;
	int hour;
	int mintue;
	int sec;
public:
	localtime_();
	void settime(const string str);
	void setcreate(const string str,const string str2,int i,float j);
	void setset(const string str, const string str2, const string str3,float i);
	void setget(const string str, const string str2, const string str3,int i,float j);
	void setremove(const string str, const string str2,int i,float j);
	void setpurge(const string str,float i);
	friend class KVDBHandler;
};
