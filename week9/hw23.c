/*
023 分數對照表

本題必須使用enum定義不同評分制資料型別，使用union定義分數資料型別，否則將不予計分。

評分類別:
typedef enum scoreType_s{G,GPA,S}scoreType_t;
等第評分:
typedef enum G_s{Aplus,A,Aduce,Bplus,B,Bduce,Cplus,C,Cduce,F,X}G_t;
GPA評分:
typedef enum
GPA_s{b4dot3,b4dot0,b3dot7,b3dot3,b3dot0,b2dot7,b2dot3,b2dot0,b1dot7,b1,b0}GPA_t;
百分制區間評分:
typedef enum S_s{b90to100,b85to89,b80to84,
b77to79,b73to76,b70to72,b67to69,b63to66,b60to62,b1to59,b0to0}S_t; 學生分數類型:
typedef union student_s{
int score;
G_t G;
GPA_t GPA;
S_t S;
}student_t;

一個班級有N位同學及M門課程，每一門課可以設定分數的評分方式。

設定M門課的評分方式，輸入N位同學的學號與其M門課的成績，
根據分數對照表進行換算，計算每一位同學百分制對照後的平均成績，並依照平均分數由小到大排序後，輸出所有同學的學號及其平均分數。

分數對照表如下：



評分方式的代號如下:
"G"代表等第評分，"GPA"代表GPA評分，"S"代表百分制區間評分。

【輸入說明】
第一行，輸入一整數 M ( 2 <= N <= 4 )，代表有M門課程。
其後M行，依序設定M門課的評分方式。
第M+1行，輸入一整數N (2 <= N <= 10 )，代表有N位同學。
其後N行，輸入該同學的學號，與該同學對應每一門課程的成績，字元間以空格符號相隔開。

範例輸入說明:
3 (三堂課)
G (第一堂課評分方式使用等第評分)
GPA (第二堂課評分方式使用GPA評分)
S (第三堂課評分方式使用百分制區間評分)
2 (兩位學生)
1001 A+ 4.3 90-100
(學號為1001，等第評分為A+，GPA評分為4.3，百分制區間評分為90-100) 1002 A 2.7 1-59
(學號為1002，等第評分為A，GPA評分為2.7，百分制區間評分為1-59)

【輸出說明】
第一行~第N行輸出同學的學號及其平均分數，字元間以空格符號相隔開，並依照平均分數由小到大排序，平均分數如有小數則無條件捨去。

範例輸出說明:
1002 69
(學號1002的學生，第一堂課對應的分數為87，第二堂課對應的分數為70，第三堂課對應的分數為50，平均分數為(87+70+50)/3=69，無條件捨去小數)
1001 95
(學號1001的學生，第一堂課對應的分數為95，第二堂課對應的分數為95，第三堂課對應的分數為95，平均分數為(95+95+95)/3=95，無條件捨去小數)

【測試資料一】
輸入：
1
G
3
1001 A+
1002 F
1003 B-

輸出：
1002 50
1003 70
1001 95

【測試資料二】
輸入：
2
G
GPA
5
1001 B- 3.7
1002 A+ 0
1003 A 4.3
1004 X 0
1005 C- 1.7

輸出：
1004 0
1002 47
1005 60
1001 76
1003 91

【測試資料三】
輸入：
3
GPA
G
S
4
1002 4.3 A+ 90-100
1007 1 C 85-89
1006 2.7 F 73-76
1010 3.3 A- 67-69

輸出：
1006 65
1007 67
1010 76
1002 95

【測試資料四】
輸入：
4
G
GPA
G
S
8
1005 A+ 2.0 C+ 90-100
1011 B- 4.3 A 0
1010 X 0 X 0
1001 X 0 A 80-84
1002 B+ 2.3 B- 63-66
1004 F 1.7 A 1-59
1034 A+ 4.3 A+ 90-100
1009 A 4.0 A 85-89

輸出：
1010 0
1001 42
1004 61
1011 63
1002 70
1005 80
1009 87
1034 95

*/

