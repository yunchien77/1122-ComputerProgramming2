/*
017 DF-expression

題目將給定一個DF-expression表達式和圖像方陣的大小，依據DF-expression表達式判斷出圖像方陣中的黑色方格的座標位置，並且將黑色方格的座標位置依照排序方式後輸出。

DF-expression是儲存圖像資訊的表達方式，
圖像為一個NxN方陣中，
若方陣中的方格全部皆為白色則記為0，
若方陣中的方格全部皆為黑色則記為1，
若方陣中的方格不全為白或不全為黑，則記為2，
並將此方陣分割為更小的4塊全等方陣(左上、右上、左下、右下)，
再依序(左上→右上→左下→右下)記錄這四塊方陣的資訊。

說明範例 ：
下方圖像為一個4x4的方陣:

□□□□
□□■□
■■□□
■■□□
上方方陣中的方格不全為白或不全為黑，
因此先記為2，當前DF-expression序列為2，
接著將4*4的方陣分割為4塊2*2的方陣，
再依序檢視左上→右上→左下→右下四塊方陣。

□□
□□
左上圖像方陣中的方格全部為白色，
因此記為0，當前DF-expression序列為20。

□□
■□
右上圖像方陣中的方格不全為白或黑，因此記為2，
將此方陣再分割為四塊1*1的方陣，
並依序檢視左上→右上→左下→右下四塊方陣，得到0010，
當前DF-expression序列為2020010。

■■
■■
左下圖像方陣中的方格全為黑色，
因此記為1，當前DF-expression序列為20200101。

□□
□□
右下圖像方陣中的方格全為白色，
因此記為0，當前DF-expression序列為202001010。
當圖像方陣中的方格全部檢視完畢後，最終會得到DF-expression為202001010。


方格座標定位法:
圖像方陣中最左上方的方格定為0,0，
由此方格往右的方格座標依序為0,1、0,2、0,3以此類推，
由此方格往下的方格座標依序為1,0、2,0、3,0以此類推，
以上方說明範例進行定位，
說明範例中的所有黑色方格座標位置為:
2,0
3,0
2,1
3,1
1,2


排序方式:
依照方陣中的方格順序由左而右，由上到下進行排序，
以上方說明範例進行排序，
說明範例中的所有黑色方格座標排序後為:
1,2
2,0
2,1
3,0
3,1

【輸入說明】
第一行:輸入一個DF-expression的表達式 S (1 <= strlen(S) <= 100)，
第二行:輸入該張圖像的寬度 N(必為2的非負整數次方，2<=N<=8)。

範例輸入說明:
20211002210010100 (DF-expression 表達式)
8(圖像為8 X 8)
(對應圖片如下:
□□□□■■■■
□□□□■■■■
□□□□□□□□
□□□□□□□□
■□□□□□□□
□■□□□□□□
■■□□□□□□
■■□□□□□□)

【輸出說明】
輸出該張圖像方陣中黑色方格排序後的座標位置，每行x值和y值間已逗號間隔 。
若該張圖像方陣中無黑色方格則輸出"all white"

範例輸出說明:
0,4
0,5
0,6
0,7
1,4
1,5
1,6
1,7
4,0
5,1
6,0
6,1
7,0
7,1

【測試資料一】
輸入：
0
4

輸出：
all white

【測試資料二】
輸入：
1
4

輸出：
0,0
0,1
0,2
0,3
1,0
1,1
1,2
1,3
2,0
2,1
2,2
2,3
3,0
3,1
3,2
3,3

【測試資料三】
輸入：
20110
2

輸出：
0,1
1,0

【測試資料四】
輸入：
221000101
4

輸出：
0,0
0,2
0,3
1,2
1,3
2,2
2,3
3,2
3,3


【測試資料五】
輸入：
202100101
4

輸出：
0,2
1,3
2,2
2,3
3,2
3,3



【測試資料六】
輸入：
200210011
4

輸出：
2,0
2,2
2,3
3,1
3,2
3,3

【測試資料七】
輸入：
210021010
4

輸出：
0,0
0,1
1,0
1,1
2,2
3,2

【測試資料八】
輸入：
22210010021001221001002100122100100210012210010021001
8

輸出：
0,0
0,4
1,1
1,5
2,2
2,6
3,3
3,7
4,0
4,4
5,1
5,5
6,2
6,6
7,3
7,7



【測試資料九】
輸入：
2221001210012100121001221010210012100121001221001210002000121101221001210012100121001
8

輸出：
0,0
0,2
0,4
0,6
1,1
1,3
1,4
1,7
2,0
2,2
2,4
2,6
3,1
3,3
3,5
3,7
4,0
4,2
4,4
4,6
5,1
5,5
5,7
6,2
6,3
6,4
6,6
7,1
7,3
7,5
7,7

*/

