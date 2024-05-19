/*
22. 交錯字串

一個字串全由大寫英文字母組成稱為大寫字串；全由小寫字母組成稱為小寫字串。字串的長度是字母的個數。本題字串由大小寫英文字母組成。
k-交錯字串定義：
(1)
由長度為k的大寫字串與長度為k的小寫字串交错串接組成。例如「StRiNg」是一個1-交錯字串，因它是一個大寫一個小寫交替出現；而「heLLow」是一個2-交錯字串，因它是兩個小寫接兩個大寫再接兩個小寫。
(2) 不管k是多少，「aBBaaa」、「BaBaBB」、「aaaAAbbCCCC」都不是k-交錯字串。
對於給定k值，找出字串最長一段連續子字串滿足k交錯字串。例如 k=2
且字串「aBBaaa」，最長k-交錯字串是「BBaa」，長度為4。又如 k=1
且輸入「BaBaBB」，最長k-交錯字串是「BaBaB」，長度為5。

【輸入說明】
第一行為輸入一個整數N(1 <= N <= 5)，代表N個字串S。
其後N行，每一行輸入一個字串S (5 <= S長度 <= 50)、一個整數k，以空白隔開。

範例輸入說明:
5 (輸出5個字串)
fFwDbRaaNk 1 (輸入字串為fFwDbRaaNk，k = 1)
xxADAkwvDDXVxcxc 5 (輸入字串xxADAkwvDDXCVxcxc ，k = 5)
QSVxcDFnmFDScvQ 3 (輸入字串QSVxcDFnmFDScvQ，k = 3)
HXzxDSkYNefAT 2 (輸入字串HXzxDSkYNefAT，k = 2)
xzjhRVDWmTDJWksvx 4 ((輸入字串xzjhRVDWmTDJWksvx ，k = 4))

【輸出說明】
輸出每個字串中符合k-交錯字串的最長子字串長度，以換行隔開
若無符合的子字串輸出 0

範例輸出說明:
7 (最長1-交錯字串為"fFwDbRa", 長度為7)
0 (無符合5-交錯字串的子字串)
0 (無符合3-交錯字串的子字串)
6 (最長2-交錯字串為"HXzxDS"和"YNefAT", 長度為6)
8 (最長4-交錯字串為"xzjhRVDW"和"TDJWksvx", 長度為8)

【測試資料一】
輸入：
3
EaRDaRa 1
aARaaFBiegQFmjJGjc 2
mnnQidhGkxsGm 3

輸出：
4
10
0

【測試資料二】
輸入：
4
IiQqTtJjUuXxLlNnPkAaCcXtEgEeYz 1
PhlyJPvogRsaiQQfdUEjasdf 3
ulZDYlkTsdfVHsdOssfEMXalLY 2
QRGDJKSFDBB 5

輸出：
30
0
6
0

【測試資料三】

輸入：
5
svQWjxcEHGsornEFHNxmwjf 2
QBBswrHDNehvKGMjasdQHDeriSBNi 3
xbEUTHcNYovfZNdplEoK 1
olfGsoomAx 4
adjjQWFJF 5

輸出：
6
18
4
0
0

【測試資料四】
輸入：
2
KXcxbEjFFBJwGwyENADebwgkSv 4
tCFJsdcFSDolpHAEfZcWSj 3

輸出：
8
15

*/

#include <stdio.h>
#include <string.h>

// 判斷一個字母是否為大寫字母
int isUpperCase(char c) { return (c >= 'A' && c <= 'Z'); }

// 判斷一個字母是否為小寫字母
int isLowerCase(char c) { return (c >= 'a' && c <= 'z'); }

// 檢查一段字串是否為k-交錯字串
int isAlternatingSubstring(char *str, int k) {
  int len = strlen(str);
  int current_len = 0;
  int Max_len = 0;
  int state = 0;
  int current_state = 0;
  int breakout = 0;

  // 如果字串長度小於2k，則不可能存在k-交錯字串
  if (len < 2 * k) {
    return 0;
  }

  // printf("now string: %s\n", str);

  for (int i = 0; i < len; i++) {
    current_len = 0;

    // printf("     next: %s\n", str + i);

    for (int j = 0; j < strlen(str + i); j += k) {
      if (breakout == 1) {
        breakout = 0;
        break;
      }
      char *pos = str + i;

      if (isUpperCase(*(pos + j)))
        state = 1;
      else if (isLowerCase(*(pos + j)))
        state = 0;

      for (int m = 0; m < k; m++) {

        // printf("m: %d\n", m);
        // 都是小寫或大寫
        if (isUpperCase(pos[j + m]))
          current_state = 1;
        else if (isLowerCase(pos[j + m]))
          current_state = 0;

        // printf("  state: %d,   curr_state: %d\n", state, current_state);

        //  k個內項目狀態不同
        if (current_state != state) {
          // printf("state different\n");
          breakout = 1;
          break;
        }
        // 狀態相同
        else {
          // 更新狀態
          state = current_state;
          current_len++;

          // printf("state: %d, current_len: %d\n", state, current_len);
        }

        if (m == (k - 1)) {
          if (isUpperCase(pos[j + m + 1]))
            current_state = 1;
          else if (isLowerCase(pos[j + m + 1]))
            current_state = 0;
          // printf("future %d, %d\n", current_state, state);
          if (current_state == state) {
            breakout = 1;
            break;
          }
        }

        // printf("max_len: %d\n", Max_len);
      }
    }

    if (current_len % k != 0)
      current_len = (current_len / k) * k;

    if (current_len > Max_len)
      Max_len = current_len;
    // printf("max_len: %d\n", Max_len);
  }
  if (Max_len <= k) {
    return 0;
  }
  return Max_len;
}

int main() {
  int N;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    char str[51];
    int k;
    scanf("%s %d", str, &k);

    int maxLen = 0;
    int len = strlen(str);
    int current_len = 0;

    // 遍歷所有可能的連續子字串，找出最長的k-交錯字串
    for (int j = 0; j < len; j++) {
      current_len = isAlternatingSubstring(str + j, k);
      if (current_len > maxLen) {
        maxLen = current_len;
      }
    }

    printf("%d\n", maxLen);
  }

  return 0;
}
