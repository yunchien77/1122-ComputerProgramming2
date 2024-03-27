/*
13. 直線方程式

給定平面上兩個點，求直線方程式 y = mx + b，
m = (y1 - y2) / (x1 - x2)
b = (x2 * y1 - x1 * y2) / (x2 - x1)

分數表示格式:
真分數或假分數: 分子/分母

【注意事項】
輸出格式: y = mx + b
1. 若x項係數 m 為 1時，輸出格式應為 y = x + b ， 而不是 y = 1x + b
2. 若x項係數 m 為 -1時，輸出格式應為 y = -x + b ， 而不是 y = -1x + b
3. 若x項係數 m 為 0且b > 0時，輸出格式應為 y = b
4. 若x項係數 m 為 0且b < 0時，輸出格式應為 y = -b
5. 若m, b項為分數，需化為最簡分數再輸出
6. 若m, b項為分數且其分母為1，需化為整數再輸出

【輸入說明】
輸入說明:
第一行輸入一正整數 N (1 <= N <= 5)，代表其後有多少筆輸入測資。
第二行輸入平面上兩個點座標位置x1, y1, x2, y2 ( -20 <= x1, y1, x2, y2 <=
20)，以空格符號隔開，座標以整數表示 其後N - 1行，跟第二行輸入格式相同。

範例輸入說明:
2 (接下會輸入兩行各兩個座標)
-2 0 0 3 (x1=-2, y1=0, x2=0, y2=3)
2 1 7 2 (x1=2, y1=1, x2=7, y2=2)


【輸出說明】
輸出格式為 y = mx + b，且m, b的值須化為最簡分數，
若 m 或 b 為 0，則那一項不輸出

範例輸出說明
y = 3/2x + 3 (m = (0-3)/(-2-0) = 3/2, b = (0*0-(-2)*3)/(-2-0) = 3)
y = 1/5x + 3/5 (m = (2-1)/(7-2) = 1/5, b = (7*1-2*2)/(7-2) = 3/5)

【測試資料一】
輸入：
5
2 -2 7 2
1 3 5 -3
5 2 -3 -2
3 1 -1 4
5 10 -3 10

輸出：
y = 4/5x - 18/5
y = -3/2x + 9/2
y = 1/2x - 1/2
y = -3/4x + 13/4
y = 10

【測試資料二】
輸入：
5
0 2 1 3
0 -1 2 -3
-2 -5 1 4
3 -6 -4 8
-1 -1 -6 -4

輸出：
y = x + 2
y = -x - 1
y = 3x + 1
y = -2x
y = 3/5x - 2/5

【測試資料三】
輸入：
3
6 -2 3 4
8 -2 -3 9
3 -12 -5 7

輸出：
y = -2x + 10
y = -x + 6
y = -19/8x - 39/8

【測試資料四】
輸入：
5
-5 5 -2 2
-6 -5 2 -5
1 -5 3 -3
2 -5 -2 11
2 1 7 2

輸出：
y = -x
y = -5
y = x - 6
y = -4x + 3
y = 1/5x + 3/5

*/

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);
void simplify(int *numerator, int *denominator);

int main() {
  int N, x1, y1, x2, y2;
  int mu, md, bu, bd;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    mu = y1 - y2;
    md = x1 - x2;
    simplify(&mu, &md);

    bu = x2 * y1 - x1 * y2;
    bd = x2 - x1;
    simplify(&bu, &bd);

    // m = 0
    if (mu == 0 || md == 0) {
      if (bu > 0) {
        if (bd == 1)
          printf("y = %d\n", bu);
        else
          printf("y = %d/%d\n", bu, bd);
      } else if (bu < 0) {
        if (bd == 1)
          printf("y = %d\n", bu);
        else
          printf("y = -%d/%d\n", bu, bd);
      } else {
        printf("y = 0\n");
      }
    }
    // m != 0, m為integer
    else if (md == 1) {
      if (mu == 1) {
        if (bd == 1) {
          if (bu > 0)
            printf("y = x + %d\n", bu);
          else
            printf("y = x - %d\n", abs(bu));
        } else {
          if (bd == 0 || bu == 0)
            printf("y = x\n");
          else {
            if (bu > 0)
              printf("y = x + %d/%d\n", bu, bd);
            else
              printf("y = x - %d/%d\n", abs(bu), bd);
          }
        }
      } else if (mu == -1) {
        if (bd == 1) {
          if (bu > 0)
            printf("y = -x + %d\n", bu);
          else if (bu < 0)
            printf("y = -x - %d\n", abs(bu));
          else
            printf("y = -x\n");
          ;
        } else {
          if (bd == 0 || bu == 0)
            printf("y = -x\n");
          else {
            if (bu > 0)
              printf("y = -x + %d/%d\n", bu, bd);
            else
              printf("y = -x - %d/%d\n", abs(bu), bd);
          }
        }
      } else {
        if (bd == 0 || bu == 0)
          printf("y = %dx\n", mu);
        else if (bd == 1) {
          if (bu > 0)
            printf("y = %dx + %d\n", mu, bu);
          else
            printf("y = %dx - %d\n", mu, abs(bu));
        } else {
          if (bu > 0)
            printf("y = %dx + %d/%d\n", mu, bu, bd);
          else
            printf("y = %dx - %d/%d\n", mu, abs(bu), bd);
        }
      }
    } else { // m != 0, m為分數
      if (bd == 1)
        printf("y = %d/%dx + %d\n", mu, md, bu);
      else {
        if (bu > 0)
          printf("y = %d/%dx + %d/%d\n", mu, md, bu, bd);
        else
          printf("y = %d/%dx - %d/%d\n", mu, md, abs(bu), bd);
      }
    }
  }
  return 0;
}

int gcd(int a, int b) {
  if (b == 0) {
    if (a < 0) { // 若最大公因數為負數，則傳回絕對值
      a = (-1) * a;
    }
    return a;
  } else {
    return gcd(b, a % b);
  }
}

void simplify(int *numerator, int *denominator) {
  int common = gcd(*numerator, *denominator);
  if (*denominator < 0) { // 分母為負數的情況
    common *= -1;
  }
  *numerator = *numerator / common;
  *denominator = *denominator / common;
}