// ���ն�.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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
	char temp[80];           //���������ݰ�
	char head[50];            //��ͷ
	char password[20];
	int i, j;
};
void accept::inputpssword()
{
	cout << "���նˣ�" << endl;
	cout << "���������룺" << endl;        //��������
	cin >> password;
	while (strcmp(password, "hello") != 0)
	{
		cout << "��Ч����" << endl;
		cout << "�������������룺" << endl;;
		cin >> password;
	}
	getchar();
	cout << "OK!" << endl;
}
class checkit :public accept
{
public:
	void check();      //�жϰ�ͷ����β
	void decrypt();    //����
private:
	char tail[30];
};
void accept::check()
{
	ifstream ocin("C:\\Users\\zhousheng\\Desktop\\test.txt");     //��tesst.txt
	if (ocin.is_open())             //�ж��ļ��Ƿ��
	{
		ocin.clear();
		ocin.seekg(0, ios::beg);           //���ļ�ָ�붨λ�����ݿ�ʼ�ĵط�
		ocin.getline(head, 19, '\0');
		if (strlen(head))
		{
			if (strcmp(head, "Data Encapsulation") != 0)        //�жϰ�ͷ
			{
				cout << "��������" << endl;
				ocin.close();
				exit(0);
			}
		}
	}
	ocin.close();
}
void checkit::check()
{
	ifstream ocin("C:\\Users\\zhousheng\\Desktop\\test.txt");     //��test.txt
	if (ocin.is_open())             //�ж��ļ��Ƿ��
	{
		ocin.clear();
		ocin.seekg(-27, ios::end);
		ocin.getline(tail, 30, '\0');
		if (strlen(temp))     //������ݰ����Ȳ�Ϊ0
		{
			if (strcmp(tail, "#C++ Mirosoft Visual Studio") != 0)    //�жϰ�β
			{
				cout << "������" << endl;
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
	ifstream ocin("C:\\Users\\zhousheng\\Desktop\\test.txt");     //��test.txt
	if (ocin.is_open())             //�ж��ļ��Ƿ��
	{
		ocin.clear();
		ocin.seekg(19, ios::beg);     //���ļ�ָ�붨λ����ͷ�Ժ���������оͲ����а�ͷ
		ocin.getline(temp, 80, '\0');        //���ļ�����ȡ�Ѿ����ܵ�����
		while (temp[i] != '\0')        //��temp��Ϊ��ʱ�����
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
			for (i = 0; i <= j - 29; i++)	                //�޳���β
				cout << temp[i];
			cout << endl;
		}
		ocin.close();
		remove("C:\\Users\\zhousheng\\Desktop\\test.txt");      //�ر��ļ�
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
