/*
1. BMI

給定一身高 h (公分) 及體重 w (公斤)，請計算出BMI數值。

BMI公式:
BMI = 體重(公斤) / (身高*身高)(公尺)


注意: 請使用題目提供的公式計算，避免小數計算答案不精確

【輸入說明】
第一行輸入一個整數 w (20 <= w <= 100)，代表體重的公斤數。
第二行輸入一個整數 h (100 <= h <= 200)，代表身高的公分數。

範例輸入說明:
85 (體重為85)
177 (身高為177)

【輸出說明】
輸出BMI數值，結果四捨五入到小數點後第一位。

範例輸出說明:
27.1 (BMI=85/(1.77 * 1.77)，BMI為27.131413，且取到小數的第1位)

【測試資料一】
輸入：
60
172

輸出：
20.3

【測試資料二】
輸入：
86
197

輸出：
22.2

【測試資料三】
輸入：
100
149

輸出：
45.0

【測試資料四】
輸入：
39
147

輸出：
18.0

【測試資料五】
輸入：
25
122

輸出：
16.8

*/
#include <stdio.h>

int main() {
  int w, h;
  float bmi;
  scanf("%d", &w);
  scanf("%d", &h);

  bmi = (float)w / ((float)h / 100 * (float)h / 100);
  printf("%.1f\n", bmi);

  return 0;
}