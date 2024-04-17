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
