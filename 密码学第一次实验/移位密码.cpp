#include<iostream>
#include<string>

using namespace std;

void attack()
{
    cin.ignore();
    cout << "请输入你想要攻击的字符串：" << endl;
    string str;
    getline(cin, str);
    cout << "====================================================" << endl;
    cout << "可能的字符串为：" << endl;
    for (int j = 1; j < 26; j++)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (64 < str[i] && str[i] < 91)
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
        cout << j << "." << str << endl;
    }
    cout << "====================================================" << endl;
}
void lock()
{
    cout << "请选择你想使用的密钥：" << endl;
    int a;
    cin >> a;
    cin.ignore();
    a = a % 26;
    cout << "请输入你想要加密的字符串：" << endl;
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
    cout << "====================================================" << endl;
    cout << "加密结果为：" << endl;
    cout << str << endl;
    cout << "====================================================" << endl;
}
void unlock()
{
    cout << "请选择你想使用的密钥：" << endl;
    int a;
    cin >> a;
    cin.ignore();
    a = a % 26;
    cout << "请输入你想要解密的字符串：" << endl;
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
    cout << "====================================================" << endl;
    cout << "解密结果为：" << endl;
    cout << str << endl;
    cout << "====================================================" << endl;
}
int main()
{
    //cout << 1 << endl;
    while (true)
    {
        cout << "====================================================" << endl;
        cout << "粥小霖的移位加密器，以下为你可以进行的操作：" << endl;
        cout << "1.加密" << endl;
        cout << "2.解密" << endl;
        cout << "3.攻击" << endl;
        cout << "4.退出" << endl;
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
                attack();
                break;
            case 4:
                cout << "bye!" << endl;
                return 0;
        }
        // system("pause");
    }
    return 0;
}