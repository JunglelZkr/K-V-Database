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
};
class HashTable
{
	HashNode* hashtable[10000];
	int size;
public:
	HashTable()
	{
		size = 0;
		memset(hashtable, 0, sizeof(HashNode*) * 10000);
	}
	void CreateHashTable(const string name)
	{
		FILE* fp = fopen(name.c_str(), "rb");
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
			char* key_ = new char[buf1 + 1];
			memset(key_, 0, buf1 + 1);
			fread(key_, 1, buf1, fp);
			insert(key_, buf);
			buf = buf + 2 + buf1 + buf2;
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
	void insert(const char* key, int offset_)
	{
		if (size >= 10000)
		{
			cout << "ÄÚ´æÒç³ö£¡" << endl;
			return;
		}
		unsigned int pos = hashprice(key) % 10000;
		HashNode* head = hashtable[pos];
		while (head)
		{
			if (strcmp(key, head->key) == 0)
			{
				head->offset = offset_;
				return;
			}
			head = head->next;
		}
		HashNode* p=new HashNode;
		p->key = new char[strlen(key) + 1];
		strcpy(p->key, key);
		p->offset = offset_;
		p->next = hashtable[pos];
		hashtable[pos] = p;
		size = size + 1;
	}
	void remove_(const char* key_)
	{
		unsigned int pos = hashprice(key_) % 10000;
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
	int find_(const char* key)
	{
		unsigned int pos = hashprice(key) % 10000;
		if (hashtable[pos])
		{
			HashNode* head = hashtable[pos];
			while (head)
			{
				if (strcmp(head->key, key) == 0)
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
		for (i = 0; i < 10000; i++)
		{
			if (hashtable[i])
			{
				HashNode* head = hashtable[i];
				while (head)
				{
					HashNode* p = head;
					head = head->next;
					if (p)
					{
						delete p;
					}
				}
			}
		}
	}
};

