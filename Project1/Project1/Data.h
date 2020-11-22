#pragma once
#include<string>
using namespace std;
class Data
{
	int klen;
	int vlen;
	char* key;
	char* value;
public:
	Data();
	Data(string k, string v);
	~Data();
	friend class KVDBHandler;
};