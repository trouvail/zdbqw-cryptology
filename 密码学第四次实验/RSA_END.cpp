#pragma once
#include <iostream>
#include<fstream>
#include<math.h>
#include <string>
#include<stdlib.h>
#include<time.h>

using namespace std;

// 本次基本上用的数的长度
const int zyl_max = 1025;

// 大素数的类，在其中定义各种运算
class bigint
{
private:
    bool num[zyl_max];
public:
    bool flag;
    // 0是正数，1是负数
    bigint()
    {
        int i;
        for (i = 0; i < zyl_max; i++)
        {
            num[i] = 0;
        }
        flag = 0;
    }
    bigint(int in)
    {
        if (in >= 0)flag = 0;
        else flag = 1;
        int i = 0;
        while (in)
        {
            num[i] = in % 2;
            in = in / 2;
            i++;
        }
        for (; i < zyl_max; i++)
        {
            num[i] = 0;
        }
    }
    bigint(string wxn)
    {
        int i, j = 0;
        int temp;
        for (i = 0; i < zyl_max; i++) {
            num[i] = 0;
        }
        for (i = (wxn.length() - 1); i >= 0; i--) {
            if (wxn[i] >= 'a' && wxn[i] <= 'f') {
                temp = wxn[i] - 'a' + 10;
            }
            else {
                if (wxn[i] >= 'A' && wxn[i] <= 'F') {
                    temp = wxn[i] - 'A' + 10;
                }
                else {
                    temp = wxn[i] - '0';
                }
            }
            if (temp / 8) {
                num[4 * j + 3] = 1;
            }
            if ((temp % 8) / 4) {
                num[4 * j + 2] = 1;
            }
            if ((temp % 4) / 2) {
                num[4 * j + 1] = 1;
            }
            if (temp % 2) {
                num[4 * j] = 1;
            }
            j++;
        }
        flag = 0;
    }
    void random(int n)
    {
        bigint temp;
        srand((int)time(0));
        for (int i = 0; i < n; i++)
        {
            int x = rand() % 2;
            if (x == 1)
                num[i] = true;
            else
                num[i] = false;
        }
        for (int i = zyl_max - 1; i >= n; i--)
        {
            num[i] = false;
        }
        num[n - 1] = true;
        num[0] = true;
    }
    friend bigint operator+(bigint a, bigint b)
    {
        bigint result;
        int i;
        bool temp = 0;
        if (a.flag == b.flag) {
            for (i = 0; i < zyl_max; i++) {
                if (a[i] == 0 && b[i] == 0 && temp == 0) {
                    result.make(i, 0);
                    temp = 0;
                }
                else {
                    if ((a[i] == 1 && b[i] == 0 && temp == 0) ||
                        (a[i] == 0 && b[i] == 1 && temp == 0) ||
                        (a[i] == 0 && b[i] == 0 && temp == 1)) {
                        temp = 0;
                        result.make(i, 1);
                    }
                    else {
                        if ((a[i] == 1 && b[i] == 1 && temp == 0) ||
                            (a[i] == 0 && b[i] == 1 && temp == 1) ||
                            (a[i] == 1 && b[i] == 0 && temp == 1)) {
                            temp = 1;
                            result.make(i, 0);
                        }
                        else {
                            if (a[i] == 1 && b[i] == 1 && temp == 1) {
                                temp = 1;
                                result.make(i, 1);
                            }
                        }
                    }
                }
            }
            result.flag = a.flag;
        }
        if (a.flag == 0 && b.flag == 1) {
            b.Num_Not();
            return a - b;
        }
        if (a.flag == 1 && b.flag == 0) {
            a.Num_Not();
            return b - a;
        }
        if (temp) {
            cout << "Overflow" << endl;
        }
        return result;
    }
    friend bigint operator-(bigint a, bigint b)
    {
        bigint result;
        int i;
        bool temp = 0;
        if (a.flag == b.flag) {
            if (!(b.abs() > a.abs())) {
                for (i = 0; i < zyl_max; i++) {
                    if ((a[i] == 0 && b[i] == 0 && temp == 0) ||
                        (a[i] == 1 && b[i] == 0 && temp == 1) ||
                        (a[i] == 1 && b[i] == 1 && temp == 0)) {
                        result.make(i, 0);
                        temp = 0;
                    }
                    else {
                        if ((a[i] == 0 && b[i] == 0 && temp == 1) ||
                            (a[i] == 0 && b[i] == 1 && temp == 0) ||
                            (a[i] == 1 && b[i] == 1 && temp == 1)) {
                            temp = 1;
                            result.make(i, 1);
                        }
                        else {
                            if (a[i] == 0 && b[i] == 1 && temp == 1) {
                                temp = 1;
                                result.make(i, 0);
                            }
                            else {
                                if (a[i] == 1 && b[i] == 0 && temp == 0) {
                                    temp = 0;
                                    result.make(i, 1);
                                }
                            }
                        }
                    }
                }
                result.flag = a.flag;
            }
            else {
                result = (b - a);
                result.flag = !a.flag;
            }
        }
        if (a.flag == 0 && b.flag == 1) {
            b.Num_Not();
            return a + b;
        }
        if (a.flag == 1 && b.flag == 0) {
            b.Num_Not();
            return a + b;
        }
        return result;
    }
    friend bigint operator*(bigint a, bigint b)
    {
        bigint result;
        int i;
        for (i = 0; i < zyl_max; i++) {
            if (b[i] == 1) {
                result = result + a;
            }
            a.leftMove(1);
        }
        if (a.flag == b.flag) {
            result.flag = 0;
        }
        else {
            result.flag = 1;
        }
        return result;
    }
    friend bigint operator/(bigint a, bigint b)
    {
        bigint count("0");
        if (a.flag == b.flag) {
            count.flag = 0;
        }
        else {
            count.flag = 1;
        }
        int i, j;
        bigint tempA = a, tempB = b, ZERO("0");
        if (ZERO > tempA) {
            tempA.Num_Not();
        }
        if (ZERO > tempB) {
            tempB.Num_Not();
        }
        for (j = zyl_max - 1; j >= 0; j--) {
            if (b[j]) {
                break;
            }
        }
        bigint result ;
        for (i = zyl_max - j - 1; i >= 0; i--) {
            result = tempB;
            result.leftMove(i);
            if (!(result > tempA)) {
                count.make(i, 1);
                tempA = tempA - result;
            }
        }
        return count;
    }
    friend bigint operator%(bigint a, bigint b)
    {
        bigint result;
        result = a - (a / b) * b;
        return result;
    }
    friend bool operator>(bigint a, bigint b)
    {
        bool Bigger = 0;
        int i;
        if (a.flag == 0 && b.flag == 1) {
            Bigger = true;
            bool allZERO = true;
            for (i = 0; i < zyl_max; i++) {
                if (a[i] != 0 || b[i] != 0) {
                    allZERO = false;
                }
            }
            if (allZERO) {
                Bigger = false;
            }
        }
        else {
            if (a.flag == 1 && b.flag == 0) {
                Bigger = false;
                bool allZERO = true;
                for (i = 0; i < zyl_max; i++) {
                    if (a[i] != 0 || b[i] != 0) {
                        allZERO = false;
                    }
                }
                if (allZERO) {
                    Bigger = false;
                }
            }
            else {
                if (a.flag == 0 && b.flag == 0) {
                    for (i = zyl_max - 1; i >= 0; i--) {
                        if (a[i] == 1 && b[i] == 0) {
                            Bigger = true;
                            break;
                        }
                        if (a[i] == 0 && b[i] == 1) {
                            Bigger = false;
                            break;
                        }
                    }
                }
                else {
                    for (i = zyl_max - 1; i >= 0; i--) {
                        if (a[i] == 1 && b[i] == 0) {
                            Bigger = false;
                            break;
                        }
                        if (a[i] == 0 && b[i] == 1) {
                            Bigger = true;
                            break;
                        }
                    }
                }
            }
        }
        return Bigger;
    }
    friend bool operator==(bigint a, bigint b)
    {
        int i;
        bool same = true;
        if (a.flag != b.flag) {
            same = false;
        }
        for (i = 0; i < zyl_max; i++) {
            if (a[i] != b[i]) {
                same = false;
                break;
            }
        }
        return same;
    }
    friend bool operator!=(bigint a, bigint b)
    {
        int i;
        if (a.flag != b.flag) {
            return true;
        }
        for (i = 0; i < zyl_max; i++) {
            if (a[i] != b[i]) {
                return true;
            }
        }
        return false;
    }
    bigint modMul(bigint a, bigint b, bigint c)
    {
        bigint result;
        int i;
        for (i = 0; i < zyl_max; i++) {
            if (b[i] == 1) {
                result = result + a;
                while (result > c)
                    result = result - c;
            }
            a.leftMove(1);
            while (a > c)
                a = a - c;
        }
        if (a.flag == b.flag) {
            result.flag = 0;
        }
        else {
            result.flag = 1;
        }
        return result;
    }
    bigint expmod(bigint e, bigint n)
    {
        bigint c("1");
        int i = zyl_max - 1;
        while (!e[i]) {
            i--;
        }
        int j;
        for (j = i; j >= 0; j--) {
            c = modMul(c, c, n);
            if (e[j]) {
                c = modMul(c, (*this), n);
            }
        }
        return c;
    }
    bigint inv(bigint x)
    {
        bigint ZERO("0"), ONE("1");
        bigint x1 = ONE, x2 = ZERO, x3 = x;
        bigint y1 = ZERO, y2 = ONE, y3 = (*this);
        bigint t1, t2, t3;
        if (y3 == ONE) {
            return ONE;
        }
        bigint q;
        bigint g;
        do {
            q = x3 / y3;
            t1 = x1 - q * y1;
            t2 = x2 - q * y2;
            t3 = x3 - q * y3;
            x1 = y1;
            x2 = y2;
            x3 = y3;
            y1 = t1;
            y2 = t2;
            y3 = t3;
        } while (!(y3 == ONE));
        g = y2;
        if (!(g > ZERO))
            g = x + g;
        return g;
    }
    void leftMove(int i)
    {
        int k;
        for (k = zyl_max - 1; k > i - 1; k--) {
            num[k] = num[k - i];
        }
        for (k = 0; k < i; k++) {
            num[k] = 0;
        }
    }
    bool operator[](int i)
    {
        return num[i];
    }
    void make(int i, bool a)
    {
        num[i] = a;
    }
    // 16进制的打印
    void print()
    {
        if (this->flag == 1) {
            cout << '-';
        }
        char result[zyl_max];
        int i;
        for (i = zyl_max - 1; i >= 0; i--) {
            if ((*this)[i] == 1) {
                break;
            }
        }
        i++;
        int k;
        int length = 0;
        switch (i % 4) {
        case 1:
            length = i + 3;
            break;
        case 2:
            length = i + 2;
            break;
        case 3:
            length = i + 1;
            break;
        case 0:
            length = i;
            break;
        }
        for (k = 0; k < length; k = k + 4) {
            if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
                result[k / 4] = '0';
            }
            if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
                result[k / 4] = '1';
            }
            if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
                result[k / 4] = '2';
            }
            if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 0) {
                result[k / 4] = '3';
            }
            if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
                result[k / 4] = '4';
            }
            if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
                result[k / 4] = '5';
            }
            if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
                result[k / 4] = '6';
            }
            if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 0) {
                result[k / 4] = '7';
            }
            if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
                result[k / 4] = '8';
            }
            if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
                result[k / 4] = '9';
            }
            if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
                result[k / 4] = 'A';
            }
            if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 0 && (*this)[k + 3] == 1) {
                result[k / 4] = 'B';
            }
            if ((*this)[k] == 0 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
                result[k / 4] = 'C';
            }
            if ((*this)[k] == 1 && (*this)[k + 1] == 0 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
                result[k / 4] = 'D';
            }
            if ((*this)[k] == 0 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
                result[k / 4] = 'E';
            }
            if ((*this)[k] == 1 && (*this)[k + 1] == 1 && (*this)[k + 2] == 1 && (*this)[k + 3] == 1) {
                result[k / 4] = 'F';
            }
        }
        if (i == 0) {
            cout << '0' << endl;
        }
        else {
            for (i = (k / 4) - 1; i >= 0; i--) {
                cout << result[i];
            }
            cout << endl;
        }
    }
    void Num_Not()
    {
        this->flag = !(this->flag);
    }
    bigint abs()
    {
        bigint temp = (*this);
        if (temp.flag == 0) {
            return temp;
        }
        else {
            temp.Num_Not();
            return temp;
        }
    }
};

