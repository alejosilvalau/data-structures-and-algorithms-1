//  Ejemplo de greedy

#include <stdio.h>
#define TOTAL_COUNT_OBJECTS 10
#define MAX_BACKPACK_WEIGHT 10

int n = TOTAL_COUNT_OBJECTS;
int weights[TOTAL_COUNT_OBJECTS] = {1, 3, 2, 5, 1, 3, 10, 1, 5, 2};
int profits[TOTAL_COUNT_OBJECTS] = {1, 15, 10, 12, 8, 10, 5, 20, 5, 10};
int backpackMaxWeight = MAX_BACKPACK_WEIGHT;

int main() {
  int backpackCurrentWeight;
  float backpackTotalProfits;
  int i, maxValueIndex;
  int used[TOTAL_COUNT_OBJECTS];
  for (i = 0; i < n; i++)
    used[i] = 0;
  backpackCurrentWeight = backpackMaxWeight;
  while (backpackCurrentWeight > 0) {
    maxValueIndex = -1;
    for (i = 0; i < n; i++)
      if ((used[i] == 0) &&
          ((maxValueIndex == -1) ||
           ((float)profits[i] / weights[i] >
            (float)profits[maxValueIndex] / weights[maxValueIndex])))
        maxValueIndex = i;
    used[maxValueIndex] = 1;
    backpackCurrentWeight -= weights[maxValueIndex];
    backpackTotalProfits += profits[maxValueIndex];
    if (backpackCurrentWeight >= 0)
      printf(
          "Added object %d (%d, %d) completely in the bag. Space left: %d.\n",
          maxValueIndex + 1, profits[maxValueIndex], weights[maxValueIndex],
          backpackCurrentWeight);
    else {
      printf("Added %d%% (%d, %d) of object %d in the bag.\n",
             (int)((1 + (float)backpackCurrentWeight / weights[maxValueIndex]) *
                   100),
             profits[maxValueIndex], weights[maxValueIndex], maxValueIndex + 1);
      backpackTotalProfits -= profits[maxValueIndex];
      backpackTotalProfits +=
          (1 + (float)backpackCurrentWeight / weights[maxValueIndex]) *
          profits[maxValueIndex];
    }
  }
  printf("Filled the bag with objects worth %.2f.\n", backpackTotalProfits);
  return 0;
}