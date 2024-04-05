/*
15. m分散度

請輸入一個整數m，及一串整數序列。
計算此序列的m分散度，
輸出該m分散度的連續子序列總數，及其所有已排序且不重複的連續子序列，
不需考慮連續子序列總數為零的狀況。

m分散度的連續子序列定義為：
序列中可分成多個長度為m且index連續的子序列，而子序列中的數字要為不重覆數字。

連續子序列排序方式:
子序列以{x, y, z}為例，
以 x 值小到大進行排序，若 x 值相同，以 y 值小到大進行排序，以此類推。

例如：
m = 3，整數序列為 {1, 2, 3, 1, 2, 3, 3}，
可分割成{1, 2, 3}, {2, 3, 1}, {3, 1, 2}, {1, 2, 3}, {2, 3,
3}個index連續的子序列， 而分割後的子序列中的數字為不重複數字的子序列為{1, 2, 3},
{2, 3, 1}, {3, 1, 2}, {1, 2, 3}， 因此 3分散度的連續子序列總數為 4 個，
而輸出依照連續子序列方式後且不重複的連續子序列為:{1, 2, 3}, {2, 3, 1}, {3, 1,
2}。


【輸入說明】
第一行:輸入一整數m (3 <= m <= 10)，代表m分散度。
第二行:輸入一串長度為 a 的整數序列 ( m <= a <=
20)，數字間以空白字元相隔開，其序列中的整數 b 大小為 0 <= b <= 9。
第三行:輸入-1結束

範例輸入說明：
3(分散度m為3)
1 2 3 5 4 3 5 4(整數序列)
-1(輸入-1結束)


【輸出說明】
第一行輸出該整數序列的m分散度的連續子序列總數。
其後n行，每行輸出已排序後且不重複的一組連續子序列，整數間以空格符號分開輸出。


範例輸出說明：
6(總共6個的子序列(包含重複))
1 2 3(x最小的子序列)
2 3 5(x第二小的子序列)
3 5 4(x第三小的子序列)
4 3 5(x第四小的子序列)
5 4 3(x第五小的子序列)


【測試資料一】
輸入：
4
1 2 3 6 9 4 5 6 7
-1

輸出：
6
1 2 3 6
2 3 6 9
3 6 9 4
4 5 6 7
6 9 4 5
9 4 5 6

【測試資料二】
輸入：
5
2 4 2 5 7 3 2 1 9 4 0 3
-1

輸出：
6
1 9 4 0 3
2 1 9 4 0
3 2 1 9 4
4 2 5 7 3
5 7 3 2 1
7 3 2 1 9

【測試資料三】
輸入：
3
2 4 5 7 9 2 4 5 3 6 8 0
-1

輸出：
10
2 4 5
3 6 8
4 5 3
4 5 7
5 3 6
5 7 9
6 8 0
7 9 2
9 2 4


【測試資料四】
輸入：
6
2 4 6 1 3 7 8 0 3 9 4 2 1 3 5 7 2 1 8 0
-1

輸出：
10
0 3 9 4 2 1
2 4 6 1 3 7
3 5 7 2 1 8
4 2 1 3 5 7
4 6 1 3 7 8
5 7 2 1 8 0
6 1 3 7 8 0
7 8 0 3 9 4
8 0 3 9 4 2
9 4 2 1 3 5

【測試資料五】
輸入：
3
1 1 1 2 3
-1

輸出：
1
1 2 3

*/
#include <stdbool.h>
#include <stdio.h>

// Function to compare two sequences for equality
int isEqual(int subSeq[], int nonRepeated[][10], int size, int m) {
  for (int i = 0; i < size; i++) {
    int equal = 1; // 初始化為1，表示相等
    for (int j = 0; j < m; j++) {
      if (subSeq[j] != nonRepeated[i][j]) {
        equal = 0; // 有任意一個元素不相等，設為0表示不相等，並中斷迴圈
        break;
      }
    }
    if (equal) {
      return 1; // 有重复
    }
  }
  return 0; // 没有重复
}

// Function to check if a sequence is unique
int isUnique(int subSeq[], int size) {
  for (int i = 0; i < size - 1; ++i) {
    for (int j = i + 1; j < size; ++j) {
      if (subSeq[i] == subSeq[j]) {
        return 0; // If duplicates are found, return false
      }
    }
  }
  return 1; // If no duplicates are found, return true
}

// Function to perform bubble sort on a 2D array based on the first element of
// each subarray
void bubbleSort(int arr[][10], int n, int m) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      // Compare the first element of subarrays
      if (arr[j][0] > arr[j + 1][0]) {
        // Swap the elements
        int temp[m];
        for (int k = 0; k < m; k++) {
          temp[k] = arr[j][k];
          arr[j][k] = arr[j + 1][k];
          arr[j + 1][k] = temp[k];
        }
      } else if (arr[j][0] ==
                 arr[j + 1][0]) { // If the first elements are equal, compare
                                  // the rest of the elements
        int k = 1;
        while (k < m && arr[j][k] == arr[j + 1][k]) {
          k++;
        }
        if (arr[j][k] > arr[j + 1][k]) {
          // Swap the elements
          int temp[m];
          for (int k = 0; k < m; k++) {
            temp[k] = arr[j][k];
            arr[j][k] = arr[j + 1][k];
            arr[j + 1][k] = temp[k];
          }
        }
      }
    }
  }
}

int main() {
  int m;
  scanf("%d", &m);
  int sequence[20];
  int count = 0;
  int input;
  while (1) {
    if (scanf("%d", &input) == 1) {
      if (input == -1) {
        break;
      } else {
        sequence[count] = input;
        count++;
      }
    } else {
      break;
    }
  }

  int totalSubsequences = count - m + 1;
  int subsequences[20][10];
  int subCount = 0;

  // Generate and store unique subsequences(序列中沒有重複元素)
  for (int i = 0; i < totalSubsequences; ++i) {
    int subSeq[m];
    for (int j = 0; j < m; ++j) {
      subSeq[j] = sequence[i + j];
    }
    if (isUnique(subSeq, m)) { // Check if the subsequence element is unique
      for (int j = 0; j < m; ++j) {
        subsequences[subCount][j] = subSeq[j];
      }
      subCount++;
    }
  }

  printf("%d\n", subCount);

  int nondRepeatedSeq[20][10] = {0};
  int equCount = 0;
  for (int i = 0; i < subCount; i++) {
    if (!isEqual(subsequences[i], nondRepeatedSeq, subCount, m)) {
      for (int k = 0; k < m; k++) {
        nondRepeatedSeq[equCount][k] = subsequences[i][k];
      }
      equCount++;
      // printf("count: %d\n", equCount);
    }
  }

  // Sort subsequences based on the first element using bubble sort
  bubbleSort(nondRepeatedSeq, equCount, m);
  for (int i = 0; i < equCount; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", nondRepeatedSeq[i][j]);
    }
    printf("\n");
  }

  return 0;
}