/*
016 反序

考慮一個數列 A = (a[1], a[2], a[3], ..., a[n] )。如果 A中兩個數a[i]和 a[j]滿足 i
< j 且 a[i]> a[j],則說 (a[i], a[j])是 A中的一個反序
(inversion)。定義W(A)為數列A中反序數量。例如,在數列 A = (3, 1, 9, 8, 9,
2)中,共有 (3, 1)、(3, 2)、(9, 8)、(9, 2)、(8, 2)、(9, 2) 6個反序 ,所以 W(A) =6。

【輸入說明】
第一行輸入正整數N，(2<=N<=100)
第二行輸入數列一數列，每個數字中間以空白隔開

範例輸入說明:
7 (整數N為7)
4 6 3 1 7 5 1 (輸入的數列為4、6、3、1、7、5、1，中間以空白隔開)

【輸出說明】
第一行輸出符合反序定義的數量

範例輸出說明:
12
((4,3)、(4,1)、(4,1)、(6,3)、(6,1)、(6,5)、(6,1)、(3,1)、(3,1)、(7,5)、(7,1)、(5,1)共12組符合)

【測試資料一】
輸入：
33
13 9 32 22 3 28 11 16 18 12 3 10 5 4 21 17 10 18 15 26 31 5 17 4 17 26 12 24 17
13 3 1 18

輸出：
263

【測試資料二】
輸入：
50
2 4 6 9 11 11 11 11 14 15 18 21 22 25 26 27 27 31 31 34 37 40 41 44 44 48 50 54
55 59 61 61 65 66 67 67 71 74 78 81 84 84 88 90 90 91 94 98 99 103

輸出：
0

【測試資料三】
輸入：
65
998 995 989 987 986 983 983 978 972 966 961 955 953 949 947 947 943 943 941 937
936 930 928 923 919 913 911 909 903 897 896 895 890 889 889 889 889 884 878 876
872 866 866 862 859 856 851 850 848 847 845 845 839 837 831 826 821 815 814 812
806 802 798 797 794

輸出：
2069


【測試資料四】
輸入：
86
0 34 66 69 84 33 36 12 65 81 75 41 29 44 75 29 68 69 12 20 27 81 73 18 11 48 77
15 15 6 19 1 41 78 31 85 18 56 58 2 42 85 84 13 68 46 44 39 68 47 8 11 71 54 9
62 19 47 82 35 69 35 28 73 70 55 69 74 59 55 37 13 45 65 59 46 32 8 14 21 13 11
22 37 84 64

輸出：
1863

【測試資料五】
輸入：
46
23 3 13 12 31 40 32 15 27 28 32 21 8 1 1 32 40 37 42 4 17 27 10 9 18 3 1 44 17 2
10 7 23 22 31 6 29 8 28 5 7 14 30 33 44 31

輸出：
499

【測試資料六】
輸入：
95
78 51 86 44 15 10 60 25 8 82 61 44 41 59 36 34 27 78 33 30 68 17 17 85 59 83 42
33 23 93 47 39 81 32 50 36 38 72 4 2 9 21 87 67 69 35 85 73 46 42 44 23 37 63 35
12 24 79 11 82 57 52 90 13 79 26 11 39 90 0 62 32 29 76 66 14 66 51 39 58 72 55
22 49 21 33 83 30 4 24 89 88 87 94 29

輸出：
2159

*/

#include <stdio.h>
int main() {
  int n = 0, count = 0;
  int input[100] = {0};
  scanf("%d", &n);
  getchar();
  for (int i = 0; i < n; i++) {
    scanf("%d", &input[i]);
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (input[j] < input[i])
        count++;
    }
  }
  printf("%d\n", count);
  return 0;
}