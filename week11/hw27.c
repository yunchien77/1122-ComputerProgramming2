/*
27. 工作排程

有M個工作要在N台機器上加工，每個工作i包含若干個工序Oij，
這些工序須依序加工，也就是前一道工序Oi(j-1)完成後才可開始下一道工序Oij。
每道工序oij可用一個有序對(Kij,Tij)表示它需在機器Kij上面花費Tij小時完成，
而每台機器一次只能處理一道工序。

所謂一道工序Oij的「最早完成時間的Cij｣是指考慮目前排程中機器Kij之可用性
以及前一道工序Oi(j-1)(若該工序存在)之完成時間後可得的最早完成時間。

所有工序的排程規則如下：
針對每一個工作的第一個尚未排程的工序，計算出此工序的「最早完成時間｣，
然後挑選出最早完成時間最小的工序納入排程中，
如果有多個完成時間都是最小，則挑選其中最小工作編號之工序，
一個工序一旦納入排程就不會再更改，重複以上步驟直到所有工序皆納入排程。

範例說明 :
工作1(以○代表) O11 = (2, 4) O12 = (1, 1)
此工作有兩道工序，第一道需要在機器2執行4小時， 第二道需要在機器1執行1小時。

工作2(以■代表) O21 = (0, 2) O22 = (2, 2) O23 = (0, 1)
有三道工序，第一道需要在機器0執行2小時，餘類推。

工作3(以●代表) O31 = (0, 7)
有一道工序需要在機器0執行7小時。

排程過程說明如下:
1. 在開始時，每個工作都是考慮第一道工序，
三個工作第1道工序需要的時間分別是 T11 = 4、T21 = 2、T31 = 7，
這也是它們的最早完成時間， 也就是C11=4、C21=2、C31=7，
因此會先排O21。
====================================
機器0→■■□□□□□□□□□□□□ --------------工作一○
機器1→□□□□□□□□□□□□□□ --------------工作二■
機器2→□□□□□□□□□□□□□□ --------------工作三●
====================================

2. 接下來，
三個工作要考慮的順序分別是工作1的第1個工序、工作2的第2個工序、工作3的第1個工序，即
O11、O22和O31。 (1) O11 需要機器2執行 4小時，而機器 2
尚未安排工序，可以開始加工的時間點是0且O11沒有前一道工序，此工序可以開始的時間是
max(0, 0) = 0，其最早完成時間 C11 = max(0,0) + 4 = 4。 (2) O22 需機器2執行
2小時，而機器 2
尚未安排工序，可以開始加工的時間點是0；但O22前一道工序O21完成時間是
2，因此這工序可以開始的時間是max(0, 2) = 2，最早完成時間 C22 = max(0,2) + 2 =
4。 (3) O31 需機器0執行 7小時，而機器 0 可開始加工的時間點是
2且O31沒有前一道工序，因此這工序可開始的時間是max(2, 0) = 2，其最早完成時間C31 =
max(2, 0) + 7 = 9。

經過上述計算，由於C11 和 C22 都是最小，根據規則，工作編號小的先排，所以會排
O11。
====================================
機器0→■■□□□□□□□□□□□□ --------------工作一○
機器1→□□□□□□□□□□□□□□ --------------工作二■
機器2→○○○○□□□□□□□□□□ --------------工作三●
====================================

3.
三個工作目前要考慮的順序分別工作1的第2個工序、工作2的第2個工序、工作3的第1個工序。
依照最早完成時間計算方式，可得到C12 = 5，C22 = 6，C31 = 9，
因此排O12，工作1的工序均已排完，所以工作1的完成時間是 5。
4. 目前剩下工作2與工作3，C22 = 6，C31 = 9，因此先排O22。
5. 目前剩下工作2與工作3， C23 = 7，C31 = 9，
因此排O23，工作2的工序已排完，所以工作2的完成時間是 7。
6. 剩下工作3，因為機器0的下一個可以開始時間是7，O31的完成時間是max(7, 0) +
7=14。
====================================
機器0→■■□□□□■●●●●●●● --------------工作一○
機器1→□□□□○□□□□□□□□□ --------------工作二■
機器2→○○○○■■□□□□□□□□ --------------工作三●
====================================

最後所有工作的工序皆有排程，最後三個工作完成時間分別是5、7、14，
因此最後輸出答案 5+7+14=26。


【輸入說明】
第一行輸入兩個整數 N 與 M，N 代表有多少台機器(1<=N<=10)，M
代表有多少個工作(1<=M<=10)，接下來會有M個工作資訊 ， 輸入順序即為工作編號順序，
之後2*M行，每兩行為一個工作資訊，第一行為整數P(1<=P<=10)，代表到工序數量；
第二行有 2 * P
個整數，依序每兩個一組代表一道工序的機器編號與需求時間T(1<=T<=10)，每個整數間以空白符號相隔開。
注意: 機器的編號由0開始

範例輸入說明:
3 3(有3台機器3個工作)
2(第一個工作有2個工序)
2 4 1 1(第一個工序需要在機器2花費4小時，第二個工序需要在機器1花費1小時)
3(第二個工作有3個工序)
0 2 2 2 0
1(第一個工序需要在機器0花費2小時，第二個工序需要在機器2花費2小時，第三個工序需要在機器0花費1小時)
1(第三個工作有1個工序)
0 7(第一個工序需要在機器0花費7小時)

對應的行程如下:
機器0→■■□□□□■●●●●●●● --------------工作一○
機器1→□□□□○□□□□□□□□□ --------------工作二■
機器2→○○○○■■□□□□□□□□ --------------工作三●


【輸出說明】
輸出每個工作完成時間的總和

範例輸出說明:
26( 三個工作完成時間各為5、7、14，5+7+14=26)


【測試資料一】
輸入：
3 3
2
0 2 0 4
3
1 2 1 3 1 5
2
2 2 2 5

輸出：
23



【測試資料二】
輸入：
4 2
1
0 3
1
0 5

輸出：
11

【測試資料三】

輸入：
4 4
3
0 2 1 3 1 4
4
0 3 0 2 1 5 1 6
1
2 4
2
2 2 2 1

輸出:
39

【測試資料四】

輸入：
3 3
3
0 1 2 4 1 3
3
0 2 2 2 1 1
1
0 3

輸出:
23

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int machine;
  int time;
} Operation;

typedef struct {
  int num_operations;
  Operation *operations;
  int current_operation;
  int completion_time;
} Job;

typedef struct {
  int available_time;
} Machine;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  Job jobs[M];
  Machine machines[N];

  for (int i = 0; i < N; i++) {
    machines[i].available_time = 0;
  }

  for (int i = 0; i < M; i++) {
    scanf("%d", &jobs[i].num_operations);
    jobs[i].operations =
        (Operation *)malloc(jobs[i].num_operations * sizeof(Operation));
    jobs[i].current_operation = 0;
    jobs[i].completion_time = 0;

    for (int j = 0; j < jobs[i].num_operations; j++) {
      scanf("%d %d", &jobs[i].operations[j].machine,
            &jobs[i].operations[j].time);
    }
  }

  int remaining_jobs = M;
  while (remaining_jobs > 0) {
    int min_completion_time = -1;
    int selected_job = -1;

    for (int i = 0; i < M; i++) {
      if (jobs[i].current_operation < jobs[i].num_operations) {
        int current_op = jobs[i].current_operation;
        int machine = jobs[i].operations[current_op].machine;
        int time = jobs[i].operations[current_op].time;

        int start_time = jobs[i].completion_time;
        if (start_time < machines[machine].available_time) {
          start_time = machines[machine].available_time;
        }

        int completion_time = start_time + time;

        if (min_completion_time == -1 ||
            completion_time < min_completion_time ||
            (completion_time == min_completion_time && i < selected_job)) {
          min_completion_time = completion_time;
          selected_job = i;
        }
      }
    }

    if (selected_job != -1) {
      int current_op = jobs[selected_job].current_operation;
      int machine = jobs[selected_job].operations[current_op].machine;
      int time = jobs[selected_job].operations[current_op].time;

      int start_time = jobs[selected_job].completion_time;
      if (start_time < machines[machine].available_time) {
        start_time = machines[machine].available_time;
      }

      jobs[selected_job].completion_time = start_time + time;
      machines[machine].available_time = start_time + time;

      jobs[selected_job].current_operation++;

      if (jobs[selected_job].current_operation ==
          jobs[selected_job].num_operations) {
        remaining_jobs--;
      }
    }
  }

  int total_completion_time = 0;
  for (int i = 0; i < M; i++) {
    total_completion_time += jobs[i].completion_time;
  }

  printf("%d\n", total_completion_time);

  for (int i = 0; i < M; i++) {
    free(jobs[i].operations);
  }

  return 0;
}
