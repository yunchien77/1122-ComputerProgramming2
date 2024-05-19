/*
24.班級資料統計
本題必須使用給定程式碼架購的struct 和 function 實作，否則將不予計分。

使用struct 儲存每位學生的資訊如下:
typedef struct student_s{
char name[50];
int score;
}student_t;


要實作的功能和對應的function 如下:
新增n位學生的資料
void input(student_t s[], int n);
回傳班級內分數最高的姓名(使用參數char name[])
void getHigh(student_t s[], int n, char name[]);
回傳班級內所有學生的平均成績無條件捨去至整數
int getAverage(student_t s[], int n);


【輸入說明】
第一行輸入N ( 2 <= N <= 15 )，學生人數。
其後2*N行，依序輸入學生學號(字元長度小於20)和其對應的分數。

範例輸入：
2 (輸入2位同學)
Andy(輸入學生Andy)
50(Andy分數50)
Mike(輸入學生Mike)
60(Mike分數60)


【輸出說明】
第一行輸出班級內分數最高的姓名
第二行輸出班級內所有學生的平均成績並無條件捨去至整數


範例輸出：
Mike(分數最高的為Mike)
55(學生的平均成績為 (60+50)/2==55)


【測試資料一】
輸入：
3
Lion
72
Andy
84
Belly
92


輸出：
Belly
82

【測試資料二】
輸入：
6
Teddy
29
Grey
83
Windy
72
Kaye
90
Diff
80
Mandy
69

輸出：
Kaye
70

【測試資料三】

輸入：
10
Kat
89
Jake
80
Lan
50
Larry
83
Judy
60
Tina
82
Dina
49
Y
83
Oan
88
Bub
26

輸出：
Kat
69

*/

#include <stdio.h>

typedef struct student_s {
  char name[50];
  int score;
} student_t;

// 新增n位學生的資料
void input(student_t s[], int n);

// 回傳班級內分數最高的姓名(使用參數char name[])
void getHigh(student_t s[], int n, char name[]);

// 回傳班級內所有學生的平均成績無條件捨去至整數
int getAverage(student_t s[], int n);

int main() {
  int n = 0;
  char name[50];
  scanf("%d", &n);

  student_t students[n];
  input(students, n);

  getHigh(students, n, name);

  int avg = getAverage(students, n);
  printf("%d\n", avg);
  return 0;
}

void input(student_t s[], int n) {
  for (int i = 0; i < n; i++) {
    scanf("%s", s[i].name);
    scanf("%d", &s[i].score);
    // printf("%s, %d\n", s[i].name, s[i].score);
  }
}

void getHigh(student_t s[], int n, char name[]) {
  int Max_score = 0;
  for (int i = 0; i < n; i++) {
    if (i == 0) {
      name = s[i].name;
      Max_score = s[i].score;
    } else {
      if (s[i].score > Max_score) {
        Max_score = s[i].score;
        name = s[i].name;
      }
    }
  }
  printf("%s\n", name);
}

int getAverage(student_t s[], int n) {
  int sum = 0, avg = 0;
  for (int i = 0; i < n; i++) {
    sum += s[i].score;
  }
  // printf("sum: %d\n", sum);
  avg = sum / n;
  // printf("avg: %d\n", avg);
  return avg;
}