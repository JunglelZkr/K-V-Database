#define _CRT_SECURE_NO_WARNINGS
#include"KVDBHandler.h"


void m()
{
	string file;
	cout << "输入要打开的数据库：";
	getline(cin, file);
	KVDBHandler handler((const string)file,1);
	string op;
	while (true)
	{
		cout << "请输入操作类型：" << endl;
		getline(cin, op);
		if (op == "select")  //重新选择要打开的数据库
		{
			cout << "请输入需要替换的数据库：";
			getline(cin, file);
			handler.changefile(file);
		}
		else if (op == "set") //写入数据
		{
			string key;
			string value;
			cout << "请输入key值：";
			getline(cin, key);
			cout << "请输入value值：";
			getline(cin, value);
			handler.set(key, value,1);
		}
		else if (op == "get") //读取数据
		{
			string key;
			string value;
			cout << "请输入要查找的value所对应的key值：";
			getline(cin, key);
			int x=handler.get(key, value);
			if (x == 0)
			{
				cout << "输入数据有误：key值不能为空" << endl;
			}
			else
			{
				if (x == 1)
				{
					cout << "key值：" << key << "所对应的value值为：" << value << endl;
				}
				if (x == 2)
				{
					cout << "key值为" << key << "的数据不存在。" << endl;
				}
				if (x == 3)
				{
					cout << "key值为" << key << "的数据已被删除。" << endl;
				}
			}
		}
		else if (op == "delete")
		{
			string key;
			cout << "请输入需要删除的key：";
			getline(cin, key);
			int x=handler.remove_(key);
			if (x == 0)
			{
				cout << "输入数据有误：key值不能为空" << endl;
			}
			if (x == 1)
			{
				cout << "删除失败（该数据不存在）" << endl;
			}
			if (x == 2)
			{
				cout << "删除失败（该数据已被删除）" << endl;
			}
			if (x == 3)
			{
				cout << "数据删除成功。" << endl;
			}
		}
		else if (op == "exit")
		{
			exit(0);
		}
		else
		{
			cout << "输入有误，请重新输入指令：" << endl;
			continue;
		}
	}
	return;
}