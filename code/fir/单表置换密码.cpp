#include<iostream>
#include<string>
using namespace std;
string str1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ", str2, a;

string get_secret(string str) 
{
	string secret(26,' ');
	int num = 0;
	for (int i = 0; i < str.length(); i++) 
	{
		if ((96 < str[i] && str[i] < 123)|| (64 < str[i] && str[i] < 91))
		{
			if (96 < str[i]&&str[i] < 123)
				str[i] -= 32;
			for (int j = 0; j <= num; j++)
			{
				if (str[i] == secret[j])
					break;
				else
				{
					if (j == num)
					{
						secret[j] = str[i];
						num++;
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (str1[i] == secret[j])
				break;
			else 
			{
				if (j == num - 1)
				{
					secret[j + 1] = str1[i];
					num++;
					break;
				}
			}
		}
	}

	cout <<"�����Ϊ:  "<<endl<<  str1 << endl<< secret<<endl;
	return secret;
}
void lock() 
{
	cin.ignore();
	cout << "����������û������" << endl;
	getline(cin, str2);
	str2 = get_secret(str2);
	cout << "��������Ҫ���ܵ�����" << endl;
	getline(cin, a);
	for (int i = 0; i < a.length(); i++)
	{
		if (64 < a[i]&&a[i] < 91)
		{
			a[i] = str2[a[i] - 65];
		}
		else
		{
			if (96 < a[i]&&a[i] < 123)
				a[i] = str2[a[i] - 97] + 32;
		}
	}
	cout << a << endl;
}
void unlock()
{
	cin.ignore();
	cout << "����������û������" << endl;
	getline(cin, str2);
	str2 = get_secret(str2);
	cout << "��������Ҫ���ܵ�����" << endl;
	getline(cin, a);
	for (int i = 0; i < a.length(); i++)
	{
		if (64 < a[i] && a[i] < 91)
		{
			for (int j = 0; j < 26; j++)
			{
				if (a[i] == str2[j])
				{
					a[i] = str1[j];
					break;
				}
			}
		}
		else
		{
			if (96 < a[i] && a[i] < 123)
			{
				for (int j = 0; j < 26; j++)
				{
					if (a[i] - 32 == str2[j])
					{
						a[i] = str1[j] + 32;
						break;
					}
				}
			}
		}
	}
	cout << a;
}
int main()
{
	while (true)
	{
		cout << "����1���ܣ�����2����";
		int a;
		cin >> a;
		switch (a)
		{
		case 1:
			lock();
			break;
		case 2:
			unlock();
		}


	}

}