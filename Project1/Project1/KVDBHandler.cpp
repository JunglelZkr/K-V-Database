#define _CRT_SECURE_NO_WARNINGS
#include"KVDBHandler.h"
#include<stdio.h>

KVDBHandler::KVDBHandler(const string &db_file,int i) //若文件db_file存在，则打开数据库；否则，创建新的数据库
{
	if (i == 1)
	{
		name = "C:\\kv数据库\\";
		if (_access(name.c_str(), 0) != 0)
		{
			_mkdir(name.c_str());
		}
		rname = db_file;
		tname = name + db_file + "time.txt";
		dname = name + db_file + "log.txt";
		name = name + db_file + ".txt";
		int x;
		localtime_ t1;
		if (_access(name.c_str(), 0) == -1)
		{
			x = 1;
			cout << "该数据库不存在，已为您创建。" << endl;
			cnt = 0;
			FILE* fq = fopen(tname.c_str(), "ab+");
			fwrite(&cnt, sizeof(int), 1, fq);
			fclose(fq);
		}
		else
		{
			x = 2;
			cout << "已为您打开该数据库。" << endl;
			FILE* fq = fopen(tname.c_str(), "rb+");
			fread(&cnt, sizeof(int), 1, fq);
			fclose(fq);
		}
		clock_t start, finish;
		float time_;
		start = clock();
		FILE* fp = fopen(name.c_str(), "ab+");
		finish = clock();
		ht.CreateHashTable(name);
		time_ = (float)(finish - start);
		fclose(fp);
		t1.setcreate(dname, rname, x, time_);
	}
	else
	{
		rname = db_file;
		name = "C:\\kv数据库\\";
		if (_access(name.c_str(), 0) != 0)
		{
			_mkdir(name.c_str());
		}
		name = name + db_file + ".txt";
		FILE* fp = fopen(name.c_str(), "ab+");
		fclose(fp);
	}
}
void KVDBHandler::changefile(const string &db_file) //改变打开的文件
{
	name = "C:\\kv数据库\\";
	if (_access(name.c_str(), 0) != 0)
	{
		_mkdir(name.c_str());
	}
	rname = db_file;
	tname = name + db_file + "time.txt";
	dname = name + db_file + "log.txt";
	name = name + db_file + ".txt";
	int x;
	localtime_ t1;
	if (_access(name.c_str(), 0) == -1)
	{
		x = 1;
		cout << "该数据库不存在，已为您创建。" << endl;
		FILE* fq = fopen(tname.c_str(), "ab+");
		int x = 0;
		fwrite(&x, sizeof(int), 1, fq);
		fclose(fq);
	}
	else
	{
		x = 3;
		cout << "已为您替换为指定数据库。" << endl;
		FILE* fq = fopen(tname.c_str(), "ab+");
		fclose(fq);
	}
	clock_t start, finish;
	float time_;
	start = clock();
	FILE* fp = fopen(name.c_str(), "ab+");
	finish = clock();
	ht.CreateHashTable(name);
	time_ = (float)(finish - start);
	fclose(fp);
	t1.setcreate(dname, rname, x, time_);
}
void KVDBHandler::set(const string &key, const string &value,int i) //写入数据，需检查是否写入成功
{
	localtime_ t1;
	clock_t start, finish;
	float time_;
	start = clock();
	if (key.size() == 0)
	{
		cout << "输入数据有误（key值不能为空）" << endl;
		return;
	}
	if (value.size() == 0)
	{
		cout << "输入数据有误（value值不能为空）" << endl;
		return;
	}
	if (key.size() != 0 && value.size() != 0)
	{
		Data d(key, value);
		FILE* fq = fopen(name.c_str(), "rb");
		if (!fq)
		{
			cout << "文件打开失败" << endl;
			system("pause");
		}
		fseek(fq, 0L, SEEK_END);
		int buf = ftell(fq);
		fclose(fq);
		FILE* fp = fopen(name.c_str(), "ab");
		fwrite(&d.klen, sizeof(int), 1, fp);
		fwrite(&d.vlen, sizeof(int), 1, fp);
		fwrite(d.key, 1, d.klen, fp);
		fwrite(d.value, 1, d.vlen, fp);
		if (i == 1)
		{
			cnt = cnt + 1;
			fclose(fp);
			finish = clock();
			time_ = (float)(finish - start);
			t1.setset(dname, key, value, time_);
			ht.insert(key.c_str(), buf);
			ifpurge();
			cout << "数据写入成功" << endl;
		}
		else
		{
			fclose(fp);
		}
	}
}
int KVDBHandler::get(const string& key, string &value)//在数据库中查找key所对应的value
{
	localtime_ t1;
	clock_t start, finish;
	float time_;
	start = clock();
	int x = 0;
	if (key.size() == 0)
	{
		finish = clock();
		time_ = (float)(finish - start);
		t1.setget(dname, "", "", x, time_);
		return x;
	}
	else
	{
		FILE* fp = fopen(name.c_str(), "rb");
		if (!fp)
		{
			cout << "文件打开失败" << endl;
			system("pause");
		}
		int offset=ht.find_(key.c_str());
		if (offset == -1)
		{
			x = 2;
			fclose(fp);
			return x;
		}
		else
		{
			fseek(fp, offset, SEEK_CUR);
			int buf;
			fread(&buf, sizeof(int), 1, fp);
			if (key.length() == -buf)
			{
				x = 3;
				fclose(fp);
				return x;
			}
			else
			{
				x = 1;
				int buf1;
				fread(&buf1, sizeof(int), 1, fp);
				fseek(fp, buf, SEEK_CUR);
				char* value_ = new char[buf1 + 1];
				memset(value_, 0, buf1 + 1);
				fread(value_, 1, buf1, fp);
				for (int i = 0; i < buf1; i++)
				{
					value.push_back(value_[i]);
				}
				delete[] value_;
			}
		}
		fclose(fp);
		finish = clock();
		time_ = (float)(finish - start);
		t1.setget(dname, key, value, x, time_);
		return x;
	}
}
int KVDBHandler::remove_(string key)//在数据库中删除key所对应的value
{
	localtime_ t1;
	clock_t start, finish;
	float time_;
	start = clock();
	if (key.size() == 0)
	{
		finish = clock();
		time_ = (float)(finish - start);
		t1.setremove(dname, key, 0, time_);
		return 0;
	}
	else
	{
		FILE* fq = fopen(name.c_str(), "rb");
		if (!fq)
		{
			cout << "文件打开失败" << endl;
			system("pause");
		}
		fseek(fq, 0L, SEEK_END);
		int buf = ftell(fq);
		fclose(fq);
		FILE* fp = fopen(name.c_str(), "ab");
		if (!fp)
		{
			cout << "文件打开失败" << endl;
			system("pause");
		}
		string value;
		int y=get(key, value);
		if (value.size() == 0)
		{
			if (y == 2)
			{
				fclose(fp);
				finish = clock();
				time_ = (float)(finish - start);
				t1.setremove(dname, key, 1, time_);
				fclose(fp);
				return 1;
			}
			if (y == 3)
			{
				fclose(fp);
				finish = clock();
				time_ = (float)(finish - start);
				t1.setremove(dname, key, 2, time_);
				return 2;
			}
		}
		else
		{
			Data d(key, value);
			int a;
			a = -d.klen;
			fwrite(&a, sizeof(int), 1, fp);
			fwrite(&d.vlen, sizeof(int), 1, fp);
			fwrite(d.key, 1, d.klen, fp);
			fwrite(d.value, 1, d.vlen, fp);
			fclose(fp);
			finish = clock();
			time_ = (float)(finish - start);
			t1.setremove(dname, key, 3, time_);
			cnt = cnt + 1;
			ht.insert(key.c_str(), buf);
			ifpurge();
			return 3;
		}
	}
}
void KVDBHandler::ifpurge()//判断是否需要进行purge操作
{
	FILE *fp = fopen(tname.c_str(), "rb+");
	if (!fp)
	{
		cout << "文件打开失败" << endl;
		system("pause");
	}
	if (cnt >= 3)
	{
		localtime_ t1;
		clock_t start, finish;
		float time_;
		start = clock();
		cout << "进行purge操作：";
		string file_;
		file_ = rname + "mid";
		KVDBHandler handler1((const string)file_, 0);
		purge(handler1);
		cnt = 0;
		finish = clock();
		time_ = (float)(finish - start);
		t1.setpurge(dname,time_);
	}
	fwrite(&cnt, sizeof(int), 1, fp);
	fclose(fp);
}
void KVDBHandler::purge(KVDBHandler &handler_)//purge操作
{
	FILE *fp = fopen(name.c_str(), "rb+");
	if (!fp)
	{
		cout << "文件打开失败" << endl;
		system("pause");
	}
	int i,j,n,t=0;
	n = ht.m;
	int *a;
	a = new int [n];
	for (i = 0; i < n; i++)
	{
		a[i] = 100000000;
	}
	for (i = 0; i < 50003; i++)
	{
		if (ht.hashtable[i])
		{
			HashNode* head = ht.hashtable[i];
			while (head)
			{
				a[t] = head->offset;
				t = t + 1;
				head = head->next;
			}
		}
	}
	int low, high;
	low = 0;
	high = n - 1;
	sort(a, low, high);
	int begin = 0;
	int offset0;
	for (i = 0; i < n; i++)
	{
		offset0 = a[i] - begin;
		fseek(fp, offset0, SEEK_CUR);
		int buf,buf1;
		string key0, value0;
		fread(&buf, sizeof(int), 1, fp);
		fread(&buf1, sizeof(int), 1, fp);
		if (buf < 0)
		{
			begin = a[i] + sizeof(int) + sizeof(int) -buf + buf1;
			fseek(fp, -buf + buf1, SEEK_CUR);
		}
		else
		{
			char* key_ = new char[buf + 1];
			memset(key_, 0, buf + 1);
			fread(key_, 1, buf, fp);
			for (j = 0; j < buf; j++)
			{
				key0.push_back(key_[j]);
			}
			char* value_ = new char[buf1 + 1];
			memset(value_, 0, buf1 + 1);
			fread(value_, 1, buf1, fp);
			for (j = 0; j < buf1; j++)
			{
				value0.push_back(value_[j]);
			}
			delete[] value_;
			handler_.set(key0, value0, 0);
			delete[] key_;
			begin = a[i] + sizeof(int) + sizeof(int) + buf + buf1;
		}
	}
	delete[] a;
	fclose(fp);
	int result = remove(name.c_str());
	rename(handler_.name.c_str(), name.c_str());
	cout << "已清理无用数据。" << endl;
	ht.clear_();
	ht.CreateHashTable(name);
}
/*bool KVDBHandler::charge(const string key)
{
	FILE* fp = fopen(name.c_str(), "rb");
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	while (ftell(fp) != size)
	{
		int buf;
		fread(&buf, 1, sizeof(int), fp);
		int buf1;
		fread(&buf1, 1, sizeof(int), fp);
		char* key_ = new char[buf + 1];
		memset(key_, 0, buf + 1);
		fread(key_, 1, buf, fp);
		string key1;
		for (int i = 0; i < buf; i++)
		{
			key1.push_back(key_[i]);
		}
		delete[] key_;
		if (key == key1)
		{
			fclose(fp);
			return true;
		}
		else
		{
			fseek(fp, buf1, SEEK_CUR);
		}
	}
	fclose(fp);
	return false;
}*/
void KVDBHandler::sort(int *a, int low, int high)//对数组a进行快排
{
	if (high <= low)
	{
		return;
	}
	int i = low;
	int j = high + 1;
	int pivotkey = a[low];
	while (1)
	{
		while (a[++i] < pivotkey)
		{
			if (i == high)
				break;
		}
		while (a[--j] > pivotkey)
		{
			if (j == low)
				break;
		}
		if (i >= j)
		{
			break;
		}
		int temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
	int temp = a[low];
	a[low] = a[j];
	a[j] = temp;
	sort(a, low, j - 1);
	sort(a, j + 1, high);
}
KVDBHandler::~KVDBHandler()
{

}