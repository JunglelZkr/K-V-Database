
#include<stdio.h>
#include<ctime>
#include"KVDBHandler.h"

class KVDBtest
{
private:
	string *key;
	string *value;
	KVDBHandler *handler;
	int len;
	int opcnt;
public:
	KVDBtest()
	{
		handler = new KVDBHandler("test");
		srand((unsigned)time(NULL));
		key = new string[100];
		value = new string[100];
		len = 0;
		opcnt = 0;
	}
	void randomString(string &p)
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
		while (opcnt < 300 || len < 100)
		{
			if (op == 0)
			{
				if (len < 80)
				{
					randomString(key[len]);
				}
				else
				{
					key[len] = key[rand() % len];
				}
				randomString(value[len]);
				len++;
				if (value[len - 1].length() == 0 || key[len - 1].length() == 0)
				{
					printf("error\n");
					system("pause");
				}
				handler->set(key[len - 1], value[len - 1]);
			}
			else if (op == 1)
			{
				string testvalue;
				int index = rand() % len;
				int result = handler->get(key[index], testvalue);
				if (result == 0)
				{
					return;
				}
				string value_;
				for (int j = 0; j < len; j++)
				{
					if (key[j] == key[index])
					{
						value_ = value[j];
					}
				}
				if (!(testvalue == value_))
				{
					printf("错误：key值为%s\nvalue值应为%s\n实际为%s\n", key[index].c_str(), value_.c_str(), testvalue.c_str());
					printf("index=%d\nlen=%d\n", index, len);
					system("pause");
					return;
				}
				if (value_.length() != 0)
				{
					printf("value值为%s\n", testvalue.c_str());
				}
				else
				{
					printf("找不到key值为%s的value值\n", key[index].c_str());
				}
			}
			else if (op == 2)
			{
				int index = rand() % len;
				string value_;
				handler->get(key[index], value_);
				if (value_.length() != 0)
				{
					for (int i = 0; i < len; i++)
					{
						if(key[i] == key[index])
						{
							value[i].clear();
						}
					}
					printf("删除了下标为%d的key\n", index);
					handler->del(key[index]);
				}
				else
				{
					op = randomop();
					continue;
				}
			}
			printf("操作次数：%d\n\n", ++opcnt);
			op = randomop();
		}
		printf("测试成功\n");
	}
	int randomop()
	{
		if (len < 0)
		{
			return 0;
		}
		else if (len < 80)
		{
			return rand() % 3;
		}
		else if (len < 100)
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
};
int main()
{
	
	KVDBtest test;
	test.test();

}