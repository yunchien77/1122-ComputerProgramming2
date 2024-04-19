/*
018 排序演算法1

輸入一數列，將數列小到大排序，輸出使用選擇排序法的比較次數和搬移次數、插入排序法的比較次數和搬移次數，請使用投影片array
P.22 P24提供的範例程式碼。

*注意：
交換1次等於搬移3次
選擇排序法比較次數只計算 d[i] 插入排序法比較次數計算 j>0 和 a[j-1]>target
判斷次數加總
陣列中同一格進行"交換"不計算搬移次數，插入排序法的移到暫存再寫入需要計算
搬移次數2次

【輸入說明】
第一行輸入一正整數N(2 <= N <= 15)，代表數列長度
第一行輸入一數列，每個數字中間以空白隔開

範例輸入說明:
5 (數列長度)
5 3 8 23 15 (輸入數列為5 3 8 23 15，以空白隔開)

【輸出說明】
第一行輸出選擇排序法的比較次數和搬移次數 以空白隔開
第二行輸出插入排序法的比較次數和搬移次數 以空白隔開

範例輸出說明:
10 6
11 9

選擇演算法:
比較次數說明
getMinIndex:
left = 0, right =4, d[i] left = 1, right =4, d[i] left = 2, right =4, d[i] left
= 3, right =4, d[i] 搬移次數說明 selectSort: i = 0, index = 1,
d[i]和d[index]進行交換, 搬移次數3次, d = [3, 5, 8, 23, 15] i = 1, index = 1,
不計算搬移次數, d = [3, 5, 8, 23, 15] i = 2, index = 2, 不計算搬移次數, d = [3,
5, 8, 23, 15] i = 3, index = 4, d[i]和d[index]進行交換, 搬移次數3次, d = [3, 5,
8, 15, 23]

故第一行輸出 10 6 (判斷次數4+3+2+1=10 搬移次數 3+3=6)

插入演算法:
比較次數說明
i = 1, j = 1, a = [5, 3, 8, 23, 15], j>0判斷2次, a[j-1]>target判斷1次
i = 2, j = 2, a = [3, 5, 8, 23, 15], j>0判斷1次, a[j-1]>target判斷1次
i = 3, j = 3, a = [3, 5, 8, 23, 15], j>0判斷1次, a[j-1]>target判斷1次
i = 4, j = 4, a = [3, 5, 8, 23, 15], j>0判斷2次, a[j-1]>target判斷2次

搬移次數說明
i = 1, target = a[i]搬移次數1次, j = 1, a[j] = a[j-1]搬移次數1次, a[j] =
target搬移次數1次, a = [3, 5, 8, 23, 15] i = 2, target = a[i]搬移次數1次, j = 2,
a[j] = target搬移次數1次, a = [3, 5, 8, 23, 15] i = 3, target = a[i]搬移次數1次,
j = 3, a[j] = target搬移次數1次, a = [3, 5, 8, 23, 15] i = 4, target =
a[i]搬移次數1次, j = 4, a[j] = a[j-1]搬移次數1次, a[j] = target搬移次數1次, a =
[3, 5, 8, 15, 23]

故第二行輸出 11 9 (判斷次數2+1+1+1+1+1+2+2=11 搬移次數 1+1+1+1+1+1+1+1+1+1=10)


【測試資料一】
輸入：
8
24 32 18 52 67 60 99 71

輸出：
28 12
21 18


【測試資料二】
輸入：
9
6 34 12 25 20 10 14 53 75

輸出：
36 9
38 27


【測試資料三】
輸入：
11
21 77 81 82 44 12 23 69 53 44 58

輸出：
55 24
75 48


【測試資料四】
輸入：
6
79 59 31 30 22 41

輸出：
15 12
30 22


【測試資料五】
輸入：
11
11 77 42 56 66 89 97 87 74 95 8

輸出：
55 12
59 40


【測試資料六】
輸入：
15
53 11 25 1 40 91 6 31 45 19 10 47 55 26 96

輸出：
105 30
106 68


【測試資料七】
輸入：
9
40 42 38 28 39 44 86 1 94

輸出：
36 18
41 30


【測試資料八】
輸入：
11
36 77 20 24 39 14 62 60 59 73 80

輸出：
55 21
52 37


【測試資料九】
輸入：
10
9 46 77 30 86 91 68 42 18 89

輸出：
45 24
54 36


【測試資料十】
輸入：
5
5 3 8 23 15

輸出：
10 6
11 10

*/

#include <stdio.h>
#define SWAP(x, y)                                                             \
  {                                                                            \
    int t;                                                                     \
    t = x;                                                                     \
    x = y;                                                                     \
    y = t;                                                                     \
  }
int getMinIndex(int d[], int left, int right, int *compare) {
  int i = 0, minIndex = left;
  for ((i = left + 1); i < right; i++) {
    *compare += 1;
    if (d[i] < d[minIndex])
      minIndex = i;
  }
  return minIndex;
}
void selectSort(int d[], int n, int *compare, int *move) {
  int i = 0, index = 0;
  for (i = 0; i < n; i++) {
    index = getMinIndex(d, i, n, compare);
    // printf("%d, %d\n", d[i], d[index]);
    if (i != index) {
      SWAP(d[i], d[index]);
      *move += 3;
    }
    // printf("i: %d, move: %d\n", i, *move);
  }
}
/*
void print(int a[], int n) {
  for (int i = 0; i < n; i++)
    printf("%d ", a[i]);
  printf("\n");
}
*/
void insertionSort(int a[], int n, int *compare, int *move) {
  int target = 0, i = 0, j = 0;
  for (i = 1; i < n; i++) {
    target = a[i];
    (*move)++;

    for (j = i; (a[j - 1] > target) && (j > 0); j--) {
      if (j > 0) {
        (*compare)++;
      }
      if (a[j - 1] > target) {
        (*compare)++;
      }

      a[j] = a[j - 1];
      (*move)++;
    }
    a[j] = target;
    (*move)++;
    (*compare) += 1;
    if (!(a[j - 1] > target) && (j > 0))
      (*compare)++;
    // printf("i: %d, compare: %d, move: %d\n", i, *compare, *move);
  }
}

int main() {
  int N;
  int data[15] = {0};

  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &data[i]);
  }

  // print(data, N);
  int copy_data[15] = {0};
  for (int i = 0; i < N; i++) {
    copy_data[i] = data[i];
  }

  int compare = 0, move = 0;
  selectSort(data, N, &compare, &move);
  printf("%d %d\n", compare, move);

  compare = 0, move = 0;
  insertionSort(copy_data, N, &compare, &move);
  printf("%d %d\n", compare, move);

  return 0;
}
