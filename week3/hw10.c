/*
10. 分數運算

給定兩個分數和一個運算符號，請依據題目給定的分數與運算符號進行分數運算
請輸出計算後的結果，需化為最簡分數，且分子不可大於分母，需化為帶分數
最簡分數定義: 分子和分母互質

分數表示格式:
真分數或假分數: 分子/分母
帶分數: 整數(分子/分母)

【輸入說明】
輸入說明:
第一行輸入第一個分數
第二行輸入所做運算，加減乘除分別為+ 、 - 、 * 、 /
第三行輸入第二個分數
第四行輸入是否繼續運算: y代表繼續 n代表結束
當繼續運算時，重複第一到第四行輸入

範例輸入說明:
1(3/4) (第一個分數的整數為1、分子為3、分母為4)
+ (運算為加)
1/2 (第二個分數的整數為0、分子為1、分母為2)
n (結束)

【輸出說明】
輸出計算結果，結果分數須化為最簡分數
若輸入分數的分母為0，或是運算結果分數的分母為0，輸出 error
若計算結果為假分數, 需轉化為帶分數格式輸出
帶分數格式: 整數(分子/分母)
若計算結果為整數，則只需輸出整數
若計算結果為負真分數，需在分子前面輸出負號
若計算結果為負帶分數為，在整數前面輸出負號
若計算結果為 0, 輸出 0

範例輸出說明
2(1/4) (兩個分數相加的結果化成帶分數，整數為2、分子為1、分母為4)

【測試資料一】
輸入：
1/2
-
1/2
y
9/2
*
15/3
y
5/0
/
3/2
n

輸出：
0
22(1/2)
error

【測試資料二】
輸入：
6(5/17)
*
2(13/5)
y
-1(7/13)
+
1(5/3)
y
-1(13/3)
*
15/13
n

輸出：
28(81/85)
1(5/39)
-6(2/13)

【測試資料三】
輸入：
6(7/8)
/
0/8
y
3(3/11)
-
-2(5/22)
y
1/3
-
1/2
y
1/2
+
1/3
n

輸出：
error
5(1/2)
-1/6
5/6
*/

#include <stdio.h>
#include <stdlib.h>

void addFractions(int num1, int den1, int num2, int den2, int *result_num,
                  int *result_den);
void subtractFractions(int num1, int den1, int num2, int den2, int *result_num,
                       int *result_den);
void multiplyFractions(int num1, int den1, int num2, int den2, int *result_num,
                       int *result_den);
void divideFractions(int num1, int den1, int num2, int den2, int *result_num,
                     int *result_den);
// 輾轉相除法求最大公因數
int gcd(int a, int b);
// 簡化分數
void simplify(int *numerator, int *denominator);
// 分數轉帶分數形式
int transferFractions(int *num, int *den);

int main() {
  // numerator分子; denominator分母
  int int1, num1, den1, int2, num2, den2;
  char operation, choice;

  int temp_int;
  char temp_char;

  int result_num, result_den;

  do {
    // 第一個分數
    // 判讀前兩個輸入
    scanf("%d%c", &temp_int, &temp_char);
    // 帶分數
    if (temp_char == '(') {
      int1 = temp_int;
      scanf("%d/%d)", &num1, &den1);
      // 轉成分數形式
      if (int1 < 0) {
        num1 = (int1 * den1) - num1;
      } else {
        num1 = (int1 * den1) + num1;
      }
    }
    // 分數
    else {
      int1 = 0;
      num1 = temp_int;
      scanf("%d", &den1);
    }

    // 輸入運算子
    getchar();
    scanf("%c", &operation);

    // 第二個分數
    scanf("%d%c", &temp_int, &temp_char);
    if (temp_char == '(') {
      int2 = temp_int;
      scanf("%d/%d)", &num2, &den2);
      if (int2 < 0) {
        num2 = (int2 * den2) - num2;
      } else {
        num2 = (int2 * den2) + num2;
      }
    } else {
      int2 = 0;
      num2 = temp_int;
      scanf("%d", &den2);
    }

    if (den1 == 0 || den2 == 0) {
      printf("error\n");
    } else {
      switch (operation) {
      case '+':
        addFractions(num1, den1, num2, den2, &result_num, &result_den);
        break;
      case '-':
        subtractFractions(num1, den1, num2, den2, &result_num, &result_den);
        break;
      case '*':
        multiplyFractions(num1, den1, num2, den2, &result_num, &result_den);
        break;
      case '/':
        divideFractions(num1, den1, num2, den2, &result_num, &result_den);
        break;
      default:
        printf("Invalid operation\n");
      }

      if (result_den == 0) {
        printf("error\n");
      } else if (result_num == 0) {
        printf("0\n");
      } else if (result_den == 1) { // 運算結果為整數
        printf("%d\n", result_num);
      } else {
        // 判斷是否是帶分數
        if (result_num >= result_den && result_num > 0 && result_den > 0) {
          int result_int = transferFractions(&result_num, &result_den);
          printf("%d(%d/%d)\n", result_int, result_num, result_den);
        } else if (result_num * (-1) >= result_den) {
          result_num = result_num * (-1);
          int result_int_neg = transferFractions(&result_num, &result_den);
          printf("-%d(%d/%d)\n", result_int_neg, result_num, result_den);
        } else {
          printf("%d/%d\n", result_num, result_den);
        }
      }
    }
    // y/n
    getchar();
    scanf("%c", &choice);
  } while (choice == 'y');
  return 0;
}

void addFractions(int num1, int den1, int num2, int den2, int *result_num,
                  int *result_den) {
  *result_den = den1 * den2; // 分母相乘
  *result_num = num1 * den2 + num2 * den1;
  // 簡化分數
  simplify(result_num, result_den);
}
void subtractFractions(int num1, int den1, int num2, int den2, int *result_num,
                       int *result_den) {
  *result_den = den1 * den2; // 分母相乘
  *result_num = num1 * den2 - num2 * den1;
  // 簡化分數
  simplify(result_num, result_den);
}
void multiplyFractions(int num1, int den1, int num2, int den2, int *result_num,
                       int *result_den) {
  *result_den = den1 * den2; // 分母相乘
  *result_num = num1 * num2;
  // 簡化分數
  simplify(result_num, result_den);
}
void divideFractions(int num1, int den1, int num2, int den2, int *result_num,
                     int *result_den) {
  *result_den = den1 * num2;
  *result_num = num1 * den2;
  // 簡化分數
  simplify(result_num, result_den);
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
  *numerator = *numerator / common;
  *denominator = *denominator / common;
}
int transferFractions(int *num, int *den) {
  int temp_int = *num / *den;
  *num = *num - *den * temp_int;
  return temp_int;
}