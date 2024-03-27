/*
一元二次方程式為 ax^2 + bx + c = 0，輸入整數係數 a, b, c,
求方程式的兩個實根或虛根。

求兩實根公式:
第一個方程式的根 x1
若x1為實根，x1= ((-b) + sqrt(b * b - 4 * a * c)) / (2 * a)
若x1為虛根，x1= ( -b ) / ( 2 * a ) + ( sqrt( -1 * ( b * b - 4 * a * c )) / ( 2 *
a ))i=實部+虛部i

第二個方程式的根 x2
若x2為實根，x2= ((-b) - sqrt(b * b - 4 * a * c)) / (2 * a)
若x2為虛根，x2=( -b ) / ( 2 * a ) - ( sqrt( -1 * ( b * b - 4 * a * c )) / ( 2 *
a ))i=實部+虛部i

【輸入說明】
第一行:輸入整數係數a
第二行:輸入整數係數b
第三行:輸入整數係數c

【輸出說明】
第一行:輸出第一個方程式的根 x1
若x1為實根，四捨五入輸出到小數點第1位
若x1為虛根，輸出實部+虛部i。實部和虛部各四捨五入到小數點第1位
第二行:輸出第二個方程式的根 x2
若x2為實根，四捨五入輸出到小數點第1位
若x2為虛根，輸出實部+虛部i。實部和虛部各四捨五入到小數點第1位
*/

#include <math.h>
#include <stdio.h>

int main() {
  int a, b, c;
  float x1_real, x1_imaginary, x2_real, x2_imaginary;
  float discriminant;

  scanf("%d", &a);
  scanf("%d", &b);
  scanf("%d", &c);

  discriminant = b * b - 4 * a * c;

  if (discriminant >= 0) {
    // 實根
    x1_real = ((-b) + sqrt(discriminant)) / (2 * a);
    x2_real = ((-b) - sqrt(discriminant)) / (2 * a);
    x1_imaginary = x2_imaginary = 0;
  } else {
    // 虛根
    x1_real = x2_real = (float)(-b) / (float)(2 * a);
    x1_imaginary = sqrt(-discriminant) / (2 * a);
    x2_imaginary = -x1_imaginary;
  }

  float x1_real_rounded = round(x1_real * 10) / 10;
  float x2_real_rounded = round(x2_real * 10) / 10;
  float x1_imaginary_rounded = round(x1_imaginary * 10) / 10;
  float x2_imaginary_rounded = round(x2_imaginary * 10) / 10;

  if (discriminant >= 0) {
    printf("%.1f\n", x1_real_rounded);
    printf("%.1f\n", x2_real_rounded);
  } else {
    // 處理虛部的正負號
    char sign1 = (x1_imaginary_rounded >= 0) ? '+' : '-';
    char sign2 = (x2_imaginary_rounded >= 0) ? '+' : '-';

    printf("%.1f%c%.1fi\n", x1_real_rounded, sign1, fabs(x1_imaginary_rounded));
    printf("%.1f%c%.1fi\n", x2_real_rounded, sign2, fabs(x2_imaginary_rounded));
  }

  return 0;
}