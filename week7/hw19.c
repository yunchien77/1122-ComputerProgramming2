/*
019 骰子

十八骰子是一種常見的擲骰子遊戲,用四顆骰子計點。四顆一開始都是點數 1 朝上,點數 4
朝前,點數 2 朝右 (如下圖所示),骰子展開如下圖所示。


骰子操作方式:
1 表示向前滾一次。(滾完之後，點數3朝上)
2 表示向後滾一次。(滾完之後，點數4朝上)
3 表示向右滾一次。(滾完之後，點數5朝上)
4 表示向左滾一次。(滾完之後，點數2朝上)

計算點數方法:
(1)若四顆點數均相同,稱一色,計18點,例如6, 6, 6, 6 或 3, 3, 3, 3。
(2)若四顆點數均不同;或有三顆點數相同,一顆不同,計 0點,例如 1, 2, 3, 4 或 2, 2, 2,
6。 (3)若兩顆點數相同,另兩顆點數也相同,但兩組兩顆點數不同,則點數計算為 -
加總兩顆較 大點數,例如 2, 2, 5, 5,加總兩顆較大點數為 5+5=10點。
(4)若兩顆點數相同,另兩顆點數不同,則點數計算為加總兩顆不同點數,例如 2, 2, 4,
5,加總兩顆不同點數為 4+5=9點。

【輸入說明】
第一行輸入正整數N，表示對骰子的操作次數，(1<=N<=10)
第二行~第N+1行輸入正整數a、b、c、d，a代表第一顆骰子的操作方式，b代表第二顆骰子的操作方式，依此類推，(1<=a,b,c,d<=4)

範例輸入說明:
2 (骰子的操作次數為2)
1 2 3 4
(第一次操作，對第一顆骰子執行向前滾、對第二顆骰子執行向後滾、對第三顆骰子執行向右滾、對第四顆骰子執行向左滾)
4 3 2 1
(第二次操作，對第一顆骰子執行向左滾、對第二顆骰子執行向右滾、對第三顆骰子執行向後滾、對第四顆骰子執行向前滾)

【輸出說明】
第一行輸出根據計算點數方法得出的分數

範例輸出說明:
0 (4顆骰子最後的點數為2、5、4、3，根據計分規則，得分為0)

【測試資料一】
輸入：
4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4

輸出：
18

【測試資料二】
輸入：
2
1 2 3 4
1 2 3 4

輸出：
18

【測試資料三】
輸入：
2
1 2 3 4
4 3 2 1

輸出：
0

【測試資料四】
輸入：
3
1 2 3 4
1 2 3 4
3 1 4 2

輸出：
10

【測試資料五】
輸入：
2
1 2 3 4
2 3 1 1

輸出：
6

【測試資料六】
輸入：
6
1 2 3 4
4 3 2 1
4 1 2 3
3 2 1 4
2 2 2 3
4 4 1 1

輸出：
0
*/

#include <stdio.h>
#define CHANGE(x, y)                                                           \
  {                                                                            \
    int temp = x;                                                              \
    x = y;                                                                     \
    y = 7 - temp;                                                              \
  }

void roll(int data[], int op);
// void change(int x, int y);
void swap(int x, int y);
int getPoint(int data[4][3]);
int countSame(int data[4][3], int sum[7]);
int sameSum(int sum[], int index);
int normalPoint(int sum[]);

int main() {
  int N = 0;
  int a[4], data[4][3];

  for (int i = 0; i < 4; i++) {
    data[i][0] = 4;
    data[i][1] = 1;
    data[i][2] = 2;
  }

  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d %d %d %d", &a[0], &a[1], &a[2], &a[3]);
    for (int j = 0; j < 4; j++) {
      roll(data[j], a[j]);
      // printf("%d %d %d\n", data[j][0], data[j][1], data[j][2]);
    }
  }

  // for (int i = 0; i < 4; i++) {
  //   printf("%d %d %d\n", data[i][0], data[i][1], data[i][2]);
  // }

  printf("%d\n", getPoint(data));
}

void roll(int data[], int op) {
  if (op == 1)
    CHANGE(data[0], data[1])
  else if (op == 2)
    CHANGE(data[1], data[0])
  else if (op == 3)
    CHANGE(data[2], data[1])
  else if (op == 4)
    CHANGE(data[1], data[2])
}

// void change(int x, int y) {
//   int temp = x;
//   x = y;
//   y = temp;
// }

void swap(int x, int y) {
  int temp = x;
  x = y;
  y = temp;
}

int getPoint(int data[4][3]) {
  int sum[7] = {0, 0, 0, 0, 0, 0, 0};
  int maxIndex = 0, point = 0;
  maxIndex = countSame(data, sum);

  // printf("%d %d %d %d %d %d\n", sum[1], sum[2], sum[3], sum[4], sum[5],
  // sum[6]);
  if (sum[maxIndex] == 4)
    point = 18;
  else if ((sum[maxIndex] == 3) || (sum[maxIndex] == 1))
    point = 0;
  else if ((sum[maxIndex] == 2) && (sameSum(sum, maxIndex) == 2))
    point = 2 * maxIndex;
  else if (sum[maxIndex] == 2)
    point = normalPoint(sum);
  return point;
}

int countSame(int data[4][3], int sum[7]) {
  int maxIndex = 0;
  for (int i = 1; i <= 6; i++) {
    for (int j = 0; j < 4; j++) {
      if (data[j][1] == i)
        sum[i]++;
    }
    if (sum[i] >= sum[maxIndex])
      maxIndex = i;
  }
  return maxIndex;
}

int sameSum(int sum[], int index) {
  int num = 0;
  for (int i = 1; i <= 6; i++) {
    if (sum[i] == sum[index])
      num++;
  }
  return num;
}

int normalPoint(int sum[]) {
  int point = 0;
  for (int i = 1; i <= 6; i++) {
    if (sum[i] == 1)
      point = point + i;
  }
  return point;
}
