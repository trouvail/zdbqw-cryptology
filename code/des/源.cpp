#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
using namespace std;

bitset<64> key;
bitset<48> sonKey[16]; 
int HexToBit[16][4] = { {0,0,0,0},{0,0,0,1},{0,0,1,0},{0,0,1,1},{0,1,0,0},{0,1,0,1},{0,1,1,0},{0,1,1,1},{1,0,0,0},{1,0,0,1},{1,0,1,0},{1,0,1,1},{1,1,0,0},{1,1,0,1},{1,1,1,0},{1,1,1,1} };
void getbit(string a, bitset<64>& temp)
{
	int num = 63;
	for (int i = 2; i < a.length(); i++)
	{
		if (a[i] <= '9')
		{
			for (int j = 0; j < 4; j++)
			{
				temp[num--] = HexToBit[a[i] - 48][j];
			}
		}
		else
		{
			for (int j = 0; j < 4; j++)
			{
				temp[num--] = HexToBit[a[i] - 65 + 10][j];
			}
		}
	}
}
void getHex(bitset<64> b,string &s) 
{
	s[0] = '0';
	s[1] = 'x';
	int num = 2;
	for (int i = 63; i >= 0; i-=4)
	{
		int a = b[i] * 8 + b[i - 1] * 4 + b[i - 2] * 2 + b[i - 3];
		if (a > 9)
			s[num++] = 'A' + a - 10;
		else
			s[num++] = '0' + a;
	}
}
int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2,
			60, 52, 44, 36, 28, 20, 12, 4,
			62, 54, 46, 38, 30, 22, 14, 6,
			64, 56, 48, 40, 32, 24, 16, 8,
			57, 49, 41, 33, 25, 17, 9,  1,
			59, 51, 43, 35, 27, 19, 11, 3,
			61, 53, 45, 37, 29, 21, 13, 5,
			63, 55, 47, 39, 31, 23, 15, 7 };

int IP_1[] = { 40, 8, 48, 16, 56, 24, 64, 32,
			  39, 7, 47, 15, 55, 23, 63, 31,
			  38, 6, 46, 14, 54, 22, 62, 30,
			  37, 5, 45, 13, 53, 21, 61, 29,
			  36, 4, 44, 12, 52, 20, 60, 28,
			  35, 3, 43, 11, 51, 19, 59, 27,
			  34, 2, 42, 10, 50, 18, 58, 26,
			  33, 1, 41,  9, 49, 17, 57, 25 };


int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

int PC_1[] = { 57, 49, 41, 33, 25, 17, 9,
			   1, 58, 50, 42, 34, 26, 18,
			  10,  2, 59, 51, 43, 35, 27,
			  19, 11,  3, 60, 52, 44, 36,
			  63, 55, 47, 39, 31, 23, 15,
			   7, 62, 54, 46, 38, 30, 22,
			  14,  6, 61, 53, 45, 37, 29,
			  21, 13,  5, 28, 20, 12,  4 };


int PC_2[] = { 14, 17, 11, 24,  1,  5,
			   3, 28, 15,  6, 21, 10,
			  23, 19, 12,  4, 26,  8,
			  16,  7, 27, 20, 13,  2,
			  41, 52, 31, 37, 47, 55,
			  30, 40, 51, 45, 33, 48,
			  44, 49, 39, 56, 34, 53,
			  46, 42, 50, 36, 29, 32 };


//扩展运算E
int E[] = { 32,  1,  2,  3,  4,  5,
			4,  5,  6,  7,  8,  9,
			8,  9, 10, 11, 12, 13,
		   12, 13, 14, 15, 16, 17,
		   16, 17, 18, 19, 20, 21,
		   20, 21, 22, 23, 24, 25,
		   24, 25, 26, 27, 28, 29,
		   28, 29, 30, 31, 32,  1 };
// 置换P
int P[] = { 16,  7, 20, 21,
		   29, 12, 28, 17,
			1, 15, 23, 26,
			5, 18, 31, 10,
			2,  8, 24, 14,
		   32, 27,  3,  9,
		   19, 13, 30,  6,
		   22, 11,  4, 25
};

int S_BOX[8][4][16] = {
	{
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	},
	{
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
	},
	{
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
	},
	{
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
	},
	{
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
	},
	{
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
	},
	{
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
	},
	{
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
	}
};





 
//进行左移

bitset<28> leftShift(bitset<28> k, int shift)
{
	bitset<28> tmp = k;
	for (int i = 27; i >= 0; --i)
	{
		if (i - shift < 0)
			k[i] = tmp[i - shift + 28];
		else
			k[i] = tmp[i - shift];
	}
	return k;
}