// 下面为2000以内的303个素数
int pri[303] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
    31 ,37 ,41, 43 ,47, 53 ,59, 61 ,67, 71,
    73 ,79, 83 ,89, 97, 101, 103 ,107, 109, 113,
    127, 131 ,137 ,139 ,149, 151, 157, 163 ,167, 173,
    179, 181, 191 ,193 ,197, 199, 211 ,223, 227 ,229,
    233, 239, 241 ,251, 257, 263, 269 ,271, 277, 281,
    283, 293 ,307, 311, 313, 317 ,331 ,337, 347, 349,
    353 ,359, 367 ,373, 379, 383 ,389 ,397, 401 ,409,
    419 ,421, 431 ,433, 439, 443 ,449 ,457 ,461 ,463,
    467, 479 ,487, 491, 499, 503 ,509 ,521 ,523, 541,
    547 ,557 ,563 ,569, 571, 577 ,587 ,593, 599 ,601,
    607, 613, 617, 619, 631, 641 ,643 ,647 ,653, 659,
    661, 673, 677, 683, 691, 701 ,709 ,719 ,727 ,733,
    739, 743 ,751, 757, 761, 769, 773 ,787 ,797, 809,
    811, 821, 823, 827, 829, 839, 853 ,857 ,859, 863,
    877, 881, 883, 887, 907, 911, 919, 929 ,937 ,941,
    947, 953, 967 ,971 ,977, 983 ,991 ,997 ,
    1009, 1013 ,1019 ,1021, 1031 ,1033 ,1039 ,1049, 1051 ,1061,
    1063 ,1069, 1087, 1091, 1093 ,1097, 1103 ,1109, 1117 ,1123,
    1129 ,1151, 1153, 1163 ,1171 ,1181 ,1187 ,1193 ,1201 ,1213,
    1217, 1223, 1229 ,1231 ,1237, 1249 ,1259 ,1277, 1279 ,1283,
    1289, 1291, 1297 ,1301 ,1303, 1307 ,1319 ,1321 ,1327, 1361,
    1367 ,1373, 1381, 1399 ,1409, 1423 ,1427 ,1429 ,1433, 1439,
    1447 ,1451, 1453, 1459 ,1471 ,1481, 1483, 1487 ,1489, 1493,
    1499 ,1511, 1523, 1531 ,1543 ,1549, 1553 ,1559, 1567, 1571,
    1579 ,1583, 1597 ,1601 ,1607 ,1609, 1613 ,1619 ,1621, 1627,
    1637, 1657, 1663 ,1667, 1669 ,1693, 1697 ,1699 ,1709 ,1721,
    1723 ,1733, 1741 ,1747, 1753, 1759, 1777 ,1783 ,1787 ,1789,
    1801, 1811, 1823 ,1831, 1847 ,1861, 1867,1871, 1873, 1877,
    1879 ,1889 ,1901 ,1907 ,1913 ,1931, 1933, 1949 ,1951 ,1973,
    1979, 1987, 1993 ,1997 ,1999
};

