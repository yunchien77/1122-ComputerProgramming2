/*005. 衝堂

請檢查輸入的三門課程是否衝堂。
依序輸入 :
課程編號、
上課小時數 (1-3 小時)、
上課時間 (依小時數輸入上課時間, 星期 1-5, 第 1-9 節)。

【輸入說明】
第一行：輸入第一堂課程編號 (整數)
第二行：輸入第一堂課程上課小時數h1 (整數, 1<=h1<=3)
接下來h1行：輸入第一堂課程的上課時間，每個時段皆為二位數的整數，十位
代表星期幾上課上課，個位代表上課的節數
...接下來第二、三堂課程的操作步驟也是一樣

範例輸入說明:
1001 (第一堂課程編號為1001)
1 (第一堂課程上課總時數為1)
11 (第一堂課程禮拜一第1節有課)
1002 (第二堂課程編號為1002)
2 (第二堂課程上課總時數為2)
11 (第二堂課程禮拜一第1節有課)
12 (第二堂課程禮拜一第2節有課)
3 (第三堂課程編號為1003)
3 (第三堂課程上課總時數為3)
23 (第三堂課程禮拜二第3節有課)
45 (第三堂課程禮拜四第5節有課)
55 (第三堂課程禮拜五第5節有課)

【輸出說明】
若無發生衝堂，則輸出correct
若發生衝堂 :
輸出所有衝堂的課程，每次輸出兩個衝堂的課程編號，以及在哪一天的哪一節衝突，參考下列格式(中間以逗號隔開)
: 課程1編號,課程2編號,衝堂在哪天哪節 先輸入的課程為課程1，後輸入的課程為課程2

範例輸出說明:
1001,1002,11 (課程編號1001和1002衝堂在11(禮拜一第1節))

【測試資料一】
輸入：
111
2
11
31
112
1
31
113
3
31
32
58

輸出：
111,112,31
111,113,31
112,113,31

【測試資料二】
輸入：
101
2
11
22
201
2
33
44
301
2
55
56

輸出：
correct

【測試資料三】
輸入：
701
2
11
33
802
2
33
34
903
2
34
51

輸出：
701,802,33
802,903,34

【測試資料四】
輸入：
101
2
11
12
102
3
11
12
34
103
1
34

輸出：
101,102,11
101,102,12
102,103,34


*/
#include <stdio.h>

int main() {
  int course_num[3], hours[3], schedules[3][3] = {0};
  int conflict[20][3] = {0};
  int boom_day[3] = {0};
  int count = 0;

  // Input course details
  for (int i = 0; i < 3; i++) {
    scanf("%d", &course_num[i]);
    scanf("%d", &hours[i]);
    for (int j = 0; j < hours[i]; j++) {
      scanf("%d", &schedules[i][j]);
    }
  }

  // Check for conflicts
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < hours[i]; j++) {
      if (schedules[i][j] == 0) // Skip empty slots
        continue;
      for (int m = i + 1; m < 3; m++) {
        for (int k = 0; k < hours[m]; k++) {
          if (schedules[m][k] == 0) // Skip empty slots
            continue;
          if (schedules[i][j] == schedules[m][k]) {
            conflict[count][0] = course_num[i];
            conflict[count][1] = course_num[m];
            boom_day[count] = schedules[i][j];
            count++;
          }
        }
      }
    }
  }

  // Output conflicts
  if (count == 0) {
    printf("correct\n");
  } else {
    for (int i = 0; i < count; i++) {
      printf("%d,%d,%d\n", conflict[i][0], conflict[i][1], boom_day[i]);
    }
  }

  return 0;
}