void getKeys()
{
	bitset<28> high;
	bitset<28> low;


	/*
	我们本应先去掉奇偶校验位，但我们发现PC_1的表中已经不含这些奇偶校验位了，所以我们可以把第一个步骤略过。
	int PC_1[] = { 57, 49, 41, 33, 25, 17, 9,
			   1, 58, 50, 42, 34, 26, 18,
			  10,  2, 59, 51, 43, 35, 27,
			  19, 11,  3, 60, 52, 44, 36,
			  63, 55, 47, 39, 31, 23, 15,
			   7, 62, 54, 46, 38, 30, 22,
			  14,  6, 61, 53, 45, 37, 29,
			  21, 13,  5, 28, 20, 12,  4 };*/
	bitset<56> firstKey;
	for (int i = 0; i < 56; i++)
	{
		firstKey[55 - i] = key[64 - PC_1[i]];
	}
	// 生成子密钥，保存在 subKeys[16] 中
	for (int rd = 0; rd < 16; rd++)
	{
		// 前28位与后28位
		for (int i = 28; i < 56; i++)
		{
			high[i - 28] = firstKey[i];
		}
		for (int i = 0; i < 28; i++)
		{
			low[i] = firstKey[i];
		}
		// 左移
		high = leftShift(high, shiftBits[rd]);
		low = leftShift(low, shiftBits[rd]);

		for (int i = 28; i < 56; i++)
		{
			firstKey[i] = high[i - 28];
		}
		for (int i = 0; i < 28; i++)
		{
			firstKey[i] = low[i];
		}
		bitset<48> zipKey;
		// 压缩置换，56位到48位
		for (int i = 0; i < 48; i++)
		{
			zipKey[47 - i] = firstKey[56 - PC_2[i]];
		}
		sonKey[rd] = zipKey;
	}
}


//f 函数是多个置换函数和替代函数的组合函数，它将32位比特的输入变换为32位的输出，
/*int E[] = { 32,  1,  2,  3,  4,  5,
			4,  5,  6,  7,  8,  9,
			8,  9, 10, 11, 12, 13,
		   12, 13, 14, 15, 16, 17,
		   16, 17, 18, 19, 20, 21,
		   20, 21, 22, 23, 24, 25,
		   24, 25, 26, 27, 28, 29,
		   28, 29, 30, 31, 32,  1 };*/
bitset<32> f(bitset<32> R, bitset<48> k)
{
	int temp = 0;
	//用于计数组成新32位
	bitset<48> expandR;
	// 我们根据表对应关系，扩展为48位
	for (int i = 0; i < 48; ++i)
		expandR[47 - i] = R[32 - E[i]];
	// 第二步：异或运算
	expandR = expandR ^ k;
	// 第三步：查找S_BOX置换表，分成8组，每个6位，其中最高位与最低位组成行号，剩下4位组成列号
	bitset<32> output;
	for (int i = 0; i < 48; i = i + 6)
	{
		int row = expandR[47 - i] * 2 + expandR[47 - i - 5];
		int col = expandR[47 - i - 1] * 8 + expandR[47 - i - 2] * 4 + expandR[47 - i - 3] * 2 + expandR[47 - i - 4];
		int num = S_BOX[i / 6][row][col];
		bitset<4> binary(num);
		output[31 - temp] = binary[3];
		output[31 - temp - 1] = binary[2];
		output[31 - temp - 2] = binary[1];
		output[31 - temp - 3] = binary[0];
		temp += 4;
	}
	/* 第四步：P-置换
	int P[] = { 16,  7, 20, 21,
		   29, 12, 28, 17,
			1, 15, 23, 26,
			5, 18, 31, 10,
			2,  8, 24, 14,
		   32, 27,  3,  9,
		   19, 13, 30,  6,
		   22, 11,  4, 25
};
	*/
	bitset<32> tmp = output;
	for (int i = 0; i < 32; ++i)
		output[31 - i] = tmp[32 - P[i]];
	return output;
}


/**
 *  DES加密
 */
