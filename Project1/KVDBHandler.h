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
	string name;
	string tname;
	string rname;
	string dname;
	int cnt;
	HashTable ht;
public:
	KVDBHandler(const string &db_file,int i);
	void changefile(const string &db_file);
	void set(const string &key, const string &value,int i);
	int get(const string& key, string &value);
	int remove_(string key);
	void purge(KVDBHandler &handler_);
	void ifpurge();
	bool charge(const string key);
	~KVDBHandler();
};