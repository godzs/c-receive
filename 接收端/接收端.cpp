// 接收端.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
class accept {
public:
	void inputpssword();
	void rebuild();
	virtual void check();
protected:
	char temp[80];           //接收用数据包
	char head[50];            //包头
	char password[20];
	int i, j;
};
void accept::inputpssword()
{
	cout << "接收端：" << endl;
	cout << "请输入密码：" << endl;        //输入密码
	cin >> password;
	while (strcmp(password, "hello") != 0)
	{
		cout << "无效密码" << endl;
		cout << "请重新输入密码：" << endl;;
		cin >> password;
	}
	getchar();
	cout << "OK!" << endl;
}
class checkit :public accept
{
public:
	void check();      //判断包头，包尾
	void decrypt();    //解密
private:
	char tail[30];
};
void accept::check()
{
	ifstream ocin("C:\\Users\\zhousheng\\Desktop\\test.txt");     //打开tesst.txt
	if (ocin.is_open())             //判断文件是否打开
	{
		ocin.clear();
		ocin.seekg(0, ios::beg);           //将文件指针定位到数据开始的地方
		ocin.getline(head, 19, '\0');
		if (strlen(head))
		{
			if (strcmp(head, "Data Encapsulation") != 0)        //判断包头
			{
				cout << "数据已损坏" << endl;
				ocin.close();
				exit(0);
			}
		}
	}
	ocin.close();
}
void checkit::check()
{
	ifstream ocin("C:\\Users\\zhousheng\\Desktop\\test.txt");     //打开test.txt
	if (ocin.is_open())             //判断文件是否打开
	{
		ocin.clear();
		ocin.seekg(-27, ios::end);
		ocin.getline(tail, 30, '\0');
		if (strlen(temp))     //如果数据包长度不为0
		{
			if (strcmp(tail, "#C++ Mirosoft Visual Studio") != 0)    //判断包尾
			{
				cout << "数据损坏" << endl;
				ocin.close();
				exit(0);
			}
		}
	}
	ocin.close();
}
void checkit::decrypt()
{
	int i = 0, j;
	ifstream ocin("C:\\Users\\zhousheng\\Desktop\\test.txt");     //打开test.txt
	if (ocin.is_open())             //判断文件是否打开
	{
		ocin.clear();
		ocin.seekg(19, ios::beg);     //将文件指针定位到包头以后，这样输出中就不会有包头
		ocin.getline(temp, 80, '\0');        //从文件中提取已经加密的数据
		while (temp[i] != '\0')        //当temp不为空时，输出
		{
			if (i <= 3)
			{
				temp[i] = temp[i] - 10;
			}
			else if (i <= 7)
			{
				temp[i] = temp[i] + 10;
			}
			else
			{
				temp[i] = temp[i] + 2;
			}
			i++;
		}
		j = strlen(temp);
		if (temp[0] != '\0')
		{
			for (i = 0; i <= j - 29; i++)	                //剔除包尾
				cout << temp[i];
			cout << endl;
		}
		ocin.close();
		remove("C:\\Users\\zhousheng\\Desktop\\test.txt");      //关闭文件
	}
	else
	{
		temp[0] = '\0';
	}
}
void accept::rebuild()
{
	if (temp[0] != '\0')
	{
		j = strlen(temp);
		ofstream oreceive("receive.txt");
		for (i = 0; i < j - 28; i++)
			oreceive << temp[i];
		oreceive.close();
	}
}

int main()
{
	checkit b;
	accept a;
	a.inputpssword();
	while (1)
	{
		accept *p = &a;
		p->check();
		p = &b;
		p->check();
		b.decrypt();
		b.rebuild();
	}
	return 0;
}