// isPrime和getPrime都是获取素数时用到的，首先是判断素数
bool isPrime(bigint a)
{
    const bigint ZERO(0);
    for (int i = 0; i < 303; i++)
    {
        bigint p(pri[i]);
        bigint d(1);
        bigint c = (a % p);
        if (c == ZERO)
            return false;
    }
    return true;
}

// 生成一个512位的大素数
bigint getPrime()
{
    bigint temp;
    bigint TWO("2");
    temp.random(512);
    while (true) {
        if (isPrime(temp)) {
            return temp;
        }
        temp = temp + TWO;
    }
}

// 接下来是RSA的类，用于保存其各个参数
class RSA
{
private:
    // p、q为两个大素数，d为私钥，f为n的欧拉函数
    bigint p, q, d, f;
public:
    // e为公钥，n为两个大素数之积
    bigint e, n;
    // m为明文，c为密文
    bigint m, c;
    RSA(bigint a, bigint b)
    {
        bigint one("1");
        p = a;
        q = b;
        n = p * q;
        f = (p - one) * (q - one);
        bigint curr("10001");
        // 默认选取的公钥e为10001，和老师给的工具中相同
        e = curr;
        // d为私钥
        d = e.inv(f);
    }
    void encode(bigint m1)
    {
        m = m1;
        c = m.expmod(e, n);
    }
    void decode(bigint c1)
    {
        c = c1;
        m = c.expmod(d, n);
    }
    void decode_show()
    {
        
        cout << "需要模的数n为：" << endl;
        n.print();
        cout << "解密所用的私钥d为：" << endl;
        d.print();
        cout << "公钥e为：" << endl;
        e.print();
        cout << "解密后的明文为：" << endl;
        m.print();
    }
    void encode_show(){
        cout << "需要模的数n为：" << endl;
        n.print();
        cout << "私钥d为：" << endl;
        d.print();
        cout << "加密所用的公钥e为：" << endl;
        e.print();
        cout << "加密后的密文为：" << endl;
        c.print();
    }
    
};


