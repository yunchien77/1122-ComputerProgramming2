/*
21. 互補單字
給定一個字串S，以及數個待比對字串Si, 1<=i<=n，輸出這些字串Si【互補對】的個數。

此題字串的定義：
(1) 英文字的集合，英文字重複出現只算一個，不考慮排列順序。例如 "Happy Happy Day"
與 "Day Happy Day" 是相同的字串。 (2)

兩個字串S1, S2為【互補對】的定義：
(1) S1, S2 沒有出現相同的字。
(2) S內的字，會全部出現在 S1 + S2內。

【輸入說明】
第1行，字串S。1<=英文字長度<=10，1<=英文字個數<=10，英文字以一個空白間隔，
第2行，整數 n，待比對字串Si 數量，2<=n<=10
第3~n+3行，字串Si，1<=英文字數量<=10，英文字以一個空白間隔，1<=每個英文字長度<=10

範例輸入說明:
happy birthday to you(字串S)
4(n，待比對字串數量)
happy to you(字串S1)
birthday birthday(字串S2)
to you(字串S3)
happy birthday(字串S4)

【輸出說明】
輸出【互補對】個數(整數)


範例輸出說明:
2
互補字串個數計算:
S1(happy to you) 跟 S2(birthday
birthday)，S1跟S2的英文字沒有重複，且字串S內的字恰好都被S1,
S2所包含，因此為互補字串。 S1(happy to you) 跟 S3(to you)，因為英文字 to 和 you
重複，不是互補字串 。 S1(happy to you) 跟 S4(happy birthday)，因為英文字 happy
重複，不是互補字串。 S2(birthday birthday) 跟 S3(to
you)，S1跟S2的字雖然沒重複，但字串S中的英文字happy沒有出現在S1或S2中，因此不是互補字串。
S2(birthday birthday) 跟 S4(happy birthday)，因為英文字 birthday
重複，不是互補字串。 S3(to you) 跟 S4(happy
birthday)，S1跟S2的英文字沒有重複，且字串S內的字恰好都被S1,
S2所包含，因此為互補字串。
根據上述互補字串個數計算，總共有兩個互補字串，答案為2。)

【測試資料一】
輸入:
I like to eat banana
4
like banana
I to eat
I like eat
to banana

輸出:
2

【測試資料二】
輸入 :
the raven is never backward
3
raven backward never
the backward raven
is never

輸出:
1


【測試資料三】
輸入 :
father mother son children friend parent
5
father mother
mother son children
children friend parent
father son friend
mother children

輸出：
0

【測試資料四】
輸入 :
MONDAY TUESDAY TUESDAY SATURDAY FRIDAY
4
MONDAY MONDAY
TUESDAY TUESDAY SATURDAY FRIDAY
TUESDAY SATURDAY FRIDAY
MONDAY SATURDAY

輸出：
2

【測試資料五】
輸入 :
the teacher teach the math to the student
4
the teacher to the student
teach math
teacher math
the teach to student

輸出：
2

【測試資料六】
輸入 :
he likes to eat dinner by himself
6
he likes to eat
dinner himself
by dinner
he likes eat himself
he eat himself
likes by dinner

輸出：
0

*/

#include <stdio.h>
#include <string.h>

// 檢查兩個字串是否為互補對
int isComplementaryPair(char *s1, char *s2, char *s) {
  char copy_s1[101], copy_s2[101], copy_s[101];
  strcpy(copy_s1, s1);
  strcpy(copy_s2, s2);
  strcpy(copy_s, s);

  // printf("%s, %s\n", copy_s1, copy_s2);
  char *token1, *token2;

  // 進行複製的 s1 的單字拆分
  token1 = strtok(copy_s1, " ");
  // printf("ggg %s\n", token1);
  while (token1 != NULL) {
    char *found = strstr(s2, token1);
    // printf("found: %s\n", found);
    if (found != NULL &&
        (*(found - 1) == ' ' || *(found + strlen(token1)) == ' ')) {
      // printf("i will come back\n");
      return 0; // s2 中存在 s1 的某個單字，不是互補對
    }
    token1 = strtok(NULL, " ");
    // printf("hhh %s\n", token1);
  }
  // printf("doneooo\n");

  // 進行複製的 s2 的單字拆分
  token2 = strtok(copy_s2, " ");
  // printf("ggg %s\n", token2);
  while (token2 != NULL) {
    // 每個單字都要從 s 中存在
    char *found = strstr(s1, token2);
    if (found != NULL && *(found - 1) == ' ' &&
        (*(found + strlen(token2)) == ' ' ||
         *(found + strlen(token2)) == '\0')) {
      // printf("i will come back too\n");
      return 0; // s1 中存在 s2 的某個單字，不是互補對
    }
    token2 = strtok(NULL, " ");
    // printf("aaa %s\n", token2);
  }
  // printf("done\n");

  char *token3 = strtok(copy_s, " ");
  while (token3 != NULL) {
    // printf("             %s\n", token3);
    char *found1 = strstr(s1, token3);
    char *found2 = strstr(s2, token3);
    if (found1 == NULL && found2 == NULL)
      return 0;
    token3 = strtok(NULL, " ");
    // printf("     %s\n", token3);
  }
  // printf("fffff\n");
  // printf("%s\n", copy_s);
  return 1; // s1 和 s2 是互補對
}

int main() {
  char s[101], si[10][101];
  int n;

  fgets(s, sizeof(s), stdin);
  s[strcspn(s, "\n")] = '\0'; // 移除換行符
  scanf("%d", &n);
  getchar();
  // printf("rrr %s\n", s);

  for (int i = 0; i < n; i++) {
    fgets(si[i], sizeof(si[i]), stdin);
    // scanf("%s", &si[i]);

    si[i][strcspn(si[i], "\n")] = '\0'; // 移除換行符
    // printf("reee %s\n", si[i]);
  }

  int count = 0;

  // 遍歷所有可能的組合，檢查是否為互補對
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (isComplementaryPair(si[i], si[j], s)) {
        count++;
      }
    }
  }

  printf("%d\n", count);

  return 0;
}
