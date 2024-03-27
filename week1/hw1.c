#include <stdio.h>

int main() {
  int w, h;
  float bmi;
  scanf("%d", &w);
  scanf("%d", &h);

  bmi = (float)w / ((float)h / 100 * (float)h / 100);
  printf("%.1f\n", bmi);

  return 0;
}