int main()
{
//    cout << 1 << endl;
    
    // 进行简介
    cout << "====================================================================================" << endl;
    cout << "粥小霖的`RSA`工具，你可以输入以下数字进行相应操作：" << endl;
    cout << "1.RSA加密" << endl;
    cout << "2.RSA解密" << endl;
    cout << "3.退出程序" << endl;
    cout << "====================================================================================" << endl;

    int i;
    cin >> i;
    RSA* rsa;
    cin.get();

    //此处用的是老师所给的工具产生的两个大素数，防止自己产生的大素数出现意外
    bigint p("A953B1DA8ED8AF6B4560B4DFE2E3B3B530ACE4F791D12BECA07CBCD62AE075C9A97036C05E9A77AE4E6DCAA3018D6B9E0B3EAD3E052BD3EE7DC00F5393A1254B");
    bigint q("93ED4D2E4D4F5F9EE6CFB9F235F52CC76A68A33C03D395E7DB9CA923554AA23F709F1597FAB3C7353E0EA16C9B37F03B3B87333FD93E25DCDCBB1A05BBE6F393");

    rsa = new RSA(p, q);
    while (i != 0)
    {
        if (i == 1)
        {
            cout << "请输入你想要加密的明文：" << endl;
            string m;
            getline(cin, m);
            rsa->encode(m);
            rsa->encode_show();
        }
        else if(i == 2)
        {
            cout << "请输入你想要解密的密文：" << endl;
            cin.ignore();
            string c;
            getline(cin, c);
            rsa->decode(c);
            rsa->decode_show();
        }
        else
        {
            break;
        }

        cout << "====================================================================================" << endl;
        cout << "粥小霖的`RSA`工具，你可以输入以下数字进行相应操作：" << endl;
        cout << "1.RSA加密" << endl;
        cout << "2.RSA解密" << endl;
        cout << "3.退出程序" << endl;
        cout << "====================================================================================" << endl;

        cin >> i;
    }
    
//    getPrime().print();
}
