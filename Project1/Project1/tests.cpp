#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctime>
#include<string>
#include"KVDBHandler.h"
#include"test.h"
using namespace std;
/*class KVDBtest
{
private:
	string *key;
	string *value;
	KVDBHandler *handler;
	int len;
	int opcnt;
	int size;
public:
	KVDBtest()
	{
		size = 1000;
		handler = new KVDBHandler("test",1);
		srand((unsigned)time(NULL));
		key = new string[size];
		value = new string[size];
		len = 0;
		opcnt = 0;
	}
	void same(string &p)
	{
		p = "1";
	}
	void randomString(string &p)//��������ַ���
	{
		p.clear();
		int len = rand() % 20 + 1;
		for (int j = 0; j < len; j++)
		{
			int a;
			a = rand() % 3;
			if (a == 0)
			{
				p.push_back(rand() % ('Z' - 'A' + 1) + 'A');
			}
			else if (a == 1)
			{
				p.push_back(rand() % ('z' - 'a' + 1) + 'a');
			}
			else if (a == 2)
			{
				p.push_back(rand() % ('9' - '0' + 1) + '0');
			}
		}
	}
	void test()
	{
		int op = 0;
		while (opcnt < 3 * size || len < size)
		{
			if (op == 0)//set
			{
				if (len < (size * 4 / 5))
				{
					randomString(key[len]);
				}
				else
				{
					key[len] = key[rand() % len];
				}
				randomString(value[len]);
				printf("set:%s %s\n", key[len].c_str(), value[len].c_str());
				printf("д���%d������\n", ++len);
				handler->set(key[len - 1], value[len - 1],1);
			}
			else if (op == 1)//get
			{
				string testvalue;
				int index = rand() % len;
				handler->get(key[index], testvalue);//��ȡ���ݿ��ж�Ӧ��value����ֵ��testvalue
				string value_;
				for (int j = 0; j < len; j++)//�������ɵ������������ҳ����һ����Ӧ��value����ֵ��value_
				{
					if (key[j] == key[index])
					{
						value_ = value[j];
					}
				}
				if (!(testvalue == value_))//���ݿⷵ�ص�test value��ʵ�ʵ�value����
				{
					printf("����keyֵΪ%s\nvalueֵӦΪ%s\nʵ��Ϊ%s\n", key[index].c_str(), value_.c_str(), testvalue.c_str());
					printf("���ǵ�%d��д�������\n�Ѿ�д��%d������\n", index + 1, len);
					double time = clock();
					printf("��ʱ%.3fs\n", time / 1000);
					system("pause");
					return;
				}
				if (value_.size() != 0)
				{
					printf("valueֵΪ%s\n", testvalue.c_str());
				}
				else
				{
					printf("�Ҳ���keyֵΪ%s��valueֵ\n", key[index].c_str());
				}
			}
			else if (op == 2)
			{
				int index = rand() % len;
				string value_;
				handler->get(key[index], value_);
				if (value_.size() != 0)//�ж�ɾ���Ƿ���Ч������Ч��������ж�Ӧ��valueֵ���
				{
					for (int i = 0; i < len; i++)
					{
						if (key[i] == key[index])
						{
							value[i].clear();
						}
					}
					printf("ɾ����%d������\n", index + 1);
					handler->remove_(key[index]);
				}
				else
				{
					op = randomop();
					continue;
				}
			}
			printf("��������%d\n\n", ++opcnt);
			op = randomop();
		}
		printf("���Գɹ�\n");
	}
	int randomop()
	{
		if (len < size / 10 && len < 100)
		{
			return 0;
		}
		else if (len < (size * 4 / 5))
		{
			return rand() % 3;
		}
		else if (len < size)
		{
			int result = rand() % 2;
			return result == 0 ? result : result + 1;
		}
		else
		{
			return 1;
		}
	}
	~KVDBtest()
	{
		delete[] key;
		delete[] value;
		delete handler;
	}
};*/
int main()
{
	/*KVDBtest test;
	test.test();*/
	m();
	//double time = clock();
	//printf("???��%.3fs\n", time / 1000);
	//m();
}