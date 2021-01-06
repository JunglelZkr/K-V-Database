#define _CRT_SECURE_NO_WARNINGS
#include"KVDBHandler.h"
#include<stdio.h>
#include"time.h"
localtime_::localtime_()//获取当前时间
{
	time_t timer;
	struct tm *tblock;
	time(&timer);
	tblock = gmtime(&timer);
	year = tblock->tm_year + 1900;
	month = tblock->tm_mon + 1;
	day = tblock->tm_mday;
	hour = tblock->tm_hour + 8;
	mintue = tblock->tm_min;
	sec = tblock->tm_sec;
}
void localtime_::settime(const string str)//在日志文件中写入当前时间
{
	FILE* fr = fopen(str.c_str(), "a");
	fprintf(fr, "%d.%d.%d %d:%d:%d ", year,month,day,hour,mintue,sec);
	fclose(fr);
}
void localtime_::setcreate(const string str,const string str2,int i,float j)//打开或创建一个数据库的日志
{
	settime(str);
	FILE* fr = fopen(str.c_str(), "a");
	char ch3 = ' ';
	char ch4 = '\n';
	if (i == 1)
	{
		string str1 = "Create a k_v called ";
		str1 = str1 + str2;
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	if (i == 2)
	{
		string str1 = "Open a k_v called ";
		str1 = str1 + str2;
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	if (i == 3)
	{
		string str1 = "Change a k_v to ";
		str1 = str1 + str2;
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	fwrite(&ch3, 1, 1, fr);
	string str3 = "running for:";
	string str4 = "ms.";
	fwrite(str3.c_str(), 1, str3.length(), fr);
	fprintf(fr, "%.3f", j);
	fwrite(str4.c_str(), 1, str4.length(), fr);
	fwrite(&ch4, 1, 1, fr);
	fclose(fr);
}
void localtime_::setset(const string str, const string str2, const string str3,float i)//写入一个数据的日志
{
	char ch3 = ' ';
	char ch4 = '\n';
	settime(str);
	FILE* fr = fopen(str.c_str(), "a");
	string str1 = "Execute set:key is ";
	str1 = str1 + str2 + ",value is " + str3;
	fwrite(str1.c_str(), 1, str1.length(), fr);
	fwrite(&ch3, 1, 1, fr);
	string str5 = "running for:";
	string str4 = "ms.";
	fwrite(str5.c_str(), 1, str5.length(), fr);
	fprintf(fr, "%.3f", i);
	fwrite(str4.c_str(), 1, str4.length(), fr);
	fwrite(&ch4, 1, 1, fr);
	fclose(fr);
}
void localtime_::setget(const string str, const string str2, const string str3, int i,float j)//查找一个数据的日志
{
	char ch3 = ' ';
	char ch4 = '\n';
	string str1 = "Execute get:";
	settime(str);
	FILE* fr = fopen(str.c_str(), "a");
	if (i == 0)
	{
		str1 = str1 + "error(keylenght=0)";
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	if (i == 1)
	{
		str1 = str1 + "key is " + str2 + ",value is " + str3;
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	if (i == 2)
	{
		str1 = str1 + "the data(key="+str2+") does not exist";
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	if (i == 3)
	{
		str1 = str1 + "the data(key=" + str2 + ") has been deleted";
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	fwrite(&ch3, 1, 1, fr);
	string str5 = "running for:";
	string str4 = "ms.";
	fwrite(str5.c_str(), 1, str5.length(), fr);
	fprintf(fr,"%.3f", j);
	fwrite(str4.c_str(), 1, str4.length(), fr);
	fwrite(&ch4, 1, 1, fr);
	fclose(fr);
}
void localtime_::setremove(const string str, const string str2, int i, float j)//删除一个数据的日志
{
	char ch3 = ' ';
	char ch4 = '\n';
	string str1 = "Execute delete:";
	settime(str);
	FILE* fr = fopen(str.c_str(), "a");
	if (i == 0)
	{
		str1 = str1 + "error(keylenght=0)";
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	if (i == 1)
	{
		str1 = str1 + "the data(key="+str2+") does not exist";
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	if (i == 2)
	{
		str1 = str1 + "the data(key="+str2+") has been deleted";
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	if (i == 3)
	{
		str1 = str1 + "the data(key="+str2+") was deleted successfully ";
		fwrite(str1.c_str(), 1, str1.length(), fr);
	}
	fwrite(&ch3, 1, 1, fr);
	string str3 = "running for:";
	string str4 = "ms.";
	fwrite(str3.c_str(), 1, str3.length(), fr);
	fprintf(fr, "%.3f", j);
	fwrite(str4.c_str(), 1, str4.length(), fr);
	fwrite(&ch4, 1, 1, fr);
	fclose(fr);
}
void localtime_::setpurge(const string str,float i)//purge操作的日志
{
	char ch3 = ' ';
	char ch4 = '\n';
	string str1 = "Execute purge:";
	settime(str);
	FILE* fr = fopen(str.c_str(), "a");
	fwrite(str1.c_str(), 1, str1.length(), fr);
	string str3 = "running for:";
	string str4 = "ms.";
	fwrite(str3.c_str(), 1, str3.length(), fr);
	fprintf(fr, "%.3f", i);
	fwrite(str4.c_str(), 1, str4.length(), fr);
	fwrite(&ch4, 1, 1, fr);
	fclose(fr);
}