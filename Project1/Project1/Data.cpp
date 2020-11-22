#include"Data.h"
Data::Data()
{
	klen = 0;
	vlen = 0;
}
Data::Data(string k, string v)
{
	klen = k.length();
	vlen = v.length();
	key = new char[klen + 1];
	for (int i = 0; i < klen; i++)
	{
		key[i] = k[i];
	}
	value = new char[vlen + 1];
	for (int i = 0; i < vlen; i++)
	{
		value[i] = v[i];
	}
}
Data::~Data()
{
	delete[] key;
	delete[] value;
	klen = 0;
	vlen = 0;
}