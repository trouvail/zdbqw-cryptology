#include<iostream>
#include<string>
using namespace std;
void attack() 
{
	cin.ignore();
	cout << "ÇëÊäÈëÐèÒª¹¥»÷µÄ×Ö·û´®" << endl;
	string str;
	getline(cin, str);
	for (int j = 1; j < 26; j++)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (64<str[i]&&str[i]<91)
			{
				
					str[i] = str[i] - 1;
					if (str[i] < 65)
						str[i] += 26;
				
			}
			else
			{
				if (96 < str[i] && str[i] < 123)
				{
					str[i] = str[i] - 1;
					if (str[i] < 97)
						str[i] += 26;

				}
			}
		}
		cout << j << ":  " << str << endl;
	}
}
void lock() 
{
	cout << "ÇëÑ¡ÔñÄãµÄÃØÔ¿" << endl;
	int a;
	cin >> a;
	cin.ignore();
	a = a % 26;
	cout << "ÇëÊäÈëÐèÒª¼ÓÃÜµÄ×Ö·û´®" << endl;
	string str;
	getline(cin, str);
	for (int i = 0; i < str.length(); i++)
	{
		if (64 < str[i] && str[i] < 91)
		{
			str[i] = (str[i] + a) % 91;
			if (str[i] < 65)
				str[i] += 65;
		}
		else
		{
			if (96 < str[i] && str[i] < 123)
			{
				str[i] = (str[i] + a) % 123;
				if (str[i] < 97)
					str[i] += 97;

			}
		}
	}
	cout << str << endl;
}
void unlock()
{
	cout << "ÇëÑ¡ÔñÄãµÄÃØÔ¿" << endl;
	int a;
	cin >> a;
	cin.ignore();
	a = a % 26;
	cout << "ÇëÊäÈëÐèÒª½âÃÜµÄ×Ö·û´®" << endl;
	string str;
	getline(cin, str);
	
		for (int i = 0; i < str.length(); i++)
		{
			if (64 < str[i] && str[i] < 91)
			{

				str[i] = str[i] - a;
				if (str[i] < 65)
					str[i] += 26;

			}
			else
			{
				if (96 < str[i] && str[i] < 123)
				{
					str[i] = str[i] - a;
					if (str[i] < 97)
						str[i] += 26;

				}
			}
		}
		cout << str<<endl;
	
}
int main() 
{
	
	
	while (true) 
	{
		cout << "ÊäÈë1¼ÓÃÜ£¬ÊäÈë2½âÃÜ£¬ÊäÈë3¹¥»÷";
		int a;
		cin >> a;
		switch (a) 
		{
		case 1:
			lock();
			break;
		case 2:
			unlock();
			break;
		case 3:
			attack();
		}
		
		
	}
	
}