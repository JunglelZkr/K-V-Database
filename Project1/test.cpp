#define _CRT_SECURE_NO_WARNINGS
#include"KVDBHandler.h"


void m()
{
	string file;
	cout << "����Ҫ�򿪵����ݿ⣺";
	getline(cin, file);
	KVDBHandler handler((const string)file,1);
	string op;
	while (true)
	{
		cout << "������������ͣ�" << endl;
		getline(cin, op);
		if (op == "select")  //����ѡ��Ҫ�򿪵����ݿ�
		{
			cout << "��������Ҫ�滻�����ݿ⣺";
			getline(cin, file);
			handler.changefile(file);
		}
		else if (op == "set") //д������
		{
			string key;
			string value;
			cout << "������keyֵ��";
			getline(cin, key);
			cout << "������valueֵ��";
			getline(cin, value);
			handler.set(key, value,1);
		}
		else if (op == "get") //��ȡ����
		{
			string key;
			string value;
			cout << "������Ҫ���ҵ�value����Ӧ��keyֵ��";
			getline(cin, key);
			int x=handler.get(key, value);
			if (x == 0)
			{
				cout << "������������keyֵ����Ϊ��" << endl;
			}
			else
			{
				if (x == 1)
				{
					cout << "keyֵ��" << key << "����Ӧ��valueֵΪ��" << value << endl;
				}
				if (x == 2)
				{
					cout << "keyֵΪ" << key << "�����ݲ����ڡ�" << endl;
				}
				if (x == 3)
				{
					cout << "keyֵΪ" << key << "�������ѱ�ɾ����" << endl;
				}
			}
		}
		else if (op == "delete")
		{
			string key;
			cout << "��������Ҫɾ����key��";
			getline(cin, key);
			int x=handler.remove_(key);
			if (x == 0)
			{
				cout << "������������keyֵ����Ϊ��" << endl;
			}
			if (x == 1)
			{
				cout << "ɾ��ʧ�ܣ������ݲ����ڣ�" << endl;
			}
			if (x == 2)
			{
				cout << "ɾ��ʧ�ܣ��������ѱ�ɾ����" << endl;
			}
			if (x == 3)
			{
				cout << "����ɾ���ɹ���" << endl;
			}
		}
		else if (op == "exit")
		{
			exit(0);
		}
		else
		{
			cout << "������������������ָ�" << endl;
			continue;
		}
	}
	return;
}