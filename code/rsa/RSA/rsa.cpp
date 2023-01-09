#include <iostream>
#include<fstream>
#include <string>
#include<stdlib.h>
#include"bigint.h"
using namespace std;

int pri[303] = { 2,3 ,5, 7 ,11, 13, 17, 19, 23, 29,
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
877, 881, 883, 887, 907, 911, 919, 929 ,937 ,941 ,947, 953, 967 ,971 ,977, 983 ,991 ,997 ,1009, 1013 ,1019 ,1021, 1031 ,1033 ,1039 ,1049, 1051 ,1061,
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
1979, 1987, 1993 ,1997 ,1999 };
bool isPrime(bigint a)
{
	bigint temp = a;
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

class RSA
{
private:
	bigint p, q, d, f;
public:
	bigint e, n;
	bigint m, c;
	RSA(bigint a, bigint b)
	{
		bigint one("1");
		p = a;
		q = b;
		n = p * q;
		f = (p - one) * (q - one);
		bigint curr("10001");
		e = curr;
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

		cout << "��Կn��" << endl;
		n.print();
		cout << "˽Կd��" << endl;
		d.print();
		cout << "��Կe��" << endl;
		e.print();
		cout << "���ģ�" << endl;
		m.print();
	}
	void encode_show(){
			cout << "��Կn��" << endl;
			n.print();
			cout << "˽Կd��" << endl;
			d.print();
			cout << "��Կe��" << endl;
			e.print();
			cout << "���ģ�" << endl;
			c.print();
		}
	
};


int main()
{
	cout << "����1���ܣ�2����  ";
	int i; cin >> i;
	RSA* rsa;
	cin.get();
	bigint p("A953B1DA8ED8AF6B4560B4DFE2E3B3B530ACE4F791D12BECA07CBCD62AE075C9A97036C05E9A77AE4E6DCAA3018D6B9E0B3EAD3E052BD3EE7DC00F5393A1254B");
	bigint q("93ED4D2E4D4F5F9EE6CFB9F235F52CC76A68A33C03D395E7DB9CA923554AA23F709F1597FAB3C7353E0EA16C9B37F03B3B87333FD93E25DCDCBB1A05BBE6F393");
	cout << "p:";
	rsa = new RSA(p, q);
	while (i != 0)
	{

			if (i == 1) {
			cout << "���������ģ�" << endl;
			string m;
			getline(cin, m);
			rsa->encode(m);
			rsa->encode_show();
		}
		else{
			cout << "����������(hex)��" << endl;
			cin.ignore();
			string c;
			getline(cin, c);
			rsa->decode(c);
			rsa->decode_show();
		}

		cout << "����1���ܣ�2����" << endl;
		cin >> i;
	}
}