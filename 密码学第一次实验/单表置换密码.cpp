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
        if ((96 < str[i] && str[i] < 123) || (64 < str[i] && str[i] < 91))
        {
            if (96 < str[i] && str[i] < 123)
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
    cout << "====================================================" << endl;
    cout << "根据输入所构造的密码表为：" << endl << str1 << endl << secret << endl;
    cout << "====================================================" << endl;
    return secret;
}
void lock()
{
    cin.ignore();
    cout << "请输入一个你喜欢的短语以构造置换密码表：" << endl;
    getline(cin, str2);
    str2 = get_secret(str2);
    cout << "请输入你想要加密的字符串：" << endl;
    getline(cin, a);
    for (int i = 0; i < a.length(); i++)
    {
        if (64 < a[i] && a[i] < 91)
        {
            a[i] = str2[a[i] - 65];
        }
        else
        {
            if (96 < a[i] && a[i] < 123)
                a[i] = str2[a[i] - 97] + 32;
        }
    }
    cout << "====================================================" << endl;
    cout << "加密结果为：" << endl;
    cout << a << endl;
    cout << "====================================================" << endl;
}
void unlock()
{
    cin.ignore();
    cout << "请输入一个你喜欢的短语以构造置换密码表：" << endl;
    getline(cin, str2);
    str2 = get_secret(str2);
    cout << "请输入你想要解密的字符串：" << endl;
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
    cout << "====================================================" << endl;
    cout << "解密结果为：" << endl;
    cout << a << endl;
    cout << "====================================================" << endl;
}
int main()
{
    // cout << 1 << endl;
    while (true)
    {
        cout << "====================================================" << endl;
        cout << "粥小霖的单表置换加密器，以下为你可以进行的操作：" << endl;
        cout << "1.加密" << endl;
        cout << "2.解密" << endl;
        cout << "3.退出" << endl;
        cout << "====================================================" << endl;
        cout << "请输入相应数字进行你想要的操作：" << endl;
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
                cout << "bye!" << endl;
                return 0;
        }
    }
    return 0;
}