bitset<64> getSecret(bitset<64>& origin)
{
	bitset<64> secret;
	bitset<64> firstInput;
	bitset<32> high;
	bitset<32> low;

	// 初始置换IP
	for (int i = 0; i < 64; i++)
		firstInput[63 - i] = origin[64 - IP[i]];
	// 一分为二
	for (int i = 32; i < 64; i++)
		high[i - 32] = firstInput[i];
	for (int i = 0; i < 32; i++)
		low[i] = firstInput[i];
	// 迭代
	for (int round = 0; round < 16; round++)
	{
		bitset<32> nextHigh;
		nextHigh = low;
		low = high ^ f(low, sonKey[round]);
		high = nextHigh;
	}
	// 合并注意高位和低位发生了调换
	for (int i = 0; i < 32; i++)
	{
		secret[i] = high[i];
		secret[i+32] = low[i];
	}
	// 结尾置换IP-1
	firstInput = secret;
	for (int i = 0; i < 64; i++)
		secret[63 - i] = firstInput[64 - IP_1[i]];
	return secret;
}

/**
 *  DES解密
 */
bitset<64> getOrigin(bitset<64>& secret)
{
	bitset<64> origin;
	bitset<64> firstInput;
	bitset<32> high;
	bitset<32> low;

	// 初始置换IP
	for (int i = 0; i < 64; i++)
		firstInput[63 - i] = secret[64 - IP[i]];
	// 一分为二
	for (int i = 32; i < 64; i++)
		high[i - 32] = firstInput[i];
	for (int i = 0; i < 32; i++)
		low[i] = firstInput[i];
	// 迭代（逆序应用）
	bitset<32> nextHigh;
	for (int round = 0; round < 16; round++)
	{
		nextHigh = low;
		low = high ^ f(low, sonKey[15 - round]);
		high = nextHigh;
	}
	// 合并注意高位和低位发生了调换
	for (int i = 0; i < 32; i++)
	{
		origin[i] = high[i];
		origin[i+32] = low[i];
	}
	// 结尾置换IP-1
	firstInput = origin;
	for (int i = 0; i < 64; i++)
		origin[63 - i] = firstInput[64 - IP_1[i]];
	return origin;
}

int main() {
	bitset<64> result;
	bitset<64> origin;
	bitset<64> first;
	string s[10] = { "0x0000000000000000","0x95F8A5E5DD31D900","0xDD7F121CA5015619" };
	//明文
	string k[10] = { "0x10316E028C8F3B4A", "0x0101010101010101","0x0101010101010101" };
	//秘钥
	string final[10] = { "0x82DCBAFBDEAB6602","0x8000000000000000","0x4000000000000000" };
	//正确结果
	cout << "输入0检测雪崩，输入1加密，输入2解密" << endl;
	int a;
	cin >> a;
	if (a == 0)
	{

		int num = 0;
		string a = "0x95F8A5E5DD31D900";
		//明文
		string b = "0x0101010103010101";
		//秘钥
		string c = "0x8000000000000000";
		//正确结果

		getbit(a, origin);
		getbit(c, first);
		getbit(b, key);
		// 生成16个子密钥
		getKeys();
		// 密文写入 a.txt
		result = getSecret(origin);

		cout << "原始结果" << first << endl << "改后结果" << result << endl;
		for (int i = 0; i < 64; i++)
		{
			if (first[i] != result[i])
				num++;
		}
		cout << num;

	}
	else if (a == 1) {
		for (int i = 0; i < 3; i++) {
			cout << "加密过程" << endl;
			cout << "明文： " << s[i] << endl << "秘钥： " << k[i] << endl << "正确结果：" << final[i] << endl;
			bitset<64> origin;
			getbit(s[i], origin);
			getbit(k[i], key);
			// 生成16个子密钥
			getKeys();
			// 密文写入 a.txt
			bitset<64> result = getSecret(origin);
			getHex(result, k[i]);
			cout << "加密结果：" << k[i] << endl;
		}
	}
	else

	{
		cout << "解密过程" << endl;
		for (int i = 0; i < 3; i++) {
			cout << "密文： " << final[i] << endl << "秘钥： " << k[i] << endl << "正确结果：" << s[i] << endl;
			bitset<64> secret;
			getbit(final[i], secret);
			getbit(k[i], key);
			// 生成16个子密钥
			getKeys();
			// 密文写入 a.txt
			result = getOrigin(secret);
			getHex(result, k[i]);
			cout << "解密结果：" << k[i] << endl;
		}
	}

}

/*
		cout << "解密过程" << endl;
		s = "0x8000000000000000";
		//密文
		k = "0x0101010101010101";
		//秘钥
		final = "0x95F8A5E5DD31D900";
		//正确结果
		cout << "密文： " << s << endl << "秘钥： " << k << endl << "正确结果：" << final << endl;
		bitset<64> secret;
		getbit(s, secret);
		getbit(k, key);
		// 生成16个子密钥
		getKeys();
		// 密文写入 a.txt
		result = getOrigin(secret);
		getHex(result, k);
		cout << "加密结果：" << k;
	}

}*/
