/*
12. 棒球問題

以下為9位棒球隊員的打擊結果，請計算在第N個出局時的總得分和跑壘次數最高的前三名球員。假設球員打擊情況：
(1) 安打：以1, 2, 3 和 H代表一、二、三和全(四)壘打。
(2) 出局：以 O表示 (OUT)。
簡化版的規則如下：
(1)
球場上有四個壘包，稱為本壘、一、二和三壘。本壘握球棒稱「擊球員」，在另外三個壘包稱「跑壘員」。
(2)
當擊球員打擊「安打」時，擊球員與跑壘員可移動；「出局」時，跑壘員不動，擊球員離場換下一位。
(3) 比賽開始由第 1位打擊，接著2, 3, …, 8, 9位球員。
(4) 打出 K 壘打時，場上球員(擊球員和跑壘員)會前進
K個壘包。本壘到一壘，接著二、三壘，最後回到本壘。回到本壘可得 1分。 (5)
每達到三個出局數時，壘包清空(跑壘員都得離開)，重新開始。



【輸入說明】
第1行:輸入第一位球員的打擊資訊。包含打擊次數整數a(1<=a<=5)和每次的打擊結果，各項資訊間以空白間隔
第2行:輸入第二位球員的打擊資訊。包含打擊次數整數b(1<=b<=5)和每次的打擊結果，各項資訊間以空白間隔
....
第9行:輸入第九位球員的打擊資訊。包含打擊次數整數m(1<=m<=5)和每次的打擊結果，各項資訊間以空白間隔
第10行:輸入計算累積出局數整數N(1<=N<=27)

範例輸入說明：
3 1 O O(第一位球員擊打數3次，第一次一壘安打，第二次OUT，第三次OUT)
3 1 2 1(第二位球員擊打數3次，第一次一壘安打，第二次二壘安打，第三次一壘安打)
3 O O O(第三位球員擊打數3次，第一次OUT，第二次OUT，第三次OUT)
3 O O O(第四位球員擊打數3次，第一次OUT，第二次OUT，第三次OUT)
3 1 1 3(第五位球員擊打數3次，第一次一壘安打，第二次一壘安打，第三次三壘安打)
3 O O H(第六位球員擊打數3次，第一次OUT，第二次OUT，第三次四壘安打)
3 3 1 2(第七位球員擊打數3次，第一次三壘安打，第二次一壘安打，第三次二壘安打)
3 O O 1(第八位球員擊打數3次，第一次OUT，第二次OUT，第三次一壘安打)
2 O 1(第九位球員擊打數2次，第一次OUT，第二次一壘安打)
13(計算累積出局數為13時的打擊情況)


【輸出說明】
第一行:輸出在累積出局數N時的總得分整數b
第二到四行:根據在累積出局數N時球員跑壘數量由大到小排序，若相同則以棒次先後排序輸出前三位打者的資訊(第幾棒,
安打數, 跑壘數量)。 ※ 跑壘數量:
球員在比賽中總共跑的壘包數量，包含自己安打跑的壘包數與隊友安打而跑的壘包數。



範例輸出說明：
0(在第13個出局時，總得分為0)
2 3 6(第二位球員，跑壘次數最多為6，安打數為3)
7 2 6(第七位球員，跑壘次數和第一名相同為6，但棒次在第一名後面，安打數為2)
1 1 3(第一位球員，跑壘次數第二多為3，安打數為1)


【測試資料一】
輸入：
3 1 1 2
3 2 O 1
3 O 1 O
3 O O 2
3 O 1 2
3 O O H
3 1 O 2
3 2 1 1
2 O 2
10

輸出：
3
1 3 7
8 2 7
7 1 4

【測試資料二】
輸入：
4 1 O 1 2
3 1 1 O
3 O 1 O
3 1 O O
3 O O 1
3 O O 3
3 2 O O
3 O 1 O
3 O 1 O
12


輸出：
0
1 2 4
2 2 4
8 1 3

【測試資料三】
輸入：
4 1 O 1 2
4 1 1 O H
4 H 2 O O
3 1 O H
3 O H 3
3 2 1 3
3 H 1 O
3 O 2 H
3 O 2 O
10

輸出：
18
2 3 12
6 3 12
1 3 9

*/

#include <stdio.h>

#define MAX_AT_BATS 5
#define PLAYER_NUM 9
#define STATE 7

void findTopThreeIndices(int arr[], int size, int indices[]);

