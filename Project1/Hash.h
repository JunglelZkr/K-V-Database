#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"KVDBHandler.h"
using namespace std;
class HashNode
{
	char *key;
	int offset;
	HashNode *next;
public:
	HashNode()
	{
		offset = 0;
		next = NULL;
	}
	~HashNode()
	{
		delete[] key;
		next = NULL;
	}
	friend class HashTable;
	friend class KVDBHandler;
};
class HashTable
{
	HashNode* hashtable[10001];
	int size0;
	friend class KVDBHandler;
public:
	HashTable()
	{
		size0 = 0;
		for (int i = 0; i < 10001; i++)
		{
			hashtable[i] = NULL;
		}
		//memset(hashtable, 0, sizeof(HashNode*) * 10001);
	}
	void CreateHashTable(const string name)
	{
		FILE* fp = fopen(name.c_str(), "rb");
		if (!fp)
		{
			cout << "文件打开失败" << endl;
			system("pause");
		}
		fseek(fp, 0L, SEEK_END);
 		int size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		int buf = 0;
		while (ftell(fp) != size)
		{
			int buf1;
			fread(&buf1, sizeof(int), 1, fp);
			int buf2;
			fread(&buf2, sizeof(int), 1, fp);
			if (buf1 < 0)
			{
				buf1 = -buf1;
				fseek(fp, buf1 + buf2, SEEK_CUR);
				buf= buf + sizeof(int) + sizeof(int) + buf1 + buf2;
				continue;
			}
			char* key_ = new char[buf1 + 1];
			memset(key_, 0, buf1 + 1);
			fread(key_, 1, buf1, fp);
			insert(key_, buf);
			buf = buf + sizeof(int)+sizeof(int) + buf1 + buf2;
			fseek(fp, buf2, SEEK_CUR);
			delete[] key_;
		}
		fclose(fp);
	}
	unsigned int hashprice(const char *key_)
	{
		const signed char* p = (const signed char*)key_;
		unsigned int h = *p;
		if (h)
		{
			for (p = p + 1; *p != '\0'; p++)
			{
				h = (h << 5) - h + *p;
			}
		}
		return h;
	}
	void insert(const char* key_, int offset_)
	{
		if (size0 >= 10001)
		{
			cout << "内存溢出！" << endl;
			return;
		}
		unsigned int pos = hashprice(key_) % 10001;
		if (!hashtable[pos])
		{
			HashNode* p = new HashNode;
			p->key = new char[strlen(key_) + 1];
			strcpy(p->key, key_);
			p->offset = offset_;
			hashtable[pos] = p;
			size0 = size0 + 1;
			return;
		}
		else
		{
			HashNode* head = hashtable[pos];
			while (head->next)
			{
				if (strcmp(key_, head->key) == 0)
				{
					head->offset = offset_;
					return;
				}
				head = head->next;
			}
			if (strcmp(key_, head->key) == 0)
			{
				head->offset = offset_;
				return;
			}
			else
			{
				HashNode* p = new HashNode;
				p->key = new char[strlen(key_) + 1];
				strcpy(p->key, key_);
				p->offset = offset_;
				head->next = p;
				return;
			}
		}
	}
	void remove_(const char* key_)
	{
		unsigned int pos = hashprice(key_) % 10001;
		if (hashtable[pos])
		{
			HashNode* head = hashtable[pos];
			HashNode* p = NULL;
			HashNode* q = NULL;
			while (head)
			{
				if (strcmp(head->key, key_) == 0)
				{
					p = head;
					break;
				}
				q = head;
				p = head->next;
			}
			if (p)
			{
				if (q)
				{
					q->next = p->next;
				}
				else
				{
					hashtable[pos] = NULL;
				}
				delete p;
			}
		}
	}
	int find_(const char* key_)
	{
		unsigned int pos = hashprice(key_) % 10001;
		if (hashtable[pos])
		{
			HashNode* head = hashtable[pos];
			while (head)
			{
				if (strcmp(head->key, key_) == 0)
				{
					return head->offset;
				}
				head = head->next;
			}
		}
		return -1;
	}
	void clear_()
	{
		int i;
		for (i = 0; i < 10001; i++)
		{
			if (hashtable[i])
			{
				HashNode *temp = hashtable[i]->next;
				while (temp)
				{
					hashtable[i]->next = temp->next;
					delete temp;
					temp = hashtable[i]->next;
				}
				delete hashtable[i];
				hashtable[i] = NULL;
			}
		}
		size0 = 0;
		for (i = 0; i < 10001; i++)
		{
			if (hashtable[i]!=NULL)
			{
				cout << "1";
			}
		}
	}
};

