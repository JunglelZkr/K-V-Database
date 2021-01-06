#pragma once
#include<io.h>
#include<direct.h>
#include<iostream>
#include"Data.h"
#include"time.h"
#include"Hash.h"
class KVDBHandler
{
private:
	string name;//数据库名称
	string tname;//用于记录操作次数（以判断是否进行purge操作）的文件的名称
	string rname;
	string dname;//日志文件名称
	int cnt;//用于暂时保存操作次数（以判断是否进行purge操作）
	HashTable ht;
public:
	KVDBHandler(const string &db_file,int i);
	void changefile(const string &db_file);
	void set(const string &key, const string &value,int i);
	int get(const string& key, string &value);
	int remove_(string key);
	void purge(KVDBHandler &handler_);
	void ifpurge();
	//bool charge(const string key);
	void sort(int *a, int low, int high);
	~KVDBHandler();
};