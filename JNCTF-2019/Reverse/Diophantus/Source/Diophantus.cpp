#include <iostream>
#include "AES.h"
#include "Base64.h"
using namespace std;
string flag="XCXEF6sntCBiaKJIWaAuPERHaHRy5vuU2NmLMqBkuww=";
string EncryptionAES(const string& strSrc,char *&g_key)
{
       const char * g_iv="aaaaaaaaaaaaaaaa";
       size_t length = strSrc.length();
       int block_num = length / BLOCK_SIZE + 1;
       //明文
       char* szDataIn = new char[block_num * BLOCK_SIZE + 1];
       memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);
       strcpy(szDataIn, strSrc.c_str());
  
       //进行PKCS7Padding填充。
       int k = length % BLOCK_SIZE;
       int j = length / BLOCK_SIZE;
       int padding = BLOCK_SIZE - k;
       for (int i = 0; i < padding; i++)
       {
              szDataIn[j * BLOCK_SIZE + k + i] = padding;
       }
       szDataIn[block_num * BLOCK_SIZE] = '\0';
  
       //
       char *szDataOut = new char[block_num * BLOCK_SIZE + 1];
       memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);
  
       //进行进行AES的CBC模式
       AES aes;
       aes.MakeKey(g_key, g_iv, 16, 16);
       aes.Encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, AES::CBC);
       string str = base64_encode((unsigned char*) szDataOut,
                     block_num * BLOCK_SIZE);
       delete[] szDataIn;
       delete[] szDataOut;
       return str;
}
string DecryptionAES(const string& strSrc,char* &g_key) //AES解密
{
       AES aes;
       const char* g_iv="aaaaaaaaaaaaaaaa";
       string strData = base64_decode(strSrc);
       size_t length = strData.length();
       //密文
       char *szDataIn = new char[length + 1];
       memcpy(szDataIn, strData.c_str(), length+1);
       //明文
       char *szDataOut = new char[length + 1];
       memcpy(szDataOut, strData.c_str(), length+1);
  
       //进行AES的CBC模式解密

       aes.MakeKey(g_key, g_iv, 16, 16);
       aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);
  
       //去PKCS7Padding填充
       if (0x00 < szDataOut[length - 1] <= 0x16)
       {
              int tmp = szDataOut[length - 1];
              for (int i = length - 1; i >= length - tmp; i--)
              {
                     if (szDataOut[i] != tmp)
                     {
                            memset(szDataOut, 0, length);
                            cout << "error" << endl;
                            break;
                     }
                     else
                            szDataOut[i] = 0;
              }
       }
       string strDest(szDataOut);
       delete[] szDataIn;
       delete[] szDataOut;
       return strDest;
}

int main(void){
    __int64_t x;
    __int64_t y;
    scanf("%lld",&x);
    scanf("%lld",&y);
    __int128_t xx;
    __int128_t yy;
    xx=x*x;
    yy=7*y*y;
    int result=xx-yy;
    __int128_t key;
    __int64_t keys[2]={x,y};
    char *key2=(char *)keys;
    if(result==8&&x>0x100000000000000&&x<0x1000000000000000&&y>0x100000000000000){
    	string output = DecryptionAES(flag,key2);
    	cout << "Here is your flag:" << output << endl;  
	}else{
		cout << "Sorry, Try again" << endl;
	}
    return 0;
}
