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