#include <math.h>
#include <stdio.h>
#include <string.h>

// Function to parse the DF-expression and update the coordinates of black cells
void parseExpression(char *S, int startRow, int startCol, int size, int *x,
                     int *y, int *index, int *count) {
  // printf("current: %c\n", S[*index]);
  // printf("startrow: %d, startcol: %d, size: %d, index: %d\n", startRow,
  // startCol, size, *index);
  if (*index >= strlen(S)) {
    return; // If we reached the end of the expression, return
  }
  if (S[*index] == '0') {
    // All white, do nothing
    (*index)++;
  } else if (S[*index] == '1') {
    // All black, mark all cells in this block as black
    if (size == 2) {
      x[*count] = startRow;
      y[*count] = startCol;
      (*count)++;
      x[*count] = startRow;
      y[*count] = startCol + 1;
      (*count)++;
      x[*count] = startRow + 1;
      y[*count] = startCol;
      (*count)++;
      x[*count] = startRow + 1;
      y[*count] = startCol + 1;
      (*count)++;
    } else {
      // Otherwise, store only one coordinate
      x[*count] = startRow;
      y[*count] = startCol;
      (*count)++;
    }
    (*index)++;
  } else { // 2
    // Not all white or all black, divide into four quadrants
    int newSize = size / 2;
    (*index)++;
    parseExpression(S, startRow, startCol, newSize, x, y, index,
                    count); // Top left
    parseExpression(S, startRow, startCol + newSize, newSize, x, y, index,
                    count); // Top right
    parseExpression(S, startRow + newSize, startCol, newSize, x, y, index,
                    count); // Bottom left
    parseExpression(S, startRow + newSize, startCol + newSize, newSize, x, y,
                    index, count); // Bottom right
  }
}

void sort(int x[], int y[], int count) {
  // Bubble sort for sorting x array elements
  for (int i = 0; i < count - 1; i++) {
    for (int j = 0; j < count - i - 1; j++) {
      if (x[j] > x[j + 1]) {
        // Swap elements if they are in the wrong order
        int temp = x[j];
        int temp1 = y[j];
        x[j] = x[j + 1];
        y[j] = y[j + 1];
        x[j + 1] = temp;
        y[j + 1] = temp1;
      }
    }
  }
}

int main() {
  char S[101];   // DF-expression
  int N;         // Width of the image
  int size;      // Size of the image
  int x[100];    // X coordinates of black cells
  int y[100];    // Y coordinates of black cells
  int count = 0; // count of saving coordinates

  // Input
  scanf("%s", S);
  scanf("%d", &N);

  // Initialize string index
  int index = 0;

  // Output
  if (strlen(S) == 1 && S[0] == '0') {
    printf("all white\n");
  } else if (strlen(S) == 1 && S[0] == '1') {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        printf("%d,%d\n", i, j);
      }
    }
  } else {
    // Parse the expression
    parseExpression(S, 0, 0, N, x, y, &index, &count);
    sort(x, y, count);
    for (int i = 0; i < count; i++) {
      printf("%d,%d\n", x[i], y[i]);
    }
  }

  return 0;
}