#include <stdio.h>
#include <string.h>

typedef enum scoreType_s { G, GPA, S } scoreType_t;
// 等第評分
typedef enum G_s {
  Aplus, // 0
  A,     // 1
  Aduce, // 2
  Bplus, // 3
  B,     // 4
  Bduce, // 5
  Cplus, // 6
  C,     // 7
  Cduce, // 8
  F,     // 9
  X      // 10
} G_t;

// GPA評分
typedef enum GPA_s {
  b4dot3, // 0
  b4dot0, // 1
  b3dot7, // 2
  b3dot3, // 3
  b3dot0, // 4
  b2dot7, // 5
  b2dot3, // 6
  b2dot0, // 7
  b1dot7, // 8
  b1,     // 9
  b0      // 10
} GPA_t;

// 百分制區間評分
typedef enum S_s {
  b90to100, // 0
  b85to89,  // 1
  b80to84,  // 2
  b77to79,  // 3
  b73to76,  // 4
  b70to72,  // 5
  b67to69,  // 6
  b63to66,  // 7
  b60to62,  // 8
  b1to59,   // 9
  b0to0     // 10
} S_t;

// 學生分數類型
typedef union student_s {
  int score;
  G_t G;
  GPA_t GPA;
  S_t S;
} student_t;

typedef struct {
  int id;
  student_t scores[4];
  int avg_score;
} student_info_t;

void sort(student_info_t students[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (students[j].avg_score > students[j + 1].avg_score) {
        student_info_t temp = students[j];
        students[j] = students[j + 1];
        students[j + 1] = temp;
      }
    }
  }
}

