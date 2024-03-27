/*
011 進制轉換

在此題目中，您將要求將一個 M 進制的數字轉換為 N
進制的數字。例如，將一個八進制（基數為 8）數字轉換為二進制（基數為
2）或十進制（基數為 10）數字。

你需要寫一個程式，這個程式接受用戶輸入的 M 進制數字，並將其轉換為 N
進制的數字。輸入和輸出的數字應該以字符串的形式表示。請注意，輸入的數字可能包含字母
A 到 Z，代表十進制數字 10 到 35。

進制轉換方式:
12進制(12AB)轉10進制=>
10進制值為:12^3*1+12^2*2+12^1*10+12^0*11=2147

10進制(19)轉2進制=>
第一位:19%2=1, 10進制數值整除2等於9
第二位:9%2=1, 10進制數值整除2等於4
第三位:4%2=0, 10進制數值整除2等於2
第四位:2%2=0, 10進制數值整除2等於1
第五位:1%2=1, 1<2, 所以不再除以2
由最高位輸出到最低位為:10011

【輸入說明】
第一行輸入M進制 (2<=M<=36)
第二行輸入M進制的數值(1<=數值長度<=10)
第三行輸入要轉換成什麼N進制 (2<=N<=36)

範例輸入說明:
Sample Input:
13 (M=13，輸入為13進制)
A45C (13進制的數值為A45C)
8 (N=8，轉換成8進制)

【輸出說明】
第一行輸出進制轉換完的結果，從最高位輸出到最低位

範例輸出說明:
54303
(13進制先轉換成10進制=>13^3*10+13^2*4+13^1*5+13^0*12=22723
10進制再轉換成8進制=>
第一位:22723%8=3, 10進制數值整除8等於2840
第二位:2840%8=0, 10進制數值整除8等於355
第三位:355%8=3, 10進制數值整除8等於44
第四位:44%8=4, 10進制數值整除8等於5
第五位:5%8=5, 5<8, 所以不再除以8
由最高位輸出到最低位為:54303)

【測試資料一】
輸入：
20
ABC8EE
7

輸出：
560541504

【測試資料二】
輸入：
35
C1230
35

輸出：
C1230

【測試資料三】
輸入：
25
12DD34
30

輸出：
D8DGO

【測試資料四】
輸入：
32
FFF59C
2

輸出：
11110111101111001010100101100

【測試資料五】
輸入：
9
0
12

輸出：
0

*/

#include <math.h>
#include <stdio.h>
#include <string.h>

int convertToDecimal(char input[], int M);
void convertToN(int decimal, int N);

int main() {
  int M, N;
  char input[11];
  scanf("%d", &M);
  getchar(); // 換行符號
  scanf("%s", input);
  scanf("%d", &N);

  int decimalDigits = convertToDecimal(input, M);
  convertToN(decimalDigits, N);

  return 0;
}

int convertToDecimal(char input[], int M) {
  int sum = 0;
  int len = strlen(input);
  for (int i = 0; i < len; i++) {
    if (input[len - i - 1] >= 48 && input[len - i - 1] <= 57) {
      sum += (input[len - i - 1] - 48) * pow(M, i);
    } else {
      sum += (input[len - i - 1] - 55) * pow(M, i);
    }
  }
  return sum;
}

void convertToN(int decimal, int N) {
  char remainder[50];
  int divisor = decimal, len = 0, temp = 0;

  while (1) {
    if (divisor < N) {
      if (divisor <= 9 && divisor >= 0)
        remainder[len] = divisor + 48;
      else
        remainder[len] = divisor + 55;
      break;
    }
    temp = divisor % N;
    if (temp <= 9 && temp >= 0) { // 0~9
      remainder[len] = temp + 48;
    } else { // A~Z
      remainder[len] = temp + 55;
    }
    divisor = divisor / N;

    len++;
  }

  for (int i = len; i >= 0; i--) {
    printf("%c", remainder[i]);
  }
}