int main() {
  char player[PLAYER_NUM][MAX_AT_BATS] = {0};
  int player_n[PLAYER_NUM] = {0}; // 每個plater揮打次數
  for (int i = 0; i < PLAYER_NUM; i++) {
    int n = 0; // 每個plater揮打次數
    scanf("%d", &n);
    player_n[i] = n;
    getchar(); // 空白鍵

    for (int j = 0; j < n; j++) {
      scanf("%c", &player[i][j]);
      getchar(); // 空白鍵(非最後一次)或換行(最後一次)
    }
  }

  int out_stop; // 累計出局數的中止條件
  scanf("%d", &out_stop);
  int out_sum = 0; // 紀錄目前總出局數
  int out = 0;     // 紀錄出局數(達三場則歸零)
  int i = 0, j = 0;
  int score = 0;
  int player_bits[PLAYER_NUM] = {0}; // 每位打者的安打數
  int state[STATE] = {0};            // 壘包狀態
  int player_state[STATE] = {0};
  int player_runs[PLAYER_NUM] = {0}; // 每位打者的跑壘次數

  while (1) {
    if (out_sum == out_stop) {
      break;
    }

    // printf("i: %d, j=%d, current: %c\n", i, j, player[i][j]);

    if (player[i][j] == 'H') { // 全壘打
      player_bits[i] += 1;
      for (int m = 0; m < 4; m++) { // 一次右移一格，共右移四次
        for (int k = STATE; k > 0; k--) {
          state[k] = state[k - 1];
          player_state[k] = player_state[k - 1];
          if (player_state[k] != 0 && k <= 3)
            player_runs[player_state[k] - 1] += 1;
          player_state[3] = 0;
          player_state[4] = 0;
          player_state[5] = 0;
          player_state[6] = 0;
        }
        state[0] = 0; // 補0
        player_state[0] = 0;
      }
      state[3] = 1; // 打者上壘
      player_state[3] = i + 1;
      player_runs[i] += 4; // 安打該選手跑壘數更新

    } else if (player[i][j] == 'O') { // 出局
      out++;
      out_sum++;
      // printf("out_sum: %d\n", out_sum);
      // printf("out: %d\n", out);
      if (out == 3) {
        for (int k = 0; k < STATE; k++) {
          state[k] = 0;
          player_state[k] = 0;
        }
        out = 0;
      }

    } else {
      player_bits[i] += 1; // 安打1~3
      for (int m = 0; m < (int)player[i][j] - 48;
           m++) { // 一次右移一格，共右移四次
        for (int k = STATE; k > 0; k--) {
          state[k] = state[k - 1];
          player_state[k] = player_state[k - 1];
          if (player_state[k] != 0 && k <= 3)
            player_runs[player_state[k] - 1] += 1;
          player_state[3] = 0;
          player_state[4] = 0;
          player_state[5] = 0;
          player_state[6] = 0;
        }
        state[0] = 0; // 補0
        player_state[0] = 0;
      }
      state[(int)player[i][j] - 48 - 1] = 1; // 打者上壘
      player_state[player[i][j] - 48 - 1] = i + 1;
      player_runs[i] += player[i][j] - 48; // 安打該選手跑壘數更新
    }

    // check
    /*
    for (int y = 0; y < STATE; y++) {
      printf("%d ", state[y]);
    }
    printf("\n");
    */

    /*
    for (int y = 0; y < STATE; y++) {
      printf("%d ", player_state[y]);
    }
    printf("\n");
    */

    // 加分，並清空
    for (int y = 3; y <= 6; y++) {
      if (state[y] == 1) {
        score++;
        // printf("score_curr: %d\n", score);
        state[y] = 0;
      }
    }

    i++;          // 換下一位選手
    if (i == 9) { // 一輪結束(九位選手都打完)，開啟新的一輪
      j++;
      i = 0; // 從第一位選手開始
    }
  }

  printf("%d\n", score);
  // 驗證各選手安打數
  /*
    for (int i = 0; i < PLAYER_NUM; i++) {
      printf("player: %d, bits: %d, runs: %d\n", i + 1, player_bits[i],
             player_runs[i]);
    }
  */

  int index[3] = {0}; // 前三個跑壘數最多者
  findTopThreeIndices(player_runs, PLAYER_NUM, index);
  // printf("%d %d %d\n", index[0], index[1], index[2]);

  for (int i = 0; i < 3; i++) {
    printf("%d %d %d\n", index[i] + 1, player_bits[index[i]],
           player_runs[index[i]]);
  }

  // 驗證輸入
  /*
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 5; j++) {
        printf("%c ", player[i][j]);
    }
    printf("\n");
  }
  */

  return 0;
}

void findTopThreeIndices(int arr[], int size, int indices[]) {
  int max1 = arr[0], max2 = 0, max3 = 0;
  int idx1 = 0, idx2 = 0, idx3 = 0;

  for (int i = 1; i < size; ++i) {
    // printf("arr[i]=%d, i=%d, max1:%d, max2:%d, max3:%d, idx1:%d, idx:%d,
    // idx:%d\n",arr[i], i, max1, max2, max3, idx1, idx2, idx3);
    if (arr[i] > max1) {
      max3 = max2;
      idx3 = idx2;
      max2 = max1;
      idx2 = idx1;
      max1 = arr[i];
      idx1 = i;
      // printf("%d 111\n", i);
    }
    if (arr[i] <= max1 && arr[i] >= max2 &&
        i != idx1) { // 不重复且大于等于第二大值
      if (arr[i] != max2 || i < idx2) {
        max3 = max2;
        idx3 = idx2;
        max2 = arr[i];
        idx2 = i;
        // printf("%d 222\n", i);
      }
    }
    if (arr[i] <= max2 && arr[i] >= max3 && i != idx1 &&
        i != idx2) { // 不重复且大于等于第三大值
      if (arr[i] != max3 || i < idx3) {
        max3 = arr[i];
        idx3 = i;
        // printf("%d 333\n", i);
      }
    }
  }

  indices[0] = idx1;
  indices[1] = idx2;
  indices[2] = idx3;
}
