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
	HashNode* hashtable[50003];
	int size0;
	int m;
	friend class KVDBHandler;
public:
	HashTable()//初始化哈希表
	{
		size0 = 0;
		m = 0;
		for (int i = 0; i < 50003; i++)
		{
			hashtable[i] = NULL;
		}
	}
	void CreateHashTable(const string name)//创建哈希表
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
	unsigned int hashprice(const char *key_)//计算key对应的哈希值
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
	void insert(const char* key_, int offset_)//将key_和其对应的offset插入哈希表中
	{
		if (size0 >= 50003)
		{
			cout << "内存溢出！" << endl;
			return;
		}
		unsigned int pos = hashprice(key_) % 50003;
		if (!hashtable[pos])
		{
			HashNode* p = new HashNode;
			p->key = new char[strlen(key_) + 1];
			strcpy(p->key, key_);
			p->offset = offset_;
			hashtable[pos] = p;
			size0 = size0 + 1;
			m = m + 1;
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
				m = m + 1;
				return;
			}
		}
	}
	void remove_(const char* key_)//在哈希表中删除key对应的元素
	{
		unsigned int pos = hashprice(key_) % 50003;
		if (hashtable[pos])
		{
			HashNode* head = hashtable[pos];
			HashNode* p = NULL;
			HashNode* q = NULL;
			if (strcmp(head->key, key_) == 0)
			{
				HashNode* p = new HashNode;

			}
			while (true)
			{
				if (strcmp(head->key, key_) == 0)
				{
					if (head->next==NULL)
					{
						head = NULL;
					}
					else if (head->next != NULL)
					{

					}
				}
			}
		}
	}
	int find_(const char* key_)//查找key对应的offset
	{
		unsigned int pos = hashprice(key_) % 50003;
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
	void clear_()//清空哈希表
	{
		int i;
		for (i = 0; i < 50003; i++)
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
		m = 0;
	}
};