int main() {
  int m, n;
  char type[4] = "";
  scanf("%d", &m);
  getchar();

  scoreType_t score[m];
  // char s[11][6] = {"90-100", "85-89", "80-84", "77-79", "73-76",
  // "70-72","67-69",  "63-66", "60-62", "1-59",  "0"}; float gpa[11][3] =
  // {4.3, 4.0, 3.7, 3.3, 3.0, 2.7, 2.3, 2.0, 1.7, 1, 0}; char g[11][3] = {"A+",
  // "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "F", "X"};
  int transform[] = {95, 87, 82, 78, 75, 70, 68, 65, 60, 50, 0};

  for (int i = 0; i < m; i++) {
    fgets(type, sizeof(type) + 1, stdin);
    type[strcspn(type, "\n")] = '\0'; // 移除換行符
    // printf("%d type: %s\n", i, type);

    if (strcmp(type, "G") == 0) {
      score[i] = G;
    } else if (strcmp(type, "GPA") == 0) {
      score[i] = GPA;
    } else if (strcmp(type, "S") == 0) {
      score[i] = S;
    }
  }
  /*
    for (int i = 0; i < m; i++) {
      printf("fff %d\n", score[i]);
    }
  */
  scanf("%d", &n);
  student_info_t students[n];
  int id = 0;

  for (int i = 0; i < n; i++) {
    // printf("i: %d\n", i);
    scanf("%d", &id);
    getchar();
    students[i].id = id;
    // printf("input end %d\n", students[i].id);

    for (int j = 0; j < m; j++) {
      switch (score[j]) {
      case G: {
        char grade[3];
        // fgets(grade, sizeof(grade), stdin);
        // grade[strcspn(grade, "\n")] = '\0'; // 移除換行符
        scanf("%s", grade);
        // printf("%s\n", grade);
        if (strcmp(grade, "A+") == 0)
          students[i].scores[j].G = Aplus;
        else if (strcmp(grade, "A") == 0)
          students[i].scores[j].G = A;
        else if (strcmp(grade, "A-") == 0)
          students[i].scores[j].G = Aduce;
        else if (strcmp(grade, "B+") == 0)
          students[i].scores[j].G = Bplus;
        else if (strcmp(grade, "B") == 0)
          students[i].scores[j].G = B;
        else if (strcmp(grade, "B-") == 0)
          students[i].scores[j].G = Bduce;
        else if (strcmp(grade, "C+") == 0)
          students[i].scores[j].G = Cplus;
        else if (strcmp(grade, "C") == 0)
          students[i].scores[j].G = C;
        else if (strcmp(grade, "C-") == 0)
          students[i].scores[j].G = Cduce;
        else if (strcmp(grade, "F") == 0)
          students[i].scores[j].G = F;
        else if (strcmp(grade, "X") == 0)
          students[i].scores[j].G = X;
        break;
      }
      case GPA: {
        float gpa;
        scanf("%f", &gpa);
        // printf("%.1f\n", gpa);
        if (gpa == 4.3f)
          students[i].scores[j].GPA = b4dot3;
        else if (gpa == 4.0f)
          students[i].scores[j].GPA = b4dot0;
        else if (gpa == 3.7f)
          students[i].scores[j].GPA = b3dot7;
        else if (gpa == 3.3f)
          students[i].scores[j].GPA = b3dot3;
        else if (gpa == 3.0f)
          students[i].scores[j].GPA = b3dot0;
        else if (gpa == 2.7f)
          students[i].scores[j].GPA = b2dot7;
        else if (gpa == 2.3f)
          students[i].scores[j].GPA = b2dot3;
        else if (gpa == 2.0f)
          students[i].scores[j].GPA = b2dot0;
        else if (gpa == 1.7f)
          students[i].scores[j].GPA = b1dot7;
        else if (gpa == 1.0f)
          students[i].scores[j].GPA = b1;
        else if (gpa == 0.0f)
          students[i].scores[j].GPA = b0;
        break;
      }

      case S: {
        char section[8];
        scanf("%s", section);
        if (strcmp(section, "90-100") == 0)
          students[i].scores[j].S = b90to100;
        else if (strcmp(section, "85-89") == 0)
          students[i].scores[j].S = b85to89;
        else if (strcmp(section, "80-84") == 0)
          students[i].scores[j].S = b80to84;
        else if (strcmp(section, "77-79") == 0)
          students[i].scores[j].S = b77to79;
        else if (strcmp(section, "73-76") == 0)
          students[i].scores[j].S = b73to76;
        else if (strcmp(section, "70-72") == 0)
          students[i].scores[j].S = b70to72;
        else if (strcmp(section, "67-69") == 0)
          students[i].scores[j].S = b67to69;
        else if (strcmp(section, "63-66") == 0)
          students[i].scores[j].S = b63to66;
        else if (strcmp(section, "60-62") == 0)
          students[i].scores[j].S = b60to62;
        else if (strcmp(section, "1-59") == 0)
          students[i].scores[j].S = b1to59;
        else if (strcmp(section, "0") == 0)
          students[i].scores[j].S = b0to0;
        break;
      }
      }
      // printf("nnnnnnexttttttttt~\n");
      //  getchar();
    }
    // printf("yyyyyyyyyy~\n");
  }

  int sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      switch (score[j]) {
      case G:
        // printf("111    %d\n", (int)students[i].scores[j].G);
        // printf("aaa     %d\n", transform[(int)students[i].scores[j].G]);
        sum += transform[(int)students[i].scores[j].G];
        // printf("ssssssssum: %d\n", sum);
        break;
      case GPA:
        // printf("222    %d\n", (int)students[i].scores[j].GPA);
        sum += transform[(int)students[i].scores[j].GPA];
        break;
      case S:
        // printf("333    %d\n", (int)students[i].scores[j].S);
        sum += transform[(int)students[i].scores[j].S];
        break;
      }
      // printf("sum: %d\n", sum);
    }
    students[i].avg_score = (sum / m);
    // printf("dddd     %d\n", students[i].avg_score);
    sum = 0;
  }

  sort(students, n);

  for (int i = 0; i < n; i++) {
    printf("%d %d\n", students[i].id, students[i].avg_score);
  }

  return 0;
}